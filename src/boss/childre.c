#include "boss.h"
#include "collision.h"
#include "global.h"
#include "motion.h"
#include "stagerun.h"
#include "zero.h"

static const u8 sInitModes[4];
static const struct Collision sCollisions[];
extern const u8 u8_ARRAY_ARRAY_0836202c[3][16];
extern const u8 u8_ARRAY_0836205c[4];

static void Childre_Init(struct Boss* p);
static void Childre_Update(struct Boss* p);
static void Childre_Die(struct Boss* p);

// clang-format off
const BossRoutine gChildreRoutine = {
    [ENTITY_INIT] =      Childre_Init,
    [ENTITY_UPDATE] =    Childre_Update,
    [ENTITY_DIE] =       Childre_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// Picks the next childre action: an RNG index into a distance-selected row of
// u8_ARRAY_ARRAY_0836202c, retried while it repeats the last action (up to the
// repeat counter), then maps it to a motion via u8_ARRAY_0836205c. Retail keeps
// the boss ptr in ip and re-loads the row-table base each loop iteration; agbcc
// hoists that loop-invariant base into a callee-saved reg, an allocation it
// won't reproduce from clean C, so dual-form it.
NON_MATCH void childre_08040428(struct Boss* p) {
#if MODERN
  u8 action;
  s32 dx = pZero2->s.coord.x - (p->s).coord.x;
  if (dx < 0) {
    dx = -dx;
  }
  do {
    u32 rand;
    RNG_0202f388 = LCG(RNG_0202f388);
    rand = (RNG_0202f388 >> 17) & 0xf;
    if (dx <= 0x4FFF) {
      action = u8_ARRAY_ARRAY_0836202c[0][rand];
    } else if (dx <= 0x8FFF) {
      action = u8_ARRAY_ARRAY_0836202c[1][rand];
    } else {
      action = u8_ARRAY_ARRAY_0836202c[2][rand];
    }
  } while (action == ((p->props).childre).unk_c4 && ((p->props).childre).unk_c5 > 1);
  if (((p->props).childre).unk_c4 == action) {
    ((p->props).childre).unk_c5++;
  } else {
    ((p->props).childre).unk_c4 = action;
    ((p->props).childre).unk_c5 = 0;
  }
  (p->s).mode[1] = u8_ARRAY_0836205c[action];
  if (action <= 1) {
    (p->s).work[2] = action;
  }
  (p->s).mode[2] = 0;
#else
  INCCODE("asm/wip/childre_08040428.inc");
#endif
}

static void onCollision(struct Body* body, struct Coord* c1, struct Coord* c2) {
  struct Zero* z = (struct Zero*)body->enemy->parent;
  struct Boss* boss = (struct Boss*)body->parent;

  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    (boss->props.childre).unk_c8.x = (z->s).coord.x;
    (boss->props.childre).unk_c8.y = (z->s).coord.y;
    (boss->props.childre).shouldTurnRight = (boss->s).coord.x < (z->s).coord.x;
  }
}

static bool8 tryKillChildre(struct Boss* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    PlaySound(SE_CHILDRE_DEATH);
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else {
      (p->s).mode[1] = 0;
    }
    Childre_Die(p);
    return TRUE;
  }

  return FALSE;
}

// --------------------------------------------

static void Childre_Init(struct Boss* p) {
  struct Body* body;
  s32 y;
  void* fn;

  // TODO: Kill them all
#if MODERN == 0
  register u32 r0 asm("r0");
  register u8 r1 asm("r1");
  register u8* r2 asm("r2");
#endif

  SET_BOSS_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);

  ResetBossBody(p, &sCollisions[0], 64);
  fn = onCollision;
  body = &p->body;
  body->fn = fn;

  if ((p->s).work[0] == 0) {
    LOAD_STATIC_GRAPHIC(SM036_UNK);
    LOAD_STATIC_GRAPHIC(SM037_EAR_SHOT);
    LOAD_STATIC_GRAPHIC(SM038_UNK);
    ((p->props).childre).unk_b4 = NULL;

    y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).coord.y = y;
    ((p->props).childre).unk_bc.y = y;

    ((p->props).childre).unk_bc.x = (((p->s).coord.x / PIXEL(240)) * PIXEL(240)) + PIXEL(120);

