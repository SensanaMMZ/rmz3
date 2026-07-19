# r8-corpus mining (2026-07-19)

Mined our own matched corpus for functions where agbcc EMITS r8 from clean C:
74 true C-compiled functions <=60 instrs (list: job tmp r8_fns.txt; smallest
real exemplar: ResetBossBody in src/boss.c, 27 instrs).

## The r8 recipe (proven by ResetBossBody)

agbcc parks the LOWEST-SPILL-PRIORITY call-crossing value (a constant) in r8
when r4-r7 are claimed by higher-priority call-crossing values. In
ResetBossBody: p(r5), &body(r4), &coord(r6) cross the InitBody call; the NULL
constant (movs r4,#0; mov r8,r4) is 4th -> r8. Constants have low spill cost
-> allocated LAST -> r8 when lows are gone.

## Beetank status after variant probes

- committed if/else: 103 instrs, 74 diff-lines (baseline)
- hoisted x / x+y: CSE'd away, no change
- chained `ya = a = FUN(...)`: CSE merges, 84 diff-lines
- asm-barrier copies (`asm("" : "=r"(ya) : "0"(a))`): 105 instrs, copies
  MATERIALIZE (see below) — best basin yet for the permuter; not shippable
  as-is (asm barrier) but proves the double-home shape is reachable.

Target fingerprint (re-read from beetank_target.s): -0x600 pool-loaded into
r2 then `mov r8,r2`; a chained r0->r4->r6 (store-home + cmp-home); b r0->r7;
cmp on the COPIES (r6,r7), stores from the ORIGINALS (r4,r0). First x-offset
-0x1000 via pool, second +0x1000 via movs/lsls (asymmetric!).

## Next leads
1. Restart decomp-permuter from the V3 barrier basin (105) instead of the
   plain form (which floored at 18 diffs after 48h).
2. Mine the other 73 exemplars for one with a call-crossing DOUBLE-HOMED
   value (grep their asm for `adds rX, r0, #0` twice after a bl) — its C
   would give the copy-idiom directly.
3. decomp.me API crawl (https://decomp.me/api/scratch?platform=gba&search=)
   for matched agbcc scratches with `mov r8` — same corpus idea, bigger pool.
4. The scratches in this directory are still worth posting.

V3 source form (for permuter seeding):
    s32 ya, yb;
    a = FUN_08009f6c((p->s).coord.x - 0x1000, (p->s).coord.y - 0x600);
    asm("" : "=r"(ya) : "0"(a));
    b = FUN_08009f6c((p->s).coord.x + 0x1000, (p->s).coord.y - 0x600);
    asm("" : "=r"(yb) : "0"(b));
    (p->s).coord.y = (a < b) ? ya : yb;

## Decisive negative (2026-07-19)

Swept ALL ~2,500 matched C functions for the target's exact fingerprint
(bl -> adds rX,r0,#0 -> adds rY,rX,#0): **zero occurrences**. The
double-home-after-call chain appears nowhere else in the entire matched
corpus. Beetank's codegen is a genuine outlier — add this fact to the
decomp.me ask (it rules out "common idiom we haven't found").

## Pokeruby exemplars DECODED (2026-07-19)

Strict re-scan (copy-of-copy only) leaves 2 true chains, both understood:

- **DoScroll_TextModeMonospace (text.c)** — `u16* buffer = call(win);
  u16* dest = buffer - 32;` → `add r7,r0` ; `add r5,r7` ; `sub r5,#0x40`.
  The copy survives CSE because dest is a GENUINELY DERIVED value and Thumb
  can't fold the 0x40 displacement into one insn. **Construct: derived
  variable from a call result, displacement beyond Thumb imm3.**
- **sub_8069638 (field_tasks.c)** — call result assigned to a REASSIGNED
  PARAMETER with uses across later calls.

Beetank experiments from these:
- E1 address-taken compare (`*ap < b`): folded away, 103 (no effect).
- E2 derived-compare (`ca = a - 0x40; cb = b - 0x40; (ca < cb) ? a : b`):
  **107 vs 109 — closest pure-C form ever**; copies materialize as
  copy+sub pairs; side-effect: p cascades r5→r6. Order-preserving for
  terrain Y values (no wrap in range), so semantically safe.
- E2 is now permuter basin v5 (pure C = shippable if it converges).
  Barrier basin v4 reached score 330 @ 25k iters (historical floor 235 @
  48h) and keeps running; original basin A at 725.

Open question is now sharper: find a derivation whose arithmetic FOLDS
AWAY (so the copy is emitted plain, without the sub) — or accept that
retail used a helper/idiom we haven't seen. The r8 part (constant -0x600
as the lowest-priority call-crosser) still needs the pressure raised by
one more live value; E2's ca/cb do exactly that, which may push -0x600
into r8 in some permuted variant.
