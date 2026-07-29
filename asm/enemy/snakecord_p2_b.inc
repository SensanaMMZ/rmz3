	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08074d90
FUN_08074d90: @ 0x08074D90
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08074DE2
	cmp r0, #1
	bgt _08074DA4
	cmp r0, #0
	beq _08074DAE
	b _08074E82
_08074DA4:
	cmp r0, #2
	beq _08074E24
	cmp r0, #3
	beq _08074E36
	b _08074E82
_08074DAE:
	ldr r0, _08074E1C @ =0xFFFFFE00
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08074DC2
	movs r2, #0x80
	lsls r2, r2, #2
_08074DC2:
	str r2, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xa
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldr r1, _08074E20 @ =0x00002807
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074DE2:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08073ea8
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08074DFA
	str r1, [r4, #0x60]
_08074DFA:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08073ef0
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	bne _08074E82
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08074E82
	.align 2, 0
_08074E1C: .4byte 0xFFFFFE00
_08074E20: .4byte 0x00002807
_08074E24:
	movs r0, #0
	strb r0, [r4, #0x13]
	ldr r1, _08074E88 @ =0x00002808
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074E36:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #8
	bne _08074E4E
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08074E8C @ =0x08366F2C
	bl SetDDP
_08074E4E:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08073ea8
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08074E66
	str r1, [r4, #0x60]
_08074E66:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08073ef0
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _08074E7C
	movs r0, #8
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_08074E7C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08074E82:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08074E88: .4byte 0x00002808
_08074E8C: .4byte 0x08366F2C

	thumb_func_start FUN_08074e90
FUN_08074e90: @ 0x08074E90
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08074EC6
	cmp r0, #1
	bgt _08074EA4
	cmp r0, #0
	beq _08074EAE
	b _08074F2A
_08074EA4:
	cmp r0, #2
	beq _08074F04
	cmp r0, #3
	beq _08074F12
	b _08074F2A
_08074EAE:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08074EFC @ =0x08366F2C
	bl SetDDP
	ldr r1, _08074F00 @ =0x00002809
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074EC6:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08073ea8
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08074EDE
	str r1, [r4, #0x60]
_08074EDE:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08073ef0
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _08074EF4
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074EF4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08074F2A
	.align 2, 0
_08074EFC: .4byte 0x08366F2C
_08074F00: .4byte 0x00002809
_08074F04:
	ldr r1, _08074F30 @ =0x0000280A
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074F12:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08074F2A
	movs r1, #0
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08074F2A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08074F30: .4byte 0x0000280A

