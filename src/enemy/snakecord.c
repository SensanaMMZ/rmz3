#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"
#include "zero.h"
#include "vfx.h"
#include "entity.h"
#include "entity/macros.h"
#include "physics.h"
#include "story.h"


// 0x08073ea8
u32 FUN_08073ea8(struct Entity* p, s32 dx) {
  if (dx == 0) {
    return 0;
  }
  p->coord.x += dx;
  if (dx < 0) {
    s32 push = PushoutToRight2(p->coord.x, p->coord.y);
    if (push > 0) {
      p->coord.x += push;
      return 2;
    }
  } else {
    s32 push = PushoutToLeft2(p->coord.x, p->coord.y);
    if (push < 0) {
      p->coord.x += push;
      return 1;
    }
  }
  return 0;
}


// 0x08073ef0
u32 FUN_08073ef0(struct Entity* p, s32 dy) {
  if (dy == 0) {
    return 0;
  }
  p->coord.y += dy;
  if (dy < 0) {
    s32 push = PushoutToDown2(p->coord.x, p->coord.y);
    if (push > 0) {
      p->coord.y += push;
      return 2;
    }
  } else {
    s32 push = PushoutToUp2(p->coord.x, p->coord.y);
    if (push < 0) {
      p->coord.y += push;
      return 1;
    }
  }
  return 0;
}

INCASM("asm/enemy/snakecord_p1_p1_a_p1.inc");

void FUN_080740e4(struct Enemy* p) {
  while ((p->s).unk_28 != NULL) {
    p = (struct Enemy*)(p->s).unk_28;
  }
  while (p != NULL) {
    if ((p->s).work[2] < 2) {
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      (p->s).mode[1] = 1;
      ((p->s).unk_2c)->unk_28 = NULL;
    }
    if ((p->s).work[0] == 0) {
      (p->s).mode[1] = 3, (p->s).mode[2] = 0;
    }
    p = (struct Enemy*)(p->s).unk_2c;
  }
}

void FUN_080740e4(struct Enemy* p);

void FUN_08074134(struct Body* body) {
  struct Enemy* parent = (struct Enemy*)body->parent;
  if (body->hitboxFlags & BODY_STATUS_B3) {
    if ((parent->s).work[0] == 1) {
      if (body->hitboxFlags & BODY_STATUS_SLASHED) {
        FUN_080740e4(parent);
      }
    }
  }
}

INCASM("asm/enemy/snakecord_p1_p1_a_p2.inc");

static const struct Coord sElementCoords[2];

// Four instructions short: retail materializes the props address once, copies
// it for the slot variable, and derives the body-status address from it
// (subs 0x28); agbcc coalesces the copy in every spelling tried.
NON_MATCH void FUN_080742ec(struct Enemy* p) {
#if MODERN
  struct VFX** slot;
  struct VFX* e;
  const struct Coord* c;
  if ((p->s).work[0] != 0) {
    return;
  }
  if ((p->s).mode[1] == 1) {
    return;
  }
  e = *(struct VFX**)&p->props[0];
  slot = (struct VFX**)&p->props[0];
  if (e != NULL) {
    return;
  }
  if (!((p->body).status & 1)) {
    return;
  }
  if ((p->body).status & 0x20000) {
    (p->s).mode[1] = 0xA;
    (p->s).mode[2] = 0;
    return;
  }
  if ((*((u8*)p + 0x97) & 0xF0) == 0x20) {
    c = &sElementCoords[1];
  } else {
    c = &sElementCoords[0];
  }
  *slot = ApplyElementEffect(0, &p->s, c);
  if (*slot != NULL) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
#else
  INCCODE("asm/enemy/snakecord_742ec.inc");
#endif
}

INCASM("asm/enemy/snakecord_p1_p1_a_p2b.inc");

static const EnemyFunc PTR_ARRAY_08366e30[12];
extern const EnemyFunc PTR_ARRAY_08366e60[12];
bool8 FUN_0807415c(struct Enemy* p);
void FUN_080742ec(struct Enemy* p);
bool8 FUN_08074208(struct Enemy* p);
void Snakecord_Die(struct Enemy* p);

