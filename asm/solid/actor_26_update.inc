	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #1
	beq _080D360C
	cmp r0, #1
	bgt _080D368C
	cmp r0, #0
	bne _080D368C
	ldr r1, _080D3694 @ =wStaticGraphicTilenums
	adds r1, #0xa2
	ldrh r0, [r1]
	str r0, [r7, #0x64]
	ldr r5, _080D3698 @ =wStaticMotionPalIDs
	adds r5, #0xa2
	ldrh r0, [r5]
	str r0, [r7, #0x68]
	ldr r0, [r7, #0x54]
	str r0, [r7, #0x5c]
	ldr r0, [r7, #0x58]
	str r0, [r7, #0x60]
	movs r6, #0
	ldr r0, _080D369C @ =0x00000305
	strh r0, [r1]
	movs r0, #8
	strh r0, [r5]
	ldr r4, _080D36A0 @ =0x00000654
	ldr r2, _080D36A4 @ =gStaticMotionGraphics
	adds r0, r4, r2
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D36A8 @ =gStaticMotionGraphics+12
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
	movs r1, #0xa2
	lsls r1, r1, #7
	adds r0, r7, #0
	bl SetMotion
	strb r6, [r7, #0x12]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D360C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r1, [r7, #0x12]
	movs r0, #0xf
	ands r0, r1
	cmp r0, #0
	bne _080D3628
	ldr r2, [r7, #0x54]
	ldr r3, [r7, #0x58]
	movs r0, #3
	movs r1, #0
	bl FUN_080c5628
_080D3628:
	ldrb r1, [r7, #0x12]
	adds r1, #1
	strb r1, [r7, #0x12]
	ldr r2, [r7, #0x5c]
	movs r4, #0x80
	lsls r4, r4, #2
	adds r2, r2, r4
	str r2, [r7, #0x5c]
	ldr r3, _080D36AC @ =gSineTable
	lsls r0, r1, #0x19
	movs r4, #0x80
	lsls r4, r4, #0x17
	adds r0, r0, r4
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r0, [r0, r4]
	lsls r0, r0, #1
	adds r2, r2, r0
	str r2, [r7, #0x54]
	lsls r1, r1, #0x1a
	lsrs r1, r1, #0x17
	adds r1, r1, r3
	movs r0, #0
	ldrsh r1, [r1, r0]
	lsls r1, r1, #2
	ldr r0, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, _080D36B0 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r1, _080D36B4 @ =0x000097FF
	adds r0, r0, r1
	cmp r2, r0
	blt _080D368C
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r0, _080D3694 @ =wStaticGraphicTilenums
	adds r0, #0xa2
	ldr r1, [r7, #0x64]
	strh r1, [r0]
	ldr r0, _080D3698 @ =wStaticMotionPalIDs
	adds r0, #0xa2
	ldr r1, [r7, #0x68]
	strh r1, [r0]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D368C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080D3694: .4byte wStaticGraphicTilenums
_080D3698: .4byte wStaticMotionPalIDs
_080D369C: .4byte 0x00000305
_080D36A0: .4byte 0x00000654
_080D36A4: .4byte gStaticMotionGraphics
_080D36A8: .4byte gStaticMotionGraphics+12
_080D36AC: .4byte gSineTable
_080D36B0: .4byte gStageRun+232
_080D36B4: .4byte 0x000097FF
