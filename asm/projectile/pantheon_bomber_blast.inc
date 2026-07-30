	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _080AD4A0
	cmp r5, #1
	bgt _080AD418
	cmp r5, #0
	beq _080AD420
	b _080AD58C
_080AD418:
	cmp r5, #2
	bne _080AD41E
	b _080AD550
_080AD41E:
	b _080AD58C
_080AD420:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080AD45C @ =0x0836C894
	bl SetDDP
	ldr r1, _080AD460 @ =0x0000690E
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080AD468
	ldr r0, _080AD464 @ =0xFFFFFD80
	str r0, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080AD490
	.align 2, 0
_080AD45C: .4byte 0x0836C894
_080AD460: .4byte 0x0000690E
_080AD464: .4byte 0xFFFFFD80
_080AD468:
	movs r0, #0xa0
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	movs r2, #1
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_080AD490:
	movs r0, #0x80
	lsls r0, r0, #1
	str r0, [r4, #0x60]
	movs r0, #0x24
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080AD4A0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080AD4B8
	subs r0, #1
	strb r0, [r4, #0x13]
_080AD4B8:
	ldrb r0, [r4, #0x13]
	cmp r0, #9
	bhi _080AD4DA
	ldr r1, [r4, #0x60]
	movs r0, #0x10
	subs r0, r0, r1
	lsls r0, r0, #4
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x50
	strh r1, [r0]
	ldr r0, [r4, #0x60]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
_080AD4DA:
	ldrb r0, [r4, #0x13]
	cmp r0, #4
	bne _080AD4FA
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	b _080AD536
_080AD4FA:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _080AD514
	ldr r0, [r4, #0x54]
	ldr r1, _080AD510 @ =0xFFFFF800
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl PushoutToRight1
	b _080AD522
	.align 2, 0
_080AD510: .4byte 0xFFFFF800
_080AD514:
	ldr r0, [r4, #0x54]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl PushoutToLeft1
_080AD522:
	cmp r0, #0
	beq _080AD536
	ldrb r0, [r4, #0x13]
	cmp r0, #0xa
	bls _080AD530
	movs r0, #0xa
	strb r0, [r4, #0x13]
_080AD530:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080AD536:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080AD58C
	ldr r1, _080AD54C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	b _080AD586
	.align 2, 0
_080AD54C: .4byte gProjectileFnTable
_080AD550:
	ldr r1, [r4, #0x60]
	movs r0, #0x10
	subs r0, r0, r1
	lsls r0, r0, #4
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x50
	strh r1, [r0]
	ldr r0, [r4, #0x60]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080AD57C
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AD58C
_080AD57C:
	ldr r1, _080AD594 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r5, [r4, #0xc]
_080AD586:
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080AD58C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AD594: .4byte gProjectileFnTable
