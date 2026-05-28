	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f6fc
FUN_0805f6fc: @ 0x0805F6FC
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0805F716
	movs r0, #0xfc
	bl PlaySound
	movs r0, #3
	strb r0, [r4, #0xf]
_0805F716:
	pop {r4}
	pop {r0}
	bx r0
