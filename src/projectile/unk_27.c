#include "zero.h"
#include "collision.h"
#include "global.h"
#include "metatile.h"
#include "projectile.h"

void CreateVFX53(struct Entity* e, u8 n);

static const ProjectileFunc PTR_ARRAY_0836c0ec[7];

static const ProjectileFunc PTR_ARRAY_0836c0d0[7];

void FUN_080a9048(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 27);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void FUN_080a90a0(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 27);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void Projectile27_Init(struct Projectile* p) {
  (PTR_ARRAY_0836c0d0[(p->s).work[0]])(p);
}


void Projectile27_Update(struct Projectile* p) {
  (PTR_ARRAY_0836c0ec[(p->s).work[0]])(p);
}

void Projectile27_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_27_pre_post_p2_p1_p1.inc");

static const struct Collision sCollisions[10];

// 0x080A9250
void FUN_080a9250(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  u8 fl;
  s32 z;
  s32 one;
  {
    const ProjectileRoutine* const* base = gProjectileFnTable;
    const ProjectileRoutine* const* rowp = base + (p->s).id;
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(**rowp)[ENTITY_UPDATE];
  }
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5C, 0x00));
  fl = (q->flags >> 4) & one;
  if (fl != 0) {
    (p->s).flags |= X_FLIP;
  } else {
    (p->s).flags &= ~X_FLIP;
  }
  {
    u32 xf2;
    asm volatile("add %0, %1, #0" : "=&l"(xf2) : "l"(fl));
    ((p->s).spr).xflip = xf2;
    {
      u8* oa = (u8*)p + 0x4a;
      u32 sh4 = xf2 << 4;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
    }
  }
  if ((p->s).flags & 0x10) {
    (p->s).coord.x += 0x1000;
    (p->s).d.x = 0x300;
    (p->s).d.y = 0x300;
    p->prevCoord.h.ylo = 0xFFE0;
  } else {
    (p->s).coord.x -= 0x1000;
    (p->s).d.x = -0x300;
    (p->s).d.y = 0x300;
    p->prevCoord.h.ylo = 0x20;
  }
  (p->s).coord.y -= 0x1200;
  p->prevCoord.h.yhi = 0xFFE0;
  z = 0;
  {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 0x40);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z;
  }
  (p->s).work[2] = 0xFF;
  Projectile27_Update(p);
}

// 0x080A9358
void FUN_080a9358(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  switch ((p->s).mode[1]) {
    case 0: {
      s32 v;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.x += *(s16*)((u8*)p + 0xbc);
      (p->s).d.y += *(s16*)((u8*)p + 0xbe);
      v = (p->s).d.x;
      if (v < 0) {
        v = -v;
      }
      if (v <= 0x100) {
        (p->s).mode[1]++;
      }
      break;
    }
    case 1: {
      s32 cy;
      s32 v;
      (p->s).coord.x += (p->s).d.x;
      cy = (p->s).coord.y;
      v = cy + 0x1800;
      v -= (pZero2->s).coord.y;
      v >>= 9;
      if (v > 0) {
        (p->s).coord.y = cy - 0x40;
      } else if (v < 0) {
        (p->s).coord.y = cy + 0x40;
      }
      if ((u8)--(p->s).work[2] == 0xFF) {
        (p->s).mode[1]++;
        (p->s).work[2] = 0x40;
      }
      break;
    }
    case 2: {
      u8 w;
      u32 m;
      s32 t;
      s32 v;
      (p->s).coord.x += (p->s).d.x;
      w = (p->s).work[2];
      m = w & 3;
      t = w;
      if (m > 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      v = t - 1;
      (p->s).work[2] = v;
      if ((u8)v == 0xFF) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
  if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/projectile/unk_27_pre_post_p2_p1_p1b.inc");

// 0x080A96F8
void FUN_080a96f8(struct Projectile* p) {
  struct Entity* e = (p->s).unk_28;
  u32 xf;
  u32 one;
  {
    const ProjectileRoutine* const* base = gProjectileFnTable;
    const ProjectileRoutine* const* rowp = base + (p->s).id;
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(**rowp)[ENTITY_UPDATE];
  }
  InitRotatableMotion(&p->s);
  (p->s).flags = DISPLAY | (p->s).flags;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5C, 0x02));
  xf = (e->flags >> 4) & one;
  if (xf != 0) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= 0xEF;
  }
  {
    u32 xf2;
    asm volatile("add %0, %1, #0" : "=&l"(xf2) : "l"(xf));
    ((p->s).spr).xflip = xf2;
    xf = xf2;
  }
  {
    u8* oa = (u8*)p + 0x4a;
    u32 sh4 = xf << 4;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    m11 |= sh4;
    *oa = m11;
  }
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x += 0x1000;
    (p->s).d.x = gSineTable[0x60] << 2;
    (p->s).d.y = gSineTable[0x20] << 2;
  } else {
    (p->s).coord.x -= 0x1000;
    (p->s).d.x = gSineTable[0xA0] << 2;
    (p->s).d.y = gSineTable[0x60] << 2;
  }
  {
    s32 z;
    (p->s).angle = 0xA0;
    z = 0;
    (p->s).coord.y -= 0x1200;
    (p->prevCoord).c.x = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    {
      struct Body* body;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[6], &(p->s).coord, 0x40);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z;
    }
  }
  Projectile27_Update(p);
}

