	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805b7f0
FUN_0805b7f0: @ 0x0805B7F0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #0xe]
	cmp r2, #0
	beq _0805B800
	cmp r2, #1
	beq _0805B840
	b _0805B86C
_0805B800:
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
	movs r0, #0x66
	bl ClearBlink
	movs r1, #0xc0
	lsls r1, r1, #2
	movs r0, #0x67
	bl LoadBlink
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805B840:
	adds r0, r4, #0
	adds r0, #0xc8
	ldr r0, [r0]
	ldrb r0, [r0, #0xe]
	cmp r0, #0x1d
	bls _0805B860
	movs r1, #0xc0
	lsls r1, r1, #2
	movs r0, #0x66
	bl LoadBlink
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0805B86C
_0805B860:
	movs r0, #0x67
	bl UpdateBlinkMotionState
	adds r0, r4, #0
	bl floatGoldOmega1
_0805B86C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
