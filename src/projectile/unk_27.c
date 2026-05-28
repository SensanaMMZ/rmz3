#include "collision.h"
#include "global.h"
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

INCASM("asm/projectile/unk_27_pre_pre_post.inc");

void Projectile27_Update(struct Projectile* p) {
  (PTR_ARRAY_0836c0ec[(p->s).work[0]])(p);
}

void Projectile27_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_27_pre_post_p2.inc");

void FUN_080a9a74(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  CreateVFX53(&p->s, (p->s).work[1]);
  SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
}

INCASM("asm/projectile/unk_27_post.inc");

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
