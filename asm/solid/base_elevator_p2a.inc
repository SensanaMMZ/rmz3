	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080d0024
FUN_080d0024: @ 0x080D0024
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	adds r0, r5, #0
	adds r0, #0xbd
	ldrb r2, [r0]
	cmp r2, #0
	beq _080D00A8
	ldrb r0, [r4, #0xd]
	ldrb r1, [r5, #0xd]
	cmp r0, r1
	beq _080D009E
	cmp r1, #0
	beq _080D006E
	cmp r2, #1
	bne _080D004C
	ldr r1, _080D0048 @ =0x00008902
	b _080D0076
	.align 2, 0
_080D0048: .4byte 0x00008902
_080D004C:
	ldrb r0, [r4, #0x12]
	bl RemovePaletteAnimation
	movs r0, #0xbc
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xc2
	ldrb r1, [r0]
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xbc
	bl StartPaletteAnimation
	b _080D009E
_080D006E:
	cmp r2, #1
	bne _080D007E
	movs r1, #0x89
	lsls r1, r1, #8
_080D0076:
	adds r0, r4, #0
	bl SetMotion
	b _080D009E
_080D007E:
	ldrb r0, [r4, #0x12]
	bl RemovePaletteAnimation
	movs r0, #0xbb
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xc2
	ldrb r1, [r0]
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xbb
	bl StartPaletteAnimation
_080D009E:
	ldrb r0, [r5, #0xd]
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080D00A8:
	ldrb r0, [r4, #0x12]
	bl StepPaletteAnimation
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _080D00D8
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080D00C6
	bl RemovePaletteAnimation
_080D00C6:
	ldr r1, _080D00E0 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080D00D8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080D00E0: .4byte gSolidFnTable

