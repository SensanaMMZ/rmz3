	push {lr}
	ldrb r0, [r0, #0x10]
	cmp r0, #0x17
	beq _080DAD50
	cmp r0, #0x17
	bgt _080DAD22
	cmp r0, #0x16
	beq _080DAD2C
	b _080DADF0
_080DAD22:
	cmp r0, #0x18
	beq _080DAD7C
	cmp r0, #0x19
	beq _080DADCE
	b _080DADF0
_080DAD2C:
	ldr r0, _080DAD44 @ =gCurStory
	adds r1, r0, #0
	adds r1, #0x25
	ldrb r0, [r1]
	cmp r0, #0
	bne _080DAD48
	adds r0, #1
	strb r0, [r1]
	movs r0, #0xad
	lsls r0, r0, #2
	b _080DADF2
	.align 2, 0
_080DAD44: .4byte gCurStory
_080DAD48:
	ldr r0, _080DAD4C @ =0x000002B5
	b _080DADF2
	.align 2, 0
_080DAD4C: .4byte 0x000002B5
_080DAD50:
	ldr r2, _080DAD60 @ =gCurStory
	ldrb r1, [r2, #6]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080DAD68
	ldr r0, _080DAD64 @ =0x000002AF
	b _080DADF2
	.align 2, 0
_080DAD60: .4byte gCurStory
_080DAD64: .4byte 0x000002AF
_080DAD68:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DADF0
	ldr r0, _080DAD78 @ =0x000002AE
	b _080DADF2
	.align 2, 0
_080DAD78: .4byte 0x000002AE
_080DAD7C:
	ldr r2, _080DAD8C @ =gCurStory
	ldrb r1, [r2, #6]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080DAD94
	ldr r0, _080DAD90 @ =0x000002B3
	b _080DADF2
	.align 2, 0
_080DAD8C: .4byte gCurStory
_080DAD90: .4byte 0x000002B3
_080DAD94:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DADC8
	ldr r0, _080DADB8 @ =gStageDiskManager
	ldr r0, [r0]
	ldrb r1, [r0, #5]
	movs r0, #0xf
	ands r0, r1
	lsrs r0, r0, #2
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080DADC0
	ldr r0, _080DADBC @ =0x000002B2
	b _080DADF2
	.align 2, 0
_080DADB8: .4byte gStageDiskManager
_080DADBC: .4byte 0x000002B2
_080DADC0:
	ldr r0, _080DADC4 @ =0x000002B1
	b _080DADF2
	.align 2, 0
_080DADC4: .4byte 0x000002B1
_080DADC8:
	movs r0, #0xac
	lsls r0, r0, #2
	b _080DADF2
_080DADCE:
	ldr r0, _080DADE4 @ =gCurStory
	adds r1, r0, #0
	adds r1, #0x28
	ldrb r0, [r1]
	cmp r0, #0
	bne _080DADE8
	adds r0, #1
	strb r0, [r1]
	movs r0, #0xae
	lsls r0, r0, #2
	b _080DADF2
	.align 2, 0
_080DADE4: .4byte gCurStory
_080DADE8:
	ldr r0, _080DADEC @ =0x000002B9
	b _080DADF2
	.align 2, 0
_080DADEC: .4byte 0x000002B9
_080DADF0:
	ldr r0, _080DADF8 @ =0x000002AD
_080DADF2:
	pop {r1}
	bx r1
	.align 2, 0
_080DADF8: .4byte 0x000002AD
