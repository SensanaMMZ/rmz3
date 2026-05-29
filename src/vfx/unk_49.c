#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[4];
static const u8 sInitModes[4];

void VFX49_Update(struct VFX* vfx);

void FUN_080c025c(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

void createLaserSign(struct Entity* e, s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = e;
  }
}

void FUN_080c02f4(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}


void FUN_080c0340(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_049);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).unk_28 = e;
  }
}

void VFX49_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  VFX49_Update(p);
}

void VFX49_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}


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
