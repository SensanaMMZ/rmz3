#include "collision.h"
#include "global.h"
#include "projectile.h"

static const struct Collision sCollisions[2];

static void BlazinTail_Init(struct Projectile* p);
static void BlazinTail_Update(struct Projectile* p);
static void BlazinTail_Die(struct Projectile* p);

static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

// clang-format off
const ProjectileRoutine gBlazinTailRoutine = {
    [ENTITY_INIT] =      BlazinTail_Init,
    [ENTITY_UPDATE] =    BlazinTail_Update,
    [ENTITY_DIE] =       BlazinTail_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Projectile* createBlazinTail(struct Entity* e, s32 hp) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 10);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
    *(s32*)(p->work) = hp;
  }
  return p;
}

// --------------------------------------------

static void BlazinTail_Init(struct Projectile* p) {
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, &sCollisions[0], *(s16*)(p->work), onCollision);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  BlazinTail_Update(p);
}

// --------------------------------------------

static void FUN_0809f140(struct Projectile* p);

static void BlazinTail_Update(struct Projectile* p) {
  static const ProjectileFunc sUpdates[1] = {
      FUN_0809f140,
  };

  if ((p->body).hp < 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    BlazinTail_Die(p);
    return;
  }
  (p->prevCoord).x = (((p->s).unk_28)->flags & X_FLIP) ? 1 : 0;
  (sUpdates[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void BlazinTail_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void FUN_0809f140(struct Projectile* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      SET_XFLIP(p, (((p->s).unk_28)->flags >> 4) & 1);
      (p->s).coord.x = ((p->s).unk_28)->coord.x;
      (p->s).coord.y = ((p->s).unk_28)->coord.y;
      if (((p->s).unk_28)->mode[1] == 9) {
        SetDDP(&p->body, &sCollisions[0]);
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SET_XFLIP(p, (((p->s).unk_28)->flags >> 4) & 1);
      (p->s).coord.x = ((p->s).unk_28)->coord.x;
      (p->s).coord.y = ((p->s).unk_28)->coord.y;
      if (((p->s).unk_28)->mode[1] != 9) {
        (p->s).mode[2] = 0;
      }
      break;
  }
}

NAKED static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  INCCODE("asm/projectile/blazin_tail_onCollision.inc");
}

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(22), -PIXEL(18), PIXEL(22), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 7,
      remaining : 0,
      range : {PIXEL(22), -PIXEL(18), PIXEL(22), PIXEL(16)},
    },
};
