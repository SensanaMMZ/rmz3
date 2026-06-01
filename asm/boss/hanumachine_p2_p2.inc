	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805d594
FUN_0805d594: @ 0x0805D594
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, [r4, #0x54]
	adds r0, r0, r5
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0
	bne _0805D5C4
	ldr r0, [r4, #0x54]
	adds r0, r0, r5
	ldr r1, [r4, #0x58]
	ldr r2, _0805D5CC @ =0xFFFFE000
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0
	bne _0805D5C4
	movs r0, #0
_0805D5C4:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_0805D5CC: .4byte 0xFFFFE000
