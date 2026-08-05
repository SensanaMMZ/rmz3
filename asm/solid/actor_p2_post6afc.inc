	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080d6c80
FUN_080d6c80: @ 0x080D6C80
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #0xc
	bls _080D6C8C
	b _080D6F5E
_080D6C8C:
	lsls r0, r0, #2
	ldr r1, _080D6C98 @ =_080D6C9C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D6C98: .4byte _080D6C9C
_080D6C9C: @ jump table
	.4byte _080D6CD0 @ case 0
	.4byte _080D6CEC @ case 1
	.4byte _080D6D04 @ case 2
	.4byte _080D6D2C @ case 3
	.4byte _080D6D64 @ case 4
	.4byte _080D6D8C @ case 5
	.4byte _080D6DD8 @ case 6
	.4byte _080D6E00 @ case 7
	.4byte _080D6E2C @ case 8
	.4byte _080D6E74 @ case 9
	.4byte _080D6F38 @ case 10
	.4byte _080D6F48 @ case 11
	.4byte _080D6F5E @ case 12
_080D6CD0:
	ldr r0, _080D6CFC @ =wDynamicGraphicTilenums
	movs r2, #0xbe
	lsls r2, r2, #1
	adds r0, r0, r2
	movs r1, #0xf0
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r0, _080D6D00 @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	movs r1, #9
	strh r1, [r0]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D6CEC:
	movs r1, #0xbe
	lsls r1, r1, #8
	adds r0, r6, #0
	movs r2, #1
	bl FUN_080d0aa0
	b _080D6F52
	.align 2, 0
_080D6CFC: .4byte wDynamicGraphicTilenums
_080D6D00: .4byte wDynamicMotionPalIDs
_080D6D04:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D6D18
	b _080D6F5E
