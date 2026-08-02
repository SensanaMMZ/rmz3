#include "collision.h"
#include "definition.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "physics.h"
#include "story.h"
#include "metatile.h"

static const struct Collision sCollisions[];

struct Enemy* createPantheonFistInElevator(s32 x, s32 y, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_FIST);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    p->props[5] = a2;
  }
  return p;
}

bool8 FUN_08094fa8(struct Enemy* p, s32 d) {
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

bool8 FUN_08094fe0(struct Enemy* p, s32 dy) {
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

u32 FUN_08095014(struct Enemy* p, s32 d) {
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

u32 FUN_08095074(struct Enemy* p, s32 dx) {
  if (dx == 0) {
    return 0;
  }
  if (dx < 0) {
    if (FUN_080098a4((p->s).coord.x - 0xE00, (p->s).coord.y - 0xA00) != 0) {
      return 1;
    }
  } else {
    if (FUN_080098a4((p->s).coord.x + 0xE00, (p->s).coord.y - 0xA00) != 0) {
      return 2;
    }
  }
  return 0;
}

void nop_080950cc(struct Enemy* p) {}

bool8 FUN_080950d0(struct Enemy* p) {
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

// 0x08095124
bool8 FUN_08095124(struct Enemy* p) {
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

struct PantheonFistObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct VFX* elementEffect;
  u8 unk_004[12];
};
static_assert(sizeof(struct PantheonFistObject) == sizeof(struct Enemy));

static const struct Coord sElementCoord;

void FUN_080951b4(struct PantheonFistObject* p) {
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

INCASM("asm/enemy/pantheon_fist_pre_p2_a_b.inc");


void PantheonFist_Update(struct Enemy* p) {
  if (!FUN_080950d0(p)) {
    FUN_080951b4((struct PantheonFistObject*)p);
    if (!FUN_08095124(p)) {
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}


static const EnemyFunc sDeads[3];

// 0x08095340
void PantheonFist_Die(struct Enemy* p) {
  if ((p->s).work[1] == 0 && IS_METTAUR) {
    u8 fl = (p->s).flags & ~DISPLAY;
    (p->s).flags = fl & ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (sDeads[(p->s).mode[1]])(p);
  }
}

void FUN_080953ac(struct Enemy* p) {}


void FUN_080953b0(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}


void FUN_080953d0(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
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

void FUN_0809542c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0xd4, 0x06));
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 f = IsFrozen(&p->s);
      if (f == 0) {
        (p->s).d.y += 0x40;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        {
          s32 r = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
          if (r < 0) {
            (p->s).coord.y += r;
            (p->s).d.y = f;
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/enemy/pantheon_fist_post_p2_p2.inc");

void FUN_08095664(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 on = 0;
      u8 rv;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        on = 1;
      }
      rv = FUN_08094fa8(p, (on << 8) - 0x80);
      if (rv == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = rv;
        return;
      }
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x02));
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      s32 on3 = 0;
      s32 on;
      s32 d;
      u8 rv2;
      if ((p->s).coord.x < (pZero2->s).coord.x) {
        on3 = 1;
      }
      on = on3;
      {
        bool8 xf2 = on;
        if (on) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
        ((p->s).spr).xflip = xf2 & 1;
        ((p->s).spr).oam.xflip = xf2;
      }
      if ((u32)((pZero2->s).coord.x - (p->s).coord.x + 0x3200) <= 0x63FF) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
      d = (on << 8) - 0x80;
      if (FUN_08094fa8(p, d) == 0 || (u8)FUN_08095014(p, d) != 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      rv2 = FUN_08094fe0(p, 1);
      if (rv2 == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = rv2;
      }
      break;
    }
  }
}

// 0x08095778
void FUN_08095778(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x03));
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
    case 1: {
      s32 d;
      u8 t;
      UpdateMotionGraphic(&p->s);
      d = (p->s).work[2] - 1;
      (p->s).work[2] = d;
      t = d;
      if (t == 0) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = t;
      }
      FUN_08094fe0(p, 1);
      break;
    }
  }
}

void CreateSmoke(u8 n, struct Coord* c);

// 0x080957D4
void FUN_080957d4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 k;
      s32 v;
      PlaySound(0x109);
      SetDDP(&p->body, &sCollisions[3]);
      k = 0x10;
      (p->s).unk_coord.x = k;
      (p->s).work[2] = Sqrt(0x500);
      v = (p->s).work[2] * (p->s).unk_coord.x;
      (p->s).d.x = v;
      k &= (p->s).flags;
      if (k == 0) {
        (p->s).d.x = -v;
      } else {
        (p->s).unk_coord.x = -(p->s).unk_coord.x;
      }
      (p->s).work[3] = 0;
      SetMotion(&p->s, MOTION(0xD4, 0x04));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      u32 one;
      u32 four;
      u32 st;
      UpdateMotionGraphic(&p->s);
      st = (pZero2->body).status;
      one = 1;
      if ((st & one) == 0) {
        goto move;
      }
      {
        u32 st2 = (p->body).status;
        four = 4;
        if ((st2 & four) != 0 && (p->s).work[2] > 0x10) {
          u8 w3 = (p->s).work[3];
          if (w3 == 0) {
            PlaySound(0x52);
            (p->s).work[3] = one;
            *((u8*)pZero2 + 0x122) = one;
            (pZero2->s).mode[1] = four;
            (pZero2->s).mode[2] = w3;
          }
        }
      }
    move:
      (p->s).d.x += (p->s).unk_coord.x;
      (p->s).work[2]--;
      {
        u8 w = (p->s).work[2];
        if ((3 & w) == 0 && w > 8) {
          CreateSmoke(3, &(p->s).coord);
        }
      }
      if ((u8)FUN_08094fa8(p, (p->s).d.x) == 0) {
        goto reset;
      }
      if ((p->s).work[2] == 0) {
        goto reset;
      }
      if ((u8)FUN_08095014(p, (p->s).d.x) == 0) {
        goto tick;
      }
    reset : {
      u8 z2 = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z2;
    }
    tick:
      UpdateMotionGraphic(&p->s);
      if ((u8)FUN_08094fe0(p, 1) == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      FUN_08094fe0(p, 1);
      break;
    }
  }
}

