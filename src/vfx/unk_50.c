#include "global.h"
#include "vfx.h"

// キュービットフォクスター の炎に関係

static const VFXFunc sUpdates[2];

struct VFX* FUN_080c078c(struct Entity* e, struct Coord* c, u8 arg2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_050);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = arg2;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Unk50Props { u8 unk_0[8]; u8 unk_8; };

struct VFX* FUN_080c07e4(struct Coord* c1, struct Coord* c2, u8 a2, u8 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_050);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    ((struct Unk50Props*)(p->props).raw)->unk_8 = a3;
    (p->s).work[1] = 1;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

INCASM("asm/vfx/unk_50_pre_pre_p2_p2.inc");

void VFX50_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

void VFX50_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_50_post.inc");

void VFX50_Init(struct VFX* vfx);
void VFX50_Update(struct VFX* vfx);
void VFX50_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX50Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX50_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX50_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX50_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c094c(struct VFX* vfx);
void FUN_080c09c8(struct VFX* vfx);

static const VFXFunc sUpdates[2] = {
    FUN_080c094c,
    FUN_080c09c8,
};

static const motion_t sMotions[3] = {
    MOTION(DM177_CUBIT_FLAME, 9),
    MOTION(DM177_CUBIT_FLAME, 10),
    MOTION(DM177_CUBIT_FLAME, 11),
};
