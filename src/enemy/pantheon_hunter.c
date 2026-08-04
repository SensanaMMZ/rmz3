#include "collision.h"
#include "enemy.h"
#include "story.h"
#include "global.h"
#include "sound.h"
#include "projectile.h"
#include "metatile.h"
#include "motion.h"
#include "vfx.h"
#include "mission.h"

struct PantheonHunterObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[8];
  bool8 isRight;  // 0xBC
  u32 unk_c0;
};
static_assert(sizeof(struct PantheonHunterObject) == sizeof(struct Enemy));

static const EnemyFunc sUpdates[13];
static const EnemyFunc sDeads[3];
static const struct Collision sCollisions[];
static const struct SlashedEnemy sSlashedEnemies[4];

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void PantheonHunter_Init(struct Enemy* p);
static void PantheonHunter_Update(struct Enemy* p);
void PantheonHunter_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonHunterRoutine = {
    [ENTITY_INIT] =      PantheonHunter_Init,
    [ENTITY_UPDATE] =    PantheonHunter_Update,
    [ENTITY_DIE] =       PantheonHunter_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreatePantheonHunter(struct Coord* c, u8 r1, u8 r2) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_HUNTER);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = r1;
    p->work[1] = r2;
  }
  return p;
}

NAKED static void PantheonHunter_Init(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	ldr r1, _08064760 @ =gEnemyFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	movs r4, #0\n\
	orrs r0, r1\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	movs r1, #0x98\n\
	lsls r1, r1, #5\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	adds r0, r6, #0\n\
	bl UpdateMotionGraphic\n\
	ldr r0, _08064764 @ =gSystemSavedataManager\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #8\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08064770\n\
	ldr r0, _08064768 @ =gCurStory\n\
	ldrb r1, [r0, #4]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	lsls r0, r0, #0x18\n\
	lsrs r5, r0, #0x18\n\
	cmp r5, #0\n\
	bne _08064770\n\
	ldrb r0, [r6, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0806476C @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0xa\n\
	b _08064788\n\
	.align 2, 0\n\
_08064760: .4byte gEnemyFnTable\n\
_08064764: .4byte gSystemSavedataManager\n\
_08064768: .4byte gCurStory\n\
_0806476C: .4byte sCollisions\n\
_08064770:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #4\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _080647B0 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #6\n\
_08064788:\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	str r5, [r4, #0x24]\n\
	ldr r0, _080647B4 @ =onCollision\n\
	str r0, [r4, #0x24]\n\
	movs r0, #0\n\
	str r0, [r6, #0x60]\n\
	str r0, [r6, #0x5c]\n\
	ldrb r0, [r6, #0x10]\n\
	cmp r0, #2\n\
	bne _080647B8\n\
	movs r0, #0xc\n\
	strb r0, [r6, #0xd]\n\
	ldrb r1, [r6, #0x11]\n\
	adds r0, r6, #0\n\
	adds r0, #0xbd\n\
	strb r1, [r0]\n\
	adds r2, r0, #0\n\
	b _080647FA\n\
	.align 2, 0\n\
_080647B0: .4byte sCollisions\n\
_080647B4: .4byte onCollision\n\
_080647B8:\n\
	cmp r0, #0\n\
	beq _080647CA\n\
	ldr r0, [r6, #0x54]\n\
	ldr r1, [r6, #0x58]\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _080647D4\n\
_080647CA:\n\
	ldr r0, [r6, #0x54]\n\
	ldr r1, [r6, #0x58]\n\
	bl FUN_08009f6c\n\
	str r0, [r6, #0x58]\n\
_080647D4:\n\
	movs r0, #6\n\
	strb r0, [r6, #0xd]\n\
	ldr r0, _080647EC @ =pZero2\n\
	ldr r0, [r0]\n\
	ldr r1, [r6, #0x54]\n\
	ldr r0, [r0, #0x54]\n\
	cmp r1, r0\n\
	bge _080647F0\n\
	adds r1, r6, #0\n\
	adds r1, #0xbd\n\
	movs r0, #1\n\
	b _080647F6\n\
	.align 2, 0\n\
_080647EC: .4byte pZero2\n\
_080647F0:\n\
	adds r1, r6, #0\n\
	adds r1, #0xbd\n\
	movs r0, #0\n\
_080647F6:\n\
	strb r0, [r1]\n\
	adds r2, r1, #0\n\
_080647FA:\n\
	adds r1, r6, #0\n\
	adds r1, #0xb4\n\
	ldr r0, [r6, #0x54]\n\
	str r0, [r1]\n\
	adds r1, #4\n\
	ldr r0, [r6, #0x58]\n\
	str r0, [r1]\n\
	adds r0, r6, #0\n\
	adds r0, #0xc0\n\
	movs r1, #0\n\
	str r1, [r0]\n\
	subs r0, #2\n\
	strb r1, [r0]\n\
	ldrb r2, [r2]\n\
	cmp r2, #0\n\
	beq _08064822\n\
	ldrb r0, [r6, #0xa]\n\
	movs r1, #0x10\n\
	orrs r0, r1\n\
	b _08064828\n\
_08064822:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
_08064828:\n\
	strb r0, [r6, #0xa]\n\
	movs r1, #1\n\
	ands r1, r2\n\
	adds r0, r6, #0\n\
	adds r0, #0x4c\n\
	strb r1, [r0]\n\
	adds r3, r6, #0\n\
	adds r3, #0x4a\n\
	lsls r1, r1, #4\n\
	ldrb r2, [r3]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strb r0, [r3]\n\
	adds r0, r6, #0\n\
	bl PantheonHunter_Update\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}

// --------------------------------------------

void FUN_08064c38(struct Enemy* p);
void nop_08064ca8(struct Enemy* p);
void phunter_08064cac(struct Enemy* p);
void FUN_08064e0c(struct Enemy* p);
void nop_08064e34(struct Enemy* p);
void FUN_08064e38(struct Enemy* p);
void FUN_08064e7c(struct Enemy* p);
void phunterRaiseArm(struct Enemy* p);
void phunterShotBuster(struct Enemy* p);
void FUN_08065104(struct Enemy* p);
void phunter_080651c0(struct Enemy* p);
void phunter_08065218(struct Enemy* p);
void phunter_080652e8(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates[13] = {
    FUN_08064c38,
    nop_08064ca8,
    phunter_08064cac,
    FUN_08064e0c,
    nop_08064e34,
    FUN_08064e38,
    FUN_08064e7c,
    phunterRaiseArm,
    phunterShotBuster,
    FUN_08065104,
    phunter_080651c0,
    phunter_08065218,
    phunter_080652e8,
};
// clang-format on

NAKED static void PantheonHunter_Update(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	adds r5, r0, #0\n\
	ldr r6, _08064888 @ =gCurStory\n\
	ldrb r1, [r6, #8]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	lsls r0, r0, #0x18\n\
	lsrs r4, r0, #0x18\n\
	cmp r4, #0\n\
	beq _0806488C\n\
	ldrb r1, [r5, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r2, #0\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r0, r5, #0\n\
	adds r0, #0x8c\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	b _080648D6\n\
	.align 2, 0\n\
_08064888: .4byte gCurStory\n\
_0806488C:\n\
	ldrb r0, [r5, #0x10]\n\
	cmp r0, #2\n\
	bne _08064904\n\
	ldr r0, _080648F4 @ =gStageRun+232\n\
	adds r1, r5, #0\n\
	adds r1, #0x54\n\
	bl CalcFromCamera\n\
	movs r1, #0x80\n\
	lsls r1, r1, #7\n\
	cmp r0, r1\n\
	bhi _080648BC\n\
	ldrb r1, [r6, #4]\n\
	movs r0, #0x10\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08064904\n\
	ldr r0, _080648F8 @ =gSystemSavedataManager\n\
	ldr r1, [r0, #0x40]\n\
	ldr r0, _080648FC @ =0x000032DA\n\
	cmp r1, r0\n\
	beq _08064904\n\
	cmp r1, #0\n\
	beq _08064904\n\
_080648BC:\n\
	ldrb r1, [r5, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r5, #0xa]\n\
	adds r0, r5, #0\n\
	adds r0, #0x8c\n\
	str r4, [r0]\n\
	adds r0, #4\n\
	str r4, [r0]\n\
	adds r0, #4\n\
	strb r4, [r0]\n\
_080648D6:\n\
	ldrb r1, [r5, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r5, #0xa]\n\
	ldr r1, _08064900 @ =gEnemyFnTable\n\
	ldrb r0, [r5, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r5, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	str r0, [r5, #0x14]\n\
	b _08064AC2\n\
	.align 2, 0\n\
_080648F4: .4byte gStageRun+232\n\
_080648F8: .4byte gSystemSavedataManager\n\
_080648FC: .4byte 0x000032DA\n\
_08064900: .4byte gEnemyFnTable\n\
_08064904:\n\
	adds r0, r5, #0\n\
	bl phunter_08064c10\n\
	ldrb r0, [r5, #0xd]\n\
	cmp r0, #2\n\
	bne _08064918\n\
	adds r0, r5, #0\n\
	bl phunter_08064cac\n\
	b _08064AC2\n\
_08064918:\n\
	adds r7, r5, #0\n\
	adds r7, #0x8c\n\
	ldr r0, [r7]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	bne _08064942\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	movs r6, #0x80\n\
	lsls r6, r6, #4\n\
	adds r1, r1, r6\n\
	bl FUN_080098a4\n\
	movs r1, #0x10\n\
	ands r1, r0\n\
	lsls r1, r1, #0x10\n\
	lsrs r4, r1, #0x10\n\
	cmp r4, #0\n\
	beq _08064960\n\
_08064942:\n\
	ldr r1, _0806495C @ =gEnemyFnTable\n\
	ldrb r0, [r5, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #2\n\
	str r1, [r5, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r5, #0x14]\n\
	adds r0, r5, #0\n\
	bl PantheonHunter_Die\n\
	b _08064AC2\n\
	.align 2, 0\n\
_0806495C: .4byte gEnemyFnTable\n\
_08064960:\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	movs r2, #0x80\n\
	lsls r2, r2, #4\n\
	adds r1, r1, r2\n\
	bl FUN_0800a40c\n\
	cmp r0, #0\n\
	beq _08064986\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	adds r1, r1, r6\n\
	bl FUN_0800a40c\n\
	ldr r1, [r5, #0x54]\n\
	adds r1, r1, r0\n\
	str r1, [r5, #0x54]\n\
	strb r4, [r5, #0xd]\n\
	strb r4, [r5, #0xe]\n\
_08064986:\n\
	adds r0, r5, #0\n\
	adds r0, #0xc0\n\
	ldr r4, [r0]\n\
	adds r6, r0, #0\n\
	cmp r4, #0\n\
	bne _080649B6\n\
	ldr r0, [r7]\n\
	movs r1, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080649B0\n\
	ldr r2, _08064A30 @ =Coord_08365c84\n\
	movs r0, #0\n\
	adds r1, r5, #0\n\
	bl ApplyElementEffect\n\
	str r0, [r6]\n\
	cmp r0, #0\n\
	beq _08064A40\n\
	str r4, [r5, #0x60]\n\
	str r4, [r5, #0x5c]\n\
_080649B0:\n\
	ldr r0, [r6]\n\
	cmp r0, #0\n\
	beq _08064A40\n\
_080649B6:\n\
	ldr r1, _08064A34 @ =0x00001303\n\
	adds r0, r5, #0\n\
	bl SetMotion\n\
	adds r0, r5, #0\n\
	bl UpdateMotionGraphic\n\
	adds r4, r5, #0\n\
	adds r4, #0x74\n\
	ldr r1, _08064A38 @ =sCollisions+24\n\
	adds r0, r4, #0\n\
	bl SetDDP\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	adds r1, #1\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	adds r7, r4, #0\n\
	cmp r0, #0\n\
	bne _08064A06\n\
	ldr r0, [r5, #0x60]\n\
	adds r0, #0x40\n\
	str r0, [r5, #0x60]\n\
	movs r1, #0xe0\n\
	lsls r1, r1, #3\n\
	cmp r0, r1\n\
	ble _080649F2\n\
	str r1, [r5, #0x60]\n\
_080649F2:\n\
	ldr r1, [r5, #0x58]\n\
	ldr r0, [r5, #0x60]\n\
	adds r1, r1, r0\n\
	str r1, [r5, #0x58]\n\
	ldr r0, [r5, #0x54]\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _08064A10\n\
_08064A06:\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	bl FUN_08009f6c\n\
	str r0, [r5, #0x58]\n\
_08064A10:\n\
	ldr r0, [r6]\n\
	bl isKilled\n\
	cmp r0, #0\n\
	beq _08064AC2\n\
	movs r4, #0\n\
	str r4, [r6]\n\
	ldr r1, _08064A3C @ =sCollisions\n\
	adds r0, r7, #0\n\
	bl SetDDP\n\
	strb r4, [r5, #0xd]\n\
	movs r0, #1\n\
	strb r0, [r5, #0xe]\n\
	b _08064AC2\n\
	.align 2, 0\n\
_08064A30: .4byte Coord_08365c84\n\
_08064A34: .4byte 0x00001303\n\
_08064A38: .4byte sCollisions+24\n\
_08064A3C: .4byte sCollisions\n\
_08064A40:\n\
	adds r0, r5, #0\n\
	bl IsFrozen\n\
	cmp r0, #0\n\
	beq _08064AAC\n\
	movs r1, #0x98\n\
	lsls r1, r1, #5\n\
	adds r0, r5, #0\n\
	bl SetMotion\n\
	adds r0, r5, #0\n\
	bl UpdateMotionGraphic\n\
	adds r0, r5, #0\n\
	adds r0, #0x74\n\
	ldr r1, _08064AA8 @ =sCollisions\n\
	bl SetDDP\n\
	movs r0, #0\n\
	str r0, [r6]\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	bne _08064A7C\n\
	ldrb r0, [r5, #0x10]\n\
	cmp r0, #1\n\
	bne _08064A9C\n\
_08064A7C:\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	bl FUN_08009f6c\n\
	adds r4, r0, #0\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	bl FUN_0800a05c\n\
	cmp r4, r0\n\
	beq _08064A9C\n\
	ldr r0, [r5, #0x54]\n\
	ldr r1, [r5, #0x58]\n\
	bl FUN_08009f6c\n\
	str r0, [r5, #0x58]\n\
_08064A9C:\n\
	movs r1, #0\n\
	movs r0, #6\n\
	strb r0, [r5, #0xd]\n\
	strb r1, [r5, #0xe]\n\
	b _08064AC2\n\
	.align 2, 0\n\
_08064AA8: .4byte sCollisions\n\
_08064AAC:\n\
	adds r0, r5, #0\n\
	bl phunter_08064bc8\n\
	ldr r0, _08064AC8 @ =sUpdates\n\
	ldrb r1, [r5, #0xd]\n\
	lsls r1, r1, #2\n\
	adds r1, r1, r0\n\
	ldr r1, [r1]\n\
	adds r0, r5, #0\n\
	bl _call_via_r1\n\
_08064AC2:\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08064AC8: .4byte sUpdates\n\
 .syntax divided\n");
}

// --------------------------------------------

void explodePHunter(struct Enemy* p);
void slashPHunter(struct Enemy* p);
static void FUN_080656cc(struct Entity* p);

static const EnemyFunc sDeads[3] = {
    (EnemyFunc)explodePHunter,
    (EnemyFunc)slashPHunter,
    (EnemyFunc)FUN_080656cc,
};

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);

// 0x08064ACC
void PantheonHunter_Die(struct Enemy* p) {
  struct Coord c;
  register u8 m asm("r5");
  m = (p->s).mode[2];
  if (m == 0) {
    register s32* bp asm("r5");
    register s32 t0 asm("r0");
    s32 msk;
    t0 = FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x800);
    t0 <<= 16;
    t0 = (s32)((u32)t0 >> 16);
    msk = 0x10;
    t0 &= msk;
    if (t0 || (*((u8*)p + 0xbe) != 0)) {
      (p->s).mode[1] = m;
      bp = (s32*)((u8*)p + 0x8c);
    } else {
      register s32* b0 asm("r1");
      s32 sv;
      b0 = (s32*)((u8*)p + 0x8c);
      sv = *b0 & 0x10000;
      bp = b0;
      if (sv != 0) {
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y - 0x1400;
        FUN_080b2b40(0, &c, 0x200, *((u8*)p + 0xbc));
        (p->s).mode[1] = 1;
      } else {
        (p->s).mode[1] = sv;
      }
    }
    {
      s32 z = 0;
      *bp = z;
      *(s32*)((u8*)p + 0x90) = z;
      *((u8*)p + 0x94) = z;
    }
    (p->s).flags &= ~4;
    (p->s).mode[2]++;
  }
  if (gCurStory.s.gameflags[4] & 0x40) {
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
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (sDeads[(p->s).mode[1]])(p);
  }
}

void phunter_08064bc8(struct Enemy* p) {
  if ((p->s).mode[1] > 1 && (p->s).mode[1] != 12) {
    if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + PIXEL(8))) {
      (p->s).coord.y -= PIXEL(16);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    } else {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
  }
}

void phunter_08064c10(struct Enemy* p) {
  if ((p->s).mode[1] == 2) return;
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

void FUN_08064c38(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1300);
    (p->s).d.y = 0;
    (p->s).d.x = 0;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  (p->s).coord.y += (p->s).d.y;
  {
    metatile_attr_t r = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (r != 0x800F && r != 0) {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1] = 5;
      (p->s).mode[2] = 0;
      (p->s).mode[3] = 6;
    }
  }
}

void nop_08064ca8(struct Enemy* p) {}

#include "zero.h"
#include "metatile.h"

void phunter_08064cac(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1303);
    {
      register struct Zero** zp asm("r4");
      register s32 dx asm("r1");
      register s32 dy asm("r0");
      register s32 s1 asm("r6");
      struct Zero* z;
      s32 s2, dist;
      zp = &pZero2;
      z = *zp;
      dx = (p->s).coord.x;
      dx -= (z->s).coord.x;
      (p->s).d.x = dx;
      dy = (p->s).coord.y - (z->s).coord.y + -0x1800;
      (p->s).d.y = dy;
      dx >>= 8;
      s1 = dx;
      s1 = s1 * dx;
      dy >>= 8;
      s2 = dy;
      s2 = s2 * dy;
      s1 += s2;
      dist = (u16)Sqrt(s1);
      if (dist != 0) {
        s32 nx = (p->s).d.x / dist;
        s32 ny;
        (p->s).d.x = nx;
        ny = (p->s).d.y / dist;
        (p->s).d.x = (nx * 3) << 1;
        (p->s).d.y = (ny * 3) << 1;
      } else {
        if (((*zp)->s).flags & 0x10) {
          (p->s).d.x = 0x600;
        } else {
          (p->s).d.x = -0x600;
        }
        (p->s).d.y = 0;
      }
    }
    if ((p->s).d.x > 0) {
      s32 z2 = 0;
      (p->s).flags &= 0xEF;
      (p->s).spr.xflip = z2;
      {
        u8* oa = (u8*)p + 0x4a;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        *oa = m11;
      }
    } else {
      s32 o = 1;
      (p->s).flags |= 0x10;
      (p->s).spr.xflip = o;
      {
        u8* oa = (u8*)p + 0x4a;
        s32 c16 = 0x10;
        s32 ov, m11;
        asm("" : "+r"(c16));
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | c16;
      }
    }
    *((u8*)p + 0xbe) = 1;
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 x = (p->s).coord.x;
    s32 dx = (p->s).d.x;
    s32 y, dy;
    x += dx;
    (p->s).coord.x = x;
    y = (p->s).coord.y;
    dy = (p->s).d.y;
    y += dy;
    (p->s).coord.y = y;
    (p->s).d.y = dy + 0x40;
    if (FUN_080098a4(x + dx, y) != 0) {
      goto die2;
    }
    if (FUN_080098a4((p->s).coord.x + (p->s).d.x, (p->s).coord.y - 0x1800) != 0) {
    die2:
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      PantheonHunter_Die(p);
    }
  }
}

void FUN_08064e0c(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x13, 3));
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
}

void nop_08064e34(struct Enemy* p) {}

INCASM("asm/enemy/pantheon_hunter_p3_a.inc");

// 0x08064e38
void FUN_08064e38(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, 0x1300);
    (p->s).work[2] = 0x1E;
    (p->s).d.y = m;
    (p->s).d.x = m;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).work[2]--;
  if ((p->s).work[2] == 0xFF) {
    (p->s).mode[1] = (p->s).mode[3];
    (p->s).mode[2] = 0;
  }
}

extern const struct Coord Coord_08365c8c;

// 0x08064E7C
void FUN_08064e7c(struct Enemy* p) {
  register s32 md asm("r0");
  register s32 zz asm("r1");
  register s32 cx asm("r2");
  if ((p->s).work[0] == 1) {
    (p->s).mode[1] = 0xb;
    phunter_08065218(p);
    return;
  }
  if ((p->s).mode[2] == 0) {
    register u8* fp asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, 0x1309);
    {
      register u8* q asm("r0");
      q = (u8*)p + 0xbd;
      v = *q;
      fp = q;
      if (v != 0) {
        md = 0x80;
      } else {
        md = 0x80;
        md = -md;
      }
      (p->s).d.x = md;
    }
    {
      register s32 f2 asm("r2");
      f2 = *fp;
      if (f2 != 0) {
        register s32 h asm("r1");
        register s32 g asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0x10;
        g |= h;
        (p->s).flags = g;
      } else {
        register u8 h2 asm("r1");
        register u8 g2 asm("r0");
        h2 = (p->s).flags;
        asm("" : "+r"(h2));
        g2 = 0xEF;
        g2 &= h2;
        (p->s).flags = g2;
      }
      {
        register s32 xv asm("r1");
        register u8* oa asm("r3");
        s32 sh4, ov, m11;
        xv = 1;
        xv &= f2;
        *((u8*)p + 0x4c) = xv;
        oa = (u8*)p + 0x4a;
        sh4 = xv << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        *oa = m11 | sh4;
      }
    }
    (p->s).mode[2]++;
  } else {
    (p->s).coord.x += (p->s).d.x;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 h1 asm("r0");
    h1 = (u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + (0x80 << 4));
    if (h1 == 0) {
      (p->s).mode[1] = h1;
      (p->s).mode[2] = h1;
      return;
    }
  }
  {
    register s32 tx asm("r5");
    register s32 ty asm("r6");
    register s32 g asm("r0");
    s32 r7v;
    g = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).coord.y = g;
    {
      register const s32* tb asm("r2");
      register s32 o asm("r1");
      tb = (const s32*)&Coord_08365c8c;
      asm("" : "+r"(tb));
      o = *((u8*)p + 0xbd);
      o <<= 2;
      o += (s32)tb;
      {
        register s32 cx2 asm("r2");
        cx2 = (p->s).coord.x;
        o = *(const s32*)o;
        tx = cx2 + o;
      }
      {
        register s32 lo asm("r1");
        register s32 k3 asm("r3");
        register s32 hi asm("r2");
        k3 = -0x800;
        asm("" : "+r"(k3));
        lo = g + k3;
        hi = 0xa0 << 4;
        ty = g + hi;
        r7v = (u16)FUN_080098a4(tx, lo);
        if (r7v == 0) {
          if ((u16)FUN_080098a4(tx, ty) != 0) {
            goto ok;
          }
        }
      }
    }
    zz = 0;
    md = 9;
    goto setmode;
  ok:
    {
      s32 fl;
      /* cx below is shared with the pZero2 block */
      {
        register s32 fv2 asm("r1");
        register s32 k16 asm("r0");
        fv2 = (p->s).flags;
        k16 = 0x10;
        k16 &= fv2;
        fl = (u8)k16;
      }
      if (fl != 0) {
        register s32 lim asm("r0");
        register s32 k asm("r3");
        lim = *(s32*)((u8*)p + 0xb4);
        k = 0xa0 << 6;
        asm("" : "+r"(k));
        lim += k;
        cx = (p->s).coord.x;
        if (cx > lim) {
          (p->s).mode[1] = 9;
          (p->s).mode[2] = r7v;
          return;
        }
      } else {
        register s32 lim2 asm("r0");
        lim2 = *(s32*)((u8*)p + 0xb4) + -0x2800;
        cx = (p->s).coord.x;
        if (cx < lim2) {
          (p->s).mode[1] = 9;
          (p->s).mode[2] = fl;
          return;
        }
      }
    }
  }
  {
    register struct EntityHeader* hp asm("r0");
    register s32 idx asm("r3");
    s32 rem;
    hp = gProjectileHeaderPtr;
    idx = 0xa;
    asm volatile("ldrsh %0, [%1, %2]" : "=l"(rem) : "l"(hp), "l"(idx));
    if (rem <= 6) {
      return;
    }
  }
  {
    register s32 sgn asm("r6");
    register struct Zero* z asm("r5");
    register s32 zx asm("r3");
    sgn = 0;
    z = pZero2;
    zx = (z->s).coord.x;
    if (zx <= cx) {
      sgn = 1;
    }
    {
      register s32 fv asm("r0");
      register s32 one asm("r1");
      {
        register s32 fl0 asm("r1");
        fl0 = (p->s).flags;
        asm("" : "+r"(fl0));
        fv = fl0 << 24;
      }
      fv = (u32)fv >> 28;
      one = 1;
      fv &= one;
      if (sgn == fv) {
        return;
      }
    }
    {
      register s32 d asm("r0");
      register s32 lim asm("r1");
      d = zx - cx;
      lim = 0xdc << 7;
      d += lim;
      lim = 0xdc << 8;
      if ((u32)d > (u32)lim) {
        return;
      }
      d = (z->s).coord.y;
      lim = (p->s).coord.y;
      d -= lim;
      lim = 0xa0 << 7;
      d += lim;
      lim = 0xa0 << 8;
      if ((u32)d > (u32)lim) {
        return;
      }
    }
  }
  {
    register s32 mv asm("r0");
    mv = (p->s).mode[1];
    zz = 0;
    (p->s).mode[3] = mv;
  }
  md = 7;
setmode:
  (p->s).mode[1] = md;
  (p->s).mode[2] = zz;
}


// 0x08065018
void phunterRaiseArm(struct Enemy* p) {
  u8 m = (p->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, 0x1301);
    (p->s).work[2] = 0x1E;
    (p->s).d.x = m;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).work[2]--;
  if ((p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/pantheon_hunter_p3_b_2_x_m.inc");

// 0x0806505c
void phunterShotBuster(struct Enemy* p) {
  struct Coord c;
  struct Projectile* q;
  u8 m = (p->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, 0x1302);
    (p->s).work[2] = m;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  switch ((p->s).work[2]) {
    case 0:
    case 5:
    case 10:
      c.y = (p->s).coord.y - 0x1200;
      if ((p->s).flags & X_FLIP) {
        c.x = (p->s).coord.x + 0x1B00;
        q = CreateLemon(&c, 0x240, 0x80);
      } else {
        c.x = (p->s).coord.x - 0x1B00;
        q = CreateLemon(&c, 0x240, 0);
      }
      if (q != NULL) {
        PlaySound(0x2C);
      }
      break;
    case 0x30:
      (p->s).mode[1] = 5;
      (p->s).mode[2] = 0;
      break;
  }
  (p->s).work[2]++;
}

void FUN_08064e7c(struct Enemy* p);

// 0x08065104
void FUN_08065104(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1300);
    (p->s).work[2] = 0x1E;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  if (gProjectileHeaderPtr->remaining > 6) {
    s32 side = 0;
    struct Zero* z = pZero2;
    s32 zx = (z->s).coord.x;
    s32 px = (p->s).coord.x;
    if (zx <= px) {
      side = 1;
    }
    if (side == (((p->s).flags >> 4) & 1)) goto tick;
    if ((u32)(zx - px + 0x6E00) > 0xDC00) goto tick;
    if ((u32)((z->s).coord.y - (p->s).coord.y + 0x5000) > 0xA000) goto tick;
    (p->s).mode[3] = (p->s).mode[1];
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
    return;
  }
tick:
  if ((u8)--(p->s).work[2] == 0xFF) {
    u8* f;
    u8 v;
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
    v = 0;
    f = (u8*)p + 0xbd;
    if (*f == 0) {
      v = 1;
    }
    *f = v;
    FUN_08064e7c(p);
  }
}

// 0x080651c0
void phunter_080651c0(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1300);
    (p->s).unk_coord.x = (p->s).d.x / 32;
    (p->s).work[2] = 0x1F;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).d.x -= (p->s).unk_coord.x;
  (p->s).work[2]--;
  if ((p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

// 0x08065218
void phunter_08065218(struct Enemy* p) {
  register s32 m asm("r5");
  register s32 v asm("r2");
  register s32 one asm("r6");
  m = (p->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, 0x1300);
    (p->s).d.y = m;
    (p->s).d.x = m;
    (p->s).mode[2]++;
  }
  UpdateMotionGraphic(&p->s);
  v = 0;
  if ((p->s).coord.x < (pZero2->s).coord.x) {
    v = 1;
  }
  if (v != 0) {
    (p->s).flags |= X_FLIP;
  } else {
    (p->s).flags &= ~X_FLIP;
  }
  one = 1;
  {
    register s32 xf asm("r1");
    u8* oa;
    s32 sh4, ov, m11;
    xf = one;
    xf &= v;
    (p->s).spr.xflip = xf;
    oa = (u8*)p + 0x4a;
    sh4 = xf << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh4;
  }
  if (gProjectileHeaderPtr->remaining > 6) {
    register s32 side asm("r5");
    struct Zero* z;
    s32 zx;
    s32 px;
    side = 0;
    z = pZero2;
    zx = (z->s).coord.x;
    px = (p->s).coord.x;
    if (zx <= px) {
      side = 1;
    }
    if (side == (s32)(((p->s).flags >> 4) & one)) {
      return;
    }
    if ((u32)(zx - px + 0x6E00) > 0xDC00) {
      return;
    }
    if ((u32)((z->s).coord.y - (p->s).coord.y + 0x5000) > 0xA000) {
      return;
    }
    (p->s).mode[3] = (p->s).mode[1];
    (p->s).mode[1] = 7;
    (p->s).mode[2] = 0;
  }
}

// 0x080652e8
void phunter_080652e8(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    if (p->props[9] != 0) {
      (p->s).d.x = 0x80;
    } else {
      (p->s).d.x = -0x80;
    }
    (p->s).d.y = -0x300;
    (p->s).mode[2]++;
  }
  SetMotion(&p->s, 0x1309);
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    *(s32*)&p->props[4] = (p->s).coord.y;
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/pantheon_hunter_p3_b_2_y_q.inc");

struct VFX* CreateGhost18(struct Coord* c, u8 r1, bool8 isRight, u8 r3);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x08065528
void slashPHunter(struct Enemy* p) {
  register u8* rp asm("r4");
  if ((p->s).mode[3] == 0) {
    SetMotion(&p->s, 0x1304);
    if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + (0x80 << 4))) {
      register struct Coord* c0 asm("r0");
      register u32 xf asm("r2");
      register u32 one asm("r1");
      c0 = &(p->s).coord;
      asm("" : "+r"(c0));
      xf = (u32)(p->s).flags >> 4;
      one = 1;
      xf &= one;
      rp = (u8*)p + 0xbc;
      ((void (*)(struct Coord*, u8, u32, u8))CreateGhost18)(c0, 0, xf, *rp);
    } else {
      register struct Coord* c1 asm("r0");
      register const struct SlashedEnemy* t3 asm("r1");
      register s32 k asm("r3");
      register s32 fl asm("r2");
      c1 = &(p->s).coord;
      asm("" : "+r"(c1));
      t3 = &sSlashedEnemies[3];
      fl = (p->s).flags;
      k = 0x10;
      k &= fl;
      ((struct VFX* (*)())CreateSlashedEnemy)(c1, t3, 0, (u8)k);
      rp = (u8*)p + 0xbc;
    }
    (p->s).coord.y += -0x2000;
    if (*rp != 0) {
      (p->s).d.x = -0x80;
    } else {
      (p->s).d.x = 0x80;
    }
    (p->s).d.y = -0x100;
    (p->s).mode[3]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    register s32 dy asm("r0");
    register s32 lim asm("r1");
    dy = (p->s).d.y;
    dy += 0x40;
    (p->s).d.y = dy;
    lim = 0xe0 << 3;
    if (dy > lim) {
      (p->s).d.y = lim;
    }
  }
  (p->s).coord.x += (p->s).d.x;
  {
    register s32 cy asm("r1");
    cy = (p->s).coord.y;
    cy += (p->s).d.y;
    (p->s).coord.y = cy;
    if ((u16)FUN_080098a4((p->s).coord.x, cy + (0x80 << 4))) {
      register struct Coord* c asm("r8");
      register const struct SlashedEnemy* t asm("ip");
      register u8* fp asm("r4");
      register s32 pal asm("r6");
      register u8* fp2 asm("r2");
      struct Coord* c0;
      c0 = &(p->s).coord;
      t = sSlashedEnemies;
      fp2 = (u8*)p + 0xbc;
      pal = *fp2;
      {
        register s32 k asm("r3");
        register s32 kk asm("r0");
        register u8 fl asm("r1");
        fl = (p->s).flags;
        k = 0x10;
        kk = k;
        kk &= fl;
        c = c0;
        fp = fp2;
        if (kk != 0) {
          k |= pal;
        } else {
          k = pal;
        }
        ((struct VFX* (*)())CreateSlashedEnemy)(c0, t, 0, k);
      }
      {
        register struct Coord* cp asm("r6");
        register const struct SlashedEnemy* t1 asm("r7");
        register s32 pal2 asm("r2");
        register s32 k2 asm("r3");
        register s32 kk2 asm("r0");
        register u8 fl2 asm("r1");
        cp = c;
        t1 = &sSlashedEnemies[1];
        pal2 = *fp;
        fl2 = (p->s).flags;
        k2 = 0x10;
        kk2 = k2;
        kk2 &= fl2;
        if (kk2 != 0) {
          k2 |= pal2;
        } else {
          k2 = pal2;
        }
        ((struct VFX* (*)())CreateSlashedEnemy)(cp, t1, 0, k2);
      }
      {
        register struct Coord* cp2 asm("r6");
        register const struct SlashedEnemy* t2 asm("r7");
        register s32 pal3 asm("r2");
        register s32 k3 asm("r3");
        register s32 kk3 asm("r0");
        register u8 fl3 asm("r1");
        cp2 = c;
        t2 = &sSlashedEnemies[2];
        pal3 = *fp;
        fl3 = (p->s).flags;
        k3 = 0x10;
        kk3 = k3;
        kk3 &= fl3;
        if (kk3 != 0) {
          k3 |= pal3;
        } else {
          k3 = pal3;
        }
        ((struct VFX* (*)())CreateSlashedEnemy)(cp2, t2, 0, k3);
      }
      {
        register struct Coord* cp4 asm("r4");
        cp4 = c;
        CreateSmoke(1, cp4);
        PlaySound(0x2a);
        TryDropItem(4, cp4);
        if (gMission.enemyCount <= 0x270E) {
          gMission.enemyCount++;
        }
        TryDropZakoDisk(p, c);
      }
      SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
    }
  }
}


// 0x080656cc
static void FUN_080656cc(struct Entity* p) {
  if (p->mode[3] == 0) {
    SetMotion(p, MOTION(SM019_PANTHEON_HUNTER, 3));
    p->mode[3]++;
  }
  UpdateMotionGraphic(p);
}

// --------------------------------------------

// 0x080656f4
static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* e = (struct Entity*)body->enemy->parent;
    struct PantheonHunterObject* self = (struct PantheonHunterObject*)body->parent;
    self->isRight = (e->coord).x > (self->s).coord.x;
  }
}

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      comboLv : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {-0x0200, -0x1000, 0x1200, 0x1000},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-0x0200, -0x1200, 0x1400, 0x2200},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      atkType : 0x00,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-0x0200, -0x1000, 0x1000, 0x1000},
    },
};

static const struct SlashedEnemy sSlashedEnemies[4] = {
    [0] = {
      m : MOTION(SM019_PANTHEON_HUNTER, 0x06),
      unk_02 : {0xFF, 0x11},
      c : {0, 0},
      d : {0x80, 0xFB00},
      unk_coord_0c : {0xFF, 0x1FF},
      unk_10 : {0, 0x40},
      unk_14 : {0x200, 0x200},
    },
    [1] = {
      m : MOTION(SM019_PANTHEON_HUNTER, 0x07),
      unk_02 : {0xFE, 0x11},
      c : {0, 0},
      d : {0x80, 0xFE00},
      unk_coord_0c : {0x7F, 0x7F},
      unk_10 : {0, 0x40},
      unk_14 : {0x200, 0x200},
    },
    [2] = {
      m : MOTION(SM019_PANTHEON_HUNTER, 0x08),
      unk_02 : {0xFE, 0x11},
      c : {0, 0},
      d : {0x100, 0xFD00},
      unk_coord_0c : {0x1FF, 0x1FF},
      unk_10 : {0, 0x40},
      unk_14 : {0x200, 0x200},
    },
    [3] = {
      m : MOTION(SM019_PANTHEON_HUNTER, 0x05),
      unk_02 : {0xFF, 0x4},
      c : {0, 0},
      d : {0, 0},
      unk_coord_0c : {0, 0},
      unk_10 : {0, 0x40},
      unk_14 : {0x800, 0x200},
    },
};

const struct Coord Coord_08365c84 = {0, -0x1000};
const struct Coord Coord_08365c8c = {0xFFFFF780, 0x880};
