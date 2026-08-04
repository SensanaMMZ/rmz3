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

	thumb_func_start FUN_080d6fa0
FUN_080d6fa0: @ 0x080D6FA0
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #5
	bls _080D6FAC
	b _080D71F0
_080D6FAC:
	lsls r0, r0, #2
	ldr r1, _080D6FB8 @ =_080D6FBC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D6FB8: .4byte _080D6FBC
_080D6FBC: @ jump table
	.4byte _080D6FD4 @ case 0
	.4byte _080D708E @ case 1
	.4byte _080D70E0 @ case 2
	.4byte _080D710C @ case 3
	.4byte _080D71B8 @ case 4
	.4byte _080D71F0 @ case 5
_080D6FD4:
	movs r4, #0xb8
	ldr r0, _080D7050 @ =wStaticGraphicTilenums
	lsls r2, r4, #1
	adds r0, r0, r2
	movs r1, #0x90
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r5, _080D7054 @ =wStaticMotionPalIDs
	adds r5, r5, r2
	movs r0, #6
	strh r0, [r5]
	lsls r4, r4, #4
	movs r0, #0xb8
	lsls r0, r0, #2
	adds r4, r4, r0
	ldr r2, _080D7058 @ =gStaticMotionGraphics
	adds r0, r4, r2
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D705C @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldrh r1, [r5]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	movs r1, #0xb8
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	ldr r4, _080D7060 @ =0xFFFFE800
	adds r0, r0, r4
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x11]
	cmp r0, #0
	beq _080D7068
	ldr r1, _080D7064 @ =0x0000B802
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0
	str r0, [r6, #0x60]
	movs r0, #3
	b _080D71EE
	.align 2, 0
_080D7050: .4byte wStaticGraphicTilenums
_080D7054: .4byte wStaticMotionPalIDs
_080D7058: .4byte gStaticMotionGraphics
_080D705C: .4byte gStaticMotionGraphics+12
_080D7060: .4byte 0xFFFFE800
_080D7064: .4byte 0x0000B802
_080D7068:
	str r0, [r6, #0x60]
	movs r0, #0x10
	str r0, [r6, #0x68]
	ldrb r4, [r6, #0xd]
	movs r3, #0x10
	movs r2, #0x5f
_080D7074:
	ldr r1, [r6, #0x60]
	adds r1, r1, r3
	str r1, [r6, #0x60]
	ldr r0, [r6, #0x58]
	subs r0, r0, r1
	str r0, [r6, #0x58]
	subs r2, #1
	cmp r2, #0
	bge _080D7074
	movs r0, #0
	strb r0, [r6, #0x13]
	adds r0, r4, #1
	strb r0, [r6, #0xd]
_080D708E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r0, [r6, #0x68]
	subs r4, r1, r0
	str r4, [r6, #0x60]
	cmp r4, #0
	beq _080D70A8
	b _080D71F0
_080D70A8:
	ldr r1, _080D70D0 @ =gPaletteManager
	ldr r0, _080D70D4 @ =0x00000404
	adds r2, r1, r0
	movs r0, #0x40
	strh r0, [r2]
	ldr r2, _080D70D8 @ =0x00000406
	adds r1, r1, r2
	movs r0, #0xe0
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r1, _080D70DC @ =0x0000B801
	adds r0, r6, #0
	bl SetMotion
	str r4, [r6, #0x60]
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r6, #0xa]
	b _080D71EA
	.align 2, 0
_080D70D0: .4byte gPaletteManager
_080D70D4: .4byte 0x00000404
_080D70D8: .4byte 0x00000406
_080D70DC: .4byte 0x0000B801
_080D70E0:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D70F2
	b _080D71F0
_080D70F2:
	ldr r1, _080D7104 @ =0x0000B802
	adds r0, r6, #0
	bl SetMotion
	ldr r0, _080D7108 @ =0x0000013D
	bl PlaySound
	b _080D71EA
	.align 2, 0
_080D7104: .4byte 0x0000B802
_080D7108: .4byte 0x0000013D
_080D710C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D7124
	ldr r1, _080D7190 @ =0x0000B802
	adds r0, r6, #0
	bl SetMotion
_080D7124:
	ldr r2, _080D7194 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080D7198 @ =0x000343FD
	muls r0, r1, r0
	ldr r4, _080D719C @ =0x00269EC3
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #0
	bne _080D7148
	ldr r1, _080D71A0 @ =0x0000B803
	adds r0, r6, #0
	bl SetMotion
_080D7148:
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D71F0
	ldr r0, _080D71A4 @ =0x0000013D
	bl StopSound
	ldr r1, _080D71A8 @ =gPaletteManager
	ldr r0, _080D71AC @ =0x00000404
	adds r2, r1, r0
	movs r4, #0x40
	movs r0, #0x40
	strh r0, [r2]
	ldr r2, _080D71B0 @ =0x00000406
	adds r1, r1, r2
	movs r0, #0xe0
	lsls r0, r0, #1
	strh r0, [r1]
	movs r1, #0xb8
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0x64
	str r0, [r6, #0x40]
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r0, _080D71B4 @ =0xFFFFFF00
	str r0, [r6, #0x60]
	strb r4, [r6, #0x13]
	b _080D71EA
	.align 2, 0
_080D7190: .4byte 0x0000B802
_080D7194: .4byte RNG_0202f388
_080D7198: .4byte 0x000343FD
_080D719C: .4byte 0x00269EC3
_080D71A0: .4byte 0x0000B803
_080D71A4: .4byte 0x0000013D
_080D71A8: .4byte gPaletteManager
_080D71AC: .4byte 0x00000404
_080D71B0: .4byte 0x00000406
_080D71B4: .4byte 0xFFFFFF00
_080D71B8:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D71F0
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r0, _080D7240 @ =gStageRun+232
	adds r1, r6, #0
	adds r1, #0x54
	bl CalcFromCamera
	ldr r1, _080D7244 @ =0x00000FFF
	cmp r0, r1
	bls _080D71F0
	ldrb r0, [r6, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r6, #0xa]
_080D71EA:
	ldrb r0, [r6, #0xd]
	adds r0, #1
_080D71EE:
	strb r0, [r6, #0xd]
_080D71F0:
	ldrb r0, [r6, #0x1e]
	lsls r0, r0, #8
	adds r1, r6, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	movs r1, #0xb8
	lsls r1, r1, #8
	cmp r0, r1
	bne _080D7238
	ldr r0, [r6, #0x60]
	cmp r0, #0
	bge _080D7238
	ldrb r0, [r6, #0x13]
	adds r2, r0, #1
	strb r2, [r6, #0x13]
	ldr r3, _080D7248 @ =gSineTable
	adds r0, #0x41
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r1, [r0, r4]
	lsls r1, r1, #2
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x64]
	lsls r2, r2, #0x19
	lsrs r2, r2, #0x17
	adds r2, r2, r3
	movs r0, #0
	ldrsh r1, [r2, r0]
	lsls r1, r1, #3
	ldr r0, [r6, #0x58]
	subs r0, r0, r1
	str r0, [r6, #0x68]
_080D7238:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080D7240: .4byte gStageRun+232
_080D7244: .4byte 0x00000FFF
_080D7248: .4byte gSineTable
