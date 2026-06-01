	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0800f894
FUN_0800f894: @ 0x0800F894
	ldr r1, _0800F8A0 @ =gOverworld
	ldr r2, _0800F8A4 @ =0x0002D038
	adds r1, r1, r2
	str r0, [r1]
	bx lr
	.align 2, 0
_0800F8A0: .4byte gOverworld
_0800F8A4: .4byte 0x0002D038
