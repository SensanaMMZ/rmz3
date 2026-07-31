	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyx_08057590
copyx_08057590: @ 0x08057590
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08057628
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080575C0
	movs r4, #0
	strb r4, [r5, #0xe]
	movs r1, #0xa0
	lsls r1, r1, #2
	movs r0, #0x63
	bl StartPaletteAnimation
	movs r0, #0x39
	bl PlaySound
	movs r0, #0xff
	strb r0, [r5, #0x12]
	strb r4, [r5, #0x13]
_080575C0:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	movs r0, #0x63
	bl StepPaletteAnimation
	ldrb r0, [r5, #0x12]
	movs r1, #7
	ands r1, r0
	cmp r1, #3
	bne _080575E8
	ldrb r2, [r5, #0x13]
	adds r0, r5, #0
	movs r1, #2
	bl CreateVFX56
	ldrb r0, [r5, #0x13]
	adds r0, #0xc
	strb r0, [r5, #0x13]
	b _0805760E
_080575E8:
	cmp r1, #7
	bne _0805760E
	ldr r3, _08057630 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _08057634 @ =0x000343FD
	adds r2, r1, #0
	muls r2, r0, r2
	ldr r0, _08057638 @ =0x00269EC3
	adds r2, r2, r0
	lsls r2, r2, #1
	lsrs r0, r2, #1
	str r0, [r3]
	lsrs r2, r2, #0x11
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	adds r0, r5, #0
	movs r1, #2
	bl CreateVFX56
_0805760E:
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r4, #4
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _08057628
	movs r0, #0x63
	bl RemovePaletteAnimation
	movs r0, #0
	strb r4, [r5, #0xd]
	strb r0, [r5, #0xe]
_08057628:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08057630: .4byte RNG_0202f388
_08057634: .4byte 0x000343FD
_08057638: .4byte 0x00269EC3
