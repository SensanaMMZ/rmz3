#include "stagerun.h"
#include "collision.h"
#include "global.h"
#include "projectile.h"

// MinigameCopyX?

static const ProjectileFunc PTR_ARRAY_0836d7cc[4];

struct Projectile* FUN_080b18d4(struct Coord* c1, struct Coord* c2, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = a2;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

struct Projectile* FUN_080b1934(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080b1990(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080b19ec(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

INCASM("asm/projectile/unk_45_p1_p5.inc");

void FUN_080b1b28(struct Projectile* p) {
  (PTR_ARRAY_0836d7cc[(p->s).mode[1]])(p);
}

void FUN_080b1b40(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_45_p2_p1a.inc");

extern const struct Collision Collision_ARRAY_0836d7dc[];
void FUN_080b2178(struct Body* body);

void FUN_080b1b7c(struct Projectile* p) {
  if (*(u8*)((u8*)p + 0xbc) != 0) {
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
    goto die;
  }
  if (!((p->body).status & 4)) {
    s32 t = (p->s).work[2] - 1;
    (p->s).work[2] = t;
    if ((t << 24) == 0) {
    die:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      return;
    }
  }
  {
  register s32 m asm("r6");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register struct Body* b asm("r4");
      b = NULL;
      (p->s).work[2] = 0x3C;
      InitNonAffineMotion(&p->s);
      (p->s).angle = m;
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = 0x100;
      if ((p->s).work[1] == 0) {
        (p->s).flags |= COLLIDABLE;
        b = &p->body;
        InitBody(b, &Collision_ARRAY_0836d7dc[0], &(p->s).coord, 1);
        b->parent = (void*)p;
        b->fn = (void*)m;
        SetMotion(&p->s, 0x5B00);
      } else if ((p->s).work[1] == 1) {
        (p->s).flags |= COLLIDABLE;
        b = &p->body;
        InitBody(b, &Collision_ARRAY_0836d7dc[1], &(p->s).coord, 1);
        b->parent = (void*)p;
        b->fn = (void*)m;
        SetMotion(&p->s, 0x5C00);
      } else {
        b = &p->body;
        if ((p->s).work[1] == 2) {
          (p->s).flags |= COLLIDABLE;
          InitBody(b, &Collision_ARRAY_0836d7dc[2], &(p->s).coord, 1);
          b->parent = (void*)p;
          b->fn = (void*)m;
          SetMotion(&p->s, 0x5F00);
        }
      }
      b->fn = (void*)FUN_080b2178;
      {
        register s32 dz asm("r0");
        dz = 0;
        asm("" : "+r"(dz));
        (p->s).d.y = dz;
      }
      (p->s).d.x = 0x500;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      break;
  }
  }
}

INCASM("asm/projectile/unk_45_p2_p1b.inc");

static const struct Collision Collision_ARRAY_0836d7dc[8];

// 0x080B1F00
void FUN_080b1f00(struct Projectile* p) {
  if (*(s16*)((u8*)(p->s).unk_28 + 4) == 2) {
    (p->s).work[2] = 0xFF;
  }
  if ((u8)--(p->s).work[2] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      s32 y;
      InitNonAffineMotion(&p->s);
      y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).coord.y = y;
      if (y <= 0x117FF) {
        goto die;
      }
      if (y > 0x13BFF) {
        goto land;
      }
      {
        FUN_0800a31c((p->s).coord.x, y - 0x800);
        FUN_0800a22c((p->s).coord.x, (p->s).coord.y - 0x800);
        if (FUN_08009f6c((p->s).coord.x - 0x2000, (p->s).coord.y - 0x800) > 0x13C00) {
          goto die;
        }
        if (FUN_08009f6c((p->s).coord.x + 0x2000, (p->s).coord.y - 0x800) <= 0x13C00) {
          goto land;
        }
      }
    die:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      (p->s).flags &= ~DISPLAY;
      return;
    land : {
      s32 z;
      (p->s).taskCol = 0x12;
      z = 0;
      (p->s).flags |= COLLIDABLE;
      {
        struct Body* body = &p->body;
        InitBody(body, &Collision_ARRAY_0836d7dc[6], &(p->s).coord, 1);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (void*)z;
      }
      SetMotion(&p->s, MOTION(0xF3, 0x00));
      (p->s).work[2] = 0xB4;
      (p->s).mode[2]++;
    }
      FALLTHROUGH;
    }
    case 1:
      if (((p->s).unk_28)->mode[1] == 1) {
        (p->s).coord.x += -0x3C000;
      }
      UpdateMotionGraphic(&p->s);
      CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord);
      break;
  }
}

void FUN_080b2204(struct Body* body);
extern const struct Collision Collision_ARRAY_0836d7dc[];

void FUN_080b2044(struct Projectile* p) {
  register s32 z6 asm("r6");
  if (*(s16*)((u8*)(p->s).unk_28 + 4) == 2) {
    (p->s).work[2] = 0xFF;
  }
  {
    s32 t = (p->s).work[2] - 1;
    z6 = 0;
    (p->s).work[2] = t;
    if ((t << 24) == 0) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      return;
    }
  }
  if (*((u8*)p + 0xbc) == 1 && (p->s).mode[2] != 2) {
    register s32 z4 asm("r4");
    struct Entity* e = (p->s).unk_28;
    u16* cnt = (u16*)((u8*)e + 0xe);
    s32 c1 = *cnt + 1;
    z4 = 0;
    *cnt = c1;
    PlaySound(0x137);
    (p->s).flags &= 0xFE;
    (p->body).status = z6;
    (p->body).prevStatus = z6;
    (p->body).invincibleTime = z4;
    (p->s).flags &= ~COLLIDABLE;
    (p->s).work[2] = 0x10;
    (p->s).mode[2] = 2;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      struct Body* body;
      InitNonAffineMotion(&p->s);
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &Collision_ARRAY_0836d7dc[7], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (BodyFunc)FUN_080b2204;
      SetMotion(&p->s, 0xAA04);
      (p->s).work[2] = 0xB4;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      if (((p->s).unk_28)->mode[1] == 1) {
        (p->s).coord.x += -0x3C000;
      }
      UpdateMotionGraphic(&p->s);
      {
        struct Camera* cam = &gStageRun.vm.camera;
        CalcFromCamera(cam, &(p->s).coord);
      }
      break;
    case 2:
      {
        register s32 wv asm("r0");
        register s32 c3 asm("r1");
        wv = (p->s).work[2];
        c3 = 3;
        wv &= c3;
        if (wv == 0) {
          PlaySound(0x22);
        }
      }
      if (((p->s).unk_28)->mode[1] == 1) {
        (p->s).coord.x += -0x3C000;
      }
      break;
  }
}


