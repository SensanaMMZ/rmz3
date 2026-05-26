# rmz3 — Decompilation Status & Roadmap

## State of the decompilation

The project builds a byte-matching ROM (SHA1 `ff7a801776dc76e6d8c7ef73a6660ae732934a3f`) using agbcc — the makefile's `compare` target gates correctness. A lot has already been done: 499 `.c` files in `src/`, 268 in `include/`, all assets extracted, build script wired through Deno + a custom preproc.

What's still in raw ARM is split across three places:

1. **`NAKED` stubs inside existing C files** — 495 occurrences in 198 files. The C wrapper exists with the right signature, but the body is `asm(".syntax unified\n...")`. Example: `src/enemy/batring.c:43` (`Batring_Init`).
2. **`INCASM("asm/.../foo.inc")` blocks** — 266 lines, each pasting a whole standalone function from `asm/{boss,enemy,cyberelf,minigame,player,projectile,solid,stage_gfx,vfx,weapon}/`. That's ~264 `.inc` files across those subsystem dirs.
3. **Unwired asm** — `asm/wip` (135 files), `asm/todo` (15), `asm/unused` (23). These aren't even called from any C file yet; they're sitting outside the linked code path.

Remaining files per subsystem (the long tail to grind through):

| Subsystem  | Files |
| ---------- | ----- |
| enemy      | 70    |
| vfx        | 48    |
| solid      | 39    |
| projectile | 37    |
| boss       | 23    |
| weapon     | 13    |
| stage_gfx  | 12    |
| cyberelf   | 11    |
| minigame   | 7     |
| player     | 4     |

## What it would take to continue

**Toolchain** (per `INSTALL.md`): devkitARM, build agbcc from source, Deno. Then `make` should produce a SHA1-matching ROM. The "modern" gcc build is documented as broken (hardcoded addresses), so you're stuck on agbcc for now — fixing the modern build is its own substantial project, but unlocks better static analysis and permuter-style tooling.

### Per-function loop (matching decomp)

