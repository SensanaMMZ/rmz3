	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r1, _080F4710 @ =0x000064AC
	adds r0, r6, r1
	ldr r7, [r0]
	ldr r1, _080F4714 @ =gMainMenuFocusLoops
	ldrb r0, [r6, #3]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	ldr r0, _080F4718 @ =0x00000DCC
	adds r4, r6, r0
	ldrb r1, [r4, #0xf]
	movs r0, #0x38
	ands r0, r1
	cmp r0, #0
	beq _080F46A2
	adds r0, r6, #0
	bl menu_080f54a0
_080F46A2:
	movs r0, #4
	bl StepPaletteAnimation
	ldrb r2, [r4, #0x10]
	adds r1, r2, #0
	cmp r1, #5
	bhi _080F473E
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _080F46D4
	adds r0, r7, #0
	adds r0, #0xb4
	ldrb r0, [r0, #0x10]
	cmp r1, r0
	beq _080F46CE
	adds r0, r2, #0
	adds r0, #0xab
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x11]
	movs r1, #0
	bl StartPaletteAnimation
_080F46CE:
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _080F473E
_080F46D4:
	ldr r1, _080F4718 @ =0x00000DCC
	adds r5, r6, r1
	ldrb r0, [r5, #0x11]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _080F473E
	ldrb r0, [r5, #0x11]
	bl RemovePaletteAnimation
	ldrb r0, [r5, #0x11]
	cmp r0, #0xb2
	bhi _080F471C
	adds r0, r7, #0
	adds r0, #0xb4
	ldrb r0, [r0, #0x10]
	strb r0, [r5, #0x10]
	adds r0, #0xb3
	strb r0, [r5, #0x11]
	ldrb r0, [r5, #0x11]
	movs r1, #0
	bl StartPaletteAnimation
	ldrb r0, [r5, #0x11]
	bl StepPaletteAnimation
	b _080F473E
	.align 2, 0
_080F4710: .4byte 0x000064AC
_080F4714: .4byte gMainMenuFocusLoops
_080F4718: .4byte 0x00000DCC
_080F471C:
	adds r0, r7, #0
	adds r0, #0xb4
	ldrb r0, [r0, #0x10]
	adds r0, #0xab
	movs r4, #0
	strb r0, [r5, #0x11]
	ldrb r0, [r5, #0x11]
	movs r1, #0
	bl StartPaletteAnimation
	ldrb r0, [r5, #0x11]
	bl StepPaletteAnimation
	ldrb r0, [r5, #0x11]
	bl RemovePaletteAnimation
	strb r4, [r5, #0x11]
_080F473E:
	adds r0, r6, #0
	bl printMainMenuString
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
