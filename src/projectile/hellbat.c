#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc* const sUpdates[5];

struct Projectile* createBat(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    p->work[1] = a2;
    p->work[2] = a3;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* createEchoWave(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a14dc(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a1538(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080a1594(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 15);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    p->work[1] = a2;
    (p->s).coord = *c;
    (p->s).unk_28 = e;
  }
  return p;
}

static const struct Collision sCollisions[9];
void Projectile15_Update(struct Projectile* p);

void Projectile15_Init(struct Projectile* p) {
  s32 z4;
  (p->s).work[2] = 0xFF;
  {
    register s32 w0 asm("r5");
    w0 = (p->s).work[0];
    if (w0 == 0) {
      struct Body* body;
      InitNonAffineMotion(&p->s);
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[0], &(p->s).coord, 4);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)(u32)w0;
    } else if (w0 == 1) {
      struct Body* body;
      s32 z5;
      InitNonAffineMotion(&p->s);
      z5 = 0;
      (p->s).work[2] = z5;
      *(u32*)((u8*)p + 0xbc) = z5;
      InitNonAffineMotion(&p->s);
      (p->s).angle = z5;
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = 0x100;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[5], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    } else if (w0 == 2) {
      struct Body* body;
      s32 z5;
      InitNonAffineMotion(&p->s);
      {
        register u8 f0 asm("r1");
        register s32 d4 asm("r0");
        f0 = (p->s).flags;
        d4 = COLLIDABLE;
        z5 = 0;
        d4 |= f0;
        (p->s).flags = d4;
      }
      body = &p->body;
      InitBody(body, &sCollisions[2], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    } else if (w0 == 3) {
      struct Body* body;
      s32 z5;
      InitScalerotMotion1(&p->s);
      {
        u8* aa = (u8*)p + 0x24;
        z5 = 0;
        *aa = z5;
      }
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = 0x100;
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[3], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    } else if (w0 == 4) {
      struct Body* body;
      s32 z5;
      InitNonAffineMotion(&p->s);
      {
        register u8 f0 asm("r1");
        register s32 d4 asm("r0");
        f0 = (p->s).flags;
        d4 = COLLIDABLE;
        z5 = 0;
        d4 |= f0;
        (p->s).flags = d4;
      }
      body = &p->body;
      InitBody(body, &sCollisions[3], &(p->s).coord, 1);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
    }
  }
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    z4 = 0;
    d0 |= f0;
    d0 |= FLIPABLE;
    (p->s).flags = d0;
  }
  ResetDynamicMotion(&p->s);
  {
    u32 tb = (u32)gProjectileFnTable;
    const ProjectileRoutine** ta = (const ProjectileRoutine**)(tb + (p->s).id * 4);
    s32 one = 1;
    *(u32*)&(p->s).mode[0] = one;
    (p->s).onUpdate = (void*)(**ta)[ENTITY_UPDATE];
    (p->s).mode[1] = one;
  }
  (p->s).mode[2] = z4;
  (p->s).mode[3] = z4;
  Projectile15_Update(p);
}

void Projectile15_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]][(p->s).mode[1]])(p);
}

