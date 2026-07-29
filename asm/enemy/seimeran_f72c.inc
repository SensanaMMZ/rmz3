	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _0808F742
	bl isKilled
	cmp r0, #0
	beq _0808F7A4
_0808F742:
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0xc0
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0xc
	bne _0808F760
	subs r0, #0x4c
	ldr r1, _0808F75C @ =0x08369524
	bl SetDDP
	b _0808F77A
	.align 2, 0
_0808F75C: .4byte 0x08369524
_0808F760:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808F794 @ =0x08369584
	ldrb r1, [r5]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808F798 @ =0x0836941C
	adds r1, r1, r2
	bl SetDDP
_0808F77A:
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _0808F7A4
	ldrb r0, [r5]
	cmp r0, #0xc
	bne _0808F79C
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0808F7A4
	.align 2, 0
_0808F794: .4byte 0x08369584
_0808F798: .4byte 0x0836941C
_0808F79C:
	movs r0, #1
	strb r0, [r4, #0xd]
	movs r0, #3
	strb r0, [r4, #0xe]
_0808F7A4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

