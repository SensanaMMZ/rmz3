#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[2];
void VFX60_Update(struct VFX* vfx);
void VFX60_Die(struct VFX* p);
extern u32 RNG_0202f388;

struct Unk60Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* CreateVFX60(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_060);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk60Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk60Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void VFX60_Init(struct VFX* p) {
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
  RNG_0202f388 = LCG(RNG_0202f388);
  (p->s).work[2] = ((RNG_0202f388 >> 16) & 7) + 0x7f;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  VFX60_Update(p);
}

void VFX60_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX60_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}


void VFX60_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}


void nop_080c2d44(struct VFX* vfx) {}

INCASM("asm/vfx/unk_60_p2.inc");

void VFX60_Init(struct VFX* vfx);
void VFX60_Update(struct VFX* vfx);
void VFX60_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX60Routine = {
    [ENTITY_INIT] =      VFX60_Init,
    [ENTITY_UPDATE] =    VFX60_Update,
    [ENTITY_DIE] =       VFX60_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void nop_080c2d44(struct VFX* vfx);
void FUN_080c2d48(struct VFX* vfx);

static const VFXFunc sUpdates[2] = {
    nop_080c2d44,
    FUN_080c2d48,
};

static const s32 s32_ARRAY_0836f3a4[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

const s32* const PTR_s32_ARRAY_0836f404[3] = {
    &s32_ARRAY_0836f3a4[0],
    &s32_ARRAY_0836f3a4[8],
    &s32_ARRAY_0836f3a4[16],
};
