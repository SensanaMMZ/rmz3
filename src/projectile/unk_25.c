#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc PTR_ARRAY_0836bf68[4];

void FUN_080a83e4(struct Entity* e, u8 w0, u8 w1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 25);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = w0;
    (p->s).work[1] = w1;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void Projectile25_Init(struct Projectile* p) {
  (PTR_ARRAY_0836bf68[(p->s).work[0]])(p);
}

void Projectile25_Update(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void Projectile25_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

static const struct Collision sCollisions[6];

void Projectile25_Update(struct Projectile* p);

// 0x080A84C4
void FUN_080a84c4(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  register s32 one asm("r4");
  s32 z7;
  register s32 xf asm("r2");
  {
    u32 tbl = (u32)gProjectileFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = 1;
    z7 = 0;
    asm volatile("" ::"r"(z7));
    fv |= fl;
    fl = 2;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, 0x5D00);
  {
    register s32 qf asm("r0");
    qf = q->flags;
    xf = qf >> 4;
  }
  xf &= one;
  if (xf != 0) {
    (p->s).flags |= X_FLIP;
  } else {
    (p->s).flags &= ~X_FLIP;
  }
  {
    register s32 v asm("r1");
    u8* oa;
    s32 sh4, ov, m11;
    asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
    (p->s).spr.xflip = v;
    oa = (u8*)p + 0x4a;
    sh4 = v << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh4;
  }
  {
    s32 dx;
    if ((p->s).flags & X_FLIP) {
      (p->s).coord.x += 0x1000;
      dx = 0x400;
    } else {
      (p->s).coord.x -= 0x1000;
      dx = -0x400;
    }
    (p->s).d.x = dx;
  }
  (p->s).coord.y -= 0x1800;
  {
    s32 z;
    struct Body* body;
    z = 0;
    (p->s).d.y = z;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836BF78, &(p->s).coord, 0x40);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z;
  }
  asm volatile("" ::"r"(z7));
  Projectile25_Update(p);
}

// 0x080A85A0
void FUN_080a85a0(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  register s32 one asm("r4");
  s32 z7;
  register s32 xf asm("r2");
  {
    u32 tbl = (u32)gProjectileFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = 1;
    z7 = 0;
    asm volatile("" ::"r"(z7));
    fv |= fl;
    fl = 2;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, 0x5D01);
  UpdateMotionGraphic(&p->s);
  {
    register s32 qf asm("r0");
    qf = q->flags;
    xf = qf >> 4;
  }
  xf &= one;
  if (xf != 0) {
    (p->s).flags |= X_FLIP;
  } else {
    (p->s).flags &= ~X_FLIP;
  }
  {
    register s32 v asm("r1");
    u8* oa;
    s32 sh4, ov, m11;
    asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
    (p->s).spr.xflip = v;
    oa = (u8*)p + 0x4a;
    sh4 = v << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh4;
  }
  {
    s32 dx;
    if ((p->s).flags & X_FLIP) {
      (p->s).coord.x += 0x1000;
      dx = 0x400;
    } else {
      (p->s).coord.x -= 0x1000;
      dx = -0x400;
    }
    (p->s).d.x = dx;
  }
  (p->s).coord.y -= 0x1800;
  {
    s32 z;
    struct Body* body;
    z = 0;
    (p->s).d.y = z;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836BFA8, &(p->s).coord, 0x40);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z;
  }
  asm volatile("" ::"r"(z7));
  Projectile25_Update(p);
}


void FUN_080a8684(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitRotatableMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(SM093_COPYX_NORMAL_SHOT, 0));
  UpdateMotionGraphic(&p->s);
  SET_XFLIP(p, (q->flags & X_FLIP) != 0);
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x += PIXEL(16);
    (p->s).d.x = COS(32) << 2, (p->s).d.y = SIN(32) << 2;
  } else {
    (p->s).coord.x -= PIXEL(16);
    (p->s).d.x = SIN(128 + 32) << 2, (p->s).d.y = COS(32) << 2;
  }
  *(&(p->s).angle) = 0xE0;
  (p->s).coord.y -= PIXEL(18);
  INIT_BODY(p, &sCollisions[4], 64, NULL);
  Projectile25_Update(p);
}

void FUN_080a8794(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitRotatableMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(SM093_COPYX_NORMAL_SHOT, 1));
  UpdateMotionGraphic(&p->s);
  SET_XFLIP(p, (q->flags & X_FLIP) != 0);
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x += PIXEL(16);
    (p->s).d.x = COS(32) << 2, (p->s).d.y = SIN(32) << 2;
  } else {
    (p->s).coord.x -= PIXEL(16);
    (p->s).d.x = SIN(128 + 32) << 2, (p->s).d.y = COS(32) << 2;
  }
  *(&(p->s).angle) = 0xE0;
  (p->s).coord.y -= PIXEL(18);
  INIT_BODY(p, &sCollisions[2], 64, NULL);
  Projectile25_Update(p);
}

void Projectile25_Init(struct Projectile* p);
void Projectile25_Update(struct Projectile* p);
void Projectile25_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile25Routine = {
    [ENTITY_INIT] =      Projectile25_Init,
    [ENTITY_UPDATE] =    Projectile25_Update,
    [ENTITY_DIE] =       Projectile25_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a84c4(struct Projectile* p);
void FUN_080a85a0(struct Projectile* p);
void FUN_080a8684(struct Projectile* p);
void FUN_080a8794(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836bf68[4] = {
    FUN_080a84c4,
    FUN_080a85a0,
    FUN_080a8684,
    FUN_080a8794,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
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
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 6,
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
};
