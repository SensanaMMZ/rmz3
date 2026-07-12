	push {r4, r5, r6, r7, lr}
	mov ip, r0
	ldr r0, _0804044C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	mov r2, ip
	ldr r0, [r2, #0x54]
	subs r3, r1, r0
	cmp r3, #0
	bge _0804043E
	rsbs r3, r3, #0
_0804043E:
	mov r4, ip
	adds r4, #0xc5
	ldr r6, _08040450 @ =RNG_0202f388
	mov r5, ip
	adds r5, #0xc4
	ldr r7, _08040454 @ =u8_ARRAY_0836205c
	b _0804045E
	.align 2, 0
_0804044C: .4byte pZero2
_08040450: .4byte RNG_0202f388
_08040454: .4byte u8_ARRAY_0836205c
_08040458:
	ldrb r0, [r4]
	cmp r0, #1
	bls _080404B4
_0804045E:
	ldr r1, [r6]
	ldr r0, _08040484 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08040488 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r6]
	lsrs r1, r0, #0x11
	movs r0, #0xf
	ands r1, r0
	adds r2, r1, #0
	ldr r0, _0804048C @ =0x00004FFF
	cmp r3, r0
	bgt _08040494
	ldr r0, _08040490 @ =u8_ARRAY_ARRAY_0836202c
	adds r0, r1, r0
	b _080404AC
	.align 2, 0
_08040484: .4byte 0x000343FD
_08040488: .4byte 0x00269EC3
_0804048C: .4byte 0x00004FFF
_08040490: .4byte u8_ARRAY_ARRAY_0836202c
_08040494:
	ldr r0, _080404A0 @ =0x00008FFF
	cmp r3, r0
	bgt _080404A8
	ldr r0, _080404A4 @ =u8_ARRAY_ARRAY_0836202c+16
	adds r0, r1, r0
	b _080404AC
	.align 2, 0
_080404A0: .4byte 0x00008FFF
_080404A4: .4byte u8_ARRAY_ARRAY_0836202c+16
_080404A8:
	ldr r0, _080404C0 @ =u8_ARRAY_ARRAY_0836202c+32
	adds r0, r2, r0
_080404AC:
	ldrb r1, [r0]
	ldrb r0, [r5]
	cmp r0, r1
	beq _08040458
_080404B4:
	ldrb r0, [r5]
	cmp r0, r1
	bne _080404C4
	ldrb r0, [r4]
	adds r0, #1
	b _080404C8
	.align 2, 0
_080404C0: .4byte u8_ARRAY_ARRAY_0836202c+32
_080404C4:
	movs r0, #0
	strb r1, [r5]
_080404C8:
	strb r0, [r4]
	adds r0, r1, r7
	ldrb r0, [r0]
	mov r2, ip
	strb r0, [r2, #0xd]
	cmp r1, #1
	bhi _080404D8
	strb r1, [r2, #0x12]
_080404D8:
	movs r0, #0
	mov r1, ip
	strb r0, [r1, #0xe]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
