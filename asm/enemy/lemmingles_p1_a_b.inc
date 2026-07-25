	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Lemmingles_Init
Lemmingles_Init: @ 0x0806E750
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r1, _0806E7C8 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	ldr r1, _0806E7CC @ =0x0836691C
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0xd]
	ldrb r0, [r5, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldr r0, _0806E7D0 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x14]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0806E7DC
	ldr r0, _0806E7D4 @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	bne _0806E7DC
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _0806E7D8 @ =0x0836686C
	adds r2, r5, #0
	adds r2, #0x54
	ldrb r0, [r5, #0x10]
	movs r3, #0xc
	adds r4, r5, #0
	adds r4, #0x74
	cmp r0, #1
	bhi _0806E7BC
	movs r3, #8
_0806E7BC:
	adds r0, r4, #0
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	b _0806E804
	.align 2, 0
_0806E7C8: .4byte gEnemyFnTable
_0806E7CC: .4byte 0x0836691C
_0806E7D0: .4byte gSystemSavedataManager
_0806E7D4: .4byte gCurStory
_0806E7D8: .4byte 0x0836686C
_0806E7DC:
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r1, r0
	strb r1, [r5, #0xa]
	ldr r1, _0806E824 @ =0x0836686C
	adds r2, r5, #0
	adds r2, #0x54
	ldrb r0, [r5, #0x10]
	movs r3, #8
	adds r4, r5, #0
	adds r4, #0x74
	cmp r0, #1
	bhi _0806E7F8
	movs r3, #4
_0806E7F8:
	adds r0, r4, #0
	bl InitBody
	str r5, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
_0806E804:
	ldr r0, _0806E828 @ =onCollision
	str r0, [r4, #0x24]
	adds r1, r5, #0
	adds r1, #0xb4
	movs r0, #0
	str r0, [r1]
	adds r1, #8
	movs r0, #1
	strb r0, [r1]
	adds r0, r5, #0
	bl Lemmingles_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0806E824: .4byte 0x0836686C
_0806E828: .4byte onCollision


