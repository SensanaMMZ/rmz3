#include "boss.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "motion.h"
#include "overworld.h"
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

INCASM("asm/boss/volteel_p1b.inc");

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

INCASM("asm/boss/volteel_p6.inc");

bool8 FUN_080440c0(struct Boss* p) { return TRUE; }

INCASM("asm/boss/volteel_p7.inc");

bool8 FUN_080449f0(struct Boss* p) { return TRUE; }

INCASM("asm/boss/volteel_p8.inc");

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

INCASM("asm/boss/volteel_p10.inc");

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

INCASM("asm/boss/volteel_p14_p1.inc");

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

INCASM("asm/boss/volteel_p14_p2.inc");

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
