	push {r4, r5, r6, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldr r0, _080DE7A4 @ =gOverworld
	ldr r1, _080DE7A8 @ =0x0002D024
	adds r6, r0, r1
	ldrb r0, [r6]
	cmp r0, #0
	beq _080DE79C
	ldrb r0, [r4, #0xd]
	adds r5, r4, #0
	adds r5, #0x54
	cmp r0, #0
	bne _080DE74E
	movs r0, #1
	adds r1, r5, #0
	bl AppendQuake
	movs r1, #0x9a
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0xa
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080DE74E:
	ldr r0, [r4, #0x5c]
	cmp r0, #0xff
	bgt _080DE758
	adds r0, #8
	str r0, [r4, #0x5c]
_080DE758:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080DE774
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080DE774
	movs r0, #2
	strb r0, [r6]
_080DE774:
	ldr r0, _080DE7AC @ =gStageRun+232
	adds r1, r5, #0
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _080DE79C
	ldr r1, _080DE7B0 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Solid45_Die
_080DE79C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DE7A4: .4byte gOverworld
_080DE7A8: .4byte 0x0002D024
_080DE7AC: .4byte gStageRun+232
_080DE7B0: .4byte gSolidFnTable
