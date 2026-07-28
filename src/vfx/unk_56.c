#include "global.h"
#include "vfx.h"

static void VFX56_Init(struct Entity* p);
static void VFX56_Update(struct Entity* p);
static void VFX56_Die(struct Entity* p);

// clang-format off
const VFXRoutine gVFX56Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX56_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX56_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX56_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void CreateVFX56(struct Entity* e, u8 kind1, u8 kind2) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_056);
    p->tileNum = 0, p->palID = 0;
    p->unk_28 = (void*)e;
    p->work[0] = kind1;
    p->work[1] = kind2;
  }
}

// --------------------------------------------

void FUN_080c15d4(struct VFX* vfx);
void FUN_080c161c(struct VFX* vfx);
void FUN_080c16fc(struct VFX* vfx);

static void VFX56_Init(struct Entity* p) {
  static const VFXFunc sInitializers[3] = {
      (VFXFunc)FUN_080c15d4,
      (VFXFunc)FUN_080c161c,
      (VFXFunc)FUN_080c16fc,
  };  // 0x0836f22c

  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(p);
  p->flags |= DISPLAY;
  p->flags |= FLIPABLE;
  SetMotion(p, MOTION(SM096_COPYX_REFLECT_LASER, 1));
  (sInitializers[p->work[0]])((void*)p);
}

void FUN_080c17e8(struct Entity* p);
void FUN_080c182c(struct Entity* p);
void FUN_080c188c(struct Entity* p);

static void VFX56_Update(struct Entity* p) {
  static const VFXFunc sUpdates[3] = {
      (VFXFunc)FUN_080c17e8,
      (VFXFunc)FUN_080c182c,
      (VFXFunc)FUN_080c188c,
  };  // 0x0836f238
  (sUpdates[p->work[0]])((void*)p);
}

static void VFX56_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

// 1 insn over: retail parks the entity pointer in ip for the whole body
// (arg-copy basin, same class as FadeBlack).
NON_MATCH void FUN_080c15d4(struct VFX* vfx) {
#if MODERN
  struct Entity* q = (vfx->s).unk_28;
  (vfx->s).flags &= ~X_FLIP;
  ((vfx->s).spr).spriteIdx = 0;
  ((vfx->s).spr).xflip &= ~0x11;
  (vfx->s).taskCol = 9;
  (vfx->s).coord.x = q->coord.x;
  (vfx->s).coord.y = q->coord.y;
  (vfx->s).work[2] = 0;
  VFX56_Update(&vfx->s);
#else
  INCCODE("asm/vfx/unk_56_c15d4.inc");
#endif
}

INCASM("asm/vfx/unk_56.inc");

// 0x080c17e8
void FUN_080c17e8(struct Entity* p) {
  if (p->work[2] == 0) {
    UpdateMotionGraphic(p);
    p->work[2] = 3;
  } else {
    p->work[2]--;
  }
  if ((p->motion).state == 3) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    VFX56_Die(p);
  }
}

void FUN_080c182c(struct Entity* p) {
  u32 c = p->work[2];
  if (c == 0) {
    UpdateMotionGraphic(p);
    c = p->work[3];
  } else {
    c--;
  }
  p->work[2] = c;
  (p->coord).x += (p->d).x;
  (p->coord).y += (p->d).y;
  (p->d).x -= (p->unk_coord).x;
  (p->d).y -= (p->unk_coord).y;
  if ((p->motion).state == 3) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    VFX56_Die(p);
  }
}

void FUN_080c188c(struct Entity* p) {
  u32 c = p->work[2];
  if (c == 0) {
    UpdateMotionGraphic(p);
    c = p->work[3];
  } else {
    c--;
  }
  p->work[2] = c;
  (p->coord).x += (p->d).x;
  (p->coord).y += (p->d).y;
  (p->d).x -= (p->unk_coord).x;
  (p->d).y -= (p->unk_coord).y;
  if ((p->motion).state == 3) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    VFX56_Die(p);
  }
}
