#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[];
void Ghost22_Die(struct VFX* p);

struct VFX* FUN_080b7b38(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_022);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk22Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080b7b8c(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_022);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk22Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk22Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

INCASM("asm/vfx/unk_22_p1_pre_pre_p2_p2.inc");

void Ghost22_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost22_Die(p);
  } else {
    (sUpdates[(p->s).mode[1]])(p);
  }
}


void Ghost22_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}


void nop_080b7d48(struct VFX* p) {}

INCASM("asm/vfx/unk_22_p2.inc");

static const VFXFunc sUpdates[3];

void Ghost22_Init(struct VFX* p);
void Ghost22_Update(struct VFX* p);
void Ghost22_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost22Routine = {
    [ENTITY_INIT] =      Ghost22_Init,
    [ENTITY_UPDATE] =    Ghost22_Update,
    [ENTITY_DIE] =       Ghost22_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void nop_080b7d48(struct VFX* p);
void FUN_080b7d4c(struct VFX* p);
void FUN_080b7e3c(struct VFX* p);

static const VFXFunc sUpdates[3] = {
    nop_080b7d48,
    FUN_080b7d4c,
    FUN_080b7e3c,
};

const s32 s32_ARRAY_0836e9f0[24] = {
    0x00000120,  -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120,  -0x00000160,  // 0
    -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120,  -0x00000160, 0x00000120,  -0x00000200,  // 1
    -0x000000B0, -0x00000200, 0x00000120,  -0x00000160, 0x00000120,  -0x00000200, -0x000000B0, -0x00000160,  // 2
};

const s32* const PTR_ARRAY_0836ea50[3] = {
    &s32_ARRAY_0836e9f0[0],
    &s32_ARRAY_0836e9f0[8],
    &s32_ARRAY_0836e9f0[16],
};
