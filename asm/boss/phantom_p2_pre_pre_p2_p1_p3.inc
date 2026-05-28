	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f9a0
FUN_0805f9a0: @ 0x0805F9A0
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r5, #4
	ands r0, r5
	cmp r0, #0
	beq _0805F9C8
	ldr r0, _0805F9C4 @ =0xFFFFFD00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0xd
	bl FUN_080607a0
	movs r0, #3
	strb r0, [r4, #0xf]
	b _0805F9D6
	.align 2, 0
_0805F9C4: .4byte 0xFFFFFD00
_0805F9C8:
	adds r0, r4, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F9D6
	strb r5, [r4, #0xf]
_0805F9D6:
	pop {r4, r5}
	pop {r0}
	bx r0
