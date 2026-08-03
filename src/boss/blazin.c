#include "boss.h"
#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "overworld.h"
#include "script.h"
#include "sound.h"
#include "zero.h"

static const BossFunc sUpdates1[12];
static const BossFunc sUpdates2[12];

static void Blazin_Init(struct Boss* p);
static void Blazin_Update(struct Boss* p);
static void Blazin_Die(struct Boss* p);

// clang-format off
const BossRoutine gBlazinRoutine = {
    [ENTITY_INIT] =      (BossFunc)Blazin_Init,
    [ENTITY_UPDATE] =    (BossFunc)Blazin_Update,
    [ENTITY_DIE] =       (BossFunc)Blazin_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateBlazin(struct Coord* c, u8 n) {
  struct Entity* p = AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_BLAZIN);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = n;
  }
  return p;
}

NAKED static void Blazin_Init(struct Boss* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	adds r5, r0, #0\n\
	bl InitNonAffineMotion\n\
	adds r0, r5, #0\n\
	bl ResetDynamicMotion\n\
	ldrb r1, [r5, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r4, #0\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r0, r5, #0\n\
	adds r0, #0x4c\n\
	strb r4, [r0]\n\
	adds r2, r5, #0\n\
	adds r2, #0x4a\n\
	ldrb r1, [r2]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r1\n\
	strb r0, [r2]\n\
	ldrb r1, [r5, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
	strb r0, [r5, #0xa]\n\
	ldr r1, _0803E9A4 @ =gBlazinCollisions\n\
	adds r0, r5, #0\n\
	movs r2, #0x40\n\
	bl ResetBossBody\n\
	ldr r1, _0803E9A8 @ =FUN_0803ff28\n\
	adds r0, r5, #0\n\
	adds r0, #0x74\n\
	str r1, [r0, #0x24]\n\
	adds r0, #0x40\n\
	strb r4, [r0]\n\
	adds r1, r5, #0\n\
	adds r1, #0xb5\n\
	movs r0, #0xff\n\
	strb r0, [r1]\n\
	adds r1, #1\n\
	strb r0, [r1]\n\
	adds r0, r5, #0\n\
	adds r0, #0xc0\n\
	str r4, [r0]\n\
	subs r0, #9\n\
	strb r4, [r0]\n\
	adds r0, #0x11\n\
	movs r7, #0\n\
	strh r4, [r0]\n\
	ldr r1, [r5, #0x58]\n\
	ldr r0, _0803E9AC @ =0xFFFFC000\n\
	adds r1, r1, r0\n\
	ldr r0, [r5, #0x54]\n\
	bl FUN_08009f6c\n\
	str r0, [r5, #0x58]\n\
	adds r1, r5, #0\n\
	adds r1, #0xb8\n\
	ldr r0, [r5, #0x54]\n\
	str r0, [r1]\n\
	adds r1, #4\n\
	ldr r0, [r5, #0x58]\n\
	str r0, [r1]\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	bl FUN_0800a134\n\
	adds r6, r0, #0\n\
	ldr r0, [r5, #0x54]\n\
	adds r1, r6, #0\n\
	bl FUN_0800a22c\n\
	adds r4, r0, #0\n\
	ldr r0, [r5, #0x54]\n\
	adds r1, r6, #0\n\
	bl FUN_0800a31c\n\
	subs r4, r4, r0\n\
	asrs r6, r4, #2\n\
	adds r1, r5, #0\n\
	adds r1, #0xd4\n\
	asrs r4, r4, #3\n\
	adds r0, r0, r4\n\
	str r0, [r1]\n\
	adds r2, r5, #0\n\
	adds r2, #0xd8\n\
	adds r1, r0, r6\n\
	str r1, [r2]\n\
	adds r3, r5, #0\n\
	adds r3, #0xdc\n\
	lsls r1, r6, #1\n\
	adds r2, r0, r1\n\
	str r2, [r3]\n\
	adds r2, r5, #0\n\
	adds r2, #0xe0\n\
	adds r1, r1, r6\n\
	adds r0, r0, r1\n\
	str r0, [r2]\n\
	adds r0, r5, #0\n\
	adds r0, #0xca\n\
	strb r7, [r0]\n\
	ldrb r0, [r5, #0x10]\n\
	cmp r0, #0\n\
	bne _0803E9B4\n\
	ldr r1, _0803E9B0 @ =gBossFnTable\n\
	ldrb r0, [r5, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r5, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r5, #0x14]\n\
	strb r7, [r5, #0xd]\n\
	b _0803E9CA\n\
	.align 2, 0\n\
_0803E9A4: .4byte gBlazinCollisions\n\
_0803E9A8: .4byte FUN_0803ff28\n\
_0803E9AC: .4byte 0xFFFFC000\n\
_0803E9B0: .4byte gBossFnTable\n\
_0803E9B4:\n\
	ldr r1, _0803E9EC @ =gBossFnTable\n\
	ldrb r0, [r5, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r5, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r5, #0x14]\n\
	movs r0, #2\n\
	strb r0, [r5, #0xd]\n\
_0803E9CA:\n\
	strb r7, [r5, #0xe]\n\
	strb r7, [r5, #0xf]\n\
	movs r1, #0\n\
	strb r1, [r5, #0x11]\n\
	adds r0, r5, #0\n\
	adds r0, #0xd0\n\
	strb r1, [r0]\n\
	subs r0, #0xc\n\
	str r1, [r0]\n\
	adds r0, #8\n\
	str r1, [r0]\n\
	adds r0, r5, #0\n\
	bl Blazin_Update\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0803E9EC: .4byte gBossFnTable\n\
 .syntax divided\n");
}

// --------------------------------------------

static bool8 nop_0803ee2c(struct Boss* _);
bool8 FUN_0803ee8c(struct Boss* _);
bool8 FUN_0803ef64(struct Boss* _);
bool8 true_0803efc4(struct Boss* _);
bool8 nop_0803f280(struct Boss* _);
bool8 FUN_0803f3fc(struct Boss* _);
bool8 nop_0803f538(struct Boss* _);
bool8 nop_0803f710(struct Boss* _);
bool8 FUN_0803f9a8(struct Boss* _);
bool8 FUN_0803f9c0(struct Boss* _);
bool8 FUN_0803fc70(struct Boss* _);
bool8 FUN_0803fd58(struct Boss* _);
bool8 blazin_0803fed8(struct Boss* p);
bool8 FUN_0803ffc0(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[12] = {
    (BossFunc)nop_0803ee2c,
    (BossFunc)FUN_0803ee8c,
    (BossFunc)FUN_0803ef64,
    (BossFunc)true_0803efc4,
    (BossFunc)nop_0803f280,
    (BossFunc)FUN_0803f3fc,
    (BossFunc)nop_0803f538,
    (BossFunc)nop_0803f710,
    (BossFunc)FUN_0803f9a8,
    (BossFunc)FUN_0803f9c0,
    (BossFunc)FUN_0803fc70,
    (BossFunc)FUN_0803fd58,
};
// clang-format on

void blazinMode0(struct Boss* p);
void blazinMode1(struct Boss* p);
void blazinMode2(struct Boss* p);
void blazinNeutral(struct Boss* p);
void blazinMode4(struct Boss* p);
void blazinMode5(struct Boss* p);
void blazinMode6(struct Boss* p);
void blazinMode7(struct Boss* p);
void blazinMode8(struct Boss* p);
void blazinEX(struct Boss* p);
void blazinMode10(struct Boss* p);
void blazinKnockBackDamage(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[12] = {
    blazinMode0,
    blazinMode1,
    blazinMode2,
    blazinNeutral,
    blazinMode4,
    blazinMode5,
    blazinMode6,
    blazinMode7,
    blazinMode8,
    blazinEX,
    blazinMode10,
    blazinKnockBackDamage,
};
// clang-format on

static void Blazin_Update(struct Boss* p) {
  if (((p->body).status & BODY_STATUS_DEAD || (p->body).hp == 0) && !(gStageRun.missionStatus & 8)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    PlaySound(SE_BLAZIN_DEATH);
    if ((p->body).status & BODY_STATUS_SLASHED) {
      (p->s).mode[3] = 1;
    } else {
      (p->s).mode[3] = 0;
    }
    Blazin_Die(p);
  } else {
    struct Projectile** tailSlot = (struct Projectile**)((u8*)p + 0xc4);
    struct Projectile* tail = *tailSlot;
    if (tail != NULL && (tail->s).mode[0] > 1) {
      *tailSlot = NULL;
      FUN_0803ffc0(p);
      *(u16*)((u8*)p + 0xc8) = 0x15;
    }
    sUpdates1[(p->s).mode[1]](p);
    blazin_0803fed8(p);
    sUpdates2[(p->s).mode[1]](p);
  }
}

// --------------------------------------------

static void blazinDeath0(struct Boss* p);
static void blazinDeath1(struct Boss* p);

static void Blazin_Die(struct Boss* p) {
  static const BossFunc sDeads[2] = {
      blazinDeath0,
      blazinDeath1,
  };
  (sDeads[(p->s).mode[1]])(p);
}

static void blazinDeath0(struct Boss* p) {
  struct Coord* velocity;
  switch ((p->s).mode[2]) {
    case 0: {
      if ((gStageRun.missionStatus & MISSION_STAY) && !(gStageRun.vm.active & 1)) {
        gStageRun.missionStatus &= ~MISSION_STAY;
        gStageRun.missionStatus |= MISSION_SUCCESS;
      }
      if (isSoundPlaying(SE_COPYX_FIRESHOT)) StopSound(SE_COPYX_FIRESHOT);
      if (isSoundPlaying(SE_BLAZIN_EX)) StopSound(SE_BLAZIN_EX);
      EXIT_BODY(p);
      velocity = &(p->s).d;
      velocity->x = velocity->y = 0;
      (p->s).work[2] = 1;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
        if ((p->s).work[2] == 0) {
          (p->s).mode[2]++;
        }
      }
      break;
    }

    case 2: {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
      break;
    }
  }
}

NAKED static void blazinDeath1(struct Boss* p) {
  asm(".syntax unified\n\
	push {r4, lr}\n\
	sub sp, #8\n\
	adds r4, r0, #0\n\
	ldrb r0, [r4, #0xe]\n\
	cmp r0, #0x19\n\
	bls _0803EB8E\n\
	b _0803EE20\n\
_0803EB8E:\n\
	lsls r0, r0, #2\n\
	ldr r1, _0803EB98 @ =_0803EB9C\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.align 2, 0\n\
_0803EB98: .4byte _0803EB9C\n\
_0803EB9C: @ jump table\n\
	.4byte _0803EC04 @ case 0\n\
	.4byte _0803EC6C @ case 1\n\
	.4byte _0803EC7C @ case 2\n\
	.4byte _0803ECEE @ case 3\n\
	.4byte _0803ED54 @ case 4\n\
	.4byte _0803EE20 @ case 5\n\
	.4byte _0803EE20 @ case 6\n\
	.4byte _0803EE20 @ case 7\n\
	.4byte _0803EE20 @ case 8\n\
	.4byte _0803EE20 @ case 9\n\
	.4byte _0803EC6C @ case 10\n\
	.4byte _0803ED6A @ case 11\n\
	.4byte _0803EE20 @ case 12\n\
	.4byte _0803EE20 @ case 13\n\
	.4byte _0803EE20 @ case 14\n\
	.4byte _0803EE20 @ case 15\n\
	.4byte _0803EE20 @ case 16\n\
	.4byte _0803EE20 @ case 17\n\
	.4byte _0803EE20 @ case 18\n\
	.4byte _0803EE20 @ case 19\n\
	.4byte _0803ED7C @ case 20\n\
	.4byte _0803ED86 @ case 21\n\
	.4byte _0803ED94 @ case 22\n\
	.4byte _0803EDDC @ case 23\n\
	.4byte _0803EDF4 @ case 24\n\
	.4byte _0803EE08 @ case 25\n\
_0803EC04:\n\
	adds r0, r4, #0\n\
	adds r0, #0xc8\n\
	ldrh r1, [r0]\n\
	adds r1, #3\n\
	ldr r2, _0803EC74 @ =0xFFFFA200\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	lsls r1, r1, #0x10\n\
	lsrs r1, r1, #0x10\n\
	adds r0, r4, #0\n\
	bl SetMotion\n\
	adds r2, r4, #0\n\
	adds r2, #0x8c\n\
	ldr r0, [r2]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _0803EC38\n\
	adds r0, r4, #0\n\
	adds r0, #0xa4\n\
	movs r1, #0\n\
	ldrsh r0, [r0, r1]\n\
	cmp r0, #0\n\
	bne _0803EC4A\n\
_0803EC38:\n\
	ldr r0, _0803EC78 @ =gStageRun\n\
	ldrh r1, [r0, #8]\n\
	movs r0, #8\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _0803EC4A\n\
	ldrb r0, [r4, #0xf]\n\
	cmp r0, #1\n\
	beq _0803EC4C\n\
_0803EC4A:\n\
	movs r0, #0xa\n\
_0803EC4C:\n\
	strb r0, [r4, #0xe]\n\
	movs r1, #0\n\
	str r1, [r2]\n\
	adds r0, r4, #0\n\
	adds r0, #0x90\n\
	str r1, [r0]\n\
	adds r0, #4\n\
	strb r1, [r0]\n\
	ldrb r2, [r4, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r2\n\
	strb r0, [r4, #0xa]\n\
	adds r0, r4, #0\n\
	adds r0, #0x5c\n\
	str r1, [r0, #4]\n\
	str r1, [r4, #0x5c]\n\
_0803EC6C:\n\
	adds r0, r4, #0\n\
	bl UpdateMotionGraphic\n\
	b _0803EDE8\n\
	.align 2, 0\n\
_0803EC74: .4byte 0xFFFFA200\n\
_0803EC78: .4byte gStageRun\n\
_0803EC7C:\n\
	movs r0, #0\n\
	str r0, [r4, #0x60]\n\
	ldr r2, [r4, #0x54]\n\
	str r2, [sp]\n\
	ldr r3, [r4, #0x58]\n\
	str r3, [sp, #4]\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0x10\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _0803EC94\n\
	str r2, [sp]\n\
_0803EC94:\n\
	ldr r1, _0803ECB4 @ =0xFFFFE000\n\
	adds r0, r3, r1\n\
	str r0, [sp, #4]\n\
	ldrb r0, [r4, #0x11]\n\
	cmp r0, #0xff\n\
	beq _0803ECC2\n\
	cmp r0, #0xfe\n\
	bne _0803ECB8\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	movs r0, #0\n\
	mov r1, sp\n\
	movs r3, #0\n\
	bl FUN_080b2b40\n\
	b _0803ECE6\n\
	.align 2, 0\n\
_0803ECB4: .4byte 0xFFFFE000\n\
_0803ECB8:\n\
	ldr r0, _0803ECD4 @ =pZero2\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0x54]\n\
	cmp r0, r2\n\
	ble _0803ECD8\n\
_0803ECC2:\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	movs r0, #0\n\
	mov r1, sp\n\
	movs r3, #1\n\
	bl FUN_080b2b40\n\
	b _0803ECE6\n\
	.align 2, 0\n\
_0803ECD4: .4byte pZero2\n\
_0803ECD8:\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	movs r0, #0\n\
	mov r1, sp\n\
	movs r3, #0\n\
	bl FUN_080b2b40\n\
_0803ECE6:\n\
	movs r0, #0x2f\n\
	bl PlaySound\n\
	b _0803EDE8\n\
_0803ECEE:\n\
	adds r0, r4, #0\n\
	adds r0, #0xc4\n\
	ldr r0, [r0]\n\
	cmp r0, #0\n\
	beq _0803ED14\n\
	adds r1, r4, #0\n\
	adds r1, #0x54\n\
	ldr r2, _0803ED10 @ =0x0000A205\n\
	ldrb r3, [r4, #0xa]\n\
	lsrs r3, r3, #4\n\
	movs r0, #1\n\
	ands r3, r0\n\
	adds r0, r4, #0\n\
	bl FUN_0809c3b4\n\
	b _0803ED28\n\
	.align 2, 0\n\
_0803ED10: .4byte 0x0000A205\n\
_0803ED14:\n\
	adds r1, r4, #0\n\
	adds r1, #0x54\n\
	ldr r2, _0803ED4C @ =0x0000A21A\n\
	ldrb r3, [r4, #0xa]\n\
	lsrs r3, r3, #4\n\
	movs r0, #1\n\
	ands r3, r0\n\
	adds r0, r4, #0\n\
	bl FUN_0809c3b4\n\
_0803ED28:\n\
	adds r0, r4, #0\n\
	adds r0, #0xc8\n\
	ldrh r1, [r0]\n\
	adds r1, #4\n\
	ldr r2, _0803ED50 @ =0xFFFFA200\n\
	adds r0, r2, #0\n\
	orrs r1, r0\n\
	lsls r1, r1, #0x10\n\
	lsrs r1, r1, #0x10\n\
	adds r0, r4, #0\n\
	bl SetMotion\n\
	adds r0, r4, #0\n\
	bl UpdateMotionGraphic\n\
	movs r0, #0x44\n\
	strb r0, [r4, #0x12]\n\
	b _0803EDE8\n\
	.align 2, 0\n\
_0803ED4C: .4byte 0x0000A21A\n\
_0803ED50: .4byte 0xFFFFA200\n\
_0803ED54:\n\
	adds r0, r4, #0\n\
	bl UpdateMotionGraphic\n\
	ldrb r0, [r4, #0x12]\n\
	cmp r0, #0\n\
	beq _0803ED6A\n\
	subs r0, #1\n\
	strb r0, [r4, #0x12]\n\
	lsls r0, r0, #0x18\n\
	cmp r0, #0\n\
	bne _0803EE20\n\
_0803ED6A:\n\
	ldr r0, [r4, #0x18]\n\
	ldrb r1, [r0, #9]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _0803EE20\n\
	movs r0, #0x14\n\
	strb r0, [r4, #0xe]\n\
	b _0803EE20\n\
_0803ED7C:\n\
	movs r0, #0x50\n\
	strb r0, [r4, #0x12]\n\
	ldrb r0, [r4, #0xe]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xe]\n\
_0803ED86:\n\
	ldr r0, [r4, #0x18]\n\
	ldrb r1, [r0, #9]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _0803EE20\n\
	b _0803EDE8\n\
_0803ED94:\n\
	ldrb r0, [r4, #0xf]\n\
	cmp r0, #1\n\
	bne _0803EDB4\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0x10\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _0803EDAC\n\
	ldr r1, _0803EDA8 @ =0x08361DE8\n\
	b _0803EDCA\n\
	.align 2, 0\n\
_0803EDA8: .4byte 0x08361DE8\n\
_0803EDAC:\n\
	ldr r1, _0803EDB0 @ =0x08361DF0\n\
	b _0803EDCA\n\
	.align 2, 0\n\
_0803EDB0: .4byte 0x08361DF0\n\
_0803EDB4:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0x10\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _0803EDC8\n\
	ldr r1, _0803EDC4 @ =0x08361DD8\n\
	b _0803EDCA\n\
	.align 2, 0\n\
_0803EDC4: .4byte 0x08361DD8\n\
_0803EDC8:\n\
	ldr r1, _0803EDF0 @ =0x08361DE0\n\
_0803EDCA:\n\
	adds r0, r4, #0\n\
	bl CreateBossExplosion\n\
	adds r1, r4, #0\n\
	adds r1, #0xc0\n\
	str r0, [r1]\n\
	ldrb r0, [r4, #0xe]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xe]\n\
_0803EDDC:\n\
	adds r0, r4, #0\n\
	adds r0, #0xc0\n\
	ldr r0, [r0]\n\
	ldrb r0, [r0, #0xc]\n\
	cmp r0, #1\n\
	bls _0803EE20\n\
_0803EDE8:\n\
	ldrb r0, [r4, #0xe]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xe]\n\
	b _0803EE20\n\
	.align 2, 0\n\
_0803EDF0: .4byte 0x08361DE0\n\
_0803EDF4:\n\
	movs r0, #0x30\n\
	strb r0, [r4, #0x12]\n\
	ldr r2, _0803EE28 @ =gStageRun\n\
	ldrb r1, [r2, #0x12]\n\
	movs r0, #2\n\
	orrs r0, r1\n\
	strb r0, [r2, #0x12]\n\
	ldrb r0, [r4, #0xe]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xe]\n\
_0803EE08:\n\
	ldrb r0, [r4, #0x12]\n\
	cmp r0, #0\n\
	beq _0803EE18\n\
	subs r0, #1\n\
	strb r0, [r4, #0x12]\n\
	lsls r0, r0, #0x18\n\
	cmp r0, #0\n\
	bne _0803EE20\n\
_0803EE18:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	strb r0, [r4, #0xa]\n\
_0803EE20:\n\
	add sp, #8\n\
	pop {r4}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0803EE28: .4byte gStageRun\n\
 .syntax divided\n");
}

// --------------------------------------------

static bool8 nop_0803ee2c(struct Boss* _) { return TRUE; }

void blazinMode0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).flags |= 1;
      SetMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 0x15) | 0xA200));
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

bool8 FUN_0803ee8c(struct Boss* _) { return TRUE; }

// 0x0803EE90
void blazinMode1(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x1A;
      SetMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 0x27) | 0xA200));
      PlaySound(0x73);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)p + 0x73) != 3) {
        break;
      }
      goto inc;
    case 3:
      (p->s).work[2] = 0x1E;
      SetMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 0x28) | 0xA200));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4:
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)p + 0x73) != 3) {
        break;
      }
      FALLTHROUGH;
    case 2:
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
        if ((u8)(p->s).work[2] != 0) {
          break;
        }
      }
    inc:
      (p->s).mode[2]++;
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_0803ef64(struct Boss* _) { return TRUE; }

struct Projectile* createBlazinTail(struct Entity* e, s32 hp);

void blazinMode2(struct Boss* p) {
  struct Projectile** tailSlot;
  switch ((p->s).mode[2]) {
    case 0:
      tailSlot = (struct Projectile**)((u8*)p + 0xc4);
      *tailSlot = NULL;
      *tailSlot = createBlazinTail(&p->s, 2);
      SetMotion(&p->s, (motion_t)(*(u16*)((u8*)p + 0xc8) | 0xA200));
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

bool8 true_0803efc4(struct Boss* _) { return TRUE; }

INCASM("asm/boss/blazin_p4.inc");

bool8 nop_0803f280(struct Boss* _) { return TRUE; }

extern const struct Collision gBlazinCollisions[];
struct Entity* blazin_080403a0(struct Boss* p, u32 n);
static void setBlazinDirection(struct Entity* p);

void blazinMode4(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 r = RANDOM(RNG_0202f388) & 3;
      u8* tp = (u8*)p + 0xca;
      s32 tx;
      if (r == *tp) {
        r = (r + 1) & 3;
      }
      *tp = r;
      tx = (s32)blazin_080403a0(p, r);
      (p->s).work[2] = 0x30;
      (p->s).d.x = (tx - (p->s).coord.x) / (p->s).work[2];
      (p->s).d.y = -(0x12000 / (p->s).work[2]);
      (p->s).work[2] = 0x2F;
      (p->s).work[3] = 1;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      setBlazinDirection(&p->s);
      if ((p->s).work[3] != 0) {
        s32 t = (p->s).work[3] - 1;
        (p->s).work[3] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).mode[2]++;
      break;
    case 2:
      {
        u32 raw = *(u16*)((u8*)p + 0xc8) + 1;
        register u32 k asm("r2");
        register u32 kc asm("r0");
        u32 mm;
        k = 0xFFFFA200;
        asm("" : "+r"(k));
        kc = k;
        asm("" : "+r"(kc));
        mm = raw | kc;
        SetMotion(&p->s, (u16)mm);
      }
      SetDDP(&p->body, &gBlazinCollisions[3]);
      (p->s).mode[2]++;
      // fallthrough
    case 3: {
      s32 dy = (p->s).d.y + 0x40;
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
    case 4:
      {
        u32 raw = *(u16*)((u8*)p + 0xc8) + 2;
        register u32 k asm("r3");
        register u32 kc asm("r0");
        u32 mm;
        k = 0xFFFFA200;
        asm("" : "+r"(k));
        kc = k;
        asm("" : "+r"(kc));
        mm = raw | kc;
        SetMotion(&p->s, (u16)mm);
      }
      SetDDP(&p->body, &gBlazinCollisions[1]);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y + -0x1000);
      (p->s).mode[2]++;
      // fallthrough
    case 5:
      UpdateMotionGraphic(&p->s);
      {
        u32 st = (p->s).motion.state;
        if (st == 3) {
          s32 z = 0;
          (p->s).mode[1] = st;
          (p->s).mode[2] = z;
        }
      }
      break;
  }
}

bool8 FUN_0803f3fc(struct Boss* _) { return TRUE; }

extern const struct Collision gBlazinCollisions[];
struct Projectile* blazin_080402a4(struct Boss* p);

void blazinMode5(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 6) | 0xA200));
      SetDDP(&p->body, &gBlazinCollisions[1]);
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      (p->s).mode[2]++;
      break;
    case 2:
      SetDDP(&p->body, &gBlazinCollisions[5]);
      *(struct Projectile**)((u8*)p + 0xcc) = blazin_080402a4(p);
      PlaySound(0x70);
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      if ((p->s).work[3] == 0 && *(s32*)((u8*)p + 0xc4) == 0) {
        GotoMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 6) | 0xA200), 4, 0);
        (p->s).work[3] = 1;
      }
      UpdateMotionGraphic(&p->s);
      {
        struct Projectile** ep = (struct Projectile**)((u8*)p + 0xcc);
        if ((*ep)->s.mode[0] > 1) {
          *ep = NULL;
          (p->s).mode[2]++;
        }
      }
      break;
    case 4:
      SetMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 7) | 0xA200));
      (p->s).mode[2]++;
      // fallthrough
    case 5:
      UpdateMotionGraphic(&p->s);
      {
        u8 st = (p->s).motion.state;
        if (st == 3) {
          (p->s).mode[1] = st;
          (p->s).mode[2] = 0;
        }
      }
      break;
  }
}

