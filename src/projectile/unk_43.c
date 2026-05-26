#include "collision.h"
#include "global.h"
#include "projectile.h"

INCASM("asm/projectile/unk_43_pre.inc");

void FUN_080b13d8(struct Projectile* p) {}

INCASM("asm/projectile/unk_43_post.inc");

void Projectile43_Init(struct Projectile* p);
void Projectile43_Update(struct Projectile* p);
static void Projectile43_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile43Routine = {
    [ENTITY_INIT] =      Projectile43_Init,
    [ENTITY_UPDATE] =    Projectile43_Update,
    [ENTITY_DIE] =       Projectile43_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b155c(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d748[1] = {
    FUN_080b155c,
};
// clang-format on

static void Projectile43_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

static const struct Collision sCollision[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
};

static const u8 u8_ARRAY_0836d77c[4] = {0, 0, 0, 0};
