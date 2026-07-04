	push {r4, r5, r6, r7, lr}
	mov ip, r0
	adds r4, r1, #0
	lsls r2, r2, #0x18
	lsls r3, r3, #0x18
	ldrb r6, [r4, #4]
	ldrb r7, [r4, #6]
	adds r4, #8
	lsrs r3, r3, #0x12
	add r3, ip
	lsrs r2, r2, #0x17
	adds r3, r3, r2
	mov ip, r3
	movs r1, #0
	cmp r1, r7
	bhs _080F3CDA
_080F3CB0:
	lsls r0, r1, #6
	mov r2, ip
	adds r3, r2, r0
	movs r2, #0
	adds r5, r1, #1
	cmp r2, r6
	bhs _080F3CD2
_080F3CBE:
	lsls r0, r2, #1
	adds r0, r0, r3
	ldrh r1, [r4]
	strh r1, [r0]
	adds r4, #2
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, r6
	blo _080F3CBE
_080F3CD2:
	lsls r0, r5, #0x18
	lsrs r1, r0, #0x18
	cmp r1, r7
	blo _080F3CB0
_080F3CDA:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
