#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

void Ghost66_Init(struct VFX* p);
void Ghost66_Update(struct VFX* p);
void Ghost66_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost66Routine = {
    [ENTITY_INIT] =      Ghost66_Init,
    [ENTITY_UPDATE] =    Ghost66_Update,
    [ENTITY_DIE] =       Ghost66_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c4450(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_066);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

static const VFXFunc sUpdates[3];
void Ghost66_Die(struct VFX* p);

struct Unk66Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080c44a8(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_066);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk66Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk66Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void Ghost66_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = -PIXEL(3) / 4;
  } else {
    (p->s).d.x = PIXEL(3) / 4;
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
  Ghost66_Update(p);
}

void Ghost66_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost66_Die(p);
  } else {
    (sUpdates[(p->s).mode[1]])(p);
  }
}


void Ghost66_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}


void nop_080c4668(struct VFX* p) {}

INCASM("asm/vfx/unk_66_p2.inc");

// --------------------------------------------

void nop_080c4668(struct VFX* p);
void FUN_080c466c(struct VFX* p);
void FUN_080c47e0(struct VFX* p);

static const VFXFunc sUpdates[3] = {
    nop_080c4668,
    FUN_080c466c,
    FUN_080c47e0,
};

const s32 s32_ARRAY_0836f5cc[24] = {
    0x00000120, 0x00000260, -0x000000B0, 0x000001A0, -0x000000B0, 0x00000260, 0x00000120, 0x000001A0, -0x000000B0, 0x000001A0, -0x000000B0, 0x00000260, 0x00000120, 0x000001A0, 0x00000120, 0x00000260, -0x000000B0, 0x00000260, 0x00000120, 0x000001A0, 0x00000120, 0x00000260, -0x000000B0, 0x000001A0,
};

const s32* const PTR_ARRAY_0836f62c[3] = {
    &s32_ARRAY_0836f5cc[0],
    &s32_ARRAY_0836f5cc[8],
    &s32_ARRAY_0836f5cc[16],
};
