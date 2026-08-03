#include "collision.h"
#include "enemy.h"
#include "element.h"
#include "global.h"
#include "motion.h"
#include "story.h"
#include "physics.h"
#include "zero.h"
#include "sound.h"
#include "vfx.h"

static void Enemy14_Init(struct Enemy* p);
void Enemy14_Update(struct Enemy* p);
void Enemy14_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gTopGabyoallRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Enemy14_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Enemy14_Update,
    [ENTITY_DIE] =       (EnemyFunc)Enemy14_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateTopGabyoall(struct Coord* c, u8 r1, u8 r2) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_TOP_GABYOALL);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = r1;
    p->work[1] = r2;
    p->coord = *c;
    return p;
  } else {
    return NULL;
  }
}

// --------------------------------------------

void FUN_0806f5d0(struct Enemy* p);
void FUN_0806f6cc(struct Enemy* p);
void FUN_0806f7dc(struct Enemy* p);
void FUN_0806f89c(struct Enemy* p);

static void Enemy14_Init(struct Enemy* p) {
  static const EnemyFunc sInitializers[4] = {
      (EnemyFunc)FUN_0806f5d0,
      (EnemyFunc)FUN_0806f6cc,
      (EnemyFunc)FUN_0806f7dc,
      (EnemyFunc)FUN_0806f89c,
  };
  (sInitializers[(p->s).work[0]])((void*)p);
}

// --------------------------------------------

