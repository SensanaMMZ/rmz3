	push {r4, r5, r6, lr}
	sub sp, #8
	adds r5, r0, #0
	ldr r2, [r5, #0x28]
	ldrb r0, [r5, #0xe]
	cmp r0, #4
	bhi _08078842
	lsls r0, r0, #2
	ldr r1, _08078764 @ =_08078768
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08078764: .4byte _08078768
_08078768: @ jump table
	.4byte _0807877C @ case 0
	.4byte _08078786 @ case 1
	.4byte _080787EA @ case 2
	.4byte _08078808 @ case 3
	.4byte _08078812 @ case 4
_0807877C:
	movs r0, #2
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08078786:
	adds r0, r5, #0
	adds r0, #0x24
	ldrb r2, [r0]
	ldr r3, [r5, #0x54]
	str r3, [sp]
	ldr r4, _08078800 @ =gSineTable
	adds r0, r2, #0
	adds r0, #0x80
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r6, #0
	ldrsh r1, [r0, r6]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #1
	adds r0, r0, r3
	str r0, [sp]
	ldr r3, [r5, #0x58]
	str r3, [sp, #4]
	adds r0, r2, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r4, #0
	ldrsh r1, [r0, r4]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #1
	adds r0, r0, r3
	str r0, [sp, #4]
	movs r1, #0x80
	lsls r1, r1, #2
	subs r2, #0x40
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	mov r0, sp
	bl CreateLemon
	movs r0, #0x2c
	bl PlaySound
	ldr r1, _08078804 @ =0x00002F08
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080787EA:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08078842
	ldrb r0, [r5, #0xe]
	adds r0, #1
	b _08078840
	.align 2, 0
_08078800: .4byte gSineTable
_08078804: .4byte 0x00002F08
_08078808:
	movs r0, #4
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08078812:
	adds r0, r2, #0
	bl IsFrozen
	cmp r0, #0
	bne _08078842
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08078842
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0807883E
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
	b _08078842
_0807883E:
	movs r0, #1
_08078840:
	strb r0, [r5, #0xe]
_08078842:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

