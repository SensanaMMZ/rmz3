thumb_func_start readKeyInput
readKeyInput:
  push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldrh r2, [r4]
	strh r2, [r4, #2]
	cmp r1, #0
	beq _0800315E
	movs r0, #0
	strh r0, [r4, #8]
	b _080031D2
_0800315E:
	movs r0, #1
	strh r0, [r4, #8]
	ldr r0, _080031AC @ =0x04000130
	ldrh r0, [r0]
	mvns r0, r0
	strh r0, [r4]
	bics r0, r2
	strh r0, [r4, #4]
	strh r1, [r4, #6]
	movs r1, #0
	movs r7, #1
	adds r6, r4, #0
	adds r6, #0xa
_08003178:
	ldrh r2, [r4]
	lsls r0, r1, #0x10
	asrs r3, r0, #0x10
	asrs r2, r3
	ands r2, r7
	adds r5, r0, #0
	cmp r2, #0
	beq _080031C0
	adds r2, r6, r3
	movs r0, #0
	ldrsb r0, [r2, r0]
	cmp r0, #0
	bne _080031B4
	adds r0, r7, #0
	lsls r0, r3
	ldrh r1, [r4, #6]
	orrs r0, r1
	strh r0, [r4, #6]
	ldrh r0, [r4, #4]
	asrs r0, r3
	ands r0, r7
	cmp r0, #0
	beq _080031B0
	ldrb r0, [r4, #0x14]
	b _080031B2
	.align 2, 0
_080031AC: .4byte 0x04000130
_080031B0:
	ldrb r0, [r4, #0x15]
_080031B2:
	strb r0, [r2]
_080031B4:
	asrs r1, r5, #0x10
	adds r1, r6, r1
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	b _080031C4
_080031C0:
	adds r0, r6, r3
	strb r2, [r0]
_080031C4:
	movs r1, #0x80
	lsls r1, r1, #9
	adds r0, r5, r1
	lsrs r1, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #9
	ble _08003178
_080031D2:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
