#include "boss.h"
#include "collision.h"
#include "global.h"
#include "stagerun.h"
#include "zero.h"
#include "vfx.h"
#include "physics.h"
#include "vfx.h"

static const BossFunc sDeads[5];


void FUN_08061b68(struct Boss* p, s32 dx, s32 dy) {
  struct Coord c;
  u32 a = *(u16*)&(p->props).raw[4] >> 8;
  s32 sinv, cosv;
  if ((p->s).flags & 0x10) {
    dx = -dx;
  }
  cosv = gSineTable[(u8)(a + 0x40)];
  c.x = dx * cosv / 256;
  sinv = gSineTable[a];
  c.x += -sinv * dy / 256;
  c.y = dx * sinv / 256;
  c.y += dy * cosv / 256;
  c.x = (p->s).coord.x + c.x;
  c.y = (p->s).coord.y + c.y;
  CreateSmoke(3, &c);
}

INCASM("asm/boss/spearook_p1_pre_pre_a.inc");

#include "entity/macros.h"

struct Boss* FUN_08061c74(struct Entity* e) {
  struct Boss* p = (struct Boss*)AllocEntityFirst(gBossHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_BOSS_ROUTINE(p, 24);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).unk_28 = e;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
  return p;
}

void FUN_08061ccc(struct Entity* e, struct Entity* e2) {
  struct Boss* p = (struct Boss*)AllocEntityFirst(gBossHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_BOSS_ROUTINE(p, 24);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).unk_28 = e;
    (p->s).unk_2c = e2;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = e->uniqueID;
  }
}

// 0x08061d24 -- parked (address-derivation basin): retail keeps the boss
// pointer live in r2 and derives +0xc0/+0xbc through a fresh temp with a
// subs #4 chain; agbcc either parks the pointer in ip (+3) or ties the
// derived address in place. Both RANDOM offsets and the hp doubling are
// decoded and verified.
NON_MATCH void FUN_08061d24(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
#if MODERN
  struct Boss* q = (struct Boss*)body->parent;
  u8 w0 = (q->s).work[0];
  if (w0 == 1) {
    if (body->hitboxFlags & 8) {
      s32 f = 0;
      u8* c0;
      if ((q->s).coord.x < (pZero2->s).coord.x) {
        f = 1;
      }
      c0 = (u8*)q + 0xc0;
      *c0 = f;
    }
  } else if (w0 == 0) {
    if (body->hitboxFlags & 1) {
      s32 f = 0;
      u16* hp;
      u8* c1;
      u8* c0;
      if ((q->s).coord.x < (pZero2->s).coord.x) {
        f = 1;
      }
      c0 = (u8*)q + 0xc0;
      *c0 = f;
      hp = (u16*)((u8*)q + 0xa4);
      c1 = (u8*)q + 0xc1;
      if (*(s32*)(c0 - 4) & 2) {
        struct Coord c;
        *hp = *hp * 2 - *c1;
        c.x = (q->s).coord.x - 0x800 + (RANDOM(RNG_0202f388) & 0x7FF);
        c.y = (q->s).coord.y - 0x1400 + (RANDOM(RNG_0202f388) & 0x7FF);
        CreateSmoke(1, &c);
        PlaySound(0x2A);
      }
      *c1 = *hp;
    }
  }
#else
  INCCODE("asm/boss/spearook_1d24.inc");
#endif
}

INCASM("asm/boss/spearook_p1_pre_pre_bc_b.inc");

#include "element.h"
#include "vfx.h"

static const struct Coord sElementCoord;

void FUN_08061ef0(struct Boss* p) {
  struct VFX** slot = (struct VFX**)&(p->props).raw[0];

  if (*slot == NULL && ((p->body).status & 1)) {
    *slot = ApplyElementEffect(0, &p->s, &sElementCoord);
    if (*slot != NULL) {
      *(u32*)&(p->props).raw[8] &= ~4;
      (p->s).mode[1] = 15;
      (p->s).mode[2] = 0;
    }
  }
}

