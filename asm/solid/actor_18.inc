	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #0xa
	bls _080D2B4C
	b _080D2D44
_080D2B4C:
	lsls r0, r0, #2
	ldr r1, _080D2B58 @ =_080D2B5C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D2B58: .4byte _080D2B5C
_080D2B5C: @ jump table
	.4byte _080D2B88 @ case 0
	.4byte _080D2BA4 @ case 1
	.4byte _080D2BBC @ case 2
	.4byte _080D2BE4 @ case 3
	.4byte _080D2C1C @ case 4
	.4byte _080D2C44 @ case 5
	.4byte _080D2C80 @ case 6
	.4byte _080D2CC4 @ case 7
	.4byte _080D2D14 @ case 8
	.4byte _080D2D2E @ case 9
	.4byte _080D2D44 @ case 10
_080D2B88:
	ldr r0, _080D2BB4 @ =wDynamicGraphicTilenums
	movs r2, #0xbe
	lsls r2, r2, #1
	adds r0, r0, r2
	movs r1, #0xf0
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r0, _080D2BB8 @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	movs r1, #9
	strh r1, [r0]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D2BA4:
	movs r1, #0xbe
	lsls r1, r1, #8
	adds r0, r4, #0
	movs r2, #1
	bl FUN_080d0aa0
	b _080D2D38
	.align 2, 0
_080D2BB4: .4byte wDynamicGraphicTilenums
_080D2BB8: .4byte wDynamicMotionPalIDs
_080D2BBC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D2BD0
	b _080D2D44
_080D2BD0:
	ldr r1, _080D2BE0 @ =0x0000BE01
	adds r0, r4, #0
	bl SetMotion
	movs r0, #8
	strb r0, [r4, #0x12]
	b _080D2D3E
	.align 2, 0
_080D2BE0: .4byte 0x0000BE01
_080D2BE4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D2BFC
	ldr r0, _080D2C14 @ =0x00000101
	bl PlaySound
_080D2BFC:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D2C08
	b _080D2D44
_080D2C08:
	ldr r1, _080D2C18 @ =0x0000BE02
	adds r0, r4, #0
	bl SetMotion
	b _080D2D3E
	.align 2, 0
_080D2C14: .4byte 0x00000101
_080D2C18: .4byte 0x0000BE02
_080D2C1C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D2C2E
	b _080D2D44
_080D2C2E:
	ldr r1, _080D2C40 @ =0x0000BE03
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x40
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x58]
	str r0, [r4, #0x68]
	b _080D2D3E
	.align 2, 0
_080D2C40: .4byte 0x0000BE03
_080D2C44:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, _080D2C7C @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	ldr r1, [r4, #0x68]
	subs r1, r1, r0
	str r1, [r4, #0x68]
	ldr r2, [r4, #0x58]
	lsls r0, r2, #3
	subs r0, r0, r2
	adds r0, r0, r1
	asrs r1, r0, #3
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	bne _080D2D44
	strb r0, [r4, #0x12]
	str r1, [r4, #0x60]
	b _080D2D3E
	.align 2, 0
_080D2C7C: .4byte gSineTable
_080D2C80:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	ldr r1, _080D2CC0 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #2
	ldr r1, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x68]
	ldr r2, [r4, #0x58]
	lsls r0, r2, #3
	subs r0, r0, r2
	adds r0, r0, r1
	asrs r2, r0, #3
	str r2, [r4, #0x58]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D2D44
	movs r0, #0x40
	strb r0, [r4, #0x12]
	str r2, [r4, #0x68]
	b _080D2D3E
	.align 2, 0
_080D2CC0: .4byte gSineTable
_080D2CC4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r2, [r4, #0x68]
	movs r0, #0x80
	lsls r0, r0, #1
	adds r2, r2, r0
	ldr r1, _080D2D0C @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	adds r2, r2, r0
	str r2, [r4, #0x68]
	ldr r0, [r4, #0x58]
	lsls r1, r0, #3
	subs r1, r1, r0
	adds r1, r1, r2
	asrs r1, r1, #3
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp2
	cmp r0, #0
	beq _080D2D44
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldr r1, _080D2D10 @ =0x0000BE0E
	adds r0, r4, #0
	bl SetMotion
	b _080D2D3E
	.align 2, 0
_080D2D0C: .4byte gSineTable
_080D2D10: .4byte 0x0000BE0E
_080D2D14:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D2D44
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
	ands r0, r1
	b _080D2D3A
_080D2D2E:
	ldr r1, _080D2D4C @ =0x0000BE0E
	adds r0, r4, #0
	movs r2, #1
	bl FUN_080d0934
_080D2D38:
	lsls r0, r0, #0x10
_080D2D3A:
	cmp r0, #0
	beq _080D2D44
_080D2D3E:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D2D44:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080D2D4C: .4byte 0x0000BE0E
