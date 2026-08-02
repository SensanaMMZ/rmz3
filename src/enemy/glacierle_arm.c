#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "motion.h"

static const EnemyFunc sUpdates1[3];
static const EnemyFunc sUpdates2[3];
static const struct Collision sCollisions[2];
static const u8 sInitModes[3];

void GlacierleAtkArm_Update(struct Enemy* p);

struct Enemy* createGlacierleAtkHand(struct Entity* e) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GLACIERLE_ARM);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    InitRotatableMotion(&p->s);
    (p->s).unk_2c = NULL;
    (p->s).unk_28 = e;
    (p->s).d.x = 0;
    (p->s).d.y = 0;
    p->props[1] = 1;
    p->props[0] = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
  return p;
}

#include "entity/macros.h"

struct Enemy* createGlacierleJoint(struct Entity* e, struct Entity* parent) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    struct Entity* prev;

    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 39);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_2c = e->unk_2c;
    (p->s).unk_28 = e;
    prev = e->unk_2c;
    if (prev != NULL) {
      prev->unk_28 = (struct Entity*)p;
      (p->s).d.x = prev->d.x;
      (p->s).d.y = prev->d.y;
      (p->s).coord.x = prev->coord.x;
      (p->s).coord.y = prev->coord.y;
      if (prev->unk_2c != NULL) {
        (p->s).coord.x += prev->coord.x - (prev->unk_2c)->coord.x;
        (p->s).coord.y += prev->coord.y - (prev->unk_2c)->coord.y;
      }
      (p->s).unk_coord.x = (p->s).coord.x;
      (p->s).unk_coord.y = (p->s).coord.y;
    } else {
      (p->s).d.x = 0;
      (p->s).d.y = 0;
    }
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = parent->uniqueID;
    *(struct Entity**)&p->props[8] = parent;
    e->unk_2c = (struct Entity*)p;
    p->props[2] = ((struct Enemy*)e)->props[0];
    ((struct Enemy*)e)->props[0]++;
  }
  return p;
}

struct Enemy* createGlacierleSucker(struct Entity* e, struct Entity* parent) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 39);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).unk_2c = e;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = parent->uniqueID;
    *(struct Entity**)&p->props[8] = parent;
  }
  return p;
}

// 0x08082348
void FUN_08082348(struct Enemy* p);

void FUN_08082348(struct Enemy* p) {
  struct Entity* q = (p->s).unk_2c;
  if (q != NULL) {
    u8* c;
    u8 d;
    u8 fl;
    u32 z;
    register u8* w asm("r0");
    if (q->unk_2c != NULL) {
      (q->unk_2c)->unk_28 = &p->s;
    }
    (p->s).unk_2c = q->unk_2c;
    c = (u8*)p + 0xb4;
    d = *c - 1;
    z = 0;
    *c = d;
    fl = q->flags & 0xFE;
    fl &= 0xFD;
    q->flags = fl;
    w = (u8*)q + 0x8c;
    *(u32*)w = z;
    asm volatile("add %0, #4" : "+r"(w));
    *(u32*)w = z;
    asm volatile("add %0, #4" : "+r"(w));
    *w = z;
    q->flags &= 0xFB;
    SET_ENEMY_ROUTINE(q, 3);
  }
}


// One insn over: retail hoists the target count 10 into a register and
// compares const-left; plain literals compare the other way (ordering tie).
NON_MATCH void FUN_080823a4(struct Entity* e, struct Entity* parent) {
#if MODERN
  s32 n;
  u8 cur = ((struct Enemy*)e)->props[0];
  if (cur != 10) {
    if (10 > cur) {
      n = 10 - cur;
      if (n > 0) {
        do {
          createGlacierleJoint(e, parent);
        } while (--n);
      }
    } else {
      n = cur - 10;
      if (n > 0) {
        do {
          FUN_08082348(e);
        } while (--n);
      }
    }
  }
#else
  INCCODE("asm/enemy/glacierle_arm_823a4.inc");
#endif
}

// 3 insns short: register naming/eval-order tie in the distance math.
NON_MATCH u32 FUN_080823ec(struct Enemy* p) {
#if MODERN
  struct Entity* a = (p->s).unk_2c;
  if (a != NULL) {
    struct Entity* b = a->unk_2c;
    if (b != NULL) {
      s32 dx = ((b->coord).x - (a->coord).x) >> 8;
      s32 dy = ((b->coord).y - (a->coord).y) >> 8;
      return (u16)Sqrt(dx * dx + dy * dy) << 8;
    }
  }
  return 0;
#else
  INCCODE("asm/enemy/glacierle_arm_823ec.inc");
#endif
}

void FUN_0808242c(struct Enemy* p, s32 dx, s32 dy) {
  u8* a1 = &p->props[0];
  u8 n0 = *a1;
  struct Entity* q = (p->s).unk_2c;
  if (q != NULL) {
    u8* np = a1;
    s32 ay = n0 * dy;
    s32 ax = n0 * dx;
    do {
      q->d.x += ax / *np;
      q->d.y += ay / *np;
      ay -= dy;
      ax -= dx;
      q = q->unk_2c;
    } while (q != NULL);
  }
}

