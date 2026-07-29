#include "collision.h"
#include "global.h"
#include "motion.h"
#include "projectile.h"
#include "trig.h"

void Projectile31_Init(struct Projectile* p);
void Projectile31_Update(struct Projectile* p);
static void Projectile31_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile31Routine = {
    [ENTITY_INIT] =      Projectile31_Init,
    [ENTITY_UPDATE] =    Projectile31_Update,
    [ENTITY_DIE] =       Projectile31_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

#include "entity/macros.h"

struct Projectile* FUN_080aa7a8(struct Entity* e, u8 a, u8 b) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 31);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a;
    (p->s).work[1] = b;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
    return p;
  }
  return NULL;
}

static const struct Collision sCollisions[2];
static const s32 s32_ARRAY_0836c35c[4];
static const s32 s32_ARRAY_0836c36c[8];
static const s32 s32_ARRAY_0836c38c[8];

void Projectile31_Init(struct Projectile* p) {
  register s32 z5 asm("r5");
  struct Entity* e = (p->s).unk_28;
  InitRotatableMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    asm("" : "+r"(d0));
    z5 = 0;
    d0 |= f0;
    {
      register s32 c2 asm("r1");
      c2 = FLIPABLE;
      d0 |= c2;
    }
    (p->s).flags = d0;
  }
  SetMotion(&p->s, 0x640F);
  (p->s).flags |= COLLIDABLE;
  {
    struct Body* body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 0x40);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z5;
  }
  {
    register u8 f1 asm("r1");
    register s32 m0 asm("r0");
    f1 = (p->s).flags;
    m0 = 0xEF;
    m0 &= f1;
    (p->s).flags = m0;
  }
  ((p->s).spr).xflip = z5;
  {
    u8* a = (u8*)p + 0x4a;
    register u8 b asm("r1");
    s32 msk;
    b = *a;
    msk = -0x11;
    msk &= b;
    *a = msk;
  }
  (p->s).coord = e->coord;
  {
    s32 dx;
    if (e->flags & 0x10) {
      (p->s).coord.x = e->coord.x + s32_ARRAY_0836c35c[(p->s).work[1] & 3];
      dx = s32_ARRAY_0836c36c[(p->s).work[1]];
    } else {
      (p->s).coord.x = e->coord.x - s32_ARRAY_0836c35c[(p->s).work[1] & 3];
      dx = -s32_ARRAY_0836c36c[(p->s).work[1]];
    }
    (p->s).d.x = dx;
  }
  {
    register s32 wk asm("r2");
    s32 dy;
    wk = *(volatile u8*)&(p->s).work[1];
    asm("" : "+r"(wk));
    (p->s).coord.y = e->coord.y - 0x3000;
    dy = s32_ARRAY_0836c38c[wk];
    asm volatile("" :: "r"(wk));
    (p->s).d.y = dy;
    {
      s32 an = ((u16)ArcTan2(*(volatile s32*)&(p->s).d.x, dy) + 0x4000) >> 8;
      (p->s).work[3] = an;
      (p->s).angle = an;
    }
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile31_Update(p);
}


void CreateVFX57(struct Coord* c, u8 a1, u8 a2, s16 dx, s16 dy);

void Projectile31_Update(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  {
    s32 an = ((u16)ArcTan2((p->s).d.x, (p->s).d.y) + 0x4000) >> 8;
    (p->s).work[3] = an;
    (p->s).angle = an;
  }
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
    CreateVFX57(&(p->s).coord, 1, 1, (RANDOM(RNG_0202f388) & 0xFF) | 0x100,
                -((RANDOM(RNG_0202f388) & 0x3FF) + 0x100));
    CreateVFX57(&(p->s).coord, 1, 3, -((RANDOM(RNG_0202f388) & 0xFF) + 0x100),
                -((RANDOM(RNG_0202f388) & 0x3FF) + 0x100));
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

static void Projectile31_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static const struct Collision sCollisions[2] = {
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

// --------------------------------------------

static const s32 s32_ARRAY_0836c35c[4] = {PIXEL(8), PIXEL(8), PIXEL(32), PIXEL(32)};

static const s32 s32_ARRAY_0836c36c[8] = {
    0x140, 0x180, 0x200, 0x280, 0xA0, 0xC0, 0x100, 0x140,
};

static const s32 s32_ARRAY_0836c38c[8] = {
    -0x600, -0x500, -0x400, -0x300, -0xC00, -0xA00, -0x800, -0x600,
};
