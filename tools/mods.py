###
# Support for `configure.py --mod`: mod discovery and hook resolution.
#
# A mod is a directory of C translation units compiled with the game's
# toolchain and appended to the DOL link order. A mod hooks a game function
# simply by defining a function with the same name; the build detects this
# from the compiled mod objects (`elf_hook.py --scan` writes a manifest that
# feeds back into configure through the ninja regeneration loop, the same way
# config.json bootstraps the build graph). The hooked function's defining
# object is rewritten so every caller rebinds to the mod's definition, while
# `orig_<name>` stays callable for wrappers (an ordinary extern declaration).
#
# Hook targets are resolved from config/<version>/symbols.txt and splits.txt.
###

import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Tuple

HOOK_PREFIX = "orig_"

SYMBOL_RE = re.compile(
    r"^(?P<name>[^\s=]+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9A-Fa-f]+);\s*//\s*(?P<attrs>.*)$"
)
SPLIT_UNIT_RE = re.compile(r"^(?P<unit>\S.*?):\s*(?P<attrs>.*)$")
SPLIT_RANGE_RE = re.compile(
    r"^\s+(?P<section>\S+)\s+start:(?P<start>0x[0-9A-Fa-f]+)\s+end:(?P<end>0x[0-9A-Fa-f]+)"
)


@dataclass
class SymbolInfo:
    name: str
    section: str
    addr: int
    kind: Optional[str]  # type: attribute (function/object/label)
    scope: str  # global/local/weak (global when unspecified)


@dataclass
class ModInfo:
    path: Path
    name: str
    sources: List[Path]
    defines: List[str] = field(default_factory=list)
    includes: List[str] = field(default_factory=list)  # relative to the mod dir


def parse_symbols_txt(path: Path) -> Dict[str, List[SymbolInfo]]:
    symbols: Dict[str, List[SymbolInfo]] = {}
    with open(path, encoding="utf-8") as f:
        for line in f:
            m = SYMBOL_RE.match(line)
            if m is None:
                continue
            kind: Optional[str] = None
            scope = "global"
            for attr in m.group("attrs").split():
                if attr.startswith("type:"):
                    kind = attr[len("type:") :]
                elif attr.startswith("scope:"):
                    scope = attr[len("scope:") :]
            sym = SymbolInfo(
                name=m.group("name"),
                section=m.group("section"),
                addr=int(m.group("addr"), 16),
                kind=kind,
                scope=scope,
            )
            symbols.setdefault(sym.name, []).append(sym)
    return symbols


def parse_splits_txt(path: Path) -> List[Tuple[str, str, int, int]]:
    """Returns (unit, section, start, end) for every split range."""
    ranges: List[Tuple[str, str, int, int]] = []
    unit: Optional[str] = None
    with open(path, encoding="utf-8") as f:
        for line in f:
            m = SPLIT_UNIT_RE.match(line)
            if m is not None:
                unit = m.group("unit")
                if unit == "Sections":  # section declaration preamble
                    unit = None
                continue
            m = SPLIT_RANGE_RE.match(line)
            if m is not None and unit is not None:
                ranges.append(
                    (
                        unit,
                        m.group("section"),
                        int(m.group("start"), 16),
                        int(m.group("end"), 16),
                    )
                )
    return ranges


def discover_mod(mod_dir: Path) -> ModInfo:
    if not mod_dir.is_dir():
        sys.exit(f"Mod directory not found: {mod_dir}")
    name = mod_dir.name
    defines: List[str] = []
    includes: List[str] = []
    toml_path = mod_dir / "mod.toml"
    if toml_path.is_file():
        try:
            import tomllib
        except ImportError:
            sys.exit(f"{toml_path} exists but Python lacks tomllib (needs 3.11+)")
        with open(toml_path, "rb") as f:
            data = tomllib.load(f).get("mod", {})
        name = data.get("name", name)
        defines = list(data.get("defines", []))
        includes = list(data.get("includes", []))
    src_dir = mod_dir / "src"
    sources = sorted(src_dir.rglob("*.c")) if src_dir.is_dir() else []
    return ModInfo(
        path=mod_dir, name=name, sources=sources, defines=defines, includes=includes
    )


