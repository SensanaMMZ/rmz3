	push {r4, lr}
	adds r4, r0, #0
	movs r0, #0x94
	lsls r0, r0, #1
	adds r1, r4, r0
	adds r0, r4, #0
	bl IsAttackOK
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0
	beq _0803040C
	ldr r2, _08030408 @ =0x0000012B
	adds r1, r4, r2
	movs r0, #0xff
	strb r0, [r1]
	adds r1, r4, #0
	adds r1, #0xec
	movs r2, #0
	movs r0, #3
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0xed
	strb r2, [r0]
	b _0803042E
	.align 2, 0
_08030408: .4byte 0x0000012B
_0803040C:
	ldr r0, _08030438 @ =0x0000012B
	adds r2, r4, r0
	ldrb r1, [r2]
	adds r0, r1, #0
	cmp r0, #0xff
	beq _0803043C
	movs r2, #0x94
	lsls r2, r2, #1
	adds r0, r4, r2
	strb r1, [r0]
	adds r1, r4, #0
	adds r1, #0xec
	movs r0, #3
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0xed
	strb r3, [r0]
_0803042E:
	adds r0, r4, #0
	bl zeroWallAtk
	b _08030442
	.align 2, 0
_08030438: .4byte 0x0000012B
_0803043C:
	movs r0, #0xff
	orrs r0, r1
	strb r0, [r2]
_08030442:
	pop {r4}
	pop {r0}
	bx r0
