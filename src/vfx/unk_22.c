#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[];
void Ghost22_Die(struct VFX* p);

INCASM("asm/vfx/unk_22_p1_pre_pre.inc");

void Ghost22_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost22_Die(p);
  } else {
    (sUpdates[(p->s).mode[1]])(p);
  }
}

INCASM("asm/vfx/unk_22_p1_pre_post.inc");

void Ghost22_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_22_p1_post.inc");

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
