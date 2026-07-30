	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #1
	beq _08046D3E
	cmp r0, #1
	bgt _08046CE4
	cmp r0, #0
	beq _08046CF0
	b _08046E50
_08046CE4:
	cmp r0, #2
	beq _08046DC0
	cmp r0, #3
	bne _08046CEE
	b _08046E22
_08046CEE:
	b _08046E50
_08046CF0:
	movs r4, #0
	adds r2, r7, #0
	adds r2, #0xb4
	ldr r1, [r7, #0x54]
	ldr r0, [r2]
	cmp r1, r0
	ble _08046D00
	movs r4, #1
_08046D00:
	adds r3, r7, #0
	adds r3, #0xc7
	strb r4, [r3]
	ldr r2, [r2]
	ldr r0, _08046DB8 @ =0xFFFF5000
	adds r2, r2, r0
	str r2, [r7, #0x54]
	ldrb r1, [r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #0xd
	adds r2, r2, r0
	str r2, [r7, #0x54]
	adds r0, r7, #0
	adds r0, #0xb8
	ldr r1, [r0]
	movs r2, #0xc0
	lsls r2, r2, #6
	adds r1, r1, r2
	str r1, [r7, #0x58]
	ldrb r0, [r3]
	lsls r0, r0, #0x10
	subs r1, r1, r0
	str r1, [r7, #0x58]
	movs r0, #0x3c
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_08046D3E:
	ldrb r1, [r7, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r6, [r7, #0x54]
	subs r0, r0, r6
	ldr r3, _08046DBC @ =0xFFFFA800
	adds r0, r0, r3
	adds r1, r7, #0
	adds r1, #0xc7
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #2
	subs r1, r1, r2
	lsls r1, r1, #0xc
	adds r0, r0, r1
	adds r2, r7, #0
	adds r2, #0xb8
	ldr r5, [r7, #0x58]
	movs r3, #0xa0
	lsls r3, r3, #7
	adds r1, r5, r3
	ldr r4, [r2]
	subs r4, r4, r1
	movs r1, #0xc
	bl __divsi3
	mov r8, r0
	adds r0, r4, #0
	movs r1, #0xc
	bl __divsi3
	add r6, r8
	str r6, [r7, #0x54]
	adds r5, r5, r0
	str r5, [r7, #0x58]
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08046DAE
	adds r1, r7, #0
	adds r1, #0xc8
	movs r0, #1
	strb r0, [r1]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_08046DAE:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	b _08046E50
	.align 2, 0
_08046DB8: .4byte 0xFFFF5000
_08046DBC: .4byte 0xFFFFA800
_08046DC0:
	ldrb r0, [r7, #0x10]
	adds r1, r7, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r1, #0xc4
	lsls r1, r1, #6
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r7, #0x10]
	cmp r0, #0
	bne _08046DFA
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x16
	bl StartPaletteAnimation
	adds r1, r7, #0
	adds r1, #0xc6
	movs r0, #0x16
	b _08046E1A
_08046DFA:
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	orrs r1, r0
	movs r0, #0x11
	bl StartPaletteAnimation
	adds r1, r7, #0
	adds r1, #0xc6
	movs r0, #0x11
_08046E1A:
	strb r0, [r1]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_08046E22:
	adds r4, r7, #0
	adds r4, #0xc6
	ldrb r0, [r4]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _08046E4A
	ldrb r0, [r4]
	cmp r0, #0
	beq _08046E42
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_08046E42:
	movs r1, #0
	movs r0, #1
	strb r0, [r7, #0xd]
	strb r1, [r7, #0xe]
_08046E4A:
	adds r0, r7, #0
	bl UpdateMotionGraphic
_08046E50:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
