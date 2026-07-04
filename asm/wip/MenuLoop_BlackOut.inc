	push {r4, lr}
	adds r2, r0, #0
	ldrh r0, [r2, #4]
	subs r0, #1
	movs r3, #0
	adds r1, r0, #0
	strh r0, [r2, #4]
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080F37BC
	ldr r0, _080F37B4 @ =gPaletteManager
	ldr r4, _080F37B8 @ =0x00000402
	adds r1, r0, r4
	strb r3, [r1]
	subs r4, #1
	adds r1, r0, r4
	strb r3, [r1]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r0, r0, r1
	strb r3, [r0]
	movs r0, #4
	strb r0, [r2, #1]
	adds r0, r2, #0
	bl MenuLoop_ExitMenu
	b _080F37D6
	.align 2, 0
_080F37B4: .4byte gPaletteManager
_080F37B8: .4byte 0x00000402
_080F37BC:
	ldr r2, _080F37DC @ =gPaletteManager
	ldr r3, _080F37E0 @ =0x00000402
	adds r0, r2, r3
	strb r1, [r0]
	movs r0, #0xff
	ands r0, r1
	ldr r4, _080F37E4 @ =0x00000401
	adds r1, r2, r4
	strb r0, [r1]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r2, r2, r1
	strb r0, [r2]
_080F37D6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080F37DC: .4byte gPaletteManager
_080F37E0: .4byte 0x00000402
_080F37E4: .4byte 0x00000401
