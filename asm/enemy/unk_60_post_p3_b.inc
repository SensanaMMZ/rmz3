	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08092b54
FUN_08092b54: @ 0x08092B54
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08092B64
	cmp r0, #1
	beq _08092B68
	b _08092B94
_08092B64:
	movs r0, #1
	strb r0, [r5, #0xe]
_08092B68:
	ldr r0, [r5, #0x28]
	ldr r0, [r0, #0x18]
	ldrb r1, [r0, #9]
	movs r6, #1
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	beq _08092B94
	ldrb r1, [r5, #0xa]
	movs r4, #0
	movs r0, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08092B9C @ =0x0000B602
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	strb r6, [r5, #0xd]
	strb r4, [r5, #0xe]
_08092B94:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08092B9C: .4byte 0x0000B602
