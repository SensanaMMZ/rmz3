	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0806fe38
FUN_0806fe38: @ 0x0806FE38
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, _0806FE58 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	subs r5, r1, r0
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _0806FEA4
	cmp r0, #1
	bgt _0806FE5C
	cmp r0, #0
	beq _0806FE62
	b _0806FF18
	.align 2, 0
_0806FE58: .4byte pZero2
_0806FE5C:
	cmp r0, #2
	beq _0806FEEC
	b _0806FF18
_0806FE62:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806FE88
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0806FE7C
	movs r0, #0x80
	b _0806FE80
_0806FE7C:
	movs r0, #0x80
	rsbs r0, r0, #0
_0806FE80:
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806FE88:
	adds r1, r5, #0
	cmp r5, #0
	bge _0806FE90
	rsbs r1, r5, #0
_0806FE90:
	ldr r0, _0806FEA0 @ =0x00000FFF
	cmp r1, r0
	bgt _0806FF18
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	b _0806FF16
	.align 2, 0
_0806FEA0: .4byte 0x00000FFF
_0806FEA4:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806FECE
	ldr r1, _0806FEC0 @ =0x00001501
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0806FEC4
	movs r0, #0xa0
	lsls r0, r0, #2
	b _0806FEC6
	.align 2, 0
_0806FEC0: .4byte 0x00001501
_0806FEC4:
	ldr r0, _0806FEE4 @ =0xFFFFFD80
_0806FEC6:
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806FECE:
	adds r1, r5, #0
	cmp r5, #0
	bge _0806FED6
	rsbs r1, r5, #0
_0806FED6:
	ldr r0, _0806FEE8 @ =0x00000FFF
	cmp r1, r0
	ble _0806FF18
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	b _0806FF18
	.align 2, 0
_0806FEE4: .4byte 0xFFFFFD80
_0806FEE8: .4byte 0x00000FFF
_0806FEEC:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806FF04
	ldr r1, _0806FF54 @ =0x00001503
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x40
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806FF04:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	movs r1, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806FF18
	strb r1, [r4, #0xd]
_0806FF16:
	strb r1, [r4, #0xe]
_0806FF18:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	cmp r0, #2
	beq _0806FFFA
	movs r5, #0
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r2, r0, r1
	str r2, [r4, #0x58]
	cmp r1, #0
	ble _0806FF5C
	ldr r0, [r4, #0x54]
	ldr r1, _0806FF58 @ =0xFFFFFF00
	adds r0, r0, r1
	movs r3, #0xc0
	lsls r3, r3, #4
	adds r1, r2, r3
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0806FF6E
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0xc0
	lsls r2, r2, #4
	b _0806FF96
	.align 2, 0
_0806FF54: .4byte 0x00001503
_0806FF58: .4byte 0xFFFFFF00
_0806FF5C:
	ldrb r0, [r4, #0x11]
	cmp r0, #2
	bne _0806FF7C
	ldr r0, _0806FF74 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r3, _0806FF78 @ =0xFFFFB000
	adds r0, r0, r3
	cmp r2, r0
	bge _0806FFA0
_0806FF6E:
	movs r5, #0x80
	lsls r5, r5, #5
	b _0806FFA0
	.align 2, 0
_0806FF74: .4byte gStageRun+232
_0806FF78: .4byte 0xFFFFB000
_0806FF7C:
	ldr r0, [r4, #0x54]
	ldr r1, _0806FFB8 @ =0xFFFFFF00
	adds r0, r0, r1
	ldr r3, _0806FFBC @ =0xFFFFF400
	adds r1, r2, r3
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0806FF6E
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, _0806FFBC @ =0xFFFFF400
_0806FF96:
	adds r1, r1, r2
	bl FUN_0800a22c
	ldr r1, [r4, #0x54]
	subs r5, r1, r0
_0806FFA0:
	adds r1, r5, #0
	cmp r1, #0
	bge _0806FFA8
	rsbs r1, r1, #0
_0806FFA8:
	movs r0, #0x80
	lsls r0, r0, #4
	cmp r1, r0
	ble _0806FFC0
	ldr r0, [r4, #0x60]
	rsbs r0, r0, #0
	b _0806FFF8
	.align 2, 0
_0806FFB8: .4byte 0xFFFFFF00
_0806FFBC: .4byte 0xFFFFF400
_0806FFC0:
	ldrb r0, [r4, #0x11]
	cmp r0, #1
	bne _0806FFFA
	ldr r2, [r4, #0x60]
	cmp r2, #0
	ble _0806FFE4
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	ldr r1, _0806FFE0 @ =0xFFFFD000
	cmp r0, r1
	bge _0806FFFA
	b _0806FFF6
	.align 2, 0
_0806FFE0: .4byte 0xFFFFD000
_0806FFE4:
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	ble _0806FFFA
_0806FFF6:
	rsbs r0, r2, #0
_0806FFF8:
	str r0, [r4, #0x60]
_0806FFFA:
	pop {r4, r5}
	pop {r0}
	bx r0
