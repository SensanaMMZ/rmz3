	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08016080
FUN_08016080: @ 0x08016080
	ldr r1, _0801608C @ =gOverworld
	ldr r2, _08016090 @ =0x0002D034
	adds r1, r1, r2
	str r0, [r1]
	bx lr
	.align 2, 0
_0801608C: .4byte gOverworld
_08016090: .4byte 0x0002D034

