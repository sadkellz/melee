#!/usr/bin/env python3
"""
Inventories every pointer cast and byte-offset walk in the source tree.

Each site is classified once by its outermost form, so `*(f32*) ((u8*) p + 0xE0)`
counts as one cast+offset rather than as three separate casts. The sites that move
a pointer by a literal constant are the ones worth chasing: each is a struct field
that has not been named yet.

Usage:
    python tools/ptr_casts.py                       # summary to stdout
    python tools/ptr_casts.py --tsv -               # TSV to stdout
    python tools/ptr_casts.py --out build/ptr-casts # index.html + ptr_casts.tsv
"""

import argparse
import bisect
import json
import re
import sys
from collections import Counter
from pathlib import Path
from typing import Iterator, NamedTuple

ROOT = Path(__file__).resolve().parent.parent
TEMPLATE = Path(__file__).resolve().parent / "ptr-casts-template.html"

# Types that never name a struct, used to split plain casts into two buckets.
PRIMITIVES = {
    "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64",
    "char", "short", "int", "long", "void", "unsigned", "signed",
    "float", "double", "uintptr_t", "intptr_t", "size_t", "bool",
}

# A type name as it appears inside a cast, e.g. `const struct Foo`, `unsigned long`.
TYPE = (
    r"(?:const\s+|volatile\s+|struct\s+|union\s+|unsigned\s+|signed\s+)*"
    r"[A-Za-z_]\w*(?:\s+(?:int|char|long|short))?"
)

CAST = re.compile(r"\(\s*(" + TYPE + r")\s*(\*+)\s*\)\s*(?=[A-Za-z_&(*])")
OFFSET = re.compile(
    r"\(\s*(" + TYPE + r")\s*(\*+)\s*\)\s*"          # the cast
    r"\(?\s*&?[A-Za-z_][\w.\[\]]*(?:\s*->\s*\w+)*\s*\)?"  # the operand
    r"\s*([-+])\s*(0[xX][0-9a-fA-F]+|\d+)\b"         # the constant
)
DEREF = re.compile(r"(?<![\w\)\]])\*\s*\(\s*(" + TYPE + r")\s*(\*+)\s*\)")
INDEX = re.compile(r"\(\s*\(\s*(" + TYPE + r")\s*(\*+)\s*\)[^()]{1,40}\)\s*\[")
ABSOLUTE = re.compile(r"\(\s*(" + TYPE + r"\s*\*+)\s*\)\s*\(?\s*(0[xX][0-9a-fA-F]{6,8})\b")
# Narrow casts are excluded: a pointer is never truncated to u8 or s16.
TO_INT = re.compile(
    r"\(\s*(u32|s32|int|long|unsigned int|unsigned long|uintptr_t|size_t)\s*\)"
    r"\s*(&?)\s*([A-Za-z_]\w*)\s*(?![\w.\[]|->)"
)
BARE_OFFSET = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)\s*([-+])\s*(0[xX][0-9a-fA-F]+)\b")
DECL = re.compile(r"\b[A-Za-z_]\w*\s*\*+\s*(?:const\s+)?([A-Za-z_]\w*)\s*(?=[,;)=\[])")
SIZEOF = re.compile(r"\bsizeof\s*$")

# Ordered most to least common; the warm ones move a pointer, the cool ones retype it.
CATEGORIES = [
    ("struct-ptr-cast", "retype to a struct", False),
    ("prim-ptr-cast", "retype to u8*/void*/f32*…", False),
    ("deref-cast", "*(T*)expr", False),
    ("cast+offset", "(T*)p + 0xNN", True),
    ("ptr-to-int", "(u32)p", False),
    ("cast+index", "((T*)p)[n]", True),
    ("raw-offset", "p + 0xNN, p already typed", True),
    ("abs-address", "(T*)0xNNNNNNNN", True),
]


class Site(NamedTuple):
    category: str
    file: str
    line: int
    type: str
    detail: str
    source: str


