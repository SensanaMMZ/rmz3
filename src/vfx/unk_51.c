#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[1];

void CreateVFX51(struct Entity* e, s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_051);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = e;
  }
}

INCASM("asm/vfx/unk_51_pre_pre_p2.inc");

void VFX51_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

INCASM("asm/vfx/unk_51_pre_post.inc");

void VFX51_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_51_post.inc");

void VFX51_Init(struct VFX* vfx);
void VFX51_Update(struct VFX* vfx);
void VFX51_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX51Routine = {
    [ENTITY_INIT] =      VFX51_Init,
    [ENTITY_UPDATE] =    VFX51_Update,
    [ENTITY_DIE] =       VFX51_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c0b68(struct VFX* vfx);

static const VFXFunc sUpdates[1] = {
    FUN_080c0b68,
};

static const u8 sInitModes[4] = {0, 0, 0, 0};
