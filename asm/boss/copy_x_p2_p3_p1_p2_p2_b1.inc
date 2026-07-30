	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyxKnockBackDamage
copyxKnockBackDamage: @ 0x08056C14
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056CC6
	ldr r1, _08056C70 @ =0x0000B311
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
	movs r3, #0
	ldr r0, _08056C74 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08056C3C
	movs r3, #1
_08056C3C:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08056C4E
	movs r3, #1
_08056C4E:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _08056C78
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08056C7E
	.align 2, 0
_08056C70: .4byte 0x0000B311
_08056C74: .4byte pZero2
_08056C78:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08056C7E:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08056C94
	ldr r0, _08056C90 @ =0xFFFFFE00
	b _08056C98
	.align 2, 0
_08056C90: .4byte 0xFFFFFE00
_08056C94:
	movs r0, #0x80
	lsls r0, r0, #2
_08056C98:
	str r0, [r4, #0x5c]
	ldr r0, _08056CE8 @ =0xFFFFFE00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0xc6
	movs r5, #0
	strb r5, [r0]
	movs r0, #8
	strb r0, [r4, #0x12]
	movs r0, #0x47
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08056CEC @ =sCollisions
	bl SetDDP
	ldr r1, [r4, #0x2c]
	cmp r1, #0
	beq _08056CC6
	movs r0, #1
	strb r0, [r1, #0x11]
	str r5, [r4, #0x2c]
_08056CC6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r1, r4, #0
	adds r1, #0xdd
	adds r0, r4, #0
	adds r0, #0xa4
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	movs r2, #0
	ldrsh r0, [r0, r2]
	cmp r1, r0
	ble _08056CF0
	movs r0, #0x24
	b _08056D4A
	.align 2, 0
_08056CE8: .4byte 0xFFFFFE00
_08056CEC: .4byte sCollisions
_08056CF0:
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r2, r1, r0
	str r2, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, #0x40
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _08056D34
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _08056D50
	ldr r1, _08056D30 @ =0x0000B308
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	b _08056D50
	.align 2, 0
_08056D30: .4byte 0x0000B308
_08056D34:
	adds r0, r2, #0
	bl FUN_08009f6c
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _08056D50
	ldr r0, [r4, #0x54]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r0, #0x22
_08056D4A:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08056D50:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08056d58
FUN_08056d58: @ 0x08056D58
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	adds r6, r4, #0
	adds r6, #0xb4
	ldr r0, [r4, #0x54]
	ldr r7, _08056DC0 @ =0xFFFF5800
	adds r0, r0, r7
	ldr r1, [r6]
	subs r1, r1, r0
	mov r8, r1
	ldr r2, _08056DC4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08056DC8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08056DCC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r5, r0, #0x11
	movs r0, #0xf
	ands r5, r0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056D9A
	ldr r1, _08056DD0 @ =0x0000B305
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
_08056D9A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r2, r4, #0
	adds r2, #0xce
	ldrb r0, [r2]
	adds r1, r4, #0
	adds r1, #0xa4
	movs r3, #0
	ldrsh r1, [r1, r3]
	cmp r0, r1
	ble _08056DD4
	movs r0, #0
	movs r1, #0x23
	strb r1, [r4, #0xd]
	movs r1, #1
	strb r1, [r4, #0xe]
	strb r0, [r2]
	b _08056E88
	.align 2, 0
_08056DC0: .4byte 0xFFFF5800
_08056DC4: .4byte RNG_0202f388
_08056DC8: .4byte 0x000343FD
_08056DCC: .4byte 0x00269EC3
_08056DD0: .4byte 0x0000B305
_08056DD4:
	ldr r0, [r4, #0x54]
	adds r3, r0, r7
	ldr r1, [r6]
	subs r2, r1, r3
	adds r6, r0, #0
	cmp r2, #0
	blt _08056DEC
	movs r0, #0xc8
	lsls r0, r0, #8
	cmp r2, r0
	bgt _08056DF6
	b _08056E24
_08056DEC:
	subs r1, r3, r1
	movs r0, #0xc8
	lsls r0, r0, #8
	cmp r1, r0
	ble _08056E24
_08056DF6:
	ldr r2, _08056E18 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08056E1C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08056E20 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08056E62
	movs r0, #6
	b _08056E82
	.align 2, 0
_08056E18: .4byte RNG_0202f388
_08056E1C: .4byte 0x000343FD
_08056E20: .4byte 0x00269EC3
_08056E24:
	cmp r5, #4
	bhi _08056E2C
	movs r0, #6
	b _08056E82
_08056E2C:
	cmp r5, #9
	bhi _08056E38
	adds r0, r4, #0
	bl copyx_080577c8
	b _08056E84
_08056E38:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r2, _08056E54 @ =0xFFFF5800
	adds r1, r6, r2
	ldr r0, [r0]
	subs r2, r0, r1
	cmp r2, #0
	blt _08056E58
	movs r0, #0xa0
	lsls r0, r0, #8
	cmp r2, r0
	bgt _08056E62
	b _08056E80
	.align 2, 0
_08056E54: .4byte 0xFFFF5800
_08056E58:
	subs r1, r1, r0
	movs r0, #0xa0
	lsls r0, r0, #8
	cmp r1, r0
	ble _08056E80
_08056E62:
	movs r0, #9
	strb r0, [r4, #0xd]
	movs r0, #0xb
	strb r0, [r4, #0xf]
	mov r0, r8
	movs r1, #0x28
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, _08056E7C @ =0xFFFFFB00
	str r0, [r4, #0x60]
	b _08056E84
	.align 2, 0
_08056E7C: .4byte 0xFFFFFB00
_08056E80:
	movs r0, #0x10
_08056E82:
	strb r0, [r4, #0xd]
_08056E84:
	movs r0, #1
	strb r0, [r4, #0xe]
_08056E88:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

