	push {r4, r5, lr}
	adds r3, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	ldr r0, _080345E4 @ =gUnlockedElfPtr
	ldr r0, [r0]
	adds r0, r0, r1
	ldrb r2, [r0]
	movs r0, #1
	ands r0, r2
	cmp r0, #0
	beq _080345EC
	adds r4, r3, #0
	adds r4, #0xb4
	ldr r5, _080345E8 @ =0x00000231
	adds r0, r3, r5
	ldrb r0, [r0]
	cmp r0, #0
	bne _080345DE
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	bne _080345DE
	ldrb r0, [r4]
	cmp r0, r1
	beq _080345DE
	ldrb r0, [r4, #1]
	cmp r0, r1
	bne _080345EC
_080345DE:
	movs r0, #1
	b _080345EE
	.align 2, 0
_080345E4: .4byte gUnlockedElfPtr
_080345E8: .4byte 0x00000231
_080345EC:
	movs r0, #0
_080345EE:
	pop {r4, r5}
	pop {r1}
	bx r1