void FUN_08095914(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xD4, 0x05));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      FUN_08094fe0(p, 1);
      break;
  }
}

INCASM("asm/enemy/pantheon_fist_post_p2_p2b.inc");

#include "mission.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
void FUN_080b7f70(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);
static const motion_t sMotions[4];

// 0x08095b70
void FUN_08095b70(struct Enemy* p) {
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
    FUN_080b7f70(&p->s, &c, (motion_t*)sMotions, 3);
  } else {
    FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions, 3);
  }
  co = &(p->s).coord;
  TryDropItem(4, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}

INCASM("asm/enemy/pantheon_fist_post_p2_p2b_b.inc");

void PantheonFist_Init(struct Enemy* p);
void PantheonFist_Update(struct Enemy* p);
void PantheonFist_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonFistRoutine = {
    [ENTITY_INIT] =      PantheonFist_Init,
    [ENTITY_UPDATE] =    PantheonFist_Update,
    [ENTITY_DIE] =       PantheonFist_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080953ac(struct Enemy* p);
void FUN_080953b0(struct Enemy* p);
void FUN_080953d0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[9] = {
    FUN_080953d0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953b0,
    FUN_080953ac,
    FUN_080953b0,
};
// clang-format on

void FUN_0809542c(struct Enemy* p);
void FUN_080954a4(struct Enemy* p);
void FUN_08095578(struct Enemy* p);
void FUN_08095664(struct Enemy* p);
void FUN_08095778(struct Enemy* p);
void FUN_080957d4(struct Enemy* p);
void FUN_08095914(struct Enemy* p);
void FUN_0809596c(struct Enemy* p);
void FUN_08095ac4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[9] = {
    FUN_0809542c,
    FUN_080954a4,
    FUN_08095578,
    FUN_08095664,
    FUN_08095778,
    FUN_080957d4,
    FUN_08095914,
    FUN_0809596c,
    FUN_08095ac4,
};
// clang-format on

// --------------------------------------------

void FUN_08095b70(struct Enemy* p);
void FUN_08095c20(struct Enemy* p);
void FUN_0809596c(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_08095b70,
    FUN_08095c20,
    FUN_0809596c,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
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
      layer : 1,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : BODY_NATURE_B2,
      remaining : 1,
      layer : 1,
      range : {-PIXEL(22), -PIXEL(19), PIXEL(26), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      nature : BODY_NATURE_B2,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(10), -PIXEL(13), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 0,
      layer : 1,
      range : {-PIXEL(4), -PIXEL(15), PIXEL(19), PIXEL(31)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
static const u8 sInitModes[2] = {2, 0};

static const motion_t sMotions[4] = {
    MOTION(SM212_PANTHEON_FIST, 9),
    MOTION(SM212_PANTHEON_FIST, 10),
    MOTION(SM212_PANTHEON_FIST, 11),
    MOTION(SM212_PANTHEON_FIST, 7),
};
