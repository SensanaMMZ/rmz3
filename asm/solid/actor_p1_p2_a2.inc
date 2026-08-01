	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Actor25_Update
Actor25_Update: @ 0x080D3280
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #9
	bls _080D328E
	b _080D358C
_080D328E:
	lsls r0, r0, #2
	ldr r1, _080D3298 @ =_080D329C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D3298: .4byte _080D329C
_080D329C: @ jump table
	.4byte _080D32C4 @ case 0
	.4byte _080D3352 @ case 1
	.4byte _080D336C @ case 2
	.4byte _080D339C @ case 3
	.4byte _080D33BA @ case 4
	.4byte _080D33DA @ case 5
	.4byte _080D3412 @ case 6
	.4byte _080D3478 @ case 7
	.4byte _080D356C @ case 8
	.4byte _080D3584 @ case 9
_080D32C4:
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	bl FUN_08009f6c
	str r0, [r7, #0x58]
	ldrb r6, [r7, #0x11]
	movs r0, #0xf
	ands r0, r6
	strb r0, [r7, #0x11]
	ldrb r4, [r7, #0x11]
	adds r4, #0xf5
	lsls r5, r4, #2
	adds r5, r5, r4
	lsls r5, r5, #2
	ldr r1, _080D333C @ =gStaticMotionGraphics
	adds r0, r5, r1
	ldr r1, _080D3340 @ =wStaticGraphicTilenums
	lsls r4, r4, #1
	adds r1, r4, r1
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r3, _080D3344 @ =gStaticMotionGraphics+12
	adds r5, r5, r3
	ldr r0, _080D3348 @ =wStaticMotionPalIDs
	adds r4, r4, r0
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r0, #0x80
	lsls r0, r0, #2
	adds r1, r1, r0
	adds r0, r5, #0
	bl LoadPalette
	ldrb r1, [r7, #0x11]
	adds r1, #0xf5
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x10
	adds r0, r7, #0
	bl SetMotion
	cmp r6, #0xf
	bhi _080D334C
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0xd]
	adds r0, #2
	strb r0, [r7, #0xd]
	b _080D358C
	.align 2, 0
_080D333C: .4byte gStaticMotionGraphics
_080D3340: .4byte wStaticGraphicTilenums
_080D3344: .4byte gStaticMotionGraphics+12
_080D3348: .4byte wStaticMotionPalIDs
_080D334C:
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D3352:
	ldrb r1, [r7, #0x11]
	adds r1, #0xf5
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x10
	adds r0, r7, #0
	movs r2, #0
	bl FUN_080d0aa0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080D336A
	b _080D358C
_080D336A:
	b _080D357C
_080D336C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D3380
	b _080D358C
_080D3380:
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xf8
	bl StartPaletteAnimation
	b _080D357C
_080D339C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	movs r0, #0xf8
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	beq _080D33B2
	b _080D358C
_080D33B2:
	movs r0, #0xf8
	bl RemovePaletteAnimation
	b _080D357C
_080D33BA:
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	orrs r1, r0
	movs r0, #0xf9
	bl StartPaletteAnimation
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D33DA:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	movs r0, #0xf9
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #4
	beq _080D33F0
	b _080D358C
_080D33F0:
	movs r0, #0xf9
	bl RemovePaletteAnimation
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xfa
	bl StartPaletteAnimation
	b _080D357C
_080D3412:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	movs r0, #0xfa
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	beq _080D3428
	b _080D358C
_080D3428:
	ldr r0, [r7, #0x54]
	str r0, [r7, #0x64]
	ldr r5, _080D34A0 @ =s32_ARRAY_08370de8
	ldrb r0, [r7, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r1, [r0]
	lsls r1, r1, #7
	ldr r0, [r7, #0x58]
	subs r0, r0, r1
	str r0, [r7, #0x68]
	adds r0, r7, #0
	adds r0, #0x64
	movs r1, #1
	movs r2, #0
	bl CreateVFX39
	str r0, [r7, #0x28]
	adds r0, #0x74
	movs r4, #0
	movs r1, #0x1f
	strb r1, [r0]
	ldr r0, [r7, #0x28]
	adds r0, #0x75
	strb r1, [r0]
	ldr r0, [r7, #0x28]
	adds r0, #0x76
	strb r1, [r0]
	movs r0, #0x58
	bl PlaySound
	strb r4, [r7, #0x12]
	ldrb r0, [r7, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r0, [r0]
	str r0, [r7, #0x5c]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D3478:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	adds r3, r0, #1
	strb r3, [r7, #0x12]
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x1f
	bhi _080D34A8
	ldr r2, [r7, #0x28]
	ldr r1, _080D34A4 @ =gSineTable
	lsls r0, r3, #0x19
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r3, #0
	ldrsh r1, [r0, r3]
	ldr r0, [r7, #0x5c]
	b _080D34EA
	.align 2, 0
_080D34A0: .4byte s32_ARRAY_08370de8
_080D34A4: .4byte gSineTable
_080D34A8:
	cmp r0, #0x20
	bne _080D34C0
	ldr r1, [r7, #0x28]
	ldr r0, [r7, #0x5c]
	subs r0, #2
	lsls r0, r0, #8
	str r0, [r1, #0x78]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	b _080D3556
_080D34C0:
	cmp r0, #0x35
	bhi _080D34D0
	ldr r1, [r7, #0x28]
	ldr r0, [r7, #0x5c]
	subs r0, #4
	lsls r0, r0, #8
	str r0, [r1, #0x78]
	b _080D3556
_080D34D0:
	cmp r0, #0x3f
	bhi _080D34F4
	ldr r2, [r7, #0x28]
	ldr r1, _080D34F0 @ =gSineTable
	movs r0, #0x40
	subs r0, r0, r3
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r3, #0
	ldrsh r1, [r0, r3]
	ldr r0, [r7, #0x5c]
	subs r0, #4
_080D34EA:
	muls r0, r1, r0
	str r0, [r2, #0x78]
	b _080D3556
	.align 2, 0
_080D34F0: .4byte gSineTable
_080D34F4:
	movs r4, #0
	ldr r5, _080D3568 @ =s32_ARRAY_08370de8
_080D34F8:
	lsls r1, r4, #0x18
	lsrs r1, r1, #0x18
	ldr r2, [r7, #0x54]
	ldr r3, [r7, #0x58]
	ldrb r0, [r7, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r0, [r0]
	str r0, [sp]
	movs r0, #0
	str r0, [sp, #4]
	movs r0, #2
	bl FUN_080c5684
	lsls r0, r4, #0x10
	movs r1, #0x80
	lsls r1, r1, #0xc
	adds r0, r0, r1
	lsrs r4, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xff
	ble _080D34F8
	ldr r0, [r7, #0x28]
	adds r0, #0x77
	movs r1, #1
	strb r1, [r0]
	movs r0, #0xfa
	bl RemovePaletteAnimation
	ldrb r4, [r7, #0x11]
	adds r4, #0xfb
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	adds r0, r4, #0
	bl StartPaletteAnimation
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D3556:
	ldr r2, [r7, #0x28]
	ldrb r0, [r7, #0x12]
	movs r1, #1
	ands r1, r0
	lsls r1, r1, #0xb
	ldr r0, [r2, #0x78]
	adds r0, r0, r1
	str r0, [r2, #0x78]
	b _080D358C
	.align 2, 0
_080D3568: .4byte s32_ARRAY_08370de8
_080D356C:
	ldrb r0, [r7, #0x11]
	adds r0, #0xfb
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _080D358C
_080D357C:
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
	b _080D358C
_080D3584:
	ldrb r0, [r7, #0x11]
	adds r0, #0xfb
	bl RemovePaletteAnimation
_080D358C:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
