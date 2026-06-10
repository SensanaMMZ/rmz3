	push {r4, r5, r6, r7}
	ldr r4, [r2]
	movs r7, #0xff
_08003D3A:
	push {r0, r1, r7}
	ldr r1, [r0]
	ldr r5, [r2, #4]
	ldr r0, [r3]
	ands r0, r1
	muls r0, r4, r0
	lsrs r0, r0, #5
	adds r0, r0, r5
	ldr r6, [r3]
	ands r6, r0
	lsls r5, r5, #5
	ldr r0, [r3, #4]
	ands r0, r1
	muls r0, r4, r0
	lsrs r0, r0, #5
	adds r0, r0, r5
	ldr r7, [r3, #4]
	ands r7, r0
	orrs r6, r7
	lsls r5, r5, #5
	ldr r0, [r3, #8]
	ands r0, r1
	lsrs r0, r0, #5
	muls r0, r4, r0
	ldr r7, [r3, #8]
	adds r0, r0, r5
	ands r7, r0
	orrs r6, r7
	pop {r0, r1, r7}
	str r6, [r1]
	adds r0, #4
	adds r1, #4
	subs r7, #1
	bpl _08003D3A
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
