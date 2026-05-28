#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc PTR_ARRAY_0836d794[1];
static const ProjectileFunc PTR_ARRAY_0836d798[1];

void FUN_080b1698(s32 x, s32 y, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 44);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
    (p->s).work[3] = a3;
  }
}

static void nop_080b16f0(struct Projectile* p) {}

INCASM("asm/projectile/unk_44_pre_p1_p2.inc");

void FUN_080b1764(struct Projectile* p) {
  (PTR_ARRAY_0836d794[(p->s).mode[1]])(p);
  (PTR_ARRAY_0836d798[(p->s).mode[1]])(p);
}

INCASM("asm/projectile/unk_44_pre_p2.inc");

void FUN_080b17d8(struct Projectile* p) {}

INCASM("asm/projectile/unk_44_post.inc");

void FUN_080b16f4(struct Projectile* p);
void FUN_080b1764(struct Projectile* p);
void FUN_080b1798(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile44Routine = {
    [ENTITY_INIT] =      FUN_080b16f4,
    [ENTITY_UPDATE] =    FUN_080b1764,
    [ENTITY_DIE] =       FUN_080b1798,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b17d8(struct Projectile* p);
void FUN_080b17dc(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836d794[1] = {FUN_080b17d8};
static const ProjectileFunc PTR_ARRAY_0836d798[1] = {FUN_080b17dc};

static const struct Collision Collision_0836d79c = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 4,
  remaining : 0,
  layer : 0x00000001,
  range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(13)},
};

static const u8 u8_ARRAY_0836d7b4[4] = {0, 0, 0, 0};
