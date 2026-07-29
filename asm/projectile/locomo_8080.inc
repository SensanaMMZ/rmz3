	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r4, [r5, #0xe]
	cmp r4, #0
	beq _080A8090
	cmp r4, #1
	beq _080A80B2
	b _080A8110
_080A8090:
	movs r0, #0x40
	bl PlaySound
	strb r4, [r5, #0x12]
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A80EC @ =0x0836BE94
	bl SetDDP
	movs r1, #0xb0
	lsls r1, r1, #7
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A80B2:
	ldr r2, _080A80F0 @ =pZero2
	ldr r0, [r2]
	ldr r1, _080A80F4 @ =0x00000143
	adds r3, r0, r1
	ldrb r1, [r3]
	movs r0, #0x10
	rsbs r0, r0, #0
	ands r0, r1
	movs r4, #1
	orrs r0, r4
	strb r0, [r3]
	ldr r0, [r2]
	ldr r1, _080A80F4 @ =0x00000143
	adds r3, r0, r1
	ldrb r1, [r3]
	movs r0, #0xf
	ands r0, r1
	strb r0, [r3]
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080A80F8
	ldrb r0, [r5, #0xa]
	orrs r0, r4
	b _080A80FE
	.align 2, 0
_080A80EC: .4byte 0x0836BE94
_080A80F0: .4byte pZero2
_080A80F4: .4byte 0x00000143
_080A80F8:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080A80FE:
	strb r0, [r5, #0xa]
	ldr r0, [r2]
	ldr r1, [r0, #0x54]
	str r1, [r5, #0x54]
	ldr r0, [r0, #0x58]
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080A8110:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