void FUN_0806f964(struct Enemy* p);
void FUN_0806fb08(struct Enemy* p);
void FUN_0806fc78(struct Enemy* p);
void FUN_0806fe38(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08366960[4] = {
    (EnemyFunc)FUN_0806f964,
    (EnemyFunc)FUN_0806fb08,
    (EnemyFunc)FUN_0806fc78,
    (EnemyFunc)FUN_0806fe38,
};

// --------------------------------------------

static const struct Collision sCollisions[];
static const struct Coord sElementCoords[4];

void Enemy14_Update(struct Enemy* p) {
  if ((p->s).work[1] != 2) {
    if (gCurStory.s.gameflags[4] & 0x40) {
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
  } else {
    if (pZero2 != NULL) {
      if (*(u16*)((u8*)pZero2 + 0x216) & 0x8000) {
        goto end;
      }
    }
  }
  if (*((u8*)p + 0xc2) != 0) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    return;
  }
  {
    register struct VFX** slot asm("r6");
    register u32 mv asm("r1");
    mv = (u16)((p->s).motionID) << 8;
    {
      register u32 st asm("r0");
      st = (p->s).motion.step;
      mv |= st;
      st = 0x1503;
      slot = (struct VFX**)((u8*)p + 0xbc);
      if (mv != st && ((p->body).status & 1)) {
      if (*slot == NULL) {
        *slot = ApplyElementEffect(0, &p->s, &sElementCoords[(p->s).work[0]]);
        if (*slot == NULL) {
          goto frozen;
        }
        SetDDP(&p->body, &sCollisions[1 + (u8)((p->s).work[0] & 2)]);
      } else {
        goto setm;
      }
    }
    if (*slot == NULL) {
      goto frozen;
    }
    }
  setm:
    SetMotion(&p->s, 0x1500);
    UpdateMotionGraphic(&p->s);
    if (isKilled((struct Entity*)*slot)) {
      *slot = NULL;
      SetDDP(&p->body, &sCollisions[(u8)((p->s).work[0] & 2)]);
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
    return;
  frozen:
    if (!IsFrozen(&p->s)) {
      (PTR_ARRAY_08366960[(p->s).work[0]])(p);
    }
  }
end:;
}

void Enemy14_Die(struct Enemy* p) {
  CreateSmoke(1, &(p->s).coord);
  PlaySound(0x2a);
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

static const struct Collision sCollisions[];
void FUN_08070000(struct Body* body, struct Coord* r1, struct Coord* r2);

// 0x0806F5D0
void FUN_0806f5d0(struct Enemy* p) {
  register s32 z6 asm("r6");
  s32 z7;
  InitNonAffineMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    z6 = 0;
    z7 = 0;
    d0 |= f0;
    d0 |= FLIPABLE;
    (p->s).flags = d0;
  }
  SetMotion(&p->s, MOTION(0x15, 0x00));
  UpdateMotionGraphic(&p->s);
  {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 0x100);
    body->parent = (struct CollidableEntity*)p;
    body->fn = FUN_08070000;
  }
  *(u32*)((u8*)p + 0xbc) = z7;
  if ((pZero2->s).coord.x > (p->s).coord.x) {
    register s32 one asm("r2");
    u8* a;
    s32 msk;
    (p->s).d.x = 0x80;
    one = 1;
    (p->s).flags |= X_FLIP;
    ((p->s).spr).xflip = one;
    a = (u8*)p + 0x4a;
    {
      register s32 m asm("r2");
      register u8 b asm("r1");
      m = 0x10;
      asm("" : "+r"(m));
      b = *a;
      msk = -0x11;
      msk &= b;
      msk |= m;
    }
    *a = msk;
  } else {
    u8* a;
    s32 msk;
    (p->s).d.x = -0x80;
    (p->s).flags &= 0xEF;
    ((p->s).spr).xflip = z7;
    a = (u8*)p + 0x4a;
    {
      register u8 b asm("r1");
      b = *a;
      msk = -0x11;
      msk &= b;
    }
    *a = msk;
  }
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  *(s32*)((u8*)p + 0xb4) = (p->s).coord.x;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  {
    u8* c;
    s32 z2;
    c = (u8*)p + 0xc2;
    z2 = 0;
    *c = z2;
    (p->s).work[2] = z2;
    SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = z2;
    (p->s).mode[2] = 1;
  }
  asm volatile("" ::"r"(z6));
  Enemy14_Update(p);
}

void FUN_0806f6cc(struct Enemy* p) {
  register s32 z6 asm("r6");
  s32 z7;
  u8* a;
  InitNonAffineMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    z6 = 0;
    z7 = 0;
    d0 |= f0;
    d0 |= FLIPABLE;
    (p->s).flags = d0;
  }
  SetMotion(&p->s, MOTION(0x15, 0x00));
  UpdateMotionGraphic(&p->s);
  {
    struct Body* body;
    (p->s).flags |= COLLIDABLE;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 0x100);
    body->parent = (struct CollidableEntity*)p;
    body->fn = FUN_08070000;
  }
  {
    register s32 one4 asm("r4");
    one4 = 1;
    asm("" : "+r"(one4));
    (p->s).flags |= Y_FLIP;
    ((p->s).spr).yflip = one4;
    a = (u8*)p + 0x4a;
    {
      register s32 m asm("r2");
      register u8 b asm("r1");
      s32 msk;
      m = 0x20;
      asm("" : "+r"(m));
      b = *a;
      msk = -0x21;
      msk &= b;
      msk |= m;
      *a = msk;
    }
    *(u32*)((u8*)p + 0xbc) = z7;
    {
      s32 msk2;
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        (p->s).d.x = 0x80;
        (p->s).flags |= X_FLIP;
        ((p->s).spr).xflip = one4;
        {
          register s32 m asm("r2");
          register u8 b asm("r1");
          m = 0x10;
          asm("" : "+r"(m));
          b = *a;
          msk2 = -0x11;
          msk2 &= b;
          msk2 |= m;
        }
      } else {
        (p->s).d.x = -0x80;
        (p->s).flags &= 0xEF;
        ((p->s).spr).xflip = z7;
        {
          register u8 b asm("r1");
          b = *a;
          msk2 = -0x11;
          msk2 &= b;
        }
      }
      *a = msk2;
    }
  }
  (p->s).coord.y = FUN_0800a134((p->s).coord.x, (p->s).coord.y);
  *(s32*)((u8*)p + 0xb4) = (p->s).coord.x;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  {
    struct Enemy* p2 = p;
    u8* c;
    s32 z2;
    asm("" : "+r"(p2));
    c = (u8*)p2 + 0xc2;
    z2 = 0;
    *c = z2;
    SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = z2;
    (p->s).mode[2] = 1;
  }
  asm volatile("" :: "r"(z6));
  Enemy14_Update(p);
}

