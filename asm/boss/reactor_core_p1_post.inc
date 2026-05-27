	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start ReactorCore_Disappear
ReactorCore_Disappear: @ 0x08061A58
	push {r4, lr}
	adds r4, r0, #0
	movs r0, #0xcb
	bl ClearBlink
	movs r0, #0xcc
	bl ClearBlink
	adds r0, r4, #0
	bl DeleteBoss
	pop {r4}
	pop {r0}
	bx r0

