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

void FUN_08093fe0(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      *(u32*)&p->props[4] &= ~1;
      SetMotion(&p->s, 0x8E06);
      UpdateMotionGraphic(&p->s);
      (p->s).d.x = m;
      (p->s).work[2] = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      u8 sv0;
      u8 sv1;
      register s32 k asm("r2");
      register s32 tx asm("r5");
      {
        s32 t0 = (u8)FUN_08093a20(p);
        asm("" : "+r"(t0));
        k = t0;
      }
      tx = (pZero2->s).coord.x;
      tx += -0x6000;
      tx += (k * 3) << 14;
      {
        register s32 dt asm("r1");
        register s32 cx asm("r0");
        cx = (p->s).coord.x;
        dt = tx - cx;
        asm("" : "+r"(dt));
        tx = dt / 32;
      }
      if (k != 2) {
        if ((FUN_080939e8(p, tx) << 24) == 0) {
          goto set1;
        }
      } else {
      set1:
        sv1 = 0;
        sv0 = 1;
        goto st106;
      }
      if ((FUN_08093a98(p, tx) << 24) != 0) {
        goto setec;
      }
      {
        s32 nd = (p->s).d.x + tx;
        s32 fl3;
        (p->s).d.x = nd;
        fl3 = 0;
        if (nd > 0x100) {
          (p->s).d.x = nd + -0x100;
        } else {
          if (nd < -0x100) {
            (p->s).d.x = nd + 0x100;
            fl3 = 1;
          }
          if (fl3 == 0) {
            goto checka64;
          }
        }
      }
      {
        register s32 wv asm("r0");
        register s32 c7 asm("r1");
        wv = (p->s).work[2];
        c7 = 7;
        wv &= c7;
        (p->s).work[2] = wv;
      }
      {
        s32 pos = 0;
        s32 w;
        if (tx > 0) {
          pos = 1;
        }
        if ((p->s).flags & 0x10) {
          if (pos == 0) {
            goto decw;
          }
          goto incw;
        }
        if (pos == 0) {
          goto incw;
        }
      decw:
        w = (p->s).work[2] - 1;
        goto stw;
      incw:
        w = (p->s).work[2] + 1;
      stw:
        (p->s).work[2] = w;
      }
      GotoMotion(&p->s, 0x8E06, (p->s).work[2], 1);
      UpdateMotionGraphic(&p->s);
      goto checka64;
    setec:
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    checka64: {
      register s32 r1v asm("r1");
      r1v = (u8)FUN_08093a64(p, 1);
      if (r1v != 0) {
        break;
      }
      sv0 = 5;
      sv1 = r1v;
    }
    st106:
      *(volatile u8*)&(p->s).mode[1] = sv0;
      *(volatile u8*)&(p->s).mode[2] = sv1;
      break;
    }
  }
}


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

// 0x08094178
void FUN_08094178(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32* w = (u32*)&p->props[4];
      *w &= ~1;
      (p->s).work[2] = 0;
      SetMotion(&p->s, MOTION(0x8E, 0x08));
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      u8 r;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 && (p->s).motion.cmdIdx == 3) {
        u8 k = 1;
        (p->s).work[2] = k;
        SET_XFLIP(p, k & ~((p->s).flags >> 4));
      }
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

// 0x0809468C -- turret sweep: clear the aim bit, flip toward the stored side,
// step the aim angle and re-enter the motion at the new frame.
// Case 0 is byte-exact (pinned r2 address + transfer-asm XOR copy + separate
// "1" constants + load-before-const ordering). Blocker is confined to case 1:
// retail reuses the now-dead flip-pointer register r6 for a copy of d.x
// (`adds r6,r1,#0`) and rotates {d.x, sum, limit} through r1/r2/r3, where
// ours lands r3/r1/r2 with no copy. Reload-after-call and const-sinking fixed
// the ordering; the rotation itself resisted pins on each of the three.
NON_MATCH void FUN_0809468c(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      u8* bd;
      u32 xf;
      u8 z;
      s32 dx;
      {
        s32* w = (s32*)((u8*)p + 0xb8);
        *w &= ~1;
      }
      SetMotion(&p->s, MOTION(0x8E, 0x06));
      {
        register u8* a asm("r2");
        register u8 bv asm("r1");
        u32 one;
        a = (u8*)p + 0xbd;
        bv = *a;
        one = 1;
        asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(one));
        xf ^= bv;
        bd = a;
        if (xf != 0) {
          (p->s).flags |= 0x10;
        } else {
          (p->s).flags &= 0xEF;
        }
        {
          u32 xv = 1;
          xv &= xf;
          ((p->s).spr).xflip = xv;
          z = 0;
          {
            u8* oa = (u8*)p + 0x4a;
            u32 sh4 = xv << 4;
            s32 ov = *oa;
            s32 m11 = -0x11;
            m11 &= ov;
            m11 |= sh4;
            *oa = m11;
          }
        }
      }
      dx = 0x100;
      (p->s).d.x = dx;
      (p->s).d.x = dx - (*bd << 9);
      UpdateMotionGraphic(&p->s);
      (p->s).d.y = z;
      (p->s).work[2] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      if ((u8)FUN_08093a98(p, (p->s).d.x) == 0) {
        u8 fl = 0;
        s32 dx = (p->s).d.x;
        s32 ny = (p->s).d.y + dx;
        s32 lim;
        (p->s).d.y = ny;
        lim = 0x100;
        if (ny > lim) {
          (p->s).d.y = ny - 0x100;
          goto turn;
        }
        if (ny < -0x100) {
          (p->s).d.y = ny + lim;
          fl = 1;
        }
        if (fl != 0) {
        turn: {
          u32 a;
          (p->s).work[2] &= 7;
          a = 0;
          if (dx > 0) {
            a = 1;
          }
          if ((p->s).flags & X_FLIP) {
            if (a != 0) {
              goto dec;
            }
            goto incm;
          }
          if (a == 0) {
            goto incm;
          }
        dec:
          (p->s).work[2]--;
          goto go;
        incm:
          (p->s).work[2]++;
        go:
          GotoMotion(&p->s, MOTION(0x8E, 0x06), (p->s).work[2], 1);
          UpdateMotionGraphic(&p->s);
        }
        }
      }
      {
        u8 r = FUN_08093a64(p, 1);
        if (r == 0) {
          *((u8*)p + 0xbc) = 2;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = r;
        }
      }
      break;
    }
  }
#else
  INCCODE("asm/enemy/shotloid_9468c.inc");
#endif
}

#include "mission.h"
#include "vfx.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
void FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
static const motion_t sMotions[5];

// 0x080947c4
void FUN_080947c4(struct Enemy* p) {
  struct Coord c;
  struct Coord* co;
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
  c.y = (p->s).coord.y - 0x1000;
  CreateSmoke(1, &c);
  PlaySound(0x2a);
  if ((p->s).work[1] == 0) {
    FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 4);
  } else {
    FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions, 4);
  }
  co = &(p->s).coord;
  TryDropItem(4, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}

INCASM("asm/enemy/shotloid_post_p2_p2c.inc");

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
