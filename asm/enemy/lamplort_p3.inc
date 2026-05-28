	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806c828
FUN_0806c828: @ 0x0806C828
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0806C84C
	cmp r0, #1
	bgt _0806C83C
	cmp r0, #0
	beq _0806C842
	b _0806C8C0
_0806C83C:
	cmp r0, #2
	beq _0806C8A2
	b _0806C8C0
_0806C842:
	movs r0, #0x28
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806C84C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806C874 @ =0x08366590
	bl SetDDP
	movs r1, #0xc8
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r2, [r0]
	cmp r2, #0
	beq _0806C878
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0806C87E
	.align 2, 0
_0806C874: .4byte 0x08366590
_0806C878:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806C87E:
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
_0806C8A2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0806C8B8
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0806C8C0
_0806C8B8:
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806C8C0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
