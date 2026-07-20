---
name: reference_permuter_packed_caveat
description: "decomp-permuter sandbox strips __attribute__((packed)) — gives FALSE matches for functions reading packed structs (gOverworld etc.), because layout change cascades into register allocation"
metadata: 
  node_type: memory
  type: reference
  originSessionId: d60616bc-5cd9-45d6-8dfd-d8157cd33fc4
---

**The permuter sandbox is UNRELIABLE for functions that read packed structs**
(notably `gOverworld` / `struct Overworld` / `struct Terrain`). Verified 2026-06-02
on `forceWaterLanding`/`dragInSea`.

`tools/permuter-setup/compile.sh` passes `-D__attribute__(x)=` (pycparser can't
parse GNU attributes), which strips `__attribute__((packed))`. This doesn't just
shift field *offsets* — the changed struct *size/layout* cascades into agbcc's
**register allocation**, so the sandbox compile of a candidate and the real
(`make`) compile of the SAME C produce **different register assignments**.

**The trap:** the permuter reported `forceWaterLanding` candidate at **score 5**
— instruction-identical to target.o except the literal pool `0x2c014` vs
`0x2c00c` (the stripped-packing offset shift). Looked like a near-match. But
dropped into the real build, the candidate STILL had the original register shift
(p→r2 not r3) — the score-5 was a pure sandbox artifact. ~30 min wasted chasing it.

**Rule:** before trusting ANY permuter result, check if the function reads a
packed struct (grep the body for `gOverworld`, `.terrain`, `.sea`, or any
`__attribute__((packed))` type). If so, the score is untrustworthy — ALWAYS
confirm a candidate in the real `make compare` build before believing it, and
treat low sandbox scores on these as likely false. Functions touching only
unpacked structs (most Entity/Enemy AI) are fine — their sandbox scores are valid.

This refines the existing `-D__attribute__(x)=` note (offsets differ) — the
deeper problem is allocation divergence, which silently breaks register-shift
matching, the exact thing the SEA-clamp permuter run was trying to solve.

**THE FIX (2026-06-02) — fake-struct candidate pins the field at its true offset.**
Don't access the packed field by its real name (`gOverworld.sea`, layout-dependent)
and don't use a raw `u8[]+offset` either — the latter FOLDS to a single link-time
literal (2-instr load) whereas the target does a runtime base+offset (4-instr,
because struct-field access with a large offset materializes the offset in a reg
and adds). Instead declare a FAKE struct that places the field at the exact ROM
offset by construction, then access it as a normal field:
```c
struct SeaOW { u8 _pad[0x2c00c]; s32 sea; };
extern struct SeaOW gOverworld;     // links to the real symbol; type is local-only
... gOverworld.sea ...              // 4-instr struct-field codegen, offset 0x2c00c FIXED
```
This (a) is layout-independent (sandbox == real build), AND (b) reproduces the
target's struct-field addressing (4 instr, not the folded 2). Verified: forceWater-
Landing/dragInSea went 11→14/14 instr and base score became a faithful 80 (the real
register-shift) instead of the misleading sandbox 5. No conflict because the host
src (sharkseal_x.c/puffy.c) doesn't include overworld_terrain.h, so the fake decl is
the only `gOverworld` in base.c. General recipe for any packed-struct permuter func.

Related: [[reference_decomp_tooling]], [[reference_agbcc_coalescer_theorem]] (these SEA clamps are register-shift, not the coalescer wall), [[project_open_todos]].
