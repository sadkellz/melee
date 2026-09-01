###
# Symbol surgery for mod hooks (see docs/modding.md).
#
# Modes:
#
#   --scan OUT OBJ...    Read mod objects and write a JSON manifest of their
#                        defined globals and undefined references. configure.py
#                        derives the hook set from it (a mod hooks a game
#                        function simply by defining a function with its name).
#                        The manifest is only rewritten when its content
#                        changes, and the ninja rule uses restat, so the
#                        configure/scan loop converges.
#
#   [flags] IN OUT       Rewrite one relocatable ELF32 BE object:
#     --redefine OLD=NEW   Rename the defined symbol OLD to NEW (global hooks;
#                          the renamed original stays callable as NEW).
#     --local NAME         Hook the local (static) function NAME: rename the
#                          definition to orig_NAME and make it global in place,
#                          add an undefined global NAME, and retarget every
#                          entry reference (relocations with addend 0) to it.
#                          The linker then resolves those intra-unit calls to
#                          the mod's definition of NAME.
#     --hook-wrap NAME     Applied to the mod object: rename the definition
#                          hook_NAME to NAME so it takes over the hooked
#                          symbol, and retarget references to NAME from within
#                          the wrapper's own body to orig_NAME — so the
#                          wrapper calls the original by its real (game
#                          header-declared) name, with no DECL_ORIG.
#
# mwld notes that shaped this tool: it resolves symbols by name (a same-named
# local in the same object shadows an undefined global, hence the renames); it
# computes liveness and emits code per symbol (so renamed definitions must
# have their MW-comment "active" flag set or their whole outgoing reference
# graph is deadstripped, and an alias symbol would duplicate the body).
# Relocations with a nonzero addend (jump tables, labels into the body) and
# extab references keep pointing at the original definition. The MW .comment
# section holds one 8-byte record per symtab entry ({align:u32, vis:u8,
# active:u8, pad:u16}), maintained in lockstep with symtab edits.
#
# With no flags, the object is copied through byte-identically.
###

import argparse
import json
import struct
import sys
from pathlib import Path
from typing import Dict, List, Optional

SHT_NOBITS = 8
SHT_RELA = 4
SHT_SYMTAB = 2
SHN_UNDEF = 0
SHN_ABS = 0xFFF1
STB_LOCAL = 0
STB_GLOBAL = 1
STB_WEAK = 2
STT_NOTYPE = 0
STT_OBJECT = 1
STT_FUNC = 2

EHDR_FMT = ">16sHHIIIIIHHHHHH"
SHDR_FMT = ">10I"
SYM_FMT = ">IIIBBH"
RELA_FMT = ">IIi"
COMMENT_HEADER_SIZE = 0x2C
COMMENT_RECORD_SIZE = 8
COMMENT_ACTIVE_FLAG = 0x08


def fail(msg: str):
    sys.exit(f"elf_hook: {msg}")


