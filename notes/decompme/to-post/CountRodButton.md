# CountRodButton

**Scratch:** https://www.decomp.me/scratch/JxrgW (score 105/4800)

**Claim link (open while logged in):**
https://www.decomp.me/scratch/JxrgW/claim?token=eyJzbHVnIjoiSnhyZ1cifQ.17PdAlWURUtLp0_fSp8WCGw71U0

---

## Paste into the About tab

Essentially one instruction from matching. The `isSubWeapon` dispatch has type-A and type-C both selecting `mapping.main`; agbcc cross-jumps those two arms, but the target keeps them separate. Splitting them with an unmergeable extra branch (the `else if (mode >= 2)` plus a dead `else` in the source) reproduces that.

The only real residual is a register-name tie: the target parks `z` in **r3** for the whole function (`adds r3, r0, #0` at entry) and later does `adds r0, r3, #0`, while agbcc keeps `z` in r0 and copies to r1 instead. Pinning `z` to r3 with `register ... asm("r3")` cascades the rest of the allocation, so it is the coalescer class.

Any source shape that makes GCC 2.9 give `z` an r3 home here without disturbing the loop's allocation? Compiler: agbcc, `-mthumb-interwork -O2 -fshort-enums`.

**REPOSTED 2026-07-22** (old JxrgW expired -- anonymous scratches are deleted
if never claimed; claim promptly): https://decomp.me/scratch/x0fOU
Claim: https://www.decomp.me/scratch/x0fOU/claim?token=eyJzbHVnIjoieDBmT1UifQ.Hb-DGSAV9hmhomJUBMDbgLClUws