// 0x0806F7DC
void FUN_0806f7dc(struct Enemy* p) {
  s32 z;
  s32 one;
  struct Body* body;
  s32 x;
  InitRotatableMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    fv |= fl;
    fl = FLIPABLE;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, 0x1500);
  UpdateMotionGraphic(&p->s);
  (p->s).flags |= COLLIDABLE;
  body = &p->body;
  InitBody(body, &sCollisions[2], &(p->s).coord, 0x100);
  body->parent = (struct CollidableEntity*)p;
  body->fn = (void*)FUN_08070000;
  (p->s).flags &= 0xEF;
  one = 1;
  ((p->s).spr).xflip = z;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    *oa = m11;
  }
  (p->s).angle = 0x40;
  *(s32*)((u8*)p + 0xbc) = z;
  (p->s).d.y = 0x80;
  x = FUN_0800a31c((p->s).coord.x, (p->s).coord.y);
  (p->s).coord.x = x;
  *(s32*)((u8*)p + 0xb4) = x;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  *((u8*)p + 0xc2) = z;
  {
    u32 tbl = (u32)gEnemyFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
  }
  (p->s).mode[1] = z;
  (p->s).mode[2] = one;
  Enemy14_Update(p);
}

s32 FUN_0800a22c(s32 x, s32 y);

// 0x0806F89C
void FUN_0806f89c(struct Enemy* p) {
  s32 z;
  s32 one;
  struct Body* body;
  s32 x;
  InitRotatableMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    fv |= fl;
    fl = FLIPABLE;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, 0x1500);
  UpdateMotionGraphic(&p->s);
  (p->s).flags |= COLLIDABLE;
  body = &p->body;
  InitBody(body, &sCollisions[2], &(p->s).coord, 0x100);
  body->parent = (struct CollidableEntity*)p;
  body->fn = (void*)FUN_08070000;
  one = 1;
  (p->s).flags |= 0x10;
  ((p->s).spr).xflip = one;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 sh = 0x10;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    m11 |= sh;
    *oa = m11;
  }
  (p->s).angle = 0x40;
  *(s32*)((u8*)p + 0xbc) = z;
  (p->s).d.y = 0x80;
  x = FUN_0800a22c((p->s).coord.x, (p->s).coord.y);
  (p->s).coord.x = x;
  *(s32*)((u8*)p + 0xb4) = x;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  *((u8*)p + 0xc2) = z;
  (p->s).work[2] = z;
  {
    u32 tbl = (u32)gEnemyFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
  }
  (p->s).mode[1] = z;
  (p->s).mode[2] = one;
  Enemy14_Update(p);
}

INCASM("asm/enemy/top_gabyoall_p2_b.inc");

// 0x08070000
void FUN_08070000(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & (BODY_STATUS_WHITE | BODY_STATUS_B3)) {
    struct Entity* self = (struct Entity*)body->parent;
    if (self->mode[1] != 2) {
      self->mode[1] = 2;
      self->mode[2] = 0;
    } else {
      self->work[2] = 64;
    }
  }
}

// --------------------------------------------

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : NO_DAMAGE,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(12), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : NO_DAMAGE,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(12), PIXEL(24)},
    },
};

static const struct Coord sElementCoords[4] = {
    {0x00000000, -0x00000800},
    {0x00000000, -0x00000800},
    {0x00000000, -0x00000800},
    {0x00000000, 0x00000800},
};
