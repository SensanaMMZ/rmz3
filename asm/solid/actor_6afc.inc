	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #1
	beq _080D6B7E
	cmp r0, #1
	bgt _080D6B10
	cmp r0, #0
	beq _080D6B16
	b _080D6C48
_080D6B10:
	cmp r0, #2
	beq _080D6BD8
	b _080D6C48
_080D6B16:
	ldr r0, [r7, #0x54]
	str r0, [r7, #0x5c]
	ldr r0, [r7, #0x58]
	str r0, [r7, #0x60]
	ldr r1, _080D6BC0 @ =wStaticGraphicTilenums
	adds r1, #0xa2
	movs r6, #0
	ldr r0, _080D6BC4 @ =0x000002BE
	strh r0, [r1]
	ldr r5, _080D6BC8 @ =wStaticMotionPalIDs
	adds r5, #0xa2
	movs r0, #6
	strh r0, [r5]
	ldr r4, _080D6BCC @ =0x00000654
	ldr r2, _080D6BD0 @ =gStaticMotionGraphics
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
	ldr r0, _080D6BD4 @ =gStaticMotionGraphics+12
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
	adds r0, r7, #0
	bl InitScalerotMotion1
	movs r1, #0xa2
	lsls r1, r1, #7
	adds r0, r7, #0
	bl SetMotion
	strb r6, [r7, #0x12]
	movs r0, #1
	strb r0, [r7, #0x13]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D6B7E:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x13]
	adds r0, #1
	strb r0, [r7, #0x13]
	movs r1, #0xf
	ands r0, r1
	cmp r0, #0
	bne _080D6B9E
	ldr r2, [r7, #0x54]
	ldr r3, [r7, #0x58]
	movs r0, #3
	movs r1, #0
	bl FUN_080c5628
_080D6B9E:
	ldr r2, [r7, #0x18]
	ldrb r1, [r2, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D6BB0
	ldr r0, [r7, #0x5c]
	adds r0, #0x60
	str r0, [r7, #0x5c]
_080D6BB0:
	ldrb r1, [r2, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D6C48
	movs r0, #0
	strb r0, [r7, #0x13]
	b _080D6C42
	.align 2, 0
_080D6BC0: .4byte wStaticGraphicTilenums
_080D6BC4: .4byte 0x000002BE
_080D6BC8: .4byte wStaticMotionPalIDs
_080D6BCC: .4byte 0x00000654
_080D6BD0: .4byte gStaticMotionGraphics
_080D6BD4: .4byte gStaticMotionGraphics+12
_080D6BD8:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x5c]
	adds r0, #0x80
	str r0, [r7, #0x5c]
	ldrb r0, [r7, #0x13]
	adds r1, r0, #1
	strb r1, [r7, #0x13]
	ldr r3, _080D6C7C @ =gSineTable
	adds r0, #0x41
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	ldrh r1, [r0]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x18
	movs r4, #0x80
	lsls r4, r4, #2
	adds r0, r4, #0
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	adds r2, r0, #0
	movs r1, #0x90
	lsls r1, r1, #1
	cmp r0, r1
	bls _080D6C12
	adds r2, r1, #0
_080D6C12:
	adds r0, r7, #0
	adds r0, #0x50
	strh r2, [r0]
	ldrb r0, [r7, #0x13]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r1, #0
	ldrsh r0, [r0, r1]
	movs r2, #0x80
	lsls r2, r2, #1
	adds r0, r0, r2
	asrs r0, r0, #1
	adds r1, r7, #0
	adds r1, #0x52
	strh r0, [r1]
	ldrb r0, [r7, #0x13]
	cmp r0, #0x50
	bls _080D6C48
	ldrb r0, [r7, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r7, #0xa]
_080D6C42:
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D6C48:
	ldrb r0, [r7, #0x12]
	adds r2, r0, #1
	strb r2, [r7, #0x12]
	ldr r3, _080D6C7C @ =gSineTable
	adds r0, #0x41
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r1, [r0, r4]
	lsls r1, r1, #1
	ldr r0, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	lsls r2, r2, #0x19
	lsrs r2, r2, #0x17
	adds r2, r2, r3
	movs r0, #0
	ldrsh r1, [r2, r0]
	lsls r1, r1, #2
	ldr r0, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080D6C7C: .4byte gSineTable
