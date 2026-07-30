	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldrb r6, [r7, #0xe]
	cmp r6, #0
	beq _080BFB64
	cmp r6, #1
	beq _080BFBEA
	b _080BFC88
_080BFB64:
	adds r0, r7, #0
	bl InitRotatableMotion
	ldr r0, _080BFC00 @ =0x00004C05
	adds r1, r0, #0
	ldrb r2, [r7, #0x12]
	adds r1, r1, r2
	adds r0, r7, #0
	bl SetMotion
	ldrb r1, [r7, #0x12]
	lsls r1, r1, #7
	ldr r0, _080BFC04 @ =0xFFFFFE00
	adds r1, r1, r0
	ldr r2, _080BFC08 @ =RNG_0202f388
	mov ip, r2
	ldr r0, [r2]
	ldr r3, _080BFC0C @ =0x000343FD
	muls r0, r3, r0
	ldr r2, _080BFC10 @ =0x00269EC3
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	movs r5, #0xff
	ands r0, r5
	adds r1, r1, r0
	str r1, [r7, #0x5c]
	ldr r1, _080BFC14 @ =0xFFFFFC80
	adds r0, r4, #0
	muls r0, r3, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r5
	subs r1, r1, r0
	str r1, [r7, #0x60]
	strb r6, [r7, #0x13]
	adds r0, r4, #0
	muls r0, r3, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r2, ip
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
	adds r4, r0, #0
	adds r4, #1
	str r4, [r7, #0x64]
	ldrb r0, [r7, #0x12]
	movs r1, #3
	bl __udivsi3
	movs r1, #1
	eors r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	muls r0, r4, r0
	subs r4, r4, r0
	str r4, [r7, #0x64]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080BFBEA:
	ldrb r0, [r7, #0x12]
	adds r0, #1
	strb r0, [r7, #0x12]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080BFC18
	ldrb r0, [r7, #0xa]
	orrs r0, r1
	b _080BFC1E
	.align 2, 0
_080BFC00: .4byte 0x00004C05
_080BFC04: .4byte 0xFFFFFE00
_080BFC08: .4byte RNG_0202f388
_080BFC0C: .4byte 0x000343FD
_080BFC10: .4byte 0x00269EC3
_080BFC14: .4byte 0xFFFFFC80
_080BFC18:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BFC1E:
	strb r0, [r7, #0xa]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	ldr r0, [r7, #0x60]
	adds r0, #0x40
	str r0, [r7, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080BFC38
	str r1, [r7, #0x60]
_080BFC38:
	ldr r1, [r7, #0x58]
	ldr r0, [r7, #0x60]
	adds r1, r1, r0
	str r1, [r7, #0x58]
	ldr r0, [r7, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080BFC74
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	movs r2, #1
	bl FUN_080bf438
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _080BFC90 @ =gVFXFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
_080BFC74:
	ldr r0, [r7, #0x64]
	ldrb r1, [r7, #0x13]
	adds r1, r1, r0
	strb r1, [r7, #0x13]
	adds r0, r7, #0
	adds r0, #0x24
	strb r1, [r0]
	adds r0, r7, #0
	bl UpdateMotionGraphic
_080BFC88:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080BFC90: .4byte gVFXFnTable
