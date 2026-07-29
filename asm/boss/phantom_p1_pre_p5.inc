	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f284
FUN_0805f284: @ 0x0805F284
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F2C8 @ =sCollisions
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	ldr r0, [r4, #0x5c]
	movs r1, #0xf0
	lsls r1, r1, #2
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r1, _0805F2CC @ =0x00006CC0
	muls r0, r1, r0
	movs r1, #0x1e
	bl __divsi3
	adds r1, r0, #0
	adds r0, r4, #0
	bl FUN_08060864
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F2D0
	adds r0, r4, #0
	movs r1, #2
	movs r2, #0
	movs r3, #2
	bl FUN_080607bc
	b _0805F2D8
	.align 2, 0
_0805F2C8: .4byte sCollisions
_0805F2CC: .4byte 0x00006CC0
_0805F2D0:
	adds r0, r4, #0
	movs r1, #2
	bl FUN_080607a0
_0805F2D8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
