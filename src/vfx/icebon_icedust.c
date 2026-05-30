#include "entity.h"
#include "global.h"
#include "vfx.h"

// アイスボンの氷のキラキラ

static const u8 sInitModes[4];

void IcebonIcedust_Update(struct VFX* p);

void ice_080b996c(struct VFX* p);
void ice_080b9a0c(struct VFX* p);

static const VFXFunc sUpdates[2];

void createIcebonIce(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_026);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[0] = 0;
  }
}

void FUN_080b98ac(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_026);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[0] = 1;
  }
}

void IcebonIcedust_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  IcebonIcedust_Update(p);
}

void IcebonIcedust_Update(struct VFX* p) {
  (sUpdates[(p->s).mode[1]])(p);
}

void IcebonIcedust_Die(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/icebon_icedust_p3_a.inc");

void ice_080b9a0c(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x1109);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void IcebonIcedust_Init(struct VFX* p);

// clang-format off
const VFXRoutine gIcebonIcedustRoutine = {
    [ENTITY_INIT] =      IcebonIcedust_Init,
    [ENTITY_UPDATE] =    IcebonIcedust_Update,
    [ENTITY_DIE] =       IcebonIcedust_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void ice_080b996c(struct VFX* p);
void ice_080b9a0c(struct VFX* p);

static const VFXFunc sUpdates[2] = {
    ice_080b996c,
    ice_080b9a0c,
};

static const u8 sInitModes[4] = {0, 1, 0, 0};
