# Modded DOL builds

`configure.py --mod` builds a modified `main.dol` from the decomp: your C code
is compiled with the game's compiler against the game's headers and linked
into the DOL. The image is fully shiftable — code and data may grow, and the
linker recomputes the layout (the stack, SDA bases and OS arena follow
automatically; only `__ArenaHi` is fixed, so the arena shrinks by your mod's
footprint).

```sh
./configure.py --mod mods/hello   # repeatable for multiple mods
ninja -f build.mod.ninja
# -> build-mod/GALE01/main.dol
```

Modded builds are fully isolated from the matching workflow: artifacts live
under `build-mod/`, the manifest is `build.mod.ninja`, and the root
`build.ninja`, `objdiff.json` and `compile_commands.json` are untouched. A
clangd database that includes mod TUs is written to
`build-mod/compile_commands.json` (`clangd --compile-commands-dir=build-mod`).
`dtk dol apply`, progress and the sha1 check are disabled in mod manifests.

Game TUs keep `-DMUST_MATCH`, so retail codegen is preserved and a build with
an empty mod is byte-identical to the original DOL — only your changes alter
behavior.

## Mod layout

```
mods/<name>/
  mod.toml        # optional
  src/**/*.c      # auto-discovered
```

```toml
[mod]
name = "hello"
defines = ["FOO", "BAR=2"]  # extra -D flags
includes = ["include"]      # extra include dirs, relative to the mod
```

Mod TUs are compiled like game code (MWCC 1.2.5n, C89) with the melee include
paths plus the mod's `src/`, any `includes` entries, and `-DMOD`. Their
sections are appended to the end of each output section, and everything
downstream shifts. [mods/hello](../mods/hello) is a working example.

## Hooks

Hooks need no registration — they are detected from what your compiled
objects define. Three spellings cover everything:

```c
#include <baselib/random.h>
#include <melee/gm/gm_1A3F.h>

/// Replace: define a game function's name, done.
f32 HSD_Randf(void) { return 0.5F; }

/// Wrap: hook_<name> takes over <name>; inside the wrapper's body, calls to
/// <name> reach the original (typed by the game header — no declarations).
void hook_gm_801A4510(void)
{
    OSReport("before\n"); // args are yours to inspect or modify
    gm_801A4510();        // the original (optional to call)
    OSReport("after\n");  // so is the return value
}

/// Checked wrap: same-name definition (the compiler verifies your signature
/// against the game header) calling the renamed original. orig_<name> is an
/// ordinary symbol — any TU may declare and call it.
extern void orig_gm_801A4510(void);
void gm_801A4510(void) { orig_gm_801A4510(); }
```

Rules of the road:

- The name is the hook: a global function definition matching a game symbol
  interposes it, and `hook_<name>` wraps `<name>`. Each detected hook is
  echoed at configure time, e.g. `hook: runGameMode (local,
  melee/gm/gm_1A3F.c) <- hello`. `static` mod functions never hook anything.
- Both global and local (`static`) game functions can be hooked. For a local
  target, write its prototype yourself (no game header declares it) — without
  one the call compiles as an implicit `int()` declaration, which silently
  miscompiles float-returning functions (the caller int-converts garbage from
  `r3` while the result sits in `f1`).
- A `hook_` wrapper's own signature is a fresh name the compiler cannot
  check, so copy the prototype exactly; use the same-name form when you want
  that checked.
- In the same-name form, never try to reach the original by calling your
  replacement recursively: the compiler sees ordinary self-recursion and is
  free to collapse it into a loop (MWCC does, at `-O4,p`) long before the
  build could redirect it. `orig_<name>` — or the `hook_` form, whose call
  target is a distinct external symbol — are the supported spellings.
- Outside a `hook_` wrapper's body (other functions, other TUs, function
  pointers), the hooked name refers to your hook, not the original.

### How it works

The build compiles your TUs, scans the objects, and reconfigures itself
within a single ninja run (`build-mod/GALE01/hooks.json` closes the loop the
same way `config.json` bootstraps the build). Each hooked symbol is resolved
to its defining object via `config/GALE01/{symbols,splits}.txt`, and
`tools/elf_hook.py` rewrites that object into `build-mod/GALE01/hooked/`
before linking. Globals get their definition renamed to `orig_<name>`; locals
get renamed and globalized in place, with every entry reference (relocations
with addend 0) retargeted to an undefined `<name>` the linker resolves to
your definition — so for locals, even intra-unit callers are intercepted.
References with a nonzero addend (jump tables, labels into the body) and
extab entries keep pointing at the original code. This works identically for
decompiled units and for units still linked from dtk-extracted objects.

mwld tracks liveness per symbol, so a renamed original would otherwise be
deadstripped along with everything only it references; the tool prevents that
by setting the MW `.comment` "active" flag on every symbol it renames (the
same marking dtk applies to extracted symbols).

Configure fails with a clear error on invalid hooks: names colliding with
data symbols or `scope:weak` (inline) functions, two mods hooking the same
symbol, ambiguous symbol names, or `orig_<name>` references when nothing
hooks `<name>`. A `hook_`-prefixed function matching no game symbol is only
warned about — check the spelling.

### Limitations

- For global hooks, callers inside the function's own TU (and recursion)
  still reach the original directly, like GNU `--wrap`; local hooks retarget
  those too. Callsites where MWCC inlined the function are not intercepted
  under either mechanism.
- Varargs functions can be replaced but not wrapped (C89 cannot forward
  `...`).
- mwld deadstrips symbols nothing references: mod data (or a helper function)
  that is never referenced from live code silently disappears from the image.
  Reference what must survive; hooked originals are exempt.

## Reconfiguration

Editing or adding mod sources reconfigures automatically on the next ninja
run (hook changes included). After *deleting* a mod source, rerun
`./configure.py --mod ...` once — ninja will name the missing file otherwise.
Mod paths must not contain spaces.

## Verifying

`powerpc-eabi-nm` (under `build/binutils/`) on `build-mod/GALE01/main.elf`
shows each hook owning its symbol at a mod address, with `orig_<name>` at the
retail address; the rewritten inputs are in `build-mod/GALE01/hooked/`. If a
modded DOL ever stalls, check for silently unresolved references — mwld links
with `-warn off`, and an unapplied branch becomes a branch-to-self:

```sh
build/binutils/powerpc-eabi-objdump -d build-mod/GALE01/main.elf | grep -c "48 00 00 01"
```

should print 0.
