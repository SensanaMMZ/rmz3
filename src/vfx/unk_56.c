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

// One instruction from a match: retail materializes the shared zero before
// the flags RMW where agbcc places it after (scheduling tie). Everything
// else reproduces via the oam.xflip bitfield insert and paired coord loads.
// diffs left, dominated by the ip-parking arg-copy basin.
// (arg-copy basin, same class as FadeBlack).
NON_MATCH void FUN_080c15d4(struct VFX* vfx) {
#if MODERN
  struct Entity* q = (vfx->s).unk_28;
  (vfx->s).flags &= ~X_FLIP;
  ((vfx->s).spr).xflip = 0;
  ((vfx->s).spr).oam.xflip = 0;
  (vfx->s).taskCol = 9;
  {
    s32 x = q->coord.x;
    s32 y = q->coord.y;
    (vfx->s).coord.x = x;
    (vfx->s).coord.y = y;
  }
  (vfx->s).work[2] = 0;
  VFX56_Update(&vfx->s);
#else
  INCCODE("asm/vfx/unk_56_c15d4.inc");
#endif
}

extern const s16 gSineTable[256];
// 0x080C161C
void FUN_080c161c(struct VFX* p) {
  struct Entity* q = (p->s).unk_28;
  s32 z = 0;
  s32 spd;
  s32 dx;
  s32 dy;
  (p->s).flags &= ~X_FLIP;
  ((p->s).spr).xflip = z;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    *oa = m11;
  }
  (p->s).coord = q->coord;
  (p->s).work[3] = RANDOM(RNG_0202f388) % 3 + 3;
  (p->s).work[2] = z;
  spd = (RANDOM(RNG_0202f388) & 0xFF) + 0x100;
  dx = (spd * gSineTable[(u8)((p->s).work[1] + 0x40)]) >> 8;
  (p->s).d.x = dx;
  {
    register s32 sv asm("r1");
    register s32 t5 asm("r5");
    sv = gSineTable[(p->s).work[1]];
    asm volatile("add %0, %1, #0" : "=&l"(t5) : "l"(spd));
    t5 *= sv;
    dy = t5 >> 8;
  }
  (p->s).d.y = dy;
  (p->s).unk_coord.x = dx / ((p->s).work[3] * 7);
  (p->s).unk_coord.y = dy / ((p->s).work[3] * 7);
  VFX56_Update(&p->s);
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
