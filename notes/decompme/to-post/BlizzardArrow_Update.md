# BlizzardArrow_Update (rmz3, agbcc) — 840/872 bytes, one duplicated block

Retail contains the "die" sequence **twice**:

    _0803BACC:  <SET_WEAPON_ROUTINE(p, ENTITY_DIE)> ; bl BlizzardArrow_Die ; b <epi>
    _0803BD1A:  <SET_WEAPON_ROUTINE(p, ENTITY_DIE)> ; bl BlizzardArrow_Die   (falls into epi)

The first is the target of the `work[3]` test and the off-screen check; the
second is the target of the `work[2]` countdown. agbcc cross-jumps mine into
a single copy no matter how the source is written, costing 32 bytes.
Confirmed by count: mine has 1 `str r1,[r6,#12]` and 10 `bl`; retail has 2
and 11.

Tried and failed:
- inlining the second copy at its use site;
- moving it to the physical end of the function so it falls into the epilogue
  (retail's layout), reached by `goto`;
- a distinguishing zero-byte `asm` barrier at the start, the middle and the
  end of the second block, as both `asm` and `asm volatile`.

The barrier trick reliably separates two identical *straight-line* blocks in
this codebase, but not when the shared tail is a call — the `bl` plus the
return edge always merge.

Question: what source shape keeps agbcc from cross-jumping two blocks that
end in the same `bl`?

Everything else in the function matches, including the LCG chain on
RNG_0202f388 and both flip blocks.
