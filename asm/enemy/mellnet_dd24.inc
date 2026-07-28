	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #5
	bls _0807DD30
	b _0807DEDE
_0807DD30:
	lsls r0, r0, #2
	ldr r1, _0807DD3C @ =_0807DD40
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807DD3C: .4byte _0807DD40
_0807DD40: @ jump table
	.4byte _0807DD58 @ case 0
	.4byte _0807DE6C @ case 1
	.4byte _0807DE34 @ case 2
	.4byte _0807DE6C @ case 3
	.4byte _0807DE8C @ case 4
	.4byte _0807DEC4 @ case 5
_0807DD58:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _0807DD80 @ =0x08367CF4
	bl SetDDP
	movs r2, #0
	ldr r0, _0807DD84 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r6, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _0807DD72
	movs r2, #1
_0807DD72:
	cmp r2, #0
	beq _0807DD88
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0807DD8E
	.align 2, 0
_0807DD80: .4byte 0x08367CF4
_0807DD84: .4byte pZero2
_0807DD88:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0807DD8E:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r0, _0807DE28 @ =pZero2
	ldr r1, [r0]
	ldr r5, [r1, #0x54]
	ldr r0, [r6, #0x54]
	subs r5, r5, r0
	ldr r4, [r1, #0x58]
	ldr r0, _0807DE2C @ =0xFFFFE800
	adds r4, r4, r0
	ldr r0, [r6, #0x58]
	subs r4, r4, r0
	asrs r0, r5, #8
	adds r7, r0, #0
	muls r7, r0, r7
	asrs r0, r4, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r7, r7, r0
	adds r0, r7, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r7, r0, #8
	lsls r5, r5, #8
	adds r0, r5, #0
	adds r1, r7, #0
	bl __divsi3
	adds r5, r0, #0
	lsls r4, r4, #8
	adds r0, r4, #0
	adds r1, r7, #0
	bl __divsi3
	lsls r5, r5, #2
	lsls r0, r0, #2
	str r5, [r6, #0x5c]
	str r0, [r6, #0x60]
	adds r0, r6, #0
	adds r0, #0x71
	movs r7, #0
	ldrsb r7, [r0, r7]
	ldr r2, _0807DE30 @ =0x08367D4E
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	rsbs r0, r0, #0
	asrs r0, r0, #0x1f
	movs r1, #2
	ands r0, r1
	adds r0, r0, r2
	ldrh r1, [r0]
	lsls r2, r7, #0x10
	lsrs r2, r2, #0x10
	adds r0, r6, #0
	movs r3, #3
	bl GotoMotion
	movs r0, #3
	b _0807DE64
	.align 2, 0
_0807DE28: .4byte pZero2
_0807DE2C: .4byte 0xFFFFE800
_0807DE30: .4byte 0x08367D4E
_0807DE34:
	adds r0, r6, #0
	adds r0, #0x71
	movs r7, #0
	ldrsb r7, [r0, r7]
	ldr r2, _0807DE88 @ =0x08367D4E
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	rsbs r0, r0, #0
	asrs r0, r0, #0x1f
	movs r1, #2
	ands r0, r1
	adds r2, #4
	adds r0, r0, r2
	ldrh r1, [r0]
	lsls r2, r7, #0x10
	lsrs r2, r2, #0x10
	adds r0, r6, #0
	movs r3, #3
	bl GotoMotion
	movs r0, #0xf
_0807DE64:
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0807DE6C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807DEDE
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _0807DEDE
	.align 2, 0
_0807DE88: .4byte 0x08367D4E
_0807DE8C:
	adds r0, r6, #0
	adds r0, #0x71
	movs r7, #0
	ldrsb r7, [r0, r7]
	ldr r2, _0807DEE4 @ =0x08367D4E
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	rsbs r0, r0, #0
	asrs r0, r0, #0x1f
	movs r1, #2
	ands r0, r1
	adds r2, #8
	adds r0, r0, r2
	ldrh r1, [r0]
	lsls r2, r7, #0x10
	lsrs r2, r2, #0x10
	adds r0, r6, #0
	movs r3, #3
	bl GotoMotion
	movs r0, #3
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0807DEC4:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0807DEDE
	movs r0, #5
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_0807DEDE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807DEE4: .4byte 0x08367D4E

