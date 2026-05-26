	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Solid32_Disappear
Solid32_Disappear: @ 0x080DBFFC
	push {r4, lr}
	adds r4, r0, #0
	movs r0, #0xbd
	bl ClearBlink
	movs r0, #0xbe
	bl ClearBlink
	adds r0, r4, #0
	bl DeleteSolid
	pop {r4}
	pop {r0}
	bx r0

