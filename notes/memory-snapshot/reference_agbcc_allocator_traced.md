---
name: reference_agbcc_allocator_traced
description: Instrumented agbcc reveals WHY registers get chosen — high regs come from the find_reg retry path; beetank's constant never competes because it's rematerialized
metadata:
  type: reference
---

Built an instrumented agbcc (playbook 1b) and got the allocator's own account.
Sources + rebuild steps: `tools/agbcc-debug/` (on ai-research); full writeup
`notes/agbcc-allocator-instrumented.md`.

**Build gotcha:** `make -C gcc -j1` — SERIAL. Parallel races the genrtl.h
generator and dies on bitmap.o. Fidelity verified: fresh build = byte-identical
.s to shipping tools/agbcc, with tracing on AND off. Debug binary stays OUTSIDE
tools/agbcc (jobs tmp/agbcc-dbg.exe).

**Usage:** `AGBCC_TRACE_ALLOC=1 agbcc-dbg ... 2>trace.txt` (inert without the
env var). Probes in global.c `find_reg` commit + spill paths and local-alloc.c
qty propagation; each line prints the priority inputs (size, calls_crossed,
live_length, n_refs).

**FINDING 1 — high registers (ip/r8) come from the RETRY path.** CopyBgMap:
`pseudo 39 -> SPILL` then `pseudo 39 -> r12`. A value that LOSES the low-reg
race gets retried into a high reg. Losers = long live_length but LOW n_refs
(39 had live 24/refs 3; the winners had refs 16, 10, 10). So the recipe for
r8/ip is: long live range + few refs + enough competitors to exhaust r4-r7.

**FINDING 2 — why beetank can't reach r8 from clean C.** Its 3 spills all have
calls_crossed 0 and never retry into a high reg. The -0x600 constant is
REMATERIALIZED (rebuilt cheaply at each use), so it never becomes a long-lived
allocno crossing the two FUN_08009f6c calls, and never enters the race it would
have to lose. **The beetank ask is therefore NOT "how do I get r8" but "what
source form stops agbcc rematerializing this constant" (need calls_crossed>=2
on its pseudo — checkable directly in the trace).**

**Method for any tie:** trace the holdout, compare the priority numbers against
what the target's assignment implies, and change the property that differs
(live length / ref count / call crossing) instead of guessing syntax. If a case
resists, add a probe for allocno_preferred_class + the conflict graph next.

**2026-07-20 TRACE-GUIDED RESULTS: (1) pret/agbcc PR #91 = the instrumentation as opt-in AGBCC_TRACE_ALLOC feature (fork SensanaMMZ/agbcc, branch feature/opt-in-alloc-trace; env-gated, byte-identical codegen). DECOMP-PROJECT compiler PR would be WRONG (breaks stock-agbcc premise) — only the pret/agbcc analysis feature is correct. (2) BEETANK PROVEN UNMATCHABLE: H1 shared-yoff/H2 volatile/H3 recompute all leave the offset pseudo at calls_crossed 0 — CSE merges the dup `coord.y-0x600` → cheap → rematerialized → never crosses calls → never races for r8. Mechanism-level proof; stays INCASM. (3) CountRodButton = tail-merge class (type A+C both `input=main`, agbcc cross-jumps, target keeps a copy). Distinct-but-equal expr for one branch → 2 non-pool diffs (closest ever); `count=count` dead-stmt does NOT block merge (must change the ASSIGNED VALUE). Needs a clean merge-blocking construct to finish. Same lever applies to the FUN_0802e338 family — retry there.**

**2026-07-20 TAIL-MERGE SPLIT INTO TWO SUB-CLASSES (trace-guided):
(A) BLOCKABLE — two branches assign the SAME value from the same expression
(CountRodButton: type-A & type-C both `input=main`). agbcc cross-jumps them;
an explicit extra branch (`else if (mode>=2) {main} else {main}`) that it can't
merge reproduces the target's kept copy → CountRodButton 4→1 instr (only a
z-home register-name tie left).
(B) UNBLOCKABLE from clean C — the branch CONDITION determines the assigned
value (FUN_0802e338 family: `if(ok){am[1]=0}else{am[1]=ok}`). In the else arm
agbcc PROVES ok==0 (that's why the branch was taken), folds any RHS spelling
(`ok`, `ok?1:0`) to 0, and merges. No source form steers this — the target kept
ok in a register because retail's compiler didn't run that value-prop. Stays
INCASM (Class 2c), now with a mechanism reason. Rule: mergeable ties where the
VALUE is branch-independent are crackable; ties where the CONDITION IS the value
are not.**
