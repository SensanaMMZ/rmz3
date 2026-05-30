	.include "asm/macros.inc"

	.syntax unified

	.text

ice_080b9a0c: @ 0x080B9A0C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080B9A1C
	cmp r0, #1
	beq _080B9A2A
	b _080B9A4C
_080B9A1C:
	ldr r1, _080B9A54 @ =0x00001109
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B9A2A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080B9A4C
	ldr r1, _080B9A58 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B9A4C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B9A54: .4byte 0x00001109
_080B9A58: .4byte gVFXFnTable