class ElfObject:
    def __init__(self, path: Path):
        self.path = path
        data = path.read_bytes()
        (
            e_ident,
            self.e_type,
            self.e_machine,
            self.e_version,
            self.e_entry,
            self.e_phoff,
            e_shoff,
            self.e_flags,
            self.e_ehsize,
            self.e_phentsize,
            self.e_phnum,
            self.e_shentsize,
            self.e_shnum,
            self.e_shstrndx,
        ) = struct.unpack_from(EHDR_FMT, data, 0)
        if e_ident[:4] != b"\x7fELF" or e_ident[4] != 1 or e_ident[5] != 2:
            fail(f"{path} is not a big-endian ELF32 object")
        self.e_ident = e_ident
        # sh_: 0 name, 1 type, 2 flags, 3 addr, 4 offset, 5 size, 6 link,
        #      7 info, 8 addralign, 9 entsize
        self.shdrs = [
            list(struct.unpack_from(SHDR_FMT, data, e_shoff + i * self.e_shentsize))
            for i in range(self.e_shnum)
        ]
        self.bodies = [
            (
                bytearray(data[s[4] : s[4] + s[5]])
                if s[1] != SHT_NOBITS
                else bytearray()
            )
            for s in self.shdrs
        ]
        self.symtab_idx = next(
            (i for i, s in enumerate(self.shdrs) if s[1] == SHT_SYMTAB), None
        )
        if self.symtab_idx is None:
            fail(f"no symbol table in {path}")
        if self.shdrs[self.symtab_idx][9] != 16:
            fail(f"unexpected symtab entry size in {path}")
        self.strtab_idx = self.shdrs[self.symtab_idx][6]
        symtab = self.bodies[self.symtab_idx]
        # st_: 0 name, 1 value, 2 size, 3 info, 4 other, 5 shndx
        self.syms = [
            list(struct.unpack_from(SYM_FMT, symtab, i * 16))
            for i in range(len(symtab) // 16)
        ]
        self.orig_nsyms = len(self.syms)
        self.comment_idx = next(
            (i for i in range(1, self.e_shnum) if self.sec_name(i) == ".comment"),
            None,
        )

    def sec_name(self, idx: int) -> str:
        strs = self.bodies[self.e_shstrndx]
        off = self.shdrs[idx][0]
        return strs[off : strs.index(b"\0", off)].decode()

    def sym_name(self, idx: int) -> str:
        strs = self.bodies[self.strtab_idx]
        off = self.syms[idx][0]
        return strs[off : strs.index(b"\0", off)].decode()

    def add_str(self, s: str) -> int:
        strtab = self.bodies[self.strtab_idx]
        off = len(strtab)
        strtab.extend(s.encode() + b"\0")
        return off

    def find_defined(self, name: str) -> int:
        matches = [
            i
            for i in range(1, len(self.syms))
            if self.syms[i][5] != SHN_UNDEF and self.sym_name(i) == name
        ]
        if not matches:
            fail(f"no defined symbol {name} in {self.path}")
        if len(matches) > 1:
            fail(f"multiple defined symbols named {name} in {self.path}")
        return matches[0]

    def check_comment(self):
        if self.comment_idx is None:
            return
        expected = COMMENT_HEADER_SIZE + COMMENT_RECORD_SIZE * len(self.syms)
        if len(self.bodies[self.comment_idx]) != expected:
            fail(
                f".comment size {len(self.bodies[self.comment_idx])} does not "
                f"match {len(self.syms)} symbols (expected {expected}) in "
                f"{self.path}; refusing to guess"
            )

    def set_active(self, idx: int):
        # mwld computes liveness per symbol; a renamed definition is no longer
        # referenced under its original name, so nothing roots it and its
        # entire outgoing reference graph would be deadstripped. Setting the
        # MW comment "active" flag roots it unconditionally, the way dtk marks
        # every extracted symbol.
        if self.comment_idx is not None:
            off = COMMENT_HEADER_SIZE + COMMENT_RECORD_SIZE * idx + 5
            self.bodies[self.comment_idx][off] |= COMMENT_ACTIVE_FLAG

    def append_sym(self, entry: List[int], comment_record: bytes) -> int:
        self.syms.append(entry)
        if self.comment_idx is not None:
            self.bodies[self.comment_idx].extend(comment_record)
        return len(self.syms) - 1

    def undef_comment_template(self) -> bytes:
        idx = next(
            (i for i in range(1, self.orig_nsyms) if self.syms[i][5] == SHN_UNDEF),
            None,
        )
        if idx is not None and self.comment_idx is not None:
            off = COMMENT_HEADER_SIZE + COMMENT_RECORD_SIZE * idx
            return bytes(self.bodies[self.comment_idx][off : off + 8])
        return b"\0" * COMMENT_RECORD_SIZE

    def add_undef(self, name_off: Optional[int] = None, name: Optional[str] = None) -> int:
        if name_off is None:
            name_off = self.add_str(name or "")
        return self.append_sym(
            [name_off, 0, 0, (STB_GLOBAL << 4) | STT_NOTYPE, 0, SHN_UNDEF],
            self.undef_comment_template(),
        )

    def rela_sections(self):
        for i, s in enumerate(self.shdrs):
            if s[1] != SHT_RELA or s[6] != self.symtab_idx:
                continue
            if self.sec_name(s[7]) in ("extab", "extabindex"):
                continue
            yield i, s

    def retarget(self, matcher, new_idx: int) -> int:
        """Points relocations accepted by matcher(target_shndx, r_offset,
        sym_idx, addend) at symbol new_idx; returns how many changed."""
        total = 0
        for i, s in self.rela_sections():
            body = self.bodies[i]
            for off in range(0, len(body), 12):
                r_offset, r_info, r_addend = struct.unpack_from(RELA_FMT, body, off)
                if matcher(s[7], r_offset, r_info >> 8, r_addend):
                    struct.pack_into(
                        RELA_FMT,
                        body,
                        off,
                        r_offset,
                        (new_idx << 8) | (r_info & 0xFF),
                        r_addend,
                    )
                    total += 1
        return total

    def write(self, out_path: Path):
        symtab = bytearray()
        for st in self.syms:
            symtab.extend(struct.pack(SYM_FMT, *st))
        self.bodies[self.symtab_idx] = symtab

        order = sorted(range(1, self.e_shnum), key=lambda i: (self.shdrs[i][4], i))
        out = bytearray(
            struct.pack(
                EHDR_FMT,
                self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                0,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx,
            )
        )
        for i in order:
            s = self.shdrs[i]
            align = max(s[8], 1)
            pos = (len(out) + align - 1) & ~(align - 1)
            out.extend(b"\0" * (pos - len(out)))
            s[4] = pos
            if s[1] != SHT_NOBITS:
                s[5] = len(self.bodies[i])
                out.extend(self.bodies[i])
        pos = (len(out) + 3) & ~3
        out.extend(b"\0" * (pos - len(out)))
        struct.pack_into(">I", out, 32, pos)  # e_shoff
        for s in self.shdrs:
            out.extend(struct.pack(SHDR_FMT, *s))
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_bytes(out)


def do_scan(out_path: Path, inputs: List[Path]):
    manifest: Dict[str, Dict] = {}
    for path in sorted(inputs):
        obj = ElfObject(path)
        defined: Dict[str, str] = {}
        undefined: List[str] = []
        for i in range(1, len(obj.syms)):
            st = obj.syms[i]
            bind, kind = st[3] >> 4, st[3] & 0xF
            if bind == STB_LOCAL:
                continue
            name = obj.sym_name(i)
            if not name:
                continue
            if st[5] == SHN_UNDEF:
                undefined.append(name)
            elif st[5] != SHN_ABS:
                defined[name] = {STT_FUNC: "func", STT_OBJECT: "object"}.get(
                    kind, "other"
                )
        manifest[path.as_posix()] = {
            "defined": dict(sorted(defined.items())),
            "undefined": sorted(undefined),
        }
    text = json.dumps({"objects": manifest}, indent=2) + "\n"
    if out_path.exists() and out_path.read_text(encoding="utf-8") == text:
        return  # unchanged; with restat=1 ninja skips downstream work
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(text, encoding="utf-8")


def do_surgery(args):
    if not args.redefine and not args.local and not args.hook_wrap:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_bytes(args.input.read_bytes())
        return

    obj = ElfObject(args.input)
    obj.check_comment()

    # --redefine: repoint the defined symbol's name; the renamed definition
    # must stay rooted (see set_active)
    for spec in args.redefine:
        old, sep, new = spec.partition("=")
        if not sep or not old or not new:
            fail(f"bad --redefine spec: {spec}")
        ri = obj.find_defined(old)
        obj.syms[ri][0] = obj.add_str(new)
        obj.set_active(ri)

    # --local: rename the definition to orig_<name> and make it global in
    # place (mwld resolves by name, so the undefined hook target must not
    # have a same-named local sibling; a separate alias symbol is no good
    # either, since mwld emits per-symbol atoms and would duplicate the
    # body), then retarget entry references to an undefined global <name>
    for name in args.local:
        li = obj.find_defined(name)
        st = obj.syms[li]
        if st[3] >> 4 != STB_LOCAL or st[3] & 0xF != STT_FUNC:
            fail(f"{name} in {args.input} is not a local function")
        old_name_off = st[0]
        st[0] = obj.add_str(f"orig_{name}")
        st[3] = (STB_GLOBAL << 4) | STT_FUNC
        obj.set_active(li)
        undef_idx = obj.add_undef(name_off=old_name_off)
        n = obj.retarget(
            lambda shndx, r_off, sym, addend: sym == li and addend == 0,
            undef_idx,
        )
        print(f"elf_hook: {args.input}: hooked local {name} ({n} references)")
        if n == 0:
            print(
                f"elf_hook: warning: no entry references to {name} in {args.input}",
                file=sys.stderr,
            )

    # --hook-wrap: hook_<name> takes over <name>; inside its body, calls to
    # <name> reach the original. Being a distinct external symbol, the call
    # cannot be collapsed by the compiler the way self-recursion is.
    for name in args.hook_wrap:
        wi = obj.find_defined(f"hook_{name}")
        st = obj.syms[wi]
        if st[3] >> 4 == STB_LOCAL or st[3] & 0xF != STT_FUNC:
            fail(f"hook_{name} in {args.input} is not a global function")
        und_idx = next(
            (
                i
                for i in range(1, len(obj.syms))
                if obj.syms[i][5] == SHN_UNDEF and obj.sym_name(i) == name
            ),
            None,
        )
        st[0] = obj.add_str(name)
        obj.set_active(wi)
        n = 0
        if und_idx is not None and st[2] > 0:
            def_sec, lo, hi = st[5], st[1], st[1] + st[2]

            def in_body(shndx, r_off, sym, addend, ds=def_sec, ui=und_idx, lo=lo, hi=hi):
                return shndx == ds and sym == ui and addend == 0 and lo <= r_off < hi

            orig_name = f"orig_{name}"
            orig_idx = next(
                (
                    i
                    for i in range(1, len(obj.syms))
                    if obj.syms[i][5] == SHN_UNDEF and obj.sym_name(i) == orig_name
                ),
                None,
            )
            if orig_idx is None:
                orig_idx = obj.add_undef(name=orig_name)
            n = obj.retarget(in_body, orig_idx)
        print(f"elf_hook: {args.input}: hook_{name} -> {name} ({n} original calls)")

    obj.write(args.output)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--scan", type=Path, metavar="OUT")
    parser.add_argument("--redefine", action="append", default=[], metavar="OLD=NEW")
    parser.add_argument("--local", action="append", default=[], metavar="NAME")
    parser.add_argument("--hook-wrap", action="append", default=[], metavar="NAME")
    parser.add_argument("files", nargs="+", type=Path)
    args = parser.parse_args()

    if args.scan is not None:
        if args.redefine or args.local or args.hook_wrap:
            fail("--scan cannot be combined with surgery flags")
        do_scan(args.scan, args.files)
        return
    if len(args.files) != 2:
        fail("expected: [flags] INPUT OUTPUT")
    args.input, args.output = args.files
    do_surgery(args)


if __name__ == "__main__":
    main()
