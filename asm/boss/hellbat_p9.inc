	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start hellbatKnockBackDamage
hellbatKnockBackDamage: @ 0x0804CAA4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0804CAB4
	cmp r5, #1
	beq _0804CB62
	b _0804CBD4
_0804CAB4:
	movs r0, #0x8a
	bl PlaySound
	ldr r1, _0804CAF0 @ =0x0000A80B
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _0804CAF4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0804CAFC
	ldr r0, _0804CAF8 @ =0xFFFFFE00
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0x4c
	movs r0, #1
	strb r0, [r1]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r4, #0xa]
	orrs r1, r0
	strb r1, [r4, #0xa]
	b _0804CB1E
	.align 2, 0
_0804CAF0: .4byte 0x0000A80B
_0804CAF4: .4byte pZero2
_0804CAF8: .4byte 0xFFFFFE00
_0804CAFC:
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
_0804CB1E:
	ldrb r0, [r4, #0xa]
	movs r1, #1
	movs r3, #0
	orrs r1, r0
	strb r1, [r4, #0xa]
	movs r0, #0x20
	ands r1, r0
	cmp r1, #0
	beq _0804CB52
	adds r0, r4, #0
	adds r0, #0x4d
	strb r3, [r0]
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x58]
	movs r1, #0xe4
	lsls r1, r1, #6
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0804CB52:
	adds r0, r4, #0
	adds r0, #0xc0
	str r3, [r0]
	movs r0, #0x28
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804CB62:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x5c]
	rsbs r1, r0, #0
	lsls r1, r1, #3
	asrs r1, r1, #8
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r1, [r4, #0x54]
	adds r1, r1, r0
	str r1, [r4, #0x54]
	cmp r0, #0
	ble _0804CB9A
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r1, r2
	ldr r1, [r4, #0x58]
	ldr r2, _0804CBDC @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToLeft1
	adds r1, r0, #0
	cmp r1, #0
	beq _0804CB9A
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0804CB9A:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _0804CBBC
	ldr r0, [r4, #0x54]
	ldr r1, _0804CBE0 @ =0xFFFFE800
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	ldr r2, _0804CBDC @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToRight1
	adds r1, r0, #0
	cmp r1, #0
	beq _0804CBBC
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0804CBBC:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0804CBCC
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804CBD4
_0804CBCC:
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804CBD4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804CBDC: .4byte 0xFFFFF800
_0804CBE0: .4byte 0xFFFFE800
