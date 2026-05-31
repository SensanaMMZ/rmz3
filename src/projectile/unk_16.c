#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "story.h"

struct Projectile* FUN_080a244c(struct Coord* c1, struct Coord* c2, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 16);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

static const struct Collision sCollisions[];
static const ProjectileFunc PTR_ARRAY_0836b350[2];
void Projectile16_Update(struct Projectile* p);

void Projectile16_Init(struct Projectile* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, &sCollisions[0], 2, NULL);
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  (p->s).work[2] = 0xFF;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  Projectile16_Update(p);
}

void Projectile16_Update(struct Projectile* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  (PTR_ARRAY_0836b350[(p->s).mode[1]])(p);
}

void Projectile16_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_16_p2_p2.inc");

void Projectile16_Init(struct Projectile* p);
void Projectile16_Update(struct Projectile* p);
void Projectile16_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile16Routine = {
    [ENTITY_INIT] =      Projectile16_Init,
    [ENTITY_UPDATE] =    Projectile16_Update,
    [ENTITY_DIE] =       Projectile16_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a25f8(struct Projectile* p);
void FUN_080a2710(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836b350[2] = {
    FUN_080a25f8,
    FUN_080a2710,
};

static const struct Collision sCollisions[3] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(24), PIXEL(24)},
    },
};
