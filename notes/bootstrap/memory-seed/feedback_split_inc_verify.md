---
name: feedback-split-inc-verify
description: never delete a split_inc_multi _pN part without grepping it first — only the part before the FIRST listed function is empty
metadata: 
  node_type: memory
  type: feedback
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

`tools/split_inc_multi.py <inc> <fn1> [fn2 ...]` cuts the inc into N+1 parts: `_p1` = everything before fn1, then fn1's stub region is removed, `_p2` = between fn1 and fn2, etc. ONLY `_p1` is empty (just the prelude) **when fn1 is the very first `thumb_func_start` in the file**. If fn1 is not first, `_p1` contains all the preceding functions.

**Why:** I assumed `_p1` is always an empty prelude and `rm`'d it after splitting cubit_p13.inc around `cubit_08054674` (the 5th function). That deleted 4 real functions (cubitKnockBackDamage, cubit_080544c0, FUN_08054530, cubit_080545cc), landing a broken commit (`undefined reference` at link). Recovered via `git show <bad>~1:asm/boss/cubit_p13.inc > ...`, re-split correctly, amended.

**SECOND FAILURE MODE (2026-06-02):** on `harpuia_p3.inc` (2 funcs: FUN_080355c4, harpuia_08035684), `split_inc_multi.py <inc> FUN_080355c4 harpuia_08035684` **deleted the original and produced 3 EMPTY 5-6 line stub parts** (just `.include/.syntax/.text`, ZERO `thumb_func_start` each) — it silently failed to extract ANY function body. Caught by the grep-each-part check (all 0 → suspicious), restored via `git checkout -- asm/.../harpuia_p3.inc`. **Reliable manual fallback** (use when the tool emits empty stubs): carve the second function into its own inc with `sed -n '1,6p;<fn2_start>,$p' orig.inc > orig_b.inc` (header lines 1-6 + fn2 onward), write fn1 as C, then `INCASM("..._b.inc")` after the C body, and `git rm` the original after `grep -c thumb_func_start _b.inc` confirms fn2 survived. Worked first try for FUN_080355c4 (commit a9dd0b6b).

**How to apply:** After every split, `grep -c "thumb_func_start" <each part>` before deleting anything. Delete a part ONLY if the count is 0. When the target func is first, `_p1` is empty (drop it, wire `INCASM(_p2)`); otherwise wire `INCASM(_p1)` before the C body and `INCASM(_p2)` after. See [[reference-decomp-tooling]] and [[feedback-decomp-build-verify]] (always full `make compare` — it caught this).
