	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08091174
FUN_08091174: @ 0x08091174
	push {lr}
	adds r1, r0, #0
	ldrb r0, [r1, #0xe]
	cmp r0, #0
	bne _08091182
	movs r0, #1
	strb r0, [r1, #0xe]
_08091182:
	pop {r0}
	bx r0
	.align 2, 0
