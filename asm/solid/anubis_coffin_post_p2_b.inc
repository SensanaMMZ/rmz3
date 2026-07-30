	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start coffin_080ce204
coffin_080ce204: @ 0x080CE204
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080CE214
	cmp r5, #1
	beq _080CE23E
	b _080CE2D4
_080CE214:
	movs r0, #0x47
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
	movs r0, #0x46
	bl StartPaletteAnimation
	strb r5, [r4, #0x13]
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CE23E:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	movs r6, #0
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r5, r4, #0
	adds r5, #0xb4
	cmp r0, #4
	bne _080CE25C
	ldr r0, [r4, #0x54]
	ldr r1, [r5]
	movs r2, #0
	bl FUN_080bf438
_080CE25C:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080CE26C
	str r1, [r4, #0x60]
_080CE26C:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r5]
	movs r2, #0x80
	lsls r2, r2, #6
	adds r0, r0, r2
	cmp r1, r0
	ble _080CE2C8
	ldrb r1, [r4, #0xb]
	movs r0, #0xf7
	ands r0, r1
	strb r0, [r4, #0xb]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r6, [r0]
	adds r0, #4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080CE2C4 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	movs r0, #0x46
	bl RemovePaletteAnimation
	b _080CE2E0
	.align 2, 0
_080CE2C4: .4byte gSolidFnTable
_080CE2C8:
	movs r0, #0x46
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CE2D4:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080CE2E0
	adds r0, r4, #0
	bl FUN_080cdd64
_080CE2E0:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
