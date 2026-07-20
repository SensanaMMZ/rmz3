# Instrumented agbcc — why the allocator picks the registers it picks

Playbook attack 1b, executed 2026-07-20. This is the first time we have the
compiler's own account of its register decisions instead of inference from
output. **It answers the "why r8/ip" question that ~48h of permuter search and
months of source variants could not.**

## Build

`pret/agbcc` source, built with the MSYS2 gcc + devkitARM binutils already on
this machine.

- **Build serially.** `make -C gcc -j1` (what upstream's `build.sh` does).
  A parallel build races the `genrtl.h` generator and dies on `bitmap.o`.
- Fidelity gate before trusting anything: the freshly built binary produced
  **byte-identical `.s`** to our shipping `tools/agbcc` on beetank.c, menu.c
  and input.c. The instrumented binary is identical too, with tracing both
  off *and* on — logging never perturbs codegen.
- The debug binary lives **outside** `tools/agbcc` (jobs tmp `agbcc-dbg.exe`).
  The shipping toolchain is untouched, so clean-room status and every existing
  match are unaffected.

## The instrumentation

Two probes, both gated on an env var so the binary is inert by default:

- `gcc/global.c`, at the point `find_reg` commits a hard register — logs the
  pseudo, chosen reg, and the four numbers the priority sort is built from:
  `size`, `calls_crossed`, `live_length`, `n_refs`. A second probe logs the
  case where `find_reg` fails (spill).
- `gcc/local-alloc.c`, where quantities propagate to pseudos — logs pseudo,
  reg, `births`, `deaths`, `n_calls_crossed`.

Run with `AGBCC_TRACE_ALLOC=1 agbcc-dbg ... 2>trace.txt`.

## Finding 1 — high registers come from the *retry* path

CopyBgMap's trace ends:

```
[galloc] pseudo 39 -> SPILL (allocno 9, calls_crossed 0)
[galloc] pseudo 39 -> r12  (allocno 9, size 1, calls_crossed 0, live_length 24, n_refs 3)
```

The pseudo **fails** the first allocation pass, then a retry places it in
**r12 (ip)**. So `mov ip, r0` in retail is not a preference — it is what agbcc
does to a value that *loses the low-register race and is retried*.

The losers are decided by the priority sort: pseudo 39 has a long live range
(24) but only 3 references, so it sorts behind everything with more refs.
Compare the winners in the same function: r2 got 16 refs, r1 got 10, r4 got 10.

**The recipe for a value to land in a high register: long live range, few
references, and enough competing live values to exhaust r4–r7 first.**

## Finding 2 — why beetank never reaches r8 from clean C

Beetank's trace has three spills, and **none of them retry into a high
register** — they stay spilled. The call-crossing profile explains it:

| calls_crossed | allocnos |
|---|---|
| 0 | 77 |
| 1 | 8 |
| 7 | 1 |

Every spilled pseudo has `calls_crossed 0`. The `-0x600` constant in our C is
**rematerialized** — agbcc rebuilds it cheaply where needed rather than keeping
it live, so it never becomes a long-lived allocno that crosses the two
`FUN_08009f6c` calls, and therefore never enters the race it would have to
*lose* to reach r8.

In the retail build that constant is live across both calls (that is precisely
why it needs a callee-saved high register, and why the function pays the
`mov r7,r8` / `push {r7}` prologue).

**So the beetank ask is now specific:** we need a source form where the
`-0x600` operand is a value agbcc will not rematerialize — one that is live
across both calls, referenced few times, competing against enough other live
values. Not "how do I get r8", but "how do I stop this constant from being
rematerialized". That is a much smaller search space, and it is testable
directly from the trace (look for `calls_crossed >= 2` on the constant's
pseudo) instead of by diffing output.

## How to use this on any holdout

1. Extract the function into a standalone file with a minimal context.
2. `AGBCC_TRACE_ALLOC=1 agbcc-dbg -mthumb-interwork -O2 -fshort-enums ... 2>t.txt`
3. Compare the trace's priority numbers against what the target's register
   assignment implies. The mismatch tells you which property to change
   (live length, ref count, call crossing) rather than guessing at syntax.

## Caveats

- The traces above are of *our* C, not retail's — they show why our output is
  what it is. Retail's numbers are inferred from its register choices.
- Priority ordering also depends on `reg_preferred_class` and the conflict
  graph, which are not yet logged. If a case resists, log
  `allocno_preferred_class` next.


## Applied to beetank — a rigorous negative result (2026-07-20)

Trace-driven, three hypotheses to get `-0x600` to cross the two calls:
- **H1** shared `yoff = coord.y - 0x600` → 103; CSE had already merged the two
  `coord.y - 0x600`, so sharing changed nothing (kept the *sum*, not the constant).
- **H2** `volatile s32 k = -0x600` → 107, but volatile forces a **stack slot**.
- **H3** recompute the offset before each call → 103; CSE re-merges it.

Every form shows the offset pseudo at `calls_crossed 0`. The lock: (1) CSE merges
the duplicate `coord.y - 0x600` to one value; (2) it is cheap, so agbcc
**rematerializes** rather than keeping it live; (3) rematerialized values never
cross the calls, so it never enters the low-reg race it must lose to reach r8.
This is a mechanism-level proof that beetank's r8 is unreachable from clean C
via agbcc's CSE+remat interaction. Stays INCASM.

## Applied to CountRodButton — near-match via merge-blocking (2026-07-20)

48 vs 48 with one missing copy (`adds r0, r3, #0`): the type-A and type-C
branches both set `input = main`, and agbcc cross-jumps them while the target
keeps them separate (same tail-merge class as the FUN_0802e338 family). A
distinct-but-equal expression for one branch blocks the merge and reaches **2
non-pool diffs** — the closest this function has been — but the only form found
so far is an ugly pointer-arithmetic no-op. A clean merge-blocking construct
would finish it. (`count = count;` does NOT block the merge; the expression must
differ in the *assigned value*, not add a dead statement.)


## CountRodButton — one instruction from a match (2026-07-20, trace-guided)

Refined the tail-merge block. The winning clean form is an explicit split that
agbcc cannot cross-jump:

```c
u8 mode = (z->unk_b4).status.keyMap.attackMode;
if (mode == 0)      input = (z->input).mapping.main;   // type A
else if (mode == 1) input = (z->input).mapping.sub;    // type B
else if (mode >= 2) input = (z->input).mapping.main;   // type C
else                input = (z->input).mapping.main;   // unreachable, blocks merge
```

This reaches **1 instruction off (2 diff lines)** — the best ever. The only
residual is a register-name tie: the target keeps `z` in r3 (`adds r0,r3,#0`),
mine keeps it in r0 (`adds r1,r0,#0`). Pinning `z` to r3 cascades the whole
allocation (32 diffs), so it is the coalescer/allocation-tie class that resists
both pins and the permuter. Left as INCASM at 1 instruction; if the instrumented
allocator later gains a `preferred_class` probe, this is the test case.
