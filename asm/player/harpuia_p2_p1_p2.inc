	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080353a8
FUN_080353a8: @ 0x080353A8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080353B8
	cmp r0, #1
	beq _080353D0
	b _080353D6
_080353B8:
	ldr r1, _080353DC @ =0x0000BE21
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080353E0 @ =0x0835EAF8
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080353D0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080353D6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080353DC: .4byte 0x0000BE21
_080353E0: .4byte 0x0835EAF8
