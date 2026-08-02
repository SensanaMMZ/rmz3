#include "collision.h"
#include "global.h"
#include "projectile.h"

void OmegaZXProjectile_Init(struct Projectile* p);
void OmegaZXProjectile_Update(struct Projectile* p);
void OmegaZXProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gOmegaZXProjectileRoutine = {
    [ENTITY_INIT] =      OmegaZXProjectile_Init,
    [ENTITY_UPDATE] =    OmegaZXProjectile_Update,
    [ENTITY_DIE] =       OmegaZXProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

struct Projectile* FUN_080afe84(struct Entity* parent, struct Coord* c, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = parent;
  }
  return p;
}

struct Projectile* FUN_080afedc(struct Entity* parent, struct Coord* c, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = parent;
  }
  return p;
}

struct Projectile* FUN_080aff34(struct Entity* parent, struct Coord* c) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = parent;
  }
  return p;
}

struct Projectile* FUN_080aff88(struct Entity* parent, struct Coord* c, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 5;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = parent;
  }
  return p;
}

static const ProjectileFunc sUpdates[9];

struct Projectile* FUN_080affe4(struct Entity* parent, struct Coord* c, u16 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).work[1] = a3;
    *(u16*)((u8*)p + 0xbc) = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = parent;
  }
  return p;
}

struct Projectile* FUN_080b0048(struct Entity* parent, struct Coord* c) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 7;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = parent;
  }
  return p;
}

struct Projectile* FUN_080b009c(struct Entity* parent) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 41);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 8;
    (p->s).unk_28 = parent;
  }
  return p;
}

void OmegaZXProjectile_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = (p->s).work[0];
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  (p->s).work[2] = 0xFF;
  OmegaZXProjectile_Update(p);
}

void OmegaZXProjectile_Update(struct Projectile* p) {
  (sUpdates[(p->s).mode[1]])(p);
}

void OmegaZXProjectile_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

#include "vfx.h"

static const struct Collision sCollisions[26];

// 0x080b0168
void FUN_080b0168(struct Projectile* p) {
  s32 t = (p->s).work[2] - 1;
  (p->s).work[2] = t;
  if ((t << 24) == 0) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0: {
        struct Body* body;
        InitNonAffineMotion(&p->s);
        ResetDynamicMotion(&p->s);
        {
          register u8 fv asm("r0");
          register u8 k asm("r1");
          fv = (p->s).flags;
          k = FLIPABLE;
          fv |= k;
          asm volatile("movs %0, #0" : "=l"(k));
          fv |= k;
          k = DISPLAY;
          fv |= k;
          k = COLLIDABLE;
          fv |= k;
          (p->s).flags = fv;
        }
        body = &p->body;
        InitBody(body, &sCollisions[17], &(p->s).coord, 2);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (BodyFunc)m;
        SetMotion(&p->s, MOTION(0xB8, 0x00));
        (p->s).d.y = m;
        (p->s).d.x = -0x500;
        (p->s).work[2] = 0x78;
        (p->s).mode[2]++;
        FALLTHROUGH;
      }
      case 1:
        (p->s).coord.x += (p->s).d.x;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}


