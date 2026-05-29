#include "global.h"
#include "script.h"
#include "stagerun.h"
#include "story.h"
#include "vfx.h"

// MMBN4との通信で出現する敵に関係するエフェクト?

static void VFX44_Init(struct Entity* p);
void VFX44_Update(struct VFX* vfx);
void VFX44_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX44Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX44_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX44_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX44_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Entity* createGhost44(struct Coord* c, u8 kind) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_044);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = kind;
    p->work[1] = 0;
    (p->coord).x = c->x;
    (p->coord).y = c->y;
  }
  return p;
}

// --------------------------------------------

static void VFX44_Init(struct Entity* p) {
  InitNonAffineMotion(p);
  p->flags |= DISPLAY;
  p->flags |= FLIPABLE;
  if (p->work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  (p->d).y = 0;
  p->work[2] = 0xFF;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  p->mode[1] = 0;
  p->mode[2] = 0;
  p->mode[3] = 0;
  VFX44_Update((void*)p);
}

void FUN_080be974(struct Entity* p);

static const EntityFunc sUpdates[1] = {
    FUN_080be974,
};

void VFX44_Update(struct VFX* p) {
  if ((gCurStory.s.gameflags[4] & 0x40) || gStageRun.vm.entities[1].entity != NULL) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    sUpdates[(p->s).mode[1]](&p->s);
  }
}

void VFX44_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_44_post.inc");
