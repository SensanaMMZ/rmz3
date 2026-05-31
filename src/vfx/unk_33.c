#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[4];
static const u8 sInitModes[4];

void Ghost33_Update(struct VFX* p);

struct Entity* FUN_080bb830(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_033);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = 0;
    p->unk_28 = (void*)e;
  }
}

struct Entity* FUN_080bb878(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_033);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = 1;
    p->unk_28 = (void*)e;
  }
}

struct Entity* FUN_080bb8c0(struct Entity* e) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_033);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = 2;
    p->unk_28 = (void*)e;
  }
}

void FUN_080bb908(s32 x, s32 y) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      p->taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_033);
      p->tileNum = 0, p->palID = 0;
      p->work[0] = 3, p->work[1] = i;
      p->coord.x = x, p->coord.y = y;
    }
  }
}

void Ghost33_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  Ghost33_Update(p);
}

void Ghost33_Update(struct VFX* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
}


void Ghost33_Die(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_33_post.inc");

void Ghost33_Init(struct VFX* p);
void Ghost33_Update(struct VFX* p);
void Ghost33_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost33Routine = {
    [ENTITY_INIT] =      Ghost33_Init,
    [ENTITY_UPDATE] =    Ghost33_Update,
    [ENTITY_DIE] =       Ghost33_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080bba18(struct VFX* p);
void FUN_080bba8c(struct VFX* p);
void FUN_080bbb30(struct VFX* p);
void FUN_080bbbd4(struct VFX* p);

static const VFXFunc sUpdates[4] = {
    FUN_080bba18,
    FUN_080bba8c,
    FUN_080bbb30,
    FUN_080bbbd4,
};

static const u8 sInitModes[4] = {0, 1, 2, 3};

static const motion_t sMotions[3] = {
    MOTION(SM040_SNAKECORD, 0x01),
    MOTION(SM040_SNAKECORD, 0x00),
    MOTION(SM040_SNAKECORD, 0x00),
};
