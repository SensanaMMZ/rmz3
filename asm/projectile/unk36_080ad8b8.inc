	push {r4, r5, r6, lr}
	adds r5, r0, #0
	bl InitRotatableMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r6, #0
	movs r4, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080AD8F4 @ =0x00006A05
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x24
	strb r4, [r0]
	ldrb r2, [r5, #0x11]
	cmp r2, #0
	beq _080AD8F8
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080AD8FE
	.align 2, 0
_080AD8F4: .4byte 0x00006A05
_080AD8F8:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AD8FE:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r5, #0
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	strb r3, [r5, #0x12]
	strb r3, [r5, #0x13]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080AD932
	movs r0, #4
	rsbs r0, r0, #0
	b _080AD934
_080AD932:
	movs r0, #4
_080AD934:
	strb r0, [r5, #0x13]
	ldr r1, _080AD954 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl Projectile36_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080AD954: .4byte gProjectileFnTable