// 0x080A9810
void FUN_080a9810(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  {
    u8 w2 = (p->s).work[2];
    s32 nx = w2 + 1;
    asm("" : "+r"(nx));
    (p->s).work[2] = nx;
    {
      s32 k7 = 7;
      register s32 res asm("r0");
      asm("" : "+r"(k7));
      res = w2 & k7;
      asm volatile("" :: "r"(w2));
      if (res == 0) {
        FUN_080a90a0(&p->s, 6, 1);
      }
    }
  }
  if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    if (*(s32*)((u8*)p + 0xb8) <= (p->s).coord.y) {
      FUN_080a90a0(&p->s, 5, 0x2B);
      FUN_080a90a0(&p->s, 5, 0x15);
      FUN_080a90a0(&p->s, 5, 0);
      FUN_080a90a0(&p->s, 5, 0xEA);
      FUN_080a90a0(&p->s, 5, 0xD4);
    } else if ((p->s).flags & X_FLIP) {
      FUN_080a90a0(&p->s, 5, 0xEB);
      FUN_080a90a0(&p->s, 5, 0xD5);
      FUN_080a90a0(&p->s, 5, 0xC0);
      FUN_080a90a0(&p->s, 5, 0xAB);
      FUN_080a90a0(&p->s, 5, 0x95);
    } else {
      FUN_080a90a0(&p->s, 5, 0x6B);
      FUN_080a90a0(&p->s, 5, 0x55);
      FUN_080a90a0(&p->s, 5, 0x40);
      FUN_080a90a0(&p->s, 5, 0x2B);
      FUN_080a90a0(&p->s, 5, 0x15);
    }
    PlaySound(0x3F);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/projectile/unk_27_pre_post_p2_p1_p1c.inc");

void FUN_080a99d4(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if ((p->s).mode[1] == 0) {
    if ((u8)--(p->s).work[2] == 0xff) {
      (p->s).mode[1]++;
    }
  } else if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_080a9a30(struct Projectile* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5c, 4));
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile27_Update(p);
}

void FUN_080a9a74(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  CreateVFX53(&p->s, (p->s).work[1]);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
}


void Projectile27_Init(struct Projectile* p);
void Projectile27_Update(struct Projectile* p);
void Projectile27_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile27Routine = {
    [ENTITY_INIT] =      Projectile27_Init,
    [ENTITY_UPDATE] =    Projectile27_Update,
    [ENTITY_DIE] =       Projectile27_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a9158(struct Projectile* p);
void FUN_080a9250(struct Projectile* p);
void FUN_080a946c(struct Projectile* p);
void FUN_080a9604(struct Projectile* p);
void FUN_080a96f8(struct Projectile* p);
void FUN_080a9920(struct Projectile* p);
void FUN_080a9a30(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836c0d0[7] = {
    FUN_080a9158,
    FUN_080a9250,
    FUN_080a946c,
    FUN_080a9604,
    FUN_080a96f8,
    FUN_080a9920,
    FUN_080a9a30,
};
// clang-format on

// --------------------------------------------

void FUN_080a9358(struct Projectile* p);
void FUN_080a953c(struct Projectile* p);
void FUN_080a9810(struct Projectile* p);
void FUN_080a99d4(struct Projectile* p);
void FUN_080a9a74(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836c0ec[7] = {
    FUN_080a9358,
    FUN_080a9358,
    FUN_080a953c,
    FUN_080a9810,
    FUN_080a9810,
    FUN_080a99d4,
    FUN_080a9a74,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[10] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(8), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