void Snakecord_Update(struct Enemy* p) {
  if ((p->s).work[0] == 1) {
    struct Entity* par = (p->s).unk_2c;
    if (par != NULL) {
      u8 pm = par->mode[0];
      if (pm > 2) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        return;
      }
      if (pm > 1) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = (p->s).work[0];
        return;
      }
    }
  }
  if (FUN_0807415c(p)) {
    return;
  }
  FUN_080742ec(p);
  if (FUN_08074208(p)) {
    return;
  }
  (PTR_ARRAY_08366e30[(p->s).mode[1]])(p);
  (PTR_ARRAY_08366e60[(p->s).mode[1]])(p);
}

extern const EnemyFunc PTR_ARRAY_08366e90[3];

void Snakecord_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (PTR_ARRAY_08366e90[(p->s).mode[1]])(p);
}

void FUN_08074618(struct Enemy* p) {}

void FUN_0807461c(struct Enemy* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
    if (status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 0xa;
      (p->s).mode[2] = 0;
    }
  }
  if ((p->body).status & BODY_STATUS_BINDING) {
    (p->s).mode[1] = 9;
    (p->s).mode[2] = 0;
  }
}

static const struct Collision sCollisions[];

void FUN_0807465c(struct Enemy* p) {
  struct VFX* c;

  if ((p->body).status & 0x800) {
    return;
  }
  (p->s).taskCol = 24;
  c = (struct VFX*)(p->s).unk_2c;
  if (c != NULL) {
    (c->s).flags &= ~DISPLAY;
    (c->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(c, ENTITY_DISAPPEAR);
  }
  if (PushoutToUp2((p->s).coord.x, (p->s).coord.y) < 0) {
    (p->s).mode[1] = 11;
  } else {
    (p->s).mode[1] = 4;
  }
  (p->s).mode[2] = 0;
}

void FUN_080746c0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)&p->props[0];

  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[4]);
    if (IsFrozen(&p->s) == 0) {
      if (PushoutToUp2((p->s).coord.x, (p->s).coord.y) < 0) {
        (p->s).mode[1] = 11;
      } else {
        (p->s).mode[1] = 4;
      }
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 10;
    (p->s).mode[2] = 0;
  }
}

void FUN_0807472c(struct Enemy* p) {
  u32 status = (p->body).status;
  if (status & BODY_STATUS_WHITE) {
    if (status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 0xa;
      (p->s).mode[2] = 0;
    }
  }
}

INCASM("asm/enemy/snakecord_p2_a.inc");

// 0x0807484c
void FUN_0807484c(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8 fv asm("r0");
      u8 t;
      t = (p->s).flags;
      fv = DISPLAY;
      fv |= t;
      (p->s).flags = fv;
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).unk_coord.x = (p->s).coord.x;
      (p->s).unk_coord.y = (p->s).coord.y;
      (p->s).d.x = m;
      (p->s).d.y = m;
      InitRotatableMotion(&p->s);
      SetMotion(&p->s, MOTION(0x28, 0x00));
      (p->s).angle = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/snakecord_p2_a2.inc");

static const u8 u8_ARRAY_08366fec[13];

void FUN_08074bac(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      InitNonAffineMotion(&p->s);
      SetMotion(&p->s, MOTION(0x28, 0x0C));
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 v6;
      u8 on;
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
      }
      v6 = (p->s).coord.x - (pZero2->s).coord.x;
      if ((u32)(v6 + 0x3000) <= 0x5FFF) {
        if ((p->s).work[2] == 0) {
          (p->s).mode[1] = 6;
          (p->s).mode[2] = 0;
        }
      }
      on = (u32)v6 >> 31;
      SET_XFLIP(p, on);
      if ((u32)(v6 + 0x1000) > 0x2000) {
        FUN_08073ea8(&p->s, on * 3 * 128 - 0xC0);
        v6 = FUN_0800a05c((p->s).coord.x, (p->s).coord.y);
        if (v6 - (p->s).coord.y > 0x400) {
          (p->s).mode[1] = 5;
          (p->s).mode[2] = 0;
        } else {
          (p->s).coord.y = v6;
        }
      }
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[u8_ARRAY_08366fec[(s8)(p->s).motion.cmdIdx]]);
      break;
    }
  }
}

