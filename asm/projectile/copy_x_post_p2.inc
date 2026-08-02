	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start initCopyXSlidingSonicBoom
initCopyXSlidingSonicBoom: @ 0x080A81D0
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldr r5, [r7, #0x28]
	ldr r1, _080A8220 @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl InitNonAffineMotion
	ldrb r1, [r7, #0xa]
	movs r0, #1
	movs r6, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	movs r1, #0xbc
	lsls r1, r1, #7
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A8224
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A822A
	.align 2, 0
_080A8220: .4byte gProjectileFnTable
_080A8224:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A822A:
	strb r0, [r7, #0xa]
	movs r5, #1
	adds r1, r5, #0
	ands r1, r2
	adds r0, r7, #0
	adds r0, #0x4c
	movs r6, #0
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r1, [r7, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r1, _080A827C @ =0x0836BEF4
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r7, [r4, #0x2c]
	str r6, [r4, #0x24]
	movs r0, #0x28
	strb r0, [r7, #0x12]
	strb r5, [r7, #0xe]
	adds r0, r7, #0
	bl CopyXProjectile_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A827C: .4byte 0x0836BEF4
