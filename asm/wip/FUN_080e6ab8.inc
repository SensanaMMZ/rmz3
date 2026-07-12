	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldr r1, _080E6B0C @ =0x000064AC
	adds r0, r0, r1
	ldr r4, [r0]
	ldr r1, _080E6B10 @ =gWidgetFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _080E6B18
	ldr r1, _080E6B14 @ =sHeadChipMotions
	adds r0, r4, #0
	adds r0, #0xb4
	ldrb r0, [r0, #0xf]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	movs r1, #5
	bl ForceEntityPalette
	b _080E6B64
	.align 2, 0
_080E6B0C: .4byte 0x000064AC
_080E6B10: .4byte gWidgetFnTable
_080E6B14: .4byte sHeadChipMotions
_080E6B18:
	cmp r0, #1
	bne _080E6B48
	ldr r1, _080E6B40 @ =sBodyChipMotions
	adds r4, #0xb4
	ldrb r0, [r4, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	ldr r1, _080E6B44 @ =sBodyChipPalIDs
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r1, [r0]
	adds r0, r5, #0
	bl ForceEntityPalette
	b _080E6B64
	.align 2, 0
_080E6B40: .4byte sBodyChipMotions
_080E6B44: .4byte sBodyChipPalIDs
_080E6B48:
	ldr r1, _080E6BB0 @ =sFootChipMotions
	adds r0, r4, #0
	adds r0, #0xb4
	ldrb r0, [r0, #0x11]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	movs r1, #5
	bl ForceEntityPalette
_080E6B64:
	adds r0, r5, #0
	adds r0, #0x4c
	movs r2, #0
	strb r2, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	subs r3, #1
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x9c
	lsls r0, r0, #8
	str r0, [r5, #0x54]
	ldr r1, _080E6BB4 @ =sChipHeight
	ldrb r0, [r5, #0x11]
	adds r0, r0, r1
	ldrb r0, [r0]
	lsls r0, r0, #8
	str r0, [r5, #0x58]
	adds r0, r5, #0
	adds r0, #0x79
	strb r2, [r0]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080E6BB0: .4byte sFootChipMotions
_080E6BB4: .4byte sChipHeight
