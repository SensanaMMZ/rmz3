#include "palette_animation.h"
#include "boss.h"
#include "stagerun.h"
#include "collision.h"
#include "global.h"
#include "mission.h"
#include "motion.h"
#include "overworld.h"
#include "zero.h"

struct Entity* CreateVFX55(struct Boss* e, u8 r1, u8 r2);

void copyx_08057744(struct Boss* p);

static void CopyX_Init(struct Boss* p);
static void CopyX_Update(struct Boss* p);
static void CopyX_Die(struct Boss* p);

// clang-format off
const BossRoutine gCopyXRoutine = {
    [ENTITY_INIT] =      (BossFunc)CopyX_Init,
    [ENTITY_UPDATE] =    (BossFunc)CopyX_Update,
    [ENTITY_DIE] =       (BossFunc)CopyX_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void CreateCopyX(struct Coord* c) {
  struct Entity* p = AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_COPY_X);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    (p->coord).x = c->x;
    (p->coord).y = c->y;
    p->work[0] = 0, p->work[1] = 0;
  }
}

// --------------------------------------------

static const struct Collision sCollisions[];

NAKED static void CopyX_Init(struct Boss* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sl\n\
	mov r6, sb\n\
	mov r5, r8\n\
	push {r5, r6, r7}\n\
	adds r7, r0, #0\n\
	movs r4, #0xeb\n\
	lsls r4, r4, #3\n\
	ldr r5, _08055620 @ =gStaticMotionGraphics\n\
	adds r0, r4, r5\n\
	ldr r1, _08055624 @ =wStaticGraphicTilenums\n\
	mov sb, r1\n\
	adds r1, #0xbc\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	mov r8, r2\n\
	add r1, r8\n\
	bl LoadGraphic\n\
	ldr r6, _08055628 @ =gStaticMotionGraphics+12\n\
	adds r4, r4, r6\n\
	ldr r0, _0805562C @ =wStaticMotionPalIDs\n\
	mov sl, r0\n\
	adds r0, #0xbc\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	ldr r4, _08055630 @ =0x00000744\n\
	adds r0, r4, r5\n\
	mov r1, sb\n\
	adds r1, #0xba\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	add r1, r8\n\
	bl LoadGraphic\n\
	adds r4, r4, r6\n\
	mov r0, sl\n\
	adds r0, #0xba\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r0, #0x80\n\
	lsls r0, r0, #2\n\
	adds r1, r1, r0\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	ldr r4, _08055634 @ =0x0000071C\n\
	adds r0, r4, r5\n\
	mov r1, sb\n\
	adds r1, #0xb6\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	add r1, r8\n\
	bl LoadGraphic\n\
	adds r4, r4, r6\n\
	mov r0, sl\n\
	adds r0, #0xb6\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	movs r4, #0xe6\n\
	lsls r4, r4, #3\n\
	adds r0, r4, r5\n\
	mov r1, sb\n\
	adds r1, #0xb8\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	add r1, r8\n\
	bl LoadGraphic\n\
	adds r4, r4, r6\n\
	mov r0, sl\n\
	adds r0, #0xb8\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r0, #0x80\n\
	lsls r0, r0, #2\n\
	adds r1, r1, r0\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	ldr r4, _08055638 @ =0x0000076C\n\
	adds r0, r4, r5\n\
	mov r1, sb\n\
	adds r1, #0xbe\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	add r1, r8\n\
	bl LoadGraphic\n\
	adds r4, r4, r6\n\
	mov r0, sl\n\
	adds r0, #0xbe\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	movs r4, #0xf0\n\
	lsls r4, r4, #3\n\
	adds r0, r4, r5\n\
	mov r1, sb\n\
	adds r1, #0xc0\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	add r1, r8\n\
	bl LoadGraphic\n\
	adds r4, r4, r6\n\
	mov r0, sl\n\
	adds r0, #0xc0\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r0, #0x80\n\
	lsls r0, r0, #2\n\
	adds r1, r1, r0\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	ldr r4, _0805563C @ =0x00000794\n\
	adds r5, r4, r5\n\
	mov r0, sb\n\
	adds r0, #0xc2\n\
	ldrh r1, [r0]\n\
	ldrh r0, [r5, #6]\n\
	lsrs r0, r0, #6\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	add r1, r8\n\
	adds r0, r5, #0\n\
	bl LoadGraphic\n\
	adds r4, r4, r6\n\
	mov r0, sl\n\
	adds r0, #0xc2\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	adds r0, r7, #0\n\
	bl InitNonAffineMotion\n\
	adds r0, r7, #0\n\
	bl ResetDynamicMotion\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #1\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	strb r0, [r7, #0xa]\n\
	ldr r1, _08055640 @ =0x0000B319\n\
	adds r0, r7, #0\n\
	bl SetMotion\n\
	adds r0, r7, #0\n\
	bl UpdateMotionGraphic\n\
	adds r0, r7, #0\n\
	adds r0, #0x4c\n\
	strb r5, [r0]\n\
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
	ldr r1, _08055644 @ =sCollisions\n\
	adds r0, r7, #0\n\
	movs r2, #0x40\n\
	bl ResetBossBody\n\
	ldr r1, _08055648 @ =CopyX_OnDamage\n\
	adds r0, r7, #0\n\
	adds r0, #0x74\n\
	str r1, [r0, #0x24]\n\
	ldr r0, [r7, #0x54]\n\
	ldr r1, [r7, #0x58]\n\
	bl FUN_0800a134\n\
	adds r1, r7, #0\n\
	adds r1, #0xb8\n\
	str r0, [r1]\n\
	ldr r0, [r7, #0x54]\n\
	ldr r1, [r7, #0x58]\n\
	bl FUN_0800a31c\n\
	adds r1, r7, #0\n\
	adds r1, #0xb4\n\
	str r0, [r1]\n\
	ldr r0, [r7, #0x54]\n\
	ldr r1, [r7, #0x58]\n\
	bl FUN_08009f6c\n\
	adds r1, r7, #0\n\
	adds r1, #0xd4\n\
	str r0, [r1]\n\
	str r0, [r7, #0x58]\n\
	subs r1, #0x18\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [r1]\n\
	adds r1, #4\n\
	ldr r0, [r7, #0x58]\n\
	str r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xc5\n\
	strb r5, [r0]\n\
	adds r0, #1\n\
	strb r5, [r0]\n\
	adds r0, #1\n\
	strb r5, [r0]\n\
	adds r1, #0xa\n\
	movs r4, #0\n\
	movs r0, #0x80\n\
	lsls r0, r0, #1\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xcc\n\
	strb r4, [r0]\n\
	adds r0, #1\n\
	strb r4, [r0]\n\
	adds r1, #0xe\n\
	movs r0, #0x3c\n\
	strh r0, [r1]\n\
	adds r1, #5\n\
	movs r0, #0x30\n\
	strb r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xcf\n\
	strb r4, [r0]\n\
	subs r1, #1\n\
	movs r0, #0xe\n\
	strb r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xde\n\
	strb r4, [r0]\n\
	subs r1, #0xc\n\
	movs r0, #0x10\n\
	strh r0, [r1]\n\
	adds r0, r7, #0\n\
	adds r0, #0xd2\n\
	movs r1, #0x80\n\
	lsls r1, r1, #2\n\
	strh r1, [r0]\n\
	str r5, [r7, #0x2c]\n\
	adds r1, r7, #0\n\
	adds r1, #0xce\n\
	movs r0, #0x18\n\
	strb r0, [r1]\n\
	adds r0, r7, #0\n\
	movs r1, #1\n\
	movs r2, #0\n\
	bl FUN_080a9aa0\n\
	ldr r1, _0805564C @ =gBossFnTable\n\
	ldrb r0, [r7, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r7, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r7, #0x14]\n\
	strb r4, [r7, #0xd]\n\
	strb r1, [r7, #0xe]\n\
	adds r0, r7, #0\n\
	bl CopyX_Update\n\
	pop {r3, r4, r5}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	mov sl, r5\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08055620: .4byte gStaticMotionGraphics\n\
_08055624: .4byte wStaticGraphicTilenums\n\
_08055628: .4byte gStaticMotionGraphics+12\n\
_0805562C: .4byte wStaticMotionPalIDs\n\
_08055630: .4byte 0x00000744\n\
_08055634: .4byte 0x0000071C\n\
_08055638: .4byte 0x0000076C\n\
_0805563C: .4byte 0x00000794\n\
_08055640: .4byte 0x0000B319\n\
_08055644: .4byte sCollisions\n\
_08055648: .4byte CopyX_OnDamage\n\
_0805564C: .4byte gBossFnTable\n\
 .syntax divided\n");
}

static void copyx_080557a4(struct Boss* p);
static void copyxMode1(struct Boss* p);
void copyxNeutral(struct Boss* p);
void copyxNextMode(struct Boss* p);
void copyxMode4(struct Boss* p);
void copyxMode5(struct Boss* p);
void copyxMode6(struct Boss* p);
void copyxMode7(struct Boss* p);
void copyxMode8(struct Boss* p);
void copyxMode9(struct Boss* p);
void copyxMode10(struct Boss* p);
void copyxMode11(struct Boss* p);
void copyxMode12(struct Boss* p);
void copyxJumpForNovaStrike(struct Boss* p);
void copyxNovaStrike2(struct Boss* p);
void copyxNovaStrike3(struct Boss* p);
void copyxMode16(struct Boss* p);
void copyxMode17(struct Boss* p);
void copyxMode18(struct Boss* p);
void copyxMode19(struct Boss* p);
void copyx_08056508(struct Boss* p);
void copyx_080565c0(struct Boss* p);
void copyx_080566b0(struct Boss* p);
void copyx_08056724(struct Boss* p);
void copyx_08056794(struct Boss* p);
void copyx_080568bc(struct Boss* p);
void copyx_08056908(struct Boss* p);
void FUN_080569a4(struct Boss* p);
void copyx_080569e4(struct Boss* p);
void FUN_08056a80(struct Boss* p);
void copyx_08056ac0(struct Boss* p);
void copyx_08056b6c(struct Boss* p);
void copyx_08056bd0(struct Boss* p);
void copyxKnockBackDamage(struct Boss* p);
void FUN_08056d58(struct Boss* p);
void copyxRaisingExcharge(struct Boss* p);
void copyxMode36(struct Boss* p);
void copyx_08057094(struct Boss* p);
void copyxMode38(struct Boss* p);

static void CopyX_Update(struct Boss* p) {
  // clang-format off
  static const BossFunc sUpdates[39] = {
      [0] =  copyx_080557a4,
      [1] =  copyxMode1,
      [2] =  copyxNeutral,
      [3] =  copyxNextMode,
      [4] =  copyxMode4,
      [5] =  copyxMode5,
      [6] =  copyxMode6,
      [7] =  copyxMode7,
      [8] =  copyxMode8,
      [9] =  copyxMode9,
      [10] = copyxMode10,
      [11] = copyxMode11,
      [12] = copyxMode12,
      [13] = copyxJumpForNovaStrike,
      [14] = copyxNovaStrike2,
      [15] = copyxNovaStrike3,
      [16] = copyxMode16,
      [17] = copyxMode17,
      [18] = copyxMode18,
      [19] = copyxMode19,
      [20] = copyx_08056508,
      [21] = copyx_080565c0,
      [22] = copyx_080566b0,
      [23] = copyx_08056724,
      [24] = copyx_08056794,
      [25] = copyx_080568bc,
      [26] = copyx_08056908,
      [27] = FUN_080569a4,
      [28] = copyx_080569e4,
      [29] = FUN_08056a80,
      [30] = copyx_08056ac0,
      [31] = copyx_08056b6c,
      [32] = copyx_08056bd0,
      [33] = copyxKnockBackDamage,
      [34] = FUN_08056d58,
      [35] = copyxRaisingExcharge,
      [36] = copyxMode36,
      [37] = copyx_08057094,
      [38] = copyxMode38,
  };
  // clang-format on

  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    StartPaletteAnimation(92, 640);
    StepPaletteAnimation(92);
    RemovePaletteAnimation(92);
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[2] = 1;
    EXIT_BODY(p);
    CopyX_Die(p);
    return;
  }

  copyx_08057744(p);
  if ((p->s).mode[1] != 33) {
    ((p->props).copyx).unk_dd = (p->body).hp - 16;
    if (((p->props).copyx).unk_dd < 0) {
      ((p->props).copyx).unk_dd = 0;
    }
  }

  // Check if Copy X is flinching
  if (((p->body).status & BODY_STATUS_WHITE) && (((p->body).unk_23 != 0) || ((p->body).status & (BODY_STATUS_B14 | BODY_STATUS_B15)))) {
    if ((u8)((p->s).mode[1] - 5) > 1) {
      if ((p->s).mode[1] != 9) {
        if ((p->s).mode[1] != 10) {
          if ((p->s).mode[1] != 11) {
            (p->s).mode[1] = 33;  // flinch(0x08056c14)
            (p->s).mode[2] = 1;
            (p->s).mode[3] = 33;
          }
        }
      }
    }
  }

  (sUpdates[(p->s).mode[1]])(p);
  StartPaletteAnimation(92 + ((p->props).copyx).unk_c5, 640);
  StepPaletteAnimation(92 + ((p->props).copyx).unk_c5);
  RemovePaletteAnimation(92 + ((p->props).copyx).unk_c5);
  UpdateMotionGraphic(&p->s);
}

void copyx_08057204(struct Boss* p);
void copyx_08057418(struct Boss* p);
void copyx_08057520(struct Boss* p);
void copyx_08057590(struct Boss* p);
void copyx_0805763c(struct Boss* p);

static void CopyX_Die(struct Boss* p) {
  // clang-format off
  static const BossFunc sDeads[5] = {
      [0] = copyx_08057204,
      [1] = copyx_08057418,
      [2] = copyx_08057520,
      [3] = copyx_08057590,
      [4] = copyx_0805763c,
  };
  // clang-format on
  copyx_08057744(p);
  (sDeads[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void copyx_080557a4(struct Boss* p) {
  if ((p->s).scriptEntity->flags & (1 << 0)) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 1;
  }
}

static void copyxMode1(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(DM179_COPY_X, 26));
    CreateVFX55(p, 0, 0);
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
    (p->s).work[2] = 0;
  }
  if (((p->s).work[2] == 0) && ((p->s).motion.cmdIdx == 6)) {
    PlaySound(SE_COPYX_MODE_CHANGE);
    (p->s).work[2]++;
  }
  if ((p->s).mode[3] == 0) {
    if ((p->s).motion.state == MOTION_END) {
      (p->s).mode[3]++;
    }
  } else if (!(gStageRun.vm.active & 1)) {
    SetMotion(&p->s, MOTION(DM179_COPY_X, 0));
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/copy_x_p1.inc");

void copyxNextMode(struct Boss* p) {
  UpdateMotionGraphic(&p->s);
  if (--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = (p->s).mode[3];
    (p->s).mode[2] = 1;
  }
}

void copyxMode4(struct Boss* p) {
  UpdateMotionGraphic(&p->s);
  ((p->props).copyx).unk_c6[0] = 1;
  (p->s).mode[1] = 3;
  (p->s).mode[2] = 1;
  (p->s).mode[3] = 2;
  {
    s16 hp = (p->body).hp;
    if (hp < 32) {
      (p->s).work[2] = 8;
    } else if (hp < 48) {
      (p->s).work[2] = 4;
    } else {
      (p->s).work[2] = 2;
    }
  }
}

INCASM("asm/boss/copy_x_p2_p1.inc");

void copyxMode8(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x10));
    (p->s).mode[2] = 0;
    {
      s32 t = (p->s).d.x >> 3;
      *(s16*)((u8*)p + 0xc8) = t;
    }
  }
  (p->s).d.x += *(s16*)((u8*)p + 0xc8);
  (p->s).coord.x += (p->s).d.x;
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 1;
    (p->s).mode[3] = 2;
    SetMotion(&p->s, MOTION(0xb3, 0x00));
    (p->s).work[2] = 8;
    SetDDP(&p->body, sCollisions);
  }
  UpdateMotionGraphic(&p->s);
}

void copyxMode9(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, 0xB305);
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 0xa;
    (p->s).mode[2] = 1;
  }
}

void copyxMode10(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, 0xb306);
    (p->s).mode[2] = 0;
    SetDDP(&p->body, &sCollisions[0]);
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0) {
    (p->s).mode[1] = (p->s).mode[3];
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/copy_x_p2_p2_b.inc");

void copyxMode12(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, 0xB305);
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).mode[1] = 3;
  (p->s).mode[2] = 1;
  (p->s).mode[3] = 2;
  (p->s).work[2] = 6;
}

INCASM("asm/boss/copy_x_p2_p3_p1_p1_a.inc");

void copyxNovaStrike2(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x09));
    (p->s).mode[2] = 0;
    (p->s).d.x = 0;
    (p->s).d.y = 0;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x10;
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 15;
    (p->s).mode[2] = 1;
  }
}

void createCopyXSonicBoom(struct Entity* e, u8 w0, u8 w1);

// r3/r5 keep transposition: retail saves the pZero2 pool address in r3 across
// both derefs and stages s5 in r5 (mine swap them), and the xflip-arm's 0xFFF8
// pool value takes r0 directly into the merged strh (mine r2+copy); the
// remaining ~55 bytes are these register-number diffs.
NON_MATCH void copyxNovaStrike3(struct Boss* p) {
#if MODERN
  if ((p->s).mode[2] != 0) {
    u8* pde;
    SetMotion(&p->s, 0xB30A);
    (p->s).mode[2] = 0;
    if ((p->s).flags & X_FLIP) {
      (p->s).d.x = 0x380;
      *(u16*)((u8*)p + 0xc8) = 0xFFF8;
    } else {
      (p->s).d.x = -0x380;
      *(u16*)((u8*)p + 0xc8) = 8;
    }
    (p->s).d.y = 0;
    (p->s).work[2] = 0;
    {
      register u8* pt asm("r0");
      u8 fv;
      pt = (u8*)p + 0xde;
      fv = *pt;
      asm("" : "=r"(pde) : "0"(pt));
      if (fv != 0) {
        SetDDP((struct Body*)(pt - 0x6a), &sCollisions[6]);
        PlaySound(0x46);
      } else {
        SetDDP(&p->body, &sCollisions[2]);
        PlaySound(0x46);
      }
    }
    createCopyXSonicBoom(&p->s, 1, 0);
    *pde = 0;
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 dx = (p->s).d.x;
    s32 w1b;
    (p->s).coord.x += dx;
    w1b = (p->s).work[2] + 1;
    (p->s).work[2] = w1b;
    if ((p->s).coord.y < *(s32*)((u8*)p + 0xb8) + 0xF000) {
      (p->s).work[2] = w1b + 1;
      {
        struct Zero* z = pZero2;
        if ((p->s).coord.y > z->s.coord.y) {
          (p->s).coord.y += -0x200;
        }
      }
      {
        s32 ax = *(s32*)((u8*)p + 0xb4);
        s32 cx = (p->s).coord.x;
        if (cx < ax + 0x1000 || cx > ax + 0x14000) {
          (p->s).mode[1] = 0xB;
          (p->s).mode[2] = 1;
        }
        {
          u32 sh = *(volatile u8*)((u8*)p + 0xa) >> 4;
          u32 nf = 1;
          u32 s5 = 0;
          s32 zx;
          nf &= ~sh;
          zx = pZero2->s.coord.x;
          if (zx < cx) {
            s5 = 1;
          }
          if (nf != s5) {
            s32 d2 = zx - cx;
            if (d2 >= 0) {
              if (d2 > 0x4000) {
                goto far2;
              }
            } else if (cx - zx > 0x4000) {
              goto far2;
            }
          }
          goto out;
        far2:
          if ((p->s).work[2] > 0x28) {
            u8* pc6 = (u8*)p + 0xc6;
            u8 c6 = *pc6;
            if (c6 == 0) {
              (p->s).mode[1] = 0xA;
              (p->s).mode[3] = 0x15;
              (p->s).d.x = c6;
              (p->s).d.y = c6;
              goto setm2;
            }
            goto set0b;
          }
        out:;
        }
      }
    } else {
      s32 nd = dx + *(s16*)((u8*)p + 0xc8);
      s32 a;
      (p->s).d.x = nd;
      a = nd;
      if (a < 0) {
        a = -a;
      }
      if (a <= 0x3FF) {
        if (*(volatile u8*)((u8*)p + 0xa) & X_FLIP) {
          (p->s).d.x = 0x400;
        } else {
          (p->s).d.x = -0x400;
        }
      }
      if ((p->s).work[2] > 0x28) {
      set0b:
        (p->s).mode[1] = 0xB;
      setm2:
        (p->s).mode[2] = 1;
      }
    }
  }
#else
  INCCODE("asm/boss/copy_x_nova3.inc");
#endif
}

INCASM("asm/boss/copy_x_p2_p3_p1_p1_b_a.inc");

extern const u8 u8_ARRAY_080fefb0[4];

// 0x08056338
void copyxMode17(struct Boss* p) {
  u8 arr[4];
  memcpy(arr, u8_ARRAY_080fefb0, 4);
  if ((p->s).mode[2] != 0) {
    if (*((u8*)p + 0xc5) == 0 && (gMission.unk_00)->rank > 4 && *((u8*)p + 0xc6) != 0) {
      (p->s).mode[1] = 0x25;
      copyx_08057094(p);
      return;
    }
    SetMotion(&p->s, MOTION(0xB3, 0x01));
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 0x12;
    (p->s).mode[2] = 1;
    if (*((u8*)p + 0xc6) != 0) {
      (p->s).work[3] = 1;
    } else {
      (p->s).work[3] = arr[*((u8*)p + 0xc5)];
    }
  }
}

extern const u8 u8_ARRAY_080fefb4[4];

void copyxMode18(struct Boss* p) {
  u8 arr[4];
  memcpy(arr, u8_ARRAY_080fefb4, 4);
  if ((p->s).mode[2] != 0) {
    u8 w;
    SetMotion(&p->s, MOTION(0xB3, 0x02));
    (p->s).mode[2] = 0;
    if (((p->props).copyx).unk_c6[0] != 0) {
      w = 4;
    } else {
      w = arr[((p->props).copyx).unk_c5];
    }
    (p->s).work[2] = w;
  }
  UpdateMotionGraphic(&p->s);
  if ((u8)--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 0x13;
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/copy_x_p2_p3_p1_p1_b_a2.inc");
extern const u8 u8_ARRAY_080fefb4[4];

void copyx_080566b0(struct Boss* p) {
  u8 arr[4];
  memcpy(arr, u8_ARRAY_080fefb0, 4);
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x15));
    (p->s).mode[2] = 0;
    (p->s).d.x = 0;
    (p->s).d.y = 0;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x10;
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 0x17;
    (p->s).mode[2] = 1;
    if (*((u8*)p + 0xc6) != 0) {
      (p->s).work[3] = 1;
    } else {
      (p->s).work[3] = arr[*((u8*)p + 0xc5)];
    }
  }
}

void copyx_08056724(struct Boss* p) {
  u8 arr[4];
  memcpy(arr, u8_ARRAY_080fefb4, 4);
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x16));
    (p->s).mode[2] = 0;
    if (*((u8*)p + 0xc6) != 0) {
      (p->s).work[2] = 4;
    } else {
      (p->s).work[2] = arr[*((u8*)p + 0xc5)];
    }
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 0x18;
    (p->s).mode[2] = 1;
  }
}

