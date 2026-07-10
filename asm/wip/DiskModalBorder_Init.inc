	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r1, _080E82AC @ =gWidgetFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #2
	movs r6, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080E82B0 @ =0x00000E04
	adds r0, r5, #0
	bl SetMotion
	ldrb r1, [r5, #0x10]
	adds r0, r4, #0
	ands r0, r1
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r0, [r5, #0x10]
	ands r4, r0
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r2, r4, #4
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	cmp r4, #0
	beq _080E82B4
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080E82BA
	.align 2, 0
_080E82AC: .4byte gWidgetFnTable
_080E82B0: .4byte 0x00000E04
_080E82B4:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080E82BA:
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #0x10]
	lsrs r0, r0, #1
	movs r2, #1
	ands r0, r2
	adds r1, r5, #0
	adds r1, #0x4d
	strb r0, [r1]
	ldrb r1, [r5, #0x10]
	lsrs r1, r1, #1
	adds r4, r5, #0
	adds r4, #0x4a
	ands r1, r2
	lsls r3, r1, #5
	ldrb r2, [r4]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _080E82EE
	ldrb r0, [r5, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _080E82F4
_080E82EE:
	ldrb r1, [r5, #0xa]
	movs r0, #0xdf
	ands r0, r1
_080E82F4:
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl DiskModalBorder_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
