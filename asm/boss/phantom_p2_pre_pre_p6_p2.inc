	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080600e0
FUN_080600e0: @ 0x080600E0
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _080600F4
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_080600F4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