void FUN_08074cb4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      SetMotion(&p->s, MOTION(0x28, 0x09));
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 r;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      r = PushoutToUp2((p->s).coord.x, (p->s).coord.y);
      if (r < 0) {
        (p->s).coord.y += r;
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

#include "motion.h"

void FUN_08074d18(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x28, 0x05));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 4) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, MOTION(0x28, 0x06));
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 4) {
        (p->s).mode[1] = 7;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x08074d90
void FUN_08074d90(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.x = -0x200;
      {
        s32 v = -0x200;
        if ((p->s).flags & X_FLIP) {
          v = 0x200;
        }
        (p->s).d.x = v;
      }
      (p->s).d.y = -((u16)Sqrt(0x100) << 6);
      SetMotion(&p->s, MOTION(0x28, 0x07));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      FUN_08073ea8(&p->s, (p->s).d.x);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      FUN_08073ef0(&p->s, (p->s).d.y);
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 4) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).work[3] = 0;
      SetMotion(&p->s, MOTION(0x28, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      if ((u8)++(p->s).work[3] == 8) {
        SetDDP(&p->body, &sCollisions[6]);
      }
      FUN_08073ea8(&p->s, (p->s).d.x);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      FUN_08073ef0(&p->s, (p->s).d.y);
      if ((p->s).d.y > 0) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// 0x08074E90
void FUN_08074e90(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[6]);
      SetMotion(&p->s, MOTION(0x28, 0x09));
      (p->s).mode[2]++;
    case 1:
      FUN_08073ea8(&p->s, (p->s).d.x);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if ((u8)FUN_08073ef0(&p->s, (p->s).d.y) == 1) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      SetMotion(&p->s, MOTION(0x28, 0x0A));
      (p->s).mode[2]++;
    case 3:
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)p + 0x73) == 3) {
        u8 z = 0;
        (p->s).mode[1] = 4;
        (p->s).mode[2] = z;
      }
      break;
  }
}

struct Entity* FUN_080bb830(struct Entity* e);

// 0x08074f34 -- parked (register-swap basin, same family as the element
// check park): retail puts the flip-select temp in r1 and the 0x7F0
// constant in r5; agbcc swaps them ([r5,r0]), and pinning either cascades
// (zx r2->r5 or p r4->r6). Instruction stream otherwise identical.
NON_MATCH void FUN_08074f34(struct Enemy* p) {
#if MODERN
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).taskCol = 0xF;
      SetDDP(&p->body, &sCollisions[8]);
      SetMotion(&p->s, MOTION(0x28, 0x0B));
      (p->s).unk_2c = FUN_080bb830(&p->s);
      (p->s).work[2] = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      register struct Zero* z asm("r3");
      s32 zx;
      if ((p->s).work[2] == 0) {
        (p->s).work[2] = 0x18;
        PlaySound(0x3B);
      }
      (p->s).work[2]--;
      z = pZero2;
      zx = (z->s).coord.x;
      (p->s).coord.x = zx + 0x800;
      {
        s32 t = zx + 0x7F0;
        if ((p->s).flags & X_FLIP) {
          t = zx - 0x800;
        }
        (p->s).coord.x = t;
      }
      (p->s).coord.y = (z->s).coord.y - 0x800;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/enemy/snakecord_4f34.inc");
#endif
}

static const u8 u8_ARRAY_08366fec[13];

// 0x08074FCC
void FUN_08074fcc(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).work[2] = m;
      SetMotion(&p->s, MOTION(0x28, 0x0C));
      (p->s).mode[2]++;
    case 1: {
      s32 hit = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
      if (hit < 0) {
        s32 k = -0x400;
        if (hit < k) {
          hit = (k * (p->s).work[2]) / 256;
        }
        (p->s).coord.y += hit;
        (p->s).work[2] = ((p->s).work[2] + 4) & 0x3F;
      } else {
        u8 z = 0;
        (p->s).mode[1] = 4;
        (p->s).mode[2] = z;
      }
      UpdateMotionGraphic(&p->s);
      SetDDP(&p->body, &sCollisions[u8_ARRAY_08366fec[(s8)(p->s).motion.cmdIdx]]);
      break;
    }
  }
}

void FUN_080bb908(s32 x, s32 y);
extern void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

