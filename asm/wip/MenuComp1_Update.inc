	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldr r0, _080E6380 @ =0x00000DCC
	adds r2, r5, r0
	ldrb r0, [r2, #4]
	cmp r0, #0
	beq _080E6388
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080E6384 @ =gWidgetFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _080E63F4
	.align 2, 0
_080E6380: .4byte 0x00000DCC
_080E6384: .4byte gWidgetFnTable
_080E6388:
	ldr r0, [r4, #0x64]
	ldr r1, [r4, #0x68]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	ldrb r1, [r2]
	cmp r0, r1
	beq _080E63D0
	ldrb r0, [r4, #0x10]
	cmp r0, r1
	bne _080E63B8
	ldr r0, _080E63B4 @ =sMenuComp1Motions
	ldrb r1, [r4, #0x10]
	lsls r1, r1, #2
	adds r0, #2
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r4, #0
	bl SetMotion
	b _080E63C8
	.align 2, 0
_080E63B4: .4byte sMenuComp1Motions
_080E63B8:
	ldr r0, _080E63FC @ =sMenuComp1Motions
	ldrb r1, [r4, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r4, #0
	bl SetMotion
_080E63C8:
	ldr r1, _080E6400 @ =0x00000DCC
	adds r0, r5, r1
	ldrb r0, [r0]
	strb r0, [r4, #0x12]
_080E63D0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	str r0, [r4, #0x64]
	str r1, [r4, #0x68]
	ldr r0, _080E6404 @ =gVideoRegBuffer+16
	ldrh r1, [r0]
	movs r0, #0x80
	lsls r0, r0, #1
	cmp r1, r0
	bls _080E63F4
	ldr r0, [r4, #0x54]
	movs r1, #0x80
	lsls r1, r1, #0xa
	adds r0, r0, r1
	str r0, [r4, #0x54]
_080E63F4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080E63FC: .4byte sMenuComp1Motions
_080E6400: .4byte 0x00000DCC
_080E6404: .4byte gVideoRegBuffer+16
