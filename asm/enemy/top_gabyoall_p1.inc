	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Enemy14_Update
Enemy14_Update: @ 0x0806F448
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x11]
	cmp r0, #2
	beq _0806F47C
	ldr r0, _0806F474 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0806F494
	ldr r1, _0806F478 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	b _0806F58E
	.align 2, 0
_0806F474: .4byte gCurStory
_0806F478: .4byte gEnemyFnTable
_0806F47C:
	ldr r0, _0806F4B4 @ =pZero2
	ldr r0, [r0]
	cmp r0, #0
	beq _0806F494
	ldr r1, _0806F4B8 @ =0x00000216
	adds r0, r0, r1
	ldrh r1, [r0]
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _0806F58E
_0806F494:
	adds r0, r5, #0
	adds r0, #0xc2
	ldrb r0, [r0]
	cmp r0, #0
	beq _0806F4C0
	ldr r1, _0806F4BC @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _0806F58E
	.align 2, 0
_0806F4B4: .4byte pZero2
_0806F4B8: .4byte 0x00000216
_0806F4BC: .4byte gEnemyFnTable
_0806F4C0:
	ldrb r1, [r5, #0x1e]
	lsls r1, r1, #8
	adds r0, r5, #0
	adds r0, #0x70
	ldrb r0, [r0]
	orrs r1, r0
	ldr r0, _0806F564 @ =0x00001503
	adds r6, r5, #0
	adds r6, #0xbc
	cmp r1, r0
	beq _0806F51C
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0806F51C
	ldr r0, [r6]
	cmp r0, #0
	bne _0806F522
	ldrb r2, [r5, #0x10]
	lsls r2, r2, #3
	ldr r0, _0806F568 @ =0x083669D0
	adds r2, r2, r0
	movs r0, #0
	adds r1, r5, #0
	bl ApplyElementEffect
	str r0, [r6]
	cmp r0, #0
	beq _0806F574
	adds r0, r5, #0
	adds r0, #0x74
	ldrb r1, [r5, #0x10]
	movs r2, #2
	ands r2, r1
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0806F56C @ =0x08366988
	adds r1, r1, r2
	bl SetDDP
_0806F51C:
	ldr r0, [r6]
	cmp r0, #0
	beq _0806F574
_0806F522:
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r6]
	bl isKilled
	cmp r0, #0
	beq _0806F58E
	movs r4, #0
	str r4, [r6]
	adds r0, r5, #0
	adds r0, #0x74
	ldrb r1, [r5, #0x10]
	movs r2, #2
	ands r2, r1
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0806F570 @ =0x08366970
	adds r1, r1, r2
	bl SetDDP
	strb r4, [r5, #0xd]
	strb r4, [r5, #0xe]
	b _0806F58E
	.align 2, 0
_0806F564: .4byte 0x00001503
_0806F568: .4byte 0x083669D0
_0806F56C: .4byte 0x08366988
_0806F570: .4byte 0x08366970
_0806F574:
	adds r0, r5, #0
	bl IsFrozen
	cmp r0, #0
	bne _0806F58E
	ldr r0, _0806F594 @ =0x08366960
	ldrb r1, [r5, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r5, #0
	bl _call_via_r1
_0806F58E:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0806F594: .4byte 0x08366960

