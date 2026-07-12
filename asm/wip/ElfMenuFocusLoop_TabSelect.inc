	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	ldr r0, _080F6C00 @ =0x00000E17
	adds r6, r7, r0
	ldrb r0, [r6]
	cmp r0, #0
	bne _080F6BB8
	movs r0, #0x4f
	movs r1, #0
	bl StartPaletteAnimation
	ldr r0, _080F6C04 @ =0x00000DFC
	adds r1, r7, r0
	ldrb r0, [r1, #8]
	strb r0, [r1, #0xa]
	ldrb r0, [r6]
	adds r0, #1
	strb r0, [r6]
_080F6BB8:
	movs r0, #0x4f
	bl StepPaletteAnimation
	ldr r0, _080F6C04 @ =0x00000DFC
	adds r4, r7, r0
	ldrb r3, [r4, #0xd]
	lsls r1, r3, #0x18
	lsrs r0, r1, #0x18
	cmp r0, #0x90
	bhi _080F6BDE
	lsrs r0, r1, #0x1c
	ldr r2, _080F6C08 @ =gWindowRegBuffer
	lsls r0, r0, #0xc
	movs r1, #0x90
	orrs r0, r1
	strh r0, [r2, #8]
	adds r0, r3, #0
	adds r0, #8
	strb r0, [r4, #0xd]
_080F6BDE:
	ldr r2, _080F6C0C @ =gJoypad
	ldrh r1, [r2, #4]
	movs r5, #0x81
	ands r5, r1
	cmp r5, #0
	beq _080F6C10
	movs r1, #0
	movs r0, #3
	strb r0, [r7, #3]
	strb r1, [r6]
	movs r0, #0x4f
	bl RemovePaletteAnimation
	movs r0, #2
	bl PlaySound
	b _080F6CB6
	.align 2, 0
_080F6C00: .4byte 0x00000E17
_080F6C04: .4byte 0x00000DFC
_080F6C08: .4byte gWindowRegBuffer
_080F6C0C: .4byte gJoypad
_080F6C10:
	movs r0, #2
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	cmp r6, #0
	beq _080F6C50
	strb r5, [r7, #3]
	movs r0, #0x4f
	bl RemovePaletteAnimation
	movs r0, #0x4e
	strb r0, [r4, #0xc]
	movs r1, #0
	bl StartPaletteAnimation
	ldrb r0, [r4, #0xc]
	bl StepPaletteAnimation
	strb r5, [r4, #8]
	ldr r2, _080F6C48 @ =gWindowRegBuffer
	ldrh r1, [r2]
	ldr r0, _080F6C4C @ =0x0000DFFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #3
	bl PlaySound
	b _080F6CB6
	.align 2, 0
_080F6C48: .4byte gWindowRegBuffer
_080F6C4C: .4byte 0x0000DFFF
_080F6C50:
	ldrb r0, [r4, #8]
	mov r8, r0
	ldrh r5, [r2, #6]
	movs r0, #0x20
	ands r0, r5
	cmp r0, #0
	beq _080F6C6A
	mov r0, r8
	adds r0, #2
	movs r1, #3
	bl __modsi3
	strb r0, [r4, #8]
_080F6C6A:
	movs r0, #0x10
	ands r0, r5
	cmp r0, #0
	beq _080F6C7E
	ldrb r0, [r4, #8]
	adds r0, #1
	movs r1, #3
	bl __modsi3
	strb r0, [r4, #8]
_080F6C7E:
	ldrb r0, [r4, #8]
	cmp r8, r0
	beq _080F6CB6
	movs r0, #0x4f
	bl RemovePaletteAnimation
	movs r0, #0x4f
	movs r1, #0
	bl StartPaletteAnimation
	movs r0, #0x4f
	bl StepPaletteAnimation
	ldrb r0, [r4, #8]
	strb r0, [r4, #0xa]
	strb r6, [r4, #6]
	strb r6, [r4, #9]
	adds r0, r7, #0
	bl FUN_080f70d8
	movs r0, #0x10
	strb r0, [r4, #0xd]
	ldr r1, _080F6CC0 @ =gWindowRegBuffer
	ldr r0, _080F6CC4 @ =0x00001090
	strh r0, [r1, #8]
	movs r0, #1
	bl PlaySound
_080F6CB6:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080F6CC0: .4byte gWindowRegBuffer
_080F6CC4: .4byte 0x00001090
