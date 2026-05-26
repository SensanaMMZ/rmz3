	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cubitMode0
cubitMode0: @ 0x08052B4C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08052B5C
	cmp r0, #1
	beq _08052B72
	b _08052B8C
_08052B5C:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08052B94 @ =0x0000B002
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08052B72:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _08052B8C
	movs r0, #0
	strb r2, [r4, #0xd]
	strb r0, [r4, #0xe]
_08052B8C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08052B94: .4byte 0x0000B002