def blank_noise(text: str) -> str:
    """Replace comments and literals with spaces, keeping every offset intact."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            while i < n and text[i] != "\n":
                out[i] = " "
                i += 1
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            out[i] = out[i + 1] = " "
            i += 2
            while i < n and not (text[i] == "*" and i + 1 < n and text[i + 1] == "/"):
                if text[i] != "\n":
                    out[i] = " "
                i += 1
            if i < n:
                out[i] = out[i + 1] = " "
                i += 2
        elif c in "\"'":
            quote = c
            out[i] = " "
            i += 1
            while i < n and text[i] != quote:
                if text[i] == "\\":
                    out[i] = " "
                    i += 1
                    if i < n and text[i] != "\n":
                        out[i] = " "
                    i += 1
                    continue
                if text[i] != "\n":
                    out[i] = " "
                i += 1
            if i < n:
                out[i] = " "
                i += 1
        else:
            i += 1
    return "".join(out)


def pointer_names(text: str):
    """Map a position to the identifiers declared as pointers visible from it.

    Declarations are collected per top-level brace body (a function, plus the
    signature that precedes it) so that an `arg0` that is a pointer in one
    function is not assumed to be one in the next.
    """
    spans, depth, start = [], 0, None
    for i, ch in enumerate(text):
        if ch == "{":
            if depth == 0:
                start = i
            depth += 1
        elif ch == "}":
            depth = max(depth - 1, 0)
            if depth == 0 and start is not None:
                spans.append((start, i))
                start = None

    file_scope: set[str] = set()
    bodies: list[tuple[int, int, set[str]]] = []
    prev = 0
    for a, b in spans:
        head_start = max(prev, text.rfind(";", prev, a) + 1, text.rfind("}", prev, a) + 1)
        names = {m[1] for m in DECL.finditer(text[head_start:a])}
        names |= {m[1] for m in DECL.finditer(text[a:b])}
        bodies.append((a, b, names))
        file_scope |= {m[1] for m in DECL.finditer(text[prev:a])}
        prev = b
    file_scope |= {m[1] for m in DECL.finditer(text[prev:])}

    starts = [b[0] for b in bodies]

    def visible(pos: int) -> set[str]:
        k = bisect.bisect_right(starts, pos) - 1
        if k >= 0 and bodies[k][0] <= pos <= bodies[k][1]:
            return bodies[k][2] | file_scope
        return file_scope

    return visible


def classify(ty: str) -> str:
    bare = re.sub(r"\b(const|volatile|struct|union)\b", "", ty).strip()
    head = bare.split()[0] if bare.split() else bare
    return "prim-ptr-cast" if head in PRIMITIVES else "struct-ptr-cast"


def scan_file(path: Path, rel: str) -> Iterator[Site]:
    raw = path.read_text(encoding="utf-8", errors="replace")
    text = blank_noise(raw)
    lines = raw.split("\n")

    offsets, acc = [], 0
    for line in text.split("\n"):
        offsets.append(acc)
        acc += len(line) + 1

    claimed: dict[int, int] = {}
    found: list[Site] = []

    def emit(category: str, start: int, ty: str, detail: str, rank: int) -> None:
        if claimed.get(start, -1) >= rank:
            return
        claimed[start] = rank
        line = bisect.bisect_right(offsets, start)
        source = lines[line - 1].strip() if line - 1 < len(lines) else ""
        found.append(Site(
            category, rel, line, re.sub(r"\s+", " ", ty).strip(),
            detail, source[:150]))

    # An outer form claims its position and swallows the plain cast nested in it.
    offset_spans, wrapper_spans = [], []
    for m in OFFSET.finditer(text):
        offset_spans.append((m.start(), m.end()))
        emit("cast+offset", m.start(), m[1] + m[2], f"{m[3]} {m[4]}", 5)
    for m in INDEX.finditer(text):
        wrapper_spans.append((m.start(), m.end()))
        emit("cast+index", m.start(), m[1] + m[2], "", 4)
    for m in DEREF.finditer(text):
        wrapper_spans.append((m.start(), m.end()))
        emit("deref-cast", m.start(), m[1] + m[2], "", 3)
    for m in ABSOLUTE.finditer(text):
        wrapper_spans.append((m.start(), m.end()))
        emit("abs-address", m.start(), m[1], m[2], 6)
    for m in CAST.finditer(text):
        if SIZEOF.search(text[max(0, m.start() - 10):m.start()]):
            continue
        if any(a <= m.start() < b for a, b in wrapper_spans):
            continue
        emit(classify(m[1]), m.start(), m[1] + m[2], "", 1)

    # Both of these need to know which identifiers are pointers, so they are
    # heuristic where the syntactic categories above are exact.
    visible = pointer_names(text)
    for m in TO_INT.finditer(text):
        if m[2] == "&" or m[3] in visible(m.start()):
            emit("ptr-to-int", m.start(), m[1], m[2] + m[3], 2)
    for m in BARE_OFFSET.finditer(text):
        if any(a <= m.start() and m.end() <= b for a, b in offset_spans):
            continue
        if m[1] in visible(m.start()):
            emit("raw-offset", m.start(), "", f"{m[2]} {m[3]}", 0)

    seen = set()
    for site in found:
        key = (site.line, site.category, site.type, site.detail)
        if key not in seen:
            seen.add(key)
            yield site


def scan_tree(src: Path) -> list[Site]:
    sites: list[Site] = []
    for path in sorted(src.rglob("*")):
        if path.suffix in (".c", ".h") and path.is_file():
            sites.extend(scan_file(path, path.relative_to(ROOT).as_posix()))
    sites.sort(key=lambda s: (s.file, s.line))
    return sites


def directory_of(rel: str) -> str:
    parts = rel.split("/")
    return "/".join(parts[:3] if len(parts) >= 3 else parts[:2])


def write_tsv(sites: list[Site], out) -> None:
    out.write("category\tfile\tline\ttype\tdetail\tsource\n")
    for s in sites:
        out.write(f"{s.category}\t{s.file}\t{s.line}\t{s.type}\t{s.detail}\t{s.source}\n")


def write_html(sites: list[Site], path: Path, revision: str, generated: str) -> None:
    payload = json.dumps([list(s) for s in sites], separators=(",", ":"))
    meta = json.dumps({
        "revision": revision,
        "generated": generated,
        "files": len({s.file for s in sites}),
    }, separators=(",", ":"))
    html = TEMPLATE.read_text(encoding="utf-8")
    html = html.replace("__PAYLOAD__", payload.replace("</", "<\\/"))
    html = html.replace("__META__", meta.replace("</", "<\\/"))
    path.write_text(html, encoding="utf-8")


def summarize(sites: list[Site]) -> None:
    by_category = Counter(s.category for s in sites)
    warm = {name for name, _, is_warm in CATEGORIES if is_warm}
    moving = sum(v for k, v in by_category.items() if k in warm)
    print(
        f"{len(sites)} sites in {len({s.file for s in sites})} files "
        f"({moving} move a pointer)\n")
    for name, shape, _ in CATEGORIES:
        if by_category[name]:
            print(f"  {by_category[name]:5d}  {name:<17} {shape}")
    print("\n  top directories")
    for d, n in Counter(directory_of(s.file) for s in sites).most_common(8):
        print(f"  {n:5d}  {d}")
    print("\n  top files")
    for f, n in Counter(s.file for s in sites).most_common(8):
        print(f"  {n:5d}  {f}")


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", type=Path, default=ROOT / "src",
                    help="tree to scan (default: src)")
    ap.add_argument("--out", type=Path,
                    help="directory to write index.html and ptr_casts.tsv into")
    ap.add_argument("--tsv", type=Path,
                    help="write the TSV here instead ('-' for stdout)")
    ap.add_argument("--revision", default="working tree",
                    help="revision label shown on the page")
    ap.add_argument("--generated", default="",
                    help="build date shown on the page")
    args = ap.parse_args()

    sites = scan_tree(args.src)

    if args.tsv:
        if str(args.tsv) == "-":
            write_tsv(sites, sys.stdout)
        else:
            with args.tsv.open("w", encoding="utf-8") as fh:
                write_tsv(sites, fh)
    if args.out:
        args.out.mkdir(parents=True, exist_ok=True)
        write_html(sites, args.out / "index.html", args.revision, args.generated)
        with (args.out / "ptr_casts.tsv").open("w", encoding="utf-8") as fh:
            write_tsv(sites, fh)
        print(
            f"wrote {args.out}/index.html and {args.out}/ptr_casts.tsv "
            f"({len(sites)} sites)")
    if not args.tsv and not args.out:
        summarize(sites)
    return 0


if __name__ == "__main__":
    sys.exit(main())
