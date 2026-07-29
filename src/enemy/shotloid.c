#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "physics.h"
#include "story.h"
#include "metatile.h"
#include "zero.h"

static const struct Collision sCollisions[];

#include "entity/macros.h"

struct Enemy* FUN_08093930(s32 x, s32 y, u8 n) {
  struct Enemy* e = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (e != NULL) {
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 62);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 2;
    (e->s).coord.x = x;
    (e->s).coord.y = y;
    e->props[9] = n;
  }
  return e;
}

struct Enemy* FUN_08093994(struct Enemy* p0) {
  register struct Enemy* p asm("r5") = p0;
  register struct Enemy* ret asm("r0");
  register struct Enemy* q asm("r4");
  ret = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  q = ret;
  if (q != NULL) {
    register s32 i2 asm("r2");
    register u32 fn asm("r1");
    (q->s).taskCol = 0x18;
    fn = (u32)gEnemyFnTable;
    i2 = 0x3E;
    (q->s).id = i2;
    fn += 0xF8;
    fn = *(u32*)fn;
    fn = *(u32*)fn;
    (q->s).onUpdate = (void*)fn;
    {
      register s32 v2 asm("r1");
      register u8* t2 asm("r2");
      v2 = 0;
      (q->s).tileNum = 0;
      t2 = &(q->s).palID;
      *t2 = v2;
    }
    (q->s).flags2 |= WHITE_PAINTABLE;
    (q->s).invincibleID = (q->s).uniqueID;
    (q->s).work[0] = 1;
    (q->s).unk_28 = (struct Entity*)p;
  }
  return ret;
}

bool8 FUN_080939e8(struct Enemy* p, s32 d) {
  s32 x = (p->s).coord.x;
  x -= PIXEL(14);
  if (d > 0) {
    x += PIXEL(28);
  }
  if (FUN_080098a4(x, (p->s).coord.y + PIXEL(10)) != 0) {
    return TRUE;
  }
  return FALSE;
}

u32 FUN_08093a20(struct Enemy* p) {
  u32 xflip = 0;
  struct Zero* z = pZero2;
  s32 px = (p->s).coord.x;
  s32 zx = (z->s).coord.x;
  if (px > zx) {
    xflip = 1;
  }
  {
    s32 t = zx - PIXEL(96);
    t += xflip * PIXEL(192);
    t -= px;
    t += PIXEL(8);
    if ((u32)t <= 0xFFF) {
      return 2;
    }
  }
  return xflip;
}

bool8 FUN_08093a64(struct Enemy* p, s32 dy) {
  if (dy > 0) {
    s32 diff;
    (p->s).coord.y += dy;
    diff = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - (p->s).coord.y;
    if (diff <= 0x7ff) {
      (p->s).coord.y = (p->s).coord.y + diff;
      return TRUE;
    }
  }
  return FALSE;
}

u32 FUN_08093a98(struct Enemy* p, s32 d) {
  if (d != 0) {
    if (d < 0) {
      if (FUN_080098a4((p->s).coord.x - PIXEL(14), (p->s).coord.y - PIXEL(10)) != 0) {
        return 1;
      }
    } else {
      if (FUN_080098a4((p->s).coord.x + PIXEL(14), (p->s).coord.y - PIXEL(10)) != 0) {
        return 2;
      }
    }
    (p->s).coord.x += d;
  }
  return 0;
}

void nop_08093af8(struct Enemy* p) {}

bool8 FUN_08093afc(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    return TRUE;
  }
  return FALSE;
}


extern const EnemyFunc sUpdates1[];
extern const EnemyFunc sUpdates2[];

// 0x08093b50
bool8 FUN_08093b50(struct Enemy* p) {
  if ((p->s).mode[1] != 7) {
    s32 v = *(s32*)&p->props[0];
    if (v == 0) {
      switch ((p->s).mode[3]) {
        case 0:
          if (IsFrozen(&p->s)) {
            (sUpdates1[(p->s).mode[1]])(p);
            (sUpdates2[(p->s).mode[1]])(p);
            (p->s).mode[3]++;
            UpdateMotionGraphic(&p->s);
            return TRUE;
          }
          break;
        case 1:
          if (IsFrozen(&p->s)) {
            if (((p->body).status & 0x00020001) == 0x00020001) {
              (p->s).mode[3] = 0;
            } else {
              return TRUE;
            }
          } else {
            (p->s).mode[3] = 0;
          }
          break;
      }
    }
  }
  return FALSE;
}

