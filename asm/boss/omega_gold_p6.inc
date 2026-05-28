	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805b744
FUN_0805b744: @ 0x0805B744
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #0xe]
	cmp r2, #1
	beq _0805B78E
	cmp r2, #1
	bgt _0805B758
	cmp r2, #0
	beq _0805B75E
	b _0805B7E6
_0805B758:
	cmp r2, #2
	beq _0805B7C2
	b _0805B7E6
_0805B75E:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	str r2, [r4, #0x60]
	str r2, [r4, #0x5c]
	movs r0, #0xff
	strb r0, [r4, #0x12]
	movs r0, #1
	rsbs r0, r0, #0
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805B78E:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0805B79A
	subs r0, #1
	strb r0, [r4, #0x12]
	b _0805B7B4
_0805B79A:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _0805B7B4
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805B7B4
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805B7B4:
	movs r0, #0xb
	bl UpdateBlinkMotionState
	adds r0, r4, #0
	bl floatGoldOmega1
	b _0805B7E6
_0805B7C2:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0805B7D2
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805B7DA
_0805B7D2:
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805B7DA:
	movs r0, #0xb
	bl UpdateBlinkMotionState
	adds r0, r4, #0
	bl floatGoldOmega1
_0805B7E6:
	pop {r4}
	pop {r0}
	bx r0
