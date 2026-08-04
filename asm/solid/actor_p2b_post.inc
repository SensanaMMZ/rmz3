	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Actor65_Update
Actor65_Update: @ 0x080D7ACC
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #5
	bls _080D7AD8
	b _080D7D04
_080D7AD8:
	lsls r0, r0, #2
	ldr r1, _080D7AE4 @ =_080D7AE8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D7AE4: .4byte _080D7AE8
_080D7AE8: @ jump table
	.4byte _080D7B00 @ case 0
	.4byte _080D7B8C @ case 1
	.4byte _080D7BF4 @ case 2
	.4byte _080D7C20 @ case 3
	.4byte _080D7CCC @ case 4
	.4byte _080D7D04 @ case 5
_080D7B00:
	movs r4, #0xb8
	ldr r0, _080D7BD0 @ =wStaticGraphicTilenums
	lsls r2, r4, #1
	adds r0, r0, r2
	movs r6, #0
	movs r1, #0xe0
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r5, _080D7BD4 @ =wStaticMotionPalIDs
	adds r5, r5, r2
	movs r0, #8
	strh r0, [r5]
	lsls r4, r4, #4
	movs r0, #0xb8
	lsls r0, r0, #2
	adds r4, r4, r0
	ldr r2, _080D7BD8 @ =gStaticMotionGraphics
	adds r0, r4, r2
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D7BDC @ =gStaticMotionGraphics+12
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
	adds r0, r7, #0
	bl SetMotion
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	bl FUN_08009f6c
	ldr r4, _080D7BE0 @ =0xFFFFE800
	adds r0, r0, r4
	str r0, [r7, #0x58]
	str r6, [r7, #0x60]
	movs r0, #0x10
	str r0, [r7, #0x68]
	movs r3, #0x10
	movs r2, #0x5f
_080D7B70:
	ldr r1, [r7, #0x60]
	adds r1, r1, r3
	str r1, [r7, #0x60]
	ldr r0, [r7, #0x58]
	subs r0, r0, r1
	str r0, [r7, #0x58]
	subs r2, #1
	cmp r2, #0
	bge _080D7B70
	movs r0, #0
	strb r0, [r7, #0x13]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D7B8C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x58]
	ldr r1, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, [r7, #0x68]
	subs r4, r1, r0
	str r4, [r7, #0x60]
	cmp r4, #0
	beq _080D7BA6
	b _080D7D04
_080D7BA6:
	ldr r1, _080D7BE4 @ =gPaletteManager
	ldr r0, _080D7BE8 @ =0x00000404
	adds r2, r1, r0
	movs r0, #0x40
	strh r0, [r2]
	ldr r2, _080D7BEC @ =0x00000406
	adds r1, r1, r2
	movs r0, #0xe0
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r1, _080D7BF0 @ =0x0000B801
	adds r0, r7, #0
	bl SetMotion
	str r4, [r7, #0x60]
	ldrb r1, [r7, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r7, #0xa]
	b _080D7CFE
	.align 2, 0
_080D7BD0: .4byte wStaticGraphicTilenums
_080D7BD4: .4byte wStaticMotionPalIDs
_080D7BD8: .4byte gStaticMotionGraphics
_080D7BDC: .4byte gStaticMotionGraphics+12
_080D7BE0: .4byte 0xFFFFE800
_080D7BE4: .4byte gPaletteManager
_080D7BE8: .4byte 0x00000404
_080D7BEC: .4byte 0x00000406
_080D7BF0: .4byte 0x0000B801
_080D7BF4:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D7C06
	b _080D7D04
_080D7C06:
	ldr r1, _080D7C18 @ =0x0000B802
	adds r0, r7, #0
	bl SetMotion
	ldr r0, _080D7C1C @ =0x0000013D
	bl PlaySound
	b _080D7CFE
	.align 2, 0
_080D7C18: .4byte 0x0000B802
_080D7C1C: .4byte 0x0000013D
_080D7C20:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D7C38
	ldr r1, _080D7CA4 @ =0x0000B802
	adds r0, r7, #0
	bl SetMotion
_080D7C38:
	ldr r2, _080D7CA8 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080D7CAC @ =0x000343FD
	muls r0, r1, r0
	ldr r4, _080D7CB0 @ =0x00269EC3
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #0
	bne _080D7C5C
	ldr r1, _080D7CB4 @ =0x0000B803
	adds r0, r7, #0
	bl SetMotion
_080D7C5C:
	ldr r0, [r7, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D7D04
	ldr r0, _080D7CB8 @ =0x0000013D
	bl StopSound
	ldr r1, _080D7CBC @ =gPaletteManager
	ldr r0, _080D7CC0 @ =0x00000404
	adds r2, r1, r0
	movs r4, #0x40
	movs r0, #0x40
	strh r0, [r2]
	ldr r2, _080D7CC4 @ =0x00000406
	adds r1, r1, r2
	movs r0, #0xe0
	lsls r0, r0, #1
	strh r0, [r1]
	movs r1, #0xb8
	lsls r1, r1, #8
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	adds r0, #0x64
	str r0, [r7, #0x40]
	ldrb r1, [r7, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r7, #0xa]
	ldr r0, _080D7CC8 @ =0xFFFFFF00
	str r0, [r7, #0x60]
	strb r4, [r7, #0x13]
	b _080D7CFE
	.align 2, 0
_080D7CA4: .4byte 0x0000B802
_080D7CA8: .4byte RNG_0202f388
_080D7CAC: .4byte 0x000343FD
_080D7CB0: .4byte 0x00269EC3
_080D7CB4: .4byte 0x0000B803
_080D7CB8: .4byte 0x0000013D
_080D7CBC: .4byte gPaletteManager
_080D7CC0: .4byte 0x00000404
_080D7CC4: .4byte 0x00000406
_080D7CC8: .4byte 0xFFFFFF00
_080D7CCC:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D7D04
	ldr r0, [r7, #0x58]
	ldr r1, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, _080D7D54 @ =gStageRun+232
	adds r1, r7, #0
	adds r1, #0x54
	bl CalcFromCamera
	ldr r1, _080D7D58 @ =0x00000FFF
	cmp r0, r1
	bls _080D7D04
	ldrb r0, [r7, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r7, #0xa]
_080D7CFE:
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D7D04:
	ldrb r0, [r7, #0x1e]
	lsls r0, r0, #8
	adds r1, r7, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	movs r1, #0xb8
	lsls r1, r1, #8
	cmp r0, r1
	bne _080D7D4C
	ldr r0, [r7, #0x60]
	cmp r0, #0
	bge _080D7D4C
	ldrb r0, [r7, #0x13]
	adds r2, r0, #1
	strb r2, [r7, #0x13]
	ldr r3, _080D7D5C @ =gSineTable
	adds r0, #0x41
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r1, [r0, r4]
	lsls r1, r1, #2
	ldr r0, [r7, #0x54]
	adds r0, r0, r1
	str r0, [r7, #0x64]
	lsls r2, r2, #0x19
	lsrs r2, r2, #0x17
	adds r2, r2, r3
	movs r0, #0
	ldrsh r1, [r2, r0]
	lsls r1, r1, #3
	ldr r0, [r7, #0x58]
	subs r0, r0, r1
	str r0, [r7, #0x68]
_080D7D4C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080D7D54: .4byte gStageRun+232
_080D7D58: .4byte 0x00000FFF
_080D7D5C: .4byte gSineTable