INCASM("asm/boss/spearook_p1_pre_pre_b.inc");


void Spearook_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08062264(struct Boss* p) {}

void FUN_08062268(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

void FUN_0806228c(struct Boss* p) {
  if ((p->body).status & 8) {
    if ((p->body).status & 0x20000) {
      *(s16*)((u8*)p + 0xba) += 0x4000;
      *(s16*)((u8*)p + 0xba) -= *((u8*)p + 0xc0) << 15;
    } else {
      *(s16*)((u8*)p + 0xba) += 0x800;
      *(s16*)((u8*)p + 0xba) -= *((u8*)p + 0xc0) << 12;
    }
    if (*(s16*)((u8*)p + 0xba) < -0x4000) {
      u16 c = 0xC000;
      *(u16*)((u8*)p + 0xba) = c;
    } else if (*(s16*)((u8*)p + 0xba) > 0x4000) {
      *(s16*)((u8*)p + 0xba) = 0x4000;
    }
  }
}

void FUN_08062304(struct Boss* p) {
  u32 v = *(u32*)((u8*)p + 0x8c);
  if (v & 1) {
    if (v & 0x20000) {
      *(u32*)((u8*)p + 0xbc) &= ~4;
      (p->s).mode[1] = 14;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_08061bf8(struct Boss* p);

// 0x08062338
void FUN_08062338(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x0836579C);
      (p->s).work[2] = 0x18;
      SetMotion(&p->s, MOTION(0xD6, 0x00));
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 t = (u8)--(p->s).work[2];
      if (t == 0) {
        u8 v = *((u8*)p + 0xC4);
        u8* c = (u8*)p + 0xC4;
        if (v == 0) {
          FUN_08061bf8(p);
        } else {
          (p->s).mode[1] = 4;
          (p->s).mode[2] = t;
        }
        (*c)++;
        if (*c > 1) {
          *c = 0;
        }
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      break;
    }
  }
}

INCASM("asm/boss/spearook_p1_post_p2_a.inc");

// 0x08062b70
void FUN_08062b70(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      *(u32*)&(p->props).raw[8] |= 0x20;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      u32 f = *(u32*)&(p->props).raw[8] & 0x20;
      if (f == 0) {
        (p->s).mode[1] = f;
        (p->s).mode[2] = f;
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      break;
    }
  }
}

INCASM("asm/boss/spearook_p1_post_p2_b.inc");

void FUN_08061b68(struct Boss* p, s32 dx, s32 dy);

// 0x08062fe0
void FUN_08062fe0(struct Boss* p) {
  struct Entity* q = (p->s).unk_28;
  u8 m;
  (p->s).coord.x = (q->coord).x;
  (p->s).coord.y = (q->coord).y - 0x1200;
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetDDP(&p->body, (const struct Collision*)0x083657CC);
      SetMotion(&p->s, MOTION(0xD6, 0x04));
      (p->s).d.x = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).d.x++;
      (p->s).d.x %= 15;
      if ((p->s).d.x == 0) {
        FUN_08061b68(p, 0xF00, -0x3100);
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        *(u32*)((u8*)q + 0xbc) &= ~0x20;
        (p->s).mode[1] = 2, (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/spearook_p1_post_p2_c.inc");

void nop_0806316c(struct Boss* p) {}

void nop_08063170(struct Boss* p) {}

INCASM("asm/boss/spearook_p3.inc");

void FUN_080632a0(struct Boss* p0) {
  register struct Boss* p asm("r2") = p0;
  if ((p->s).mode[2] == 0) {
    register struct StageRun* sr asm("r4");
    register u32 st asm("r3");
    register s32 one asm("r5");
    register u32 av asm("r1");
    sr = &gStageRun;
    st = sr->missionStatus;
    one = 1;
    if (one & st) {
      register s32 chk asm("r0");
      av = sr->vm.active;
      chk = one & av;
      if (chk == 0) {
        sr->missionStatus = (st & 0xFFFE) | MISSION_SUCCESS;
      }
    }
    EXIT_BODY(p);
    (p->s).mode[2]++;
  }
}

INCASM("asm/boss/spearook_p3b.inc");

void nop_08063510(struct Boss* p) {}

void FUN_08063514(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      EXIT_BODY(p);
      (p->s).d.y = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      {
        s32 push = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (push < 0) {
          (p->s).coord.y += push;
          CreateSmoke(1, &(p->s).coord);
          PlaySound(0x2a);
          (p->s).flags &= ~DISPLAY;
          (p->s).flags &= ~FLIPABLE;
          EXIT_BODY(p);
          SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      break;
  }
}

void Spearook_Init(struct Boss* p);
void Spearook_Update(struct Boss* p);
void Spearook_Die(struct Boss* p);

// clang-format off
const BossRoutine gSpearookRoutine = {
    [ENTITY_INIT] =      Spearook_Init,
    [ENTITY_UPDATE] =    Spearook_Update,
    [ENTITY_DIE] =       Spearook_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_08062304(struct Boss* p);
void FUN_08062264(struct Boss* p);
void FUN_0806228c(struct Boss* p);
void FUN_08062268(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[17] = {
    FUN_08062304,
    FUN_08062264,
    FUN_0806228c,
    FUN_08062264,
    FUN_08062304,
    FUN_0806228c,
    FUN_08062264,
    FUN_08062304,
    FUN_0806228c,
    FUN_08062304,
    FUN_0806228c,
    FUN_0806228c,
    FUN_0806228c,
    FUN_0806228c,
    FUN_08062304,
    FUN_08062268,
    FUN_08062264,
};
// clang-format on

void FUN_08062338(struct Boss* p);
void FUN_080623bc(struct Boss* p);
void FUN_080624b0(struct Boss* p);
void FUN_08062588(struct Boss* p);
void FUN_0806267c(struct Boss* p);
void FUN_08062754(struct Boss* p);
void FUN_08062848(struct Boss* p);
void FUN_0806293c(struct Boss* p);
void FUN_08062a94(struct Boss* p);
void FUN_08062b70(struct Boss* p);
void FUN_08062bb4(struct Boss* p);
void FUN_08062c78(struct Boss* p);
void FUN_08062e30(struct Boss* p);
void FUN_08062fe0(struct Boss* p);
void FUN_08063074(struct Boss* p);
void nop_0806316c(struct Boss* p);
void nop_08063170(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[17] = {
    FUN_08062338,
    FUN_080623bc,
    FUN_080624b0,
    FUN_08062588,
    FUN_0806267c,
    FUN_08062754,
    FUN_08062848,
    FUN_0806293c,
    FUN_08062a94,
    FUN_08062b70,
    FUN_08062bb4,
    FUN_08062c78,
    FUN_08062e30,
    FUN_08062fe0,
    FUN_08063074,
    nop_0806316c,
    nop_08063170,
};
// clang-format on

// --------------------------------------------

void FUN_08063174(struct Boss* p);
void FUN_080632a0(struct Boss* p);
void FUN_080632f8(struct Boss* p);
void FUN_08063514(struct Boss* p);
void nop_08063510(struct Boss* p);

// clang-format off
static const BossFunc sDeads[5] = {
    FUN_08063174,
    FUN_080632a0,
    FUN_080632f8,
    FUN_08063514,
    nop_08063510,
};
// clang-format on

// --------------------------------------------

// 0x08365784
static const struct Collision sCollisions[17] = {
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
      special : CS_BOSS,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(42), PIXEL(17)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(20), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 5,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 2,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 7,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(64), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 6,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 5,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 3,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(64), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 2,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(46), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(31), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(17), PIXEL(21), PIXEL(12)},
    },
};

static const u8 u8_ARRAY_0836591c[16] = {
    7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9,
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(16)};
static const u8 sInitModes[4] = {1, 2, 3, 16};

static const u8 u8_ARRAY_08365938[16] = {
    3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7,
};
