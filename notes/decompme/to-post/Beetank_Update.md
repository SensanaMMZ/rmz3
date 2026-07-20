# Beetank_Update  (already claimed — description still needs posting)

**Scratch:** https://www.decomp.me/scratch/gwvlA

Already attached to your account, so no claim link is needed — just open the
About tab and paste. A community fork (ZBgsB) reached 805 using register pins
plus asm barriers, but it is not valid C (`yOffset` is read before it is ever
assigned), so the question below still stands.

---

## Paste into the About tab

This function matches except the final `coord.y = min(a, b)` clamp. Retail codegen has three features clean C never reproduces with agbcc -O2:

1. the `-0x600` constant is cached in **r8** (costing the `mov r7,r8` / `push {r7}` prologue pair visible in the diff);
2. both call results are **double-homed** — the compare reads copies (`adds r6,r4,#0` / `adds r7,r0,#0`) while the stores use the originals;
3. no high-word instruction anywhere (a `long long` form floors at 18 diffs with a dead `asr`).

What has been ruled out: roughly 48 hours of decomp-permuter search floored at 18 instruction diffs; RTL dumps (`-da`) show clean C value-numbers the copies away in cse2; and the exact `bl` → `adds rX,r0` → `adds rY,rX` chain appears **zero times across ~2,500 matched functions** in this project. The closest clean-C form derives the compare operands (`ca = a - 0x40; cb = b - 0x40; (ca < cb) ? a : b`), which materializes both copies and reaches 107/109 instructions — but with `sub`s attached, and it shifts the surrounding allocation.

Has anyone seen GCC 2.9 pick a high register as a reload base like this, or know a source shape whose derivation folds to a *plain* copy (compare on copies, stores from originals)?
