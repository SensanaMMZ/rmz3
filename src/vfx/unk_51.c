#include "global.h"
#include "metatile.h"
#include "motion.h"
#include "definition.h"
#include "vfx.h"

static const VFXFunc sUpdates[1];
static const u8 sInitModes[4];

void VFX51_Update(struct VFX* vfx);

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

void VFX51_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  VFX51_Update(p);
}

void VFX51_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}


void VFX51_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

void FUN_080c0b68(struct VFX* v) {
  s32 n;

  switch ((v->s).mode[2]) {
    case 0:
      RNG_0202f388 = LCG(RNG_0202f388);
      (v->s).d.x = ((RNG_0202f388 >> 16) & 0x3FF) - 0x200;
      RNG_0202f388 = LCG(RNG_0202f388);
      (v->s).d.y = -((RNG_0202f388 >> 16) & 0x1FF);
      RNG_0202f388 = LCG(RNG_0202f388);
      SetMotion(&v->s, MOTION(0x54, 0x0b) + ((RNG_0202f388 >> 16) & 1));
      (v->s).work[2] = 0;
      (v->s).mode[2]++;
      // fallthrough
    case 1:
      n = (v->s).work[2] + 1;
      (v->s).work[2] = n;
      if (n & 1) {
        (v->s).flags |= DISPLAY;
      } else {
        (v->s).flags &= ~DISPLAY;
      }
      (v->s).coord.x += (v->s).d.x;
      (v->s).d.y += 0x40;
      if ((v->s).d.y > 0x700) {
        (v->s).d.y = 0x700;
      }
      (v->s).coord.y += (v->s).d.y;
      UpdateMotionGraphic(&v->s);
      if (FUN_080098a4((v->s).coord.x, (v->s).coord.y) != 0) {
        CreateSmoke(3, &(v->s).coord);
        (v->s).flags &= ~DISPLAY;
        (v->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(v, ENTITY_DISAPPEAR);
      }
      break;
  }
}

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