void Projectile15_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080a176c(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

INCASM("asm/projectile/hellbat_p2_p1_p1.inc");

void FUN_080a1a10(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

INCASM("asm/projectile/hellbat_p2_p1_p2.inc");

void FUN_080a1f10(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_080a1f1c(struct Projectile* p) {
  s32 v, a, hit;
  if (((p->s).unk_28)->mode[0] <= 1) {
    if (--(p->s).work[2] == 0) {
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      return;
    }
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 t asm("r0");
      (p->s).unk_coord.x = 0;
      if ((((p->s).unk_28)->flags & 0x10) == 0) {
        t = -0x12;
      } else {
        t = 0x12;
      }
      (p->s).d.x = t;
    }
      (p->s).work[2] = 0xC8;
      SetMotion(&p->s, MOTION(0xA9, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      v = (p->s).unk_coord.x + (p->s).d.x;
      (p->s).unk_coord.x = v;
      a = v;
      if (v < 0) {
        a = -v;
      }
      if (a > 0x300) {
        (p->s).unk_coord.x = v - (p->s).d.x;
      }
      (p->s).coord.x += (p->s).unk_coord.x;
      if (((p->s).unk_28)->mode[0] > 1) {
        if ((p->s).unk_coord.x > 0) {
          hit = PushoutToLeft1((p->s).coord.x, (p->s).coord.y);
        } else {
          hit = PushoutToRight1((p->s).coord.x, (p->s).coord.y);
        }
        if (hit != 0) {
          SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
        }
      } else {
        if ((p->s).unk_coord.x > 0) {
          hit = PushoutToLeft1((p->s).coord.x, (p->s).coord.y);
        } else {
          hit = PushoutToRight1((p->s).coord.x, (p->s).coord.y);
        }
        if (hit != 0) {
          (p->s).coord.x += hit;
          (p->s).unk_coord.x = -(p->s).unk_coord.x;
          (p->s).d.x = -(p->s).d.x;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080a2020(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

INCASM("asm/projectile/hellbat_p3_p1.inc");

void FUN_080a22ec(struct Projectile* p) {
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
}

void FUN_080a22f8(struct Projectile* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        (p->s).flags |= 1;
        SetMotion(&p->s, 0xA905);
        SetDDP(&p->body, &sCollisions[4]);
        (p->s).flags &= 0xDF;
        *((u8*)p + 0x4d) = m;
        {
          u8* oa = (u8*)p + 0x4a;
          s32 ov = *oa;
          s32 m21 = -0x21;
          m21 &= ov;
          *oa = m21;
        }
        if ((p->s).d.x > 0) {
          (p->s).coord.x += -0x1400;
        } else {
          (p->s).coord.x += 0x1400;
        }
        (p->s).unk_coord.x = 0;
        (p->s).work[3] = 0;
        (p->s).mode[2]++;
        // fallthrough
      case 1: {
        (p->s).coord.x += (p->s).d.x;
        {
          s32 acc = (p->s).unk_coord.x + (p->s).d.x;
          (p->s).unk_coord.x = acc;
          if (*((u8*)p + 0xb5) == 0) {
            s32 a = acc;
            if (a < 0) {
              a = -a;
            }
            if (a > 0x1400) {
              if ((p->s).work[3] == 0) {
                struct Projectile* q;
                (p->s).work[3] = 1;
                q = FUN_080a1594(&p->s, &(p->s).coord, 1);
                (q->s).d.x = (p->s).d.x;
              }
            }
          }
        }
        UpdateMotionGraphic(&p->s);
        {
          s32 push;
          if ((p->s).d.x > 0) {
            push = PushoutToLeft1((p->s).coord.x + 0x400, (p->s).coord.y);
          } else {
            push = PushoutToRight1((p->s).coord.x - 0x400, (p->s).coord.y);
          }
          if (push != 0) {
            (p->s).coord.x += push;
            (p->s).d.y = -0x300;
            (p->s).mode[2]++;
          }
        }
        break;
      }
      case 2:
        (p->s).coord.y += (p->s).d.y;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

void Projectile15_Init(struct Projectile* p);
void Projectile15_Update(struct Projectile* p);
void Projectile15_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gHellbatProjectileRoutine = {
    [ENTITY_INIT] =      Projectile15_Init,
    [ENTITY_UPDATE] =    Projectile15_Update,
    [ENTITY_DIE] =       Projectile15_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a176c(struct Projectile* p);
void FUN_080a1778(struct Projectile* p);

static const ProjectileFunc sUpdates1[2] = {
    FUN_080a176c,
    FUN_080a1778,
};

void FUN_080a1a10(struct Projectile* p);
void FUN_080a1a1c(struct Projectile* p);

static const ProjectileFunc sUpdates2[2] = {
    FUN_080a1a10,
    FUN_080a1a1c,
};

void FUN_080a1f10(struct Projectile* p);
void FUN_080a1f1c(struct Projectile* p);

static const ProjectileFunc sUpdates3[2] = {
    FUN_080a1f10,
    FUN_080a1f1c,
};

void FUN_080a2020(struct Projectile* p);
void FUN_080a202c(struct Projectile* p);

static const ProjectileFunc sUpdates4[2] = {
    FUN_080a2020,
    FUN_080a202c,
};

void FUN_080a22ec(struct Projectile* p);
void FUN_080a22f8(struct Projectile* p);

static const ProjectileFunc sUpdates5[2] = {
    FUN_080a22ec,
    FUN_080a22f8,
};

// clang-format off
static const ProjectileFunc*const sUpdates[5] = {
    sUpdates1,
    sUpdates2,
    sUpdates3,
    sUpdates4,
    sUpdates5,
};
// clang-format on

static const struct Collision sCollisions[9] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(0), -PIXEL(2), PIXEL(20), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(2), PIXEL(20), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      element : ELEMENT_THUNDER,
      remaining : 0,
      layer : 0x00000002,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(11), PIXEL(30)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(10)},
    },
};