// 0x080B0214
void FUN_080b0214(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  u8 m;
  if (q->mode[0] > 1) {
    goto die;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8 fv asm("r0");
      register u8 fl asm("r1");
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      fl = (p->s).flags;
      fv = 2;
      fv |= fl;
      fl = 1;
      fv |= fl;
      (p->s).flags = fv;
      (p->s).taskCol = 0x11;
      (p->s).work[2] = m;
      SetMotion(&p->s, 0xB900);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      struct Entity* q1 = *(struct Entity* volatile*)&(p->s).unk_28;
      (p->s).coord.x = q1->coord.x;
      (p->s).coord.y = q1->coord.y;
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->mode[1] == 5) {
        return;
      }
      goto clear;
    }
    case 2:
      (p->s).coord.x = q->coord.x;
      (p->s).coord.y = q->coord.y;
      UpdateMotionGraphic(&p->s);
      {
        register s32 w asm("r1");
        register s32 dec asm("r0");
        w = (p->s).work[2];
        dec = w;
        dec += 0xFF;
        (p->s).work[2] = dec;
        {
          register s32 k1 asm("r0");
          k1 = 1;
          k1 &= w;
          if (k1 != 0) {
            register u8 fl asm("r1");
            register u8 fv asm("r0");
            fl = (p->s).flags;
            fv = 1;
            fv |= fl;
            (p->s).flags = fv;
          } else {
            register u8 fl2 asm("r1");
            register u8 fv2 asm("r0");
            fl2 = (p->s).flags;
            asm("" : "+r"(fl2));
            fv2 = 0xFE;
            fv2 &= fl2;
            (p->s).flags = fv2;
          }
        }
      }
      if ((p->s).work[2] != 0) {
        return;
      }
    clear:
      (p->s).flags &= 0xFE;
    die:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}


// 0x080b02dc
void FUN_080b02dc(struct Projectile* p) {
  u8 m;
  if (((p->s).unk_28)->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      (p->s).flags |= FLIPABLE;
      (p->s).flags |= DISPLAY;
      (p->s).work[2] = m;
      SetMotion(&p->s, MOTION(0xB9, 0x02));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      struct Entity* q;
      register u8 t asm("r1") = (p->s).work[2];
      (p->s).work[2] = t + 1;
      if (t & 1) {
        u8 f = DISPLAY | (p->s).flags;
        (p->s).flags = f;
      } else {
        u8 f = ~DISPLAY & (p->s).flags;
        (p->s).flags = f;
      }
      q = (p->s).unk_28;
      (p->s).coord.x = (q->coord).x;
      (p->s).coord.y = (q->coord).y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/projectile/omega_zx_post_p2b.inc");

#include "stagerun.h"
#include "camera.h"

// 0x080b10b8
void FUN_080b10b8(struct Projectile* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      struct Body* body;
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      (p->s).flags |= COLLIDABLE;
      body = &p->body;
      InitBody(body, &sCollisions[25], &(p->s).coord, 2);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (BodyFunc)m;
      {
        register u8 fv asm("r0");
        register u8 k asm("r1");
        fv = (p->s).flags;
        k = FLIPABLE;
        fv |= k;
        k = DISPLAY;
        fv |= k;
        (p->s).flags = fv;
      }
      SetMotion(&p->s, MOTION(0xBB, 0x06));
      (p->s).work[2] = 0x14;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        (p->s).coord.y = cam->viewport.y + 0x3FFF;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2] = 0xa;
      break;
    case 0xa:
      SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

INCASM("asm/projectile/omega_zx_post_p2b_b.inc");

void FUN_080b0168(struct Projectile* p);
void FUN_080b0214(struct Projectile* p);
void FUN_080b02dc(struct Projectile* p);
void omega2_080b0370(struct Projectile* p);
void omega2_080b07c8(struct Projectile* p);
void FUN_080b0bb0(struct Projectile* p);
void omega2_080b0ca8(struct Projectile* p);
void FUN_080b10b8(struct Projectile* p);
void FUN_080b116c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates[9] = {
    FUN_080b0168,
    FUN_080b0214,
    FUN_080b02dc,
    omega2_080b0370,
    omega2_080b07c8,
    FUN_080b0bb0,
    omega2_080b0ca8,
    FUN_080b10b8,
    FUN_080b116c,
};
// clang-format on

static const struct Collision sCollisions[26] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(30)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(6)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(4)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(2)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(1)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      nature : BODY_NATURE_B7,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(34), PIXEL(34)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      unk_0a : 0x21,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(30), PIXEL(30)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 255,
      unk_0a : 0x21,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(48), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      unk_0a : 0x21,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(48), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(86), PIXEL(40), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      nature : BODY_NATURE_B7,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      nature : BODY_NATURE_B7,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      nature : BODY_NATURE_B7,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(50), PIXEL(27)},
    },
};