// 0x08082484 -- lay the arm chain along the vector to (dx, dy).
// Blocker (home-rotation basin): {by, bx, dx, dy} come out r7/r8/r9/r10
// in retail but rotate one place in ours (bx/dx/dy/by); declaration
// order, symmetric-vs-split bx, in-loop and in-branch priority boosts,
// and r7/r8 pins each moved the rotation without landing it.
NON_MATCH void FUN_08082484(struct Enemy* p, s32 dx, s32 dy) {
#if MODERN
  s32 cx, cy;
  u8* ap;
  s32 by, bx;
  s32 d;
  dx -= (p->s).coord.x;
  dy -= (p->s).coord.y;
  d = (dx >> 8) * (dx >> 8);
  d += (dy >> 8) * (dy >> 8);
  d = (u16)Sqrt(d) << 8;
  bx = (p->s).coord.x;
  by = (p->s).coord.y;
  if (d != 0) {
    s32 ux = (dx << 8) / d;
    s32 uy;
    bx = (ux << 2) + (p->s).coord.x;
    uy = (dy << 8) / d;
    by = (uy << 2) + (p->s).coord.y;
    dx -= ux << 3;
    dy -= uy << 3;
  }
  {
    struct Entity* q = (p->s).unk_2c;
    u8* a1 = &p->props[0];
    if (*a1 == 1) {
      cx = dx >> 8;
      cy = dy >> 8;
      ap = &(p->s).angle;
      if (q != NULL) {
        q->coord.x = bx;
        q->coord.y = by;
      }
    } else {
      cx = dx >> 8;
      cy = dy >> 8;
      ap = &(p->s).angle;
      if (q != NULL) {
        u8* np = a1;
        s32 ya = 0;
        s32 xa = 0;
        do {
          q->coord.x = bx;
          q->unk_coord.x = q->coord.x = bx + xa / (*np - 1);
          q->coord.y = by;
          q->unk_coord.y = q->coord.y = by + ya / (*np - 1);
          ya += dy;
          xa += dx;
          q = q->unk_2c;
        } while (q != NULL);
      }
    }
  }
  *ap = ArcTan2(cx, cy) >> 8;
#else
  INCCODE("asm/enemy/glacierle_arm_82484.inc");
#endif
}

INCASM("asm/enemy/glacierle_arm_bb_b.inc");

void FUN_0808288c(struct Enemy* p, u8 a) {
  struct Entity* q = (p->s).unk_2c;
  if (q != NULL) {
    (p->s).angle = a - 0x40;
    q->coord.x = (p->s).coord.x;
    q->coord.x += gSineTable[(u8)(a + 0x40)] * 17;
    q->coord.y = (p->s).coord.y;
    q->coord.y += gSineTable[a] * 17;
  }
}

void nop_080828dc(struct Enemy* p) {}

void GlacierleAtkArm_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  if ((p->s).work[0] == 0) {
    INIT_BODY(p, sCollisions, 1, (void*)nop_080828dc);
  }
  GlacierleAtkArm_Update(p);
}

void GlacierleAtkArm_Update(struct Enemy* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

// 0x08082984
void GlacierleAtkArm_Die(struct Enemy* p) {
  switch ((p->s).work[0]) {
    case 0:
    case 1:
      switch ((p->s).mode[1]) {
        case 0:
          (p->s).d.y = 0;
          (p->s).mode[1]++;
          /* fallthrough */
        case 1:
          (p->s).d.y += 0x40;
          if ((p->s).d.y > 0x700) {
            (p->s).d.y = 0x700;
          }
          (p->s).coord.y += (p->s).d.y;
          if (FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
            if ((p->s).work[0] == 0) {
              CreateSmoke(1, &(p->s).coord);
              PlaySound(0x2A);
              goto vanish;
            }
            if (*((u8*)p + 0xb6) & 1) {
              CreateSmoke(2, &(p->s).coord);
            }
            goto vanish;
          }
          break;
      }
      break;
    case 2:
    vanish:
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
      break;
  }
}

void nop_08082a1c(struct Enemy* p) {}

void FUN_08082a20(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 savedAngle = (p->s).angle;
      InitRotatableMotion(&p->s);
      SetMotion(&p->s, MOTION(0x59, 0));
      (p->s).angle = savedAngle;
      if (p->props[1] == 0) {
        UpdateMotionGraphic(&p->s);
      }
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      if (p->props[1] != 0) {
        UpdateMotionGraphic(&p->s);
      }
      break;
  }
  if (((struct Entity*)(p->s).unk_28)->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_08082aa0(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      InitNonAffineMotion(&p->s);
      SetMotion(&p->s, MOTION(0x59, 1));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
  }
  if ((*(struct Entity**)&p->props[8])->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_08082af8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 savedAngle = (p->s).angle;
      InitRotatableMotion(&p->s);
      SetMotion(&p->s, MOTION(0x59, 2));
      (p->s).angle = savedAngle;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
  }
  if ((*(struct Entity**)&p->props[8])->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  }
}

void GlacierleAtkArm_Init(struct Enemy* p);
void GlacierleAtkArm_Update(struct Enemy* p);
void GlacierleAtkArm_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gGlacierleAtkArmRoutine = {
    [ENTITY_INIT] =      GlacierleAtkArm_Init,
    [ENTITY_UPDATE] =    GlacierleAtkArm_Update,
    [ENTITY_DIE] =       GlacierleAtkArm_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void nop_08082a1c(struct Enemy* p);

static const EnemyFunc sUpdates1[3] = {
    nop_08082a1c,
    nop_08082a1c,
    nop_08082a1c,
};

void FUN_08082a20(struct Enemy* p);
void FUN_08082aa0(struct Enemy* p);
void FUN_08082af8(struct Enemy* p);

static const EnemyFunc sUpdates2[3] = {
    FUN_08082a20,
    FUN_08082aa0,
    FUN_08082af8,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(12), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
};

static const u8 sInitModes[3] = {0, 1, 2};
