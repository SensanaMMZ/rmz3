	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r1, _080DC978 @ =gSolidFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r0, [r6, #0x28]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x1e
	bne _080DC990
	adds r0, r6, #0
	bl InitScalerotMotion1
	adds r0, r6, #0
	adds r0, #0x50
	movs r1, #0x80
	lsls r1, r1, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	ldr r0, [r6, #0x54]
	ldr r1, _080DC97C @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r1, r6, #0
	adds r1, #0xb8
	ldr r0, [r6, #0x58]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [r1]
	ldr r0, _080DC980 @ =0xFFFFFE00
	str r0, [r6, #0x5c]
	ldr r2, _080DC984 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DC988 @ =0x000343FD
	muls r0, r1, r0
	ldr r7, _080DC98C @ =0x00269EC3
	adds r0, r0, r7
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	ands r0, r1
	adds r0, #0x18
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r6, #0x60]
	strb r4, [r6, #0x11]
	ldr r1, [r6, #0x28]
	ldrb r0, [r1, #0x12]
	adds r0, #1
	strb r0, [r1, #0x12]
	b _080DCA0E
	.align 2, 0
_080DC978: .4byte gSolidFnTable
_080DC97C: .4byte 0xFFFFE000
_080DC980: .4byte 0xFFFFFE00
_080DC984: .4byte RNG_0202f388
_080DC988: .4byte 0x000343FD
_080DC98C: .4byte 0x00269EC3
_080DC990:
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldr r5, _080DCA50 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r3, _080DCA54 @ =0x000343FD
	muls r0, r3, r0
	ldr r2, _080DCA58 @ =0x00269EC3
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsls r0, r0, #2
	lsrs r0, r0, #0x13
	ldr r1, [r6, #0x54]
	adds r1, r1, r0
	str r1, [r6, #0x54]
	adds r1, r6, #0
	adds r1, #0xb8
	ldr r0, [r6, #0x58]
	movs r7, #0x80
	lsls r7, r7, #5
	adds r0, r0, r7
	str r0, [r1]
	adds r0, r4, #0
	muls r0, r3, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	movs r1, #0x3f
	ands r0, r1
	subs r1, #0xff
	subs r1, r1, r0
	str r1, [r6, #0x5c]
	adds r0, r4, #0
	muls r0, r3, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r5]
	lsrs r0, r0, #0x11
	movs r1, #3
	ands r0, r1
	adds r0, #0x18
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r6, #0x60]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080DCA5C @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #2
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
_080DCA0E:
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	movs r1, #0xe6
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	movs r2, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	adds r0, r6, #0
	bl Solid37_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080DCA50: .4byte RNG_0202f388
_080DCA54: .4byte 0x000343FD
_080DCA58: .4byte 0x00269EC3
_080DCA5C: .4byte sCollisions
