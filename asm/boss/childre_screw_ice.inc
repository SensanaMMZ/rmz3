	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08041898
	cmp r0, #1
	bgt _08041870
	cmp r0, #0
	beq _0804187A
	b _08041964
_08041870:
	cmp r0, #2
	beq _080418B8
	cmp r0, #3
	beq _080418FA
	b _08041964
_0804187A:
	movs r0, #0x40
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080418B0 @ =0x08361F54
	bl SetDDP
	ldr r1, _080418B4 @ =0x0000A40D
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041898:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08041964
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08041964
	.align 2, 0
_080418B0: .4byte 0x08361F54
_080418B4: .4byte 0x0000A40D
_080418B8:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804196C @ =0x08361EF4
	bl SetDDP
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl CreateVFX31_2
	movs r0, #0xa0
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080418DE
	ldr r2, _08041970 @ =0xFFFFFD80
_080418DE:
	str r2, [r4, #0x5c]
	ldr r0, _08041974 @ =0xFFFFFD00
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x58]
	ldr r1, _08041978 @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r1, _0804197C @ =0x0000A40E
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080418FA:
	ldr r0, [r4, #0x54]
	ldr r3, [r4, #0x5c]
	adds r2, r0, r3
	str r2, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xbc
	ldr r0, [r0]
	subs r0, r0, r2
	movs r5, #0xc0
	lsls r5, r5, #7
	adds r1, r0, r5
	movs r0, #0xc0
	lsls r0, r0, #8
	cmp r1, r0
	bls _0804191C
	subs r0, r2, r3
	str r0, [r4, #0x54]
_0804191C:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0804192C
	str r1, [r4, #0x60]
_0804192C:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	ldr r2, _08041980 @ =0xFFFFF800
	adds r0, r0, r2
	subs r0, r0, r1
	cmp r0, #0
	bge _0804195E
	movs r1, #0xa4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r5]
	str r0, [r4, #0x58]
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_0804195E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08041964:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804196C: .4byte 0x08361EF4
_08041970: .4byte 0xFFFFFD80
_08041974: .4byte 0xFFFFFD00
_08041978: .4byte 0xFFFFE000
_0804197C: .4byte 0x0000A40E
_08041980: .4byte 0xFFFFF800
