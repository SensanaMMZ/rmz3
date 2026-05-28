#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sInitializers[2];
static const VFXFunc sUpdates[2];

void Ghost73_Init(struct VFX* p);
void Ghost73_Update(struct VFX* p);
void Ghost73_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost73Routine = {
    [ENTITY_INIT] =      Ghost73_Init,
    [ENTITY_UPDATE] =    Ghost73_Update,
    [ENTITY_DIE] =       Ghost73_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c6e24(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_073);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

INCASM("asm/vfx/unk_73_pre.inc");

void Ghost73_Init(struct VFX* p) {
  (sInitializers[(p->s).work[0]])(p);
}

INCASM("asm/vfx/unk_73_post_pre_p1.inc");

void Ghost73_Update(struct VFX* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(p->s).work[0]])(p);
}

INCASM("asm/vfx/unk_73_post_pre_p2.inc");

void Ghost73_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_73_post_post.inc");

// --------------------------------------------

void FUN_080c6f60(struct VFX* p);
void FUN_080c7120(struct VFX* p);

static const VFXFunc sInitializers[2] = {
    FUN_080c6f60,
    FUN_080c7120,
};

// --------------------------------------------

void FUN_080c705c(struct VFX* p);
void FUN_080c7250(struct VFX* p);

static const VFXFunc sUpdates[2] = {
    FUN_080c705c,
    FUN_080c7250,
};

// --------------------------------------------

const motion_t motion_t_ARRAY_0836f884[3] = {
    MOTION(SM220_CANNON_HOPPER, 8),
    MOTION(SM220_CANNON_HOPPER, 8),
    MOTION(SM220_CANNON_HOPPER, 9),
};
