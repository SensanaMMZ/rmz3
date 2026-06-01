	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a9b90
FUN_080a9b90: @ 0x080A9B90
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldr r1, _080A9BD8 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r7, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	movs r1, #0xbe
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A9BDC
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A9BE2
	.align 2, 0
_080A9BD8: .4byte gProjectileFnTable
_080A9BDC:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A9BE2:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	beq _080A9C20
	ldr r0, [r6, #0x54]
	movs r1, #0xf8
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r0, #0x80
	str r0, [r6, #0x5c]
	movs r0, #0x7f
	strb r0, [r6, #0x12]
	b _080A9C30
_080A9C20:
	ldr r0, [r6, #0x54]
	ldr r2, _080A9C7C @ =0xFFFFE100
	adds r0, r0, r2
	str r0, [r6, #0x54]
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r6, #0x5c]
	strb r1, [r6, #0x12]
_080A9C30:
	ldr r0, [r6, #0x58]
	ldr r1, _080A9C80 @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r5, #0
	str r5, [r6, #0x60]
	strb r5, [r6, #0x13]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A9C84 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb4
	ldr r0, [r6, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r6, #0x58]
	str r0, [r1]
	movs r0, #1
	strb r0, [r6, #0xe]
	adds r0, r6, #0
	bl Projectile28_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A9C7C: .4byte 0xFFFFE100
_080A9C80: .4byte 0xFFFFE800
_080A9C84: .4byte sCollisions

	thumb_func_start FUN_080a9c88
FUN_080a9c88: @ 0x080A9C88
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	bl UpdateMotionGraphic
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A9CEC
	adds r5, r6, #0
	adds r5, #0xb4
	ldr r4, _080A9CE8 @ =gSineTable
	ldrb r2, [r6, #0x12]
	adds r0, r2, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r3, #0
	ldrsh r1, [r0, r3]
	movs r0, #0xb
	muls r1, r0, r1
	ldr r0, [r5]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r3, r6, #0
	adds r3, #0xb8
	ldrb r0, [r6, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r4, #0
	ldrsh r1, [r0, r4]
	movs r0, #0x16
	muls r1, r0, r1
	ldr r0, [r3]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r2, #0x10
	strb r2, [r6, #0x12]
	ldr r0, [r6, #0x5c]
	adds r0, #8
	str r0, [r6, #0x5c]
	movs r1, #0x80
	lsls r1, r1, #2
	cmp r0, r1
	ble _080A9D36
	b _080A9D34
	.align 2, 0
_080A9CE8: .4byte gSineTable
_080A9CEC:
	adds r5, r6, #0
	adds r5, #0xb4
	ldr r4, _080A9D7C @ =gSineTable
	ldrb r2, [r6, #0x12]
	adds r0, r2, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r3, #0
	ldrsh r1, [r0, r3]
	movs r0, #0xb
	muls r1, r0, r1
	ldr r0, [r5]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r3, r6, #0
	adds r3, #0xb8
	ldrb r0, [r6, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r4, #0
	ldrsh r1, [r0, r4]
	movs r0, #0x16
	muls r1, r0, r1
	ldr r0, [r3]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	subs r2, #0x10
	strb r2, [r6, #0x12]
	ldr r0, [r6, #0x5c]
	subs r0, #8
	str r0, [r6, #0x5c]
	ldr r1, _080A9D80 @ =0xFFFFFE00
	cmp r0, r1
	bge _080A9D36
_080A9D34:
	str r1, [r6, #0x5c]
_080A9D36:
	ldrb r1, [r6, #0x13]
	adds r0, r1, #1
	strb r0, [r6, #0x13]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	bne _080A9D4E
	adds r0, r6, #0
	movs r1, #6
	movs r2, #0
	bl FUN_080a90a0
_080A9D4E:
	ldr r0, [r5]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r5]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080A9D76
	ldr r1, _080A9D84 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080A9D76:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A9D7C: .4byte gSineTable
_080A9D80: .4byte 0xFFFFFE00
_080A9D84: .4byte gProjectileFnTable
