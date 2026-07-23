# The matching workflow, in order

Written after the first match produced by the Ghidra harness
(`unused_080e9680` / `unused_080e9698`, ROM verified, upstream PR #49).

Read `notes/backlog-truth.md` alongside this — it holds the per-function
findings. This file is the procedure and the mistakes.

## 0. Before anything: know which flags the file uses

**Read the per-file overrides at the bottom of `makefile` first.**

```make
$(BUILD_DIR)/src/mmbn4.o:       CFLAGS := -O -mno-thumb-interwork
$(BUILD_DIR)/src/libs/agb_sram.o: CFLAGS := -O -mthumb-interwork
$(BUILD_DIR)/src/libs/m4a.o:    AGBCC  := tools/agbcc/bin/old_agbcc$(EXE)
```

Every ad-hoc probe and both ranking scripts hardcode `-mthumb-interwork -O2`.
For those three files that is simply the wrong compiler invocation, and any
diff taken with it is meaningless. This cost a whole wrong conclusion (below).

## 1. Pick a target

```sh
python3 tools/classify_holdouts.py     # 489 declared holdouts -> withc / pure
```

- **with a C body** → objdiff/permuter territory; the ranking match% is real.
- **pure INCCODE stub** → needs reconstruction first.

Rank by size (`tools/ghidra/rom_symbols.txt` has exact sizes). Small functions
are the cheapest matches — the first two matches were 24 and 46 bytes.

## 2. Get the structure

```sh
python3 tools/ghidra/batch_decompile.py      # -> build/ghidra-drafts/*.c
python3 tools/ghidra/resolve_pool_refs.py    # DAT_08xxxxxx -> real names
```

Cross-check against the m2c draft. Trust a structure when both agree; treat a
disagreement as a signal that one of them mis-decoded control flow.

## 3. Write C, then diff **bytes**

```sh
python3 tools/fnbytes.py ours.o expected/build/rmz3/src/FILE.o FUNC --diff
```

Never judge by `objdump -d`. A function that came from an `INCCODE`'d `.inc` is
stored as raw data in the expected object, so the disassembler renders it as
`.word`s and a disassembly diff says nothing.

## 4. Read the diff as evidence

The byte diff names the source-level property. From the two matches:

| what the bytes showed | what it meant |
|---|---|
| epilogue `pop {r1}; bx r1` instead of `pop {r0}` | `r0` live at exit → the value is **returned**, not discarded |
| an extra `lsls #24; lsrs #24` | a **`u8` return** forcing truncation → the type is a word |
| our size 46 vs their 48 | trailing **alignment padding** counted inside the asm symbol, not a real difference |
| `fff7 feff` vs `fff7 cbff` on a `bl` | **link-equivalent**: compiled code emits a relocation, the `.inc` baked the final offset in as `.byte` data |

`tools/fnbytes.py` and `build/scratch/cmp_text.py` classify the last one
automatically; check relocations before calling a `bl` difference real.

## 5. Verify at ROM level — the only check that cannot lie

```sh
make -j4 DEVKITARM=/c/devkitPro/devkitARM
sha1sum rmz3.gba      # ff7a801776dc76e6d8c7ef73a6660ae732934a3f
```

Do not commit a match before this passes.

## 6. Ship it upstream

On a match, open a PR against `mmzret/rmz3` so the maintainer can review:

1. `git checkout -b contrib/<name> upstream/dev`
2. apply the change **using their names** (`Coords32`, not `struct Coord`)
3. compile their file and compare against our SHA1-proven
   `expected/build/rmz3/src/*.o` — zero real differences
4. re-compile with `-Werror` (their build uses it) and confirm silence
5. commit, push to the `SensanaMMZ/rmz3-upstream` fork, open the PR with
   `base: dev`

## Build environment traps

Three separate things blocked the verification build, none of them related to
the code:

- **`DEVKITARM`** in the profile points at `/opt/devkitpro/devkitARM`, which
  does not exist here. Pass it explicitly:
  `make DEVKITARM=/c/devkitPro/devkitARM`. Without it `$(TOOL)/arm-none-eabi-as`
  resolves to `/bin/arm-none-eabi-as` and every assemble fails with error 127.
- **Stale `build/**/*.d`** referenced `include/constants/entity/projectile.h`,
  a header that does not exist in this tree. `find build -name '*.d' -delete`.
- **Prebuilt host tools** get rebuilt if their sources look newer, and they do
  not survive `-Werror` on a modern g++. Touch the `.exe`s.

## Corrections to conclusions I got wrong

Recorded because the reasoning errors are more reusable than the facts.

### "src/mmbn4.c is not our compiler's output" — WRONG

I found `push {r7, lr}` / `pop {r7, pc}` in its helpers, confirmed that form
appears only 3 times in the entire ROM (all in mmbn4), and concluded the file
came from a different toolchain — writing off 18 functions.

The evidence was real. The inference was not: I went from *"different from the
rest of the game"* to *"outside our toolchain"* without testing it. In fact the
makefile has always compiled that file with `-O -mno-thumb-interwork`, and
`-mno-thumb-interwork` is exactly what produces `pop {r7, pc}`. Every probe I
ran used the default `-mthumb-interwork -O2`. **The codegen looked foreign
because I compiled it wrong.** agbcc also reproduces `push {r7, lr}` with
`-fno-omit-frame-pointer` (which `-O2` disables), and `old_agbcc.exe` is
already in the tree, already used for `m4a.o`.

Status: **unknown, worth investigating** — not ruled out. Still unexplained is
that the target holds the global's address in r7 rather than a frame pointer,
and ends with a redundant `movs r0, r0` / `tst r0, r0`. The Klonoa GBA project
reports old_agbcc allocates pool loads to a different register and that `-ftst`
emits `tst` instead of `ands`+`cmp`, which is worth probing next.

### "The objdiff ranking shows the closest holdouts" — WRONG

`objdiff_rank.sh` compiles at `MODERN=1`, and `MODERN` swaps
`SET_ENTITY_ROUTINE` for a form that schedules differently. Twelve of nineteen
ranked entries **already matched the ROM**. A harness bug that reports 92% reads
as progress; one that reports 40% gets investigated. Trust that match% only for
functions actually declared `NON_MATCH`/`NAKED`.

### Verifications that silently passed while checking nothing

Four in one session. Each looked like a result:

- a byte comparison that piped `objcopy` to `/dev/stdout`, got nothing, and
  printed **BYTE-IDENTICAL** — comparing two empty strings, on functions whose
  sizes differed by 6 bytes;
- a hand-written-asm detector that skipped monolithic `.inc` files and so
  scanned a handful of functions instead of 2,409;
- a build-liveness check whose pattern matched `bash` processes, reporting a
  dead build as alive;
- two build-error greps that fired on the literal `-Werror` in a compile
  command and on a benign line starting with `make`.

The rule that came out of it: **a check that can pass without doing its work is
not a check.** Detectors now print their own coverage (`detect_handwritten_asm.py`
reports segments scanned and warns if too many parse empty), and comparisons are
calibrated in both directions — confirm the tool reports IDENTICAL for a known
match *and* DIFFERS for a known mismatch before believing either.
