	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x74]
	ldr r1, _080E6C04 @ =gWidgetFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _080E6C0C
	ldr r0, _080E6C08 @ =sHeadChipMotions
	ldrb r1, [r4, #0x11]
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	movs r1, #5
	bl ForceEntityPalette
	b _080E6C50
	.align 2, 0
_080E6C04: .4byte gWidgetFnTable
_080E6C08: .4byte sHeadChipMotions
_080E6C0C:
	cmp r0, #1
	bne _080E6C38
	ldr r1, _080E6C30 @ =sBodyChipMotions
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldr r1, _080E6C34 @ =sBodyChipPalIDs
	ldrb r0, [r4, #0x11]
	adds r0, r0, r1
	ldrb r1, [r0]
	adds r0, r4, #0
	bl ForceEntityPalette
	b _080E6C50
	.align 2, 0
_080E6C30: .4byte sBodyChipMotions
_080E6C34: .4byte sBodyChipPalIDs
_080E6C38:
	ldr r0, _080E6C90 @ =sFootChipMotions
	ldrb r1, [r4, #0x11]
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	movs r1, #5
	bl ForceEntityPalette
_080E6C50:
	adds r0, r4, #0
	adds r0, #0x4c
	movs r2, #0
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	subs r3, #1
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r3]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	strb r2, [r4, #0x12]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080E6C90: .4byte sFootChipMotions
