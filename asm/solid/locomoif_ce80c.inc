	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080CE81E
	cmp r0, #1
	beq _080CE828
	b _080CE862
_080CE81E:
	movs r0, #0x40
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CE828:
	ldr r1, [r4, #0x5c]
	subs r1, #4
	str r1, [r4, #0x5c]
	adds r2, r4, #0
	adds r2, #0xb4
	ldrh r0, [r2]
	adds r0, r0, r1
	movs r5, #0
	strh r0, [r2]
	adds r0, r4, #0
	bl FUN_080ce538
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080CE862
	ldr r0, _080CE868 @ =0x0000010B
	bl StopSound
	adds r0, r6, #0
	adds r0, #0xbd
	strb r5, [r0]
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
_080CE862:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080CE868: .4byte 0x0000010B
