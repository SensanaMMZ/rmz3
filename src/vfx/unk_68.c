#include "entity.h"
#include "global.h"
#include "trig.h"
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

struct Projectile* FUN_080afda4(struct VFX* p);

void FUN_080c4c2c(s32 x, s32 y, s32 speed, u8 angle) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_068);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = (COS(angle) * speed) / 0x100;
    (p->s).d.y = (SIN(angle) * speed) / 0x100;
    (p->s).unk_2c = (struct Entity*)FUN_080afda4(p);
  }
}

void Ghost68_Init(struct VFX* p) {
  (sGhost68Initializers[(p->s).work[0]])(p);
  Ghost68_Update(p);
}


void Ghost68_Update(struct VFX* p) {
  (sGhost68Updates[(p->s).work[0]])(p);
}

void Ghost68_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  (p->s).flags &= ~FLIPABLE;
  SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
}



void FUN_080c4d30(struct VFX* p) {
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
}

void FUN_080c4d60(struct VFX* p) {
  switch ((p->s).mode[1]) {
    case 0:
      SetMotion(&p->s, 0x8700);
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

void FUN_080c4db8(struct VFX* p) {
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
}

void FUN_080c4de8(struct VFX* p) {
  struct Entity* parent = (p->s).unk_2c;
  switch ((p->s).mode[1]) {
    case 0:
      SetMotion(&p->s, 0x8701);
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      parent->coord.x = (p->s).coord.x;
      parent->coord.y = (p->s).coord.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}