#if MODERN
    ((p->props).childre).unk_c4 = 0xFF;
#else
    r2 = &((p->props).childre).unk_c4;
    r0 = *r2;
    r1 = 0xFF;
    r0 |= r1;
    *r2 = r0;
#endif
    ((p->props).childre).unk_c5 = 0;
  }
  Childre_Update(p);
}

// --------------------------------------------

void childreNeutral(struct Boss* p);
static void nop_08040788(struct Boss* p);

void childreMode0(struct Boss* p);
void childreMode1(struct Boss* p);
void childreMode2(struct Boss* p);
void childreMode3(struct Boss* p);
void childreStartRising(struct Boss* p);
void childreRising(struct Boss* p);
void childreMode6(struct Boss* p);
void childreMode7(struct Boss* p);
void childreMode8(struct Boss* p);
void childreStartScrewIce(struct Boss* p);
void childreMaybeMiddleScrewIce(struct Boss* p);
void childreScrewIce(struct Boss* p);
void childreMissile(struct Boss* p);
void childreStartEarShot(struct Boss* p);
void childreEarShot(struct Boss* p);
void childreEndEarShot(struct Boss* p);
void childreMode16(struct Boss* p);
void childreStun(struct Boss* p);
void childreMode18(struct Boss* p);

static void Childre_Update(struct Boss* p) {
  // clang-format off
  static const BossFunc sUpdates1[19] = {
      childreNeutral,
      nop_08040788,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      childreNeutral,
      nop_08040788,
      nop_08040788,
      nop_08040788,
  };
  // clang-format on

  // clang-format off
  static const BossFunc sUpdates2[19] = {
      childreMode0,
      childreMode1,
      childreMode2,
      childreMode3,
      childreStartRising,
      childreRising,
      childreMode6,
      childreMode7,
      childreMode8,
      childreStartScrewIce,
      childreMaybeMiddleScrewIce,
      childreScrewIce,
      childreMissile,
      childreStartEarShot,
      childreEarShot,
      childreEndEarShot,
      childreMode16,
      childreStun,
      childreMode18,
  };
  // clang-format on

  bool8 killed;

  struct Entity* e = ((p->props).childre).unk_b4;
  if ((e != NULL) && isKilled(e)) {
    ((p->props).childre).unk_b4 = NULL;
  }

  killed = tryKillChildre(p);
  if (!killed) {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

// --------------------------------------------

void childre_08042140(struct Boss* p);
void childre_08042224(struct Boss* p);

static void Childre_Die(struct Boss* p) {
  static const BossFunc sDeads[2] = {
      childre_08042140,
      childre_08042224,
  };
  (sDeads[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void nop_08040788(struct Boss* p) {
  // nop
  return;
}

INCASM("asm/boss/childre_pre_a.inc");

// 170==170 instructions; register-name ties in the side-check subtraction
// and the attr1 anchor (same class as childreMode1's recorded tie).
NON_MATCH void childreMode0(struct Boss* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      u32 onLeft;
      (p->s).coord.y = *(s32*)((u8*)p + 0xc0);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0;
      onLeft = (u32)((pZero2->s).coord.x - (p->s).coord.x) >> 31;
      if ((p->s).flags & X_FLIP) {
        if (onLeft != 0) goto turn;
      } else if (onLeft == 0) {
        goto turn;
      }
      (p->s).mode[2] += 2;
      break;
    turn:
      PlaySound(0x67);
      SetMotion(&p->s, MOTION(0xA4, 8));
      (p->s).d.y = -0x200;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      t = *(s32*)((u8*)p + 0xc0) - (p->s).coord.y;
      if (t < 0) {
        (p->s).coord.y += t;
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == MOTION_END) {
        (p->s).work[2] = 1;
        (p->s).mode[2]++;
      }
      break;
    }
    case 2: {
      if ((p->s).work[2] != 0) {
        u8 inv;
        ((p->s).spr).xflip = (((p->s).flags >> 4) ^ 1) & 1;
        inv = (((p->s).flags >> 4) ^ 1) & 1;
        *((u8*)&((p->s).spr).oam + 6) = (*((u8*)&((p->s).spr).oam + 6) & ~0x11) | (inv << 4);
        if (inv) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
      }
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x20;
      SetMotion(&p->s, MOTION(0xA4, 0));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      (p->s).work[2]--;
      if ((p->s).work[2] == 0) {
        if (!((pZero2->body).status & BODY_STATUS_DEAD) && (pZero2->body).hp != 0) {
          childre_08040428(p);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/boss/childre_mode0.inc");
#endif
}

INCASM("asm/boss/childre_pre_b.inc");

// 0x0804102C
void childreStartRising(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 sq;
      s32 tx;
      PlaySound(0x67);
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).coord.y -= 0x800;
      sq = 0x100;
      sq = (u16)Sqrt(sq);
      (p->s).d.y = -(sq << 6);
      (p->s).coord.y += (p->s).d.y;
      {
        s32 base = *(s32*)((u8*)p + 0xbc);
        (p->s).d.x = base - 0x6000;
        tx = (p->s).d.x;
        if ((p->s).flags & X_FLIP) {
          tx = base + 0x6000;
        }
      }
      (p->s).d.x = tx - (p->s).coord.x;
      (p->s).d.x /= sq;
      SetMotion(&p->s, 0xA41A);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 fl = 0;
      s32* pbc;
      s32 nx = (p->s).coord.x + (p->s).d.x;
      register s32 dd asm("r5");
      (p->s).coord.x = nx;
      pbc = (s32*)((u8*)p + 0xbc);
      {
        s32 bv = *pbc;
        dd = bv - nx;
        asm volatile("" :: "r"(bv));
        asm volatile("" :: "r"(nx));
      }
      if ((u32)(dd + 0x6800) > 0xD000) {
        fl = 1;
      }
      asm volatile("" :: "r"(dd));
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      if (fl != 0 || (p->s).d.y > 0) {
        s32 base2 = *pbc;
        s32 tx2;
        (p->s).coord.x = base2 - 0x6800;
        tx2 = (p->s).coord.x;
        if ((p->s).flags & X_FLIP) {
          s32 k68;
          asm("movs %0, #0xD0
	lsl %0, %0, #7" : "=l"(k68));
          tx2 = base2 + k68;
        }
        (p->s).coord.x = tx2;
        {
          s32 z = 0;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = z;
        }
      }
      if ((s8)(p->s).motion.cmdIdx != 6) {
        UpdateMotionGraphic(&p->s);
      }
      break;
    }
  }
}

INCASM("asm/boss/childre_pre_b2.inc");

// 0x08041320
void childreMode6(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 xf;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).flags &= ~DISPLAY;
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      xf = (((p->s).flags >> 4) ^ 1) & 1;
      ((p->s).spr).xflip = xf;
      {
        u32 xf2 = (((p->s).flags >> 4) ^ 1) & 1;
        u8* oa = (u8*)p + 0x4a;
        u32 sh4 = xf2 << 4;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
        if (xf2 != 0) {
          (p->s).flags |= 0x10;
        } else {
          (p->s).flags &= 0xEF;
        }
      }
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if ((u8)--(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      u8 fl;
      s32 base;
      register s32 x asm("r1");
      s32 z;
      base = *(s32*)((u8*)p + 0xbc);
      {
        s32 t = base + 0x5000;
        (p->s).coord.x = t;
        asm volatile("add %0, %1, #0" : "=&l"(x) : "l"(t));
      }
      fl = (p->s).flags;
      if (fl & X_FLIP) {
        x = base - 0x5000;
      }
      (p->s).coord.x = x;
      {
        u8 k = DISPLAY;
        register u8 res asm("r0");
        asm("" : "+r"(k));
        z = 0;
        res = k | fl;
        (p->s).flags = res;
      }
      SetMotion(&p->s, MOTION(0xA4, 0x06));
      (p->s).d.y = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 y;
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      if (y > gOverworld.sea) {
        u8 z2;
        (p->s).coord.y = gOverworld.sea;
        z2 = 0;
        (p->s).mode[1] = 7;
        (p->s).mode[2] = z2;
      }
      break;
    }
  }
}

INCASM("asm/boss/childre_pre_b3.inc");

void childreEndEarShot(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xa4, 0x16));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/childre_post_a.inc");

void childreMode18(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x6d);
      (p->s).flags |= DISPLAY;
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      SetMotion(&p->s, 0xA41F);
      {
        s32 y, dx, dy, dist, nx, ny;
        y = (p->s).coord.y;
        (p->s).coord.y = y + 0x800;
        dx = (p->s).coord.x - *(s32*)((u8*)p + 0xc8);
        (p->s).d.x = dx;
        dy = y - 0x2800;
        dy -= *(s32*)((u8*)p + 0xcc);
        (p->s).d.y = dy;
        dist = (dx >> 8) * (dx >> 8);
        dist += (dy >> 8) * (dy >> 8);
        dist = Sqrt(dist) << 8;
        nx = ((p->s).d.x << 8) / dist;
        (p->s).d.x = nx;
        ny = ((p->s).d.y << 8) / dist;
        (p->s).d.y = ny;
        (p->s).d.x = nx * 1408 / 256;
        (p->s).d.y = ny * 1408 / 256;
      }
      (p->s).mode[2]++;
      // fallthrough
    case 1: {
      register s32 rem asm("r6");
      s32 x, bx;
      x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      bx = *(s32*)((u8*)p + 0xbc);
      if (x > bx + 0x6000) {
        (p->s).coord.x = bx + 0x6000;
      } else if (x < bx - 0x6000) {
        (p->s).coord.x = bx - 0x6000;
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      {
        s32 ny = (p->s).coord.y + (p->s).d.y;
        (p->s).coord.y = ny;
        {
          register s32 tmp asm("r0");
          tmp = *(s32*)((u8*)p + 0xc0) + 0x800;
          rem = tmp - ny;
        }
        if (rem < 0 && (p->s).d.y > 0) {
          (p->s).coord.y = ny + rem;
        }
      }
      UpdateMotionGraphic(&p->s);
      if (rem < 0 && (p->s).d.y > 0) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
    }
  }
}

INCASM("asm/boss/childre_post_b.inc");

// --------------------------------------------

// 0x08361eac
static const struct Collision sCollisions[16] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x0D00, 0x1400, 0x1A00},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x08,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x0D00, 0x1400, 0x1A00},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1300, 0x1500},
    },
    [4] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x08,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x1300, 0x1500},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1200, 0x1000, 0x3800},
    },
    [6] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x08,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x2600, 0x1200, 0x1800},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1200, 0x1000, 0x3800},
    },
    [8] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x08,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x2600, 0x1200, 0x1800},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x0D00, 0x1400, 0x1A00},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x1000, -0x0E00, 0x3000, 0x0E00},
    },
    [11] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x08,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x0D00, 0x1400, 0x1A00},
    },
    [12] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000001,
      range : {0x0000, -0x0D00, 0x1400, 0x1A00},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x2200, -0x0B00, 0x5200, 0x0E00},
    },
    [14] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0E00, -0x0C00, 0x2B00, 0x2200},
    },
    [15] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x08,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x0D00, 0x1400, 0x1A00},
    },
};

const u8 u8_ARRAY_ARRAY_0836202c[3][16] = {
    {0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3},
    {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3},
    {0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3},
};

const u8 u8_ARRAY_0836205c[4] = {2, 2, 12, 13};

static const u8 sInitModes[4] = {1, 16, 0, 0};

const struct Coord Coord_08362064 = {0, -0x1000};

const s16 s16_0836206c = 0x2601;

// clang-format off
const motion_t sChildreMotions[6] = {
    MOTION(DM164_CHILDRE, 0x10),
    MOTION(DM164_CHILDRE, 0x11),
    MOTION(DM164_CHILDRE, 0x11),
    MOTION(DM164_CHILDRE, 0x11),
    MOTION(DM164_CHILDRE, 0x11),
    MOTION(DM164_CHILDRE, 0x12),
};
// clang-format on

const struct Coord Coord_0836207c = {0x200, 0xFFFFE800};
const struct Coord Coord_08362084 = {0x600, 0xFFFFE700};
