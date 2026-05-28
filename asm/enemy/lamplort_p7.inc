	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806cb5c
FUN_0806cb5c: @ 0x0806CB5C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0806CB6C
	cmp r0, #1
	beq _0806CBD2
	b _0806CBFA
_0806CB6C:
	ldr r1, _0806CB90 @ =0x00001901
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806CB94 @ =0x08366590
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r2, [r0]
	cmp r2, #0
	beq _0806CB98
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0806CB9E
	.align 2, 0
_0806CB90: .4byte 0x00001901
_0806CB94: .4byte 0x08366590
_0806CB98:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806CB9E:
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
	ldr r1, [r4, #0x2c]
	adds r1, #0xb4
	ldr r0, [r1]
	movs r2, #2
	orrs r0, r2
	str r0, [r1]
	movs r0, #8
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806CBD2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0806CBFA
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0806CBF2
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0806CBFA
_0806CBF2:
	movs r1, #0
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806CBFA:
	pop {r4}
	pop {r0}
	bx r0
