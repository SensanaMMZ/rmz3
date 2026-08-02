	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080d98e8
FUN_080d98e8: @ 0x080D98E8
	push {r4, r5, lr}
	adds r5, r0, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0xba
	ldrh r1, [r0]
	ldr r0, _080D9C50 @ =0x00000241
	cmp r1, r0
	bne _080D9930
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D9930
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r2, [r0]
	ldrb r1, [r2, #0x1a]
	movs r0, #4
	orrs r0, r1
	strb r0, [r2, #0x1a]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C68 @ =0x00000716
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9930:
	adds r0, r5, #0
	adds r0, #0xba
	ldrh r2, [r0]
	ldr r1, _080D9C70 @ =0x000002CF
	adds r4, r0, #0
	cmp r2, r1
	bne _080D9972
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D9972
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r2, [r0]
	ldrb r1, [r2, #0x1a]
	movs r0, #4
	orrs r0, r1
	strb r0, [r2, #0x1a]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C68 @ =0x00000716
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9972:
	ldrh r1, [r4]
	ldr r0, _080D9C74 @ =0x00000247
	cmp r1, r0
	bne _080D99B0
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D99B0
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r2, [r0]
	ldrb r1, [r2, #0x1c]
	movs r0, #8
	orrs r0, r1
	strb r0, [r2, #0x1c]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	movs r1, #0xe5
	lsls r1, r1, #3
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D99B0:
	ldrh r1, [r4]
	ldr r0, _080D9C78 @ =0x0000024E
	cmp r1, r0
	bne _080D99EE
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D99EE
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r1, [r0]
	adds r1, #0x2a
	ldrb r2, [r1]
	movs r0, #1
	orrs r0, r2
	strb r0, [r1]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C7C @ =0x00000792
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D99EE:
	ldrh r1, [r4]
	ldr r0, _080D9C80 @ =0x00000253
	cmp r1, r0
	bne _080D9A2C
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D9A2C
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r1, [r0]
	adds r1, #0x2b
	ldrb r2, [r1]
	movs r0, #4
	orrs r0, r2
	strb r0, [r1]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C84 @ =0x0000079E
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9A2C:
	ldrh r1, [r4]
	ldr r0, _080D9C88 @ =0x0000025A
	cmp r1, r0
	bne _080D9A60
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r1, [r0]
	adds r1, #0x29
	ldrb r2, [r1]
	movs r0, #4
	orrs r0, r2
	strb r0, [r1]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C8C @ =0x0000078E
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9A60:
	ldrh r1, [r4]
	ldr r0, _080D9C90 @ =0x0000025D
	cmp r1, r0
	bne _080D9A94
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r2, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #8
	orrs r0, r1
	strb r0, [r2, #0xa]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	movs r1, #0xd3
	lsls r1, r1, #3
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9A94:
	ldrh r1, [r4]
	ldr r0, _080D9C94 @ =0x00000271
	cmp r1, r0
	bne _080D9AD2
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D9AD2
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r1, [r0]
	adds r1, #0x2b
	ldrb r2, [r1]
	movs r0, #1
	orrs r0, r2
	strb r0, [r1]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C98 @ =0x0000079A
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9AD2:
	ldrh r1, [r4]
	movs r0, #0xa1
	lsls r0, r0, #2
	cmp r1, r0
	bne _080D9B08
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r1, [r0]
	adds r1, #0x2b
	ldrb r2, [r1]
	movs r0, #2
	orrs r0, r2
	strb r0, [r1]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9C9C @ =0x0000079C
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9B08:
	ldrh r1, [r4]
	ldr r0, _080D9CA0 @ =0x000002A6
	cmp r1, r0
	bne _080D9B3A
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r2, [r0]
	ldrb r1, [r2, #0xe]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0xe]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9CA4 @ =0x000006B4
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9B3A:
	ldrh r2, [r4]
	movs r0, #0xb2
	lsls r0, r0, #2
	cmp r2, r0
	bne _080D9B4C
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x20
	str r0, [r1]
_080D9B4C:
	movs r0, #0xb0
	lsls r0, r0, #2
	cmp r2, r0
	bne _080D9B5C
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x34
	str r0, [r1]
_080D9B5C:
	ldr r0, _080D9CAC @ =0x000002C2
	cmp r2, r0
	bne _080D9B6A
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x20
	str r0, [r1]
_080D9B6A:
	movs r0, #0xb1
	lsls r0, r0, #2
	cmp r2, r0
	bne _080D9B7A
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x34
	str r0, [r1]
_080D9B7A:
	ldr r0, _080D9CB0 @ =0x000002C6
	cmp r2, r0
	bne _080D9B88
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x28
	str r0, [r1]
_080D9B88:
	movs r0, #0xaf
	lsls r0, r0, #2
	cmp r2, r0
	bne _080D9B98
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x20
	str r0, [r1]
_080D9B98:
	ldr r0, _080D9CB4 @ =0x000002BE
	cmp r2, r0
	bne _080D9BA6
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x34
	str r0, [r1]
_080D9BA6:
	ldr r0, _080D9CB8 @ =0x000002BA
	cmp r2, r0
	bne _080D9BB4
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x64
	str r0, [r1]
_080D9BB4:
	ldrh r1, [r4]
	ldr r0, _080D9CBC @ =0x000002CA
	cmp r1, r0
	bne _080D9BC4
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x34
	str r0, [r1]
_080D9BC4:
	ldrh r1, [r4]
	ldr r0, _080D9CC0 @ =0x000002B6
	cmp r1, r0
	bne _080D9BE8
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D9BE8
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0xc8
	str r0, [r1]
	ldr r1, _080D9CC4 @ =gCurStory
	adds r1, #0x24
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
_080D9BE8:
	ldrh r1, [r4]
	movs r0, #0xad
	lsls r0, r0, #2
	cmp r1, r0
	bne _080D9BFA
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x34
	str r0, [r1]
_080D9BFA:
	ldrh r1, [r4]
	ldr r0, _080D9CC8 @ =0x000002B1
	cmp r1, r0
	bne _080D9C36
	ldr r0, _080D9C54 @ =gTextWindow+8
	movs r1, #0x16
	ldrsh r0, [r0, r1]
	cmp r0, #9
	bne _080D9C36
	ldr r0, _080D9C58 @ =gStageDiskManager
	ldr r2, [r0]
	ldrb r1, [r2, #5]
	movs r0, #4
	orrs r0, r1
	strb r0, [r2, #5]
	ldr r2, _080D9C5C @ =gTextPrinter
	ldr r0, _080D9C60 @ =0x00000594
	adds r2, r2, r0
	ldr r0, _080D9C64 @ =StringOfsTable
	ldr r1, _080D9CCC @ =0x0000066E
	adds r0, r0, r1
	ldrh r0, [r0]
	ldr r1, _080D9C6C @ =gStringData
	adds r0, r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #1
	movs r1, #0x5a
	bl PrintTextWindow
_080D9C36:
	ldrh r1, [r4]
	movs r0, #0xae
	lsls r0, r0, #2
	cmp r1, r0
	bne _080D9C48
	ldr r1, _080D9CA8 @ =gECrystalGainAmount
	ldr r0, [r1]
	adds r0, #0x50
	str r0, [r1]
_080D9C48:
	movs r0, #0
	strb r0, [r5, #0xd]
	strb r0, [r5, #0xe]
	b _080D9CD0
	.align 2, 0
_080D9C50: .4byte 0x00000241
_080D9C54: .4byte gTextWindow+8
_080D9C58: .4byte gStageDiskManager
_080D9C5C: .4byte gTextPrinter
_080D9C60: .4byte 0x00000594
_080D9C64: .4byte StringOfsTable
_080D9C68: .4byte 0x00000716
_080D9C6C: .4byte gStringData
_080D9C70: .4byte 0x000002CF
_080D9C74: .4byte 0x00000247
_080D9C78: .4byte 0x0000024E
_080D9C7C: .4byte 0x00000792
_080D9C80: .4byte 0x00000253
_080D9C84: .4byte 0x0000079E
_080D9C88: .4byte 0x0000025A
_080D9C8C: .4byte 0x0000078E
_080D9C90: .4byte 0x0000025D
_080D9C94: .4byte 0x00000271
_080D9C98: .4byte 0x0000079A
_080D9C9C: .4byte 0x0000079C
_080D9CA0: .4byte 0x000002A6
_080D9CA4: .4byte 0x000006B4
_080D9CA8: .4byte gECrystalGainAmount
_080D9CAC: .4byte 0x000002C2
_080D9CB0: .4byte 0x000002C6
_080D9CB4: .4byte 0x000002BE
_080D9CB8: .4byte 0x000002BA
_080D9CBC: .4byte 0x000002CA
_080D9CC0: .4byte 0x000002B6
_080D9CC4: .4byte gCurStory
_080D9CC8: .4byte 0x000002B1
_080D9CCC: .4byte 0x0000066E
_080D9CD0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
