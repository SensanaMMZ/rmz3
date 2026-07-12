	push {r4, r5, r6, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	ldr r2, _080F5894 @ =0x000064AC
	adds r0, r4, r2
	ldr r0, [r0]
	cmp r1, #0xff
	bne _080F589C
	movs r2, #0
	adds r3, r0, #0
	adds r3, #0xb4
	ldrb r1, [r3, #0x17]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	beq _080F584C
	ldr r1, _080F5898 @ =0x00000DD2
	adds r0, r4, r1
	strb r2, [r0]
	movs r2, #1
_080F584C:
	ldrb r1, [r3, #0x17]
	movs r6, #2
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	beq _080F5866
	ldr r1, _080F5898 @ =0x00000DD2
	adds r0, r4, r1
	adds r0, r0, r2
	strb r5, [r0]
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
_080F5866:
	ldrb r1, [r3, #0x17]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080F587E
	ldr r1, _080F5898 @ =0x00000DD2
	adds r0, r4, r1
	adds r0, r0, r2
	strb r6, [r0]
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
_080F587E:
	ldrb r1, [r3, #0x17]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080F58AC
	ldr r1, _080F5898 @ =0x00000DD2
	adds r0, r4, r1
	adds r0, r0, r2
	movs r1, #3
	strb r1, [r0]
	b _080F58AC
	.align 2, 0
_080F5894: .4byte 0x000064AC
_080F5898: .4byte 0x00000DD2
_080F589C:
	ldr r2, _080F58A8 @ =0x00000DD2
	adds r0, r4, r2
	adds r0, r0, r1
	ldrb r0, [r0]
	b _080F58AE
	.align 2, 0
_080F58A8: .4byte 0x00000DD2
_080F58AC:
	movs r0, #0xff
_080F58AE:
	pop {r4, r5, r6}
	pop {r1}
	bx r1
