	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Actor32_Update
Actor32_Update: @ 0x080D3E28
	push {r4, r5, lr}
	adds r3, r0, #0
	ldrb r0, [r3, #0xd]
	ldr r5, _080D3E40 @ =gWindowRegBuffer
	cmp r0, #4
	bhi _080D3EDC
	lsls r0, r0, #2
	ldr r1, _080D3E44 @ =_080D3E48
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D3E40: .4byte gWindowRegBuffer
_080D3E44: .4byte _080D3E48
_080D3E48: @ jump table
	.4byte _080D3E5C @ case 0
	.4byte _080D3E72 @ case 1
	.4byte _080D3E94 @ case 2
	.4byte _080D3EC0 @ case 3
	.4byte _080D3EDC @ case 4
_080D3E5C:
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r3, #0x54]
	movs r0, #0x92
	lsls r0, r0, #8
	str r0, [r3, #0x58]
	movs r0, #0
	strb r0, [r3, #0x13]
	ldrb r0, [r3, #0xd]
	adds r0, #1
	strb r0, [r3, #0xd]
_080D3E72:
	ldr r0, [r3, #0x58]
	ldr r1, _080D3F08 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [r3, #0x58]
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldr r5, _080D3F0C @ =gWindowRegBuffer
	cmp r0, #0x3f
	bls _080D3EDC
	movs r0, #0
	strb r0, [r3, #0x13]
	ldrb r0, [r3, #0xd]
	adds r0, #1
	strb r0, [r3, #0xd]
_080D3E94:
	ldr r1, _080D3F10 @ =gSineTable
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
	movs r0, #0xb8
	muls r0, r1, r0
	str r0, [r3, #0x54]
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldr r5, _080D3F0C @ =gWindowRegBuffer
	cmp r0, #0x3f
	bls _080D3EDC
	movs r0, #0x10
	strb r0, [r3, #0x13]
	ldrb r0, [r3, #0xd]
	adds r0, #1
	strb r0, [r3, #0xd]
_080D3EC0:
	ldrb r0, [r3, #0x13]
	subs r0, #1
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	ldr r5, _080D3F0C @ =gWindowRegBuffer
	cmp r0, #0
	bne _080D3EDC
	ldrh r0, [r5]
	ldr r1, _080D3F14 @ =0x0000BFFF
	ands r1, r0
	strh r1, [r5]
	ldrb r0, [r3, #0xd]
	adds r0, #1
	strb r0, [r3, #0xd]
_080D3EDC:
	ldrb r0, [r3, #0x12]
	adds r0, #1
	strb r0, [r3, #0x12]
	ldr r2, [r3, #0x54]
	asrs r2, r2, #8
	movs r1, #1
	ands r0, r1
	lsls r0, r0, #3
	adds r2, r2, r0
	adds r1, r2, #0
	adds r1, #0xc0
	adds r4, r5, #0
	movs r0, #0xc0
	subs r0, r0, r2
	lsls r2, r0, #8
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #0xf0
	bgt _080D3F18
	movs r0, #0xff
	ands r0, r1
	b _080D3F1A
	.align 2, 0
_080D3F08: .4byte 0xFFFFF800
_080D3F0C: .4byte gWindowRegBuffer
_080D3F10: .4byte gSineTable
_080D3F14: .4byte 0x0000BFFF
_080D3F18:
	movs r0, #0xf0
_080D3F1A:
	orrs r0, r2
	strh r0, [r4, #6]
	ldr r1, [r3, #0x58]
	asrs r1, r1, #8
	ldrb r2, [r3, #0x12]
	movs r0, #1
	ands r0, r2
	lsls r0, r0, #3
	subs r1, r1, r0
	adds r2, r0, #0
	adds r2, #0x93
	movs r0, #0xff
	ands r2, r0
	lsls r1, r1, #0x10
	asrs r0, r1, #0x10
	cmp r0, #0
	blt _080D3F40
	lsls r0, r0, #8
	orrs r2, r0
_080D3F40:
	strh r2, [r5, #0xa]
	ldr r1, _080D3F50 @ =gPaletteManager
	ldr r2, _080D3F54 @ =0x00007FFF
	adds r0, r2, #0
	strh r0, [r1]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080D3F50: .4byte gPaletteManager
_080D3F54: .4byte 0x00007FFF

	thumb_func_start Actor33_Update
Actor33_Update: @ 0x080D3F58
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #0xe
	bls _080D3F64
	b _080D4108
_080D3F64:
	lsls r0, r0, #2
	ldr r1, _080D3F70 @ =_080D3F74
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D3F70: .4byte _080D3F74
_080D3F74: @ jump table
	.4byte _080D3FB0 @ case 0
	.4byte _080D3FC8 @ case 1
	.4byte _080D4006 @ case 2
	.4byte _080D402C @ case 3
	.4byte _080D403E @ case 4
	.4byte _080D405C @ case 5
	.4byte _080D406A @ case 6
	.4byte _080D4080 @ case 7
	.4byte _080D4092 @ case 8
	.4byte _080D40A6 @ case 9
	.4byte _080D40B6 @ case 10
	.4byte _080D40C4 @ case 11
	.4byte _080D40D4 @ case 12
	.4byte _080D40F4 @ case 13
	.4byte _080D4102 @ case 14
_080D3FB0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D3FC8:
	ldr r1, _080D404C @ =gPaletteManager
	ldr r0, _080D4050 @ =0x00000404
	adds r2, r1, r0
	movs r0, #0x40
	strh r0, [r2]
	ldr r0, _080D4054 @ =0x00000406
	adds r1, r1, r0
	movs r0, #0xe0
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D3FEA
	b _080D4108
_080D3FEA:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080D4058 @ =0x00003503
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D4006:
	ldr r1, _080D404C @ =gPaletteManager
	ldr r0, _080D4050 @ =0x00000404
	adds r2, r1, r0
	movs r0, #0x40
	strh r0, [r2]
	ldr r0, _080D4054 @ =0x00000406
	adds r1, r1, r0
	movs r0, #0xe0
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D4108
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D402C:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080D4108
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D403E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #8
	b _080D40E6
	.align 2, 0
_080D404C: .4byte gPaletteManager
_080D4050: .4byte 0x00000404
_080D4054: .4byte 0x00000406
_080D4058: .4byte 0x00003503
_080D405C:
	ldr r1, _080D407C @ =0x00003501
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D406A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D4108
	b _080D40EC
	.align 2, 0
_080D407C: .4byte 0x00003501
_080D4080:
	adds r0, r4, #0
	movs r1, #0
	bl SetMotion
	movs r0, #4
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D4092:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D4108
	b _080D40EC
_080D40A6:
	movs r1, #0xcc
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D40B6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x10
	b _080D40E6
_080D40C4:
	movs r1, #0xc4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D40D4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	subs r0, #0x50
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x20
_080D40E6:
	ands r0, r1
	cmp r0, #0
	beq _080D4108
_080D40EC:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	b _080D4108
_080D40F4:
	ldr r1, _080D4110 @ =0x00003303
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D4102:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080D4108:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080D4110: .4byte 0x00003303
