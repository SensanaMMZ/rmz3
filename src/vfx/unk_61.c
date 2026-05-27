#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[3];
void VFX61_Die(struct VFX* p);

INCASM("asm/vfx/unk_61_pre_pre.inc");

void VFX61_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX61_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}

INCASM("asm/vfx/unk_61_pre_post.inc");

void VFX61_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_61_post.inc");

void VFX61_Init(struct VFX* vfx);
void VFX61_Update(struct VFX* vfx);
void VFX61_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX61Routine = {
    [ENTITY_INIT] =      VFX61_Init,
    [ENTITY_UPDATE] =    VFX61_Update,
    [ENTITY_DIE] =       VFX61_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3108(struct VFX* vfx);
void FUN_080c3214(struct VFX* vfx);
void FUN_080c338c(struct VFX* vfx);

static const VFXFunc sUpdates[3] = {
    FUN_080c3108,
    FUN_080c3214,
    FUN_080c338c,
};

static const s32 s32_ARRAY_0836f430[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

static const s32* const PTR_s32_ARRAY_0836f490[3] = {
    &s32_ARRAY_0836f430[0],
    &s32_ARRAY_0836f430[8],
    &s32_ARRAY_0836f430[16],
};
