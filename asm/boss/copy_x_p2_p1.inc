	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start copyxMode5
copyxMode5: @ 0x08055B2C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08055BB0
	movs r1, #0xb3
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	movs r3, #0
	ldr r0, _08055B88 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08055B54
	movs r3, #1
_08055B54:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08055B66
	movs r3, #1
_08055B66:
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
	beq _08055B8C
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08055B92
	.align 2, 0
_08055B88: .4byte pZero2
_08055B8C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08055B92:
	strb r0, [r4, #0xa]
	movs r0, #0x20
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	bl CreateVFX52
	str r0, [r4, #0x2c]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08055BF4 @ =0x08363C78
	bl SetDDP
	movs r0, #0x45
	bl PlaySound
_08055BB0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _08055C0E
	ldr r0, [r4, #0x2c]
	movs r1, #1
	strb r1, [r0, #0x11]
	movs r0, #0
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xf]
	adds r2, r4, #0
	adds r2, #0xc5
	strb r0, [r2]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	movs r1, #2
	strb r1, [r4, #0xf]
	adds r0, r4, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r0, [r0, r2]
	cmp r0, #0x1f
	bgt _08055BF8
	movs r0, #8
	strb r0, [r4, #0x12]
	b _08055C04
	.align 2, 0
_08055BF4: .4byte 0x08363C78
_08055BF8:
	cmp r0, #0x2f
	bgt _08055C02
	movs r0, #4
	strb r0, [r4, #0x12]
	b _08055C04
_08055C02:
	strb r1, [r4, #0x12]
_08055C04:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08055C14 @ =sCollisions
	bl SetDDP
_08055C0E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08055C14: .4byte sCollisions