void FUN_080a83e4(struct Entity* e, u8 w0, u8 w1);
void FUN_080a88a4(struct Entity* e, u8 a1, u8 a2);
void FUN_080a9048(struct Entity* e, u8 a1, u8 a2);

// 0x08056794
void copyx_08056794(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u8* q;
    u8 z;
    SetMotion(&p->s, MOTION(0xB3, 0x17));
    (p->s).mode[2] = 0;
    if ((p->s).flags & X_FLIP) {
      (p->s).d.x = -0x200;
    } else {
      (p->s).d.x = 0x200;
    }
    (p->s).d.y = -0x200;
    q = &((p->props).copyx).unk_c6[0];
    z = *q;
    if (z != 0) {
      u8 z0;
      FUN_080a83e4(&p->s, 3, 0);
      z0 = 0;
      *q = z0;
      (p->s).work[2] = 0xC;
      ((p->props).copyx).unk_c6[1] = z0;
      PlaySound(0x46);
    } else {
      s16 sid;
      switch (((p->props).copyx).unk_c5) {
        case 0:
          FUN_080a83e4(&p->s, 2, 0);
          goto snd46;
        case 1:
          FUN_080a88a4(&p->s, 1, 6);
          (p->s).work[2] = 0xC;
          ((p->props).copyx).unk_c6[1] = 6;
          break;
        case 2:
          FUN_080a9048(&p->s, 1, 0);
          sid = 0x49;
          goto play;
        case 3:
          FUN_080a9048(&p->s, 4, 0);
        snd46:
          sid = 0x46;
        play:
          PlaySound(sid);
          (p->s).work[2] = 6;
          ((p->props).copyx).unk_c6[1] = z;
          break;
      }
    }
  }
  UpdateMotionGraphic(&p->s);
  {
    u8* w3 = &((p->props).copyx).unk_c6[1];
    if (*w3 != 0) {
      *w3 = *w3 - 1;
      return;
    }
  }
  (p->s).coord.x += (p->s).d.x;
  {
    s32 y = (p->s).coord.y;
    s32 dy = (p->s).d.y;
    (p->s).coord.y = y + dy;
    dy += 0x40;
    (p->s).d.y = dy;
  }
  if ((u8)--(p->s).work[2] == 0xFF) {
    u8 m = 0xFF;
    if ((m & --(p->s).work[3]) == 0) {
      (p->s).mode[1] = 0x19;
    } else {
      (p->s).mode[1] = 0x17;
    }
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/copy_x_p1_b_a2.inc");

void copyx_080568bc(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x18));
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 11;
    (p->s).mode[2] = 1;
  }
}

