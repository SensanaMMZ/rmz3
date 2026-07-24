#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

void Ghost67_Update(struct VFX* p);
void Ghost67_Die(struct VFX* p);
extern const VFXFunc sGhost67Updates[1];
extern u32 RNG_0202f388;

struct Unk67Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080c4914(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_067);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk67Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk67Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void Ghost67_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = -0xc0;
  } else {
    (p->s).d.x = 0xc0;
  }
  (p->s).d.y = 0;
  if ((p->s).work[1] == 0) {
    RNG_0202f388 = LCG(RNG_0202f388);
    (p->s).work[2] = ((RNG_0202f388 >> 16) & 7) + 0x7f;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
  }
  Ghost67_Update(p);
}

void Ghost67_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost67_Die(p);
  } else {
    (sGhost67Updates[(p->s).mode[1]])(p);
  }
}


void Ghost67_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

extern const s32* const PTR_ARRAY_0836f6b0[3];

void FUN_080c4aac(struct VFX* p) {
  u16 attr;
  (p->s).work[2]--;
  if ((p->s).work[2] == 0 ||
      ((attr = FUN_080098a4((p->s).coord.x, (p->s).coord.y)) != 0 &&
       !(attr & 0x8000) && (p->s).d.y > 0)) {
    CreateSmoke(2, &(p->s).coord);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  } else {
    switch ((p->s).mode[2]) {
      case 0: {
        const s32* const* tbl = PTR_ARRAY_0836f6b0;
        u16* mp = &((struct Unk67Props*)(p->props).raw)->unk_0;
        u32 base = (u32)tbl[*mp % 3];
        const s32* pair = (const s32*)(((struct Unk67Props*)(p->props).raw)->unk_4 * 8 + base);
        (p->s).d.y = pair[1] + (RANDOM(RNG_0202f388) & 0x1F);
        (p->s).d.x = pair[0] - (RANDOM(RNG_0202f388) & 0x3F);
        SetMotion(&p->s, *mp);
        (p->s).work[3] = 0;
        (p->s).mode[2]++;
        FALLTHROUGH;
      }
      case 1: {
        if ((u8)++(p->s).work[3] & 1) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
        (p->s).d.y += 0x20;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        (p->s).coord.x += (p->s).d.x;
        UpdateMotionGraphic(&p->s);
        break;
      }
    }
  }
}

void Ghost67_Init(struct VFX* p);
void Ghost67_Update(struct VFX* p);
void Ghost67_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost67Routine = {
    [ENTITY_INIT] =      Ghost67_Init,
    [ENTITY_UPDATE] =    Ghost67_Update,
    [ENTITY_DIE] =       Ghost67_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c4aac(struct VFX* p);

const VFXFunc sGhost67Updates[1] = {
    FUN_080c4aac,
};

const s32 s32_ARRAY_0836f650[24] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

const s32* const PTR_ARRAY_0836f6b0[3] = {
    &s32_ARRAY_0836f650[0],
    &s32_ARRAY_0836f650[8],
    &s32_ARRAY_0836f650[16],
};
