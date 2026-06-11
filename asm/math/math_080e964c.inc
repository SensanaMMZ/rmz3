	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r3, r1, #0
	adds r4, r2, #0
	subs r2, r6, r3
	adds r0, r2, r4
	movs r5, #0xff
	ands r0, r5
	lsls r1, r4, #1
	cmp r0, r1
	bhi _080E9666
	adds r3, r6, #0
	b _080E9678
_080E9666:
	ands r2, r5
	movs r0, #1
	rsbs r0, r0, #0
	cmp r2, #0x7f
	bgt _080E9672
	movs r0, #1
_080E9672:
	muls r0, r4, r0
	adds r3, r3, r0
	ands r3, r5
_080E9678:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
