	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805651E
	ldr r1, _0805653C @ =0x0000B304
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
_0805651E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080565AC
	adds r5, r4, #0
	adds r5, #0xcd
	ldrb r0, [r5]
	cmp r0, #0
	beq _08056540
	subs r0, #1
	b _0805659A
	.align 2, 0
_0805653C: .4byte 0x0000B304
_08056540:
	adds r0, r4, #0
	adds r0, #0xc7
	ldrb r0, [r0]
	cmp r0, #0
	bne _0805659C
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #1
	bne _0805657C
	ldr r2, _08056570 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08056574 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08056578 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	b _0805659A
	.align 2, 0
_08056570: .4byte RNG_0202f388
_08056574: .4byte 0x000343FD
_08056578: .4byte 0x00269EC3
_0805657C:
	cmp r0, #2
	bne _0805659C
	ldr r2, _080565B4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080565B8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080565BC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
_0805659A:
	strb r0, [r5]
_0805659C:
	movs r0, #3
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	movs r0, #2
	strb r0, [r4, #0xf]
	movs r0, #4
	strb r0, [r4, #0x12]
_080565AC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080565B4: .4byte RNG_0202f388
_080565B8: .4byte 0x000343FD
_080565BC: .4byte 0x00269EC3