struct ShotloidObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct VFX* elementEffect;
  u8 unk_004[12];
};
static_assert(sizeof(struct ShotloidObject) == sizeof(struct Enemy));

static const struct Coord sElementCoord;

void FUN_08093be0(struct ShotloidObject* p) {
  if (p->elementEffect == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    if (((p->body).status & BODY_STATUS_RECOILED)) {
      (p->s).mode[1] = 7;
      (p->s).mode[2] = 0;
    } else {
      p->elementEffect = ApplyElementEffect(0, &p->s, &sElementCoord);
      if (p->elementEffect != NULL) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
    }
  }
}

INCASM("asm/enemy/shotloid_pre_p2_a_b.inc");


void Shotloid_Update(struct Enemy* p) {
  if (!FUN_08093afc(p)) {
    if ((p->s).work[0] == 0) {
      FUN_08093be0((struct ShotloidObject*)p);
      if (FUN_08093b50(p)) {
        return;
      }
    }
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}


static const EnemyFunc sDeads[3];

// 0x08093d74
void Shotloid_Die(struct Enemy* p) {
  if ((p->s).work[1] == 0 && IS_METTAUR) {
    u8 fl = (p->s).flags & ~DISPLAY;
    (p->s).flags = fl & ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (sDeads[(p->s).mode[1]])(p);
  }
}

void FUN_08093de0(struct Enemy* p) {}


void FUN_08093de4(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}


void FUN_08093e04(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[0]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

// 0x08093e60
void FUN_08093e60(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0x8E, 0x04));
      *(u32*)&p->props[4] &= ~1;
      SetDDP(&p->body, (const struct Collision*)0x08369E84);
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 f = IsFrozen(&p->s);
      if (f == 0) {
        s32 r;
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (r < 0) {
          (p->s).coord.y += r;
          (p->s).d.y = f;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/enemy/shotloid_post_p2_p2.inc");

void FUN_08094110(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 f = *(u32*)&p->props[4];
      f |= 1;
      f |= 2;
      *(u32*)&p->props[4] = f;
      SetMotion(&p->s, MOTION(0x8E, 0x02));
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      u8 r;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      r = FUN_08093a64(p, 1);
      if (r == 0) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = r;
      }
      break;
    }
  }
}

INCASM("asm/enemy/shotloid_post_p2_p2b.inc");

void Shotloid_Init(struct Enemy* p);
void Shotloid_Update(struct Enemy* p);
void Shotloid_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gShotloidRoutine = {
    [ENTITY_INIT] =      Shotloid_Init,
    [ENTITY_UPDATE] =    Shotloid_Update,
    [ENTITY_DIE] =       Shotloid_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_08093e04(struct Enemy* p);
void FUN_08093de0(struct Enemy* p);
void FUN_08093de4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[9] = {
    FUN_08093e04,
    FUN_08093de4,
    FUN_08093de4,
    FUN_08093de4,
    FUN_08093de4,
    FUN_08093de4,
    FUN_08093de0,
    FUN_08093de0,
    FUN_08093de4,
};
// clang-format on

void FUN_08093e60(struct Enemy* p);
void FUN_08093ee4(struct Enemy* p);
void FUN_08093fe0(struct Enemy* p);
void FUN_08094110(struct Enemy* p);
void FUN_08094178(struct Enemy* p);
void FUN_08094224(struct Enemy* p);
void FUN_08094320(struct Enemy* p);
void FUN_08094534(struct Enemy* p);
void FUN_0809468c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[9] = {
    FUN_08093e60,
    FUN_08093ee4,
    FUN_08093fe0,
    FUN_08094110,
    FUN_08094178,
    FUN_08094224,
    FUN_08094320,
    FUN_08094534,
    FUN_0809468c,
};
// clang-format on

// --------------------------------------------

void FUN_080947c4(struct Enemy* p);
void FUN_08094874(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_080947c4,
    FUN_08094874,
    FUN_08094534,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(23), PIXEL(23)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(12), PIXEL(23), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(23), PIXEL(23)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(10)};
static const u8 sInitModes[2] = {5, 6};

// clang-format off
static const motion_t sMotions[5] = {
    MOTION(SM142_SHOTLOID, 13),
    MOTION(SM142_SHOTLOID, 14),
    MOTION(SM142_SHOTLOID, 15),
    MOTION(SM142_SHOTLOID, 16),
    MOTION(SM142_SHOTLOID, 11),
};
// clang-format on
