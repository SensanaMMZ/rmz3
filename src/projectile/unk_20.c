#include "collision.h"
#include "global.h"
#include "physics.h"
#include "trig.h"
#include "projectile.h"
#include "vfx.h"

static const struct Collision sCollisions[3];
static const u8 sInitModes[4];

void Projectile20_Update(struct Projectile* p);

static void nop_080a5048(struct Projectile* p) {}

void Projectile20_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_080a5048);
  Projectile20_Update(p);
}

static const ProjectileFunc PTR_ARRAY_0836ba50[10];
static const ProjectileFunc PTR_ARRAY_0836ba78[10];

void Projectile20_Update(struct Projectile* p) {
  struct Entity* parent = (p->s).unk_28;
  if (parent->mode[0] > 1 && (p->s).mode[1] != 7) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
  PTR_ARRAY_0836ba50[(p->s).mode[1]](p);
  PTR_ARRAY_0836ba78[(p->s).mode[1]](p);
}

void Projectile20_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(3, &(p->s).coord);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080a5144(struct Projectile* p) {}

INCASM("asm/projectile/unk_20_post.inc");

void FUN_080a53e8(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0: {
      u8 a;
      u8 b;
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0x49, 0x01));
      a = (p->s).work[2];
      if ((p->s).flags & X_FLIP) {
        a = -a;
      }
      b = a - 0x40;
      (p->s).d.x = (COS(b) * 0x2C0) / 256;
      (p->s).d.y = (SIN(b) * 0x2C0) / 256;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      if (PushoutToUp1((p->s).coord.x, (p->s).coord.y + 0x1000) < 0) {
        (p->s).mode[2]++;
      }
      {
        s32 t = (p->s).work[2] + 0x10;
        (p->s).work[2] = t;
        (p->s).angle = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      (p->s).work[3] = 0x3C;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      {
        s32 t = (p->s).work[2] + 0x10;
        (p->s).work[2] = t;
        (p->s).angle = t;
      }
      UpdateMotionGraphic(&p->s);
      if (*(u32*)((u8*)q + 0xc0) & 4) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/projectile/unk_20_post_c.inc");

void FUN_080a569c(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0: {
      u8 on;
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).taskCol = 0x17;
      InitRotatableMotion(&p->s);
      on = (q->flags >> 4) & 1;
      SET_XFLIP(p, on);
      SetMotion(&p->s, MOTION(0x49, 0x01));
      (p->s).work[2] = 0;
      (p->s).work[3] = 0x10;
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      {
        s32 dx;
        s32 px;
        s32 dy;
        s32 py;
        dx = q->coord.x;
        px = (p->s).coord.x;
        dx -= px;
        dy = q->coord.y;
        py = (p->s).coord.y;
        dy -= py;
        (p->s).coord.x = px + dx / 6;
        (p->s).coord.y = py + dy / 6;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).work[2] = 0;
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      s32 t = (p->s).work[3] + 1;
      (p->s).work[3] = t;
      if ((u8)t > 0x13) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      if ((p->s).work[3] > 0x10) {
        (p->s).work[2] += 0x10;
      } else {
        (p->s).work[2] += (p->s).work[3];
      }
      (p->s).angle = (p->s).work[2];
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/projectile/unk_20_post_d.inc");

void FUN_080a4f3c(struct Projectile* p);

void FUN_080a5ac0(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      FUN_080a4f3c(p);
      (p->s).flags |= DISPLAY;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      u8 t;
      (p->s).coord.y -= (p->s).d.y;
      (p->s).d.y -= 0x40;
      (p->s).work[3] -= (p->s).work[2];
      t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      (p->s).angle = (p->s).work[3];
      break;
    }
  }
}

INCASM("asm/projectile/unk_20_postb.inc");

void Projectile20_Init(struct Projectile* p);
void Projectile20_Update(struct Projectile* p);
void Projectile20_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile20Routine = {
    [ENTITY_INIT] =      Projectile20_Init,
    [ENTITY_UPDATE] =    Projectile20_Update,
    [ENTITY_DIE] =       Projectile20_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a5144(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836ba50[10] = {
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
    FUN_080a5144,
};
// clang-format on

void FUN_080a5148(struct Projectile* p);
void FUN_080a51b4(struct Projectile* p);
void FUN_080a5290(struct Projectile* p);
void FUN_080a53e8(struct Projectile* p);
void FUN_080a54f8(struct Projectile* p);
void FUN_080a569c(struct Projectile* p);
void FUN_080a57ac(struct Projectile* p);
void FUN_080a598c(struct Projectile* p);
void FUN_080a5ac0(struct Projectile* p);
void FUN_080a5b28(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836ba78[10] = {
    FUN_080a5148,
    FUN_080a51b4,
    FUN_080a5290,
    FUN_080a53e8,
    FUN_080a54f8,
    FUN_080a569c,
    FUN_080a57ac,
    FUN_080a598c,
    FUN_080a5ac0,
    FUN_080a5b28,
};
// clang-format on

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(46)},
    },
};

static const u8 sInitModes[4] = {0, 0, 0, 0};
