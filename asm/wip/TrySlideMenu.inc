	push {r4, lr}
	adds r3, r0, #0
	ldr r0, _080F3C14 @ =gJoypad
	ldrh r1, [r0, #4]
	movs r0, #2
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0
	beq _080F3C18
	movs r0, #3
	strb r0, [r3, #1]
	strb r0, [r3, #2]
	b _080F3C7C
	.align 2, 0
_080F3C14: .4byte gJoypad
_080F3C18:
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	cmp r4, #0
	beq _080F3C44
	ldr r1, _080F3C3C @ =0x00000E18
	adds r0, r3, r1
	ldrb r0, [r0]
	adds r0, #3
	movs r1, #3
	ands r0, r1
	ldr r4, _080F3C40 @ =0x00000E19
	adds r1, r3, r4
	strb r0, [r1]
	strb r2, [r3, #2]
	b _080F3C66
	.align 2, 0
_080F3C3C: .4byte 0x00000E18
_080F3C40: .4byte 0x00000E19
_080F3C44:
	movs r0, #0x80
	lsls r0, r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080F3C52
	movs r0, #0
	b _080F3C7E
_080F3C52:
	ldr r1, _080F3C84 @ =0x00000E18
	adds r0, r3, r1
	ldrb r0, [r0]
	adds r0, #1
	movs r1, #3
	ands r0, r1
	ldr r2, _080F3C88 @ =0x00000E19
	adds r1, r3, r2
	strb r0, [r1]
	strb r4, [r3, #2]
_080F3C66:
	ldr r2, _080F3C8C @ =sEachMenuLoops
	ldrb r0, [r1]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r0]
	adds r0, r3, #0
	bl _call_via_r1
	movs r0, #0x33
	bl PlaySound
_080F3C7C:
	movs r0, #1
_080F3C7E:
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080F3C84: .4byte 0x00000E18
_080F3C88: .4byte 0x00000E19
_080F3C8C: .4byte sEachMenuLoops
