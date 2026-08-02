	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldr r0, [r7, #0x58]
	adds r2, r0, r1
	str r2, [r7, #0x58]
	cmp r1, #0
	bge _0808D2B4
	ldr r0, [r7, #0x54]
	ldr r1, _0808D2AC @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r4, _0808D2B0 @ =0xFFFFE200
	adds r1, r2, r4
	bl PushoutToDown1
	adds r5, r0, #0
	ldr r0, [r7, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r7, #0x58]
	adds r1, r1, r4
	bl PushoutToDown1
	adds r6, r0, #0
	cmp r5, r6
	bge _0808D29E
	adds r5, r0, #0
_0808D29E:
	cmp r5, #0
	ble _0808D2EC
	ldr r0, [r7, #0x58]
	adds r0, r0, r5
	str r0, [r7, #0x58]
	movs r0, #1
	b _0808D2EE
	.align 2, 0
_0808D2AC: .4byte 0xFFFFEE00
_0808D2B0: .4byte 0xFFFFE200
_0808D2B4:
	ldr r0, [r7, #0x54]
	ldr r1, _0808D2E8 @ =0xFFFFEE00
	adds r0, r0, r1
	adds r1, r2, #0
	bl PushoutToUp1
	adds r5, r0, #0
	ldr r0, [r7, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r7, #0x58]
	bl PushoutToUp1
	adds r6, r0, #0
	cmp r5, r6
	ble _0808D2D8
	adds r5, r0, #0
_0808D2D8:
	cmp r5, #0
	bge _0808D2EC
	ldr r0, [r7, #0x58]
	adds r0, r0, r5
	str r0, [r7, #0x58]
	movs r0, #2
	b _0808D2EE
	.align 2, 0
_0808D2E8: .4byte 0xFFFFEE00
_0808D2EC:
	movs r0, #0
_0808D2EE:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
