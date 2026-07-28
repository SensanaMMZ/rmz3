#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
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

INCASM("asm/enemy/shrimpolin.inc");

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
