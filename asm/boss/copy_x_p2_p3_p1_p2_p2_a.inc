	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start copyx_08056ac0
copyx_08056ac0: @ 0x08056AC0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056B2E
	ldr r1, _08056B18 @ =0x0000B301
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _08056B1C @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08056AE2
	movs r3, #1
_08056AE2:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08056AF4
	movs r3, #1
_08056AF4:
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
	beq _08056B20
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08056B26
	.align 2, 0
_08056B18: .4byte 0x0000B301
_08056B1C: .4byte pZero2
_08056B20:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08056B26:
	strb r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
_08056B2E:
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _08056B4C
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08056B5E
	ldr r1, _08056B48 @ =0x0000B302
	adds r0, r4, #0
	bl SetMotion
	b _08056B5E
	.align 2, 0
_08056B48: .4byte 0x0000B302
_08056B4C:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08056B5E
	movs r0, #0x1f
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08056B5E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

