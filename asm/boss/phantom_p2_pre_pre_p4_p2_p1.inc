	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805fadc
FUN_0805fadc: @ 0x0805FADC
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x5c]
	bl FUN_08060864
	adds r0, r4, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805FAF6
	movs r0, #3
	strb r0, [r4, #0xf]
_0805FAF6:
	pop {r4}
	pop {r0}
	bx r0
