#include "global.h"
#include "story.h"
#include "vfx.h"

void VFX38_Die(struct VFX* vfx);
extern const VFXFunc PTR_ARRAY_0836ee24[3];

struct VFX* FUN_080bcf68(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_038);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk38Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080bcfbc(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_038);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk38Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk38Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void VFX38_Update(struct VFX* vfx);

void VFX38_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = -PIXEL(1) / 2;
  } else {
    (p->s).d.x = PIXEL(1) / 2;
  }
  (p->s).d.y = 0;

  if ((p->s).work[1] == 0) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else {
    RNG_0202f388 = LCG(RNG_0202f388);
    (p->s).work[2] = 127 + ((RNG_0202f388 >> 16) & 7);
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 2, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  }
  VFX38_Update(p);
}

void VFX38_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX38_Die(vfx);
  } else {
    (PTR_ARRAY_0836ee24[(vfx->s).mode[1]])(vfx);
  }
}


void VFX38_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}


void nop_080bd17c(struct VFX* vfx) {}

INCASM("asm/vfx/unk_38_p2.inc");

void VFX38_Init(struct VFX* vfx);
void VFX38_Update(struct VFX* vfx);
void VFX38_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX38Routine = {
    [ENTITY_INIT] =      VFX38_Init,
    [ENTITY_UPDATE] =    VFX38_Update,
    [ENTITY_DIE] =       VFX38_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void nop_080bd17c(struct VFX* vfx);
void FUN_080bd180(struct VFX* vfx);
void FUN_080bd288(struct VFX* vfx);

const VFXFunc PTR_ARRAY_0836ee24[3] = {
    nop_080bd17c,
    FUN_080bd180,
    FUN_080bd288,
};

static const u8 u8_ARRAY_0836ee30[32 * 3] = {
    0x20, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0xA0, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0xA0, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0xA0, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0xA0, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0xA0, 0xFE, 0xFF, 0xFF, 0x20, 0x01, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0xA0, 0xFE, 0xFF, 0xFF,
};

const u8* const PTR_ARRAY_0836ee90[3] = {
    &u8_ARRAY_0836ee30[0],
    &u8_ARRAY_0836ee30[32],
    &u8_ARRAY_0836ee30[64],
};
