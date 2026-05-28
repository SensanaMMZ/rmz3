#include "collision.h"
#include "global.h"
#include "projectile.h"

struct Projectile* createPantheonBomb(struct Coord* c1, struct Coord* c2, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 35);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    (p->s).work[1] = 0;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

struct Projectile* createPantheonBombBlast(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 35);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

INCASM("asm/projectile/pantheon_bomber_p3.inc");

void PantheonBombProjectile_Init(struct Projectile* p);
void PantheonBombProjectile_Update(struct Projectile* p);
void PantheonBombProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gPantheonBombProjectileRoutine = {
    [ENTITY_INIT] =      PantheonBombProjectile_Init,
    [ENTITY_UPDATE] =    PantheonBombProjectile_Update,
    [ENTITY_DIE] =       PantheonBombProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void _pantheonBombAI(struct Projectile* p);
void pantheonBombBlastAI(struct Projectile* p);

static const ProjectileFunc sUpdates[2] = {
    _pantheonBombAI,
    pantheonBombBlastAI,
};

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(28), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
};
