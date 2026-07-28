	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c12b0
FUN_080c12b0: @ 0x080C12B0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldr r1, _080C12D8 @ =0x00006101
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080C12DC
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080C12E2
	.align 2, 0
_080C12D8: .4byte 0x00006101
_080C12DC:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080C12E2:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r2, r5, #0
	adds r2, #0x49
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [r5, #0x54]
	str r1, [r5, #0x58]
	movs r1, #0xc0
	lsls r1, r1, #2
	movs r0, #0x61
	bl StartPaletteAnimation
	strb r4, [r5, #0x12]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080c1328
FUN_080c1328: @ 0x080C1328
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _080C137E
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080C13BE
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r1, #0xa0
	lsls r1, r1, #2
	movs r0, #0x65
	bl StartPaletteAnimation
	movs r1, #0xc0
	lsls r1, r1, #2
	movs r0, #0x60
	bl StartPaletteAnimation
	movs r0, #0x65
	bl StepPaletteAnimation
	movs r0, #0x60
	bl StepPaletteAnimation
	movs r0, #0x8d
	lsls r0, r0, #1
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080C13BE
_080C137E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0x65
	bl StepPaletteAnimation
	movs r0, #0x60
	bl StepPaletteAnimation
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080C13BE
	movs r0, #0x65
	bl RemovePaletteAnimation
	movs r0, #0x60
	bl RemovePaletteAnimation
	ldr r1, _080C13C4 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl VFX55_Die
_080C13BE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C13C4: .4byte gVFXFnTable

