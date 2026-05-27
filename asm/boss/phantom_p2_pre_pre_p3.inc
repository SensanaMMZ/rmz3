	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805fa28
FUN_0805fa28: @ 0x0805FA28
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805FA40 @ =sCollisions
	bl SetDDP
	movs r0, #1
	strh r0, [r4, #0xe]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805FA40: .4byte sCollisions