// 0x08056908
void copyx_08056908(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u8 z;
    SetMotion(&p->s, MOTION(0xB3, 0x0B));
    z = 0;
    (p->s).mode[2] = z;
    (p->s).work[2] = z;
  }
  UpdateMotionGraphic(&p->s);
  switch ((p->s).work[2]) {
    case 0x2C:
    case 0x70:
    case 0xB4:
      PlaySound(0x3C);
    case 0x35:
    case 0x3E:
    case 0x79:
    case 0x82:
    case 0xBD:
    case 0xC6:
      FUN_080a9048(&p->s, 2, 0);
      FUN_080a9048(&p->s, 2, 1);
      break;
  }
  {
    s32 d = (p->s).work[2] + 1;
    u8 t;
    (p->s).work[2] = d;
    t = d;
    if (t == 0xD9) {
      (p->s).mode[1] = 0x1B;
      (p->s).mode[2] = 1;
      *(u8*)((u8*)p + 0xc6) = 0;
    }
  }
}

void FUN_080569a4(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0xc));
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == MOTION_END) {
    (p->s).mode[1] = MOTION_END;
    (p->s).mode[2] = 1;
    (p->s).mode[3] = 2;
    (p->s).work[2] = 4;
  }
}

// 0x080569E4
void copyx_080569e4(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xB3, 0x0D));
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  {
    u8 t = *(u8*)((u8*)p + 0x73);
    if (t == 3) {
      u8 z = 0;
      (p->s).mode[1] = t;
      (p->s).mode[2] = 1;
      (p->s).mode[3] = 0x1D;
      FUN_080a88a4(&p->s, 4, 0);
      FUN_080a88a4(&p->s, 4, 1);
      FUN_080a88a4(&p->s, 4, 2);
      FUN_080a88a4(&p->s, 4, 3);
      FUN_080a88a4(&p->s, 4, 4);
      FUN_080a88a4(&p->s, 4, 5);
      FUN_080a88a4(&p->s, 4, 6);
      FUN_080a88a4(&p->s, 4, 7);
      *(u8*)((u8*)p + 0xc6) = z;
      (p->s).work[2] = 0x28;
      PlaySound(0x46);
    }
  }
}

