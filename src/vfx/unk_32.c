#include "global.h"
#include "story.h"
#include "vfx.h"

static void Ghost32_Init(struct VFX* p);
void Ghost32_Update(struct VFX* p);
void Ghost32_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost32Routine = {
    [ENTITY_INIT] =      Ghost32_Init,
    [ENTITY_UPDATE] =    Ghost32_Update,
    [ENTITY_DIE] =       Ghost32_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080ba7c8(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba81c(struct Coord* c, bool8 isRight, s16 r2, s32 r3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = isRight;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->props).unk32.unk_0 = r2;
    (p->props).unk32.unk_4 = r3;
  }
  return p;
}

struct VFX* FUN_080ba888(struct Coord* c, struct Coord* d, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).d.x = d->x;
    (p->s).d.y = d->y;
  }
  return p;
}

struct VFX* FUN_080ba8e8(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 3;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba940(struct Coord* c, u8 n, u8 r2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 4;
    (p->props).unk32.unk_c = r2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba9a0(struct Coord* c) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = 5;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba9f4(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 6;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080baa4c(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 7;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

// --------------------------------------------

void FUN_080baad8(struct VFX* p);
void FUN_080bab54(struct VFX* p);
void FUN_080babac(struct VFX* p);
void FUN_080bac14(struct VFX* p);
void FUN_080bac5c(struct VFX* p);
void FUN_080baca4(struct VFX* p);
void FUN_080bacec(struct VFX* p);
void FUN_080bad34(struct VFX* p);

static void Ghost32_Init(struct VFX* p) {
  // clang-format off
  static const VFXFunc sInitializers[8] = {
      FUN_080baad8,
      FUN_080bab54,
      FUN_080babac,
      FUN_080bac14,
      FUN_080bac5c,
      FUN_080baca4,
      FUN_080bacec,
      FUN_080bad34,
  };
  // clang-format on
  (p->s).work[2] = 0xFF;
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  (sInitializers[(p->s).work[1]])(p);
  Ghost32_Update(p);
}

static const VFXFunc sUpdates[8];
void Ghost32_Die(struct VFX* p);

void FUN_080baad8(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
    (p->s).d.x = PIXEL(3) / 8;
  } else {
    SET_XFLIP(p, TRUE);
    (p->s).d.x = -PIXEL(3) / 8;
  }
  (p->s).d.y = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
}

void FUN_080bab54(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).d.x = 0, (p->s).d.y = 0;
  RNG_0202f388 = LCG(RNG_0202f388);
  (p->s).work[2] = ((RNG_0202f388 >> 16) & 7) + 0x7F;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
}

INCASM("asm/vfx/unk_32_pre_pre.inc");

void Ghost32_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost32_Die(p);
  } else {
    (sUpdates[(p->s).mode[1]])(p);
  }
}


void Ghost32_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_32_post.inc");

void FUN_080bb7c4(struct VFX* p) {
  if (--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }

  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(SM039_PANTHEON_AQUA, 12));
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).work[3]++;
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080bade8(struct VFX* p);
void FUN_080bb048(struct VFX* p);
void FUN_080bb17c(struct VFX* p);
void FUN_080bb2d8(struct VFX* p);
void FUN_080bb3d4(struct VFX* p);
void FUN_080bb5d4(struct VFX* p);
void FUN_080bb68c(struct VFX* p);
void FUN_080bb7c4(struct VFX* p);

// clang-format off
static const VFXFunc sUpdates[8] = {
    FUN_080bade8,
    FUN_080bb048,
    FUN_080bb17c,
    FUN_080bb2d8,
    FUN_080bb3d4,
    FUN_080bb5d4,
    FUN_080bb68c,
    FUN_080bb7c4,
};
// clang-format on

const s32 s32_ARRAY_ARRAY_0836ec64[6][8] = {
    {0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160}, {-0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200}, {-0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160}, {-0x00000060, -0x00000160, 0x00000060, -0x00000200, 0x000000A0, -0x00000160, -0x000000A0, -0x00000200}, {-0x000000A0, -0x00000160, 0x00000060, -0x00000200, -0x00000060, -0x00000160, 0x000000A0, -0x00000200}, {0x000000A0, -0x00000200, -0x000000A0, -0x00000160, 0x00000060, -0x00000200, -0x00000060, -0x00000160},
};

static const s32* const PTR_ARRAY_0836ed24[6] = {
    s32_ARRAY_ARRAY_0836ec64[0], s32_ARRAY_ARRAY_0836ec64[1], s32_ARRAY_ARRAY_0836ec64[2], s32_ARRAY_ARRAY_0836ec64[3], s32_ARRAY_ARRAY_0836ec64[4], s32_ARRAY_ARRAY_0836ec64[5],
};
