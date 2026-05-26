	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start blazinMode8
blazinMode8: @ 0x0803F9AC
	push {lr}
	adds r1, r0, #0
	ldrb r0, [r1, #0xe]
	cmp r0, #0
	bne _0803F9BA
	movs r0, #1
	strb r0, [r1, #0xe]
_0803F9BA:
	pop {r0}
	bx r0
	.align 2, 0