void FUN_08056a80(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0xe));
    (p->s).mode[2] = 0;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == MOTION_END) {
    (p->s).mode[1] = MOTION_END;
    (p->s).mode[2] = 1;
    (p->s).mode[3] = 2;
    (p->s).work[2] = 4;
  }
}

// 0x08056AC0
void copyx_08056ac0(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    struct Zero* z;
    register u32 v asm("r3");
    SetMotion(&p->s, MOTION(0xB3, 1));
    v = 0;
    asm("" : "+r"(v));
    z = pZero2;
    if ((z->s).coord.x > (p->s).coord.x) {
      v = 1;
    }
    (p->s).spr.xflip = v;
    v = (z->s).coord.x > (p->s).coord.x;
    (p->s).spr.oam.xflip = v;
    if (v) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
  }
  if ((p->s).mode[3] != 0) {
    if (*(u8*)((u8*)p + 0x73) == 3) {
      SetMotion(&p->s, MOTION(0xB3, 2));
    }
  } else {
    if (*(u8*)((u8*)p + 0x73) == 3) {
      (p->s).mode[1] = 0x1f;
      (p->s).mode[2] = 1;
    }
  }
  UpdateMotionGraphic(&p->s);
}

void FUN_080a9aa0(struct Entity* e, u8 kind1, u8 kind2);

