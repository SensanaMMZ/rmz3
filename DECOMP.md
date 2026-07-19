# rmz3 decompilation — environment, status, and how to continue

This document is the working reference for everyone (humans + agents) picking up the decomp effort. It covers:

- the local toolchain and what each piece does
- the build patches required for Windows / devkitPro msys2
- what's matched, what's still in asm, and what's been tried
- the permuter scaffolding under `tools/permuter-setup/` and how to drive it
- agbcc gotchas seen so far and the tricks that worked around them

The build gate is `make compare` — it hashes `rmz3.gba` against `ff7a801776dc76e6d8c7ef73a6660ae732934a3f`. Every commit on this branch keeps that match. Anything that breaks it gets reverted before merging.

---

## Toolchain

| Tool | Path | Purpose |
| ---- | ---- | ------- |
| devkitARM (gcc 13.2) | `C:\devkitPro\devkitARM\bin\arm-none-eabi-*` | The ARM `as`, `ld`, `objcopy`, `objdump` |
| devkitPro msys2 bash | `C:\devkitPro\msys2\usr\bin\bash.exe` | Build shell; the makefile is bash/POSIX |
| host gcc 15.2 | `/usr/bin/gcc` (inside the msys) | Builds `tools/agbcc` from source and the host helpers (`gbagfx`, `mid2agb`, `preproc`, `scaninc`) |
| Deno 2.8 | `/usr/local/bin/deno.exe` (shim) | Runs `tools/dev/*.ts` asset/sprite generators |
| agbcc | `tools/agbcc/bin/{agbcc,old_agbcc}.exe` | The legacy GBA C compiler; what the project's match depends on |
| libpng 1.6.43 | `/usr/local/{lib,include}` | Required by `gbagfx` for PNG → 4bpp conversion |
| asm-differ | `tools/asm-differ/` | Side-by-side function diff during manual decomp |
| decomp-permuter | `tools/decomp-permuter/` | Randomized source mutation to brute-force matches |
| mGBA 0.10.5 | `C:\Program Files\mGBA\mGBA.exe` | Runtime testing of built ROMs |

The build always runs inside the devkitPro msys2 shell — `$DEVKITARM` is set there but not in PowerShell / Git Bash, and pacman-installed dependencies (zlib, libpng, gcc) live under the msys.

```powershell
# Typical invocation:
& 'C:\devkitPro\msys2\usr\bin\bash.exe' -lc 'cd /c/.../rmz3 && export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig && make -j8 && sha1sum -c rmz3.sha1'
```

---

## Build patches applied for Windows / devkitPro msys2

These are merged in `72bb521 — Fix legacy build under Windows / devkitPro msys2`.

1. **`makefile`: `CPP := cpp`.** `make`'s default `CPP = $(CC) -E` becomes `cc -E`, which on this gcc 15 silently emits nothing for `.s` inputs (the driver dispatches them to the assembler-only path). Standalone `cpp` doesn't. Without this, every asm-script object linked in is empty — link fails with undefined refs to `Script_MissionFail`, `gStageScriptList`, etc.
2. **`makefile`: add `-std=gnu89` to `CPPFLAGS`.** gcc 15's default mode is `gnu23`, which sets `__STDC_VERSION__=202311L`. That triggers the C23 varargs typedef branch in `include/gba/m4a_internal.h:172` (`typedef void (*MPlayFunc)(...);`) which agbcc can't parse — "ANSI C requires a named argument before `...'".
3. **`makefile`: `echo "\n..."` → `printf '\n...'`.** Bash's builtin `echo` doesn't interpret `\n` without `-e`. MSYS bash inherits that. The original `@echo ".text\n\t.align\t2, 0\n"` was appending the literal text "`\n`" to the generated `.s`, breaking the assembler. `printf` is POSIX-portable here.
4. **`tools/dev/{animation,graphic_header,stage}.ts`: `import { ... } from '@std/path/posix'`.** Deno's `@std/path` `join()` returns platform-native separators — `\` on Windows. The generated `sprites/static/anim.s` had `.include "sprites\static\foo\sequence.inc"` lines, which GNU as reads as escape sequences (`\s` etc.), corrupting the paths.
5. **`.gitignore`: add `tools/asm-differ/`, `tools/decomp-permuter/`, `tools/*/*.exe`, `.claude/`.** Third-party tool clones and built host binaries.

---

