#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc PTR_ARRAY_0836c034[6];

static const ProjectileFunc PTR_ARRAY_0836c01c[6];

void FUN_080a88a4(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 26);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void FUN_080a88fc(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 26);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void Projectile26_Init(struct Projectile* p) {
  (PTR_ARRAY_0836c01c[(p->s).work[0]])(p);
}


void Projectile26_Update(struct Projectile* p) {
  (PTR_ARRAY_0836c034[(p->s).work[0]])(p);
  UpdateMotionGraphic(&p->s);
}

// 0x080A8990
void Projectile26_Die(struct Projectile* p) {
  struct Entity* o = (p->s).unk_28;
  u8* q;
  s32 z;
  if ((p->s).work[0] <= 1) {
    s32 t = (p->s).work[2] - 1;
    z = 0;
    (p->s).work[2] = t;
    if ((u8)t == 0xff) {
      q = (u8*)p + 0x8c;
      *(s32*)q = z;
      asm("" : "+r"(q));
      q += 4;
      *(s32*)q = z;
      asm("" : "+r"(q));
      q += 4;
      asm("" : "+r"(q));
      *q = z;
      (p->s).flags &= ~4;
      SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
      {
        u8* r = (u8*)o + 0xcf;
        if ((u8)--*r == 0) {
          StopSound(*(s16*)((u8*)p + 0xc0));
        }
      }
    }
  } else {
      q = (u8*)p + 0x8c;
      z = 0;
      asm("" : "+r"(z));
      *(s32*)q = z;
      asm("" : "+r"(q));
      q += 4;
      *(s32*)q = z;
      asm("" : "+r"(q));
      q += 4;
      asm("" : "+r"(q));
      *q = z;
      (p->s).flags &= ~4;
      SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
    StopSound(*(s16*)((u8*)p + 0xc0));
  }
}

static const struct Collision sCollisions[4];

// 0x080A8A38
void FUN_080a8a38(struct Projectile* p) {
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
  InitNonAffineMotion(&p->s);
  (p->s).flags = DISPLAY | (p->s).flags;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5B, 0x01));
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
  p->soundID = 0xFFFF;
  p->soundID = PlaySound(0x48);
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x += 0x1000;
    (p->s).d.x = 0x380;
  } else {
    (p->s).coord.x += -0x1000;
    (p->s).d.x = -0x380;
  }
  (p->s).coord.y += -0x1800;
  (p->s).d.y = 0;
  {
    register u8* q asm("r1");
    p->prevCoord.h.ylo = 0xFFF0;
    q = (u8*)p + 0xb4;
    *(s32*)q = (p->s).coord.x;
    asm volatile("add %0, #4" : "+r"(q));
    *(s32*)q = (p->s).coord.y;
  }
  ++*((u8*)e + 0xcf);
  INIT_BODY(p, sCollisions, 0x40, NULL);
  (p->s).work[2] = 2;
  Projectile26_Update(p);
}

// 0x080A8B50
void FUN_080a8b50(struct Projectile* p) {
  struct Entity* e = (p->s).unk_28;
  u32 xf;
  u32 one;
  s32 z;
  {
    const ProjectileRoutine* const* base = gProjectileFnTable;
    const ProjectileRoutine* const* rowp = base + (p->s).id;
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(**rowp)[ENTITY_UPDATE];
  }
  InitNonAffineMotion(&p->s);
  (p->s).flags = DISPLAY | (p->s).flags;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5B, 0x01));
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
  p->soundID = 0xFFFF;
  p->soundID = PlaySound(0x48);
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x += 0x1000;
    (p->s).d.x = 0x380;
    (p->s).d.y = 0x380;
  } else {
    (p->s).coord.x += -0x1000;
    (p->s).d.x = -0x380;
    (p->s).d.y = 0x380;
  }
  (p->s).coord.y += -0x1200;
  {
    p->prevCoord.h.ylo = 0xFFE8;
    z = 0;
  }
  ++*((u8*)e + 0xcf);
  {
    register u8* q asm("r1");
    q = (u8*)p + 0xb4;
    *(s32*)q = (p->s).coord.x;
    asm volatile("add %0, #4" : "+r"(q));
    *(s32*)q = (p->s).coord.y;
  }
  {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 0x40);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z;
  }
  (p->s).work[2] = 2;
  Projectile26_Update(p);
}

INCASM("asm/projectile/unk_26_post_a2.inc");

// 0x080a8f14
void FUN_080a8f14(struct Projectile* p) {
  if ((p->s).mode[1] == 0) {
    if ((u8)--(p->s).work[2] == 0xFF) {
      register u8 n asm("r2") = (p->s).work[1];
      if (n != 1) {
        if ((p->s).work[0] & 1) {
          n--;
          FUN_080a88fc(&p->s, 3, n);
        } else {
          n--;
          FUN_080a88fc(&p->s, 2, n);
        }
      }
      (p->s).mode[1]++;
    }
  }
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += *(s16*)((u8*)p + 0xbc);
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    (p->s).work[2] = 0x10;
  }
}

metatile_attr_t FUN_080098a4(s32 x, s32 y);

void FUN_080a8fa8(struct Projectile* p) {
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += PIXEL(1) / 4;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    FUN_080a88fc(&p->s, 5, 0);
  }
}

void FUN_080a8ff0(struct Projectile* p) {
  s32 t;
  s32 z;
  t = (p->s).work[2] + 1;
  z = 0;
  (p->s).work[2] = t;
  if ((u8)t == 0x24) {
    (p->body).status = z;
    (p->body).prevStatus = z;
    (p->body).invincibleTime = z;
    (p->s).flags &= ~COLLIDABLE;
  }
  if ((p->s).motion.state == 4) {
    (p->s).flags &= ~DISPLAY;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void Projectile26_Init(struct Projectile* p);
void Projectile26_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile26Routine = {
    [ENTITY_INIT] =      Projectile26_Init,
    [ENTITY_UPDATE] =    Projectile26_Update,
    [ENTITY_DIE] =       Projectile26_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a8a38(struct Projectile* p);
void FUN_080a8b50(struct Projectile* p);
void FUN_080a8c74(struct Projectile* p);
void FUN_080a8d70(struct Projectile* p);
void FUN_080a8e64(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836c01c[6] = {
    FUN_080a8a38,
    FUN_080a8b50,
    FUN_080a8c74,
    FUN_080a8c74,
    FUN_080a8d70,
    FUN_080a8e64,
};
// clang-format on

// --------------------------------------------

void FUN_080a8f14(struct Projectile* p);
void FUN_080a8fa8(struct Projectile* p);
void FUN_080a8ff0(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836c034[6] = {
    FUN_080a8f14,
    FUN_080a8f14,
    FUN_080a8f14,
    FUN_080a8f14,
    FUN_080a8fa8,
    FUN_080a8ff0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
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
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
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
};

static const s16 s16_ARRAY_0836c0ac[8] = {
    -PIXEL(1), PIXEL(1), -PIXEL(2), PIXEL(2), -PIXEL(3), PIXEL(3), -PIXEL(4), PIXEL(4),
};
