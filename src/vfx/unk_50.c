#include "global.h"
#include "vfx.h"

// キュービットフォクスター の炎に関係

INCASM("asm/vfx/unk_50_pre.inc");

void VFX50_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_50_post.inc");

void VFX50_Init(struct VFX* vfx);
void VFX50_Update(struct VFX* vfx);
void VFX50_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX50Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX50_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX50_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX50_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c094c(struct VFX* vfx);
void FUN_080c09c8(struct VFX* vfx);

static const VFXFunc sUpdates[2] = {
    FUN_080c094c,
    FUN_080c09c8,
};

static const motion_t sMotions[3] = {
    MOTION(DM177_CUBIT_FLAME, 9),
    MOTION(DM177_CUBIT_FLAME, 10),
    MOTION(DM177_CUBIT_FLAME, 11),
};
