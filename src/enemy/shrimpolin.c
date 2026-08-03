#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "physics.h"
#include "story.h"

struct ShrimporinObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct VFX* elementEffect;
  u8 unk_004[12];
};
static_assert(sizeof(struct ShrimporinObject) == sizeof(struct Enemy));

static const EnemyFunc sUpdates1[8];
static const EnemyFunc sUpdates2[8];
static const struct Collision sCollisions[6];
static const struct Coord sElementCoord;
static const u8 sInitModes[4];
static const motion_t sMotions[4];

static void Shrimporin_Init(struct Enemy* p);
static void Shrimporin_Update(struct Enemy* p);
static void Shrimporin_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gShrimporinRoutine = {
    [ENTITY_INIT] =      Shrimporin_Init,
    [ENTITY_UPDATE] =    Shrimporin_Update,
    [ENTITY_DIE] =       Shrimporin_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void CreateShrimporin(s32 x, s32 y, u8 n, bool8 r3) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 7);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    if (r3) {
      (p->s).work[0] = 5;
    } else {
      (p->s).work[0] = 2;
    }
  }
}

void nop_08069874(struct Body* body, struct Coord* c1, struct Coord* c2) { return; }

static bool8 tryKillShrimporin(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    if ((p->s).work[0] == 2) {
      (p->s).mode[1] = 3;
    } else if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[1] = 1;
    } else if ((p->body).status & BODY_STATUS_RECOILED) {
      (p->s).mode[1] = 2;
    } else {
      (p->s).mode[1] = 0;
    }
    Shrimporin_Die(p);
    return TRUE;
  }
  return FALSE;
}

