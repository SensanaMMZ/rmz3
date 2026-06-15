	push {r4, r5, r6, lr}
	ldr r3, [r0, #0x2c]
	ldr r0, [r0, #0xc]
	ldr r5, [r0, #0x2c]
	movs r0, #8
	ldrsb r0, [r5, r0]
	cmp r0, #0
	bne _080CAF6E
	ldr r0, [r3, #0x58]
	ldr r1, [r5, #0x58]
	cmp r0, r1
	blt _080CAF6E
	subs r1, r0, r1
	movs r0, #0x80
	lsls r0, r0, #4
	cmp r1, r0
	bgt _080CAF6E
	ldrb r2, [r3, #0x10]
	movs r6, #2
	adds r0, r6, #0
	ands r0, r2
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0
	beq _080CAF36
	ldr r0, _080CAF2C @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #4
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080CAF6E
	ldr r1, [r3, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _080CAF30
	movs r0, #1
	strb r0, [r3, #0xd]
	strb r2, [r3, #0xe]
	b _080CAF58
	.align 2, 0
_080CAF2C: .4byte gCurStory
_080CAF30:
	strb r6, [r3, #0xd]
	strb r2, [r3, #0xe]
	b _080CAF58
_080CAF36:
	ldr r1, [r3, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _080CAF4C
	movs r1, #1
	adds r0, r1, #0
	ands r0, r2
	cmp r0, #0
	bne _080CAF6E
	strb r1, [r3, #0xd]
	b _080CAF56
_080CAF4C:
	movs r0, #1
	ands r0, r2
	cmp r0, #0
	beq _080CAF6E
	strb r6, [r3, #0xd]
_080CAF56:
	strb r4, [r3, #0xe]
_080CAF58:
	ldr r0, _080CAF74 @ =0x00000119
	adds r1, r5, r0
	movs r0, #1
	strb r0, [r1]
	ldr r2, _080CAF78 @ =gStageRun
	ldrh r1, [r2, #0x14]
	orrs r0, r1
	strh r0, [r2, #0x14]
	adds r0, r3, #0
	adds r0, #0xb4
	str r5, [r0]
_080CAF6E:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080CAF74: .4byte 0x00000119
_080CAF78: .4byte gStageRun
