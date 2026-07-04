	push {r4, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #4]
	adds r0, #1
	adds r1, r0, #0
	strh r0, [r4, #4]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xf
	ble _080F36FC
	ldr r1, _080F36F0 @ =gPaletteManager
	ldr r2, _080F36F4 @ =0x00000402
	adds r0, r1, r2
	movs r2, #0x20
	strb r2, [r0]
	ldr r3, _080F36F8 @ =0x00000401
	adds r0, r1, r3
	strb r2, [r0]
	movs r0, #0x80
	lsls r0, r0, #3
	adds r1, r1, r0
	strb r2, [r1]
	movs r0, #2
	strb r0, [r4, #1]
	adds r0, r4, #0
	bl MenuLoop_Update
	b _080F3716
	.align 2, 0
_080F36F0: .4byte gPaletteManager
_080F36F4: .4byte 0x00000402
_080F36F8: .4byte 0x00000401
_080F36FC:
	ldr r2, _080F3724 @ =gPaletteManager
	ldr r3, _080F3728 @ =0x00000402
	adds r0, r2, r3
	strb r1, [r0]
	movs r0, #0xff
	ands r0, r1
	subs r3, #1
	adds r1, r2, r3
	strb r0, [r1]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r2, r2, r1
	strb r0, [r2]
_080F3716:
	adds r0, r4, #0
	bl menu_080f39a8
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080F3724: .4byte gPaletteManager
_080F3728: .4byte 0x00000402
