#include "global.h"
#include "story.h"
#include "vfx.h"

struct VFX21 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  u16 unk_0;
  u16 unk_2;
  s32 unk_4;
  u8 unk_8[8];
};
static_assert(sizeof(struct VFX21) == sizeof(struct VFX));

static const s32* const PTR_s32_ARRAY_0836e9c4[3];

static void BatringNecro_Init(struct VFX* vfx);
static void BatringNecro_Update(struct VFX* vfx);
static void Ghost21_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gBatringNecroRoutine = {
    [ENTITY_INIT] =      BatringNecro_Init,
    [ENTITY_UPDATE] =    BatringNecro_Update,
    [ENTITY_DIE] =       Ghost21_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080b7680(struct Coord* c, u8 param_2) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_BATRING_NECRO);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = param_2;
    (vfx->s).work[1] = 0;
    (vfx->s).coord.x = c->x;
    (vfx->s).coord.y = c->y;
  }
  return vfx;
}

struct Entity* FUN_080b76d4(struct Coord* c, u8 r1, u16 r2, s32 r3) {
  struct VFX21* p = (struct VFX21*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_BATRING_NECRO);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = r1, (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    p->unk_0 = r2;
    p->unk_4 = r3;
  }
  return (struct Entity*)p;
}

// --------------------------------------------

static void BatringNecro_Init(struct VFX* vfx) {
  InitNonAffineMotion(&vfx->s);
  (vfx->s).flags |= DISPLAY;
  (vfx->s).flags |= FLIPABLE;
  (vfx->s).work[2] = 0xFF;
  if ((vfx->s).work[0] == 0) {
    SET_XFLIP(vfx, FALSE);
    (vfx->s).d.x = PIXEL(3) / 8;
  } else {
    SET_XFLIP(vfx, TRUE);
    (vfx->s).d.x = -PIXEL(3) / 8;
  }
  (vfx->s).d.y = 0;

  if ((vfx->s).work[1] == 0) {
    (vfx->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
    (vfx->s).mode[1] = 1, (vfx->s).mode[2] = 0, (vfx->s).mode[3] = 0;
  } else {
    RNG_0202f388 = LCG(RNG_0202f388);
    (vfx->s).work[2] = 127 + ((RNG_0202f388 >> 16) & 7);
    SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
    (vfx->s).mode[1] = 2, (vfx->s).mode[2] = 0, (vfx->s).mode[3] = 0;
  }
  BatringNecro_Update(vfx);
}

// --------------------------------------------

static void nop_080b788c(struct VFX* vfx);
void FUN_080b7890(struct VFX* vfx);
void FUN_080b7a04(struct VFX* vfx);

static void BatringNecro_Update(struct VFX* vfx) {
  static const VFXFunc sUpdates[3] = {
      nop_080b788c,
      FUN_080b7890,
      FUN_080b7a04,
  };
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    Ghost21_Die(vfx);
    return;
  }
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

// --------------------------------------------

static void Ghost21_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

// --------------------------------------------

static void nop_080b788c(struct VFX* vfx) {
  // nop
  return;
}

INCASM("asm/vfx/unk_21.inc");

// --------------------------------------------

static const s32 s32_ARRAY_0836e964[8 * 3] = {
    0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160,
};

static const s32* const PTR_s32_ARRAY_0836e9c4[3] = {
    &s32_ARRAY_0836e964[0],
    &s32_ARRAY_0836e964[8],
    &s32_ARRAY_0836e964[16],
};
