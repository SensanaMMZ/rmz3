	push {lr}
	ldr r3, [r0, #0x2c]
	cmp r3, #0
	beq _08082426
	ldr r2, [r3, #0x2c]
	cmp r2, #0
	beq _08082426
	ldr r1, [r2, #0x54]
	ldr r0, [r3, #0x54]
	subs r1, r1, r0
	ldr r0, [r2, #0x58]
	ldr r2, [r3, #0x58]
	subs r0, r0, r2
	asrs r1, r1, #8
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	asrs r0, r0, #8
	adds r2, r0, #0
	muls r2, r0, r2
	adds r0, r2, #0
	adds r1, r1, r0
	adds r0, r1, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r1, r0, #8
	adds r0, r1, #0
	b _08082428
_08082426:
	movs r0, #0
_08082428:
	pop {r1}
	bx r1