void copyx_08056b6c(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x03));
    (p->s).mode[2] = 0;
    (p->s).work[2] = 0x40;
    PlaySound(0x46);
  }
  UpdateMotionGraphic(&p->s);
  if (((p->s).work[2] & 7) == 0) {
    FUN_080a9aa0(&p->s, 0, 0);
  }
  if ((u8)--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 0x20;
    (p->s).mode[2] = 1;
    *(u8*)((u8*)p + 0xc6) = 0;
  }
}

// 0x08056bd0
void copyx_08056bd0(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, 0xB303);
    (p->s).mode[2] = 0;
    (p->s).work[2] = 0x40;
  }
  UpdateMotionGraphic(&p->s);
  {
    u8 st = (p->s).motion.state;
    if (st == 3) {
      (p->s).mode[1] = st;
      (p->s).mode[2] = 1;
      (p->s).mode[3] = 2;
      (p->s).work[2] = 4;
    }
  }
}

INCASM("asm/boss/copy_x_p2_p3_p1_p2_p2_b1.inc");

struct Entity* CreateVFX52(struct Entity* e);

void copyxRaisingExcharge(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    GotoMotion(&p->s, 0xB31A, 10, 0);
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
    {
      s32 onR = 0;
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        onR = 1;
      }
      ((p->s).spr).xflip = onR;
    }
    {
      s32 onR2 = 0;
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        onR2 = 1;
      }
      {
        register u8* t0 asm("r0");
        register u8* oa asm("ip");
        register u32 sh asm("r2");
        u32 off = 0x4a;
        asm("" : "+r"(off));
        off += (u32)p;
        t0 = (u8*)off;
        oa = t0;
        asm("" : "+r"(oa));
        sh = onR2 << 4;
        {
          s32 ov = *t0;
          s32 m11 = -0x11;
          u32 vv;
          register u8* fa asm("r1");
          asm("" : "+r"(m11));
          vv = (m11 & ov) | sh;
          fa = oa;
          asm("" : "+r"(fa));
          *fa = vv;
        }
      }
      if (onR2 != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
    }
    (p->s).work[2] = 0xC;
    PlaySound(0x4A);
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 m3 asm("r1");
    m3 = (p->s).mode[3];
    if (m3 == 0) {
      s32 raw = (p->s).work[2] - 1;
      (p->s).work[2] = raw;
      if ((u8)raw == 0xFF) {
        SetDDP(&p->body, &sCollisions[4]);
        (p->s).unk_2c = CreateVFX52(&p->s);
        (p->s).work[2] = 0x20;
        goto adv;
      }
    } else if (m3 == 1) {
      s32 raw2 = (p->s).work[2] - 1;
      s32 z = 0;
      (p->s).work[2] = raw2;
      if ((u8)raw2 == 0xFF) {
        (p->s).unk_2c->work[1] = m3;
        (p->s).unk_2c = (struct Entity*)z;
        (p->s).work[2] = z;
        FUN_080a9aa0(&p->s, 2, z);
      adv:
        (p->s).mode[3]++;
      }
    } else {
      if (((p->s).work[2] & 3) == 0) {
        (*(u16*)((u8*)p + 0xa4))++;
        (*(u16*)((u8*)p + 0xd8))++;
        PlaySound(0x4B);
      }
      {
        u8 w = (p->s).work[2];
        if (w == 0x7F || (gStageRun.missionStatus & 8)) {
          (p->s).mode[1] = 3;
          (p->s).mode[2] = 1;
          (p->s).mode[3] = 2;
          SetDDP(&p->body, &sCollisions[0]);
          (p->s).work[2] = 4;
        } else {
          (p->s).work[2] = w + 1;
        }
      }
    }
  }
}

