	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080be974
FUN_080be974: @ 0x080BE974
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080BE9A6
	cmp r0, #1
	bgt _080BE988
	cmp r0, #0
	beq _080BE992
	b _080BEA1A
_080BE988:
	cmp r0, #2
	beq _080BE9D4
	cmp r0, #3
	beq _080BE9F8
	b _080BEA1A
_080BE992:
	movs r1, #0xf4
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x14
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BE9A6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0x12]
	adds r0, r1, #0
	adds r0, #0xff
	strb r0, [r4, #0x12]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080BE9C4
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080BE9CA
_080BE9C4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BE9CA:
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080BEA1A
	b _080BE9EA
_080BE9D4:
	ldr r1, _080BE9F4 @ =0x00003D01
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x62
	bl PlaySound
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
_080BE9EA:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080BEA1A
	.align 2, 0
_080BE9F4: .4byte 0x00003D01
_080BE9F8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080BEA1A
	ldr r1, _080BEA20 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080BEA1A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BEA20: .4byte gVFXFnTable

