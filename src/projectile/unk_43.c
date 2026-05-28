#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "vfx.h"

static const u8 u8_ARRAY_0836d77c[4];

void Projectile43_Update(struct Projectile* p);

INCASM("asm/projectile/unk_43_pre_p1.inc");

void Projectile42_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(1, &(p->s).coord);
  PlaySound(0x2a);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080b13d8(struct Projectile* p) {}

void FUN_080b13dc(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x8e, 0xc));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) || ((p->body).status & 4)) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void FUN_080b145c(struct Coord* c, s32 dx) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 43);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).d.x = dx;
    (p->s).work[2] = dx > 0 ? 1 : 0;
    (p->s).work[0] = 0;
  }
}

void Projectile43_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836d77c[(p->s).work[0]];
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  Projectile43_Update(p);
}

INCASM("asm/projectile/unk_43_post_p2_p3.inc");

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
