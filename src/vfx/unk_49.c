#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[4];

INCASM("asm/vfx/unk_49_pre_pre.inc");

void VFX49_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

INCASM("asm/vfx/unk_49_pre_post.inc");

void VFX49_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_49_post.inc");

void VFX49_Init(struct VFX* vfx);
void VFX49_Update(struct VFX* vfx);
void VFX49_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX49Routine = {
    [ENTITY_INIT] =      VFX49_Init,
    [ENTITY_UPDATE] =    VFX49_Update,
    [ENTITY_DIE] =       VFX49_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c0400(struct VFX* vfx);
void FUN_080c04d4(struct VFX* vfx);
void FUN_080c05a8(struct VFX* vfx);
void FUN_080c065c(struct VFX* vfx);

static const VFXFunc sUpdates[4] = {
    FUN_080c0400,
    FUN_080c04d4,
    FUN_080c05a8,
    FUN_080c065c,
};

static const u8 sInitModes[4] = {0, 1, 2, 3};
