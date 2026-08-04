	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Actor10_Update
Actor10_Update: @ 0x080D1F18
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #8
	bls _080D1F24
	b _080D21E8
_080D1F24:
	lsls r0, r0, #2
	ldr r1, _080D1F30 @ =_080D1F34
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D1F30: .4byte _080D1F34
_080D1F34: @ jump table
	.4byte _080D1F58 @ case 0
	.4byte _080D1FDE @ case 1
	.4byte _080D2024 @ case 2
	.4byte _080D203E @ case 3
	.4byte _080D2054 @ case 4
	.4byte _080D2064 @ case 5
	.4byte _080D2114 @ case 6
	.4byte _080D2180 @ case 7
	.4byte _080D21E8 @ case 8
_080D1F58:
	ldr r0, _080D2004 @ =0x085D79AC
	ldr r1, _080D2008 @ =wStaticGraphicTilenums
	ldrh r1, [r1, #0x12]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D200C @ =gStaticMotionGraphics+((20*9)+12)
	ldr r1, _080D2010 @ =wStaticMotionPalIDs
	ldrh r1, [r1, #0x12]
	ldrb r2, [r0, #7]
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	bl LoadPalette
	adds r0, r6, #0
	bl InitRotatableMotion
	ldr r1, _080D2014 @ =0x00000902
	adds r0, r6, #0
	bl SetMotion
	adds r1, r6, #0
	adds r1, #0x24
	movs r0, #0x40
	strb r0, [r1]
	movs r2, #1
	ldrb r1, [r6, #0xa]
	movs r0, #0x20
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4d
	strb r2, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	movs r2, #0x20
	ldrb r1, [r3]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_0800a31c
	movs r1, #0xe0
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r6, #0x64]
	ldr r0, _080D2018 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r2, _080D201C @ =0x00009BFF
	adds r0, r0, r2
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D1FDE:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r1, _080D2020 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r1, [r6, #0x64]
	cmp r0, r1
	blt _080D1FF4
	b _080D21E8
_080D1FF4:
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #0x10
	bl AppendQuake
	ldr r0, [r6, #0x64]
	str r0, [r6, #0x54]
	b _080D21E2
	.align 2, 0
_080D2004: .4byte gStaticMotionGraphics+(20*9)
_080D2008: .4byte wStaticGraphicTilenums
_080D200C: .4byte gStaticMotionGraphics+(20*9)+12
_080D2010: .4byte wStaticMotionPalIDs
_080D2014: .4byte 0x00000902
_080D2018: .4byte gStageRun+232
_080D201C: .4byte 0x00009BFF
_080D2020: .4byte 0xFFFFF800
_080D2024:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D2038
	b _080D21E8
_080D2038:
	movs r0, #0x1e
	strb r0, [r6, #0x12]
	b _080D21E2
_080D203E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D2052
	b _080D21E8
_080D2052:
	b _080D21E2
_080D2054:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, [r6, #0x54]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	b _080D21CC
_080D2064:
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _080D2072
	b _080D21E8
_080D2072:
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r0, _080D2154 @ =0x085D79AC
	ldr r1, _080D2158 @ =wStaticGraphicTilenums
	ldrh r1, [r1, #0x12]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D215C @ =gStaticMotionGraphics+((20*9)+12)
	ldr r1, _080D2160 @ =wStaticMotionPalIDs
	ldrh r1, [r1, #0x12]
	ldrb r2, [r0, #7]
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	bl LoadPalette
	ldr r1, _080D2164 @ =0x00000902
	adds r0, r6, #0
	bl SetMotion
	adds r1, r6, #0
	adds r1, #0x24
	movs r0, #0x20
	strb r0, [r1]
	movs r5, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4d
	strb r5, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080D2168 @ =sCollisions_08370B58
	adds r2, #0xa
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _080D216C @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r2, _080D2170 @ =0x000097FF
	adds r1, r0, r2
	str r1, [r6, #0x54]
	ldr r1, _080D2174 @ =0x00001FFF
	adds r0, r0, r1
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	str r0, [r6, #0x68]
	ldr r2, _080D2178 @ =0xFFFFD000
	adds r0, r0, r2
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D2114:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r1, _080D217C @ =0xFFFFFA00
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	lsls r0, r1, #6
	subs r0, r0, r1
	ldr r1, [r6, #0x68]
	adds r0, r0, r1
	asrs r0, r0, #6
	str r0, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _080D21E8
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #4
	bl AppendQuake
	movs r0, #0
	str r0, [r6, #0x5c]
	movs r0, #0xf
	strb r0, [r6, #0x12]
	b _080D21E2
	.align 2, 0
_080D2154: .4byte gStaticMotionGraphics+(20*9)
_080D2158: .4byte wStaticGraphicTilenums
_080D215C: .4byte gStaticMotionGraphics+((20*9)+12)
_080D2160: .4byte wStaticMotionPalIDs
_080D2164: .4byte 0x00000902
_080D2168: .4byte sCollisions_08370B58
_080D216C: .4byte gStageRun+232
_080D2170: .4byte 0x000097FF
_080D2174: .4byte 0x00001FFF
_080D2178: .4byte 0xFFFFD000
_080D217C: .4byte 0xFFFFFA00
_080D2180:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, [r6, #0x58]
	lsls r0, r1, #6
	subs r0, r0, r1
	ldr r2, _080D21B4 @ =0xFFFFD000
	adds r0, r0, r2
	ldr r1, [r6, #0x68]
	adds r0, r0, r1
	asrs r0, r0, #6
	str r0, [r6, #0x58]
	adds r2, r6, #0
	adds r2, #0x24
	ldrb r1, [r2]
	lsls r0, r1, #4
	subs r0, r0, r1
	adds r0, #0x4f
	asrs r0, r0, #4
	strb r0, [r2]
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080D21B8
	subs r0, #1
	strb r0, [r6, #0x12]
	b _080D21E8
	.align 2, 0
_080D21B4: .4byte 0xFFFFD000
_080D21B8:
	ldr r1, [r6, #0x5c]
	lsls r0, r1, #5
	subs r0, r0, r1
	movs r1, #0xc0
	lsls r1, r1, #3
	adds r0, r0, r1
	asrs r0, r0, #5
	str r0, [r6, #0x5c]
	ldr r1, [r6, #0x54]
	adds r1, r1, r0
_080D21CC:
	str r1, [r6, #0x54]
	ldr r0, _080D21F0 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r2, _080D21F4 @ =0x000097FF
	adds r0, r0, r2
	cmp r1, r0
	blt _080D21E8
	ldrb r0, [r6, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r6, #0xa]
_080D21E2:
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D21E8:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080D21F0: .4byte gStageRun+232
_080D21F4: .4byte 0x000097FF
