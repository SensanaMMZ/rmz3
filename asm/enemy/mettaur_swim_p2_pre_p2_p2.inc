	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08089c94
FUN_08089c94: @ 0x08089C94
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #9
	bls _08089CA0
	b _08089E56
_08089CA0:
	lsls r0, r0, #2
	ldr r1, _08089CAC @ =_08089CB0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08089CAC: .4byte _08089CB0
_08089CB0: @ jump table
	.4byte _08089CD8 @ case 0
	.4byte _08089CF2 @ case 1
	.4byte _08089D6A @ case 2
	.4byte _08089DD4 @ case 3
	.4byte _08089D74 @ case 4
	.4byte _08089D82 @ case 5
	.4byte _08089DBC @ case 6
	.4byte _08089DD4 @ case 7
	.4byte _08089E10 @ case 8
	.4byte _08089E22 @ case 9
_08089CD8:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08089D10 @ =0x08368844
	bl SetDDP
	movs r0, #0
	str r0, [r4, #0x5c]
	str r0, [r4, #0x60]
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089CF2:
	movs r2, #0
	ldr r0, _08089D14 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _08089D04
	movs r2, #1
_08089D04:
	cmp r2, #0
	beq _08089D18
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08089D1E
	.align 2, 0
_08089D10: .4byte 0x08368844
_08089D14: .4byte pZero2
_08089D18:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08089D1E:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_08088c4c
	ldr r0, [r4, #0x60]
	adds r0, #0x10
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #1
	cmp r0, r1
	ble _08089D54
	str r1, [r4, #0x60]
_08089D54:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08089DAE
	movs r0, #9
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _08089DAE
_08089D6A:
	ldr r1, _08089D70 @ =0x0000DD0A
	b _08089DC8
	.align 2, 0
_08089D70: .4byte 0x0000DD0A
_08089D74:
	ldr r1, _08089DB8 @ =0x0000DD0B
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089D82:
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_08088bc8
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08089D9C
	str r1, [r4, #0x60]
_08089D9C:
	adds r0, r4, #0
	bl FUN_08088ba8
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08089DAE
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089DAE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08089E56
	.align 2, 0
_08089DB8: .4byte 0x0000DD0B
_08089DBC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08089E08 @ =0x08368814
	bl SetDDP
	ldr r1, _08089E0C @ =0x0000DD0F
_08089DC8:
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089DD4:
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_08088c4c
	ldr r0, [r4, #0x60]
	adds r0, #0x10
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #1
	cmp r0, r1
	ble _08089DEE
	str r1, [r4, #0x60]
_08089DEE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08089E56
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08089E56
	.align 2, 0
_08089E08: .4byte 0x08368814
_08089E0C: .4byte 0x0000DD0F
_08089E10:
	ldr r1, _08089E5C @ =0x0000DD0B
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089E22:
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_08088c4c
	ldr r0, [r4, #0x60]
	adds r0, #0x10
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #1
	cmp r0, r1
	ble _08089E3C
	str r1, [r4, #0x60]
_08089E3C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08089E50
	movs r0, #0xb
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08089E50:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08089E56:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08089E5C: .4byte 0x0000DD0B
