# Upstream decomp policy — compliance audit (2026-07-20)

The maintainer published a policy to reduce PR conflicts. Full text recorded in
`memory-snapshot/feedback_upstream_decomp_policy.md`. This is what the audit of
our open PRs found and what was changed.

## The policy, in four parts

1. **Flatten entity layout.** Standardize on `COLLISION_OBJECT_HDR` (or
   `ENTITY_HDR` + `ENTITY_SPRITE`) so access is `p->coord`, not `(p->s).coord`.
2. **Wrapper macros** for functions taking `struct Entity*`, so call sites read
   `Func(enti)` instead of `_Func((struct Entity*)(enti))`.
3. **Prefer `typedef`** to simplify struct type names.
4. **Naming:** "Motion" will be unified as "SpriteAnimation".

## Audit findings

**Item 1 — no action needed (and none should be taken in matching PRs).**
Upstream's `entity.h` today defines `OBJECT_HDR` (= `struct Entity s; struct
Body body;`) and has no `COLLISION_OBJECT_HDR` yet; Boss/Enemy/Projectile/Solid
all use it. So `(p->s).mode[1]` is the *current* correct style and our PRs match
the tree as it stands. The flattening is a future migration the maintainer will
drive; a matching PR should not half-convert it, because mixed styles inside one
file are worse than either, and layout churn makes byte-verification unreviewable.

**Item 4 — violations found and fixed.** 18 call sites across 13 files still used
raw Motion-era spellings. Our porter rewrote `SetMotion(&p->s, …)` but missed
other receiver names (`&z->s`, `&vfx->s`) and the `InitNonAffineMotion` form:

| was | now |
|---|---|
| `SetMotion(&z->s, …)` | `SetSpriteAnimation(z, …)` |
| `InitNonAffineMotion(&p->s)` | `EnableSpriteAnimation_Normal(p)` |
| `UpdateMotionGraphic(&p->s)` | `UpdateSpriteAnimation(p)` |

Fixed on `contrib/tail-batch-1` (10 files) and `contrib/projectile-batch-1`
(3 files). **Every rewritten file was rebuilt and byte-compared against its
pre-rewrite object: all identical**, as expected since the macros expand to the
same calls. No other open branch had violations.

**Items 2 and 3 — satisfied by construction.** The fix above *is* the wrapper-macro
form, and the ported code uses upstream's existing typedefs.

## Standing rule for future work

New upstream-bound code: wrapper-macro spellings, no new Motion-named symbols,
match the target file's existing entity-access style, and never mix a
rename/restructure into a matching PR.