## What's matched

| Symbol | File | Address | Status | Commit |
| ------ | ---- | ------- | ------ | ------ |
| `unused_080046c8` | `src/sprite.c:38` | 0x080046c8 | ✓ matched (manual, first try) | `00c256f` |
| `unused_08006ea8` | `src/overworld_layer.c:1438` | 0x08006ea8 | ✓ matched (manual + `u8` arg insight) | `90f1b87` |
| `getMetatileID` | `src/terrain.c:241` | 0x08008e08 | ✓ matched (permuter, `int new_var = 2` trick) | `617dc08` |
| `unused_080b4960` | `src/vfx/unk_07.c:281` | 0x080b4960 | ✓ matched (permuter + manual, `register asm` + barrier) | `4bdc1e9` |
| `Solid45_Die` | `src/solid/giant_elevator_pier.c:236` | 0x080de7b4 | ✓ matched (manual, standard die-routine) | `c4bc77a` |
| `ShotcounterBullet_Die` | `src/projectile/shotcounter_bullet.c:154` | 0x0809ce70 | ✓ matched (manual, `EXIT_BODY` macro + .inc split) | `2653618` |
| `nop_080a5048` | `src/projectile/unk_20.c:5` | 0x080a5048 | ✓ matched (empty bx-lr, .inc split) | `3bb4443` |
| `nop_0809ceac` | `src/projectile/shotcounter_bullet.c:160` | 0x0809ceac | ✓ matched (empty bx-lr) | `4747ffb` |
| `FUN_0809cf98` | `src/projectile/shotcounter_bullet.c:164` | 0x0809cf98 | ✓ matched (empty bx-lr at end of inc) | `f7ca53a` |
| `FUN_08084700` | `src/enemy/omega_gold_hand.c:37` | 0x08084700 | ✓ matched (empty bx-lr at end) | `0ab2c56` |
| `nop_0805474c` | `src/boss/locomo_if.c:5` | 0x0805474c | ✓ matched (empty bx-lr at start) | `2e5d070` |
| `Solid25_Die` | `src/solid/unk_25.c:41` | 0x080d8b40 | ✓ matched (empty bx-lr at end) | `97a0af1` |

**Tally**: `asm/unused/` 23 → 19, `asm/solid/` 39 → 37, `asm/projectile/` 37 → 34, `asm/enemy/` 70 → 69, `asm/boss/` 23 → 22. 12 functions matched total.

Note: permuter reports an integer "score" derived from instruction-level diffing. **Score 0 is the canonical match marker, but small non-zero scores (≤ ~10) can also be byte-perfect matches** — the score includes noise from symbol-name lookups and instruction counts. Always test small-score candidates against `make compare`; that's what landed `getMetatileID` (permuter reported 5 — turned out to be byte-identical).

---

## What's been tried but doesn't yet match

These all compile, the math is correct, but agbcc's register allocation or constant-materialization picks differ from the original. They're the immediate permuter targets — set up under `tools/permuter-setup/<fn>/`.

| Symbol | Why it didn't match manually |
| ------ | ---------------------------- |
| `unused_080069e0` | Nested fill loop. Inner-loop pointer ends up in `r1` vs original's `r0`. |
| `unused_08006e3c` | Metatile lookup with `__udivsi3`/`__umodsi3` calls. Callee-saved register assignment of `(p, unk_x, unk_y)` differs. |
| `getMetatileID` | My emit is 6 bytes *shorter* than the original — agbcc folds `gOverworld.terrain.tilemap` directly to its absolute address while the original goes via `gOverworld + 0x7e0`. |
| `unused_080b4960` | Has a `bl FUN_08009f6c` call whose result + a subsequent `abs()` are computed but discarded; ends with hardcoded `return 0xF00`. Dead-code preservation that agbcc -O2 normally kills — source must use a side-effecting helper. |
| `unused_080e14d4` | Raw-byte function: linked-list search via `->next` (offset 4) for `->field_9 == id`. Speculative candidate. |

Two known-hard ones in `asm/wip/` were also touched and left as `NON_MATCH`:

| Symbol | Why |
| ------ | --- |
| `GetSplitHeavenSpeed` | agbcc CSEs the two `z->slow` loads; original keeps them separate (`ldrb` twice). |
| `InitSound` | agbcc folds `0x150` to `mov #0xa8; lsl #1`; original uses `ldr =0x150` + mask. |

