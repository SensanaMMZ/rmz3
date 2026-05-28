	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080607bc
FUN_080607bc: @ 0x080607BC
	push {r4, lr}
	adds r4, r0, #0
	adds r4, #0xb4
	strb r1, [r4]
	ldr r4, _080607E0 @ =sMotions
	lsls r1, r1, #1
	adds r1, r1, r4
	ldrh r1, [r1]
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	lsls r3, r3, #0x10
	lsrs r3, r3, #0x10
	bl GotoMotion
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080607E0: .4byte sMotions
