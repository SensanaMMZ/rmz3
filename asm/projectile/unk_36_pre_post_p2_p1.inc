	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ad698
FUN_080ad698: @ 0x080AD698
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	movs r1, #0xd4
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080AD76C @ =0x0836C8E0
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r4, _080AD770 @ =gSineTable
	ldrb r0, [r6, #0x11]
	adds r3, r0, #0
	adds r3, #0xc0
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080AD6F2
	adds r0, #0xff
_080AD6F2:
	asrs r2, r0, #8
	str r2, [r6, #0x5c]
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080AD70C
	adds r0, #0xff
_080AD70C:
	asrs r1, r0, #8
	str r1, [r6, #0x60]
	lsls r0, r2, #3
	ldr r2, [r6, #0x54]
	adds r2, r2, r0
	str r2, [r6, #0x54]
	lsls r1, r1, #3
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xb4
	str r2, [r0]
	adds r1, r6, #0
	adds r1, #0xb8
	ldr r0, [r6, #0x58]
	str r0, [r1]
	adds r0, r6, #0
	movs r1, #1
	movs r2, #3
	bl FUN_080ad5f0
	adds r0, r6, #0
	movs r1, #1
	movs r2, #6
	bl FUN_080ad5f0
	adds r0, r6, #0
	movs r1, #1
	movs r2, #9
	bl FUN_080ad5f0
	ldr r1, _080AD774 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl Projectile36_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080AD76C: .4byte 0x0836C8E0
_080AD770: .4byte gSineTable
_080AD774: .4byte gProjectileFnTable

	thumb_func_start FUN_080ad778
FUN_080ad778: @ 0x080AD778
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AD7C4
	ldr r1, _080AD7CC @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
_080AD7C4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AD7CC: .4byte gProjectileFnTable

