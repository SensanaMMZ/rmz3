	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start ActorLastLeviathan_Update
ActorLastLeviathan_Update: @ 0x080D56B0
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #0xd
	bls _080D56BE
	b _080D59CC
_080D56BE:
	lsls r0, r0, #2
	ldr r1, _080D56C8 @ =_080D56CC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D56C8: .4byte _080D56CC
_080D56CC: @ jump table
	.4byte _080D5704 @ case 0
	.4byte _080D5720 @ case 1
	.4byte _080D5770 @ case 2
	.4byte _080D57C0 @ case 3
	.4byte _080D5810 @ case 4
	.4byte _080D5838 @ case 5
	.4byte _080D5860 @ case 6
	.4byte _080D58A4 @ case 7
	.4byte _080D58CA @ case 8
	.4byte _080D5904 @ case 9
	.4byte _080D5944 @ case 10
	.4byte _080D5974 @ case 11
	.4byte _080D59A4 @ case 12
	.4byte _080D59C6 @ case 13
_080D5704:
	ldr r0, _080D5760 @ =wDynamicGraphicTilenums
	movs r2, #0xbd
	lsls r2, r2, #1
	adds r0, r0, r2
	movs r1, #0xb0
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r0, _080D5764 @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	movs r1, #7
	strh r1, [r0]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D5720:
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	adds r0, #1
	str r0, [sp, #4]
	movs r0, #0x80
	lsls r0, r0, #8
	ldr r3, _080D5768 @ =0x08370E10
	movs r1, #1
	mov r2, sp
	bl AppendHazard
	movs r1, #0xbd
	lsls r1, r1, #8
	adds r0, r6, #0
	movs r2, #1
	bl FUN_080d0aa0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080D5750
	b _080D59CC
_080D5750:
	ldr r1, _080D576C @ =0x0000BD05
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0x14
	strb r0, [r6, #0x12]
	b _080D59BE
	.align 2, 0
_080D5760: .4byte wDynamicGraphicTilenums
_080D5764: .4byte wDynamicMotionPalIDs
_080D5768: .4byte Rect_08370e10
_080D576C: .4byte 0x0000BD05
_080D5770:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	beq _080D5786
	b _080D59CC
_080D5786:
	ldr r1, _080D57B8 @ =0x0000BD09
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0xf7
	bl PlaySound
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080D57BC @ =0x08370D70
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	movs r0, #0x14
	strb r0, [r6, #0x12]
	b _080D59BE
	.align 2, 0
_080D57B8: .4byte 0x0000BD09
_080D57BC: .4byte sCollisions_08370C68+(24*11)
_080D57C0:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	beq _080D57D6
	b _080D59CC
_080D57D6:
	ldr r1, _080D5808 @ =0x0000BD0B
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0xf7
	bl PlaySound
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080D580C @ =0x08370D88
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	movs r0, #0xa
	strb r0, [r6, #0x12]
	b _080D59BE
	.align 2, 0
_080D5808: .4byte 0x0000BD0B
_080D580C: .4byte sCollisions_08370C68+(24*12)
_080D5810:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D5824
	b _080D59CC
_080D5824:
	ldr r1, _080D5834 @ =0x0000BD0C
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0xa
	strb r0, [r6, #0x12]
	b _080D59BE
	.align 2, 0
_080D5834: .4byte 0x0000BD0C
_080D5838:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0
	beq _080D584E
	b _080D59CC
_080D584E:
	ldr r1, _080D585C @ =0x0000BD14
	adds r0, r6, #0
	bl SetMotion
	strb r4, [r6, #0x12]
	b _080D59BE
	.align 2, 0
_080D585C: .4byte 0x0000BD14
_080D5860:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	beq _080D5876
	b _080D59CC
_080D5876:
	movs r0, #0xf7
	bl PlaySound
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080D58A0 @ =0x08370DA0
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
	b _080D59BE
	.align 2, 0
_080D58A0: .4byte sCollisions_08370C68+(24*13)
_080D58A4:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080D58F8 @ =0x08370DB8
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D58CA:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080D59CC
	ldr r1, _080D58FC @ =0x0000BD10
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0xf6
	bl PlaySound
	movs r0, #0xa0
	lsls r0, r0, #3
	str r0, [r6, #0x5c]
	ldr r0, _080D5900 @ =0xFFFFFEC0
	str r0, [r6, #0x60]
	b _080D59BE
	.align 2, 0
_080D58F8: .4byte sCollisions_08370C68+(24*14)
_080D58FC: .4byte 0x0000BD10
_080D5900: .4byte 0xFFFFFEC0
_080D5904:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	ldr r2, [r6, #0x60]
	adds r1, r1, r2
	str r1, [r6, #0x58]
	adds r2, #0x40
	str r2, [r6, #0x60]
	movs r2, #0xa0
	lsls r2, r2, #5
	adds r1, r1, r2
	bl PushoutToUp1
	cmp r0, #0
	beq _080D59CC
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	ldr r1, _080D5940 @ =0xFFFFEC00
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r0, #0
	str r0, [r6, #0x60]
	b _080D59BE
	.align 2, 0
_080D5940: .4byte 0xFFFFEC00
_080D5944:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x5c]
	lsls r1, r0, #3
	subs r1, r1, r0
	asrs r1, r1, #3
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D59CC
	movs r1, #0xbd
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	movs r0, #2
	strb r0, [r6, #0x12]
	b _080D59BE
_080D5974:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x5c]
	lsls r1, r0, #3
	subs r1, r1, r0
	asrs r1, r1, #3
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D59CC
	ldr r1, _080D59A0 @ =0x0000BD0F
	adds r0, r6, #0
	bl SetMotion
	b _080D59BE
	.align 2, 0
_080D59A0: .4byte 0x0000BD0F
_080D59A4:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x5c]
	lsls r1, r0, #3
	subs r1, r1, r0
	asrs r1, r1, #3
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	cmp r1, #3
	bgt _080D59CC
_080D59BE:
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
	b _080D59CC
_080D59C6:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080D59CC:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
