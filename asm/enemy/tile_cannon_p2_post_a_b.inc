	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start TileCannon_Init
TileCannon_Init: @ 0x08078248
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r1, _080782B8 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r1, _080782BC @ =0x08367540
	ldrb r0, [r6, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r6, #0xd]
	ldrb r0, [r6, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0x10]
	cmp r1, #2
	beq _080782C4
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080782C0 @ =0x08367460
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x58]
	movs r1, #0x90
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r6, #0x58]
	b _08078324
	.align 2, 0
_080782B8: .4byte gEnemyFnTable
_080782BC: .4byte 0x08367540
_080782C0: .4byte 0x08367460
_080782C4:
	ldr r0, _080782F8 @ =gSystemSavedataManager
	ldrb r0, [r0, #0x15]
	ands r1, r0
	cmp r1, #0
	beq _08078304
	ldr r0, _080782FC @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _08078304
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08078300 @ =0x08367508
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xa
	b _0807831C
	.align 2, 0
_080782F8: .4byte gSystemSavedataManager
_080782FC: .4byte gCurStory
_08078300: .4byte 0x08367508
_08078304:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08078348 @ =0x08367508
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #6
_0807831C:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
_08078324:
	ldr r0, _0807834C @ =FUN_08078170
	str r0, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	str r0, [r1]
	movs r0, #0x28
	strb r0, [r6, #0x12]
	subs r1, #0x8f
	movs r0, #0x1f
	strb r0, [r1]
	adds r0, r6, #0
	bl TileCannon_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08078348: .4byte 0x08367508
_0807834C: .4byte FUN_08078170


