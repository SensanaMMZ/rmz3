#include "global.h"
#include "story.h"
#include "vfx.h"

void VFX38_Die(struct VFX* vfx);
extern const VFXFunc PTR_ARRAY_0836ee24[3];

INCASM("asm/vfx/unk_38_p1_pre_pre.inc");

void VFX38_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX38_Die(vfx);
  } else {
    (PTR_ARRAY_0836ee24[(vfx->s).mode[1]])(vfx);
  }
}

INCASM("asm/vfx/unk_38_p1_pre_post.inc");

void VFX38_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_38_p1_post.inc");

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
