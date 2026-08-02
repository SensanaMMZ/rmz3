#include "global.h"
#include "metatile.h"
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

#include "motion.h"
#include "zero.h"

void FUN_080bba18(struct VFX* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    switch ((p->s).mode[2]) {
      case 0:
        SetMotion(&p->s, MOTION(0x28, 0x0d));
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        (p->s).coord.x = (pZero2->s).coord.x;
        (p->s).coord.y = (pZero2->s).coord.y - 0x1000;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

INCASM("asm/vfx/unk_33_post_b.inc");

// 0x080BBB30
void FUN_080bbb30(struct VFX* p) {
  struct Entity* q = (p->s).unk_28;
  if (q->mode[0] <= 1) {
    s32 x;
    s32 y;
    u8 a;
    switch ((p->s).mode[2]) {
      case 0:
        SetMotion(&p->s, MOTION(0x28, 0x04));
        (p->s).mode[2]++;
      case 1:
        x = q->coord.x;
        (p->s).coord.x = x;
        y = q->coord.y;
        (p->s).coord.y = y;
        a = *(u8*)((u8*)q + 0x24);
        (p->s).coord.x = x + gSineTable[(u8)(a + 0xC0)] * 10;
        (p->s).coord.y = y + gSineTable[(u8)(a + 0x80)] * 10;
        UpdateMotionGraphic(&p->s);
        if (*(u8*)((u8*)p + 0x73) != 4) {
          return;
        }
        break;
      default:
        return;
    }
  }
  {
    u8 fl = (p->s).flags & 0xFE;
    fl &= 0xFD;
    (p->s).flags = fl;
  }
  SET_VFX_ROUTINE(p, 3);
}

void FUN_080bbbd4(struct VFX* vfx);
static const motion_t sMotions[3];

void FUN_080bbbd4(struct VFX* vfx) {
  s32 md = (vfx->s).mode[2];
  switch (md) {
    case 0: {
      s32 k4;
      InitRotatableMotion(&vfx->s);
      (vfx->s).angle = RANDOM(RNG_0202f388);
      k4 = (vfx->s).work[1];
      SetMotion(&vfx->s, sMotions[k4]);
      (vfx->s).d.x = ((k4 - 1) << 8) + (RANDOM(RNG_0202f388) & 0x1FF) - 0x100;
      (vfx->s).d.y = -0x200 - (RANDOM(RNG_0202f388) & 0x1FF);
      (vfx->s).work[2] = md;
      (vfx->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      s32 t = (vfx->s).work[2] + 1;
      (vfx->s).work[2] = t;
      if (t & 1) {
        (vfx->s).flags |= DISPLAY;
      } else {
        (vfx->s).flags &= ~DISPLAY;
      }
      (vfx->s).coord.x += (vfx->s).d.x;
      (vfx->s).coord.y += (vfx->s).d.y;
      (vfx->s).d.y += 0x40;
      UpdateMotionGraphic(&vfx->s);
      if (FUN_080098a4((vfx->s).coord.x, (vfx->s).coord.y) != 0 && (vfx->s).d.y > 0) {
        CreateSmoke(3, &(vfx->s).coord);
        SET_VFX_ROUTINE(vfx, ENTITY_DIE);
      }
      break;
    }
  }
}

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
