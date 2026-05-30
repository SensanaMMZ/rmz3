	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b97f4
FUN_080b97f4: @ 0x080B97F4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080B9804
	cmp r0, #1
	beq _080B9818
	b _080B985A
_080B9804:
	movs r1, #0xe0
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x28
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B9818:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080B9830
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080B9836
_080B9830:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080B9836:
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080B985A
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B985A
	ldr r1, _080B9860 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B985A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B9860: .4byte gVFXFnTable
