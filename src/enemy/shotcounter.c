#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "zero.h"
#include "vfx.h"

bool8 shotcounter_08066da0(struct Enemy* p);

static const struct Collision sCollisions[];

static void Shotcounter_Init(struct Enemy* p);
static void Shotcounter_Update(struct Enemy* p);
static void Shotcounter_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gShotcounterRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Shotcounter_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Shotcounter_Update,
    [ENTITY_DIE] =       (EnemyFunc)Shotcounter_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// Unused
static struct Entity* CreateShotcounter(struct Coord* c, u8 r1) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    s32 x, y;
    p->taskCol = 0x18;
    INIT_ENEMY_ROUTINE(p, ENEMY_SHOTCOUNTER);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = r1;
  }
  return (void*)p;
}

NAKED static void Shotcounter_Init(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	bl InitNonAffineMotion\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	movs r3, #0\n\
	adds r2, r0, #0\n\
	orrs r2, r1\n\
	movs r0, #2\n\
	orrs r2, r0\n\
	orrs r2, r3\n\
	strb r2, [r6, #0xa]\n\
	ldr r0, _0806602C @ =gSystemSavedataManager\n\
	ldrb r1, [r0, #0x14]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08066038\n\
	ldr r0, _08066030 @ =gCurStory\n\
	ldrb r1, [r0, #4]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	lsls r0, r0, #0x18\n\
	lsrs r5, r0, #0x18\n\
	cmp r5, #0\n\
	bne _08066038\n\
	movs r0, #4\n\
	orrs r2, r0\n\
	strb r2, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _08066034 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0xc\n\
	b _08066050\n\
	.align 2, 0\n\
_0806602C: .4byte gSystemSavedataManager\n\
_08066030: .4byte gCurStory\n\
_08066034: .4byte sCollisions\n\
_08066038:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #4\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0806607C @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #8\n\
_08066050:\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	str r5, [r4, #0x24]\n\
	ldr r0, _08066080 @ =FUN_08066e34\n\
	str r0, [r4, #0x24]\n\
	adds r1, r6, #0\n\
	adds r1, #0xb4\n\
	ldr r0, [r6, #0x54]\n\
	str r0, [r1]\n\
	movs r0, #0\n\
	str r0, [r6, #0x60]\n\
	str r0, [r6, #0x5c]\n\
	ldrb r1, [r6, #0x10]\n\
	cmp r1, #0\n\
	bne _08066084\n\
	adds r0, r6, #0\n\
	adds r0, #0xbc\n\
	strb r1, [r0]\n\
	adds r4, r0, #0\n\
	b _0806608E\n\
	.align 2, 0\n\
_0806607C: .4byte sCollisions\n\
_08066080: .4byte FUN_08066e34\n\
_08066084:\n\
	adds r1, r6, #0\n\
	adds r1, #0xbc\n\
	movs r0, #1\n\
	strb r0, [r1]\n\
	adds r4, r1, #0\n\
_0806608E:\n\
	adds r0, r6, #0\n\
	adds r0, #0xc0\n\
	movs r5, #0\n\
	str r5, [r0]\n\
	subs r0, #3\n\
	strb r5, [r0]\n\
	subs r0, #5\n\
	str r5, [r0]\n\
	adds r0, r6, #0\n\
	bl IsFrozen\n\
	cmp r0, #0\n\
	beq _08066112\n\
	movs r1, #0x80\n\
	lsls r1, r1, #3\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	adds r0, r6, #0\n\
	bl UpdateMotionGraphic\n\
	ldrb r2, [r4]\n\
	cmp r2, #0\n\
	bne _080660E4\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	adds r0, #0x4c\n\
	strb r2, [r0]\n\
	adds r3, r6, #0\n\
	adds r3, #0x4a\n\
	ldrb r1, [r3]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r1\n\
	strb r0, [r3]\n\
	str r2, [r6, #0x5c]\n\
	ldr r0, _080660E0 @ =0xFFFFFF00\n\
	b _0806610C\n\
	.align 2, 0\n\
_080660E0: .4byte 0xFFFFFF00\n\
_080660E4:\n\
	movs r2, #1\n\
	ldrb r0, [r6, #0xa]\n\
	movs r1, #0x10\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	adds r0, #0x4c\n\
	strb r2, [r0]\n\
	adds r3, r6, #0\n\
	adds r3, #0x4a\n\
	movs r2, #0x10\n\
	ldrb r1, [r3]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r1\n\
	orrs r0, r2\n\
	strb r0, [r3]\n\
	str r5, [r6, #0x5c]\n\
	movs r0, #0x80\n\
	lsls r0, r0, #1\n\
_0806610C:\n\
	str r0, [r6, #0x64]\n\
	movs r0, #0\n\
	str r0, [r6, #0x60]\n\
_08066112:\n\
	adds r0, r6, #0\n\
	adds r0, #0xbf\n\
	movs r1, #0\n\
	strb r1, [r0]\n\
	subs r0, #1\n\
	strb r1, [r0]\n\
	ldr r2, _08066144 @ =gEnemyFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r2\n\
	movs r2, #1\n\
	str r2, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	strb r2, [r6, #0xd]\n\
	strb r1, [r6, #0xe]\n\
	strb r1, [r6, #0xf]\n\
	adds r0, r6, #0\n\
	bl Shotcounter_Update\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_08066144: .4byte gEnemyFnTable\n\
 .syntax divided\n");
}

static bool8 FUN_080665e0(void* _ UNUSED);
static bool8 FUN_080665e8(void* _ UNUSED);
bool8 FUN_080667b8(struct Enemy* p);
bool8 nop_08066978(struct Enemy* p);
bool8 FUN_08066ad0(struct Enemy* p);
bool8 FUN_08066ad8(struct Enemy* p);
bool8 FUN_08066b30(struct Enemy* p);
bool8 FUN_08066b38(struct Enemy* p);
bool8 FUN_08066bdc(struct Enemy* p);

static void FUN_080665e4(void* _ UNUSED);
void FUN_080665ec(struct Enemy* p);
void shotcounter_080667bc(struct Enemy* p);
void shotcounter_0806697c(struct Enemy* p);
void FUN_08066ad4(struct Enemy* p);
void FUN_08066adc(struct Enemy* p);
void FUN_08066b34(struct Enemy* p);
void FUN_08066b3c(struct Enemy* p);
void shotcounter_08066be0(struct Enemy* p);

static void Shotcounter_Update(struct Enemy* p) {
  // clang-format off
  static const EnemyFunc sUpdates1[9] = {
      (EnemyFunc)FUN_080665e0,
      (EnemyFunc)FUN_080665e8,
      (EnemyFunc)FUN_080667b8,
      (EnemyFunc)nop_08066978,
      (EnemyFunc)FUN_08066ad0,
      (EnemyFunc)FUN_08066ad8,
      (EnemyFunc)FUN_08066b30,
      (EnemyFunc)FUN_08066b38,
      (EnemyFunc)FUN_08066bdc,
  };
  // clang-format on

  // clang-format off
  static const EnemyFunc sUpdates2[9] = {
      (EnemyFunc)FUN_080665e4,
      (EnemyFunc)FUN_080665ec,
      (EnemyFunc)shotcounter_080667bc,
      (EnemyFunc)shotcounter_0806697c,
      (EnemyFunc)FUN_08066ad4,
      (EnemyFunc)FUN_08066adc,
      (EnemyFunc)FUN_08066b34,
      (EnemyFunc)FUN_08066b3c,
      (EnemyFunc)shotcounter_08066be0,
  };
  // clang-format on

  if (((p->body).status & BODY_STATUS_DEAD) && ((p->s).mode[1] != 8 || IsFrozen((void*)p))) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Shotcounter_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])((void*)p);
  shotcounter_08066da0(p);
  if ((p->s).mode[1] == 8 || (p->s).mode[1] == 5 || (p->s).mode[1] == 7 || !IsFrozen((void*)p)) {
    (sUpdates2[(p->s).mode[1]])((void*)p);
  }
}

NAKED static void Shotcounter_Die(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	sub sp, #0x20\n\
	adds r7, r0, #0\n\
	ldr r0, _08066220 @ =gCurStory\n\
	ldrb r1, [r0, #8]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _08066228\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r2, #0\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r7, #0xa]\n\
	adds r0, r7, #0\n\
	adds r0, #0x8c\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r7, #0xa]\n\
	ldr r1, _08066224 @ =gEnemyFnTable\n\
	ldrb r0, [r7, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r7, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	b _080665AE\n\
	.align 2, 0\n\
_08066220: .4byte gCurStory\n\
_08066224: .4byte gEnemyFnTable\n\
_08066228:\n\
	ldrb r0, [r7, #0xe]\n\
	cmp r0, #0xb\n\
	bls _08066230\n\
	b _080665B0\n\
_08066230:\n\
	lsls r0, r0, #2\n\
	ldr r1, _0806623C @ =_08066240\n\
	adds r0, r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.align 2, 0\n\
_0806623C: .4byte _08066240\n\
_08066240: @ jump table\n\
	.4byte _08066270 @ case 0\n\
	.4byte _08066388 @ case 1\n\
	.4byte _080662C0 @ case 2\n\
	.4byte _080662D4 @ case 3\n\
	.4byte _08066390 @ case 4\n\
	.4byte _080665B0 @ case 5\n\
	.4byte _080665B0 @ case 6\n\
	.4byte _080665B0 @ case 7\n\
	.4byte _080665B0 @ case 8\n\
	.4byte _080665B0 @ case 9\n\
	.4byte _08066388 @ case 10\n\
	.4byte _08066510 @ case 11\n\
_08066270:\n\
	ldr r1, _08066298 @ =0x00000406\n\
	adds r0, r7, #0\n\
	bl SetMotion\n\
	adds r1, r7, #0\n\
	adds r1, #0x8c\n\
	ldr r2, [r1]\n\
	movs r0, #0x80\n\
	lsls r0, r0, #2\n\
	ands r0, r2\n\
	adds r3, r1, #0\n\
	cmp r0, #0\n\
	beq _0806629C\n\
	movs r0, #0x80\n\
	lsls r0, r0, #9\n\
	ands r2, r0\n\
	cmp r2, #0\n\
	beq _0806629C\n\
	movs r0, #1\n\
	b _0806629E\n\
	.align 2, 0\n\
_08066298: .4byte 0x00000406\n\
_0806629C:\n\
	movs r0, #0xa\n\
_0806629E:\n\
	strb r0, [r7, #0xe]\n\
	movs r1, #0\n\
	str r1, [r3]\n\
	adds r0, r7, #0\n\
	adds r0, #0x90\n\
	str r1, [r0]\n\
	adds r0, #4\n\
	strb r1, [r0]\n\
	ldrb r2, [r7, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r2\n\
	strb r0, [r7, #0xa]\n\
	adds r0, r7, #0\n\
	adds r0, #0x5c\n\
	str r1, [r0, #4]\n\
	str r1, [r7, #0x5c]\n\
	b _08066388\n\
_080662C0:\n\
	adds r0, r7, #0\n\
	bl UpdateMotionGraphic\n\
	adds r0, r7, #0\n\
	adds r0, #0x73\n\
	ldrb r0, [r0]\n\
	cmp r0, #3\n\
	beq _080662D2\n\
	b _080665B0\n\
_080662D2:\n\
	b _08066388\n\
_080662D4:\n\
	ldr r1, _08066314 @ =0x00000406\n\
	adds r0, r7, #0\n\
	bl SetMotion\n\
	adds r0, r7, #0\n\
	bl UpdateMotionGraphic\n\
	movs r0, #0\n\
	strb r0, [r7, #0x13]\n\
	str r0, [r7, #0x60]\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp]\n\
	ldr r0, [r7, #0x58]\n\
	str r0, [sp, #4]\n\
	adds r4, r7, #0\n\
	adds r4, #0xbc\n\
	ldrb r1, [r4]\n\
	mov r0, sp\n\
	bl CreateGhost20\n\
	ldrb r0, [r4]\n\
	cmp r0, #0\n\
	bne _0806631C\n\
	ldr r0, [sp]\n\
	ldr r1, _08066318 @ =0xFFFFF800\n\
	adds r0, r0, r1\n\
	str r0, [sp]\n\
	ldr r0, [sp, #4]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #4\n\
	b _08066328\n\
	.align 2, 0\n\
_08066314: .4byte 0x00000406\n\
_08066318: .4byte 0xFFFFF800\n\
_0806631C:\n\
	ldr r0, [sp]\n\
	movs r1, #0x80\n\
	lsls r1, r1, #4\n\
	adds r0, r0, r1\n\
	str r0, [sp]\n\
	ldr r0, [sp, #4]\n\
_08066328:\n\
	adds r0, r0, r1\n\
	str r0, [sp, #4]\n\
	adds r0, r7, #0\n\
	adds r0, #0xbe\n\
	ldrb r0, [r0]\n\
	cmp r0, #0xff\n\
	beq _08066356\n\
	cmp r0, #0xfe\n\
	bne _0806634A\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	movs r0, #0\n\
	mov r1, sp\n\
	movs r3, #0\n\
	bl FUN_080b2b40\n\
	b _0806637A\n\
_0806634A:\n\
	ldr r0, _08066368 @ =pZero2\n\
	ldr r0, [r0]\n\
	ldr r1, [r0, #0x54]\n\
	ldr r0, [r7, #0x54]\n\
	cmp r1, r0\n\
	ble _0806636C\n\
_08066356:\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	movs r0, #0\n\
	mov r1, sp\n\
	movs r3, #1\n\
	bl FUN_080b2b40\n\
	b _0806637A\n\
	.align 2, 0\n\
_08066368: .4byte pZero2\n\
_0806636C:\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	movs r0, #0\n\
	mov r1, sp\n\
	movs r3, #0\n\
	bl FUN_080b2b40\n\
_0806637A:\n\
	adds r1, r7, #0\n\
	adds r1, #0x54\n\
	movs r0, #4\n\
	bl TryDropItem\n\
	movs r0, #0x44\n\
	strb r0, [r7, #0x12]\n\
_08066388:\n\
	ldrb r0, [r7, #0xe]\n\
	adds r0, #1\n\
	strb r0, [r7, #0xe]\n\
	b _080665B0\n\
_08066390:\n\
	adds r0, r7, #0\n\
	bl UpdateMotionGraphic\n\
	ldr r0, [r7, #0x60]\n\
	adds r0, #0x10\n\
	str r0, [r7, #0x60]\n\
	movs r1, #0xe0\n\
	lsls r1, r1, #3\n\
	cmp r0, r1\n\
	ble _080663A6\n\
	str r1, [r7, #0x60]\n\
_080663A6:\n\
	ldr r1, [r7, #0x58]\n\
	ldr r0, [r7, #0x60]\n\
	adds r1, r1, r0\n\
	str r1, [r7, #0x58]\n\
	ldr r2, [r7, #0x5c]\n\
	rsbs r0, r2, #0\n\
	lsls r0, r0, #2\n\
	asrs r0, r0, #8\n\
	adds r2, r2, r0\n\
	str r2, [r7, #0x5c]\n\
	ldr r0, [r7, #0x54]\n\
	adds r0, r0, r2\n\
	str r0, [r7, #0x54]\n\
	bl FUN_080098a4\n\
	lsls r0, r0, #0x10\n\
	cmp r0, #0\n\
	beq _08066464\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp]\n\
	ldr r0, [r7, #0x58]\n\
	str r0, [sp, #4]\n\
	movs r0, #2\n\
	mov r1, sp\n\
	bl CreateSmoke\n\
	ldr r2, _08066444 @ =RNG_0202f388\n\
	ldr r1, [r2]\n\
	ldr r0, _08066448 @ =0x000343FD\n\
	adds r4, r1, #0\n\
	muls r4, r0, r4\n\
	ldr r0, _0806644C @ =0x00269EC3\n\
	adds r4, r4, r0\n\
	lsls r4, r4, #1\n\
	lsrs r0, r4, #1\n\
	str r0, [r2]\n\
	lsrs r4, r4, #0x11\n\
	movs r0, #3\n\
	ands r4, r0\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp, #8]\n\
	ldr r0, [r7, #0x58]\n\
	add r6, sp, #8\n\
	str r0, [r6, #4]\n\
	adds r5, r7, #0\n\
	adds r5, #0xbc\n\
	ldrb r1, [r5]\n\
	ldr r2, _08066450 @ =0x00000409\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldrb r1, [r5]\n\
	ldr r2, _08066454 @ =0x0000040A\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldrb r1, [r5]\n\
	ldr r2, _08066458 @ =0x0000040B\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	movs r0, #0x2a\n\
	bl PlaySound\n\
	ldr r2, _0806645C @ =gMission\n\
	ldrh r1, [r2, #0xc]\n\
	ldr r0, _08066460 @ =0x0000270E\n\
	cmp r1, r0\n\
	bhi _0806643A\n\
	adds r0, r1, #1\n\
	strh r0, [r2, #0xc]\n\
_0806643A:\n\
	adds r1, r7, #0\n\
	adds r1, #0x54\n\
	adds r0, r7, #0\n\
	b _08066592\n\
	.align 2, 0\n\
_08066444: .4byte RNG_0202f388\n\
_08066448: .4byte 0x000343FD\n\
_0806644C: .4byte 0x00269EC3\n\
_08066450: .4byte 0x00000409\n\
_08066454: .4byte 0x0000040A\n\
_08066458: .4byte 0x0000040B\n\
_0806645C: .4byte gMission\n\
_08066460: .4byte 0x0000270E\n\
_08066464:\n\
	ldrb r0, [r7, #0x12]\n\
	cmp r0, #0\n\
	bne _0806646C\n\
	b _080665B0\n\
_0806646C:\n\
	subs r0, #1\n\
	strb r0, [r7, #0x12]\n\
	lsls r0, r0, #0x18\n\
	cmp r0, #0\n\
	beq _08066478\n\
	b _080665B0\n\
_08066478:\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp]\n\
	ldr r0, [r7, #0x58]\n\
	str r0, [sp, #4]\n\
	movs r0, #2\n\
	mov r1, sp\n\
	bl CreateSmoke\n\
	ldr r2, _080664F0 @ =RNG_0202f388\n\
	ldr r1, [r2]\n\
	ldr r0, _080664F4 @ =0x000343FD\n\
	adds r4, r1, #0\n\
	muls r4, r0, r4\n\
	ldr r1, _080664F8 @ =0x00269EC3\n\
	adds r4, r4, r1\n\
	lsls r4, r4, #1\n\
	lsrs r0, r4, #1\n\
	str r0, [r2]\n\
	lsrs r4, r4, #0x11\n\
	movs r0, #3\n\
	ands r4, r0\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp, #0x10]\n\
	ldr r0, [r7, #0x58]\n\
	add r6, sp, #0x10\n\
	str r0, [r6, #4]\n\
	adds r5, r7, #0\n\
	adds r5, #0xbc\n\
	ldrb r1, [r5]\n\
	ldr r2, _080664FC @ =0x00000409\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldrb r1, [r5]\n\
	ldr r2, _08066500 @ =0x0000040A\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldrb r1, [r5]\n\
	ldr r2, _08066504 @ =0x0000040B\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	movs r0, #0x2a\n\
	bl PlaySound\n\
	ldr r2, _08066508 @ =gMission\n\
	ldrh r1, [r2, #0xc]\n\
	ldr r0, _0806650C @ =0x0000270E\n\
	cmp r1, r0\n\
	bhi _080664E8\n\
	adds r0, r1, #1\n\
	strh r0, [r2, #0xc]\n\
_080664E8:\n\
	adds r1, r7, #0\n\
	adds r1, #0x54\n\
	adds r0, r7, #0\n\
	b _08066592\n\
	.align 2, 0\n\
_080664F0: .4byte RNG_0202f388\n\
_080664F4: .4byte 0x000343FD\n\
_080664F8: .4byte 0x00269EC3\n\
_080664FC: .4byte 0x00000409\n\
_08066500: .4byte 0x0000040A\n\
_08066504: .4byte 0x0000040B\n\
_08066508: .4byte gMission\n\
_0806650C: .4byte 0x0000270E\n\
_08066510:\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp]\n\
	ldr r0, [r7, #0x58]\n\
	str r0, [sp, #4]\n\
	movs r0, #1\n\
	mov r1, sp\n\
	bl CreateSmoke\n\
	movs r0, #0x2a\n\
	bl PlaySound\n\
	movs r0, #0x54\n\
	adds r0, r0, r7\n\
	mov r8, r0\n\
	movs r0, #4\n\
	mov r1, r8\n\
	bl TryDropItem\n\
	ldr r2, _080665BC @ =RNG_0202f388\n\
	ldr r1, [r2]\n\
	ldr r0, _080665C0 @ =0x000343FD\n\
	adds r4, r1, #0\n\
	muls r4, r0, r4\n\
	ldr r1, _080665C4 @ =0x00269EC3\n\
	adds r4, r4, r1\n\
	lsls r4, r4, #1\n\
	lsrs r0, r4, #1\n\
	str r0, [r2]\n\
	lsrs r4, r4, #0x11\n\
	movs r0, #3\n\
	ands r4, r0\n\
	ldr r0, [r7, #0x54]\n\
	str r0, [sp, #0x18]\n\
	ldr r0, [r7, #0x58]\n\
	add r6, sp, #0x18\n\
	str r0, [r6, #4]\n\
	adds r5, r7, #0\n\
	adds r5, #0xbc\n\
	ldrb r1, [r5]\n\
	ldr r2, _080665C8 @ =0x00000409\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldrb r1, [r5]\n\
	ldr r2, _080665CC @ =0x0000040A\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldrb r1, [r5]\n\
	ldr r2, _080665D0 @ =0x0000040B\n\
	adds r0, r6, #0\n\
	adds r3, r4, #0\n\
	bl FUN_080b721c\n\
	ldr r2, _080665D4 @ =gMission\n\
	ldrh r1, [r2, #0xc]\n\
	ldr r0, _080665D8 @ =0x0000270E\n\
	cmp r1, r0\n\
	bhi _0806658E\n\
	adds r0, r1, #1\n\
	strh r0, [r2, #0xc]\n\
_0806658E:\n\
	adds r0, r7, #0\n\
	mov r1, r8\n\
_08066592:\n\
	bl TryDropZakoDisk\n\
	ldrb r1, [r7, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	strb r0, [r7, #0xa]\n\
	ldr r1, _080665DC @ =gEnemyFnTable\n\
	ldrb r0, [r7, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #4\n\
	str r1, [r7, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0x10]\n\
_080665AE:\n\
	str r0, [r7, #0x14]\n\
_080665B0:\n\
	add sp, #0x20\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080665BC: .4byte RNG_0202f388\n\
_080665C0: .4byte 0x000343FD\n\
_080665C4: .4byte 0x00269EC3\n\
_080665C8: .4byte 0x00000409\n\
_080665CC: .4byte 0x0000040A\n\
_080665D0: .4byte 0x0000040B\n\
_080665D4: .4byte gMission\n\
_080665D8: .4byte 0x0000270E\n\
_080665DC: .4byte gEnemyFnTable\n\
 .syntax divided\n");
}

static bool8 FUN_080665e0(void* _) { return TRUE; }

static void FUN_080665e4(void* _) { return; }

static bool8 FUN_080665e8(void* _) { return TRUE; }

INCASM("asm/enemy/shotcounter_p1.inc");

bool8 FUN_080667b8(struct Enemy* p) { return TRUE; }

struct Projectile* CreateShotcounterBullet(struct Coord* c, struct Coord* d, u8 r2, u8 r3);

// 0x080667BC
void shotcounter_080667bc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 z asm("r4");
      register u8* fp asm("r1");
      register s32 one asm("r0");
      SetMotion(&p->s, 0x401);
      PlaySound(0x103);
      fp = (u8*)p + 0xbd;
      z = 0;
      one = 1;
      *fp = one;
      SetDDP(&p->body, &sCollisions[7]);
      (p->s).work[2] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if ((u8)++(p->s).work[2] == 2) {
        *((u8*)p + 0xbd) = 1;
        SetDDP(&p->body, &sCollisions[7]);
      }
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) != 3) {
        break;
      }
      (p->s).work[2] = 0xc;
      goto bump;
    case 3:
      SetMotion(&p->s, 0x402);
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 4: {
      if ((p->s).work[2] != 0) {
        register s32 t asm("r2");
        {
          register s32 v asm("r0");
          v = (p->s).work[2];
          v -= 1;
          (p->s).work[2] = v;
          t = (u8)v;
        }
        if (t == 0) {
          struct Coord c;
          struct Coord d;
          register u8* kp asm("r3");
          c.y = (p->s).coord.y;
          d.y = t;
          {
            register u8* q asm("r0");
            register s32 kv asm("r2");
            q = (u8*)p + 0xbc;
            kv = *q;
            kp = q;
            if (kv == 0) {
              register s32 k1 asm("r2");
              register s32 cx asm("r0");
              cx = (p->s).coord.x;
              k1 = -0xe00;
              cx += k1;
              c.x = cx;
              d.x = -0x280;
            } else {
              register s32 k2 asm("r2");
              register s32 cx2 asm("r0");
              cx2 = (p->s).coord.x;
              k2 = 0xe0 << 4;
              cx2 += k2;
              c.x = cx2;
              d.x = 0xa0 << 2;
            }
          }
          CreateShotcounterBullet(&c, &d, *kp, 0);
          CreateSmoke(3, &c);
          PlaySound(0x2c);
        }
      }
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) != 3) {
        break;
      }
      goto bump;
    }
    case 5:
      (p->s).work[2] = 0xc;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 2:
    case 6:
      UpdateMotionGraphic(&p->s);
      if (*((u8*)p + 0x73) == 3) {
        goto bump;
      }
      if ((p->s).work[2] == 0) {
        break;
      }
      if ((u8)--(p->s).work[2] != 0) {
        break;
      }
    bump:
      (p->s).mode[2]++;
      break;
    case 7:
      SetMotion(&p->s, 0x403);
      PlaySound(0x103);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 8: {
      register s32 st asm("r6");
      register s32 z2 asm("r4");
      register u8* fp2 asm("r1");
      register s32 one2 asm("r0");
      UpdateMotionGraphic(&p->s);
      st = *((u8*)p + 0x73);
      if (st != 3) {
        break;
      }
      fp2 = (u8*)p + 0xbd;
      z2 = 0;
      one2 = 1;
      *fp2 = one2;
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).mode[1] = st;
      (p->s).mode[2] = z2;
      break;
    }
  }
}


bool8 nop_08066978(struct Enemy* p) { return TRUE; }

void shotcounter_0806697c(struct Enemy* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      SetMotion(&p->s, 0x0404);
      {
        register s32 fb asm("r2");
        fb = *((u8*)p + 0xbc);
        asm("" : "+r"(fb));
        if (fb == 0) {
          (p->s).flags &= 0xEF;
          (p->s).spr.xflip = fb;
          {
            u8* oa = (u8*)p + 0x4a;
            s32 ov = *oa;
            s32 m11 = -0x11;
            m11 &= ov;
            *oa = m11;
          }
          (p->s).d.x = fb;
        } else {
          s32 o = 1;
          u32 f2 = (p->s).flags;
          s32 t16 = 0x10;
          t16 |= f2;
          (p->s).flags = t16;
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
          (p->s).d.x = m;
        }
      }
      {
        s32 z = 0;
        u8* a;
        (p->s).d.y = z;
        a = (u8*)p + 0xb8;
        *(s32*)a = z;
        asm("" : "+r"(a));
        SetDDP((struct Body*)(a - 0x44), &sCollisions[5]);
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1:
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      SetMotion(&p->s, 0x0405);
      {
        u8* fb;
        register s32 v asm("r2");
        register s32 v0 asm("r0");
        register s32 one1 asm("r1");
        fb = (u8*)p + 0xbc;
        asm("" : "+r"(fb));
        v0 = *fb;
        one1 = 1;
        v0 ^= one1;
        *fb = v0;
        v = v0;
        asm("" : "+r"(v0));
        if (v == 0) {
          (p->s).flags &= 0xEF;
          (p->s).spr.xflip = v;
          {
            u8* oa = (u8*)p + 0x4a;
            s32 ov = *oa;
            s32 m11 = -0x11;
            m11 &= ov;
            *oa = m11;
          }
          (p->s).d.x = v;
        } else {
          s32 o;
          register u8* t0 asm("r0");
          register u8* oa2 asm("ip");
          register u8* fa asm("r1");
          register u8* xa asm("r0");
          register s32 z3 asm("r3");
          u32 off;
          o = 1;
          asm("" : "+r"(o));
          {
            register s32 cf asm("r1");
            u32 fl2 = (p->s).flags;
            cf = 0x10;
            fl2 |= cf;
            (p->s).flags = fl2;
          }
          xa = (u8*)p + 0x4c;
          z3 = 0;
          asm("" : "+r"(z3) : "r"(xa));
          *xa = o;
          asm("" : "+r"(z3));
          off = 0x4a;
          asm("" : "+r"(off));
          off += (u32)p;
          t0 = (u8*)off;
          oa2 = t0;
          asm("" : "+r"(oa2));
          {
            s32 c16 = 0x10;
            s32 ov, m11;
            u32 vv;
            asm("" : "+r"(c16));
            ov = *t0;
            m11 = -0x11;
            m11 &= ov;
            vv = m11 | c16;
            fa = oa2;
            asm("" : "+r"(fa));
            *fa = vv;
          }
          (p->s).d.x = z3;
        }
      }
      (p->s).d.y = 0;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 3:
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        s32 z = 0;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      break;
  }
}

bool8 FUN_08066ad0(struct Enemy* p) { return TRUE; }


void FUN_08066ad4(struct Enemy* p) {}

bool8 FUN_08066ad8(struct Enemy* p) { return TRUE; }

void FUN_08066adc(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[8]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    u8* flag = (u8*)((u8*)p + 0xbf);
    s32 zero = 0;
    *flag = zero;
    *slot = (struct Entity*)zero;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = zero;
    SetDDP(&p->body, &sCollisions[7]);
    (p->s).mode[2] = 1;
  }
}

bool8 FUN_08066b30(struct Enemy* p) { return TRUE; }


void FUN_08066b34(struct Enemy* p) {}

bool8 FUN_08066b38(struct Enemy* p) { return TRUE; }

// 0x08066B3C
void FUN_08066b3c(struct Enemy* p) {
  struct Entity** slot;
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      SetDDP(&p->body, &sCollisions[8]);
      (p->s).d.y = m;
      (p->s).mode[2]++;
    case 1:
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + (p->s).d.y + 0x1000)) {
        (p->s).d.y = 0;
        (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - 0x1000;
      } else {
        (p->s).coord.y += (p->s).d.y;
      }
      break;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    u32 z;
    u8 one;
    u8* q;
    q = (u8*)p + 0xbf;
    z = 0;
    *q = z;
    *slot = (struct Entity*)z;
    one = 1;
    (p->s).mode[1] = one;
    (p->s).mode[2] = z;
    SetDDP(&p->body, &sCollisions[7]);
    (p->s).mode[2] = one;
  }
}

bool8 FUN_08066bdc(struct Enemy* p) { return TRUE; }

// 0x08066BE0
void shotcounter_08066be0(struct Enemy* p) {
  u16 v;
  s32 t, sl;
  u8 w;
  struct Entity** slot;

  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[10]);
      (p->s).mode[3] = ((pZero2->s).flags >> 4) & 1;
      (p->s).work[2] = 0x1a;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      break;
    default:
      return;
  }

  {
    register s32 k asm("r3");
    s32 x, y;
    x = (p->s).coord.x + (p->s).d.x;
    k = 0x1000;
    asm("" : "+l"(k));
    x += k;
    y = (p->s).coord.y + (p->s).d.y + k;
    v = FUN_080098a4(x, y);
  }
  if (v != 0 && (v & 0x8000) == 0) {
    goto blocked;
  }
  {
    register s32 k asm("r2");
    s32 x, y, n;
    x = (p->s).coord.x - (p->s).d.x;
    n = -0x1000;
    asm("" : "+l"(n));
    x += n;
    y = (p->s).coord.y + (p->s).d.y;
    k = 0x1000;
    asm("" : "+l"(k));
    y += k;
    v = FUN_080098a4(x, y);
  }
  if (v != 0 && (v & 0x8000) == 0) {
    goto blocked;
  }
  {
    register s32 k asm("r3");
    register s32 n asm("r2");
    s32 x, y;
    x = (p->s).coord.x + (p->s).d.x;
    k = 0x1000;
    asm("" : "+l"(k));
    x += k;
    y = (p->s).coord.y + (p->s).d.y;
    n = -0x1000;
    asm("" : "+l"(n));
    y += n;
    v = FUN_080098a4(x, y);
  }
  if (v != 0 && (v & 0x8000) == 0) {
    goto blocked;
  }
  {
    register s32 n asm("r3");
    s32 x, y;
    x = (p->s).coord.x - (p->s).d.x;
    n = -0x1000;
    asm("" : "+l"(n));
    x += n;
    y = (p->s).coord.y + (p->s).d.y + n;
    v = FUN_080098a4(x, y);
  }
  if (v != 0 && (v & 0x8000) == 0) {
    goto blocked;
  }

  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.x += ((p->s).d.x - ((p->s).d.x << 4)) >> 8;
  (p->s).d.y += ((p->s).d.y - ((p->s).d.y << 4)) >> 8;

  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    u8* q = (u8*)p + 0xbf;
    s32 z = 0;
    *q = z;
    *slot = (struct Entity*)z;
  }

  t = (p->s).work[2] - 1;
  (p->s).work[2] = t;
  w = t;
  if (w != 0) {
    return;
  }
  *(s32*)((u8*)p + 0xb8) = w;
  sl = (s32)*slot;
  {
    if (sl != 0) {
      u8 f = *((u8*)p + 0xbf);
      if (f == 1) {
        if (*(s16*)((u8*)p + 0xa4) <= 1) {
          goto blocked;
        }
        asm("" : : "l"(f));
        (p->s).mode[1] = 5;
        (p->s).mode[2] = w;
        return;
      }
      if (f == 2) {
        if (*(s16*)((u8*)p + 0xa4) <= 1) {
          SET_ENEMY_ROUTINE(p, f);
          return;
        }
        (p->s).mode[1] = 7;
        (p->s).mode[2] = w;
        return;
      }
      if (*(s16*)((u8*)p + 0xa4) <= 1) {
        goto blocked;
      }
      (p->s).mode[1] = 1;
      (p->s).mode[2] = w;
      return;
    }
    if (*(s16*)((u8*)p + 0xa4) > 1) {
      goto setmode1;
    }
  }
blocked:
  SET_ENEMY_ROUTINE(p, 2);
  return;
setmode1:
  (p->s).mode[1] = 1;
  (p->s).mode[2] = sl;
}

#include "element.h"
#include "vfx.h"

extern const struct Coord Coord_08365e84;

bool8 shotcounter_08066da0(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)&p->props[12];
  struct VFX* e;
  u8 attr;

  if (*slot == NULL && ((p->body).status & 1)) {
    e = ApplyElementEffect(0, &p->s, &Coord_08365e84);
    *slot = e;
    if ((p->s).mode[1] != 8) {
      if (e != NULL) {
        attr = *(u8*)((u8*)p + 0x97) & 0xf0;
        if (attr == 0x10) {
          p->props[11] = 1;
          (p->s).mode[1] = 5;
          (p->s).mode[2] = 0;
        } else if (attr == 0x30) {
          p->props[11] = 2;
          (p->s).mode[1] = 7;
          (p->s).mode[2] = 0;
        }
      }
    } else if (e != NULL) {
      attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        p->props[11] = 1;
      } else if (attr == 0x30) {
        p->props[11] = 2;
      }
    }
  }
  return TRUE;
}

void FUN_08066e34(struct Body* b0, struct Coord* c0) {
  register struct Body* body asm("r2");
  register struct Coord* c asm("r5");
  register const struct Collision* pc asm("r3");
  struct Body* eb;
  body = b0;
  c = c0;
  eb = (struct Body*)body->enemy;
  pc = eb->processing;
  {
  u8 at = pc->atkType;
  if (at == 3 || at == 0xE || at == 0xF) {
    register struct Enemy* p asm("r4");
    p = (struct Enemy*)body->parent;
    if ((p->body).status & 0x200) {
      if ((p->s).coord.x < c->x) {
        *((u8*)p + 0xbe) = 0xFF;
      } else {
        *((u8*)p + 0xbe) = 0xFE;
      }
      asm volatile("" :: "r"(p));
    }
  }
  }
  if ((*(u32*)&pc->atkType & 0x200FF) == 0x20002) {
    register struct Enemy* p asm("r4");
    p = (struct Enemy*)body->parent;
    if ((p->s).mode[1] != 8) {
      if (((p->body).status & 0x200) && !IsFrozen(&p->s)) {
        (p->body).hp = 1;
      }
      {
        register struct Zero* zd asm("r2");
        register s32 dx asm("r0");
        register s32 dy asm("r1");
        u32 dist;
        zd = pZero2;
        dx = (p->s).coord.x;
        asm("" : "+r"(dx));
        dx -= (zd->s).coord.x;
        (p->s).unk_coord.x = dx;
        dy = (p->s).coord.y;
        asm("" : "+r"(dy));
        dy += 0x1000;
        dy -= (zd->s).coord.y;
        (p->s).unk_coord.y = dy;
        dx >>= 2;
        {
          s32 t = dx;
          t *= dx;
          dx = t;
        }
        dy >>= 2;
        {
          s32 t = dy;
          t *= dy;
          dy = t;
        }
        dist = (u16)Sqrt(dx + dy) << 2;
        if (dist != 0) {
          (p->s).unk_coord.x = ((p->s).unk_coord.x << 8) / (s32)dist;
          (p->s).unk_coord.y = ((p->s).unk_coord.y << 8) / (s32)dist;
        } else {
          if ((pZero2->s).coord.x > (p->s).coord.x) {
            (p->s).unk_coord.x = -0x100;
          } else {
            (p->s).unk_coord.x = 0x100;
          }
          (p->s).unk_coord.y = dist;
        }
        (p->s).d.x = ((p->s).unk_coord.x * 7 << 8) >> 8;
        (p->s).d.y = ((p->s).unk_coord.y * 7 << 8) >> 8;
        (p->s).mode[1] = 8;
        (p->s).mode[2] = 0;
      }
    }
  }
}

// 0x08365D64
static const struct Collision sCollisions[12] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 4,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    [1] = {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 3,
      range : {-PIXEL(12), PIXEL(0), PIXEL(8), PIXEL(30)},
    },
    [2] = {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 2,
      layer : 0xFFFFFFFF,
      range : {-PIXEL(6), PIXEL(12), PIXEL(12), PIXEL(8)},
    },
    [3] = {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 1,
      layer : 0xFFFFFFFF,
      range : {-PIXEL(6), -PIXEL(12), PIXEL(12), PIXEL(8)},
    },
    [4] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(14), PIXEL(0), PIXEL(8), PIXEL(22)},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(26)},
    },
    [6] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(26)},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    [8] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {-PIXEL(10), PIXEL(0), PIXEL(8), PIXEL(18)},
    },
    [9] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(14), PIXEL(0), PIXEL(8), PIXEL(22)},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
    [11] = {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(26)},
    },
};

const struct Coord Coord_08365e84 = {0, 0};
