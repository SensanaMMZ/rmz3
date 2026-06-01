	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08035330
FUN_08035330: @ 0x08035330
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08035340
	cmp r0, #1
	beq _08035352
	b _08035370
_08035340:
	ldr r1, _08035378 @ =0x0000BE21
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08035352:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08035368
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08035370
_08035368:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08035370:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08035378: .4byte 0x0000BE21
