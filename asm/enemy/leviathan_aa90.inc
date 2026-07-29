	push {r4, r5, r6, lr}
	ldr r6, [r0, #8]
	ldr r0, [r6, #0x54]
	ldr r2, [r1, #8]
	subs r0, r0, r2
	asrs r5, r0, #8
	ldr r0, [r6, #0x58]
	ldr r1, [r1, #0xc]
	subs r0, r0, r1
	asrs r4, r0, #8
	subs r5, #0x10
	adds r0, r5, #0
	cmp r5, #0
	bge _0809AAAE
	adds r0, r5, #7
_0809AAAE:
	asrs r5, r0, #3
	ldrb r1, [r6, #0x13]
	subs r0, r5, r1
	adds r0, #1
	cmp r0, #0
	bge _0809AABE
	subs r5, r1, #1
	b _0809AAC6
_0809AABE:
	adds r0, r5, #7
	cmp r0, #0x1e
	ble _0809AAC6
	movs r5, #0x17
_0809AAC6:
	adds r4, #0x10
	adds r0, r4, #0
	cmp r4, #0
	bge _0809AAD0
	adds r0, r4, #7
_0809AAD0:
	asrs r4, r0, #3
	cmp r4, #0
	bgt _0809AADA
	movs r4, #1
	b _0809AAE0
_0809AADA:
	cmp r4, #0x11
	ble _0809AAE0
	movs r4, #0x11
_0809AAE0:
	ldr r0, [r6, #0x68]
	cmp r0, #1
	ble _0809AAFC
	lsls r1, r5, #0x10
	lsrs r1, r1, #0x10
	lsls r2, r4, #0x10
	lsrs r2, r2, #0x10
	bl PrintMinigameNumber
	ldr r0, _0809AB20 @ =0x080FF070
	adds r1, r5, #2
	adds r2, r4, #0
	bl PrintUnicodeString
_0809AAFC:
	ldr r0, _0809AB24 @ =0x080FF078
	adds r4, #1
	adds r1, r5, #0
	adds r2, r4, #0
	bl PrintUnicodeString
	ldr r0, [r6, #0x5c]
	adds r1, r5, #1
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	adds r2, r4, #0
	bl PrintMinigameNumber
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809AB20: .4byte 0x080FF070
_0809AB24: .4byte 0x080FF078

