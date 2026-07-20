---
name: feedback_upstream_decomp_policy
description: mmzret's (upstream maintainer) decomp policy for rmz3 — entity layout, wrapper macros, typedefs, naming; follow it in every upstream-bound PR
metadata:
  type: feedback
---

The upstream maintainer published a decomp policy to reduce PR conflicts. All
upstream-bound work MUST follow it; fork-side code should converge toward it too.

**1. Entity structure layout — flatten, don't nest.**
Standardize on `COLLISION_OBJECT_HDR` (or `ENTITY_HDR` + `ENTITY_SPRITE`) for
all entity types so field access is `p->coord` / `p->mode[1]`, NOT `(p->s).coord`.
entity.h is currently mixed; the target state is uniform. agbcc has no C11
anonymous structs, hence the macros.

```c
typedef struct Boss {
  COLLISION_OBJECT_HDR;  // 0x00
  u8 buffer[48];         // 0xB4
} Boss;                  // 228 bytes
```

**Why:** avoids excessive `(p->s).xxx` nesting. Confirmed not to change
compilation results.

**2. Wrapper macros for Entity-taking functions.** Instead of casting at every
call site, define:

```c
void _Func(struct Entity* p);
#define Func(enti) (_Func((struct Entity*)(enti)))
```

so call sites read `Func(enti)` rather than `_Func((struct Entity*)(enti))`.
(SetMotion/SetSpriteAnimation is the canonical example — this is why upstream's
`SetSpriteAnimation(p, ...)` takes the entity directly.)

**3. Prefer `typedef` to simplify struct type names** wherever possible
(`typedef struct Boss {...} Boss;` → use `Boss*` not `struct Boss*`).

**Why (my read):** these three together are also what lets `p->field` work
uniformly regardless of entity kind.

**4. Naming: "Motion" → "SpriteAnimation".** Everything currently named Motion
will be unified as SpriteAnimation upstream. Our port dictionary already maps
SetMotion→SetSpriteAnimation and UpdateMotionGraphic→UpdateSpriteAnimation —
keep going in that direction and do NOT introduce new Motion-named symbols in
upstream-bound code.

**How to apply:** for new upstream PRs, write flattened access (`p->mode[1]`)
and typedef'd types when the target file's struct already supports it; where a
file still uses `struct Enemy { struct Entity s; ... }`, match the file's
existing style rather than half-converting it (mixed styles inside one file are
worse than either). Never rename/restructure in a matching PR — layout changes
belong in their own PR so byte-verification stays reviewable. See
[[project_resume_state]] for the port dictionary.
