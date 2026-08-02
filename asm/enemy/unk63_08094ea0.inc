	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08094EB0
	cmp r5, #1
	beq _08094EDA
	b _08094F38
_08094EB0:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xf
	strb r0, [r1]
	movs r0, #0x40
	bl PlaySound
	strb r5, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08094F14 @ =0x08369F2C
	bl SetDDP
	movs r1, #0xb0
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094EDA:
	ldr r2, _08094F18 @ =pZero2
	ldr r0, [r2]
	ldr r1, _08094F1C @ =0x00000143
	adds r3, r0, r1
	ldrb r1, [r3]
	movs r0, #0x10
	rsbs r0, r0, #0
	ands r0, r1
	movs r5, #1
	orrs r0, r5
	strb r0, [r3]
	ldr r0, [r2]
	ldr r1, _08094F1C @ =0x00000143
	adds r3, r0, r1
	ldrb r1, [r3]
	movs r0, #0xf
	ands r0, r1
	strb r0, [r3]
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08094F20
	ldrb r0, [r4, #0xa]
	orrs r0, r5
	b _08094F26
	.align 2, 0
_08094F14: .4byte 0x08369F2C
_08094F18: .4byte pZero2
_08094F1C: .4byte 0x00000143
_08094F20:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08094F26:
	strb r0, [r4, #0xa]
	ldr r0, [r2]
	ldr r1, [r0, #0x54]
	str r1, [r4, #0x54]
	ldr r0, [r0, #0x58]
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08094F38:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
