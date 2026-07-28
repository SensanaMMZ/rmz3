	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	movs r2, #0xa
	adds r0, #0xb4
	ldrb r0, [r0]
	cmp r2, r0
	beq _080823E6
	adds r1, r0, #0
	cmp r2, r1
	ble _080823D2
	subs r0, r2, r1
	cmp r0, #0
	ble _080823E6
	adds r4, r0, #0
_080823C2:
	adds r0, r5, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	subs r4, #1
	cmp r4, #0
	bne _080823C2
	b _080823E6
_080823D2:
	subs r0, #0xa
	cmp r0, #0
	ble _080823E6
	adds r4, r0, #0
_080823DA:
	adds r0, r5, #0
	bl FUN_08082348
	subs r4, #1
	cmp r4, #0
	bne _080823DA
_080823E6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