---

## Lessons about agbcc (so far)

These came out of the matching attempts. Each is a rule of thumb, not a guarantee — but worth trying before reaching for permuter.

1. **`u8` parameter beats `u32` + `(u8)` cast.** When the function reads a u8 arg, declare it `u8` in the signature instead of `u32` with a `(u8)` mask inside. agbcc emits the sign-extension as part of the prologue, which often matches the original's instruction order. This is what made `unused_08006ea8` match.
2. **Parenthesize to control accumulation.** `((u8)a * 150 + b) + c * 15` (group `t = a*150 + b` first, then `r = t + c*15`) emits two ADDs into the same accumulator, vs `c*15 + (u8)a*150 + b` which spreads them. Both are equivalent C but produce different register lifetimes.
3. **Source order is scheduling order — usually.** agbcc schedules independent ops in the order they appear in source. To get a load to happen *before* another arithmetic op, name it as a separate statement before that op.
4. **`s16` for loop counters that the original sign-extends.** A counter with `(s16)` semantics ends up as `lsls #16; asrs #16` pairs in the asm. Declaring `s16` instead of `s32` introduces those.
5. **agbcc prefers the shorter encoding.** For constants representable as `imm8 << n`, agbcc emits `mov #imm8; lsl #n` (4 bytes) instead of `ldr =literal` (4 bytes + 4 bytes pool). To force a literal-pool load you need a source structure that hides the constant from compile-time eval (a `const` variable, a sufficiently complex expression, or sometimes a temp).
6. **Some optimizations can't be coaxed.** Strength reduction across loop iterations (the `r2 += 0xFFFF0000` pattern in `unused_080e9d94`), specific high-register spills (`x → ip`), and CSE-suppression (`GetSplitHeavenSpeed`) all resisted manual rewriting. Those are permuter's job.

---

## Permuter scaffolding — `tools/permuter-setup/`

```
tools/permuter-setup/
├─ compile.sh.template    # Per-function compile.sh, generated with REPO sed-substituted in
├─ setup_fn.sh            # Bootstrap a function dir from src + .inc + candidate.c
├─ sanity_all.sh          # Quick "do all base.c files compile?" check
├─ run_all.sh             # Sequentially run permuter on every set-up dir
├─ candidates/            # Hand-written starting C bodies (one .c per function)
└─ <fn>/                  # One directory per function being permuted
   ├─ compile.sh          # Wraps cpp+agbcc+as for one .c
   ├─ base.c              # Preprocessed source + the candidate body
   ├─ target.o            # Original .inc assembled into a .o with symbol <fn>
   └─ settings.toml       # func_name + compiler_type=gcc + objdump_command
```

### Adding a new function

1. **Write a candidate** as `tools/permuter-setup/candidates/<fn>.c`. It must be valid C, take whatever args the wrapper specifies, and reference no extern that isn't already declared in the containing source file.
2. **Bootstrap the directory:**
   ```bash
   tools/permuter-setup/setup_fn.sh <fn> <src_file> <inc_file> tools/permuter-setup/candidates/<fn>.c
   ```
3. **Sanity-check it compiles:**
   ```bash
   tools/permuter-setup/sanity_all.sh
   ```
4. **Run permuter** (the script is the easiest path):
   ```bash
   tools/permuter-setup/run_all.sh 300   # 5 min per fn
   ```
   Or directly for one function with a longer budget:
   ```bash
   py tools/decomp-permuter/permuter.py tools/permuter-setup/<fn> -j2 --best-only --stop-on-zero
   ```

### What setup_fn.sh actually does

