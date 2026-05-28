#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc PTR_ARRAY_0836d8b0[3];
static const ProjectileFunc PTR_ARRAY_0836d8bc[3];
static const ProjectileFunc PTR_ARRAY_0836d8c8[3];

INCASM("asm/projectile/unk_46_p1.inc");

void FUN_080b22c8(struct Projectile* p) {
  (PTR_ARRAY_0836d8b0[(p->s).work[0]])(p);
}

INCASM("asm/projectile/unk_46_p2.inc");

void FUN_080b22e0(struct Projectile* p) {
  (PTR_ARRAY_0836d8bc[(p->s).work[0]])(p);
}

INCASM("asm/projectile/unk_46_p3.inc");

void FUN_080b22f8(struct Projectile* p) {
  (PTR_ARRAY_0836d8c8[(p->s).work[0]])(p);
}

INCASM("asm/projectile/unk_46_p4_p1.inc");

void FUN_080b274c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_46_p4_p2.inc");

void FUN_080b2764(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_46_p4_p3.inc");

void FUN_080b277c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_46_p4_p4.inc");

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