def load_hook_scan(path: Path) -> Optional[dict]:
    """Loads the manifest written by `elf_hook.py --scan`, or None before the
    first build has produced it (the ninja regeneration loop converges)."""
    if not path.is_file():
        return None
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def resolve_hooks(
    scan: Optional[dict],
    obj_to_unit: Dict[str, Tuple[str, str]],  # object path -> (mod name, unit)
    symbols_txt: Path,
    splits_txt: Path,
) -> Tuple[
    Dict[str, List[Tuple[str, str]]],  # game unit -> [(old, new)] renames
    Dict[str, List[str]],  # game unit -> local hook names
    Dict[str, List[str]],  # mod unit -> hook_-prefixed wrapper targets
]:
    if scan is None:
        return {}, {}, {}

    symbols = parse_symbols_txt(symbols_txt)
    ranges = parse_splits_txt(splits_txt)

    def owning_unit(sym: SymbolInfo) -> Optional[str]:
        return next(
            (
                u
                for u, section, start, end in ranges
                if section == sym.section and start <= sym.addr < end
            ),
            None,
        )

    hooks: Dict[str, Tuple[str, str]] = {}  # name -> (mod name, mod unit)
    renames: Dict[str, List[Tuple[str, str]]] = {}
    local_hooks: Dict[str, List[str]] = {}
    hook_wraps: Dict[str, List[str]] = {}

    for obj_path, entry in sorted(scan.get("objects", {}).items()):
        if obj_path not in obj_to_unit:
            continue  # stale manifest entry; the scan edge will refresh it
        mod_name, mod_unit = obj_to_unit[obj_path]
        for defined_name, kind in entry.get("defined", {}).items():
            # An exact game-symbol match hooks it directly; a hook_<name>
            # wrapper hooks <name> and calls the original by its real name.
            name = defined_name
            infos = symbols.get(name)
            wrapper = False
            if not infos and defined_name.startswith("hook_"):
                name = defined_name[len("hook_") :]
                infos = symbols.get(name)
                wrapper = infos is not None
                if not wrapper:
                    print(
                        f"warning: {defined_name} in {mod_unit} matches no "
                        "game symbol; not a hook",
                        file=sys.stderr,
                    )
            if not infos:
                continue  # plain mod helper
            where = f"{mod_unit} (mod {mod_name})"
            if len(infos) > 1:
                sys.exit(f"Hook error: {name} ({where}) is defined more than once in {symbols_txt}")
            sym = infos[0]
            if sym.kind != "function" or kind != "func":
                sys.exit(
                    f"Hook error: {name} ({where}) collides with game symbol "
                    f"{sym.section}:{sym.addr:#x} (type:{sym.kind}); only "
                    "functions can be interposed"
                )
            if sym.scope == "weak":
                sys.exit(
                    f"Hook error: {name} ({where}) is scope:weak (an inline "
                    "function with copies in multiple units) and cannot be hooked"
                )
            if name in hooks:
                other_mod, other_unit = hooks[name]
                sys.exit(
                    f"Hook error: {name} is defined by both {other_unit} "
                    f"(mod {other_mod}) and {where}"
                )
            unit = owning_unit(sym)
            if unit is None:
                sys.exit(
                    f"Hook error: no unit in {splits_txt} covers {name} at "
                    f"{sym.section}:{sym.addr:#x}"
                )
            hooks[name] = (mod_name, mod_unit)
            if sym.scope == "local":
                local_hooks.setdefault(unit, []).append(name)
            else:
                renames.setdefault(unit, []).append((name, HOOK_PREFIX + name))
            if wrapper:
                hook_wraps.setdefault(mod_unit, []).append(name)
            print(f"hook: {name} ({sym.scope}, {unit}) <- {mod_name}")

    # A mod may call orig_<name> from any TU, but only if something hooks <name>
    for obj_path, entry in sorted(scan.get("objects", {}).items()):
        if obj_path not in obj_to_unit:
            continue
        mod_name, mod_unit = obj_to_unit[obj_path]
        for name in entry.get("undefined", []):
            if not name.startswith(HOOK_PREFIX):
                continue
            base = name[len(HOOK_PREFIX) :]
            if base in symbols and base not in hooks:
                sys.exit(
                    f"Hook error: {mod_unit} (mod {mod_name}) calls {name} "
                    f"but no mod defines {base}"
                )

    return renames, local_hooks, hook_wraps