bool8 nop_0803f538(struct Boss* _) { return TRUE; }

INCASM("asm/boss/blazin_p7.inc");

bool8 nop_0803f710(struct Boss* _) { return TRUE; }

INCASM("asm/boss/blazin_p8.inc");

bool8 FUN_0803f9a8(struct Boss* _) { return TRUE; }

void blazinMode8(struct Boss* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_0803f9c0(struct Boss* _) { return TRUE; }

INCASM("asm/boss/blazin_p10.inc");

bool8 FUN_0803fc70(struct Boss* _) { return TRUE; }

// 0x0803FC74
void blazinMode10(struct Boss* p) {
  register s32 z asm("r6");
  z = (p->s).mode[2];
  switch (z) {
    case 0: {
      u8* d0 = (u8*)p + 0xd0;
      if (*d0 == 1) {
        struct Projectile** slot;
        *d0 = z;
        slot = (struct Projectile**)((u8*)p + 0xc4);
        *slot = (struct Projectile*)z;
        *slot = createBlazinTail(&p->s, 2);
        *(u16*)((u8*)p + 0xc8) = z;
      }
      if (isSoundPlaying(0x48)) {
        StopSound(0x48);
      }
      if (isSoundPlaying(0x72)) {
        StopSound(0x72);
      }
      (p->s).work[3] = z;
      PlaySound(0x74);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if (*(u32*)((u8*)p + 0xcc) == 0) {
        break;
      }
      if (*(u32*)((u8*)p + 0xc4) != 0) {
        break;
      }
      if ((p->s).work[3] != 0) {
        break;
      }
      GotoMotion(&p->s, (motion_t)((*(u16*)((u8*)p + 0xc8) + 6) | 0xA200), 4, 0);
      UpdateMotionGraphic(&p->s);
      (p->s).work[3] = 1;
      break;
  }
  {
    register u32* c0 asm("r4");
    c0 = (u32*)((u8*)p + 0xc0);
    if (isKilled((struct Entity*)*c0)) {
      register u32* cc asm("r2");
      register struct Entity* e asm("r1");
      cc = (u32*)((u8*)p + 0xcc);
      e = (struct Entity*)*cc;
      if (e == NULL) {
        goto nullcase;
      }
      if (e->mode[0] <= 1) {
        return;
      }
      {
        register s32 zz asm("r0");
        register s32 three asm("r1");
        zz = 0;
        *cc = zz;
        *c0 = zz;
        three = 3;
        (p->s).mode[1] = three;
        (p->s).mode[2] = zz;
        goto tail;
      }
    nullcase:
      *c0 = (u32)e;
      (p->s).mode[1] = 3;
      (p->s).mode[2] = (u8)(u32)e;
    tail:
      (p->s).mode[3] = 0xFF;
    }
  }
}

bool8 FUN_0803fd58(struct Boss* _) { return TRUE; }

INCASM("asm/boss/blazin_p12_p1.inc");

#include "element.h"
#include "vfx.h"

extern const struct Coord gBlazinCoords[5];

bool8 blazin_0803fed8(struct Boss* p) {
  struct VFX** slot = (struct VFX**)&(p->props).raw[12];

  if (*slot == NULL && ((p->body).status & 1)) {
    *slot = ApplyElementEffect(9, &p->s, gBlazinCoords);
    if (*slot != NULL) {
      if ((*(u8*)((u8*)p + 0x97) & 0xf0) == 0x10) {
        (p->s).mode[1] = 10;
        (p->s).mode[2] = 0;
      } else {
        *slot = NULL;
      }
    }
  }
  return TRUE;
}

// 0x0803ff28
void FUN_0803ff28(struct Body* body, struct Coord* c, struct Coord* c2 UNUSED) {
  register const struct Collision* pr asm("r2") = (body->enemy)->processing;
  u8 k = pr->atkType;
  if (k == 3 || k == 0xE || k == 0xF) {
    struct Boss* q = (struct Boss*)body->parent;
    if (((q->body).status & BODY_STATUS_DEAD) || (q->body).hp == 0) {
      if (!(gStageRun.missionStatus & MISSION_FAIL)) {
        if ((q->s).coord.x < c->x) {
          (q->s).work[1] = 0xFF;
        } else {
          (q->s).work[1] = 0xFE;
        }
      }
    }
  }
  {
    const struct Collision* pr2 = (body->enemy)->processing;
    if ((body->processing)->kind != 2 && (body->processing)->layer != -1 &&
        (*(u32*)&pr2->atkType & 0x200FF) == 0x20002) {
      struct Boss* q = (struct Boss*)body->parent;
      if ((q->s).mode[1] != 0xB && (q->s).mode[1] != 5) {
        (q->s).mode[1] = 0xB, (q->s).mode[2] = 0;
      }
    }
  }
}

struct Enemy* FUN_0809c430(struct Entity* e, struct Coord* c);

bool8 FUN_0803ffc0(struct Boss* p) {
  struct Coord c;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  FUN_0809c430((struct Entity*)p, &c);
  return TRUE;
}

extern const s32 s32_ARRAY_080fee20[3];
struct Projectile* FUN_0809e55c(struct Entity* e, struct Coord* c, struct Coord* c2);

bool8 blazin_0803ffdc(struct Boss* p, u8 i) {
  struct Coord c[2];
  c[0].x = (p->s).coord.x;
  c[0].y = (p->s).coord.y - 0x2800;
  if (((p->s).flags & 0x10) == 0) {
    c[1].x = -s32_ARRAY_080fee20[i];
  } else {
    c[1].x = s32_ARRAY_080fee20[i];
  }
  {
    s32 gy = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    struct Coord* c2 = &c[1];
    c2->y = gy;
    {
      s32 t0 = c[0].x;
      c[1].x += t0;
    }
    FUN_0809e55c(&p->s, &c[0], c2);
  }
  return 1;
}

extern const u8 u8_ARRAY_080feda8[16];
extern const struct Coord Coord_ARRAY_080fedb8[13];
struct Projectile* FUN_0809e500(struct Entity* e, struct Coord* c, struct Coord* d);

// 0x08040044
bool8 blazin_08040044(struct Boss* p, u8 a1, u8 a2) {
  struct Coord c;
  struct Coord d;
  u8 ang;
  u8 a1b;
  a1b = a1;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  if (((p->s).flags & 0x10) == 0) {
    {
      u32 t = (u32)u8_ARRAY_080feda8[a2] << 24;
      t += 0xC0000000;
      ang = t >> 24;
    }
    if (a2 <= 6) {
      ang = ang + a1;
    } else {
      ang = ang - a1;
    }
    c.x = Coord_ARRAY_080fedb8[a2].x + c.x;
  } else {
    ang = 0x40 - u8_ARRAY_080feda8[a2];
    if (a2 <= 6) {
      ang = ang - a1;
    } else {
      ang = ang + a1b;
    }
    c.x = c.x - Coord_ARRAY_080fedb8[a2].x;
  }
  c.y = Coord_ARRAY_080fedb8[a2].y + c.y;
  d.x = gSineTable[ang];
  d.y = gSineTable[(u8)(ang + 0x40)];
  FUN_0809e500(&p->s, &c, &d);
  return 1;
}


extern const u8 BlazinFireballAngles[8];
struct Projectile* _createBlazinEXFireBall(struct Entity* e, struct Coord* c, struct Coord* d, u8 angle);

// 0x08040110
bool8 createBlazinEXFireBall(struct Boss* p, u8 a1, u8 a2, s32 a3) {
  struct Coord dir;
  struct Coord c;
  u8 ang;
  struct Projectile* q;
  if (((p->s).flags & 0x10) == 0) {
    const u8* tp = &BlazinFireballAngles[a1];
    s32 m13 = a2 * 13;
    ang = m13 + *tp;
    asm("" : "+r"(ang));
  } else {
    const u8* tp2 = &BlazinFireballAngles[a1];
    s32 m13b = a2 * 13;
    ang = *tp2 - m13b;
    asm("" : "+r"(ang));
  }
  dir.x = gSineTable[ang];
  dir.y = -gSineTable[(u8)(ang + 0x40)];
  c.x = 0;
  c.y = -0x1C00;
  c.x += ((dir.x * 3) << 11) >> 8;
  c.y += ((dir.y * 3) << 11) >> 8;
  c.x = (p->s).coord.x + c.x;
  c.y = (p->s).coord.y + c.y;
  q = _createBlazinEXFireBall(&p->s, &c, &dir, ang + 0x80);
  if (q != NULL) {
    *(s32*)((u8*)q + 0xbc) = a3;
  }
  return 1;
}

INCASM("asm/boss/blazin_p12_p2_p1c.inc");

struct Projectile* blazin_0809e620(struct Entity* e, struct Coord* c, struct Coord* d);

// One scheduling slot apart: retail hoists the &c arg add into the coord.y
// load shadow; agbcc orders the pool load first (and swaps r3/r4 with the
// plain member store). Same 41 instructions either way.
NON_MATCH struct Projectile* blazin_080402a4(struct Boss* p) {
#if MODERN
  struct Coord v;
  struct Coord c;
  u32 angle = 0x54;
  if (!((p->s).flags & X_FLIP)) {
    angle = 0xAC;
  }
  v.x = gSineTable[angle];
  v.y = -gSineTable[(u8)(angle + 0x40)];
  c.x = (p->s).coord.x;
  ((s32*)&c)[1] = (p->s).coord.y - PIXEL(8);
  return blazin_0809e620(&p->s, &c, &v);
#else
  INCCODE("asm/boss/blazin_402a4.inc");
#endif
}

extern const u16 UnkBlaizinModes_080fed5a[5];

s32 blazin_080402fc(s32 def0, s32 v0, s32 mode) {
  register s32 def asm("r0") = def0;
  register s32 v asm("r4") = v0;
  s32 i;
  register const u16* base asm("r5");
  register const u16* t asm("r3");
  if (mode == 1) {
    i = 0;
    base = UnkBlaizinModes_080fed5a;
    t = base;
    for (; i <= 4; t++, i++) {
      if (*t == v) {
        return base[(i + 1) % 5];
      }
    }
  } else {
    i = 0;
    base = UnkBlaizinModes_080fed5a;
    t = base;
    for (; i <= 3; t++, i++) {
      if (*t == v) {
        return base[(i + 1) % 4];
      }
    }
  }
  return def;
}

s32 howFarBlazin(struct Boss* p) {
  s32 zx = (pZero2->s).coord.x;
  s32 sx = (p->s).coord.x;
  s32 d = zx - sx;
  if (d <= 0) {
    d = sx - zx;
  }
  if (d <= 0x4eff) {
    return 0;
  }
  if (d <= 0x8eff) {
    return 1;
  }
  return 2;
}


// 0x080403a0
struct Entity* blazin_080403a0(struct Boss* p, u32 n) {
  if (n == 0) {
    return *(struct Entity**)&(p->props).raw[0x20];
  } else if (n == 1) {
    return *(struct Entity**)&(p->props).raw[0x24];
  } else if (n == 2) {
    return *(struct Entity**)&(p->props).raw[0x28];
  } else {
    return *(struct Entity**)&(p->props).raw[0x2C];
  }
}

// 0x080403c4
static void setBlazinDirection(struct Entity* p) {
  struct Entity* z = (struct Entity*)pZero2;
  if ((z->coord).x > (p->coord).x) {
    if (!(p->flags & X_FLIP)) {
      (p->spr).xflip = TRUE, (p->spr).oam.xflip = TRUE;
      p->flags |= X_FLIP;
    }
  } else {
    if (p->flags & X_FLIP) {
      (p->spr).xflip = FALSE, (p->spr).oam.xflip = FALSE;
      p->flags &= ~X_FLIP;
    }
  }
}

// --------------------------------------------

// 0x08361c68
const struct Collision gBlazinCollisions[15] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, -0x1200, 0x2400, 0x2600},
    },

    // --------------------------------------------

    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1100, 0x2200, 0x2400},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      range : {0x0000, -0x1200, 0x2400, 0x2600},
    },

    // --------------------------------------------

    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1700, 0x1A00, 0x2A00},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      range : {0x0000, -0x1800, 0x1C00, 0x2D00},
    },

    // --------------------------------------------

    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x800, -0xD00, 0x2F00, 0x1900},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      range : {-0x900, -0xE00, 0x3100, 0x1B00},
    },

    // --------------------------------------------

    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x1500, 0x2200, 0x2D00},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      range : {0x0000, -0x1600, 0x2400, 0x2F00},
    },

    // --------------------------------------------

    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x300, -0xE00, 0x2500, 0x1C00},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      range : {-0x400, -0xF00, 0x2700, 0x1E00},
    },

    // --------------------------------------------

    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 3,
      layer : 0x00000001,
      range : {0x0100, -0x1500, 0x1E00, 0x2E00},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 2,
      range : {0x0200, -0x1600, 0x2000, 0x3000},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x1B00, -0x1B00, 0x1A00, 0x0D00},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x07,
      remaining : 0,
      range : {-0x1C00, -0x1C00, 0x1C00, 0x0F00},
    },
};

// 0x08361dd0
const struct Coord gBlazinCoords[5] = {
    {PIXEL(0), -PIXEL(32)}, {PIXEL(12), -PIXEL(32)}, {PIXEL(12), -PIXEL(32)}, {PIXEL(18), -PIXEL(32)}, {PIXEL(18), -PIXEL(32)},
};
