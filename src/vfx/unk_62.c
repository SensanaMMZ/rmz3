#include "global.h"
#include "metatile.h"
#include "vfx.h"

static const motion_t sMotions[3];
static const VFXFunc sInitializers[1];
static const VFXFunc sUpdates[1];

void CreateVFX62(struct Entity* e, struct Coord* c) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_062);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 0;
      (p->s).work[1] = i;
      (p->s).unk_28 = e;
      (p->s).coord.x = c->x;
      (p->s).coord.y = c->y;
    }
  }
}

void VFX62_Init(struct VFX* vfx) {
  (sInitializers[(vfx->s).work[0]])(vfx);
}


void VFX62_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).work[0]])(vfx);
}


void VFX62_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

void FUN_080c3574(struct VFX* p) {
  u8 on;
  s32 w;
  on = (((p->s).unk_28)->flags >> 4) & 1;
  w = (p->s).work[1];
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  SET_XFLIP(p, on);
  if (w == 1) {
    SET_XFLIP(p, w);
  }
  SetMotion(&p->s, sMotions[w]);
  if (on != 0) {
    w = 2 - w;
  }
  (p->s).d.x = ((w - 1) << 7) + (RANDOM(RNG_0202f388) & 0x1FF) - 0x100;
  (p->s).d.y = -0x200 - (RANDOM(RNG_0202f388) & 0x1FF);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  VFX62_Update(p);
}

// 0x080c3678
void FUN_080c3678(struct VFX* p) {
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += PIXEL(1) / 4;
  UpdateMotionGraphic(&p->s);
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    CreateSmoke(3, &(p->s).coord);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

void VFX62_Init(struct VFX* vfx);
void VFX62_Update(struct VFX* vfx);
void VFX62_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX62Routine = {
    [ENTITY_INIT] =      VFX62_Init,
    [ENTITY_UPDATE] =    VFX62_Update,
    [ENTITY_DIE] =       VFX62_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3574(struct VFX* vfx);

static const VFXFunc sInitializers[1] = {
    FUN_080c3574,
};

void FUN_080c3678(struct VFX* vfx);

static const VFXFunc sUpdates[1] = {
    FUN_080c3678,
};

static const motion_t sMotions[3] = {
    MOTION(SM221_METTAUR, 16),
    MOTION(SM221_METTAUR, 16),
    MOTION(SM221_METTAUR, 17),
};
