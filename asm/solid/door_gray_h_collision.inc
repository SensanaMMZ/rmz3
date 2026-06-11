	push {r4, r5, lr}
	ldr r3, [r0, #0x2c]
	ldr r0, [r0, #0xc]
	ldr r4, [r0, #0x2c]
	movs r2, #8
	ldrsb r2, [r4, r2]
	cmp r2, #0
	bne _080D7EAA
	ldr r1, [r3, #0x58]
	ldr r0, [r4, #0x58]
	cmp r1, r0
	ble _080D7E84
	ldrb r1, [r3, #0x10]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _080D7EAA
	strb r5, [r3, #0xd]
	b _080D7E92
_080D7E84:
	ldrb r1, [r3, #0x10]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D7EAA
	movs r0, #2
	strb r0, [r3, #0xd]
_080D7E92:
	strb r2, [r3, #0xe]
	ldr r0, _080D7EB0 @ =0x00000119
	adds r1, r4, r0
	movs r0, #1
	strb r0, [r1]
	ldr r2, _080D7EB4 @ =gStageRun
	ldrh r1, [r2, #0x14]
	orrs r0, r1
	strh r0, [r2, #0x14]
	adds r0, r3, #0
	adds r0, #0xb4
	str r4, [r0]
_080D7EAA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080D7EB0: .4byte 0x00000119
_080D7EB4: .4byte gStageRun
