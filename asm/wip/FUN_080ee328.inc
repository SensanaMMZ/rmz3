	lsrs r1, r1, #1
	push {r4, r5, r6, r7}
	movs r7, #0x7f
_080EE32E:
	ldr r4, [r0]
	lsrs r5, r4, #0xa
	ands r5, r2
	lsrs r6, r4, #5
	ands r6, r2
	ands r4, r2
	adds r4, r4, r5
	adds r4, r4, r6
	adds r5, r4, #0
	ands r5, r7
	lsls r5, r5, #1
	ldrh r5, [r3, r5]
	lsrs r4, r4, #0x10
	ands r4, r7
	lsls r4, r4, #1
	ldrh r4, [r3, r4]
	lsls r4, r4, #0x10
	orrs r4, r5
	str r4, [r0]
	adds r0, #4
	subs r1, #1
	bne _080EE32E
	pop {r4, r5, r6, r7}
	bx lr