INCASM("asm/boss/copy_x_p2_p3_p1_p2_p2_b2.inc");

void copyx_08057418(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, MOTION(0xb3, 0x6));
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
    {
      s32* pb = (s32*)((u8*)p + 0xb4);
      s32 t = (p->s).coord.x - 0xA800;
      (p->s).d.x = (*pb - t) / 20;
    }
    (p->s).d.y = -0x500;
    (p->s).work[2] = 0x14;
  }
  {
    u8* xa = &((p->s).spr).xflip;
    s32 z = 0;
    *xa = z;
    {
      u8* a = (u8*)&((p->s).spr).oam + 6;
      register u8 b asm("r1");
      s32 msk;
      b = *a;
      msk = z - 0x11;
      msk &= b;
      *a = msk;
    }
  }
  (p->s).flags &= ~X_FLIP;
  switch ((p->s).mode[3]) {
    case 0: {
      (p->s).coord.y += (p->s).d.y;
      (p->s).d.y += 0x40;
      if ((u8)--(p->s).work[2] == 0xFF) {
        SetMotion(&p->s, MOTION(0xb3, 0x14));
        (p->s).mode[3]++;
        (p->s).work[2] = 0x14;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((u8)--(p->s).work[2] == 0xFF) {
        (p->s).mode[3]++;
        (p->s).work[2] = 0x30;
      }
      break;
    case 2:
      if ((u8)--(p->s).work[2] == 0xFF) {
        (p->s).mode[3]++;
      }
      break;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 1;
      }
      break;
  }
}

