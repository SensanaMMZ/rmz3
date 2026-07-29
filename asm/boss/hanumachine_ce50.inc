	.include "asm/macros.inc"

	.syntax unified

	.text

	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	bne _0805CF06
	ldr r1, _0805CEA4 @ =0x0000B506
	adds r0, r5, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805CEA8 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805CE72
	movs r3, #1
_0805CE72:
	adds r0, r5, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805CE84
	movs r3, #1
_0805CE84:
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r2, r3, #4
	ldrb r1, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r4]
	cmp r3, #0
	beq _0805CEAC
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805CEB2
	.align 2, 0
_0805CEA4: .4byte 0x0000B506
_0805CEA8: .4byte pZero2
_0805CEAC:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805CEB2:
	strb r0, [r5, #0xa]
	ldr r0, _0805CEF4 @ =pZero2
	ldr r0, [r0]
	adds r1, r5, #0
	adds r1, #0xb4
	ldr r0, [r0, #0x54]
	ldr r4, [r1]
	subs r0, r0, r4
	movs r1, #0xc0
	lsls r1, r1, #6
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r1, r2
	adds r4, r4, r0
	ldr r0, [r5, #0x54]
	subs r4, r4, r0
	adds r0, r4, #0
	movs r1, #0x18
	bl __divsi3
	str r0, [r5, #0x5c]
	ldr r1, _0805CEF8 @ =0xFFFFFA00
	str r1, [r5, #0x60]
	cmp r0, #0
	ble _0805CEFC
	movs r0, #0x80
	lsls r0, r0, #5
	b _0805CEFE
	.align 2, 0
_0805CEF4: .4byte pZero2
_0805CEF8: .4byte 0xFFFFFA00
_0805CEFC:
	ldr r0, _0805CF54 @ =0xFFFFF000
_0805CEFE:
	str r0, [r5, #0x64]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805CF06:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r1, [r5, #0x64]
	adds r0, r5, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805CF24
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_0805CF24:
	ldr r2, [r5, #0x60]
	adds r0, r5, #0
	movs r1, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805CF3C
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
_0805CF3C:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	cmp r0, #0
	blt _0805CF4E
	movs r1, #0
	movs r0, #0x17
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0805CF4E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805CF54: .4byte 0xFFFFF000
