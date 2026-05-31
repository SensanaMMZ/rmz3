#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[9];


void oz_080c39a0(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = 0;
  }
}

static const u8 sInitModes[7];
void Ghost64_Update(struct VFX* p);

void FUN_080c39e8(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = 1;
    {
      s32 ex = (e->coord).x;
      s32 x = (p->s).coord.x = ex + PIXEL(12);
      if ((e->flags & X_FLIP) != 0) {
        x = ex - PIXEL(12);
      }
      (p->s).coord.x = x;
    }
    (p->s).coord.y = (e->coord).y - PIXEL(32);
  }
}

void oz_Rekkoha_080c3a5c(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = 3;
    {
      s32 ex = (e->coord).x;
      s32 x = (p->s).coord.x = ex + PIXEL(12);
      if ((e->flags & X_FLIP) != 0) {
        x = ex - PIXEL(12);
      }
      (p->s).coord.x = x;
    }
    (p->s).coord.y = (e->coord).y - PIXEL(32);
  }
}

void ozMessenkou2(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    {
      s32 ex = (e->coord).x;
      s32 x = (p->s).coord.x = ex - PIXEL(5);
      if ((e->flags & X_FLIP) != 0) {
        x = ex + PIXEL(5);
      }
      (p->s).coord.x = x;
    }
    (p->s).coord.y = (e->coord).y + PIXEL(1);
  }
}

void oz_080c3b44(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = (e->coord).x;
    (p->s).coord.y = (e->coord).y - PIXEL(22);
  }
}

void oz_080c3b9c(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 5;
    (p->s).coord.x = (e->coord).x;
    (p->s).coord.y = (e->coord).y - PIXEL(22);
  }
}

void FUN_080c3bf4(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).coord.x = x, (p->s).coord.y = y;
  }
}

void Ghost64_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  Ghost64_Update(p);
}

void Ghost64_Update(struct VFX* p) {
  (sUpdates[(p->s).mode[1]])(p);
}


void Ghost64_Die(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_64_p3.inc");

void Ghost64_Init(struct VFX* p);

// clang-format off
const VFXRoutine gGhost64Routine = {
    [ENTITY_INIT] =      Ghost64_Init,
    [ENTITY_UPDATE] =    Ghost64_Update,
    [ENTITY_DIE] =       Ghost64_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3cbc(struct VFX* p);
void FUN_080c3d84(struct VFX* p);
void FUN_080c3e98(struct VFX* p);
void FUN_080c3f1c(struct VFX* p);
void FUN_080c3f74(struct VFX* p);
void FUN_080c3ffc(struct VFX* p);
void FUN_080c4074(struct VFX* p);
void FUN_080c40ec(struct VFX* p);
void FUN_080c4144(struct VFX* p);

// clang-format off
static const VFXFunc sUpdates[9] = {
    FUN_080c3cbc,
    FUN_080c3d84,
    FUN_080c3e98,
    FUN_080c3f1c,
    FUN_080c3f74,
    FUN_080c3ffc,
    FUN_080c4074,
    FUN_080c40ec,
    FUN_080c4144,
};
// clang-format on

static const u8 sInitModes[7] = {8, 2, 3, 4, 5, 6, 7};
