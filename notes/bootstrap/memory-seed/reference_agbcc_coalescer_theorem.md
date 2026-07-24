---
name: reference_agbcc_coalescer_theorem
description: "Why the \"redundant register spreading\" holdout class is C-unreachable — agbcc coalesces all SImode copies, so extra pressure can only come with an extension insn"
metadata: 
  node_type: memory
  type: reference
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

**The SImode-coalescer theorem (proven for beetank via [[reference_agbcc_rtl_dumps]], 2026-06-02).**
A precise, reusable explanation for the whole "redundant register spreading" /
"target uses one more callee-saved reg than my clean C" holdout class.

**Setup:** some targets occupy MORE callee-saved registers than the faithful C
compile, doing only plain 32-bit (SImode) work, with NO sign/zero-extend insns.
Beetank is the canonical case: target caches the shared constant `-(6<<8)` in
**r8** (a high callee-saved reg, forcing the r8 push/pop) and double-homes both
`a` and `b`; clean C caches the same constant in **r4** and keeps one copy each.

**What the RTL dumps showed:**
- The clean C **already CSEs the shared constant and reuses it across both calls**
  — structurally identical to the target. The ONLY difference is r4 vs r8, driven
  purely by how many *other* values are simultaneously live (register pressure).
- To bump the constant from r4 up to r8 you must occupy r4–r7 with other live
  values, i.e. keep a redundant second copy of `a`/`b` live across a call.
- **agbcc's register coalescer folds away every SImode (plain 32-bit) redundant
  copy** (`s32 t = a;`, ternary temp, call-surviving copy — all coalesced → no
  extra pressure → no r8). Verified: variants `clean`, `s32 new_var`, `(a<b)?a:b`
  all emit `push {r4,r5,r6,lr}`, zero r8 refs.
- The ONLY non-coalesceable scalar copies are non-SImode, and each drags an
  extension/fill insn the target doesn't have:
  - `short`/`char` (HI/QImode) → occupies an extra reg BUT emits a sign-extend
    (`asr`/sxth) on store, and only reached r7 (not enough for r8).
  - `long long` (DImode) → occupies the reg *pair*, reaches r8, BUT the high word
    is a dead `asr #31` **born at RTL-generation and never dead-code-eliminated**
    (the DImode value stays live until the truncating store, so flow never sees
    the high word as dead).

**Theorem:** In agbcc you cannot raise register pressure with a redundant *copy*
of an SImode value — the coalescer always removes it. Therefore a target whose
extra register occupancy coexists with **plain SImode stores and no extension
insn** has *no agbcc-compilable C preimage*: any C that occupies the extra
register also emits an extension instruction (HImode→sxth/asr, DImode→asr#31)
that the target lacks. {extra-reg, SImode-only, no-extension} is unreachable.

**Litmus test for this holdout class (use before sinking time into one):**
diff the faithful compile vs target. If the target occupies ≥1 more callee-saved
register while doing only SImode ops and contains NO extension insn the clean
build lacks → it's C-unreachable; resolve as `NON_MATCH #if MODERN` dual-form
(see beetank in [[project_open_todos]]) and move on. Don't grind the permuter
(beetank: ~20M iters floored at score 235) or hand-variants (~37 tried).

**Litmus run on the 6 set-aside allocation holdouts (2026-06-02) — NONE fit the wall:**
`FUN_080939e8`/`FUN_08093a20` (shotloid), `FUN_08094fa8` (pantheon_fist),
`FUN_0803a5c8` (shield_fly), `forceWaterLanding` (sharkseal_x), `dragInSea` (puffy).
All are SImode-only, NO high-reg (r8+) spill, NO extension insn, NO single-value
double-home. They're **low-register numbering/scheduling divergences**, the SAME
tractable class as the already-solved `generator_cannon`/`gallisni` — NOT the
coalescer wall. So they are **permuter/restructure territory, not proven-dead.**
Concrete proof: `forceWaterLanding` faithful C (`if (SEA > p->coord.y) p->coord.y
= SEA;`) compiles to **14/14 instr, identical structure** — the only diff is the
target shifts every temp up one reg (p→r3 skipping r0; mine p→r2). ~10 source-level
variants (operand order, temps, ptr-caching) ALL keep p in r2 — the shift is
**sticky to hand-restructuring**, so it's genuine permuter work, not a quick win.
"Not the wall" ≠ "easy": these need the permuter (which is what it's FOR — low-reg
search), unlike beetank where the permuter was futile. Don't dual-form these; grind them.

Related: [[reference_agbcc_rtl_dumps]], [[reference_agbcc_match_idioms]], [[project_open_todos]].
