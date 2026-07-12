#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "projectile.h"
#include "story.h"

static const ProjectileFunc sUpdates[1];
static const struct Collision sCollision;

static void Projectile2_Init(struct Projectile* p);
static void Projectile2_Update(struct Projectile* p);
static void Projectile2_Die(struct Projectile* p);
void FUN_080ba9a0(struct Coord* c);

// clang-format off
const ProjectileRoutine gProjectile2Routine = {
    [ENTITY_INIT] =      Projectile2_Init,
    [ENTITY_UPDATE] =    Projectile2_Update,
    [ENTITY_DIE] =       Projectile2_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

struct Projectile* CreateProjectile2(struct Coord* c1, struct Coord* c2, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 2);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

// --------------------------------------------

// Init a type-2 projectile: display + flippable + collidable body (hp 1, no
// on-collision fn), face by spawn direction (work[0]), arm the lifetime timer
// (work[2]=0xff), route to Update. Retail hand-writes the direction flip with
// the flags/xflip/oam writes DUPLICATED per branch and recomputes the spr
// pointers separately; agbcc-from-clean-C (SET_XFLIP, which shares the post-if
// writes, or the pointer-reused form) is several instr shorter — a retail-
// suboptimal codegen quirk clean C can't reproduce. INCCODE for the byte-match.
NON_MATCH static void Projectile2_Init(struct Projectile* p) {
#if MODERN
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, &sCollision, 1, NULL);
  SET_XFLIP(p, (p->s).work[0]);
  (p->s).work[2] = 0xff;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  Projectile2_Update(p);
#else
  INCCODE("asm/wip/Projectile2_Init.inc");
#endif
}

static void updateProjectile2(struct Projectile* p);

static void Projectile2_Update(struct Projectile* p) {
  static const ProjectileFunc sUpdates[1] = {
      updateProjectile2,
  };

  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Projectile2_Die(p);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
}

static void Projectile2_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

static void updateProjectile2(struct Projectile* p) {
  (p->s).work[2]--;
  if ((u8)(p->s).work[2] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x270B);
      if ((p->s).work[0] == 0) {
        (p->s).d.x = -0x240;
      } else {
        (p->s).d.x = 0x240;
      }
      (p->s).d.y = 0;
      (p->s).work[2] = 0x78;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      if ((u8)++(p->s).work[3] % 0x14 == 0) {
        s32 sea = gOverworld.sea;
        if (sea < (p->s).coord.y - 0x800) {
          FUN_080ba9a0(&(p->s).coord);
        }
      }
      if ((p->s).work[2] <= 0x1D) {
        if ((p->s).work[2] & 1) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 4,
  nature : BODY_NATURE_B7,
  remaining : 0,
  layer : 0x00000001,
  range : {0x0000, 0x0000, 0x1400, 0x0800},
};
