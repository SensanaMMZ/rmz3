	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080bf6d8
FUN_080bf6d8: @ 0x080BF6D8
	push {r4, lr}
	adds r4, r0, #0
	ldr r3, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	cmp r0, #9
	bls _080BF6E6
	b _080BF886
_080BF6E6:
	lsls r0, r0, #2
	ldr r1, _080BF6F0 @ =_080BF6F4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080BF6F0: .4byte _080BF6F4
_080BF6F4: @ jump table
	.4byte _080BF71C @ case 0
	.4byte _080BF75E @ case 1
	.4byte _080BF78C @ case 2
	.4byte _080BF79E @ case 3
	.4byte _080BF7B0 @ case 4
	.4byte _080BF7BA @ case 5
	.4byte _080BF7D8 @ case 6
	.4byte _080BF7EE @ case 7
	.4byte _080BF83A @ case 8
	.4byte _080BF844 @ case 9
_080BF71C:
	movs r0, #0x80
	bl PlaySound
	movs r0, #0x46
	bl RemovePaletteAnimation
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x47
	bl StartPaletteAnimation
	ldr r1, [r4, #0x54]
	ldr r0, _080BF788 @ =0xFFFFF600
	adds r1, r1, r0
	ldrb r2, [r4, #0x12]
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #0xa
	adds r1, r1, r0
	str r1, [r4, #0x54]
	movs r0, #6
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF75E:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BF770
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF770:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080BF82C
	ldrb r0, [r4, #0x13]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _080BF82C
	adds r0, r4, #0
	bl FUN_080bf390
	b _080BF82C
	.align 2, 0
_080BF788: .4byte 0xFFFFF600
_080BF78C:
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #7
	subs r0, #0x40
	str r0, [r4, #0x5c]
	movs r0, #0x30
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF79E:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080BF812
	ldrb r0, [r4, #0x13]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _080BF812
	b _080BF80C
_080BF7B0:
	movs r0, #0x50
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF7BA:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080BF7D0
	ldrb r0, [r4, #0x13]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _080BF7D0
	adds r0, r4, #0
	bl FUN_080bf390
_080BF7D0:
	ldr r0, [r4, #0x58]
	subs r0, #0xc0
	str r0, [r4, #0x58]
	b _080BF81A
_080BF7D8:
	movs r1, #0x75
	ldrb r2, [r4, #0x12]
	movs r0, #0xea
	muls r0, r2, r0
	subs r1, r1, r0
	str r1, [r4, #0x5c]
	movs r0, #0x30
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF7EE:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080BF812
	ldrb r0, [r4, #0x13]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _080BF812
	ldr r0, [r4, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	ble _080BF812
_080BF80C:
	adds r0, r4, #0
	bl FUN_080bf390
_080BF812:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_080BF81A:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BF82C
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF82C:
	movs r0, #0x47
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080BF886
_080BF83A:
	movs r0, #0x50
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BF844:
	movs r0, #0x47
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	subs r0, #0xc0
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BF886
	movs r0, #0x47
	bl RemovePaletteAnimation
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080BF88C @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080BF886:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BF88C: .4byte gVFXFnTable
