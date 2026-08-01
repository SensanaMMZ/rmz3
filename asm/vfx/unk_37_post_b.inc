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