NAKED static bool8 shrimporin_080698dc(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	adds r4, r0, #0\n\
	ldrb r1, [r4, #0xd]\n\
	cmp r1, #7\n\
	beq _0806998A\n\
	ldrb r0, [r4, #0x10]\n\
	cmp r0, #2\n\
	beq _0806998A\n\
	cmp r0, #5\n\
	beq _0806998A\n\
	adds r0, r4, #0\n\
	adds r0, #0xb4\n\
	ldr r0, [r0]\n\
	cmp r0, #0\n\
	bne _0806998A\n\
	ldrb r0, [r4, #0xf]\n\
	cmp r0, #0\n\
	beq _08069906\n\
	cmp r0, #1\n\
	beq _08069948\n\
	b _0806998A\n\
_08069906:\n\
	adds r0, r4, #0\n\
	bl IsFrozen\n\
	cmp r0, #0\n\
	beq _0806998A\n\
	ldr r1, _08069940 @ =sUpdates1\n\
	ldrb r0, [r4, #0xd]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	ldr r1, [r0]\n\
	adds r0, r4, #0\n\
	bl _call_via_r1\n\
	ldr r1, _08069944 @ =sUpdates2\n\
	ldrb r0, [r4, #0xd]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	ldr r1, [r0]\n\
	adds r0, r4, #0\n\
	bl _call_via_r1\n\
	ldrb r0, [r4, #0xf]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xf]\n\
	adds r0, r4, #0\n\
	bl UpdateMotionGraphic\n\
_0806993C:\n\
	movs r0, #1\n\
	b _0806998C\n\
	.align 2, 0\n\
_08069940: .4byte sUpdates1\n\
_08069944: .4byte sUpdates2\n\
_08069948:\n\
	cmp r1, #2\n\
	bne _08069966\n\
	ldrb r0, [r4, #0x13]\n\
	movs r1, #3\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _08069960\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x58]\n\
	ldrb r2, [r4, #0x11]\n\
	bl FUN_080b8f68\n\
_08069960:\n\
	ldrb r0, [r4, #0x13]\n\
	adds r0, #1\n\
	strb r0, [r4, #0x13]\n\
_08069966:\n\
	adds r0, r4, #0\n\
	bl IsFrozen\n\
	cmp r0, #0\n\
	beq _08069988\n\
	adds r0, r4, #0\n\
	adds r0, #0x8c\n\
	ldr r0, [r0]\n\
	ldr r1, _08069984 @ =0x00020001\n\
	ands r0, r1\n\
	cmp r0, r1\n\
	bne _0806993C\n\
	movs r0, #0\n\
	strb r0, [r4, #0xf]\n\
	b _0806998C\n\
	.align 2, 0\n\
_08069984: .4byte 0x00020001\n\
_08069988:\n\
	strb r0, [r4, #0xf]\n\
_0806998A:\n\
	movs r0, #0\n\
_0806998C:\n\
	pop {r4}\n\
	pop {r1}\n\
	bx r1\n\
 .syntax divided\n");
}

void shrimporin_08069994(struct ShrimporinObject* p) {
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

static void FUN_080699e0(struct Enemy* p) {
  if (((p->body).status & (BODY_STATUS_WHITE | BODY_STATUS_RECOILED)) == (BODY_STATUS_WHITE | BODY_STATUS_RECOILED)) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

// --------------------------------------------

NAKED static void Shrimporin_Init(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	ldr r1, _08069A24 @ =gEnemyFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	ldrb r0, [r6, #0x10]\n\
	cmp r0, #2\n\
	bls _08069A28\n\
	subs r0, #3\n\
	strb r0, [r6, #0x10]\n\
	strb r1, [r6, #0x11]\n\
	b _08069A2C\n\
	.align 2, 0\n\
_08069A24: .4byte gEnemyFnTable\n\
_08069A28:\n\
	movs r0, #0\n\
	strb r0, [r6, #0x11]\n\
_08069A2C:\n\
	ldr r1, _08069A84 @ =sInitModes\n\
	ldrb r0, [r6, #0x10]\n\
	adds r0, r0, r1\n\
	ldrb r0, [r0]\n\
	movs r4, #0\n\
	movs r5, #0\n\
	strb r0, [r6, #0xd]\n\
	ldrb r0, [r6, #0x10]\n\
	cmp r0, #2\n\
	beq _08069AB4\n\
	adds r1, r6, #0\n\
	adds r1, #0xb8\n\
	ldr r0, [r6, #0x54]\n\
	str r0, [r1]\n\
	ldr r0, [r6, #0x54]\n\
	ldr r1, [r6, #0x58]\n\
	bl FUN_0800a05c\n\
	str r0, [r6, #0x58]\n\
	ldr r0, _08069A88 @ =gSystemSavedataManager\n\
	ldrb r1, [r0, #0x14]\n\
	movs r0, #4\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08069A94\n\
	ldr r0, _08069A8C @ =gCurStory\n\
	ldrb r1, [r0, #4]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _08069A94\n\
	ldrb r0, [r6, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _08069A90 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0xc\n\
	b _08069ACA\n\
	.align 2, 0\n\
_08069A84: .4byte sInitModes\n\
_08069A88: .4byte gSystemSavedataManager\n\
_08069A8C: .4byte gCurStory\n\
_08069A90: .4byte sCollisions\n\
_08069A94:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #4\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _08069AB0 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #8\n\
	b _08069ACA\n\
	.align 2, 0\n\
_08069AB0: .4byte sCollisions\n\
_08069AB4:\n\
	ldrb r0, [r6, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _08069B04 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #1\n\
_08069ACA:\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	str r5, [r4, #0x24]\n\
	adds r1, r6, #0\n\
	adds r1, #0xb4\n\
	movs r0, #0\n\
	str r0, [r1]\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #2\n\
	orrs r0, r1\n\
	movs r1, #1\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	ldrb r0, [r6, #0x11]\n\
	adds r1, r6, #0\n\
	adds r1, #0x22\n\
	strb r0, [r1]\n\
	ldr r0, _08069B08 @ =nop_08069874\n\
	str r0, [r4, #0x24]\n\
	adds r0, r6, #0\n\
	bl Shrimporin_Update\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08069B04: .4byte sCollisions\n\
_08069B08: .4byte nop_08069874\n\
 .syntax divided\n");
}

// --------------------------------------------

static void FUN_080699e0(struct Enemy* p);
static void nop_08069c20(struct Enemy* p);
static void shrimporin_08069c24(struct ShrimporinObject* p);

// clang-format off
static const EnemyFunc sUpdates1[8] = {
    (EnemyFunc)shrimporin_08069c24,
    (EnemyFunc)nop_08069c20,
    (EnemyFunc)nop_08069c20,
    (EnemyFunc)FUN_080699e0,
    (EnemyFunc)FUN_080699e0,
    (EnemyFunc)nop_08069c20,
    (EnemyFunc)FUN_080699e0,
    (EnemyFunc)nop_08069c20,
};
// clang-format on

void shrimporin_08069c80(struct Enemy* p);
void shrimporin_08069d00(struct Enemy* p);
void shrimporinBurrowSnow(struct Enemy* p);
void popoutShrimporin(struct Enemy* p);
void shrimporinSpin(struct Enemy* p);
void shrimporinIce(struct Enemy* p);
void shrimporin_0806a230(struct Enemy* p);
void shrimporin_0806a544(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[8] = {
    shrimporin_08069c80,
    shrimporin_08069d00,
    shrimporinBurrowSnow,
    popoutShrimporin,
    shrimporinSpin,
    shrimporinIce,
    shrimporin_0806a230,
    shrimporin_0806a544,
};
// clang-format on

static void Shrimporin_Update(struct Enemy* p) {
  if ((p->s).work[0] == 2) {
    if (IS_METTAUR) {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      return;
    }
    if (tryKillShrimporin(p)) {
      return;
    }
  } else {
    if (tryKillShrimporin(p)) {
      return;
    }
    shrimporin_08069994((void*)p);
    if (shrimporin_080698dc(p)) {
      return;
    }
  }

  (sUpdates1[(p->s).mode[1]])((void*)p);
  (sUpdates2[(p->s).mode[1]])((void*)p);
}

// --------------------------------------------

void explodeShrimpolin(struct Enemy* p);
void slashShrimporin(struct Enemy* p);
void shrimporin_0806a544(struct Enemy* p);
void shrimporin_0806a4ec(struct Enemy* p);

static void Shrimporin_Die(struct Enemy* p) {
  static const EnemyFunc sDeads[4] = {
      explodeShrimpolin,
      slashShrimporin,
      shrimporin_0806a544,
      shrimporin_0806a4ec,
  };

  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeads[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void nop_08069c20(struct Enemy* p) { return; }

static void shrimporin_08069c24(struct ShrimporinObject* p) {
  struct VFX* elementEffect = p->elementEffect;
  if (elementEffect == NULL || isKilled(&elementEffect->s)) {
    p->elementEffect = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen((void*)p)) {
      (p->s).mode[1] = 6;
      (p->s).mode[2] = 0;
    }
  }

  if (((p->body).status & 0x20001) == 0x20001) {
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

s32 FUN_0800a40c(s32 x, s32 y);

// One copy from a match: retail relocates the wall-pushout call result to r1
// before loading coord.x into r0; agbcc keeps the result in place in every
// spelling tried (plain +=, s32 temp, s16 temp).
NON_MATCH void shrimporin_08069c80(struct Enemy* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).d.y = 0;
      SetDDP(&p->body, &sCollisions[2]);
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
          s32 r = PushoutToUp2((p->s).coord.x, (p->s).coord.y + PIXEL(8));
          if (r < 0) {
            (p->s).d.y = f;
            (p->s).coord.y += r;
          }
        }
      }
      (p->s).coord.x += FUN_0800a40c((p->s).coord.x, (p->s).coord.y + PIXEL(12));
      break;
    }
  }
#else
  INCCODE("asm/enemy/shrimporin_9c80.inc");
#endif
}

// 0x08069d00
void shrimporin_08069d00(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register u8 fv asm("r0");
      register u8 t asm("r1");
      SetDDP(&p->body, sCollisions);
      t = (p->s).flags;
      fv = 0xFE;
      fv &= t;
      (p->s).flags = fv;
      asm volatile("" ::"r"(t));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 d = (pZero2->s).coord.x - (p->s).coord.x;
      u8 w = (p->s).work[0];
      if (w == 0) {
        if (d <= 0x77FF) {
          (p->s).mode[1] = 2;
          (p->s).mode[2] = w;
        }
      } else {
        if (d > 0x7800) {
          s32 z = 0;
          (p->s).mode[1] = 2;
          (p->s).mode[2] = z;
        }
      }
      break;
    }
  }
}

INCASM("asm/enemy/shrimpolin.inc");

void createShrimporinIce(s32 x, s32 y, u8 n);

void popoutShrimporin(struct Enemy* p) {
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0:
      PlaySound(0x55);
      (p->s).flags |= DISPLAY;
      GotoMotion(&p->s, MOTION(0x0D, 0x01), 1, 1);
      UpdateMotionGraphic(&p->s);
      (p->s).work[2] = 0x10;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 2: {
      s32 on;
      SetDDP(&p->body, &sCollisions[1]);
      createShrimporinIce((p->s).coord.x, (p->s).coord.y, (p->s).work[1]);
      SetMotion(&p->s, MOTION(0x0D, 0x02));
      on = 0;
      if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
        on = 1;
      }
      SET_XFLIP(p, on);
      {
        register s32 w18 asm("r1");
        w18 = 0x18;
        asm("" : "+r"(w18));
        (p->s).d.y = -0x5AA;
        (p->s).coord.y += -0x800;
        (p->s).work[2] = w18;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 3: {
      u8 t;
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.y += 0x40;
      t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void shrimporinSpin(struct Enemy* p) {
  u8 md = (p->s).mode[2];
  switch (md) {
    case 0:
      SetMotion(&p->s, MOTION(0x0D, 0x03));
      (p->s).work[2] = md;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = 0;
      }
      if ((s8)(p->s).motion.cmdIdx == 5 && (p->s).work[2] == 0) {
        s32 one = 1;
        s32 x2;
        (p->s).work[2] = one;
        x2 = (p->s).coord.x - 0x700;
        if ((p->s).flags & 0x10) {
          x2 = (p->s).coord.x + 0x700;
        }
        CreateShrimporin(x2, (p->s).coord.y + 0xF00, ((p->s).flags >> 4) & one, (p->s).work[1]);
      }
      break;
  }
}

// 0x0806A0F8
void shrimporinIce(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      s32 dx;
      s32 dy;
      s32 d;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, MOTION(0x0D, 0x06));
      (p->s).d.x = (pZero2->s).coord.x - (p->s).coord.x;
      {
        u8 w2 = (p->s).work[2];
        if ((p->s).d.x > 0) {
          if (w2 != 1) {
            goto zero;
          }
          goto aim;
        }
        if (w2 == 0) {
          goto aim;
        }
      }
    zero:
      (p->s).d.x = 0;
      (p->s).d.y = 0x280;
      goto done;
    aim:
      {
        struct Zero* z = pZero2;
        s32 yy = (p->s).coord.y + 0x1800;
        dy = (z->s).coord.y - yy;
      }
      (p->s).d.y = dy;
      dx = (p->s).d.x;
      d = (dx >> 8) * (dx >> 8);
      d += (dy >> 8) * (dy >> 8);
      d = (u16)Sqrt(d) << 8;
      if (d != 0) {
        s32 ux = ((p->s).d.x << 8) / d;
        s32 uy;
        (p->s).d.x = ux;
        uy = ((p->s).d.y << 8) / d;
        (p->s).d.y = uy;
        (p->s).d.x = (ux * 5 << 7) / 256;
        (p->s).d.y = (uy * 5 << 7) / 256;
      } else {
        (p->s).d.x = 0x280;
        (p->s).d.y = d;
      }
    done:
      (p->s).work[2] = 0xFF;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 x = (p->s).coord.x + (p->s).d.x;
      s32 y;
      (p->s).coord.x = x;
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      (p->s).work[2]--;
      if ((u16)GetGroundMetatileAttr(x, y) != 0 || ((p->body).status & 4) != 0 ||
          (p->s).work[2] == 0) {
        SET_ENEMY_ROUTINE(p, ENTITY_DIE);
        (p->s).mode[1] = 3;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

bool8 IsVoidSpace(s32 x, s32 y);

// 0x0806A230
void shrimporin_0806a230(struct Enemy* p) {
  s32 r;
  u8 m2 = (p->s).mode[2];
  switch (m2) {
    case 0:
      (p->s).flags |= DISPLAY;
      (p->s).d.x = m2;
      (p->s).d.y = m2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 dx;
      (p->s).coord.x += (p->s).d.x;
      dx = (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (dx != 0) {
        if (dx > 0) {
          r = PushoutToLeft2((p->s).coord.x + 0xC00, (p->s).coord.y - 0x800);
          if (r >= 0) {
            goto up;
          }
        } else {
          r = PushoutToRight2((p->s).coord.x - 0xC00, (p->s).coord.y - 0x800);
          if (r <= 0) {
            goto up;
          }
        }
        (p->s).coord.x += r;
      }
    up:
      r = PushoutToUp2((p->s).coord.x, (p->s).coord.y + 0x600);
      if ((u8)IsVoidSpace((p->s).coord.x, (p->s).coord.y) != 0) {
        u32 z;
        u8 t = (p->s).flags;
        u8 fv = 0xFE;
        fv &= t;
        asm volatile("" ::"r"(t));
        z = 0;
        fv &= 0xFD;
        (p->s).flags = fv;
        (p->body).status = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
        break;
      }
      if (r >= 0) {
        break;
      }
      if ((p->s).d.x != 0) {
        s32* q = (s32*)((u8*)p + 0xb8);
        s32 x = (p->s).coord.x;
        s32 b = *q;
        if (x > b) {
          if (x <= b + 0x16800) {
            goto place;
          }
          *q = x + -0x16800;
          goto place2;
        }
        if (x >= b - 0x16800) {
          goto place;
        }
        *q = x + 0x16800;
      place2:;
      }
    place:
      (p->s).coord.y += r;
      createShrimporinIce((p->s).coord.x, (p->s).coord.y, (p->s).work[1]);
      {
        u8 z2 = 0;
        (p->s).mode[1] = 2;
        (p->s).mode[2] = z2;
      }
      break;
    }
  }
}

#include "mission.h"
#include "vfx.h"

void FUN_080b8080(struct Enemy* p, struct Coord* c, const motion_t* m, s32 n, s32 a4);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x0806a370
void explodeShrimpolin(struct Enemy* p) {
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
  FUN_080b8080(p, &c, sMotions, 3, (p->s).work[1]);
  co = &(p->s).coord;
  TryDropItem(2, co);
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, co);
  SET_ENEMY_ROUTINE(p, 4);
}

struct Entity* FUN_080b2b40(u8 kind, struct Coord* c, u16 r2, bool16 isDirRight);
void FUN_080b869c(struct Entity* e, struct Coord* c, struct Coord* dc, s32 y, motion_t* motions, u8 frame, u8 taskCol, u8 palID);

// 0x0806A40C
void slashShrimporin(struct Enemy* p) {
  register s32 z asm("r6");
  z = (p->s).mode[2];
  switch (z) {
    case 0: {
      register s32 dir asm("r4");
      struct Coord c;
      dir = 0;
      if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
        dir = 1;
      }
      SetMotion(&p->s, MOTION(0x0D, 0x04));
      {
        u8* a = (u8*)p + 0x8c;
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = z;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = z;
      }
      (p->s).flags &= ~COLLIDABLE;
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y;
      ((struct Entity* (*)(s32, struct Coord*, s32, s32))FUN_080b2b40)(0, &c, 0x200, dir);
      {
        register s32 k asm("r1");
        k = 0x60;
        c.x = k - ((dir * 3) << 6);
        c.y = k;
      }
      FUN_080b869c(&p->s, &(p->s).coord, &c, 0x40, (motion_t*)&sMotions[3], 0x18, 1, (p->s).work[1]);
      (p->s).work[2] = 0x18;
      (p->s).d.y = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t;
      (p->s).d.y += 0x30;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      t <<= 24;
      if (t != 0) {
        if ((u16)GetGroundMetatileAttr((p->s).coord.x, (p->s).coord.y) == 0) {
          break;
        }
      }
      explodeShrimpolin(p);
      break;
    }
  }
}



void shrimporinIceCrash(s32 x, s32 y, u8 frame);

void shrimporin_0806a4ec(struct Enemy* p) {
  (p->body).status = 0;
  (p->body).prevStatus = 0;
  (p->body).invincibleTime = 0;
  (p->s).flags &= ~COLLIDABLE;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  if ((p->s).work[1] == 0) {
    PlaySound(0x3F);
  } else {
    PlaySound(0x122);
  }
  shrimporinIceCrash((p->s).coord.x, (p->s).coord.y, (p->s).work[1]);
}

INCASM("asm/enemy/shrimpolin_b.inc");

// --------------------------------------------

static const struct Collision sCollisions[6] = {
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
      damage : 2,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1800, 0x1800},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x04,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x1800, 0x1800},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [4] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x04,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1800, 0x1800},
    },
};

static const struct Coord sElementCoord = {0, 0};

static const u8 sInitModes[4] = {1, 1, 5, 0};

static const motion_t sMotions[4] = {
    MOTION(SM013_SHRIMPOLIN, 0x07),
    MOTION(SM013_SHRIMPOLIN, 0x08),
    MOTION(SM013_SHRIMPOLIN, 0x08),
    MOTION(SM013_SHRIMPOLIN, 0x05),
};
