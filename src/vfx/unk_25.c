#include "boss.h"
#include "global.h"
#include "vfx.h"

struct VFX25 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  struct Coord c;  // 0x74
  u8 unk_7c[4];
  u16 unk_80;
  u16 unk_82;
};
static_assert(sizeof(struct VFX25) == sizeof(struct VFX));

static void VFX25_Init(struct VFX25* vfx);
static void VFX25_Update(struct VFX* vfx);
static void VFX25_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX25Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX25_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX25_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX25_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct Entity* FUN_080b9184(struct Coord* c, u8 n) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_025);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = n;
    (p->coord).x = c->x, (p->coord).y = c->y;
  }
  return p;
}

struct Entity* omegaWhite_080b91d4(struct Coord* c, u8 n, struct Entity* omega) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_025);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = n;
    (p->coord).x = c->x, (p->coord).y = c->y;
    p->unk_28 = (void*)omega;
  }
  return p;
}

struct Entity* FUN_080b9228(struct Coord* c) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_025);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = 4;
    (p->coord).x = c->x, (p->coord).y = c->y;
  }
  return p;
}

// --------------------------------------------

static void VFX25_Init(struct VFX25* p) {
  if ((p->s).work[0] == 0) {
    InitNonAffineMotion(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    (p->s).work[2] = 8;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;

  } else if ((p->s).work[0] == 1) {
    InitNonAffineMotion(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    (p->s).work[2] = 8;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;

  } else if ((p->s).work[0] == 2) {
    InitNonAffineMotion(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    (p->c).x = 0, (p->c).y = 0;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 2, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
    (p->s).taskCol = 24;

  } else if ((p->s).work[0] == 3) {
    InitNonAffineMotion(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    (p->c).x = 0, (p->c).y = 0;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 3, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
    (p->s).taskCol = 24;
    (p->s).work[2] = 160;

  } else if ((p->s).work[0] == 4) {
    struct VFX25* q;

    (p->s).work[2] = 60;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 4, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
    q = (struct VFX25*)AllocEntityFirst(gVFXHeaderPtr);
    if (q != NULL) {
      (q->s).taskCol = 1;
      INIT_VFX_ROUTINE(q, VFX_UNK_025);
      (q->s).tileNum = 0, (q->s).palID = 0;
      (q->s).work[0] = 5;
      (q->s).coord = (p->s).coord;
      (q->s).d.x = 0;
      q->unk_80 = 0xe000;
      (q->s).d.y = 0xC0;
    }

  } else if ((p->s).work[0] == 5) {
    InitScalerotMotion1(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    RNG_0202f388 = LCG(RNG_0202f388);
    (p->s).work[2] = ((RNG_0202f388 >> 16) & 0x7) + 60;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 5, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  }

  VFX25_Update((void*)p);
}

// --------------------------------------------

static void FUN_080b9494(struct Entity* p);
void FUN_080b94dc(struct VFX* vfx);
void FUN_080b9530(struct VFX* vfx);
void FUN_080b963c(struct VFX* vfx);
void FUN_080b970c(struct VFX* vfx);
void FUN_080b9738(struct VFX* vfx);
void FUN_080b97f4(struct VFX* vfx);

static void VFX25_Update(struct VFX* vfx) {
  // clang-format off
  static const VFXFunc sUpdates[7] = {
      (VFXFunc)FUN_080b9494,
      (VFXFunc)FUN_080b94dc,
      (VFXFunc)FUN_080b9530,
      (VFXFunc)FUN_080b963c,
      (VFXFunc)FUN_080b970c,
      (VFXFunc)FUN_080b9738,
      (VFXFunc)FUN_080b97f4,
  };
  // clang-format on
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

// --------------------------------------------

static void VFX25_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

// --------------------------------------------

// 0x080b9494
static void FUN_080b9494(struct Entity* p) {
  p->work[2]--;
  if (p->work[2] == 0) {
    p->work[2] = 8, p->mode[1] = 1, p->mode[2] = 0;
    return;
  }

  switch (p->mode[2]) {
    case 0: {
      SetMotion(p, MOTION(SM010_OMEGA_RING, 8));
      p->mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(p);
      break;
    }
  }
}

INCASM("asm/vfx/unk_25_p1.inc");

void FUN_080b970c(struct VFX* p) {
  if (--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/vfx/unk_25_p2_a.inc");

void FUN_080b97f4(struct VFX* vfx) {
  switch ((vfx->s).mode[2]) {
    case 0:
      SetMotion(&vfx->s, 0xe000);
      (vfx->s).work[2] = 0x28;
      (vfx->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&vfx->s);
      if ((vfx->s).work[2] & 1) {
        (vfx->s).flags |= DISPLAY;
      } else {
        (vfx->s).flags &= ~DISPLAY;
      }
      if ((vfx->s).work[2] != 0 && --(vfx->s).work[2] == 0) {
        SET_VFX_ROUTINE(vfx, ENTITY_DIE);
      }
      break;
  }
}
