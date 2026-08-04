	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cannonHopper_08097d10
cannonHopper_08097d10: @ 0x08097D10
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #4
	bls _08097D1E
	b _08097F34
_08097D1E:
	lsls r0, r0, #2
	ldr r1, _08097D28 @ =_08097D2C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08097D28: .4byte _08097D2C
_08097D2C: @ jump table
	.4byte _08097D40 @ case 0
	.4byte _08097D98 @ case 1
	.4byte _08097DB4 @ case 2
	.4byte _08097E88 @ case 3
	.4byte _08097E9C @ case 4
_08097D40:
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	adds r1, r5, #0
	adds r1, #0xbd
	strb r0, [r1]
	ldr r0, _08097D68 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	lsrs r2, r0, #0x1f
	cmp r2, #0
	beq _08097D6C
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08097D72
	.align 2, 0
_08097D68: .4byte pZero2
_08097D6C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08097D72:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	strb r3, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08097D98:
	ldr r0, _08097E6C @ =0x0000DC14
	adds r1, r0, #0
	ldrb r0, [r5, #0x13]
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0xc
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08097DB4:
	ldr r1, [r5, #0x5c]
	ldr r2, [r5, #0x60]
	adds r0, r5, #0
	bl FUN_08096ffc
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xb
	bne _08097E52
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _08097E52
	ldr r0, _08097E70 @ =0x0836A42D
	ldrb r1, [r5, #0x13]
	subs r2, r1, #1
	adds r0, r2, r0
	ldrb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	beq _08097DF2
	movs r0, #0x80
	subs r0, r0, r4
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
_08097DF2:
	movs r0, #0x20
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	cmp r7, #0
	beq _08097E06
	movs r0, #0xff
	subs r0, r0, r4
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
_08097E06:
	ldr r1, [r5, #0x54]
	str r1, [sp]
	ldr r0, _08097E74 @ =0x0836A434
	lsls r3, r2, #2
	adds r2, r3, r0
	ldr r0, [r2]
	adds r0, r0, r1
	str r0, [sp]
	adds r1, r0, #0
	cmp r6, #0
	beq _08097E22
	ldr r0, [r2]
	lsls r0, r0, #1
	subs r1, r1, r0
_08097E22:
	str r1, [sp]
	ldr r1, [r5, #0x58]
	str r1, [sp, #4]
	ldr r0, _08097E78 @ =0x0836A448
	adds r3, r3, r0
	ldr r0, [r3]
	adds r0, r0, r1
	str r0, [sp, #4]
	adds r2, r0, #0
	cmp r7, #0
	beq _08097E3E
	ldr r0, [r3]
	lsls r0, r0, #1
	subs r2, r2, r0
_08097E3E:
	str r2, [sp, #4]
	movs r0, #0x2c
	bl PlaySound
	movs r1, #0xa0
	lsls r1, r1, #2
	mov r0, sp
	adds r2, r4, #0
	bl CreateLemon
_08097E52:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _08097E80
	ldrb r0, [r5, #0x13]
	adds r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #6
	bne _08097E7C
	movs r0, #3
	b _08097E7E
	.align 2, 0
_08097E6C: .4byte 0x0000DC14
_08097E70: .4byte 0x0836A42D
_08097E74: .4byte 0x0836A434
_08097E78: .4byte 0x0836A448
_08097E7C:
	movs r0, #1
_08097E7E:
	strb r0, [r5, #0xe]
_08097E80:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08097F34
_08097E88:
	movs r1, #0xdc
	lsls r1, r1, #8
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x18
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08097E9C:
	ldr r1, [r5, #0x5c]
	ldr r2, [r5, #0x60]
	adds r0, r5, #0
	bl FUN_08096ffc
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08097F2E
	adds r0, r5, #0
	adds r0, #0xbd
	ldrb r2, [r0]
	cmp r2, #0
	beq _08097EC4
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08097ECA
_08097EC4:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08097ECA:
	strb r0, [r5, #0xa]
	movs r7, #1
	adds r1, r7, #0
	ands r1, r2
	adds r4, r5, #0
	adds r4, #0x4c
	strb r1, [r4]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r0, r5, #0
	adds r0, #0xc0
	ldr r0, [r0]
	adds r6, r3, #0
	cmp r0, #0x4f
	bgt _08097F00
	movs r0, #3
	strb r0, [r5, #0xd]
	movs r0, #0
	strb r0, [r5, #0xe]
	b _08097F2E
_08097F00:
	ldrb r2, [r5, #0xa]
	lsrs r0, r2, #4
	adds r1, r7, #0
	bics r1, r0
	cmp r1, #0
	beq _08097F12
	movs r0, #0x10
	orrs r0, r2
	b _08097F16
_08097F12:
	movs r0, #0xef
	ands r0, r2
_08097F16:
	strb r0, [r5, #0xa]
	movs r3, #0
	strb r1, [r4]
	lsls r1, r1, #4
	ldrb r2, [r6]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r6]
	strb r3, [r5, #0xd]
	strb r3, [r5, #0xe]
_08097F2E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08097F34:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
