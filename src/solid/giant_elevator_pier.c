#include "collision.h"
#include "global.h"
#include "quake.h"
#include "solid.h"
#include "stagerun.h"

static const struct Rect sSize;

static void Solid45_Init(struct Solid* p);
static void Solid45_Update(struct Solid* p);
void Solid45_Die(struct Solid* p);

// clang-format off
const SolidRoutine gGiantElevatorPierRoutine = {
    [ENTITY_INIT] =      Solid45_Init,
    [ENTITY_UPDATE] =    Solid45_Update,
    [ENTITY_DIE] =       Solid45_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

NAKED static void Solid45_Init(struct Solid* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	ldr r0, _080DE638 @ =gOverworld\n\
	ldr r1, _080DE63C @ =0x0002D024\n\
	adds r0, r0, r1\n\
	ldrb r4, [r0]\n\
	cmp r4, #0\n\
	beq _080DE644\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r2, #0\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	adds r0, #0x8c\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	ldr r1, _080DE640 @ =gSolidFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	str r0, [r6, #0x14]\n\
	b _080DE6E2\n\
	.align 2, 0\n\
_080DE638: .4byte gOverworld\n\
_080DE63C: .4byte 0x0002D024\n\
_080DE640: .4byte gSolidFnTable\n\
_080DE644:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	orrs r0, r1\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	movs r1, #0x9a\n\
	lsls r1, r1, #8\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	ldrb r1, [r6, #0xb]\n\
	movs r0, #8\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xb]\n\
	ldr r0, _080DE6E8 @ =sSize\n\
	str r0, [r6, #0x30]\n\
	ldr r0, _080DE6EC @ =0x00002001\n\
	strh r0, [r6, #0x26]\n\
	str r4, [r6, #0x60]\n\
	str r4, [r6, #0x5c]\n\
	ldr r0, [r6, #0x54]\n\
	ldr r2, _080DE6F0 @ =0xFFFFF800\n\
	adds r1, r0, r2\n\
	str r1, [r6, #0x54]\n\
	ldr r1, _080DE6F4 @ =0xFFFFB000\n\
	adds r0, r0, r1\n\
	ldr r1, [r6, #0x58]\n\
	bl FUN_08009f6c\n\
	ldr r2, _080DE6F8 @ =0x00000101\n\
	adds r0, r0, r2\n\
	str r0, [r6, #0x58]\n\
	ldr r4, _080DE6FC @ =0x00000C08\n\
	ldr r1, _080DE700 @ =gStaticMotionGraphics\n\
	adds r0, r4, r1\n\
	ldr r1, _080DE704 @ =wStaticGraphicTilenums\n\
	movs r5, #0x9a\n\
	lsls r5, r5, #1\n\
	adds r1, r1, r5\n\
	ldrh r1, [r1]\n\
	ldrh r2, [r0, #6]\n\
	lsrs r2, r2, #6\n\
	subs r1, r1, r2\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r1, r1, r2\n\
	bl LoadGraphic\n\
	ldr r0, _080DE708 @ =gStaticMotionGraphics+12\n\
	adds r4, r4, r0\n\
	ldr r0, _080DE70C @ =wStaticMotionPalIDs\n\
	adds r0, r0, r5\n\
	ldrh r1, [r0]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
	ldr r1, _080DE710 @ =gSolidFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	adds r0, r6, #0\n\
	bl Solid45_Update\n\
_080DE6E2:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080DE6E8: .4byte sSize\n\
_080DE6EC: .4byte 0x00002001\n\
_080DE6F0: .4byte 0xFFFFF800\n\
_080DE6F4: .4byte 0xFFFFB000\n\
_080DE6F8: .4byte 0x00000101\n\
_080DE6FC: .4byte 0x00000C08\n\
_080DE700: .4byte gStaticMotionGraphics\n\
_080DE704: .4byte wStaticGraphicTilenums\n\
_080DE708: .4byte gStaticMotionGraphics+12\n\
_080DE70C: .4byte wStaticMotionPalIDs\n\
_080DE710: .4byte gSolidFnTable\n\
 .syntax divided\n");
}

static void Solid45_Update(struct Solid* p) {
  UpdateMotionGraphic(&p->s);
  if (gOverworld.state[0] != 0) {
    if ((p->s).mode[1] == 0) {
      AppendQuake(1, &(p->s).coord);
      SetMotion(&p->s, 0x9A00);
      (p->s).work[2] = 0xA;
      (p->s).mode[1]++;
    }
    if ((p->s).d.x <= 0xFF) {
      (p->s).d.x += 8;
    }
    (p->s).coord.x -= (p->s).d.x;
    if ((p->s).work[2] != 0) {
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        gOverworld.state[0] = 2;
      }
    }
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      Solid45_Die(p);
    }
  }
}

void Solid45_Die(struct Solid* p) {
  (p->s).flags &= ~DISPLAY;
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

static const struct Rect sSize = {PIXEL(0), PIXEL(7), PIXEL(128), PIXEL(16)};
