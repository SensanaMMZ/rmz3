# The rmz3 decomp with Claude — how it was set up, and where it stands

A narrative record of the whole collaboration: what the setup was, how the
workflow evolved era by era, and the current state. Companion doc to
`claude-setup.md` (which is the how-to distillation of this journey).

---

## 0. The starting point

- Target: **Mega Man Zero 3 (JP)**, byte-perfect matching decomp against the
  retail ROM (`ff7a8017…`), building on the mmzret/rmz3 project as upstream.
- Private working fork: `SensanaMMZ/rmz3`. Upstream contributions flow
  through a second fork so PRs land on mmzret/rmz3 cleanly.
- Toolchain: **pret agbcc** (GCC 2.9 Thumb-1 reconstruction) + devkitARM
  binutils, driven from Claude Code on Windows (Git Bash / MSYS mix — an
  early lesson was normalizing every path with `cygpath -m` before it
  crosses the MSYS/Windows boundary).
- Ground truth: an `expected/` tree of proven-matching objects, so any
  candidate C can be compared function-by-function without a full ROM link.

## 1. Building the verification loop (the foundation era)

The first real infrastructure was `tools/mdiff.sh`: compile ONE file with
the exact retail flags, objdump-diff ONE function against expected, print
instruction counts. Hard lessons got baked in as guards over time:

- stale `.o` files lie → force rebuild before trusting any match;
- a failed compile diffs two empty dumps as a fake "0 diffs" → guard
  missing symbols;
- agbcc emits partial code past some errors → hard-fail on any
  non-warning diagnostic;
- disassembly framing can fabricate "real" diffs → the final arbiter is
  raw `.text` bytes with reloc words accounted for.

Sibling tools followed: `modern_sweep.sh` (rank every holdout by closeness),
`refresh-expected.sh`, and a permuter harness (`tools/permuter-setup/`).

## 2. The matching eras (how ~2,500 functions got matched)

Progress came in idiom waves, each recorded in a growing catalog
(`MATCHING_IDIOMS.md` + persistent memory) so it compounded:

- **Struct/field discipline** — every entity access through the project's
  named fields; wrong-but-compiling field paths silently destroy matches.
- **The register-asm discovery** — `register T x asm("rN")` pins crack
  single register-allocation ties that looked C-unreachable (this overturned
  an earlier "coalescer theorem" that had written those off).
- **Dispatch and bitfield idioms** — jump-table state machines, shift-extract
  forms, chained assignments.
- **The permuter, demoted** — random search proved useless on allocation
  ties from plain C; it only pays when seeded from an engineered basin.
  Its sandbox also strips struct packing → false matches on gOverworld
  readers; every "improvement" is re-verified in the real build.
- **The dual-form convention** — functions whose logic is decoded but whose
  bytes resist: committed as `NON_MATCH`/`NAKED` with a `#if MODERN` C body
  documenting the semantics and the asm carrying the bytes. ~61 of these
  remain, each with a recorded reason.

Deep-dive artifacts from this era: the beetank r8 analysis (a full RTL-level
characterization of the hardest register-allocation holdout) and the proof
that the remaining gaps are source-reconstruction problems, not compiler
bugs.

## 3. The upstream porting era (33 PRs, ~940 functions)

Mid-2026 the fork was far ahead of upstream: over a thousand functions we
had matched still shipped as raw asm in mmzret/rmz3. The porting campaign
translated them to upstream's naming and structure and sent them back:

- A translation dictionary grew case by case (allocator names are *swapped*
  between the trees — caught by a reloc audit that found one shipped bug;
  motion/palette/score subsystem renames; their flattened entity types).
- Verification hardened into a per-file pipeline: size, per-function
  encodings, symbol spans, and reloc names joined on offset.
- The end state was an industrialized porter (`port_file.py`): transplant
  the fork's C over upstream's monolithic asm file, split the asm around it
  into segments, auto-reconcile declarations, auto-add includes, verify.
  Batches went from one function per PR to ~80 files per PR.

Result: **PRs #16–#45 on mmzret/rmz3, ~940 byte-verified functions**, zero
unverified submissions, and a failure queue worked to empty.

## 4. The holdout research era (current)

With porting done, attention returned to the hard residue. The blockers
were classified into four classes (see `holdout-playbook.md`) with a
per-class attack plan. What that produced so far:

- **Corpus mining** — instead of guessing what C produces a codegen shape,
  index every matched function's asm and search it. `pattern_index.py`
  covers 15,127 functions (this repo + pokeruby). It answered in an
  afternoon what 48 hours of permuter search hadn't: the exact conditions
  for an r8 reload base, and the derived-variable construct that survives
  CSE as a register copy.
- **Flag archaeology** — a falsifiable sweep of GCC 2.9 optimization
  switches against the tail-merge family. Verdict: cleanly falsified (no
  flag recipe reconciles the whole file), which retired that hypothesis
  permanently and left a reference shape for the remaining attempts.
- **m2c first drafts** — m2c's ARM target now drafts the entire remaining
  asm tail: **1,861 structurally-correct C drafts from 616 asm includes**,
  post-processed into project idioms and ranked into a worklist. This is
  the throughput path for everything not yet decoded.
- **Community surface** — the hardest holdout is live as a decomp.me
  scratch (Beetank_Update) with a precise allocator question; it drew its
  first community fork within a day (pins+barriers — validating the shape,
  not yet valid C).
- **Permuters** — three seeded basins ran in parallel on beetank; all
  plateaued above the historical floor, confirming (again) that this class
  doesn't fall to search.

## 5. Where we are now

- **Fork**: ~2,500 functions matched; every remaining asm function has a
  ranked m2c draft waiting.
- **Upstream**: 33 PRs / ~940 functions contributed and byte-verified.
- **Holdouts**: ~61 dual-forms, each classified with a documented reason
  and an active attack (or an honest "this is retail's compiler being
  weirder than clean C can be").
- **Research kit**: shared on the `ai-research` branch — playbook, setup
  guide, scratch packages, corpus index, draft pipeline.
- **Open front**: the register-allocation tie class — one community answer
  or one instrumented-allocator session away from its next breakthrough.

The through-line of the whole project: **give the model a byte-truth loop
it can run itself, record every result in memory (negative ones included),
and escalate from guesswork to corpus evidence.** Everything else was
iteration.
