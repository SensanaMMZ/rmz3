	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f6c8
FUN_0805f6c8: @ 0x0805F6C8
	push {lr}
	adds r1, r0, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0805F6DC
	movs r0, #1
	strb r0, [r1, #0xf]
_0805F6DC:
	pop {r0}
	bx r0
