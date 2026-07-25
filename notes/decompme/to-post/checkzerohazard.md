# CheckZeroHazard — posted 2026-07-25 (compiles server-side: success=True)

- scratch: https://www.decomp.me/scratch/16JgT
- claim: https://www.decomp.me/scratch/16JgT/claim?token=eyJzbHVnIjoiMTZKZ1QifQ.RStAmJOMBGPfaOr12UrsLYNFNJ4
  (USER: open while logged in — anonymous scratches expire)
- root cause: whole-function register-role shuffle on a leaf loop — the
  target pins z into ip with `mov ip, r0` as the FIRST insn, x->sl,
  y->sb, count-ptr->r5, gOverworld->r6; ours lands z in r2/x in ip.
  Statement-level structure is PROVEN correct (188/188 size-exact seed):
  hoisted u8 len, per-field pooled anchors for start.x/.y
  (gOverworld+0x1DC/+0x1E0) + base-register access for w/h/objectLen.
  22k permuter iterations found nothing better.
- payoff: 3 functions share the anchors (CheckZeroHazard 0802707C,
  IsInHazard 080283EC, IsAgainstHazard 0802848C) — solving one
  transfers.
- best local harness: build/scratch/hz/t4.c

About-tab text:
  188-byte hazard-overlap scan (leaf, no calls). Every instruction
  matches modulo a whole-function register-role rotation: target does
  `mov ip, r0` first and keeps the Zero pointer there, with x in sl and
  y in sb. agbcc (gcc 2.9 thumb) -O2 -mthumb-interwork -fshort-enums.
  Statement shape is locked (size-exact); looking for whatever source
  quirk rotates the allocation order.