1. Pick an asm chunk (start with `asm/unused/*` — failures don't affect gameplay, or a `NAKED` stub in a file whose neighbors are already done so types/macros are at hand).
2. Read the asm, find its symbol in the linker map (`build/rmz3/rmz3.map`), look at callers/callees for type clues.
3. Rewrite as C using the structs already in `include/`.
4. `make && make compare` — iterate the C until agbcc emits byte-identical thumb. This is the slow part; agbcc has quirks that often require unusual C (specific operator ordering, temporary variables, `register` hints, etc.). The pret/decomp community has `decomp-permuter` for randomized C source mutation against an objective function — worth setting up.
5. Once it matches, replace `INCASM(...)` with the C, or replace the `NAKED { asm(...) }` body, and delete the `.inc`.

### Practical accelerators

- A working `m2c`-style ARMv4t-to-C transpiler (none is as mature as the MIPS one; `mwccgap`/`asm-differ` from the pret ecosystem is what people use).
- `asm-differ` for side-by-side diff of your candidate vs original on each iteration.
- mGBA with GDB stub for runtime checks before the SHA1 matches.

### Suggested order

Start in `asm/unused/` (low risk, builds intuition for the codebase's conventions), then `vfx` and `solid` (mechanically simpler than bosses), then chew through `enemy`. Save bosses and `asm/wip/AgbMain.inc` for last — they're the largest individual functions and exercise the most subsystems.

---

## Fixing the modern build

The modern build (`make modern` → `arm-none-eabi-gcc` + `ld_script-modern.ld`) is currently broken because the ROM contains hardcoded VMAs that only line up when agbcc + the strict layout in `ld_script.ld` places every TU at its original address. Modern gcc emits differently-sized code, and `ld_script-modern.ld` collects sections with `*(.text*)` / `*(.rodata*)` wildcards instead of the explicit per-object ordering in `linker/text.txt` and `linker/rodata.txt` — so things slide. There are three concrete problems, in increasing order of pain.

### Problem 1 — Absolute pointers to named data (~53 unique addresses)

Raw asm in `asm/boss/*.inc`, `asm/mmbn4.inc`, etc. embeds literal pointers into `.rodata`:

```
ldr r5, _0803F180 @ =0x080FED27
...
_0803F180: .4byte 0x080FED27        @ → BlazinEXModes
```

Almost every such literal in the `0x080FECxx`–`0x080FF1xx` range corresponds to a named C symbol already declared in `src/data/data_080fea74.c` (e.g. `BlazinModes`, `BlazinEXModes`, `VolteelModes`, `CubitEXModes`, `Coord_ARRAY_080fedb8`, ...). The matrix is roughly:

- ~40 literals → named data symbols (mostly `data_080fea74.c`).
- ~15 literals → boot/IRQ entry-point offsets inside `crt0.s` / `mmbn4.c` (`MaybeIntrMain`, `IntrMain`, `0x08001510`, ...). These are local labels in the same TU and *already work* via local references — the bare numeric literal is a documentation echo, not a relocation.
- ~15 literals → intra-function jump-table base pointers (see Problem 2).

**Fix:** for each `.4byte 0xNNNNNNNN` that points to a named extern, replace with `.4byte SymbolName` and add an `.extern SymbolName` at the top of the `.inc`. Pure mechanical sweep, scriptable:

```sh
grep -rEn "\.4byte\s+0x080[0-9a-fA-F]{4,5}" asm src
```

Then for each unique address, find the symbol whose `// 0x080XXXXX` comment in `data_080fea74.c` matches and substitute. Build with `make compare` after each batch to confirm the agbcc build still matches the original ROM — these edits must be neutral for the legacy build.

### Problem 2 — Embedded jump tables of absolute branch targets (~15 sites)

Switch statements compile to a pattern like `asm/boss/baby_elf.inc:1597`:

```
ldr r1, _080467E4 @ =0x080467E8       @ base of jump table
adds r0, r0, r1
ldr r0, [r0]
mov pc, r0
_080467E4: .4byte 0x080467E8
_080467E8:
    .byte 0x00, 0x68, 0x04, 0x08      @ 0x08046800
    .byte 0x10, 0x68, 0x04, 0x08      @ 0x08046810
    ...
```

The `.byte` arrays are little-endian absolute Thumb branch targets. As soon as the function moves, every entry is wrong. The base-address `.4byte 0x080467E8` *and* every table entry must be re-emitted as label references.

**Fix:** rewrite each table as `.4byte _label, _label, ...` and replace the `.byte` runs with the original local labels. Each site is ~5–10 minutes of manual work — find the table, find the `_080468xx:` labels in the same function, swap. Look for the `mov pc, r0` / `bx r0` after an indexed load to locate them. ~15 of these total.

Alternative: decompile the function to C with a real `switch` — modern gcc emits its own (relocatable) jump table. Faster overall if the function was on the decomp roadmap anyway.

### Problem 3 — Linker doesn't preserve order (the real blocker)

`ld_script-modern.ld` does:

```
.text : { src/rom_header.o; src/crt0.o; src/sprite2.o; src/mmbn4.o; src/main.o; *(.text*); }
.rodata : { *(.rodata*); INCLUDE "linker/rodata_sprite.txt"; }
```

vs `ld_script.ld` which `INCLUDE`s `linker/text.txt` (492 lines) and `linker/rodata.txt` (618 lines) — explicit per-object ordering. Because Problems 1 and 2 leave absolute addresses everywhere (and because some asm constant-pool layouts assume the function lives at a specific 4-byte alignment relative to its pool), modern needs the same explicit layout.

**Fix:** make `ld_script-modern.ld` `INCLUDE` the same `linker/text.txt` and `linker/rodata.txt` fragments the legacy script does. Then make sure `linker/iwram.txt` / `linker/ewram.txt` (currently included) also produce identical placement under gcc. Modern gcc may emit extra `.text.startup`, `.text.unlikely`, `.text.hot` sub-sections that the explicit list doesn't cover — add `*(.text.*)` as a catch-all *after* the explicit list, not instead of it. Same for `.rodata.str1.4`, `.rodata.cst*`.

### Order of operations

1. **Bring the modern linker script in line with the legacy one** (Problem 3) — `INCLUDE` the same fragments. This alone won't make it match, but it stops the reordering from masking other issues.
2. **Sweep absolute → symbolic data pointers** (Problem 1). Verify after each batch with `make compare` (legacy build must still match).
3. **Rewrite jump tables** (Problem 2). Same verification.
4. Try `make modern`. Expect a flood of remaining mismatches from:
   - agbcc's `-fhex-asm` and `-mthumb-interwork` quirks vs modern gcc codegen,
   - hand-tuned inline asm that assumes specific register allocation,
   - `m4a.o` / `agb_sram.o`'s `-mno-thumb-interwork` flag dance — keep these flag overrides in the modern path too,
   - `src/libs/m4a.o`'s use of `tools/agbcc/bin/old_agbcc` — modern can't replicate; either keep building this one TU with old_agbcc or accept that the modern ROM won't be byte-identical.
5. Accept that the modern build's product will not pass `compare` even when correct. Add a `compare-modern` target that's either skipped or compares against a separately-recorded `rmz3-modern.sha1`.

### Realistic scope

Problems 1 and 3 are an afternoon each. Problem 2 is a couple of days. Getting the modern build to *boot and run* (not byte-match) is achievable in a week or two. Getting it to byte-match the original is not a goal worth pursuing — by design, modern gcc generates different code; the legacy build remains the source of truth for `compare`, and the modern build's value is purely as a development aid (better diagnostics, faster compile, working sanitizers and permuter setups).