_080D6D18:
	ldr r1, _080D6D28 @ =0x0000BE01
	adds r0, r6, #0
	bl SetMotion
	movs r0, #8
	strb r0, [r6, #0x12]
	b _080D6F58
	.align 2, 0
_080D6D28: .4byte 0x0000BE01
_080D6D2C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D6D44
	ldr r0, _080D6D5C @ =0x00000101
	bl PlaySound
_080D6D44:
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D6D50
	b _080D6F5E
_080D6D50:
	ldr r1, _080D6D60 @ =0x0000BE02
	adds r0, r6, #0
	bl SetMotion
	b _080D6F58
	.align 2, 0
_080D6D5C: .4byte 0x00000101
_080D6D60: .4byte 0x0000BE02
_080D6D64:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D6D76
	b _080D6F5E
_080D6D76:
	ldr r1, _080D6D88 @ =0x0000BE03
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0x40
	strb r0, [r6, #0x12]
	ldr r0, [r6, #0x58]
	str r0, [r6, #0x68]
	b _080D6F58
	.align 2, 0
_080D6D88: .4byte 0x0000BE03
_080D6D8C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, _080D6DD0 @ =gSineTable
	ldrb r0, [r6, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	ldr r1, [r6, #0x68]
	subs r1, r1, r0
	str r1, [r6, #0x68]
	ldr r2, [r6, #0x58]
	lsls r0, r2, #3
	subs r0, r0, r2
	adds r0, r0, r1
	asrs r0, r0, #3
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0
	beq _080D6DC0
	b _080D6F5E
_080D6DC0:
	ldr r1, _080D6DD4 @ =0x0000BE11
	adds r0, r6, #0
	bl SetMotion
	strb r4, [r6, #0x12]
	ldr r0, [r6, #0x58]
	str r0, [r6, #0x60]
	b _080D6F58
	.align 2, 0
_080D6DD0: .4byte gSineTable
_080D6DD4: .4byte 0x0000BE11
_080D6DD8:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D6DEA
	b _080D6F5E
_080D6DEA:
	movs r0, #0x92
	lsls r0, r0, #1
	bl PlaySound
	ldr r1, _080D6DFC @ =0x0000BE12
	adds r0, r6, #0
	bl SetMotion
	b _080D6F58
	.align 2, 0
_080D6DFC: .4byte 0x0000BE12
_080D6E00:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _080D6E14
	b _080D6F5E
_080D6E14:
	movs r0, #0x92
	lsls r0, r0, #1
	bl StopSound
	ldr r1, _080D6E28 @ =0x0000BE13
	adds r0, r6, #0
	bl SetMotion
	b _080D6F58
	.align 2, 0
_080D6E28: .4byte 0x0000BE13
_080D6E2C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D6E3E
	b _080D6F5E
_080D6E3E:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080D6E6C @ =0x08370DD0
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r1, _080D6E70 @ =0x0000BE03
	adds r0, r6, #0
	bl SetMotion
	str r5, [r6, #0x5c]
	strb r5, [r6, #0x13]
	b _080D6F58
	.align 2, 0
_080D6E6C: .4byte sCollisions_08370C68+(24*15)
_080D6E70: .4byte 0x0000BE03
_080D6E74:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x5c]
	cmp r0, #0
	beq _080D6EAA
	adds r0, #0x20
	str r0, [r6, #0x5c]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080D6E8E
	str r1, [r6, #0x5c]
_080D6E8E:
	ldr r1, [r6, #0x60]
	ldr r0, [r6, #0x5c]
	adds r1, r1, r0
	str r1, [r6, #0x60]
	ldr r0, [r6, #0x54]
	bl PushoutToUp1
	cmp r0, #0
	beq _080D6EAA
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x60]
	bl FUN_08009f6c
	str r0, [r6, #0x60]
_080D6EAA:
	ldrb r0, [r6, #0x13]
	cmp r0, #0
	beq _080D6ED8
	subs r0, #1
	strb r0, [r6, #0x13]
	movs r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080D6EC4
	adds r0, r6, #0
	bl PaintEntityWhite
	b _080D6ECA
_080D6EC4:
	adds r0, r6, #0
	bl UpdateEntityPaletteID
_080D6ECA:
	ldrb r0, [r6, #0x13]
	cmp r0, #0x16
	bne _080D6ED8
	ldr r1, _080D6EF8 @ =0x0000BE0D
	adds r0, r6, #0
	bl SetMotion
_080D6ED8:
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080D6F00
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x60]
	bl FUN_08009f6c
	str r0, [r6, #0x58]
	ldr r1, _080D6EFC @ =0x0000BE0E
	adds r0, r6, #0
	bl SetMotion
	b _080D6F58
	.align 2, 0
_080D6EF8: .4byte 0x0000BE0D
_080D6EFC: .4byte 0x0000BE0E
_080D6F00:
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080D6F5E
	ldr r1, _080D6F34 @ =0x0000BE0C
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r6, #0x13]
	ldr r0, [r6, #0x5c]
	adds r0, #1
	str r0, [r6, #0x5c]
	movs r0, #0xf8
	bl isSoundPlaying
	cmp r0, #0
	bne _080D6F5E
	movs r0, #0xf8
	bl PlaySound
	b _080D6F5E
	.align 2, 0
_080D6F34: .4byte 0x0000BE0C
_080D6F38:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #8
	ands r0, r1
	b _080D6F54
_080D6F48:
	ldr r1, _080D6F98 @ =0x0000BE0B
	adds r0, r6, #0
	movs r2, #1
	bl FUN_080d0934
_080D6F52:
	lsls r0, r0, #0x10
_080D6F54:
	cmp r0, #0
	beq _080D6F5E
_080D6F58:
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D6F5E:
	ldrb r0, [r6, #0xd]
	subs r0, #6
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bhi _080D6F90
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldr r1, _080D6F9C @ =gSineTable
	ldrb r0, [r6, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #2
	ldr r1, [r6, #0x60]
	adds r1, r1, r0
	str r1, [r6, #0x68]
	ldr r2, [r6, #0x58]
	lsls r0, r2, #3
	subs r0, r0, r2
	adds r0, r0, r1
	asrs r0, r0, #3
	str r0, [r6, #0x58]
_080D6F90:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080D6F98: .4byte 0x0000BE0B
_080D6F9C: .4byte gSineTable
