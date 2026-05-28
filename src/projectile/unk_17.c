#include "collision.h"
#include "global.h"
#include "motion.h"
#include "projectile.h"

struct Projectile* FUN_080a2790(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = 1;
  }
  return p;
}

struct Projectile* FUN_080a27e4(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = 2;
  }
  return p;
}

struct Projectile* FUN_080a2838(struct Entity* e, struct Coord* c1, struct Coord* c2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a3;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
    (p->s).work[1] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

INCASM("asm/projectile/unk_17_pre_p4.inc");

void FUN_080a2d9c(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x42, 4));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

INCASM("asm/projectile/unk_17_post.inc");

void Projectile17_Init(struct Projectile* p);
void Projectile17_Update(struct Projectile* p);
void Projectile17_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile17Routine = {
    [ENTITY_INIT] =      Projectile17_Init,
    [ENTITY_UPDATE] =    Projectile17_Update,
    [ENTITY_DIE] =       Projectile17_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a2adc(struct Projectile* p);
void FUN_080a2d9c(struct Projectile* p);
void FUN_080a2dec(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836b3b4[3] = {
    FUN_080a2adc,
    FUN_080a2d9c,
    FUN_080a2dec,
};

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};
