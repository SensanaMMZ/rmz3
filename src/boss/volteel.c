#include "boss.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "overworld.h"
#include "physics.h"
#include "script.h"
#include "stagerun.h"
#include "zero.h"

static const struct Collision sCollisions[24];

bool8 volteel_080457c4(struct Boss* p);

static void Volteel_Init(struct Boss* p);
static void Volteel_Update(struct Boss* p);
static void Volteel_Die(struct Boss* p);

// clang-format off
const BossRoutine gVolteelRoutine = {
    [ENTITY_INIT] =      Volteel_Init,
    [ENTITY_UPDATE] =    Volteel_Update,
    [ENTITY_DIE] =       Volteel_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

struct Boss* CreateVolteel(struct Coord* c, u8 n) {
  struct Boss* p = (struct Boss*)AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_VOLTEEL);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

NAKED static void Volteel_Init(struct Boss* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	adds r7, r0, #0\n\
	bl InitNonAffineMotion\n\
	adds r0, r7, #0\n\
	adds r0, #0x24\n\
	movs r4, #0\n\
	strb r4, [r0]\n\
	adds r1, r7, #0\n\
	adds r1, #0x50\n\
	movs r0, #0\n\
	mov r8, r0\n\
	movs r0, #0x80\n\
	lsls r0, r0, #1\n\
	strh r0, [r1]\n\
	adds r1, #2\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	bl ResetDynamicMotion\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	strb r0, [r7, #0xa]\n\
	adds r0, r7, #0\n\
	adds r0, #0x4c\n\
	mov r1, r8\n\
	strb r1, [r0]\n\
	adds r2, r7, #0\n\
	adds r2, #0x4a\n\
	ldrb r1, [r2]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r1\n\
	strb r0, [r2]\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
	strb r0, [r7, #0xa]\n\
	ldr r1, _08043444 @ =sCollisions\n\
	adds r0, r7, #0\n\
	movs r2, #0x40\n\
	bl ResetBossBody\n\
	adds r1, r7, #0\n\
	adds r1, #0xc9\n\
	movs r0, #0x40\n\
	strb r0, [r1]\n\
	ldr r1, _08043448 @ =FUN_0804586c\n\
	adds r0, r7, #0\n\
	adds r0, #0x74\n\
	str r1, [r0, #0x24]\n\
	adds r0, #0x40\n\
	mov r1, r8\n\
	strb r1, [r0]\n\
	adds r1, r7, #0\n\
	adds r1, #0xb5\n\
	movs r0, #0xff\n\
	strb r0, [r1]\n\
	adds r1, #1\n\
	strb r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xc0\n\
	str r4, [r0]\n\
	subs r0, #9\n\
	mov r1, r8\n\
	strb r1, [r0]\n\
	ldr r1, [r7, #0x58]\n\
	ldr r0, _0804344C @ =0xFFFFC000\n\
	adds r1, r1, r0\n\
	ldr r0, [r7, #0x54]\n\
	bl FUN_0800a05c\n\
	str r0, [r7, #0x58]\n\
	adds r1, r7, #0\n\
	adds r1, #0xb8\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [r1]\n\
	adds r1, #4\n\
	ldr r0, [r7, #0x58]\n\
	str r0, [r1]\n\
	ldr r0, [r7, #0x54]\n\
	ldr r1, [r7, #0x58]\n\
	bl FUN_0800a134\n\
	adds r5, r0, #0\n\
	ldr r0, [r7, #0x54]\n\
	adds r1, r5, #0\n\
	bl FUN_0800a22c\n\
	adds r6, r0, #0\n\
	ldr r0, [r7, #0x54]\n\
	adds r1, r5, #0\n\
	bl FUN_0800a31c\n\
	adds r4, r0, #0\n\
	subs r0, r6, r4\n\
	asrs r5, r0, #1\n\
	adds r5, r4, r5\n\
	ldr r1, [r7, #0x58]\n\
	adds r0, r5, #0\n\
	bl FUN_0800a134\n\
	adds r1, r7, #0\n\
	adds r1, #0xd4\n\
	str r0, [r1]\n\
	ldr r1, [r7, #0x58]\n\
	adds r0, r5, #0\n\
	bl FUN_0800a05c\n\
	adds r1, r7, #0\n\
	adds r1, #0xd8\n\
	str r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xdc\n\
	str r4, [r0]\n\
	adds r0, #4\n\
	str r6, [r0]\n\
	subs r0, #0x16\n\
	mov r1, r8\n\
	strb r1, [r0]\n\
	ldrb r0, [r7, #0x10]\n\
	cmp r0, #0\n\
	bne _08043454\n\
	ldr r1, _08043450 @ =gBossFnTable\n\
	ldrb r0, [r7, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r7, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r7, #0x14]\n\
	mov r0, r8\n\
	strb r0, [r7, #0xd]\n\
	strb r0, [r7, #0xe]\n\
	strb r0, [r7, #0xf]\n\
	b _08043470\n\
	.align 2, 0\n\
_08043444: .4byte sCollisions\n\
_08043448: .4byte FUN_0804586c\n\
_0804344C: .4byte 0xFFFFC000\n\
_08043450: .4byte gBossFnTable\n\
_08043454:\n\
	ldr r1, _08043484 @ =gBossFnTable\n\
	ldrb r0, [r7, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r7, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r7, #0x14]\n\
	movs r0, #3\n\
	strb r0, [r7, #0xd]\n\
	mov r1, r8\n\
	strb r1, [r7, #0xe]\n\
	strb r1, [r7, #0xf]\n\
_08043470:\n\
	movs r0, #0\n\
	strb r0, [r7, #0x11]\n\
	adds r0, r7, #0\n\
	bl Volteel_Update\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08043484: .4byte gBossFnTable\n\
 .syntax divided\n");
}

// --------------------------------------------

bool8 nop_080438a4(struct Boss* p);
bool8 FUN_080438f0(struct Boss* p);
bool8 FUN_08043988(struct Boss* p);
bool8 nop_080439d0(struct Boss* p);
bool8 nop_08043db0(struct Boss* p);
bool8 FUN_080440c0(struct Boss* p);
bool8 FUN_080449f0(struct Boss* p);
bool8 FUN_08044cb4(struct Boss* p);
bool8 FUN_08044f00(struct Boss* p);
bool8 FUN_080450bc(struct Boss* p);
bool8 FUN_08045464(struct Boss* p);
bool8 FUN_08045570(struct Boss* p);
bool8 FUN_08045610(struct Boss* p);

void volteelMode0(struct Boss* p);
void volteelMode1(struct Boss* p);
void volteelMode2(struct Boss* p);
void volteelNeutral(struct Boss* p);
void volteelMode4(struct Boss* p);
void volteelMode5(struct Boss* p);
void volteelMode6(struct Boss* p);
void volteelElectricCage(struct Boss* p);
void volteelMode8(struct Boss* p);
void volteelMode9(struct Boss* p);
void volteelEX(struct Boss* p);
void volteelMode11(struct Boss* p);
void volteelKnockBackDamage(struct Boss* p);

static void Volteel_Update(struct Boss* p) {
  // clang-format off
  static const BossFunc sUpdates1[] = {
      (BossFunc)nop_080438a4,
      (BossFunc)FUN_080438f0,
      (BossFunc)FUN_08043988,
      (BossFunc)nop_080439d0,
      (BossFunc)nop_08043db0,
      (BossFunc)FUN_080440c0,
      (BossFunc)FUN_080449f0,
      (BossFunc)FUN_08044cb4,
      (BossFunc)FUN_08044f00,
      (BossFunc)FUN_080450bc,
      (BossFunc)FUN_08045464,
      (BossFunc)FUN_08045570,
      (BossFunc)FUN_08045610,
  };
  // clang-format on
  // clang-format off
  static const BossFunc sUpdates2[] = {
      volteelMode0,
      volteelMode1,
      volteelMode2,
      volteelNeutral,
      volteelMode4,
      volteelMode5,
      volteelMode6,
      volteelElectricCage,
      volteelMode8,
      volteelMode9,
      volteelEX,
      volteelMode11,
      volteelKnockBackDamage,
  };
  // clang-format on
  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    PlaySound(SE_VOLTEEL_DEATH);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[3] = 1;
    } else {
      (p->s).mode[3] = 0;
    }
    Volteel_Die(p);
    return;
  }

  (sUpdates1[(p->s).mode[1]])(p);
  volteel_080457c4(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

// --------------------------------------------

void volteelDeath0(struct Boss* p);
void volteelDeath1(struct Boss* p);

static void Volteel_Die(struct Boss* p) {
  static const BossFunc seq[] = {
      volteelDeath0,
      volteelDeath1,
  };
  (seq[(p->s).mode[1]])(p);
}

// 0x08043540 -- parked (allocation basin): retail homes the 1/0 multi-def
// constant in r5 and gStageRun in r3 with copy-first ands; agbcc rotates
// [r1/r2/r3] through ms/one/base in every arrangement tried. Full decode:
// mission-fail latch, sprite unscale, sea/state reset by terrain id,
// status clear, 1-frame delay then mode 1.
NON_MATCH void volteelDeath0(struct Boss* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      u16 ms = gStageRun.missionStatus;
      s32 one = 1;
      if ((one & ms) && !(one & gStageRun.vm.active)) {
        gStageRun.missionStatus = (ms & 0xFFFE) | 0x10;
      }
      (p->s).angle = 0;
      one = 0;
      ((p->s).spr).mag.x = 0x100;
      ((p->s).spr).mag.y = 0x100;
      (p->s).spr.yflip = one;
      ((p->s).spr).oam.yflip = 0;
      (p->s).flags &= ~0x20;
      if (_isSoundPlaying(0x7F)) {
        StopSound(0x7F);
      }
      if ((*(u16*)(g + 0x1D0) & 0x7F) == 0xD) {
        gOverworld.state[0] = one;
      } else {
        gOverworld.state[2] = one;
      }
      (p->body).status = 0;
      (p->body).prevStatus = 0;
      (p->body).invincibleTime = 0;
      (p->s).flags &= ~COLLIDABLE;
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 1;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1:
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).mode[1] = 1, (p->s).mode[2] = 0;
      break;
  }
#else
  INCCODE("asm/boss/volteel_3540.inc");
#endif
}

struct Entity* FUN_080b2b40(u8 kind, struct Coord* c, s32 r2, u8 r3);
void FUN_0809c3b4(struct Entity* e, struct Coord* c, motion_t m, u8 dir);
struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);

// 0x08043640
void volteelDeath1(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register u32* st asm("r2");
      register u32 z asm("r1");
      u8 m3;
      {
        u8* a = (u8*)p + 0x49;
        u32 v = *a;
        s32 m = -0xd;
        u32 e8a;
        m &= v;
        e8a = 8;
        asm volatile("" : "+l"(e8a));
        m |= e8a;
        *a = m;
      }
      SetMotion(&p->s, MOTION(0xA5, 0x04));
      {
        u32 fl = (p->s).flags;
        u32 f = 1;
        f |= fl;
        (p->s).flags = f;
      }
      st = (u32*)((u8*)p + 0x8c);
      if ((*st & (0x80 << 2)) == 0) {
        if (*(s16*)((u8*)p + 0xa4) != 0) {
          goto ten;
        }
      }
      {
        u32 ms = gStageRun.missionStatus;
        u32 e8 = 8;
        e8 &= ms;
        if (e8 != 0) {
          goto ten;
        }
      }
      m3 = (p->s).mode[3];
      if (m3 != 1) {
      ten:
        m3 = 0xa;
      }
      (p->s).mode[2] = m3;
      z = 0;
      *st = z;
      *(u32*)((u8*)p + 0x90) = z;
      *((u8*)p + 0x94) = z;
      {
        u32 fv = (p->s).flags;
        u32 f2 = 0xfb;
        f2 &= fv;
        (p->s).flags = f2;
      }
      {
        s32* d = (s32*)((u8*)p + 0x5c);
        d[1] = z;
      }
      (p->s).d.x = z;
      FALLTHROUGH;
    }
    case 1:
    case 10:
      UpdateMotionGraphic(&p->s);
      goto inc;
    case 2: {
      struct Coord c;
      s32 cx;
      s32 cy;
      u8 w1;
      (p->s).d.y = 0;
      cx = (p->s).coord.x;
      c.x = cx;
      cy = (p->s).coord.y;
      c.y = cy;
      if (((p->s).flags & 0x10) != 0) {
        *(volatile s32*)&c.x = cx;
      }
      c.y = cy - 0x2500;
      w1 = (p->s).work[1];
      if (w1 == 0xff) {
        goto one;
      }
      if (w1 == 0xfe) {
        ((void (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x80 << 2, 0);
        goto snd;
      }
      if ((pZero2->s).coord.x <= cx) {
        goto zero;
      }
    one:
      ((void (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x80 << 2, 1);
      goto snd;
    zero:
      ((void (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x80 << 2, 0);
    snd:
      PlaySound(0x2f);
      goto inc;
    }
    case 3: {
      struct Coord* cc = &(p->s).coord;
      u32 dir;
      {
        register s32 mo asm("r2");
        mo = MOTION(0xA5, 0x05);
        asm volatile("" : "+l"(mo));
        dir = ((p->s).flags >> 4) & 1;
        ((void (*)(struct Entity*, struct Coord*, s32, s32))FUN_0809c3b4)(
            &p->s, cc, mo, dir);
      }
      SetMotion(&p->s, MOTION(0xA5, 0x06));
      UpdateMotionGraphic(&p->s);
      (p->s).work[2] = 0x44;
      goto inc;
    }
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      FALLTHROUGH;
    case 11:
      if (((p->s).scriptEntity->flags & 0x80) == 0) {
        break;
      }
      (p->s).mode[2] = 0x14;
      break;
    case 20:
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 21:
      if (((p->s).scriptEntity->flags & 0x80) == 0) {
        break;
      }
      goto inc;
    case 22: {
      const struct Coord* ec;
      if (((p->s).flags & 0x10) == 0) {
        ec = (const struct Coord*)0x08362578;
        asm volatile("" : "+l"(ec));
      } else {
        ec = (const struct Coord*)0x08362580;
        asm volatile("" : "+l"(ec));
      }
      *(struct Entity**)((u8*)p + 0xc0) = CreateBossExplosion(&p->s, (struct Coord*)ec);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 23:
      if ((*(struct Entity**)((u8*)p + 0xc0))->mode[0] <= 1) {
        break;
      }
    inc:
      (p->s).mode[2]++;
      break;
    case 24: {
      register struct StageRun* sr asm("r2");
      register s32 g asm("r0");
      register s32 h asm("r1");
      (p->s).work[2] = 0x3c;
      sr = &gStageRun;
      h = *((u8*)sr + 0x12);
      asm("" : "+r"(h));
      g = 2;
      g |= h;
      *((u8*)sr + 0x12) = g;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 25:
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      {
        u32 fv = (p->s).flags;
        u32 f = 0xfe;
        f &= fv;
        (p->s).flags = f;
      }
      break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      break;
  }
}

bool8 nop_080438a4(struct Boss* p) { return TRUE; }

void volteelMode0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      SetMotion(&p->s, MOTION(0xa5, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_080438f0(struct Boss* p) { return TRUE; }

// 0x080438f4
void volteelMode1(struct Boss* p) {
  motion_t m;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x3C;
      PlaySound(0x79);
      m = MOTION(0xA5, 0x0E);
      goto setmotion;
    case 2:
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      goto advance;
    case 3:
      m = MOTION(0xA5, 0x10);
    setmotion:
      SetMotion(&p->s, m);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    advance:
      (p->s).mode[2]++;
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2, (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_08043988(struct Boss* p) { return TRUE; }

void volteelMode2(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0xa5, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (!(gStageRun.vm.active & 1)) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

bool8 nop_080439d0(struct Boss* p) { return TRUE; }

INCASM("asm/boss/volteel_p5.inc");

bool8 nop_08043db0(struct Boss* p) { return TRUE; }

s32 PushoutToUp2(s32 x, s32 y);
s32 PushoutToLeft2(s32 x, s32 y);
s32 PushoutToRight2(s32 x, s32 y);
void volteel_08045abc(struct Boss* p);

// 0x08043DB4
void volteelMode4(struct Boss* p) {
  s32 nm;
  switch ((p->s).mode[2]) {
    case 0: {
      s32 best;
      register s32 bx asm("r6");
      register s32 cand asm("r4");
      best = 0x7FFFFFFF;
      {
        register s32 v asm("r0");
        register s32 k asm("r1");
        v = (pZero2->s).coord.x;
        k = -0x1200;
        bx = v + k;
      }
      {
        register s32 r asm("r1");
        register s32 cy asm("r1");
        cy = (p->s).coord.y + -0x5000;
        r = FUN_0800a05c(bx, cy);
        if (r < best && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          best = r;
        }
      }
      {
        register s32 v asm("r0");
        register s32 k asm("r1");
        v = (pZero2->s).coord.x;
        k = 0x90 << 5;
        cand = v + k;
      }
      {
        register s32 r asm("r1");
        register s32 cy asm("r1");
        cy = (p->s).coord.y + -0x5000;
        r = FUN_0800a05c(cand, cy);
        if (r < best && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          best = r;
          bx = cand;
        }
      }
      {
        register s32 r asm("r1");
        register s32 cy asm("r1");
        cand = (pZero2->s).coord.x;
        cy = (p->s).coord.y + -0x5000;
        r = FUN_0800a05c(cand, cy);
        if (r < best && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          best = r;
          bx = cand;
        }
      }
      (p->s).work[2] = 0x50;
      (p->s).d.x = (bx - (p->s).coord.x) / 0x50;
      {
        register s32 c asm("r1");
        register s32 dy asm("r0");
        c = 0xc8 << 8;
        dy = (p->s).coord.y;
        dy = best - dy;
        c -= dy;
        (p->s).d.y = -(c / 0x50);
      }
      (p->s).work[2] = 0x4f;
      (p->s).work[3] = 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      volteel_08045abc(p);
      if ((p->s).work[3] != 0) {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) == 0) {
          goto inc1;
        }
        break;
      }
    inc1:
      nm = (p->s).mode[2] + 1;
      asm volatile("");
      goto setmode;
    case 2:
      SetMotion(&p->s, 0xA501);
      SetDDP(&p->body, &sCollisions[3]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      register s32 hit asm("r6");
      register s32 r asm("r4");
      hit = 0;
      {
        register s32 dy asm("r2");
        dy = (p->s).d.y + 0x10;
        (p->s).d.y = dy;
        {
          register s32 cx asm("r0");
          register s32 dx asm("r1");
          cx = (p->s).coord.x;
          dx = (p->s).d.x;
          cx += dx;
          (p->s).coord.x = cx;
          {
            register s32 cy asm("r1");
            register s32 k asm("r2");
            cy = (p->s).coord.y;
            cy += dy;
            (p->s).coord.y = cy;
            k = 0x90 << 5;
            cx += k;
            r = PushoutToUp2(cx, cy);
          }
        }
      }
      if (r != 0) {
        register s32 a asm("r1");
        a = r;
        if (r < 0) {
          a = -r;
        }
        if (a <= 0x7FF) {
          (p->s).coord.y += r;
          hit = 1;
        }
      }
      {
        register s32 cx asm("r0");
        register s32 k asm("r1");
        cx = (p->s).coord.x;
        k = -0x1200;
        cx += k;
        r = PushoutToUp2(cx, (p->s).coord.y);
      }
      if (r != 0) {
        register s32 a asm("r1");
        a = r;
        if (r < 0) {
          a = -r;
        }
        if (a <= 0x7FF) {
          (p->s).coord.y += r;
          hit = 1;
        }
      }
      r = PushoutToUp2((p->s).coord.x, (p->s).coord.y);
      if (r != 0) {
        register s32 a asm("r1");
        a = r;
        if (r < 0) {
          a = -r;
        }
        if (a <= 0x7FF) {
          (p->s).coord.y += r;
          hit = 1;
        }
      }
      {
        register s32 cx asm("r0");
        register s32 k asm("r2");
        cx = (p->s).coord.x;
        k = 0x90 << 5;
        cx += k;
        r = PushoutToLeft2(cx, (p->s).coord.y);
      }
      if (r != 0) {
        (p->s).coord.x += r;
      }
      {
        register s32 cx asm("r0");
        register s32 k asm("r1");
        cx = (p->s).coord.x;
        k = -0x1200;
        cx += k;
        PushoutToRight2(cx, (p->s).coord.y);
      }
      if (r != 0) {
        (p->s).coord.x += r;
      }
      {
        register s32 mv asm("r1");
        u32 cur = MOTION_VALUE(p);
        mv = 0xA502;
        if (cur != mv && (p->s).d.y > 0) {
          SetMotion(&p->s, mv);
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          goto chkhit;
        }
      }
      nm = (p->s).mode[2] + 1;
      asm volatile("");
      goto setmode;
    chkhit:
      if (hit != 1) {
        break;
      }
      nm = (p->s).mode[2] + 1;
      goto setmode;
    }
    case 4: {
      register s32 best asm("r4");
      SetMotion(&p->s, 0xA503);
      SetDDP(&p->body, &sCollisions[1]);
      best = 0x7FFFFFFF;
      {
        register s32 cx asm("r0");
        register s32 r asm("r1");
        register s32 cy asm("r1");
        register s32 k asm("r2");
        cx = (p->s).coord.x;
        cy = (p->s).coord.y;
        k = -0x1000;
        cy += k;
        r = FUN_0800a05c(cx, cy);
        if (r < best && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          best = r;
          (p->s).coord.y = best;
        }
      }
      {
        register s32 r asm("r1");
        register s32 cx asm("r0");
        register s32 cy asm("r1");
        register s32 k asm("r2");
        cx = (p->s).coord.x;
        k = -0x1200;
        cx += k;
        cy = (p->s).coord.y;
        k = -0x1000;
        cy += k;
        r = FUN_0800a05c(cx, cy);
        if (r < best && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          best = r;
          (p->s).coord.y = best;
        }
      }
      {
        register s32 r asm("r1");
        register s32 cx asm("r0");
        register s32 cy asm("r1");
        register s32 k asm("r2");
        cx = (p->s).coord.x;
        k = 0x90 << 5;
        cx += k;
        cy = (p->s).coord.y;
        k = -0x1000;
        cy += k;
        r = FUN_0800a05c(cx, cy);
        if (r < best && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          (p->s).coord.y = r;
        }
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 5: {
      register u32 st asm("r1");
      UpdateMotionGraphic(&p->s);
      st = *((u8*)p + 0x73);
      if (st != 3) {
        break;
      }
      nm = 0;
      (p->s).mode[1] = st;
    setmode:
      (p->s).mode[2] = nm;
      break;
    }
  }
}

bool8 FUN_080440c0(struct Boss* p) { return TRUE; }

INCASM("asm/boss/volteel_p7.inc");

bool8 FUN_080449f0(struct Boss* p) { return TRUE; }

// 0x080449F4
void volteelMode6(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 mid;
      {
        s32* pa;
        register s32* pb asm("r6");
        register s32 t asm("r2");
        register s32 zx asm("r3");
        register s32 b asm("r5");
        register s32* q1 asm("r1");
        register s32* q2 asm("r0");
        register s32 u asm("r1");
        register s32 v asm("r0");
        s32 a;
        {
          u8 fl = (p->s).flags;
          u32 f = 1;
          f |= fl;
          (p->s).flags = f;
        }
        {
          struct Zero* z0 = pZero2;
          q1 = (s32*)((u8*)p + 0xdc);
          zx = (z0->s).coord.x;
        }
        a = *q1;
        t = zx - a;
        pa = q1;
        if (t <= 0) {
          t = a - zx;
        }
        q2 = (s32*)((u8*)p + 0xe0);
        b = *q2;
        u = zx - b;
        pb = q2;
        if (u > 0 ? t > u : t > (v = b - zx)) {
          register u8* q asm("r2");
          register u32 z asm("r1");
          (p->s).coord.x = *pb;
          (p->s).unk_coord.x = *pa + (0x80 << 7);
          q = (u8*)p + 0xca;
          z = 0;
          *q = 1;
          {
            u8* x = (u8*)p + 0x4c;
            *x = z;
          }
          q -= 0x80;
          {
            s32 ov = *q;
            s32 m11 = -0x11;
            m11 &= ov;
            *q = m11;
          }
          {
            u8 fl = (p->s).flags;
            u32 f = 0xEF;
            f &= fl;
            (p->s).flags = f;
          }
        } else {
          register u8* q asm("r1");
          register u32 k asm("r1");
          (p->s).coord.x = *pa;
          (p->s).unk_coord.x = *pb + -0x4000;
          q = (u8*)p + 0xca;
          *q = 3;
          q -= 0x7e;
          *q = 1;
          {
            u8* oa = (u8*)p + 0x4a;
            u32 v = *oa;
            k = 0x10;
            v |= k;
            *oa = v;
          }
          {
            u8 fl = (p->s).flags;
            k |= fl;
            (p->s).flags = k;
          }
        }
      }
      {
        s32* hi = (s32*)((u8*)p + 0xd8);
        s32* lo = (s32*)((u8*)p + 0xd4);
        s32 h = *hi;
        mid = h - ((h - *lo) >> 1);
      }
      (p->s).coord.y = mid + (0x90 << 6);
      (p->s).unk_coord.y = 0x7FFFFFFF;
      {
        register s32 r asm("r2");
        r = FUN_0800a05c((p->s).unk_coord.x, mid + -0x2C00);
        if (r < (p->s).unk_coord.y && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          (p->s).unk_coord.y = r;
        }
      }
      {
        register s32 r asm("r2");
        r = FUN_0800a05c((p->s).unk_coord.x + (0x90 << 5), (p->s).coord.y + -0x5000);
        if (r < (p->s).unk_coord.y && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          (p->s).unk_coord.y = r;
        }
      }
      {
        register s32 r asm("r2");
        r = FUN_0800a05c((p->s).unk_coord.x + -0x1200, (p->s).coord.y + -0x5000);
        if (r < (p->s).unk_coord.y && r > *(s32*)((u8*)p + 0xbc) + -0x5000) {
          (p->s).unk_coord.y = r;
        }
      }
      {
        register s32 ux asm("r0");
        s32 q;
        ux = (p->s).unk_coord.x;
        (p->s).work[2] = 0x50;
        (p->s).d.x = (ux - (p->s).coord.x) / 0x50;
        {
          register s32 c asm("r2");
          register s32 uy asm("r0");
          register s32 cy asm("r1");
          c = 0xc8 << 8;
          uy = (p->s).unk_coord.y;
          cy = (p->s).coord.y;
          uy -= cy;
          c -= uy;
          q = c / 0x50;
        }
        (p->s).d.y = -q;
      }
      {
        u8 w = 0x4f;
        (p->s).work[2] = w;
        (p->s).work[3] = w;
      }
      PlaySound(0x7a);
      SetMotion(&p->s, MOTION(0xA5, 0x12));
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 mv asm("r5");
      u32 mvv;
      s32 dy = (p->s).d.y + 0x10;
      (p->s).d.y = dy;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += dy;
      mvv = MOTION_VALUE(p);
      asm("" : "+r"(mvv));
      mv = 0xA513;
      if (mvv != mv) {
        register u32 half asm("r0");
        register u32 w2 asm("r1");
        half = (p->s).work[3];
        w2 = (p->s).work[2];
        half >>= 1;
        if (w2 < half) {
          {
            u8 fl = (p->s).flags;
            u32 f = 1;
            f |= fl;
            (p->s).flags = f;
          }
          SetDDP(&p->body, &sCollisions[15]);
          {
            register struct Entity* e asm("r0");
            register s32 m asm("r1");
            e = &p->s;
            m = mv;
            SetMotion(e, m);
          }
        } else {
          register u32 one asm("r0");
          register u32 f asm("r0");
          one = 1;
          one &= w2;
          if (one != 0) {
            u8 fl = (p->s).flags;
            f = 1;
            f |= fl;
          } else {
            u8 fl = (p->s).flags;
            f = 0xFE;
            f &= fl;
          }
          (p->s).flags = f;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
      }
      break;
    }
    case 2: {
      u8* a = (u8*)p + 0x49;
      u32 v = *a;
      s32 m = -0xd;
      u32 e8a;
      m &= v;
      e8a = 8;
      m |= e8a;
      *a = m;
      SetMotion(&p->s, MOTION(0xA5, 0x02));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3: {
      s32 dy = (p->s).d.y + 0x10;
      (p->s).d.y = dy;
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += dy;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    }
    case 4: {
      u8 z = 0;
      (p->s).mode[1] = 3;
      (p->s).mode[2] = z;
      break;
    }
  }
}

bool8 FUN_08044cb4(struct Boss* p) { return TRUE; }

// Scratch-parity basin: two register pairs refuse to flip - the case-2 flags
// load wants r1 with its test const in r0 (mine mirror them), and the cage-off
// arm's masked-and computes the z-0x11 before the byte load regardless of
// barrier or eval-order levers. 4 bytes of pure parity; every arm, the k-select
// diamonds, and both probe transfers otherwise stream-match.
NON_MATCH void volteelElectricCage(struct Boss* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      if (!((p->s).flags & 0x10)) {
        s32 r0v = FUN_08009f6c((p->s).coord.x + 0x3600, (p->s).coord.y + -0x800);
        s32 r;
        asm volatile("add %0, %1, #0" : "=&l"(r) : "l"(r0v));
        if (r != (p->s).coord.y) {
          (p->s).mode[2]++;
        } else {
          (p->s).mode[2] = 0xA;
        }
      } else {
        s32 r0v = FUN_08009f6c((p->s).coord.x + -0x3600, (p->s).coord.y + -0x800);
        s32 r;
        asm volatile("add %0, %1, #0" : "=&l"(r) : "l"(r0v));
        if (r != (p->s).coord.y) {
          (p->s).mode[2]++;
        } else {
          (p->s).mode[2] = 0xA;
        }
      }
      break;
    case 1:
      SetMotion(&p->s, 0xA507);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        u32 m10;
        if (!((p->s).flags & ({ m10 = 0x10; asm("" : "+r"(m10)); 0x10; }))) {
          u8* xa = (u8*)p + 0x4c;
          u8 ov;
          u8 fv;
          *xa = 1;
          xa -= 2;
          ov = *xa;
          ov |= m10;
          *xa = ov;
          fv = (p->s).flags;
          fv |= m10;
          (p->s).flags = fv;
        } else {
          u8* xa = (u8*)p + 0x4c;
          s32 z = 0;
          asm("" : "+r"(z));
          *xa = z;
          {
            u8* oa = (u8*)p + 0x4a;
            *oa = *oa & (({ asm("" : "+r"(z)); z; }) - 0x11);
          }
          (p->s).flags &= ~0x10;
        }
        (p->s).mode[2] = 0xA;
      }
      break;
    case 10:
      (p->s).work[2] = 0x46;
      SetMotion(&p->s, 0xA508);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[3] = 0x12;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 11: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      t = (p->s).work[3];
      if (t != 0) {
        t--;
        (p->s).work[3] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    }
    case 12: {
      u8* ow;
      s32 k;
      SetMotion(&p->s, 0xA509);
      SetDDP(&p->body, &sCollisions[5]);
      ow = (u8*)&gOverworld;
      if ((*(u16*)(ow + 0x1D0) & 0x7F) == 0xD) {
        k = 0x2D024;
        asm volatile("");
      } else {
        k = 0x2D026;
      }
      *(ow + k) = 1;
      PlaySound(0x7D);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 13: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t != 0) {
        t--;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    }
    case 14: {
      u8* ow;
      s32 k;
      SetMotion(&p->s, 0xA50A);
      ow = (u8*)&gOverworld;
      if ((*(u16*)(ow + 0x1D0) & 0x7F) == 0xD) {
        k = 0x2D024;
        asm volatile("");
      } else {
        k = 0x2D026;
      }
      *(ow + k) = 0;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 15:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
#else
  INCCODE("asm/boss/volteel_cage.inc");
#endif
}

bool8 FUN_08044f00(struct Boss* p) { return TRUE; }

// 0x08044F04
void volteelMode8(struct Boss* p) {
  register s32 nm asm("r0");
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x1e;
      SetMotion(&p->s, 0xA50C);
      SetDDP(&p->body, &sCollisions[1]);
      PlaySound(0x7b);
      UpdateMotionGraphic(&p->s);
      (p->s).work[3] = 0xb;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      if ((p->s).work[3] != 0) {
        if ((u8)--(p->s).work[3] != 0) {
          break;
        }
      }
      (p->s).work[3] = 0;
      nm = (p->s).mode[2] + 1;
      asm volatile("");
      goto setm;
    case 2:
      if ((p->s).work[3] == 0) {
        if ((s8)*((u8*)p + 0x71) == 4) {
          SetDDP(&p->body, (const struct Collision*)0x08362528);
          (p->s).work[3] = 1;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      nm = (p->s).mode[2] + 1;
      asm volatile("");
      goto setm;
    case 3:
      SetMotion(&p->s, 0xA50D);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4:
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) != 3) {
        break;
      }
      nm = (p->s).mode[2] + 1;
      asm volatile("");
      goto setm;
    case 5: {
      register s32 z asm("r4");
      z = 0;
      (p->s).work[2] = 0x1e;
      SetMotion(&p->s, 0xA50B);
      SetDDP(&p->body, &sCollisions[1]);
      PlaySound(0x7b);
      (p->s).work[3] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 6:
      if ((p->s).work[3] == 0) {
        if ((s8)*((u8*)p + 0x71) == 4) {
          register s32 one asm("r0");
          SetDDP(&p->body, (const struct Collision*)0x08362528);
          one = 1;
          asm volatile("strb %0, [%1, #0x13]" ::"l"(one), "l"(p) : "memory");
        }
      }
      UpdateMotionGraphic(&p->s);
      asm volatile("");
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      asm volatile("");
      nm = (p->s).mode[2] + 1;
      asm volatile("");
      goto setm;
    case 7:
      SetMotion(&p->s, 0xA50D);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      asm volatile("");
      FALLTHROUGH;
    case 8: {
      register s32 st asm("r1");
      UpdateMotionGraphic(&p->s);
      st = *((u8*)p + 0x73);
      if (st != 3) {
        break;
      }
      nm = 0;
      (p->s).mode[1] = st;
    setm:
      (p->s).mode[2] = nm;
      break;
    }
  }
}


bool8 FUN_080450bc(struct Boss* p) { return TRUE; }

INCASM("asm/boss/volteel_p11.inc");

bool8 FUN_08045464(struct Boss* p) { return TRUE; }

void FUN_080459e8(struct Boss* p);

void volteelEX(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x30;
      (p->s).work[3] = 4;
      SetMotion(&p->s, MOTION(0xa5, 0xe));
      SetDDP(&p->body, &sCollisions[8]);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 2:
      PlaySound(0x7F);
      SetMotion(&p->s, MOTION(0xa5, 0xf));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2];
      if (t != 0) {
        t -= 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      t = (p->s).work[3];
      if (t != 0) {
        t -= 1;
        (p->s).work[3] = t;
        if ((t << 24) != 0) goto ex;
      }
      (p->s).mode[2]++;
      break;
    ex:
      FUN_080459e8(p);
      PlaySound(0x80);
      (p->s).work[2] = 0x30;
      break;
    }
    case 4:
      StopSound(0x7F);
      SetMotion(&p->s, MOTION(0xa5, 0xa));
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      /* fallthrough */
    case 5: {
      u8 st;
      UpdateMotionGraphic(&p->s);
      st = (p->s).motion.state;
      if (st == 3) {
        (p->s).mode[1] = st;
        (p->s).mode[2] = 0;
      }
      break;
    }
  }
}

bool8 FUN_08045570(struct Boss* p) { return TRUE; }

// 0x08045574
void volteelMode11(struct Boss* p) {
  struct Entity** slot;
  register u8 m asm("r5");
  m = (p->s).mode[2];
  if (m == 0) {
    if (isSoundPlaying(0x7F)) {
      StopSound(0x7F);
    }
    {
      register s32 off asm("r1");
      u8* g;
      g = (u8*)&gOverworld;
      if ((gOverworld.terrain.id & 0x7F) == 0xD) {
        off = 0x2D024;
        asm("" : "+r"(off) : "r"(m));
      } else {
        off = 0x2D026;
        asm("" : "+r"(off));
      }
      {
        register u8* t asm("r0");
        t = g + off;
        *t = m;
      }
    }
    {
      u8 v = (p->s).flags;
      register u8 fv asm("r1");
      fv = 1;
      fv |= v;
      (p->s).flags = fv;
    }
    PlaySound(0x81);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    u32 z = 0;
    u8 a;
    u8 r;
    *slot = (struct Entity*)z;
    a = *(u8*)((u8*)p + 0xd0);
    {
      register s32 ac asm("r1");
      asm volatile("add %0, %1, #0" : "=&l"(ac) : "l"(a));
      if (ac != 5 && ac != 9) {
        goto other;
      }
    }
    {
      (p->s).mode[1] = a;
      (p->s).mode[2] = *(u8*)((u8*)p + 0xd1);
      r = *(u8*)((u8*)p + 0xd2);
      goto done;
    }
  other:
    {
      (p->s).mode[1] = 3;
      (p->s).mode[2] = z;
      r = 0xFF;
    }
  done:
    (p->s).mode[3] = r;
  }
}

bool8 FUN_08045610(struct Boss* p) { return TRUE; }

s32 PushoutToUp2(s32 x, s32 y);
s32 PushoutToLeft2(s32 x, s32 y);
s32 PushoutToRight2(s32 x, s32 y);

// 0x08045614
void volteelKnockBackDamage(struct Boss* p) {
  register s32 z asm("r5");
  z = (p->s).mode[2];
  switch (z) {
    case 0: {
      register u8* oa asm("r2");
      PlaySound(0x81);
      SetMotion(&p->s, 0xA504);
      if (isSoundPlaying(0x7f)) {
        StopSound(0x7f);
      }
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        register s32 g asm("r0");
        register s32 k asm("r1");
        (p->s).d.x = -0x200;
        *((u8*)p + 0x4c) = 1;
        oa = (u8*)p + 0x4a;
        g = *oa;
        k = 0x10;
        g |= k;
        *oa = g;
        {
          register s32 fv asm("r0");
          fv = (p->s).flags;
          k |= fv;
          (p->s).flags = k;
        }
      } else {
        register s32 ov asm("r1");
        register s32 m asm("r0");
        (p->s).d.x = 0x80 << 2;
        *((u8*)p + 0x4c) = z;
        oa = (u8*)p + 0x4a;
        ov = *oa;
        m = -0x11;
        m &= ov;
        *oa = m;
        {
          register u8 h asm("r1");
          register u8 g2 asm("r0");
          h = (p->s).flags;
          asm("" : "+r"(h));
          g2 = 0xEF;
          g2 &= h;
          (p->s).flags = g2;
        }
      }
      {
        register u8* oa2 asm("r5");
        register s32 zr asm("r3");
        oa2 = oa;
        {
          register s32* cp asm("r0");
          cp = (s32*)((u8*)p + 0xc0);
          zr = 0;
          *cp = zr;
        }
        {
          register u8* gw asm("r2");
          register s32 off asm("r1");
          register u8* dst asm("r0");
          gw = (u8*)&gOverworld;
          off = 0xe8 << 1;
          if ((*(u16*)(gw + off) & 0x7f) == 0xd) {
            off = 0x0002D024;
          } else {
            off = 0x0002D026;
          }
          dst = gw + off;
          *dst = zr;
        }
        {
          register s32 g3 asm("r0");
          register s32 h3 asm("r1");
          register s32 z2 asm("r2");
          h3 = (p->s).flags;
          asm("" : "+r"(h3));
          g3 = 1;
          z2 = 0;
          g3 |= h3;
          (p->s).flags = g3;
          {
            register u8* q asm("r3");
            register s32 ov2 asm("r1");
            register s32 m2 asm("r0");
            register s32 k8 asm("r1");
            q = (u8*)p + 0x49;
            ov2 = *q;
            m2 = 0xd;
            m2 = -m2;
            m2 &= ov2;
            k8 = 8;
            m2 |= k8;
            *q = m2;
          }
          {
            register u8* a2 asm("r0");
            a2 = (u8*)p + 0x24;
            *a2 = z2;
            a2 += 0x29;
            asm("" : "+r"(a2));
            *a2 = z2;
          }
        }
        {
          register s32 ov3 asm("r1");
          register s32 m3 asm("r0");
          ov3 = *oa2;
          m3 = -0x21;
          m3 &= ov3;
          *oa2 = m3;
        }
        {
          register u8 h4 asm("r1");
          register u8 g4 asm("r0");
          h4 = (p->s).flags;
          asm("" : "+r"(h4));
          g4 = 0xDF;
          g4 &= h4;
          (p->s).flags = g4;
        }
      }
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 dx asm("r1");
      register s32 cy asm("r2");
      UpdateMotionGraphic(&p->s);
      {
        register s32 v asm("r0");
        v = (p->s).d.x;
        dx = -v;
        dx <<= 3;
        dx >>= 8;
        v += dx;
        (p->s).d.x = v;
      }
      {
        register s32 v2 asm("r0");
        register s32 lim asm("r1");
        v2 = (p->s).d.y;
        v2 += 0x20;
        (p->s).d.y = v2;
        lim = 0xe0 << 3;
        if (v2 > lim) {
          (p->s).d.y = lim;
        }
      }
      {
        register s32 yv asm("r1");
        register s32 dyv asm("r0");
        yv = (p->s).coord.y;
        dyv = (p->s).d.y;
        cy = yv + dyv;
        (p->s).coord.y = cy;
      }
      {
        register s32 cx asm("r0");
        cx = (p->s).coord.x;
        dx = (p->s).d.x;
        cx += dx;
        (p->s).coord.x = cx;
        if (dx > 0) {
          register s32 k3 asm("r3");
          register s32 yy asm("r1");
          k3 = 0x90 << 5;
          cx += k3;
          k3 = -0x800;
          yy = cy + k3;
          yy = PushoutToLeft2(cx, yy);
          if (yy != 0) {
            (p->s).coord.x += yy;
          }
        }
      }
      if ((p->s).d.x < 0) {
        register s32 xx asm("r0");
        register s32 k4 asm("r1");
        register s32 k5 asm("r2");
        xx = (p->s).coord.x;
        k4 = -0x1200;
        xx += k4;
        k4 = (p->s).coord.y;
        k5 = -0x800;
        k4 += k5;
        k4 = PushoutToRight2(xx, k4);
        if (k4 != 0) {
          (p->s).coord.x += k4;
        }
      }
      {
        register s32 pu asm("r1");
        pu = PushoutToUp2((p->s).coord.x, (p->s).coord.y);
        if (pu != 0) {
          (p->s).coord.y += pu;
        }
      }
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      {
        register s32 z3 asm("r0");
        register s32 three asm("r1");
        z3 = 0;
        three = 3;
        (p->s).mode[1] = three;
        (p->s).mode[2] = z3;
        (p->s).mode[3] = 0xff;
      }
      break;
    }
  }
}


#include "element.h"

extern const struct Coord Coord_ARRAY_08362570[7];

// 0x080457c4
bool8 volteel_080457c4(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xc0);
  if (*slot != NULL) {
    return TRUE;
  }
  if (!((p->body).status & 1)) {
    return TRUE;
  }
  {
    const struct Coord* c;
    if ((p->s).mode[1] == 9) {
      u8 w = (p->s).work[3];
      if (w == 0) {
        c = &Coord_ARRAY_08362570[4];
      } else if (w == 1) {
        c = &Coord_ARRAY_08362570[5];
      } else if (w == 2) {
        c = &Coord_ARRAY_08362570[3];
      } else if (w == 3) {
        c = &Coord_ARRAY_08362570[6];
      } else {
        goto after;
      }
    } else {
      c = &Coord_ARRAY_08362570[0];
    }
    *slot = (struct Entity*)ApplyElementEffect(0xd, &p->s, c);
  }
after : {
  struct Entity** s2 = (struct Entity**)((u8*)p + 0xc0);
  if (*s2 == NULL) {
    return TRUE;
  }
  if ((*((u8*)p + 0x97) & 0xf0) == 0x30) {
    s32 z;
    u8 v1 = (p->s).mode[1];
    u8* d0 = (u8*)p + 0xd0;
    asm("" : "+r"(d0));
    z = 0;
    *d0 = v1;
    {
      u8 v2 = (p->s).mode[2];
      u8* d1 = (u8*)p + 0xd1;
      u8 v3;
      asm("" : "+r"(d1));
      *d1 = v2;
      v3 = (p->s).mode[3];
      d1 += 1;
      asm("" : "+r"(d1));
      *d1 = v3;
    }
    (p->s).mode[1] = 0xb;
    (p->s).mode[2] = z;
  } else {
    *s2 = NULL;
  }
}
  return TRUE;
}

// 0x0804586c
void FUN_0804586c(struct Body* body) {
  register const struct Collision* c asm("r2");
  u8 a;
  c = (body->enemy)->processing;
  a = c->atkType;
  if (a == 3 || a == 14 || a == 15) {
    struct CollidableEntity* q = body->parent;
    struct CollidableEntity* r = (body->enemy)->parent;
    if (((q->body).status & BODY_STATUS_DEAD) || (q->body).hp == 0) {
      if ((gStageRun.missionStatus & MISSION_FAIL) == 0) {
        if ((r->s).d.x < 0) {
          (q->s).work[1] = 0xFF;
        } else {
          (q->s).work[1] = 0xFE;
        }
      }
    }
  }
  {
    const struct Collision* c2 = (body->enemy)->processing;
    const struct Collision* pr = body->processing;
    struct CollidableEntity* q;
    u8 m;
    if (pr->kind == 2) {
      return;
    }
    if (pr->layer == 0xFFFFFFFF) {
      return;
    }
    if ((*(u32*)&c2->atkType & 0x000200FF) != 0x00020002) {
      return;
    }
    q = body->parent;
    m = (q->s).mode[1];
    if (m == 0xc) {
      return;
    }
    if (m == 9) {
      return;
    }
    if (m == 5 && (q->s).mode[2] > 4) {
      return;
    }
    {
      s32 z = 0;
      (q->s).mode[1] = 0xc;
      (q->s).mode[2] = z;
    }
  }
}

extern const u16 unk_080fee80[3 + 5 + 4];
bool8 FUN_080459d4(struct Boss* p);

// 0x08045910 -- given a mode value, return the next one in its cyclic table.
// Which table and how long depends on `flag` and FUN_080459d4(p).
// Logic verified; parked three instructions short. Retail materialises
// `ldr r5, =&unk_080fee80[N]` separately inside each of the four arms (four
// pool entries); agbcc cse's the address constant and hoists a single load
// above the branch, so the four arms lose their own load and gain one.
// `asm("" : "+r"(t))` after each assignment does not re-materialise it -- the
// barrier makes the value opaque only after the hoisted constant is formed.
// (The bool8 return of FUN_080459d4 IS solved: the `(s32(*)(...))` cast kills
// the lsls#24/lsrs#24 mask, and routing all four `return t[idx]` through one
// `goto pick` label collapsed the duplicated index-to-value tails, 93 -> 79.)
NON_MATCH u16 FUN_08045910(struct Boss* p, u32 m, s32 flag) {
#if MODERN
  s32 ret;
  s32 i;
  s32 idx;
  const u16* t;
  const u16* q;
  if (flag == 1) {
    ret = ((s32(*)(struct Boss*))FUN_080459d4)(p);
    if (ret != 0) {
      i = 0;
      t = &unk_080fee80[8];
      q = t;
      do {
        if (*q == m) {
          idx = (i + 1) % 3;
          goto pick;
        }
        q++;
        i++;
      } while (i <= 2);
    } else {
      i = 0;
      t = &unk_080fee80[3];
      q = t;
      do {
        if (*q == m) {
          idx = (i + 1) % 5;
          goto pick;
        }
        q++;
        i++;
      } while (i <= 4);
    }
  } else {
    ret = ((s32(*)(struct Boss*))FUN_080459d4)(p);
    if (ret != 0) {
      i = 0;
      t = &unk_080fee80[8];
      q = t;
      do {
        if (*q == m) {
          idx = (i + 1) % 3;
          goto pick;
        }
        q++;
        i++;
      } while (i <= 2);
    } else {
      i = 0;
      t = &unk_080fee80[3];
      q = t;
      do {
        if (*q == m) {
          idx = (i + 1) % 4;
          goto pick;
        }
        q++;
        i++;
      } while (i <= 3);
    }
  }
  return ret;
pick:
  return t[idx];
#else
  INCCODE("asm/boss/volteel_p14_p1_b.inc");
#endif
}

bool8 FUN_080459d4(struct Boss* p) {
  if ((p->s).mode[1] == 5) {
    return TRUE;
  }
  return FALSE;
}

struct Projectile* FUN_0809f4dc(struct Entity* e, struct Coord* c, struct Coord* d, u8 n);

// 0x080459E8
void FUN_080459e8(struct Boss* p) {
  struct Coord c;
  struct Coord d;
  const s16* st;
  s32 cx = (p->s).coord.x;
  c.x = cx;
  c.y = (p->s).coord.y - 0x3E00;
  if (((p->s).flags & 0x10) == 0) {
    c.x = cx - 0x1200;
    st = gSineTable;
    d.x = st[0xb2];
    d.y = st[0xf2];
    FUN_0809f4dc(&p->s, &c, &d, 0x72);
    d.x = st[0xce];
    d.y = st[0xe];
    FUN_0809f4dc(&p->s, &c, &d, 0x8e);
  } else {
    c.x = cx + 0x1200;
    st = gSineTable;
    d.x = st[0x32];
    d.y = st[0x72];
    FUN_0809f4dc(&p->s, &c, &d, 0xf2);
    d.x = st[0x4e];
    d.y = st[0x8e];
    FUN_0809f4dc(&p->s, &c, &d, 0xe);
  }
}

void volteel_08045abc(struct Boss* p) {
  if (MOTION_VALUE(p) == MOTION(0xA5, 0x07)) {
    if ((p->s).motion.state == 3) {
      if (((p->s).flags & X_FLIP) == 0) {
        (p->s).spr.xflip = TRUE;
        (p->s).spr.oam.xflip = TRUE;
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).spr.xflip = FALSE;
        (p->s).spr.oam.xflip = FALSE;
        (p->s).flags &= ~X_FLIP;
      }
      SetMotion(&p->s, MOTION(0xA5, 0x00));
    }
  } else if (pZero2->s.coord.x > (p->s).coord.x) {
    if (((p->s).flags & X_FLIP) == 0) {
      SetMotion(&p->s, MOTION(0xA5, 0x07));
    }
  } else {
    if (((p->s).flags & X_FLIP) != 0) {
      SetMotion(&p->s, MOTION(0xA5, 0x07));
    }
  }
}

// --------------------------------------------

// 0x08362330
static const struct Collision sCollisions[24] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, -0x1200, 0x2400, 0x2600},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1800, 0x1C00, 0x2600},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0000, -0x1900, 0x1E00, 0x2800},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1C00, 0x1C00, 0x3C00},
    },
    [4] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0000, -0x1D00, 0x1E00, 0x3E00},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0200, -0x1C00, 0x1A00, 0x3600},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x2800, -0x0F00, 0x1700, 0x2100},
    },
    [7] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {-0x0300, -0x1D00, 0x1C00, 0x3800},
    },
    [8] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {-0x0700, -0x1600, 0x1F00, 0x2600},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0A00, -0x3F00, 0x2300, 0x1100},
    },
    [10] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {-0x0800, -0x1700, 0x2100, 0x2800},
    },
    [11] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0600, -0x1100, 0x7C00, 0x1000},
    },
    [12] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0700, -0x1200, 0x7E00, 0x1200},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1100, 0x1000, 0x7C00},
    },
    [14] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0000, -0x1200, 0x1200, 0x7E00},
    },
    [15] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1C00, 0x1A00, 0x3600},
    },
    [16] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0100, -0x1D00, 0x1C00, 0x3800},
    },
    [17] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0E00, 0x0000, 0x1C00, 0x0E00},
    },
    [18] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {-0x0F00, 0x0000, 0x1E00, 0x1000},
    },
    [19] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0E00, 0x0E00, 0x1C00},
    },
    [20] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0000, 0x0F00, 0x1000, 0x1E00},
    },
    [21] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {0x0000, -0x1C00, 0x1A00, 0x3600},
    },
    [22] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 5,
      atkType : 0x00,
      element : 0x01,
      nature : 0x00,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000002,
      range : {-0x4E00, -0x1900, 0x4500, 0x1000},
    },
    [23] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x06,
      remaining : 0,
      range : {0x0100, -0x1D00, 0x1C00, 0x3800},
    },
};

// 0x08362570
const struct Coord Coord_ARRAY_08362570[7] = {
    {0x00000000, -0x00002000}, {0x00000600, -0x00002500}, {0x00000600, -0x00002500}, {0x00000000, 0x00000400}, {0x00000000, 0x00000400}, {-0x00001000, 0x00000000}, {-0x00001000, 0x00000000},
};
