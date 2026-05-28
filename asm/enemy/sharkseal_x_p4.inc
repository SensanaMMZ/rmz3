	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start sharksealxMode2
sharksealxMode2: @ 0x080708E0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080708F0
	cmp r5, #1
	beq _0807094E
	b _0807098A
_080708F0:
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0807091C @ =0x08366A44
	bl SetDDP
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r2, [r0]
	cmp r2, #0
	beq _08070920
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08070926
	.align 2, 0
_0807091C: .4byte 0x08366A44
_08070920:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08070926:
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
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807094E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x60]
	adds r0, #0x20
	str r0, [r4, #0x60]
	movs r1, #0x80
	lsls r1, r1, #1
	cmp r0, r1
	ble _08070964
	str r1, [r4, #0x60]
_08070964:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl forceWaterLanding
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08070982
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807098A
_08070982:
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0807098A:
	pop {r4, r5}
	pop {r0}
	bx r0
