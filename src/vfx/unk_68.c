#include "entity.h"
#include "global.h"
#include "vfx.h"

// ファントム(ボス)関連?

void FUN_080c4d30(struct VFX* p);
void FUN_080c4db8(struct VFX* p);

const VFXFunc sGhost68Initializers[2] = {
    FUN_080c4d30,
    FUN_080c4db8,
};

void FUN_080c4d60(struct VFX* p);
void FUN_080c4de8(struct VFX* p);

const VFXFunc sGhost68Updates[2] = {
    FUN_080c4d60,
    FUN_080c4de8,
};

// --------------------------------------------

void Ghost68_Init(struct VFX* p);
void Ghost68_Update(struct VFX* p);
void Ghost68_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost68Routine = {
    [ENTITY_INIT] =      (VFXFunc)Ghost68_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Ghost68_Update,
    [ENTITY_DIE] =       (VFXFunc)Ghost68_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c4be0(s32 x, s32 y) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_068);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = 0;
    (p->coord).x = x, (p->coord).y = y;
  }
}

INCASM("asm/vfx/unk_68_pre_pre.inc");

void Ghost68_Init(struct VFX* p) {
  (sGhost68Initializers[(p->s).work[0]])(p);
  Ghost68_Update(p);
}

INCASM("asm/vfx/unk_68_pre_post.inc");

void Ghost68_Update(struct VFX* p) {
  (sGhost68Updates[(p->s).work[0]])(p);
}

void Ghost68_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  (p->s).flags &= ~FLIPABLE;
  SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
}

INCASM("asm/vfx/unk_68_post_p1.inc");

INCASM("asm/vfx/unk_68_post_p2_p1.inc");

void FUN_080c4d30(struct VFX* p) {
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
}

INCASM("asm/vfx/unk_68_post_p2_p2.inc");

void FUN_080c4db8(struct VFX* p) {
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
}

INCASM("asm/vfx/unk_68_post_p2_p3.inc");
