	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805d1c4
FUN_0805d1c4: @ 0x0805D1C4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0805D1E0
	ldr r1, _0805D20C @ =0x0000B50C
	movs r2, #2
	movs r3, #5
	bl GotoMotion
	str r5, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805D1E0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805D204
	movs r1, #0
	movs r0, #0x1b
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805D204:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805D20C: .4byte 0x0000B50C

