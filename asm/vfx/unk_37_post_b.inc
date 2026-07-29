	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080bcd9c
FUN_080bcd9c: @ 0x080BCD9C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080BCDAC
	cmp r0, #1
	beq _080BCDE0
	b _080BCE3C
_080BCDAC:
	ldr r1, _080BCE00 @ =0x0000330C
	adds r0, r4, #0
	bl SetMotion
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x1a
	bl StartPaletteAnimation
	movs r0, #0xc
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCDE0:
	movs r0, #0x1a
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080BCE04
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080BCE0A
	.align 2, 0
_080BCE00: .4byte 0x0000330C
_080BCE04:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BCE0A:
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BCE3C
	movs r0, #0x1a
	bl RemovePaletteAnimation
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080BCE44 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080BCE3C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BCE44: .4byte gVFXFnTable

	thumb_func_start FUN_080bce48
FUN_080bce48: @ 0x080BCE48
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _080BCEA6
	cmp r0, #1
	bgt _080BCE5C
	cmp r0, #0
	beq _080BCE66
	b _080BCF5E
_080BCE5C:
	cmp r0, #2
	beq _080BCEE0
	cmp r0, #3
	beq _080BCEEA
	b _080BCF5E
_080BCE66:
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	ldrb r0, [r5, #0x12]
	subs r1, #3
	strb r0, [r1]
	ldr r4, _080BCED0 @ =0x0836EE0A
	ldr r2, _080BCED4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BCED8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BCEDC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #1
	adds r0, r0, r4
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x12
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080BCEA6:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BCEB8
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080BCEB8:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080BCF5E
	.align 2, 0
_080BCED0: .4byte 0x0836EE0A
_080BCED4: .4byte RNG_0202f388
_080BCED8: .4byte 0x000343FD
_080BCEDC: .4byte 0x00269EC3
_080BCEE0:
	movs r0, #0x10
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080BCEEA:
	ldrb r0, [r5, #0x12]
	adds r4, r0, #0
	cmp r4, #8
	bls _080BCF02
	movs r0, #1
	ands r0, r4
	cmp r0, #0
	beq _080BCF18
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080BCF1E
_080BCF02:
	ldrb r0, [r5, #0x12]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BCF18
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080BCF1E
_080BCF18:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BCF1E:
	strb r0, [r5, #0xa]
	subs r0, r4, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BCF48
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080BCF64 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_080BCF48:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080BCF5E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BCF64: .4byte gVFXFnTable
