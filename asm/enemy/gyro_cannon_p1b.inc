	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806d470
FUN_0806d470: @ 0x0806D470
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r2, [r4, #0xe]
	cmp r2, #0
	bne _0806D508
	adds r0, #0xb4
	ldrb r1, [r0, #0xa]
	adds r6, r0, #0
	cmp r1, #0
	beq _0806D48E
	strb r2, [r4, #0xd]
	adds r5, r4, #0
	adds r5, #0x8c
	b _0806D4E8
_0806D48E:
	adds r1, r4, #0
	adds r1, #0x8c
	ldr r2, [r1]
	movs r0, #0x80
	lsls r0, r0, #9
	ands r2, r0
	adds r5, r1, #0
	cmp r2, #0
	beq _0806D4E6
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0806D4C8 @ =0xFFFFEC00
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	ldrb r3, [r6, #8]
	movs r0, #0
	mov r1, sp
	bl FUN_080b2b40
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _0806D4CC
	movs r0, #1
_0806D4C2:
	strb r0, [r4, #0xd]
	b _0806D4E8
	.align 2, 0
_0806D4C8: .4byte 0xFFFFEC00
_0806D4CC:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0xb0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0
	beq _0806D4C2
	movs r0, #2
	b _0806D4C2
_0806D4E6:
	strb r2, [r4, #0xd]
_0806D4E8:
	movs r1, #0
	str r1, [r5]
	adds r0, r4, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #1
	strb r0, [r6, #9]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806D508:
	ldr r0, _0806D520 @ =0x08366694
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0806D520: .4byte sUpdates2

	thumb_func_start FUN_0806d524
FUN_0806d524: @ 0x0806D524
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0806D568 @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0806D5F4
	ldr r7, _0806D56C @ =sSlashedEnemies
	adds r2, r4, #0
	adds r2, #0xb4
	ldrb r5, [r2, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	adds r6, r2, #0
	cmp r0, #0
	beq _0806D570
	orrs r3, r5
	b _0806D572
	.align 2, 0
_0806D568: .4byte 0xFFFFEE00
_0806D56C: .4byte sSlashedEnemies
_0806D570:
	adds r3, r5, #0
_0806D572:
	mov r0, sp
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r5, sp
	ldr r7, _0806D594 @ =sSlashedEnemies
	ldrb r2, [r6, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806D598
	orrs r3, r2
	b _0806D59A
	.align 2, 0
_0806D594: .4byte sSlashedEnemies
_0806D598:
	adds r3, r2, #0
_0806D59A:
	adds r0, r5, #0
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r5, sp
	ldr r7, _0806D5BC @ =0x0836673C
	ldrb r2, [r6, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806D5C0
	orrs r3, r2
	b _0806D5C2
	.align 2, 0
_0806D5BC: .4byte sSlashedEnemies+(28*1)
_0806D5C0:
	adds r3, r2, #0
_0806D5C2:
	adds r0, r5, #0
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r5, sp
	ldr r7, _0806D5E4 @ =0x0836673C
	ldrb r2, [r6, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806D5E8
	orrs r3, r2
	b _0806D5EA
	.align 2, 0
_0806D5E4: .4byte sSlashedEnemies+(28*1)
_0806D5E8:
	adds r3, r2, #0
_0806D5EA:
	adds r0, r5, #0
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
_0806D5F4:
	movs r0, #0x2a
	bl PlaySound
	ldr r1, _0806D614 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806D614: .4byte gEnemyFnTable
