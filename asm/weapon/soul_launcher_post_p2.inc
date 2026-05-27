	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0803b4e8
FUN_0803b4e8: @ 0x0803B4E8
	push {lr}
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _0803B500 @ =0x0000800F
	cmp r1, r0
	bne _0803B4FA
	movs r1, #0
_0803B4FA:
	adds r0, r1, #0
	pop {r1}
	bx r1
	.align 2, 0
_0803B500: .4byte 0x0000800F