1. Preprocesses the containing source file (`cpp -P` with project's CPPFLAGS minus `__attribute__` stripping). This gives us all the typedefs / structs / extern declarations needed for the candidate to compile.
2. Drops two classes of lines from the preprocessed output:
   - `"asm/...inc"` lines — NAKED stubs from other functions in the same file. Their `.include` directives reference paths that don't resolve from the assembler's tmp dir.
   - `extern char assertion[...]` — `static_assert` expansions for packed struct sizes. They'd fail in the permuter sandbox because we strip `__attribute__`.
3. Appends the candidate body.
4. Assembles `<inc_file>` with a thumb-func wrapper into `target.o` (the canonical bytes permuter is trying to match).
5. Writes a `compile.sh` (template with `@@REPO@@` substituted) and a `settings.toml` pinning `objdump_command` to the devkitARM toolchain.

### Required patches to decomp-permuter for Windows

These are local edits to `tools/decomp-permuter/src/`:

- **`main.py:328`** — wrapped the `os.stat(compile_cmd).st_mode & 0o100` exec-bit check in `if os.name != "nt"`. Windows Python's `os.stat` doesn't expose POSIX exec bits, so the check rejected every script.
- **`compiler.py`** — added a `_compile_argv` helper that prepends `bash.exe` when `compile_cmd` is a `.sh` on Windows. `CreateProcess` doesn't honor shebangs.

Both patches are minimal and could be upstreamed.

### Why `__attribute__` is stripped in the per-function compile pass

`perm_pycparser`'s code generator emits `__attribute__((aligned(1)))` *before* the type (`__attribute__((aligned(1))) u8 unk_12f[2]`), while the project source has it *between* the type and declarator (`u8 __attribute__((aligned(1))) unk_12f[2]`). agbcc accepts the latter but not the former.

Stripping `__attribute__` makes packed structs land at the wrong size, which is **fine for functions that don't read packed fields** (pure pointer math, leaf computations) and **broken for functions that do** (anything touching `struct Zero` field offsets above 0x12f, for instance). When permuter results look obviously wrong, this is the first suspect.

A cleaner fix would be a small patch to `perm_pycparser/c_generator.py` to emit attributes in the post-type position. Filed for later.

---

## Continuing the work

In rough priority order:

1. **Harvest matches from the current 5 permuter runs.** When a 0-score candidate appears, it lands in `tools/permuter-setup/<fn>/output-*.c`. Drop the body into the project source, rebuild, verify SHA, commit, delete the `.inc`.
2. **Drain the rest of `asm/unused/`** (~19 files) using the same setup_fn.sh + permuter loop. Most are short and follow patterns similar to what's already matched.
3. **Move to `asm/wip/` and `asm/todo/`** — these are wired-up but unfinished. `GetSplitHeavenSpeed` and `InitSound` are good warm-up targets since the C is already drafted.
4. **The big subsystem grind** — `INCASM(...)` lines in `src/{enemy,vfx,solid,projectile,boss,...}` pull in ~264 standalone `.inc` files. These are the long tail. `nb.md` has the per-subsystem counts.

Permuter doesn't replace human judgment: it bridges the gap between "this is the right C" and "this is the right C *that agbcc emits the same way*". When permuter sits at score > 0 for hours, the candidate is wrong logically — not just allocated differently. Revisit the trace before throwing more compute at it.

---

## Iteration cycle log

### Round 1 — first permuter pass (5 candidates × 5 min)

- `getMetatileID` matched (score 5 — permuter noise, byte-identical). Committed `617dc08`.
- `unused_080069e0` reached score 70 — close, but candidate had broken structure (uninit pointer). Not a real match.
- `unused_08006e3c`, `unused_080b4960`, `unused_080e14d4` — high scores, far from match.

**Lesson:** test small-score candidates against `make compare` — permuter's score includes noise (symbol lookups, instruction counts), so non-zero scores ≤ ~10 sometimes are byte-perfect.

### Round 2 — second permuter pass (7 candidates × 10 min)

Added 5 new candidates (FadeBlack, GetSplitHeavenSpeed, onRod, ResetCharTiles, TurnDownBGM) and re-ran with longer budget.

| Function | Best | Notes |
| -------- | ---- | ----- |
| `unused_080069e0` | 70 | Tested — not a match; permuter added pointer-of-pointer aliasing that agbcc optimized away. |
| `unused_08006e3c` | 940 | Far. Candidate likely needs structural rework. |
| `unused_080b4960` | 275 | **Manually got the body matching** (`register asm("r4/r5/r1")` pinning + `asm volatile` barrier kept the abs() alive). Remaining diff: agbcc eagerly loads `-0x2000` from LP and conditionally overwrites — 2 bytes shorter than the original's if-else. Need a phrasing that defeats the load-hoist optimization. |
| `unused_080e14d4` | 1205 | Speculative candidate; raw-byte function, struct layout unclear. |
| `FadeBlack` | 2185 | High — body math is right but loop structure differs. |
| `GetSplitHeavenSpeed` | no improvement | Pycparser couldn't parse base after some mutation; permuter aborted. |
| `ResetCharTiles` | 1045 | Mutations went unproductive (silly `&p->tilelist[79]` repetition). |
| `onRod` | base score = 220 (no improvement) | Tested `u8*` cast approach — close structurally but layout/order differs. Bitfield struct restriction makes this stubborn. |

**Patterns observed this round:**

1. **agbcc's eager LP-load optimization** beats most C rephrasings. When one branch of an if-else needs a literal pool entry, agbcc loads it before the branch and conditionally overwrites in the cheaper branch. Source-level rephrasing (`if/else` vs ternary vs explicit blocks) does not change this — agbcc reaches the same form. Defeating it likely requires `volatile` on the loop variable or a memory store between the load and the if-else.

2. **`register asm("rN")` pinning works for forcing callee-save register saves.** Pinning live-across-call values into r4/r5/r6 makes agbcc include them in the function prologue's `push`. Combined with an `asm volatile("" : "+r"(d) : "r"(x))` barrier, otherwise-dead computations are preserved (this was the key to making `unused_080b4960` save `{r4, r5, r6, lr}` like the original).

3. **`int new_var = 2`** trick: factoring out a constant offset into a named variable defeats agbcc's index-folding and forces a specific instruction sequence. This is what landed `getMetatileID` at byte-identity even though permuter's reported score was 5.

4. **pycparser chokes on agbcc-specific shapes** (notably bitfields with `__attribute__((packed))` in non-canonical position). When permuter reports "no improvement over baseline" it sometimes means it couldn't even parse the function — check the log for "Syntax error in base.c".

### Manual workflow (proven on getMetatileID, unused_080046c8, unused_08006ea8)

For functions where you can read the asm and write reasonable C:
1. Write the candidate inline in the source file (replace the NAKED stub).
2. `make` → expect FAIL.
3. `arm-none-eabi-objdump.exe -d --start-address=0xNNN --stop-address=0xNNN+function-size rmz3.elf` to see emitted asm.
4. Diff against the original `.inc`. Categorize the diff:
   - **Wrong instruction order** → reorder C statements.
   - **Wrong register usage** → try `register asm("rN")` pins.
   - **Wrong constant materialization** → introduce/remove intermediate variables, change types (`u32` vs `u16` vs `s16`), inline or factor out subexpressions.
   - **Extra/missing instructions** → most often a CSE or DCE difference; try `asm volatile("" : "+r"(v))` barriers or `register asm()` pins.
5. Iterate. If stuck for ≥ 3 attempts, write a candidate file and hand off to permuter.

### Permuter workflow

1. Write candidate at `tools/permuter-setup/candidates/<fn>.c`.
2. `tools/permuter-setup/setup_fn.sh <fn> <src> <inc> tools/permuter-setup/candidates/<fn>.c`
3. `tools/permuter-setup/sanity_all.sh` to verify it compiles.
4. `tools/permuter-setup/run_some.sh 600 <fn>` (10 min budget; bump to 1800 if close).
5. When permuter reports a score, **always test it** — small scores (≤ ~10) might be byte-perfect; larger scores ≥ ~200 usually mean broken/wrong C.
6. If permuter plateaus and the candidate compiles to wrong bytes, update the candidate with what was learned and run again. Each `run_*` cycle iterates from the candidate, not from the previous best output.

### Round 3 — focused iteration cycle (after first 5 candidates)

This is where the workflow really paid off. unused_080b4960 went from "obviously won't match" (manually) to byte-perfect through a permuter+manual combo:

1. **Permuter round 1** (300s budget): best score 1295 → 280. The mutations were going haywire (broken C with missing returns).
2. **Manual diagnosis**: identified that the abs() needs preservation and `register asm` pinning forces specific register saves. Updated candidate.
3. **Permuter round 2** (900s budget, new candidate): score 280 → 10. Permuter found the missing piece — `r = -0x2000; dx = r;` via the r5-pinned register defeats agbcc's eager LP-load.
4. **Manual finish**: tested score-10 candidate, noticed prologue match but epilogue mismatch (`pop {r1}; bx r1` vs orig's `pop {r0}; bx r0`). Realized the function is **void**, not s32 — change return type + add `register s32 ret asm("r0")` pin → byte-perfect.

The cycle that works: **permuter explores the search space; humans recognize structural patterns and fix-them-up after.** Neither alone matched this function.

### Round 4 — Solid45_Die (first-try manual on a die-routine)

Trivial pattern: clear flags, set ENTITY_EXIT routine. Used the standard `SET_SOLID_ROUTINE(p, ENTITY_EXIT)` macro. The initial attempt used `ENTITY_DISAPPEAR` (= 3) — caught by `make compare` immediately; fixed to `ENTITY_EXIT` (= 4) and matched.

**Generalization**: many `*_Die` routines across `solid/`, `enemy/`, `vfx/`, `projectile/` follow this exact shape. Worth a sweep with the same template.

### Round 5 — ShotcounterBullet_Die + EXIT_BODY macro discovery

Found that the "die-routine" template for Projectiles uses `EXIT_BODY(p)` macro (defined in `include/entity/macros.h`), which expands to:
```c
((Object*)p->body).status = 0;
((Object*)p->body).prevStatus = 0;
((Object*)p->body).invincibleTime = 0;
((Object*)p->s).flags &= ~COLLIDABLE;
```

This matches a 12-byte zero clear at `p + 0x8c` (= `p->body.status` through the bitfield at offset 0x20 of Body) plus the `flags &= ~0x04` (COLLIDABLE = bit 2).

So a typical Projectile_Die is:
```c
void X_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}
```

**Key technique — splitting an .inc**: When the function to extract is at the *start* of a multi-function `.inc`, you can:
1. Delete the function's section from the `.inc`.
2. Add the C version BEFORE the `INCASM(...)` line in the containing `.c`.
3. Source order in the `.c` preserves the binary layout.

This won't work for functions in the MIDDLE of the `.inc` — those need either decompiling everything around them in one go, or splitting the `.inc` into pre/post pieces.

### Round 6 — bulk extraction of empty stubs (.inc start/end splits)

Found that many `.inc` files contain `nop_*` or `_Die` functions that are pure `bx lr` (empty body, void return). These are essentially placeholder routines in function tables.

**Pattern**: When such a stub is at the start OR end of the `.inc`, trivially extractable:
- **Start**: Edit `.inc` to remove the stub section. Add `static void name(struct X* p) {}` BEFORE the `INCASM` line in `.c`.
- **End**: Edit `.inc` to truncate the stub section. Add the C function AFTER the `INCASM` line.

5 matches landed in one batch using this template:
- `nop_080a5048` (projectile/unk_20, start), `nop_0809ceac` + `FUN_0809cf98` (shotcounter_bullet, start+end), `FUN_08084700` (enemy/omega_gold_hand, end), `nop_0805474c` (boss/locomo_if, start), `Solid25_Die` (solid/unk_25, end).

**Limit reached**: Searched all subsystem `.inc`s and exhausted the trivial cases. Remaining empty stubs are all in the MIDDLE of `.inc` files (preceded and followed by complex functions), which would require either decompiling everything surrounding them or generating pre/post `.inc` pairs.

### Setup script bug discovered + fixed

`setup_fn.sh` didn't handle `.inc` files that have their own prologue (`thumb_func_start X; X:`) — those are common in subsystem dirs (`asm/{boss,enemy,solid,vfx,projectile}/`) while `asm/unused/` and `asm/wip/` files have bare function bodies. The script now detects via `grep -q "thumb_func_start[[:space:]]*$FN"` and skips its own prologue if the .inc already has one. Without this fix, `target.s` had a duplicate symbol error.

### Patterns observed (cumulative)

- **`u8` param vs `u32` + `(u8)` cast**: signature type affects where the sign-ext happens (prologue vs body).
- **`int new_var = 2; ... + new_var`**: factor out constants to break agbcc's index-folding.
- **`register Tname asm("rN")` pinning**: forces callee-save register saves and pins specific values across calls. Mostly used for matching arbitrary register assignments the original made.
- **`asm volatile("" : "+r"(d) : "r"(x))` barrier**: prevents agbcc -O2 from DCE'ing dead-looking computations. Use when the original preserves something you'd expect to be eliminated.
- **`void` vs `s32` return**: changes epilogue. Functions where the asm doesn't preserve r0 at return are void.
- **`else { r = const; dx = r; }`**: assigning a constant via a pinned register defeats agbcc's eager LP-load optimization in if-else dx-selectors.
- **ENTITY_* constants**: ENTITY_INIT=0, UPDATE=1, DIE=2, DISAPPEAR=3, EXIT=4. Die-routines usually set routine to EXIT, not DISAPPEAR.
