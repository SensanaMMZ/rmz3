	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806cac8
FUN_0806cac8: @ 0x0806CAC8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0806CAD8
	cmp r0, #1
	beq _0806CB3A
	b _0806CB52
_0806CAD8:
	ldr r1, _0806CB08 @ =0x00001908
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806CB0C @ =0x08366590
	bl SetDDP
	ldr r1, [r4, #0x2c]
	adds r1, #0xb4
	ldr r0, [r1]
	movs r2, #2
	orrs r0, r2
	str r0, [r1]
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r2, [r0]
	cmp r2, #0
	beq _0806CB10
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0806CB16
	.align 2, 0
_0806CB08: .4byte 0x00001908
_0806CB0C: .4byte 0x08366590
_0806CB10:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806CB16:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806CB3A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0806CB52
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806CB52:
	pop {r4}
	pop {r0}
	bx r0
