	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f9f4
FUN_0805f9f4: @ 0x0805F9F4
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _0805FA08
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_0805FA08:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
