#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "vfx.h"

static const ProjectileFunc sUpdates[4];
static const struct Collision sCollisions[5];

struct Projectile* FUN_080ac818(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
    (p->s).work[1] = 0;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac880(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 1;
    (p->s).work[1] = 0;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac8e8(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
    (p->s).work[1] = 1;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac950(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 1;
    (p->s).work[1] = 1;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080ac9b4(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 34);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 2;
    (p->prevCoord).c.x = prevX;
    (p->prevCoord).c.y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

void Projectile34_Update(struct Projectile* p);

// 0x080ACA18
void Projectile34_Init(struct Projectile* p) {
  register u8 f asm("r1");
  register s32 z6 asm("r6");
  s32 w0;
  InitNonAffineMotion(&p->s);
  {
    register s32 k asm("r0");
    register s32 z2 asm("r2");
    f = (p->s).flags;
    k = 1;
    z2 = 0;
    asm volatile("" : "+r"(z2));
    z6 = 0;
    f |= k;
    k = 2;
    f |= k;
    asm volatile("" : "+r"(z2));
    f |= z2;
    (p->s).flags = f;
  }
  w0 = (p->s).work[0];
  if (w0 == 2) {
    struct Body* body;
    f |= COLLIDABLE;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C728, &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z6;
    {
      u32 tbl = (u32)gProjectileFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = w0;
  } else if ((p->s).work[1] == 0) {
    struct Body* body;
    f |= COLLIDABLE;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C728, &(p->s).coord, 1);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z6;
    {
      u32 tbl = (u32)gProjectileFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    asm volatile("strb %0, [%1, #0xd]" :: "l"(z6), "l"(p) : "memory");
  } else {
    struct Body* body;
    f |= COLLIDABLE;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C728, &(p->s).coord, 1);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z6;
    {
      u32 tbl = (u32)gProjectileFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = 3;
  }
  (p->s).mode[2] = z6;
  (p->s).mode[3] = z6;
  Projectile34_Update(p);
}

void Projectile34_Update(struct Projectile* p) {
  (sUpdates[(p->s).mode[1]])(p);
}

void Projectile34_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080acb54(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    switch ((p->s).mode[2]) {
      case 0:
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0xa00);
        } else {
          SetMotion(&p->s, 0xa03);
        }
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        UpdateMotionGraphic(&p->s);
        break;
    }
    if ((p->prevCoord).c.y == 0 || --(p->prevCoord).c.y == 0) {
      (p->s).work[2] = 0x7f;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_080acbe0(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else if (--(p->s).work[2] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0xa01);
          SetDDP(&p->body, &sCollisions[1]);
          (p->s).d.y = (p->prevCoord).c.x;
          (p->s).d.x = m;
        } else {
          SetMotion(&p->s, 0xa04);
          SetDDP(&p->body, &sCollisions[2]);
          (p->s).d.x = -(p->prevCoord).c.x;
          (p->s).d.y = m;
        }
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).work[3] = (RNG_0202f388 >> 16) & 1;
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        UpdateMotionGraphic(&p->s);
        if ((p->s).motion.state == 3) {
          (p->s).flags |= DISPLAY;
          (p->s).mode[2]++;
        }
        break;
      case 2:
        (p->s).coord.x += (p->s).d.x;
        (p->s).coord.y += (p->s).d.y;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

INCASM("asm/projectile/unk_34_post_p2a.inc");

void FUN_080acea0(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8* a = (u8*)p + 0x8c;
      s32 z = 0;
      *(u32*)a = z;
      asm("" : "+r"(a));
      a += 4;
      *(u32*)a = z;
      asm("" : "+r"(a));
      a += 4;
      asm("" : "+r"(a));
      *a = z;
      (p->s).flags &= 0xFB;
      if ((p->s).work[0] == 0) {
        SetMotion(&p->s, 0xA00);
      } else {
        SetMotion(&p->s, 0xA03);
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      UpdateMotionGraphic(&p->s);
      {
        s32* w = (s32*)((u8*)p + 0xbc);
        s32 v = *w;
        if (v != 0) {
          v -= 1;
          *w = v;
          if (v != 0) {
            break;
          }
        }
      }
      (p->s).work[2] = 0x7F;
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      u8 w0 = (p->s).work[0];
      if (w0 == 0) {
        SetMotion(&p->s, 0xA01);
        SetDDP(&p->body, &sCollisions[1]);
        (p->s).d.y = *(s32*)((u8*)p + 0xb8);
        (p->s).d.x = w0;
      } else {
        SetMotion(&p->s, 0xA04);
        SetDDP(&p->body, &sCollisions[2]);
        (p->s).d.x = -*(s32*)((u8*)p + 0xb8);
        (p->s).d.y = 0;
      }
      (p->s).work[3] = RANDOM(RNG_0202f388) & 1;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).flags |= 1;
      (p->s).work[2] = 0xFF;
      (p->s).mode[2]++;
      break;
    case 4:
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void Projectile34_Init(struct Projectile* p);
void Projectile34_Update(struct Projectile* p);
void Projectile34_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile34Routine = {
    [ENTITY_INIT] =      Projectile34_Init,
    [ENTITY_UPDATE] =    Projectile34_Update,
    [ENTITY_DIE] =       Projectile34_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080acb54(struct Projectile* p);
void FUN_080acbe0(struct Projectile* p);
void FUN_080accf0(struct Projectile* p);
void FUN_080acea0(struct Projectile* p);

static const ProjectileFunc sUpdates[4] = {
    FUN_080acb54,
    FUN_080acbe0,
    FUN_080accf0,
    FUN_080acea0,
};

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(48), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      nature : 0x80,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(2), PIXEL(26), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(2), PIXEL(26), PIXEL(20)},
    },
};

static const s32 s32_ARRAY_0836c7a0[32] = {
    0x00000180, -0x00000340, -0x00000220, -0x00000260, -0x00000220, -0x00000300, 0x000002C0, -0x00000260, -0x00000180, -0x00000340, -0x00000200, -0x00000280, 0x00000160, -0x000001F0, 0x00000260, -0x00000280, 0x00000200, -0x00000440, 0x00000120, -0x000002A0, 0x00000120, -0x00000340, -0x000000B0, -0x000002A0, -0x00000200, -0x00000440, 0x00000120, -0x000002A0, 0x00000120, -0x00000340, -0x000000B0, -0x000002A0,
};

static const s32* const PTR_ARRAY_0836c820[4] = {
    &s32_ARRAY_0836c7a0[0],
    &s32_ARRAY_0836c7a0[8],
    &s32_ARRAY_0836c7a0[16],
    &s32_ARRAY_0836c7a0[24],
};
