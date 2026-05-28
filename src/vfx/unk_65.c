#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[1];

void CreateGhost65(s32 x, s32 y, u8 w1, u8 w2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_065);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = w1;
    (p->s).work[2] = w2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

INCASM("asm/vfx/unk_65_p1_p2.inc");

void Ghost65_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

INCASM("asm/vfx/unk_65_p2.inc");

void Ghost65_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_65_p3.inc");

void Ghost65_Init(struct VFX* vfx);

// clang-format off
const VFXRoutine gGhost65Routine = {
    [ENTITY_INIT] =      Ghost65_Init,
    [ENTITY_UPDATE] =    Ghost65_Update,
    [ENTITY_DIE] =       Ghost65_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c4320(struct VFX* vfx);

static const VFXFunc sUpdates[1] = {
    FUN_080c4320,
};

const u8 u8_ARRAY_0836f59c[2] = {0, 0};

// clang-format off
static const motion_t sMotions[6] = {
  MOTION(SM116_DEATHLOCK, 0x09),
  MOTION(SM116_DEATHLOCK, 0x0A),
  MOTION(SM116_DEATHLOCK, 0x0B),
  MOTION(SM116_DEATHLOCK, 0x0C),
  MOTION(SM116_DEATHLOCK, 0x0D),
  MOTION(SM116_DEATHLOCK, 0x08),
};
// clang-format on
