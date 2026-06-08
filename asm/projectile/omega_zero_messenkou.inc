	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080AE6EC
	cmp r0, #1
	beq _080AE760
	b _080AE7CE
_080AE6EC:
	adds r0, r4, #0
	bl InitRotatableMotion
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #5
	movs r1, #0x80
	rsbs r1, r1, #0
	adds r5, r1, #0
	subs r0, r5, r0
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080AE7D4 @ =0x0836CA08
	bl SetDDP
	ldr r2, _080AE7D8 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #0x1d
	movs r3, #0x80
	lsls r3, r3, #0x17
	adds r0, r0, r3
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080AE72E
	adds r0, #0xff
_080AE72E:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #0x1d
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080AE74A
	adds r0, #0xff
_080AE74A:
	asrs r0, r0, #8
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldr r1, _080AE7DC @ =0x00008001
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080AE760:
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
	beq _080AE786
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AE7CE
_080AE786:
	ldr r0, _080AE7E0 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _080AE7CE
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
	ldr r1, _080AE7E4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080AE7CE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AE7D4: .4byte 0x0836CA08
_080AE7D8: .4byte gSineTable
_080AE7DC: .4byte 0x00008001
_080AE7E0: .4byte gStageRun+232
_080AE7E4: .4byte gProjectileFnTable