void copyx_08057520(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    (p->s).mode[2] = 0;
    PlaySound(0x11A);
    StartPaletteAnimation(0x62, 0x280);
    (p->s).work[2] = 0x24;
  }
  UpdateMotionGraphic(&p->s);
  StepPaletteAnimation(0x62);
  (p->s).spr.xflip = 0;
  (p->s).spr.oam.xflip = 0;
  (p->s).flags &= ~X_FLIP;
  if ((u8)--(p->s).work[2] == 0xFF) {
    RemovePaletteAnimation(0x62);
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 1;
  }
}

struct Entity* CreateVFX56(struct Entity* e, u8 a, u8 b);

// 0x08057590
void copyx_08057590(struct Boss* p) {
  if (((p->s).scriptEntity->flags & 2) == 0) {
    return;
  }
  if ((p->s).mode[2] != 0) {
    u8 z = 0;
    (p->s).mode[2] = z;
    StartPaletteAnimation(0x63, 0x280);
    PlaySound(0x39);
    (p->s).work[2] = 0xFF;
    (p->s).work[3] = z;
  }
  UpdateMotionGraphic(&p->s);
  StepPaletteAnimation(0x63);
  {
    u8 m = 7 & (p->s).work[2];
    if (m == 3) {
      CreateVFX56(&p->s, 2, (p->s).work[3]);
      (p->s).work[3] += 0xC;
    } else if (m == 7) {
      u32 t = RNG_0202f388 * 0x343FD + 0x269EC3;
      t <<= 1;
      RNG_0202f388 = t >> 1;
      CreateVFX56(&p->s, 2, t >> 0x11);
    }
  }
  {
    u8 fl = (p->s).scriptEntity->flags;
    register u8 four asm("r4");
    u32 v;
    four = 4;
    asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(four));
    v &= fl;
    if (v != 0) {
      u8 z;
      RemovePaletteAnimation(0x63);
      z = 0;
      (p->s).mode[1] = four;
      (p->s).mode[2] = z;
    }
  }
}

struct Entity* CreateVFX39(struct Coord* c, u8 r1, u8 r2);

void copyx_0805763c(struct Boss* p) {
  struct Coord c;
  u32 m2 = (p->s).mode[2];
  if (m2 == 0) {
    struct Entity** a;
    struct Entity* v;
    c.x = (p->s).coord.x;
    c.y = (p->s).coord.y - 0x1000;
    v = CreateVFX39(&c, 1, 0);
    a = (struct Entity**)((u8*)p + 0xe0);
    *a = v;
    if (v == NULL) {
      return;
    }
    *((u8*)*a + 0x74) = 0x1F;
    *((u8*)*a + 0x75) = 0x1F;
    *((u8*)*a + 0x76) = 0x1F;
    *(s32*)((u8*)*a + 0x78) = m2;
    asm volatile("" ::: "memory");
    *((u8*)*a + 0x7c) = 0x21;
    *((u8*)*a + 0x7d) = 0x1E;
    StartPaletteAnimation(0x64, 0x280);
    gStageRun.vm.active |= VM_FLAG1;
    (p->s).work[2] = 0xFF;
    (p->s).work[3] = m2;
    StopSound(0x39);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).mode[2] <= 1) {
    s32 msk;
    struct Entity** a2;
    StepPaletteAnimation(0x64);
    {
      u8 w3 = (p->s).work[3];
      s32 t = w3 + 4;
      if (t > 0xFF) {
        t = 0xFF;
      }
      (p->s).work[3] = t;
      asm volatile("" :: "r"(w3));
    }
    msk = (p->s).work[2] & 1;
    if (msk != 0) {
      struct Entity** b = (struct Entity**)((u8*)p + 0xe0);
      *(s32*)((u8*)*b + 0x78) = (p->s).work[3] << 8;
      a2 = b;
    } else {
      s32 v = ((p->s).work[3] << 8) - 0xF00;
      if (v > 0) {
        struct Entity** b = (struct Entity**)((u8*)p + 0xe0);
        *(s32*)((u8*)*b + 0x78) = v;
        a2 = b;
      } else {
        struct Entity** b = (struct Entity**)((u8*)p + 0xe0);
        *(s32*)((u8*)*b + 0x78) = msk;
        a2 = b;
      }
    }
    if ((u8)--(p->s).work[2] == 0xFF) {
      RemovePaletteAnimation(0x64);
      *((u8*)*a2 + 0x77) = 1;
      (p->s).mode[2]++;
    }
  }
}

