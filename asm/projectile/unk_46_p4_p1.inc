	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b2384
FUN_080b2384: @ 0x080B2384
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080B241C @ =0x0000E902
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0x11]
	adds r1, #5
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r4, #0
	bl ForceEntityPalette
	movs r2, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r5, #1
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #5
	adds r0, #8
	lsls r0, r0, #8
	str r0, [r4, #0x54]
	movs r0, #0xf0
	lsls r0, r0, #7
	str r0, [r4, #0x58]
	ldr r1, _080B2420 @ =0x00000DE9
	adds r0, r6, r1
	ldrb r1, [r4, #0x11]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r4, #0x12]
	ldrb r3, [r4, #0x11]
	adds r0, r6, #0
	adds r1, r4, #0
	movs r2, #2
	bl FUN_080b2270
	str r0, [r4, #0x2c]
	ldr r1, _080B2424 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r5, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl FUN_080b22e0
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B241C: .4byte 0x0000E902
_080B2420: .4byte 0x00000DE9
_080B2424: .4byte gProjectileFnTable
