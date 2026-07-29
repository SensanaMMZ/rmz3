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
	bge _0809AA2E
	adds r0, r5, #7
_0809AA2E:
	asrs r5, r0, #3
	cmp r5, #0
	bge _0809AA38
	movs r5, #0
	b _0809AA40
_0809AA38:
	adds r0, r5, #4
	cmp r0, #0x1e
	ble _0809AA40
	movs r5, #0x1a
_0809AA40:
	adds r4, #0x10
	adds r0, r4, #0
	cmp r4, #0
	bge _0809AA4A
	adds r0, r4, #7
_0809AA4A:
	asrs r4, r0, #3
	cmp r4, #0
	bgt _0809AA54
	movs r4, #1
	b _0809AA5A
_0809AA54:
	cmp r4, #0x11
	ble _0809AA5A
	movs r4, #0x11
_0809AA5A:
	ldr r0, _0809AA88 @ =0x080FF064
	adds r1, r5, #0
	adds r2, r4, #0
	bl PrintUnicodeString
	ldr r0, _0809AA8C @ =0x080FF06C
	adds r1, r5, #2
	adds r4, #1
	adds r2, r4, #0
	bl PrintUnicodeString
	ldr r0, [r6, #0x5c]
	lsls r1, r5, #0x10
	lsrs r1, r1, #0x10
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	adds r2, r4, #0
	bl PrintMinigameNumber
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809AA88: .4byte 0x080FF064
_0809AA8C: .4byte 0x080FF06C

