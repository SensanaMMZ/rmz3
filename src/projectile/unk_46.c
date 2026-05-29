#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc PTR_ARRAY_0836d8b0[3];
static const ProjectileFunc PTR_ARRAY_0836d8bc[3];
static const ProjectileFunc PTR_ARRAY_0836d8c8[3];

struct Projectile* FUN_080b221c(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 46);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
  }
  return p;
}

struct Projectile* FUN_080b2270(struct Entity* e, struct Entity* e2, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 46);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).unk_2c = e2;
    (p->s).work[0] = a2;
    (p->s).work[1] = a3;
  }
  return p;
}

void FUN_080b22c8(struct Projectile* p) {
  (PTR_ARRAY_0836d8b0[(p->s).work[0]])(p);
}


void FUN_080b22e0(struct Projectile* p) {
  (PTR_ARRAY_0836d8bc[(p->s).work[0]])(p);
}


void FUN_080b22f8(struct Projectile* p) {
  (PTR_ARRAY_0836d8c8[(p->s).work[0]])(p);
}

INCASM("asm/projectile/unk_46_p4_p1.inc");

void FUN_080b274c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b2764(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b277c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b22c8(struct Projectile* p);
void FUN_080b22e0(struct Projectile* p);
void FUN_080b22f8(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile46Routine = {
    [ENTITY_INIT] =      FUN_080b22c8,
    [ENTITY_UPDATE] =    FUN_080b22e0,
    [ENTITY_DIE] =       FUN_080b22f8,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b2310(struct Projectile* p);
void FUN_080b2384(struct Projectile* p);
void FUN_080b2428(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d8b0[3] = {
    FUN_080b2310,
    FUN_080b2384,
    FUN_080b2428,
};
// clang-format on

void FUN_080b24c8(struct Projectile* p);
void FUN_080b258c(struct Projectile* p);
void FUN_080b2654(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d8bc[3] = {
    FUN_080b24c8,
    FUN_080b258c,
    FUN_080b2654,
};
// clang-format on

void FUN_080b274c(struct Projectile* p);
void FUN_080b2764(struct Projectile* p);
void FUN_080b277c(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d8c8[3] = {
    FUN_080b274c,
    FUN_080b2764,
    FUN_080b277c,
};
// clang-format on
