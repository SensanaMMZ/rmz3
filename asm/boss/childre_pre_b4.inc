	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start childreMissile
childreMissile: @ 0x08041984
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _08041990
	b _08041B38
_08041990:
	lsls r0, r0, #2
	ldr r1, _0804199C @ =_080419A0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804199C: .4byte _080419A0
_080419A0: @ jump table
	.4byte _080419B4 @ case 0
	.4byte _08041A04 @ case 1
	.4byte _08041A50 @ case 2
	.4byte _08041AA8 @ case 3
	.4byte _08041AE8 @ case 4
_080419B4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080419E0 @ =sCollisions+(24*1)
	bl SetDDP
	movs r0, #0
	strb r0, [r4, #0x12]
	ldr r0, _080419E4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	subs r2, r1, r0
	lsrs r2, r2, #0x1f
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080419E8
	cmp r2, #0
	beq _080419EC
	b _080419F2
	.align 2, 0
_080419E0: .4byte sCollisions+(24*1)
_080419E4: .4byte pZero2
_080419E8:
	cmp r2, #0
	beq _080419F2
_080419EC:
	ldrb r0, [r4, #0xe]
	adds r0, #2
	b _08041B36
_080419F2:
	ldr r1, _08041A48 @ =0x0000A408
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _08041A4C @ =0xFFFFFE00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041A04:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08041A14
	str r1, [r4, #0x60]
_08041A14:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	subs r0, r0, r1
	cmp r0, #0
	bge _08041A2C
	adds r0, r1, r0
	str r0, [r4, #0x58]
_08041A2C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08041A3E
	b _08041B38
_08041A3E:
	movs r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _08041B36
	.align 2, 0
_08041A48: .4byte 0x0000A408
_08041A4C: .4byte 0xFFFFFE00
_08041A50:
	movs r0, #0x69
	bl PlaySound
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08041A9E
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _08041A96
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08041A9C
_08041A96:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08041A9C:
	strb r0, [r4, #0xa]
_08041A9E:
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041AA8:
	ldr r1, _08041B18 @ =0x0836206E
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x12]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bhi _08041ADE
	movs r0, #0x64
	bl PlaySound
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, _08041B1C @ =0xFFFFE600
	adds r1, r1, r2
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r3, #1
	ands r2, r3
	bl CreateChildreMissile
_08041ADE:
	movs r0, #0x18
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041AE8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0x12]
	adds r0, r1, #0
	cmp r0, #0
	beq _08041AFA
	cmp r0, #5
	bne _08041B24
_08041AFA:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r2, [r0]
	cmp r2, #3
	bne _08041B38
	adds r0, r1, #1
	movs r1, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #6
	bne _08041B20
	strb r1, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _08041B38
	.align 2, 0
_08041B18: .4byte 0x0836206E
_08041B1C: .4byte 0xFFFFE600
_08041B20:
	strb r2, [r4, #0xe]
	b _08041B38
_08041B24:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08041B38
	adds r0, r1, #1
	strb r0, [r4, #0x12]
	movs r0, #3
_08041B36:
	strb r0, [r4, #0xe]
_08041B38:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start childreStartEarShot
childreStartEarShot: @ 0x08041B40
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _08041B4C
	b _08041CB4
_08041B4C:
	lsls r0, r0, #2
	ldr r1, _08041B58 @ =_08041B5C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08041B58: .4byte _08041B5C
_08041B5C: @ jump table
	.4byte _08041B74 @ case 0
	.4byte _08041BC6 @ case 1
	.4byte _08041C0C @ case 2
	.4byte _08041C72 @ case 3
	.4byte _08041C90 @ case 4
	.4byte _08041C9C @ case 5
_08041B74:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08041BA0 @ =sCollisions+(24*1)
	bl SetDDP
	movs r0, #0
	strb r0, [r4, #0x12]
	ldr r0, _08041BA4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	subs r2, r1, r0
	lsrs r2, r2, #0x1f
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08041BA8
	cmp r2, #0
	beq _08041BAC
	b _08041BB4
	.align 2, 0
_08041BA0: .4byte sCollisions+(24*1)
_08041BA4: .4byte pZero2
_08041BA8:
	cmp r2, #0
	beq _08041BB4
_08041BAC:
	ldrb r0, [r4, #0xe]
	adds r0, #2
	strb r0, [r4, #0xe]
	b _08041CB4
_08041BB4:
	ldr r1, _08041C04 @ =0x0000A408
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _08041C08 @ =0xFFFFFE00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041BC6:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08041BD6
	str r1, [r4, #0x60]
_08041BD6:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	subs r0, r0, r1
	cmp r0, #0
	bge _08041BEE
	adds r0, r1, r0
	str r0, [r4, #0x58]
_08041BEE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08041CB4
	movs r0, #1
	strb r0, [r4, #0x12]
	b _08041C82
	.align 2, 0
_08041C04: .4byte 0x0000A408
_08041C08: .4byte 0xFFFFFE00
_08041C0C:
	ldr r1, _08041C54 @ =0x0000A413
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08041C60
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _08041C58
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08041C5E
	.align 2, 0
_08041C54: .4byte 0x0000A413
_08041C58:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08041C5E:
	strb r0, [r4, #0xa]
_08041C60:
	ldr r1, _08041C8C @ =0x0000A403
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041C72:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08041CB4
_08041C82:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08041CB4
	.align 2, 0
_08041C8C: .4byte 0x0000A403
_08041C90:
	movs r0, #0x6c
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041C9C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08041CB4
	movs r1, #0
	movs r0, #0xe
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08041CB4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
