#include "boss.h"
#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "zero.h"

static const u8 sDeathtanzModes[32];
static const struct Collision sCollisions[];
static const u8 sInitModes[2];

static void Deathtanz_Init(struct Boss* p);
static void Deathtanz_Update(struct Boss* p);
static void Deathtanz_Die(struct Boss* p);

// clang-format off
const BossRoutine gDeathtanzRoutine = {
    [ENTITY_INIT] =      (BossFunc)Deathtanz_Init,
    [ENTITY_UPDATE] =    (BossFunc)Deathtanz_Update,
    [ENTITY_DIE] =       (BossFunc)Deathtanz_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

NAKED static void calcNextAction(struct Boss* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	mov ip, r0\n\
	movs r3, #0\n\
	adds r0, #0xb4\n\
	mov r2, ip\n\
	ldr r1, [r2, #0x54]\n\
	ldr r2, [r0]\n\
	cmp r1, r2\n\
	bge _08048D84\n\
	movs r3, #1\n\
_08048D84:\n\
	ldr r0, _08048DA4 @ =pZero2\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0x54]\n\
	cmp r0, r2\n\
	bge _08048D92\n\
	movs r0, #1\n\
	eors r3, r0\n\
_08048D92:\n\
	ldr r7, _08048DA8 @ =RNG_0202f388\n\
	mov r5, ip\n\
	adds r5, #0xc3\n\
	ldr r0, _08048DAC @ =sDeathtanzModes\n\
	mov r8, r0\n\
	lsls r6, r3, #4\n\
	mov r4, ip\n\
	adds r4, #0xc4\n\
	b _08048DBA\n\
	.align 2, 0\n\
_08048DA4: .4byte pZero2\n\
_08048DA8: .4byte RNG_0202f388\n\
_08048DAC: .4byte sDeathtanzModes\n\
_08048DB0:\n\
	ldr r0, _08048DF8 @ =gMission\n\
	ldr r0, [r0]\n\
	ldrb r0, [r0, #1]\n\
	cmp r0, #4\n\
	bhi _08048DE6\n\
_08048DBA:\n\
	ldr r1, [r7]\n\
	ldr r0, _08048DFC @ =0x000343FD\n\
	muls r0, r1, r0\n\
	ldr r1, _08048E00 @ =0x00269EC3\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	lsrs r1, r0, #1\n\
	str r1, [r7]\n\
	lsrs r3, r0, #0x11\n\
	movs r0, #0xf\n\
	ands r3, r0\n\
	adds r0, r3, r6\n\
	add r0, r8\n\
	ldrb r1, [r5]\n\
	ldrb r2, [r0]\n\
	cmp r1, r2\n\
	bne _08048DE2\n\
	ldrb r0, [r4]\n\
	cmp r0, #0\n\
	bne _08048DBA\n\
_08048DE2:\n\
	cmp r2, #0x11\n\
	beq _08048DB0\n\
_08048DE6:\n\
	adds r0, r3, r6\n\
	add r0, r8\n\
	ldrb r1, [r0]\n\
	ldrb r0, [r5]\n\
	cmp r0, r1\n\
	bne _08048E04\n\
	ldrb r0, [r4]\n\
	adds r0, #1\n\
	b _08048E08\n\
	.align 2, 0\n\
_08048DF8: .4byte gMission\n\
_08048DFC: .4byte 0x000343FD\n\
_08048E00: .4byte 0x00269EC3\n\
_08048E04:\n\
	movs r0, #0\n\
	strb r1, [r5]\n\
_08048E08:\n\
	strb r0, [r4]\n\
	adds r0, r3, r6\n\
	add r0, r8\n\
	ldrb r0, [r0]\n\
	movs r1, #0\n\
	mov r2, ip\n\
	strb r0, [r2, #0xd]\n\
	strb r1, [r2, #0xe]\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}

static void onCollision(struct Body* body, struct Coord* c1, struct Coord* c2) {
  struct Zero* z = (struct Zero*)body->enemy->parent;
  struct Boss* boss = (struct Boss*)body->parent;

  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    (boss->props.deathtanz).unk_c8.x = (z->s).coord.x;
    (boss->props.deathtanz).unk_c8.y = (z->s).coord.y;
    (boss->props.deathtanz).shouldTurnRight = (boss->s).coord.x < (z->s).coord.x;
  }
}

static bool8 tryKillDeathtanz(struct Boss* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    PlaySound(SE_DEATHTANZ_DEATH);
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else {
      (p->s).mode[1] = 0;
    }
    Deathtanz_Die(p);
    return TRUE;
  }

  return FALSE;
}

static void Deathtanz_Init(struct Boss* p) {
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
  SET_BOSS_COLLISION_HANDLER(p, onCollision);

  if ((p->s).work[0] == 0) {
    LOAD_STATIC_GRAPHIC(SM054_DEATHTANZ_ROCK);
    LOAD_STATIC_GRAPHIC(SM055_DEATHTANZ_PROJECTILE);

    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    ((p->props).deathtanz).unk_b4.x = (p->s).coord.x >> 8;
    ((p->props).deathtanz).unk_b4.x = ((((p->props).deathtanz).unk_b4.x / 240) * PIXEL(240)) + PIXEL(120);
    ((p->props).deathtanz).unk_b4.y = (p->s).coord.y;
    ((p->props).deathtanz).unk_bd = 0;
    ((p->props).deathtanz).unk_c1 = 3;
#if MODERN
    ((p->props).deathtanz).unk_c3 = 0xFF;
#else
    r2 = &((p->props).deathtanz).unk_c3;
    r0 = *r2;
    r1 = 0xFF;
    r0 |= r1;
    *r2 = r0;
#endif
    ((p->props).deathtanz).unk_c4 = 0;
  }
  Deathtanz_Update(p);
}

// --------------------------------------------

static void nop_0804908c(void* _);
static void tryMakeFlinch(struct Boss* p);

void deathtanzMode0(struct Boss* p);
void deathtanzNeutral(struct Boss* p);
void deathtanzMode2(struct Boss* p);
void deathtanzMode3(struct Boss* p);
void deathtanzMode4(struct Boss* p);
void deathtanzPreAI(struct Boss* p);
void deathtanzMode6(struct Boss* p);
void deathtanzMode7(struct Boss* p);
void deathtanzMode8(struct Boss* p);
void deathtanzMode9(struct Boss* p);
void deathtanzMode10(struct Boss* p);
void deathtanzMode11(struct Boss* p);
void deathtanzMode12(struct Boss* p);
void deathtanzMode13(struct Boss* p);
void deathtanzMode14(struct Boss* p);
void deathtanzMode15(struct Boss* p);
void deathtanzMode16(struct Boss* p);
void deathtanzEX1(struct Boss* p);
void deathtanzEX2(struct Boss* p);
void deathtanzMode19(struct Boss* p);
void deathtanzKnockBackDamage(struct Boss* p);

static void Deathtanz_Update(struct Boss* p) {
  // clang-format off
  static const BossFunc sUpdates1[21] = {
      (BossFunc)nop_0804908c,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)nop_0804908c,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)tryMakeFlinch,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
      (BossFunc)nop_0804908c,
  };
  // clang-format on

  // clang-format off
  static const BossFunc sUpdates2[21] = {
      (BossFunc)deathtanzMode0,
      (BossFunc)deathtanzNeutral,
      (BossFunc)deathtanzMode2,
      (BossFunc)deathtanzMode3,
      (BossFunc)deathtanzMode4,
      (BossFunc)deathtanzPreAI,
      (BossFunc)deathtanzMode6,
      (BossFunc)deathtanzMode7,
      (BossFunc)deathtanzMode8,
      (BossFunc)deathtanzMode9,
      (BossFunc)deathtanzMode10,
      (BossFunc)deathtanzMode11,
      (BossFunc)deathtanzMode12,
      (BossFunc)deathtanzMode13,
      (BossFunc)deathtanzMode14,
      (BossFunc)deathtanzMode15,
      (BossFunc)deathtanzMode16,
      (BossFunc)deathtanzEX1,
      (BossFunc)deathtanzEX2,
      (BossFunc)deathtanzMode19,
      (BossFunc)deathtanzKnockBackDamage,
  };
  // clang-format on

  bool8 killed = tryKillDeathtanz(p);
  if (!killed) {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

// --------------------------------------------

void FUN_0804ac44(struct Boss* p);
void deathtanz_0804adb0(struct Boss* p);

static void Deathtanz_Die(struct Boss* p) {
  static const BossFunc sDeads[2] = {
      (BossFunc)FUN_0804ac44,
      (BossFunc)deathtanz_0804adb0,
  };
  (sDeads[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void nop_0804908c(void* p) {}

static void tryMakeFlinch(struct Boss* p) {
  if ((p->body).status & BODY_STATUS_WHITE) {
    if ((p->body).status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 20;
      (p->s).mode[2] = 0;
    }
  }
}

INCASM("asm/boss/deathtanz_pre_a.inc");

// 0x08049330
void deathtanzNeutral(struct Boss* p) {
  u8* fp;
  u8 fv;
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      {
        u8* fp0 = (u8*)p + 0xbd;
        fv = *fp0;
        asm volatile("add %0, %1, #0" : "=&l"(fp) : "l"(fp0));
      }
      if (fv != 0) {
        register s32 one asm("r2");
        s32 v;
        s32 v2;
        register u8* oa asm("ip");
        u8* t0;
        v = (p->s).flags >> 4;
        one = 1;
        v ^= one;
        asm("" : "+r"(v));
        v &= one;
        ((p->s).spr).xflip = v;
        v2 = (p->s).flags >> 4;
        v2 ^= one;
        asm("" : "+r"(v2));
        v2 &= one;
        {
          u32 off = 0x4a;
          u32 sh4;
          s32 ov;
          s32 m11;
          register u8* fa asm("r2");
          asm("" : "+r"(off));
          off += (u32)p;
          t0 = (u8*)off;
          oa = t0;
          asm("" : "+r"(oa));
          sh4 = v2 << 4;
          ov = *t0;
          m11 = -0x11;
          asm("" : "+r"(m11));
          m11 &= ov;
          m11 |= sh4;
          fa = oa;
          asm("" : "+r"(fa));
          *fa = m11;
        }
        if (v2 != 0) {
          (p->s).flags |= 0x10;
        } else {
          (p->s).flags &= 0xEF;
        }
      }
      *fp = 0;
      (p->s).work[2] = 8;
      SetMotion(&p->s, 0xA706);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 raw;
      struct Zero* z;
      UpdateMotionGraphic(&p->s);
      raw = (p->s).work[2] - 1;
      (p->s).work[2] = raw;
      if ((raw << 24) != 0) {
        break;
      }
      z = pZero2;
      if (*(u32*)((u8*)z + 0x8c) & 0x200) {
        break;
      }
      if (*(s16*)((u8*)z + 0xa4) == 0) {
        break;
      }
      calcNextAction(p);
      break;
    }
  }
}

INCASM("asm/boss/deathtanz_pre_a2.inc");

void deathtanzMode4(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      motion_t m;
      SetDDP(&p->body, &sCollisions[1]);
      m = MOTION(0xA7, 0x32);
      goto setm;
    case 2:
      m = MOTION(0xA7, 0x33);
    setm:
      SetMotion(&p->s, m);
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 4: {
      s32 v, nv;
      PlaySound(0x5e);
      SetDDP(&p->body, &sCollisions[18]);
      v = Sqrt(0x1C0) << 6;
      nv = -v;
      (p->s).d.x = v;
      if ((p->s).flags & X_FLIP) {
        (p->s).d.x = nv;
      }
      SetMotion(&p->s, MOTION(0xA7, 0x34));
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 5: {
      s32 cx = (p->s).coord.x;
      s32 od = (p->s).d.x;
      (p->s).coord.x = cx + od;
      if ((p->s).flags & X_FLIP) {
        s32 nd = od + 0x40;
        (p->s).d.x = nd;
        if (nd > 0) {
          (p->s).mode[2]++;
        }
      } else {
        s32 nd = od - 0x40;
        (p->s).d.x = nd;
        if (nd < 0) {
          (p->s).mode[2]++;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 6:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xA7, 0x35));
      (p->s).mode[2]++;
      /* fallthrough */
    case 7:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x080498a4
void deathtanzPreAI(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8* c;
      s32 f;
      struct Zero* z;
      s32 px;
      s32 zx;
      ((p->props).deathtanz).unk_bd = 0;
      f = 0;
      z = pZero2;
      px = (p->s).coord.x;
      zx = (z->s).coord.x;
      c = &((p->props).deathtanz).unk_bd;
      if (px > zx) {
        f = 1;
      }
      if ((p->s).flags & X_FLIP) {
        if (f == 0) goto advance;
      } else {
        if (f != 0) goto advance;
      }
      SetDDP(&p->body, &sCollisions[4]);
      *c = 1;
      SetMotion(&p->s, MOTION(0xA7, 0x07));
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
      advance:
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/deathtanz_c.inc");

void FUN_080a08e0(struct Entity* e, s32 x, s32 y, u8 a3);

void deathtanzMode7(struct Boss* p) {
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0:
      SetDDP(&p->body, &sCollisions[28]);
      ((p->props).deathtanz).unk_be = md;
      SetMotion(&p->s, MOTION(0xA7, 0x23));
      (p->s).work[2] = md;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((s8)(p->s).motion.cmdIdx == 3 && (p->s).work[2] == 0) {
        s32 cx;
        register s32 off asm("r0");
        (p->s).work[2] = 1;
        ((p->props).deathtanz).unk_c1 &= ~1;
        PlaySound(0x5D);
        cx = (p->s).coord.x;
        if ((p->s).flags & 0x10) {
          off = 0x2400;
        } else {
          off = -0x2400;
        }
        FUN_080a08e0(&p->s, cx + off, (p->s).coord.y - 0x3700, ((p->s).flags >> 4) & 1);
        SetDDP(&p->body, &sCollisions[32]);
      }
      if (((p->props).deathtanz).unk_be != 0) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      ((p->props).deathtanz).unk_c1 |= 1;
      SetMotion(&p->s, MOTION(0xA7, 0x25));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 8;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

extern void __divsi3();

// 0x08049C54
void deathtanzMode8(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 v;
      SetDDP(&p->body, &sCollisions[15]);
      (p->s).d.x = -0x3000;
      {
        register s32 q asm("r1");
        s32 sq = ((s32 (*)(s32))Sqrt)(0x666);
        asm volatile("add %0, %1, #0" : "=&l"(q) : "l"(sq));
        q <<= 16;
        q = (u32)q >> 16;
        asm volatile("" ::: "memory");
        v = ((s32 (*)(s32, s32))__divsi3)((p->s).d.x, q);
      }
      (p->s).d.x = v;
      if ((p->s).flags & X_FLIP) {
        (p->s).d.x = -v;
      }
      (p->s).d.y = m;
      SetMotion(&p->s, MOTION(0xA7, 0x0B));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 ny;
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x19;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      {
        s32 dv;
        ny = (p->s).coord.y;
        dv = (p->s).d.y;
        ny += dv;
        (p->s).coord.y = ny;
      }
      if (ny > *(s32*)((u8*)p + 0xb8)) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      SetDDP(&p->body, &sCollisions[9]);
      SetMotion(&p->s, MOTION(0xA7, 0x09));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/deathtanz_c2.inc");

static const u8 sPostures[14];

// 0x08049EE0
void deathtanzMode10(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 bx asm("r3");
      register s32 v asm("r0");
      register s32 tx asm("r2");
      register s32 dx asm("r1");
      s32 dy, dist, nx, ny;
      PlaySound(0x5D);
      SetDDP(&p->body, &sCollisions[15]);
      bx = *(s32*)((u8*)p + 0xb4);
      v = bx + -0x1400;
      (p->s).d.x = v;
      tx = v;
      if ((p->s).flags & 0x10) {
        tx = bx + 0xA0 * 32;
      }
      dx = tx - (p->s).coord.x;
      (p->s).d.x = dx;
      dy = *(s32*)((u8*)p + 0xb8) - (p->s).coord.y;
      (p->s).d.y = dy;
      dx >>= 8;
      dist = dx * dx;
      dy >>= 8;
      dist += dy * dy;
      dist = Sqrt(dist) << 8;
      nx = ((p->s).d.x << 8) / dist;
      (p->s).d.x = nx;
      ny = ((p->s).d.y << 8) / dist;
      (p->s).d.x = nx << 3;
      (p->s).d.y = ny << 3;
      {
        register s32 q asm("r0");
        asm volatile("add %0, %1, #0" : "=&l"(q) : "l"(dist));
        (p->s).work[2] = q >> 11;
      }
      SetMotion(&p->s, MOTION(0xA7, 0x0B));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t <= 0x17) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).work[2] = 0;
      SetMotion(&p->s, MOTION(0xA7, 0x26));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      if ((p->s).work[2] == 0) {
        s32 cy, by;
        (p->s).coord.x += (p->s).d.x;
        cy = (p->s).coord.y + (p->s).d.y;
        (p->s).coord.y = cy;
        by = *(s32*)((u8*)p + 0xb8);
        if (cy > by) {
          (p->s).coord.y = by;
          (p->s).work[2] = 1;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      SetDDP(&p->body, &sCollisions[sPostures[(s8)(p->s).motion.cmdIdx]]);
      break;
    case 4:
      SetDDP(&p->body, &sCollisions[7]);
      SetMotion(&p->s, MOTION(0xA7, 0x08));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        register u8 f asm("r1");
        register s32 md asm("r0");
        f = *((u8*)p + 0xbf);
        if (f != 0) {
          f = 0;
          md = 5;
        } else {
          md = 0xB;
        }
        (p->s).mode[1] = md;
        (p->s).mode[2] = f;
      }
      break;
  }
}

// 0x0804A0A8
void deathtanzMode11(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 bx asm("r3");
      register s32 v asm("r0");
      register s32 tx asm("r2");
      register s32 dx asm("r1");
      s32 dy, dist, nx, ny;
      SetDDP(&p->body, &sCollisions[12]);
      bx = *(s32*)((u8*)p + 0xb4);
      v = bx + -0x5400;
      (p->s).d.x = v;
      tx = v;
      if ((p->s).flags & 0x10) {
        tx = bx + 0x5400;
      }
      dx = tx - (p->s).coord.x;
      (p->s).d.x = dx;
      {
        s32 by = *(s32*)((u8*)p + 0xb8);
        s32 k = -0x6800;
        asm("" : "+r"(k));
        by += k;
        dy = by - (p->s).coord.y;
      }
      (p->s).d.y = dy;
      dx >>= 8;
      dist = dx * dx;
      dy >>= 8;
      dist += dy * dy;
      dist = Sqrt(dist) << 8;
      nx = ((p->s).d.x << 8) / dist;
      (p->s).d.x = nx;
      ny = ((p->s).d.y << 8) / dist;
      (p->s).d.x = nx << 3;
      (p->s).d.y = ny << 3;
      {
        register s32 q asm("r0");
        asm volatile("add %0, %1, #0" : "=&l"(q) : "l"(dist));
        (p->s).work[2] = q >> 11;
      }
      SetMotion(&p->s, MOTION(0xA7, 0x0A));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2: {
      register s32 one asm("r2");
      s32 bx;
      SetDDP(&p->body, &sCollisions[35]);
      {
        register s32 xf0 asm("r0");
        xf0 = (p->s).flags >> 4;
        one = 1;
        xf0 ^= one;
        asm("" : "+r"(xf0));
        xf0 &= one;
        ((p->s).spr).xflip = xf0;
      }
      {
        register s32 xf asm("r1");
        register u8* oa asm("r4");
        s32 sh4, ov, m11;
        xf = (p->s).flags >> 4;
        xf ^= one;
        asm("" : "+r"(xf));
        xf &= one;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
        if (xf != 0) {
          (p->s).flags |= 0x10;
        } else {
          register u8 h asm("r1");
          register u8 g asm("r0");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g = 0xEF;
          g &= h;
          (p->s).flags = g;
        }
      }
      {
        s32* bp = (s32*)((u8*)p + 0xb4);
        s32 cx = (p->s).coord.x;
        s32 nx;
        bx = *bp;
        if (cx < bx) {
          nx = bx + -0x5400;
        } else {
          register s32 k2 asm("r2");
          k2 = 0xA8 * 128;
          asm("" : "+r"(k2));
          nx = bx + k2;
        }
        (p->s).coord.x = nx;
      }
      SetMotion(&p->s, MOTION(0xA7, 0x0C));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u8* q = (u8*)p + 0xbf;
        s32 z0 = 0;
        s32 one = 1;
        *q = one;
        (p->s).mode[1] = 0xA;
        (p->s).mode[2] = z0;
      }
      break;
  }
}

void deathtanz_080a0934(struct Entity* e, s32 x, s32 y, u8 a3, u8 a4);

// 0x0804A234
void deathtanzMode12(struct Boss* p) {
  register s32 z asm("r5");
  z = (p->s).mode[2];
  switch (z) {
    case 0:
      if ((u32)(((p->s).coord.x - *(s32*)((u8*)p + 0xb4)) + 0xC8 * 64) > 0xC8 * 128) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = z;
        UpdateMotionGraphic(&p->s);
        break;
      }
      SetDDP(&p->body, &sCollisions[60]);
      *((u8*)p + 0xbe) = z;
      SetMotion(&p->s, MOTION(0xA7, 0x0D));
      (p->s).work[2] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((s8)(p->s).motion.cmdIdx == 6) {
        register s32 w asm("r5");
        w = (p->s).work[2];
        if (w == 0) {
          register s32 one asm("r6");
          register s32 x asm("r1");
          register s32 cx asm("r2");
          register u32 fl asm("r3");
          s32 y;
          one = 1;
          (p->s).work[2] = one;
          PlaySound(0x5D);
          cx = (p->s).coord.x;
          x = cx - 0x3700;
          fl = (p->s).flags;
          if (fl & 0x10) {
            x = cx + 0x3700;
          }
          y = (p->s).coord.y - 0x3200;
          ((void (*)(struct Entity*, s32, s32, s32, s32))deathtanz_080a0934)(&p->s, x, y, (fl >> 4) & one, w);
          *((u8*)p + 0xc1) &= 0xFD;
        }
      }
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      u32 rv = (RNG_0202f388 * 0x343FD + 0x269EC3) << 1;
      u32 b;
      asm("" : "+r"(rv));
      RNG_0202f388 = rv >> 1;
      b = (rv >> 0x11) & 1;
      (p->s).work[2] = b * 18 + 0x3C;
      SetMotion(&p->s, MOTION(0xA7, 0x0E));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((u8)t == 0) {
        (p->s).mode[1] = 0xD;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void deathtanz_080a0934(struct Entity* e, s32 x, s32 y, u8 a3, u8 a4);

// 0x0804A378
void deathtanzMode13(struct Boss* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetMotion(&p->s, MOTION(0xA7, 0x0F));
      (p->s).work[2] = m;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((s8)(p->s).motion.cmdIdx == 5 && (p->s).work[2] == 0) {
        register s32 one asm("r5");
        register s32 x asm("r1");
        register s32 cx asm("r2");
        register u32 fl asm("r3");
        s32 y;
        one = 1;
        (p->s).work[2] = one;
        PlaySound(0x5D);
        cx = (p->s).coord.x;
        x = cx - 0x3700;
        fl = (p->s).flags;
        if (fl & 0x10) {
          x = cx + 0x3700;
        }
        y = (p->s).coord.y - 0x3200;
        ((void (*)(struct Entity*, s32, s32, s32, s32))deathtanz_080a0934)(&p->s, x, y, (fl >> 4) & one, one);
        *((u8*)p + 0xc1) &= 0xFE;
      }
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, MOTION(0xA7, 0x10));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0xbe) != 0) {
        (p->s).mode[1] = 0xE;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x0804A454
void deathtanzMode14(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register u8* c1 asm("r3");
      register u8 fv asm("r1");
      register u8 g asm("r0");
      register s32 z asm("r2");
      c1 = (u8*)p + 0xc1;
      fv = *c1;
      g = 2;
      z = 0;
      g |= fv;
      *c1 = g;
      *((u8*)p + 0xbe) = z;
      SetMotion(&p->s, MOTION(0xA7, 0x11));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      goto inc;
    case 2:
      SetDDP(&p->body, &sCollisions[62]);
      SetMotion(&p->s, MOTION(0xA7, 0x13));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0xbe) == 0) {
        break;
      }
    inc:
      (p->s).mode[2]++;
      break;
    case 4: {
      register u8* c2 asm("r2");
      register u8 fv2 asm("r1");
      register u8 g2 asm("r0");
      c2 = (u8*)p + 0xc1;
      fv2 = *c2;
      g2 = 1;
      g2 |= fv2;
      *c2 = g2;
      SetDDP(&p->body, &sCollisions[60]);
      SetMotion(&p->s, MOTION(0xA7, 0x15));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

// 0x0804A540
void deathtanzMode15(struct Boss* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      PlaySound(0x5C);
      SetDDP(&p->body, &sCollisions[1]);
      *(u8*)((u8*)p + 0xbe) = m;
      SetMotion(&p->s, MOTION(0xA7, 0x16));
      (p->s).mode[2]++;
    case 1:
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)p + 0x73) == 3) {
        u8 z = 0;
        (p->s).mode[1] = 0x10;
        (p->s).mode[2] = z;
      }
      break;
  }
}

void deathtanz_080a09a0(struct Entity* parent, s32 x, s32 y, u8 n);

// 0x0804A59C
void deathtanzMode16(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 x;
      s32 y;
      u32 fl;
      u8 dir;
      SetDDP(&p->body, &sCollisions[65]);
      x = (p->s).coord.x - 0x800;
      fl = (p->s).flags;
      if (X_FLIP & fl) {
        x = (p->s).coord.x + 0x800;
      }
      y = (p->s).coord.y - 0x2600;
      dir = (fl >> 4) & 1;
      deathtanz_080a09a0(&p->s, x, y, dir);
      ((p->props).deathtanz).unk_c1 &= ~1;
      SetMotion(&p->s, MOTION(0xA7, 0x18));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      if (((p->props).deathtanz).unk_be == 0) {
        break;
      }
      goto inc;
    case 2:
      ((p->props).deathtanz).unk_c1 |= 1;
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, MOTION(0xA7, 0x1A));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    inc:
      (p->s).mode[2]++;
      break;
    case 4:
      SetMotion(&p->s, MOTION(0xA7, 0x1B));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u8 z = 0;
        (p->s).mode[1] = 5;
        (p->s).mode[2] = z;
      }
      break;
  }
}

INCASM("asm/boss/deathtanz_c3.inc");

s32 PushoutToUp1(s32 x, s32 y);
s32 PushoutToDown1(s32 x, s32 y);

// 0x0804AA24
void deathtanzKnockBackDamage(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 dx, dy, dist, nx, ny;
      PlaySound(0x60);
      SetMotion(&p->s, MOTION(0xA7, 0x36));
      dx = (p->s).coord.x - *(s32*)((u8*)p + 0xc8);
      (p->s).d.x = dx;
      dy = (p->s).coord.y - 0x3000;
      dy -= *(s32*)((u8*)p + 0xcc);
      (p->s).d.y = dy;
      dist = (dx >> 8) * (dx >> 8);
      dist += (dy >> 8) * (dy >> 8);
      dist = Sqrt(dist) << 8;
      nx = ((p->s).d.x << 8) / dist;
      (p->s).d.x = nx;
      ny = ((p->s).d.y << 8) / dist;
      (p->s).d.y = ny;
      (p->s).d.x = nx * 1152 / 256;
      (p->s).d.y = ny * 1152 / 256;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 r asm("r6");
      s32 x, bx, ny;
      x = (p->s).coord.x + (p->s).d.x;
      (p->s).coord.x = x;
      bx = *(s32*)((u8*)p + 0xb4);
      if (x > bx + 0x5000) {
        (p->s).coord.x = bx + 0x5000;
      } else if (x < bx - 0x5000) {
        (p->s).coord.x = bx - 0x5000;
      }
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      ny = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = ny;
      if ((p->s).d.y > 0) {
        r = PushoutToUp1((p->s).coord.x, ny);
        if (r < 0) {
          (p->s).coord.y += r;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = 0;
        }
      } else {
        r = PushoutToDown1((p->s).coord.x, ny - 0x2000);
        if (r < 0) {
          (p->s).coord.y += r;
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x0804AB50
void deathtanzMode19(struct Boss* p) {
  struct Entity* e = (p->s).unk_28;
  register s32 m asm("r1");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      s32 k10;
      register s32 z6 asm("r6");
      {
        register u8 f2 asm("r0");
        f2 = (p->s).flags2;
        k10 = 0x10;
        asm("" : "+r"(k10));
        z6 = 0;
        f2 |= k10;
        (p->s).flags2 = f2;
      }
      (p->s).invincibleID = e->uniqueID;
      {
        u8* a = (u8*)p + 0x8c;
        *(s32*)a = m;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = m;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = m;
      }
      (p->s).flags &= ~4;
      {
        register s32 one asm("r2");
        register s32 xv asm("r1");
        u32 t0 = e->flags;
        t0 >>= 4;
        one = 1;
        t0 &= one;
        ((p->s).spr).xflip = t0;
        xv = (u32)e->flags >> 4;
        xv &= one;
        {
          register u8* oa asm("ip");
          s32 sh4, ov, m11;
          oa = (u8*)p + 0x4a;
          sh4 = xv << 4;
          ov = *oa;
          m11 = -0x11;
          m11 &= ov;
          m11 |= sh4;
          *oa = m11;
        }
        if (xv != 0) {
          register u8 g asm("r0");
          g = (p->s).flags;
          g |= k10;
          (p->s).flags = g;
        } else {
          register u8 h asm("r1");
          register u8 g2 asm("r0");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g2 = 0xEF;
          g2 &= h;
          (p->s).flags = g2;
        }
      }
      SetMotion(&p->s, 0xA739);
      (p->s).mode[2]++;
      asm volatile("" : "+l"(z6));
      FALLTHROUGH;
    }
    case 1: {
      register s32 dx asm("r1");
      {
        s32 cx = (p->s).coord.x;
        dx = (p->s).d.x;
        (p->s).coord.x = cx + dx;
      }
      {
        register s32 k asm("r0");
        if ((p->s).work[3] != 0) {
          k = 0xF6;
        } else {
          k = 0xFA;
        }
        (p->s).d.x = dx * k / 256;
      }
      FUN_0801779c(&p->s);
      if (e->mode[0] == 4) {
        register u8 g asm("r0");
        register u8 h asm("r1");
        register s32 zr asm("r2");
        u8* a;
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        zr = 0;
        h = 0xFD;
        g &= h;
        (p->s).flags = g;
        a = (u8*)p + 0x8c;
        *(s32*)a = zr;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(s32*)a = zr;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = zr;
        (p->s).flags &= ~4;
        SET_BOSS_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

INCASM("asm/boss/deathtanz_c3b.inc");

// --------------------------------------------

// 0x083627dc
static const struct Collision sCollisions[71] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
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
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0100, -0x2B00, 0x2400, 0x1F00},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0600, -0x1500, 0x3400, 0x2400},
    },
    [3] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0300, -0x1D00, 0x1300, 0x3B00},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x2000, 0x1700, 0x3E00},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x2A00, 0x4900, 0x1900},
    },
    [6] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x2000, 0x1700, 0x3E00},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0900, -0x1A00, 0x2F00, 0x3700},
    },
    [8] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0800, -0x1500, 0x2800, 0x2400},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0500, -0x3400, 0x2C00, 0x1A00},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0B00, -0x1300, 0x2F00, 0x2700},
    },
    [11] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0200, -0x1C00, 0x1C00, 0x3A00},
    },
    [12] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0C00, -0x3300, 0x1A00, 0x1400},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0200, -0x2A00, 0x1300, 0x5100},
    },
    [14] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0200, -0x2B00, 0x1300, 0x5100},
    },
    [15] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0400, -0x2A00, 0x1B00, 0x5100},
    },
    [16] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x1200, -0x2E00, 0x1A00, 0x1400},
    },
    [17] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0400, -0x2A00, 0x1B00, 0x5100},
    },
    [18] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0300, -0x1C00, 0x2400, 0x3300},
    },
    [19] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x1F00, -0x1B00, 0x3400, 0x0F00},
    },
    [20] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x1B00, 0x1500, 0x3500},
    },
    [21] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0600, -0x2B00, 0x1B00, 0x4400},
    },
    [22] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0A00, -0x4000, 0x2400, 0x1B00},
    },
    [23] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0300, -0x2A00, 0x1400, 0x4C00},
    },
    [24] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000001,
      range : {0x0700, -0x2B00, 0x1B00, 0x4400},
    },
    [25] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0C00, -0x1C00, 0x2400, 0x1000},
    },
    [26] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 1,
      range : {0x0900, -0x1500, 0x1200, 0x2900},
    },
    [27] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0600, -0x2F00, 0x1400, 0x3100},
    },
    [28] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000001,
      range : {0x0700, -0x2B00, 0x1B00, 0x4400},
    },
    [29] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0C00, -0x2C00, 0x2400, 0x1000},
    },
    [30] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 1,
      range : {0x0900, -0x1500, 0x1200, 0x2900},
    },
    [31] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0600, -0x2F00, 0x1400, 0x3100},
    },
    [32] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0700, -0x2B00, 0x1B00, 0x4400},
    },
    [33] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 1,
      range : {0x0900, -0x1500, 0x1200, 0x2900},
    },
    [34] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0600, -0x2F00, 0x1400, 0x3100},
    },
    [35] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000001,
      range : {0x0A00, -0x2600, 0x1000, 0x4800},
    },
    [36] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0500, -0x1B00, 0x2C00, 0x1000},
    },
    [37] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 1,
      range : {-0x0200, -0x3600, 0x1500, 0x1F00},
    },
    [38] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0A00, -0x1900, 0x1100, 0x2E00},
    },
    [39] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x2C00, 0x1000, 0x5600},
    },
    [40] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0B00, -0x3600, 0x2C00, 0x1000},
    },
    [41] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0100, -0x2C00, 0x1100, 0x5600},
    },
    [42] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x2C00, 0x1000, 0x5600},
    },
    [43] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0700, -0x3000, 0x2C00, 0x1000},
    },
    [44] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0100, -0x2C00, 0x1100, 0x5600},
    },
    [45] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x2C00, 0x1000, 0x5600},
    },
    [46] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x2100, -0x5300, 0x0B00, 0x3300},
    },
    [47] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0100, -0x2C00, 0x1100, 0x5600},
    },
    [48] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [49] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0300, -0x5A00, 0x3600, 0x3400},
    },
    [50] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [51] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [52] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x3300, -0x5A00, 0x3600, 0x3400},
    },
    [53] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [54] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [55] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x3300, -0x2600, 0x3600, 0x3400},
    },
    [56] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [57] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [58] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x1C00, -0x1700, 0x0800, 0x3400},
    },
    [59] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0400, -0x2600, 0x1000, 0x5600},
    },
    [60] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0B00, -0x1F00, 0x2400, 0x4000},
    },
    [61] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0C00, -0x1C00, 0x1300, 0x3B00},
    },
    [62] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0500, -0x3100, 0x1E00, 0x1B00},
    },
    [63] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0300, -0x1200, 0x3A00, 0x2600},
    },
    [64] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0C00, -0x1C00, 0x1300, 0x3B00},
    },
    [65] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x0A00, 0x2E00, 0x1800},
    },
    [66] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x2100, 0x0F00, 0x4500},
    },
    [67] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0300, -0x1D00, 0x1300, 0x3B00},
    },
    [68] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x1000, 0x3200, 0x2300},
    },
    [69] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x2300, 0x1100, 0x4800},
    },
    [70] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x05,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, -0x1A00, 0x1900, 0x3700},
    },
};

static const u8 sDeathtanzModes[32] = {
    2, 2, 2, 2, 2, 2, 2, 2, 12, 12, 12, 12, 17, 17, 17, 17, 2, 2, 2, 2, 2, 2, 12, 12, 15, 15, 15, 15, 17, 17, 17, 17,
};

static const u8 sInitModes[2] = {0, 19};

// 0x08362ea6
static const u8 u8_ARRAY_08362ea6[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3,
};

// 0x08362eb6
static const u8 sPostures[14] = {
    39, 39, 42, 42, 45, 45, 48, 51, 54, 57, 57, 57, 57, 0,
};

// 0x08362ec4
static const struct Coord sExplosionCoords[2] = {
    {PIXEL(0), -PIXEL(35)},
    {PIXEL(0), -PIXEL(35)},
};
