	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _08040964
	cmp r5, #1
	bgt _080408FC
	cmp r5, #0
	beq _08040908
	b _08040A4A
_080408FC:
	cmp r5, #2
	beq _080409B0
	cmp r5, #3
	bne _08040906
	b _08040A12
_08040906:
	b _08040A4A
_08040908:
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08040938 @ =sCollisions+(24*1)
	bl SetDDP
	strb r5, [r4, #0x12]
	ldr r0, _0804093C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	subs r2, r1, r0
	lsrs r2, r2, #0x1f
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08040940
	cmp r2, #0
	beq _08040944
	b _0804094C
	.align 2, 0
_08040938: .4byte sCollisions+(24*1)
_0804093C: .4byte pZero2
_08040940:
	cmp r2, #0
	beq _0804094C
_08040944:
	ldrb r0, [r4, #0xe]
	adds r0, #2
	strb r0, [r4, #0xe]
	b _08040A4A
_0804094C:
	movs r0, #0x67
	bl PlaySound
	ldr r1, _080409A8 @ =0x0000A408
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _080409AC @ =0xFFFFFE00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08040964:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08040974
	str r1, [r4, #0x60]
_08040974:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	subs r0, r0, r1
	cmp r0, #0
	bge _0804098C
	adds r0, r1, r0
	str r0, [r4, #0x58]
_0804098C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08040A4A
	movs r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08040A4A
	.align 2, 0
_080409A8: .4byte 0x0000A408
_080409AC: .4byte 0xFFFFFE00
_080409B0:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080409F4
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r5, r4, #0
	adds r5, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r5]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r5]
	cmp r1, #0
	beq _080409EC
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080409F2
_080409EC:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080409F2:
	strb r0, [r4, #0xa]
_080409F4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08040A50 @ =sCollisions+(24*1)
	bl SetDDP
	movs r0, #0x20
	strb r0, [r4, #0x12]
	movs r1, #0xa4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08040A12:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08040A44
	ldr r0, _08040A54 @ =pZero2
	ldr r2, [r0]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _08040A44
	adds r0, r2, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	beq _08040A44
	adds r0, r4, #0
	bl childre_08040428
_08040A44:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08040A4A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08040A50: .4byte sCollisions+(24*1)
_08040A54: .4byte pZero2