void copyx_08057744(struct Boss* p) {
  s32 b = *(s32*)&((p->props).copyx).unk_b4[0];
  s32 x;
  s32 lim = b + 0x1000;
  if ((x = (p->s).coord.x) < lim || x > b + 0x14000) {
    (p->s).coord.x = *(s32*)&((p->props).copyx).unk_b4[8];
  }
  *(s32*)&((p->props).copyx).unk_b4[8] = (p->s).coord.x;
  {
    s32 b2 = *(s32*)&((p->props).copyx).unk_b4[4];
    s32 y;
    s32 lim2 = b2 + 0x3000;
    if ((y = (p->s).coord.y) < lim2) {
      (p->s).coord.y = *(s32*)&((p->props).copyx).unk_b4[0xc];
    }
    *(s32*)&((p->props).copyx).unk_b4[0xc] = (p->s).coord.y;
  }
}

void CopyX_OnDamage(struct Body* body) {
  if (body->hitboxFlags & 1) {
    struct Boss* self = (struct Boss*)body->parent;
    u8 r = 0;
    if ((self->s).coord.x < (pZero2->s).coord.x) {
      r = 1;
    }
    *(u8*)((u8*)self + 0xc4) = r;
  }
}

void copyx_080577c8(struct Boss* p) {
  if (*((u8*)p + 0xc6) != 0) {
    s32 md = *((u8*)p + 0xc5);
    switch (md) {
      case 0: {
        struct Zero* z = pZero2;
        if (((z->s).coord.x >> 8) & 1) {
          goto m11;
        }
        (p->s).mode[1] = 9;
        (p->s).mode[3] = 0x15;
        (p->s).d.x = ((z->s).coord.x - (p->s).coord.x) / 0x58;
        (p->s).d.y = -0x580;
        break;
      }
      case 1:
        (p->s).mode[1] = 0x1C;
        break;
      case 2:
        (p->s).mode[1] = 0x1A;
        break;
      case 3:
        (p->s).mode[1] = 0x1E;
        break;
    }
  } else {
    if (*((u8*)p + 0xc5) == 0) {
      if ((RANDOM(RNG_0202f388) & 0xF) > 9) {
        goto tele;
      }
    } else {
      if ((RANDOM(RNG_0202f388) & 0xF) > 5) {
        goto tele;
      }
    }
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 1;
    return;
  tele:
    {
      struct Zero* z2 = pZero2;
      if (((z2->s).coord.x >> 9) & 1) {
      m11:
        (p->s).mode[1] = 0x11;
      } else {
        (p->s).mode[1] = 9;
        (p->s).mode[3] = 0x15;
        (p->s).d.x = ((z2->s).coord.x - (p->s).coord.x) / 0x50;
        (p->s).d.y = -0x500;
      }
    }
  }
}

// 0x080578E0
void copyx_080578e0(struct Boss* p) {
  u8 buf[4];
  s32 n;
  register s32 i asm("r2");
  u8* f;
  register s32 v asm("r1");
  s32 one;
  u32 t;
  u8* sel;
  register u32* rng asm("ip");
  n = 0;
  i = 0;
  rng = &RNG_0202f388;
  {
    u8* q = (u8*)p + 0xdc;
    v = *q;
    one = 1;
    asm volatile("add %0, %1, #0" : "=&l"(f) : "l"(q));
  }
  do {
    if (((v >> i) & one) != 0) {
      buf[n] = i;
      n++;
    }
    i++;
  } while (i <= 3);
  t = *rng * 0x343FD + 0x269EC3;
  t <<= 1;
  {
    register u32 h asm("r1");
    h = t >> 1;
    *rng = h;
  }
  {
    u32 idx = (t >> 0x11) % n;
    (p->s).mode[1] = 5;
    sel = &buf[idx];
  }
  (p->s).mode[3] = *sel;
  {
    register s32 k asm("r4");
    register u32 sv asm("r0");
    register u32 b asm("r1");
    u32 msk;
    k = 1;
    asm volatile("add %0, %1, #0" : "=&l"(sv) : "l"(k));
    b = *sel;
    sv <<= b;
    msk = 0xF;
    sv ^= msk;
    sv &= *f;
    *f = sv;
    if (sv == 0) {
      register u32 sv2 asm("r0");
      register u32 b2 asm("r2");
      asm volatile("add %0, %1, #0" : "=&l"(sv2) : "l"(k));
      b2 = *sel;
      sv2 <<= b2;
      sv2 ^= msk;
      *f = sv2;
    }
  }
}

// 0x08363c18
static const struct Collision sCollisions[10] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(18), PIXEL(16), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(18), PIXEL(16), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(12), -PIXEL(24), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(12), -PIXEL(24), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(18), PIXEL(16), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(18), PIXEL(16), PIXEL(36)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0,
      hitzone : 5,
      hardness : METAL,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(12), -PIXEL(24), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(12), -PIXEL(24), PIXEL(8), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(8), PIXEL(8), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(8), PIXEL(8), PIXEL(16)},
    },
};