// 1 insn from matching: retail keeps the work[1] load in r0 and copies it
// into the a register; agbcc coalesces the copy away (allocation tie).
NON_MATCH void FUN_080b2178(struct Body* body) {
#if MODERN
  u8 win = 0;
  struct CollidableEntity* parent = body->parent;
  struct CollidableEntity* other = (body->enemy)->parent;
  u32 a;
  if (((struct Entity*)parent)->work[1] == 0 && ((struct Entity*)other)->work[1] == 2) {
    win = 1;
  }
  a = ((struct Entity*)parent)->work[1];
  if (a == 1 && ((struct Entity*)other)->work[1] == 0) {
    win = 1;
  }
  if (a == 2 && ((struct Entity*)other)->work[1] == 1) {
    win = 1;
  }
  *(u8*)((u8*)parent + 0xbc) = 1;
  if (win == 1) {
    *(u8*)((u8*)parent + 0xbc) = win;
  }
#else
  INCCODE("asm/projectile/unk_45_2178.inc");
#endif
}

// 1 insn from matching: retail keeps the work[1] load in r0 and copies it
// into the a register; agbcc coalesces the copy away (allocation tie).
NON_MATCH void FUN_080b21c0(struct Body* body) {
#if MODERN
  u8 win = 0;
  struct CollidableEntity* parent = body->parent;
  struct CollidableEntity* other = (body->enemy)->parent;
  u32 a;
  if (((struct Entity*)other)->work[1] == 0 && ((struct Entity*)parent)->work[1] == 2) {
    win = 1;
  }
  a = ((struct Entity*)other)->work[1];
  if (a == 1 && ((struct Entity*)parent)->work[1] == 0) {
    win = 1;
  }
  if (a == 2 && ((struct Entity*)parent)->work[1] == 1) {
    win = 1;
  }
  if (win == 1) {
    *(u8*)((u8*)parent + 0xbc) = win;
  }
#else
  INCCODE("asm/projectile/unk_45_21c0.inc");
#endif
}

void FUN_080b2204(struct Body* body) {
  struct CollidableEntity* parent = body->parent;
  if ((body->enemy->processing)->faction == 0) {
    *(u8*)((u8*)parent + 0xbc) = 1;
  }
}

void FUN_080b1a48(struct Projectile* p);
void FUN_080b1b28(struct Projectile* p);
void FUN_080b1b40(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile45Routine = {
    [ENTITY_INIT] =      FUN_080b1a48,
    [ENTITY_UPDATE] =    FUN_080b1b28,
    [ENTITY_DIE] =       FUN_080b1b40,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b1b7c(struct Projectile* p);
void FUN_080b1cbc(struct Projectile* p);
void FUN_080b1f00(struct Projectile* p);
void FUN_080b2044(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d7cc[4] = {
    FUN_080b1b7c,
    FUN_080b1cbc,
    FUN_080b1f00,
    FUN_080b2044,
};
// clang-format on

static const struct Collision Collision_ARRAY_0836d7dc[8] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 2,
      element : ELEMENT_FLAME,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 2,
      element : ELEMENT_THUNDER,
      remaining : 0,
      layer : 0x00000002,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 2,
      element : ELEMENT_ICE,
      remaining : 0,
      layer : 0x00000008,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0x000A5294,
      range : {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0x0046318C,
      range : {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0x004C6318,
      range : {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(22), PIXEL(28), PIXEL(44)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
};
