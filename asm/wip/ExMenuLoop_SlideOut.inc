	push {lr}
	adds r2, r0, #0
	ldr r1, _080F7D00 @ =0x00000E19
	adds r0, r2, r1
	ldrb r0, [r0]
	cmp r0, #2
	bne _080F7D08
	ldr r1, _080F7D04 @ =gVideoRegBuffer+16
	ldrh r0, [r1]
	adds r0, #0x10
	b _080F7D0E
	.align 2, 0
_080F7D00: .4byte 0x00000E19
_080F7D04: .4byte gVideoRegBuffer+16
_080F7D08:
	ldr r1, _080F7D3C @ =gVideoRegBuffer+16
	ldrh r0, [r1]
	subs r0, #0x10
_080F7D0E:
	strh r0, [r1]
	adds r3, r1, #0
	ldrh r0, [r3]
	ldr r1, _080F7D40 @ =0x000001FF
	ands r1, r0
	strh r1, [r3]
	movs r0, #0xff
	ands r0, r1
	cmp r0, #0
	bne _080F7D38
	ldr r3, _080F7D44 @ =0x00000E19
	adds r0, r2, r3
	ldrb r1, [r0]
	subs r3, #1
	adds r0, r2, r3
	strb r1, [r0]
	movs r0, #1
	strb r0, [r2, #2]
	adds r0, r2, #0
	bl ExMenuLoop_Exit
_080F7D38:
	pop {r0}
	bx r0
	.align 2, 0
_080F7D3C: .4byte gVideoRegBuffer+16
_080F7D40: .4byte 0x000001FF
_080F7D44: .4byte 0x00000E19
