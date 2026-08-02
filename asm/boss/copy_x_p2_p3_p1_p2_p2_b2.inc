	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start copyxMode36
copyxMode36: @ 0x08056FD4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08057064
	ldr r1, _08057038 @ =0x0000B314
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
	movs r3, #0
	ldr r0, _0805703C @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08057002
	movs r3, #1
_08057002:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08057014
	movs r3, #1
_08057014:
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
	beq _08057040
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08057046
	.align 2, 0
_08057038: .4byte 0x0000B314
_0805703C: .4byte pZero2
_08057040:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08057046:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08057090 @ =0x08363C78
	bl SetDDP
	adds r0, r4, #0
	bl CreateVFX52
	str r0, [r4, #0x2c]
	movs r0, #0x20
	strb r0, [r4, #0x12]
	movs r0, #0x45
	bl PlaySound
_08057064:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _08057088
	ldr r0, [r4, #0x2c]
	movs r1, #1
	strb r1, [r0, #0x11]
	movs r0, #0
	str r0, [r4, #0x2c]
	movs r0, #0xf
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0xde
	strb r1, [r0]
_08057088:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08057090: .4byte 0x08363C78
