	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_080e5300
FUN_080e5300: @ 0x080E5300
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	adds r7, r0, #0
	adds r0, #0xb4
	ldr r0, [r0]
	mov sb, r0
	adds r0, r7, #0
	adds r0, #0xb8
	ldr r0, [r0]
	mov r8, r0
	movs r1, #0x80
	lsls r1, r1, #2
	adds r0, r7, #0
	bl SetMotion
	adds r6, r7, #0
	adds r6, #0x4c
	movs r0, #0
	strb r0, [r6]
	movs r1, #0x4a
	adds r1, r1, r7
	mov sl, r1
	ldrb r1, [r1]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	mov r2, sl
	strb r0, [r2]
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	bl UpdateMotionGraphic
	bl GetBeeAtkBoost
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r7, #0xa]
	movs r2, #4
	orrs r1, r2
	strb r1, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #4
	ldr r0, _080E53DC @ =0x08371E18
	adds r1, r1, r0
	adds r5, r7, #0
	adds r5, #0x54
	adds r0, r4, #0
	adds r2, r5, #0
	movs r3, #1
	bl InitBody
	str r7, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
	mov r2, r8
	ldr r0, [r2, #0x54]
	ldr r1, [r2, #0x58]
	str r0, [r7, #0x54]
	str r1, [r7, #0x58]
	adds r0, r5, #0
	bl FUN_080e1608
	adds r1, r0, #0
	str r1, [r7, #0x2c]
	cmp r1, #0
	beq _080E53E4
	mov r0, sp
	bl FUN_080e16c4
	ldr r2, [sp]
	ldr r3, [sp, #4]
	ldr r0, [r7, #0x54]
	subs r0, r2, r0
	ldr r1, [r7, #0x58]
	subs r1, r3, r1
	bl CalcAngle
	adds r2, r7, #0
	adds r2, #0xbc
	strb r0, [r2]
	ldr r3, _080E53E0 @ =gSineTable
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r1, [r0, r4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	str r0, [r7, #0x5c]
	ldrb r0, [r2]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	b _080E5494
	.align 2, 0
_080E53DC: .4byte sCollisions
_080E53E0: .4byte gSineTable
_080E53E4:
	mov r4, sb
	ldrb r0, [r4, #0xd]
	cmp r0, #2
	bne _080E547C
	ldrb r1, [r4, #0x1e]
	lsls r1, r1, #8
	mov r0, sb
	adds r0, #0x70
	ldrb r0, [r0]
	orrs r0, r1
	movs r1, #0xa0
	lsls r1, r1, #3
	cmp r0, r1
	bne _080E5440
	mov r0, sb
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #2
	ble _080E547C
	ldrb r0, [r7, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	strb r0, [r6]
	ldrb r1, [r7, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	lsls r3, r1, #4
	mov r0, sl
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, sl
	strb r0, [r2]
	cmp r1, #0
	beq _080E5474
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080E547A
_080E5440:
	mov r4, sb
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	strb r0, [r6]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	lsls r3, r1, #4
	mov r0, sl
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, sl
	strb r0, [r2]
	cmp r1, #0
	beq _080E5474
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080E547A
_080E5474:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080E547A:
	strb r0, [r7, #0xa]
_080E547C:
	mov r4, sb
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080E548E
	movs r0, #0xc0
	lsls r0, r0, #3
	b _080E5490
_080E548E:
	ldr r0, _080E54A8 @ =0xFFFFFA00
_080E5490:
	str r0, [r7, #0x5c]
	movs r0, #0
_080E5494:
	str r0, [r7, #0x60]
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E54A8: .4byte 0xFFFFFA00
