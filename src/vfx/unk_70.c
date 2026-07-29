#include "entity.h"
#include "global.h"
#include "vfx.h"

static void Ghost70_Init(struct VFX* p);
void Ghost70_Update(struct VFX* p);
void Ghost70_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost70Routine = {
    [ENTITY_INIT] =      Ghost70_Init,
    [ENTITY_UPDATE] =    Ghost70_Update,
    [ENTITY_DIE] =       Ghost70_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c5628(u8 r0, u8 r1, s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_070);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = r0;
    (p->s).work[1] = r1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = 0;
    (p->s).d.y = 0;
  }
  return p;
}

struct VFX* FUN_080c5684(u8 r0, u8 r1, s32 x, s32 y, s32 dx, s32 dy) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_070);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = r0;
    (p->s).work[1] = r1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = dx;
    (p->s).d.y = dy;
  }
  return p;
}

// --------------------------------------------

void FUN_080c572c(struct VFX* p);

static void Ghost70_Init(struct VFX* p) {
  // clang-format off
  static VFXFunc const sInitializers[] = {
      FUN_080c572c,
      FUN_080c572c,
      FUN_080c572c,
      FUN_080c572c,
      FUN_080c572c,
      FUN_080c572c,
  };
  // clang-format on
  (sInitializers[(p->s).work[0]])(p);
}

extern const VFXFunc sGhost70Updates[6];
extern const VFXFunc sGhost70Deinitializers[6];


void Ghost70_Update(struct VFX* p) {
  (sGhost70Updates[(p->s).work[0]])(p);
}


void Ghost70_Die(struct VFX* p) {
  (sGhost70Deinitializers[(p->s).work[0]])(p);
}

void FUN_080c572c(struct VFX* p) {
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost70_Update(p);
}

void FUN_080c5764(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_DIE);
  Ghost70_Die(p);
}


void FUN_080c5784(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_70_p3_p3.inc");

void FUN_080c5c64(struct VFX* vfx) {
  s32 md = (vfx->s).mode[1];
  switch (md) {
    case 0:
      SetMotion(&vfx->s, (RANDOM(RNG_0202f388) & 3) | MOTION(0x51, 0x02));
      (vfx->s).taskCol = 0x13;
      {
        s32 dx = (RANDOM(RNG_0202f388) % 0x1400) - 0xA00;
        (vfx->s).coord.x += dx;
      }
      (vfx->s).d.y = md;
      (vfx->s).work[2] = 0x50;
      (vfx->s).mode[1]++;
      // fallthrough
    case 1: {
      s32 t;
      s32 f;
      register s32 z asm("r2");
      s32 v = (vfx->s).d.y + 4;
      (vfx->s).d.y = v;
      (vfx->s).coord.y += v;
      t = (vfx->s).work[2] - 1;
      z = 0;
      (vfx->s).work[2] = t;
      asm volatile("" : "+r"(z));
      if ((u8)t <= 9) {
        if (t & 1) {
          register s32 fa asm("r0");
          register s32 c1 asm("r1");
          fa = (vfx->s).flags;
          c1 = DISPLAY;
          asm("" : "+r"(c1));
          fa |= c1;
          f = fa;
        } else {
          goto off;
        }
        goto store;
      }
      if ((u8)t <= 0x13) {
        if (t & 2) {
          register s32 fc asm("r0");
          register s32 c2 asm("r1");
          fc = (vfx->s).flags;
          c2 = DISPLAY;
          fc |= c2;
          f = fc;
        } else {
        off: {
            register u8 f1 asm("r1");
            register s32 fr asm("r0");
            f1 = (vfx->s).flags;
            fr = 0xFE;
            fr &= f1;
            f = fr;
          }
        }
      store:
        (vfx->s).flags = f;
      }
      UpdateMotionGraphic(&vfx->s);
      if ((vfx->s).work[2] == 0) {
        register u8 f1 asm("r1");
        register s32 f2 asm("r0");
        f1 = (vfx->s).flags;
        f2 = 0xFE;
        f2 &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f2 &= c2;
        }
        (vfx->s).flags = f2;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

// --------------------------------------------

void FUN_080c5764(struct VFX* p);
void FUN_080c57a4(struct VFX* p);
void FUN_080c5860(struct VFX* p);
void FUN_080c598c(struct VFX* p);
void FUN_080c5b30(struct VFX* p);
void FUN_080c5c64(struct VFX* p);

// clang-format off
const VFXFunc sGhost70Updates[6] = {
  FUN_080c5764,
  FUN_080c57a4,
  FUN_080c5860,
  FUN_080c598c,
  FUN_080c5b30,
  FUN_080c5c64,
};
// clang-format on

// --------------------------------------------

void FUN_080c5784(struct VFX* p);

// clang-format off
const VFXFunc sGhost70Deinitializers[6] = {
  FUN_080c5784,
  FUN_080c5784,
  FUN_080c5784,
  FUN_080c5784,
  FUN_080c5784,
  FUN_080c5784,
};
// clang-format on
