# The matching workflow, in order

Written after the first match produced by the Ghidra harness
(`unused_080e9680` / `unused_080e9698`, ROM verified, upstream PR #49).

Read `notes/backlog-truth.md` alongside this — it holds the per-function
findings. This file is the procedure and the mistakes.
`notes/urls-of-gba-decomps/extracted-practices.md` is the companion knowledge
base: flag levers, C nudge catalog, and tooling surveyed from 17 other GBA
decomps (2026-07-23). Consult it when a function resists step 4.

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
| pool word `symbol+0xNNN` (one reloc), other addresses derived by runtime adds | the source anchors a **local pointer at that offset** (`T** ep = &g.member;`) and derives everything else arithmetically from it. `&g.member`/`&arr[N]` pools the addend in place (REL: word holds 0xNNN + R_ARM_ABS32). `ep - K` pools `-0xNNN` instead of folding back to `symbol+0` when the anchor is a local. Proven on FlushOAM (120/120); applies to the `gOverworld+0x1DC` hazard cluster. **Method: write tiny probe TUs to learn which shape produces the pool form before touching the real function.** |

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

Status: **RESOLVED (2026-07-25)** — the module is hand-written assembly.
The `movs r0, r0` / `tst r0, r0` tails are flag-register returns: callers
`beq` immediately after `bl` with no comparison (asm/mmbn4.inc:1681). No
compiler emits flag-returning calls, so no flag sweep can ever match these
18 functions; they stay NAKED permanently, like crt0. The original
"different from the rest of the game" observation was correct — the
error was assuming it had to be a *compiler* difference.

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

Addendum to the byte-evidence table: **a declaration's return type is
load-bearing in every CALLER, not just the definition** — retyping a
bool8 helper to bool32 deletes the `lsls #24` truncation at each call
site that tests the result (Mellnet_Update shrank 2 bytes and shifted
the whole ROM). When lifting a stub whose declared type you want to
change, grep its callers first; the sha1 gate is the only reliable
catch. Related: probe TUs never verify declaration-type effects on
callers, and reloc masking never verifies data-index addends — both
are ROM-build-only checks (cattatank, mellnet 2026-07-24).

Second addendum (byte-evidence table growth, 2026-07-24):
- an unexplained register copy WEDGED INSIDE a condition evaluation
  (between `ands` and `cmp`) = the source computes the condition into a
  named temp, assigns an unrelated variable, then tests the temp
  (`t = x & 1; ptr = other; if (t)`) — proven on FUN_080b963c;
- `movs rX,#1; orrs rX,rY` with the 1 landing DIRECTLY in the result
  register = compound two-statement form (`v = 1; v |= y;`); both
  `v = y | 1` and `v = 1 | y` route the constant through a scratch reg
  first — proven on FUN_080b9cf8;
- an asymmetric (u8) truncation between two if/else arms assigning the
  same variable is NOT a contradiction: GCC 2.9 combine is per-basic-
  block, so the arm that only copies a cross-block value keeps its
  truncation while the arm that computes a fresh OR loses it.

## 4b. Cross-reference the decomp corpus BEFORE contorting a harness

Added 2026-07-25. `tools/decomp_crawl.py` mirrors every repo in
`notes/urls-of-gba-decomps/list-of-decomps.md` into `../decomp-corpus/`,
compiles each project's `src/**/*.c` with OUR agbcc, and indexes every
function's instruction stream. That turns "which C shape produces this
instruction?" into a lookup instead of a guess.

```sh
python3 tools/decomp_crawl.py clone [proj ...]   # shallow clone / fetch
python3 tools/decomp_crawl.py index [proj ...]   # compile + index + dated reports
python3 tools/decomp_crawl.py grep 'mov\s+r8'    # corpus-wide instruction search
python3 tools/decomp_crawl.py check              # weekly: which upstreams moved
```

Reports land in `notes/decompme/crawl/<proj>_<trait>_report_<YYYY-MM-DD>.md`
(same format as the original `pokeruby_r8_report.md`), one file per trait per
crawl date, so old reports stay as a record and new ones never overwrite them.
Traits indexed: r8/high-reg pinning, `and #0xff` vs `lsl/lsr #24` byte
truncation, `__umodsi3`/`__udivsi3`, `mul`, `rsb`, `bic`, `tst`, `mov ip`.
`../decomp-corpus/manifest.json` records each project's commit + crawl date.

**Ordering rule:** corpus grep comes AFTER the byte diff names the property
(step 4) and BEFORE escalating to decomp.me (step 5). Posting a scratch
without having grepped the corpus for the offending instruction wastes a
community ask on something the corpus can answer — and the scratch write-up
should cite what the corpus did or did not show.

**Cadence:** re-run `check` weekly; re-clone + re-index only the projects it
reports as moved. Note that projects using non-agbcc toolchains still index
usefully (their C compiles under agbcc often enough to be a source-shape
corpus), but `files_failed` in the manifest tells you how much of a project
was unusable.
