	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08054B54
	cmp r0, #1
	bgt _08054B34
	cmp r0, #0
	beq _08054B3E
	b _08054B8E
_08054B34:
	cmp r0, #2
	beq _08054B6E
	cmp r0, #3
	beq _08054B72
	b _08054B8E
_08054B3E:
	adds r0, r4, #0
	bl InitRotatableMotion
	movs r1, #0xa8
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08054B54:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08054B66
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08054B66:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08054B8E
_08054B6E:
	movs r0, #3
	strb r0, [r4, #0xe]
_08054B72:
	adds r1, r4, #0
	adds r1, #0xbd
	movs r0, #1
	strb r0, [r1]
	ldr r1, _08054B94 @ =gStageRun
	ldrb r1, [r1, #0x12]
	ands r0, r1
	cmp r0, #0
	bne _08054B88
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08054B88:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08054B8E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08054B94: .4byte gStageRun