void MaybeKillSnakecord(struct Enemy* p) {
  struct Coord c;
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  {
    u8 f = (p->s).flags & ~COLLIDABLE;
    f &= ~DISPLAY;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  CreateSmoke(1, &c);
  PlaySound(0x2A);
  FUN_080bb908((p->s).coord.x, (p->s).coord.y);
  TryDropItem(3, &(p->s).coord);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x080750f8
void FUN_080750f8(struct Enemy* p) {
  struct Coord c;
  {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    u8* q = (u8*)p + 0x8c;
    s32 z;
    asm("" : "+r"(q));
    z = 0;
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *(s32*)q = z;
    asm("" : "+r"(q));
    q += 4;
    asm("" : "+r"(q));
    *q = z;
    t = (p->s).flags;
    f = 0xFB;
    f &= t;
    asm volatile("" ::"r"(t));
    k2 = 0xFE;
    f &= k2;
    (p->s).flags = f;
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y + 0x800;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/snakecord_p2_d.inc");

void Snakecord_Init(struct Enemy* p);
void Snakecord_Update(struct Enemy* p);
void Snakecord_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSnakecordRoutine = {
    [ENTITY_INIT] =      Snakecord_Init,
    [ENTITY_UPDATE] =    Snakecord_Update,
    [ENTITY_DIE] =       Snakecord_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080746c0(struct Enemy* p);
void FUN_08074618(struct Enemy* p);
void FUN_08074618(struct Enemy* p);
void FUN_0807472c(struct Enemy* p);
void FUN_0807461c(struct Enemy* p);
void FUN_0807465c(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08366e30[12] = {
    FUN_080746c0,
    FUN_08074618,
    FUN_08074618,
    FUN_0807472c,
    FUN_0807472c,
    FUN_0807472c,
    FUN_0807472c,
    FUN_0807461c,
    FUN_0807461c,
    FUN_0807465c,
    FUN_08074618,
    FUN_0807472c,
};
// clang-format on

// --------------------------------------------

void snakecord_08074754(struct Enemy* p);
void FUN_080748a8(struct Enemy* p);
void FUN_0807484c(struct Enemy* p);
void FUN_08074ac0(struct Enemy* p);
void FUN_08074bac(struct Enemy* p);
void FUN_08074cb4(struct Enemy* p);
void FUN_08074d18(struct Enemy* p);
void FUN_08074d90(struct Enemy* p);
void FUN_08074e90(struct Enemy* p);
void FUN_08074f34(struct Enemy* p);
void FUN_08075154(struct Enemy* p);
void FUN_08074fcc(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366e60[12] = {
    snakecord_08074754,
    FUN_080748a8,
    FUN_0807484c,
    FUN_08074ac0,
    FUN_08074bac,
    FUN_08074cb4,
    FUN_08074d18,
    FUN_08074d90,
    FUN_08074e90,
    FUN_08074f34,
    FUN_08075154,
    FUN_08074fcc,
};
// clang-format on

// --------------------------------------------

void MaybeKillSnakecord(struct Enemy* p);
void FUN_080750f8(struct Enemy* p);
void FUN_08075154(struct Enemy* p);

const EnemyFunc PTR_ARRAY_08366e90[3] = {
    MaybeKillSnakecord,
    FUN_080750f8,
    FUN_08075154,
};

// --------------------------------------------

// 0x08366e9c
static const struct Collision sCollisions[] = {
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
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(4), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : HARDNESS_B3,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(8), PIXEL(8), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(26), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(26), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      unk_0a : 0x21,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(8), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(8), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      unk_0a : 0x21,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(16), PIXEL(64), PIXEL(64)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(11), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(11), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(3), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : 8,
      remaining : 0,
      range : {-PIXEL(2), -PIXEL(3), PIXEL(11), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(2), -PIXEL(26), PIXEL(11), PIXEL(10)},
    },
};

// --------------------------------------------

// 0x08366fec
static const u8 u8_ARRAY_08366fec[13] = {
    4, 4, 4, 4, 4, 4, 9, 9, 11, 11, 11, 11, 11,
};

static const struct Coord sElementCoords[2] = {
    {PIXEL(0), -PIXEL(24)},
    {PIXEL(0), -PIXEL(16)},
};

static const u8 sInitModes[4] = {1, 2, 0, 0};
