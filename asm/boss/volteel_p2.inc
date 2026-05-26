	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start volteelMode0
volteelMode0: @ 0x080438A8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080438B8
	cmp r0, #1
	beq _080438D0
	b _080438EA
_080438B8:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	movs r1, #0xa5
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080438D0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _080438EA
	movs r0, #0
	strb r2, [r4, #0xd]
	strb r0, [r4, #0xe]
_080438EA:
	pop {r4}
	pop {r0}
	bx r0
