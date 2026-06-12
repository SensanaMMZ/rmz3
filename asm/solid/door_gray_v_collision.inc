	push {r4, r5, r6, lr}
	ldr r3, [r0, #0x2c]
	ldr r0, [r0, #0xc]
	ldr r5, [r0, #0x2c]
	movs r0, #8
	ldrsb r0, [r5, r0]
	cmp r0, #0
	bne _080D046A
	ldr r0, [r3, #0x58]
	ldr r1, [r5, #0x58]
	cmp r0, r1
	blt _080D046A
	subs r1, r0, r1
	movs r0, #0x80
	lsls r0, r0, #4
	cmp r1, r0
	bgt _080D046A
	ldrb r2, [r3, #0x10]
	movs r6, #2
	adds r0, r6, #0
	ands r0, r2
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0
	beq _080D0432
	ldr r0, _080D0428 @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #4
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080D046A
	ldr r1, [r3, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _080D042C
	movs r0, #1
	strb r0, [r3, #0xd]
	strb r2, [r3, #0xe]
	b _080D0454
	.align 2, 0
_080D0428: .4byte gCurStory
_080D042C:
	strb r6, [r3, #0xd]
	strb r2, [r3, #0xe]
	b _080D0454
_080D0432:
	ldr r1, [r3, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _080D0448
	movs r1, #1
	adds r0, r1, #0
	ands r0, r2
	cmp r0, #0
	bne _080D046A
	strb r1, [r3, #0xd]
	b _080D0452
_080D0448:
	movs r0, #1
	ands r0, r2
	cmp r0, #0
	beq _080D046A
	strb r6, [r3, #0xd]
_080D0452:
	strb r4, [r3, #0xe]
_080D0454:
	ldr r0, _080D0470 @ =0x00000119
	adds r1, r5, r0
	movs r0, #1
	strb r0, [r1]
	ldr r2, _080D0474 @ =gStageRun
	ldrh r1, [r2, #0x14]
	orrs r0, r1
	strh r0, [r2, #0x14]
	adds r0, r3, #0
	adds r0, #0xb4
	str r5, [r0]
_080D046A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080D0470: .4byte 0x00000119
_080D0474: .4byte gStageRun
