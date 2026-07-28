	push {r4, r5, lr}
	ldr r5, [r2]
	ldr r3, [r1]
	adds r4, r3, r5
	str r4, [r1]
	ldr r3, [r1, #4]
	ldr r2, [r2, #4]
	adds r3, r3, r2
	str r3, [r1, #4]
	adds r1, r0, #0
	adds r1, #0xdc
	ldr r1, [r1]
	ldr r2, _080AFE28 @ =0xFFFFB400
	adds r1, r1, r2
	ldr r3, _080AFE2C @ =0xFFFFDA00
	adds r2, r4, r3
	adds r0, #0xd4
	ldr r0, [r0]
	subs r4, r2, r0
	cmp r4, r1
	bls _080AFE30
	adds r0, r4, #0
	muls r0, r5, r0
	cmp r0, #0
	ble _080AFE30
	movs r0, #1
	b _080AFE32
	.align 2, 0
_080AFE28: .4byte 0xFFFFB400
_080AFE2C: .4byte 0xFFFFDA00
_080AFE30:
	movs r0, #0
_080AFE32:
	pop {r4, r5}
	pop {r1}
	bx r1
