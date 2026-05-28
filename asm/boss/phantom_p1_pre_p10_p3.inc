	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f738
FUN_0805f738: @ 0x0805F738
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080609a4
	lsls r0, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	ble _0805F764
	movs r0, #3
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0xb7
	strb r1, [r0]
	adds r1, #0x12
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r0, r4, #0
	bl FUN_08060a48
	adds r0, r4, #0
	bl FUN_0805f76c
_0805F764:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
