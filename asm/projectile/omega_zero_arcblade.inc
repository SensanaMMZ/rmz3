	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080AE7F8
	cmp r0, #1
	beq _080AE87C
	b _080AE8EA
_080AE7F8:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080AE8F0 @ =0x0836C9C0
	bl SetDDP
	adds r0, r4, #0
	bl InitRotatableMotion
	movs r5, #0x80
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #7
	movs r1, #6
	bl __divsi3
	subs r0, r5, r0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080AE828
	movs r0, #0x80
	subs r0, r0, r5
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
_080AE828:
	adds r1, r5, #0
	adds r1, #0x80
	adds r0, r4, #0
	adds r0, #0x24
	strb r1, [r0]
	ldr r2, _080AE8F4 @ =gSineTable
	adds r0, r5, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080AE84E
	adds r0, #0xff
_080AE84E:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	lsls r0, r5, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080AE866
	adds r0, #0xff
_080AE866:
	asrs r0, r0, #8
	str r0, [r4, #0x60]
	ldr r1, _080AE8F8 @ =0x00008009
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x80
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080AE87C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080AE8A2
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AE8EA
_080AE8A2:
	ldr r0, _080AE8FC @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _080AE8EA
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080AE900 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080AE8EA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AE8F0: .4byte 0x0836C9C0
_080AE8F4: .4byte gSineTable
_080AE8F8: .4byte 0x00008009
_080AE8FC: .4byte gStageRun+232
_080AE900: .4byte gProjectileFnTable
