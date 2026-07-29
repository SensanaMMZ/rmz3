	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ccca4
FUN_080ccca4: @ 0x080CCCA4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080CCCEC
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080CCCE8 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _080CCDDE
	.align 2, 0
_080CCCE8: .4byte gSolidFnTable
_080CCCEC:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080CCCF8
	cmp r0, #1
	beq _080CCD46
	b _080CCDDE
_080CCCF8:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x1d
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r1, #0xd8
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #4
	subs r1, r1, r0
	strb r1, [r4, #0x12]
	ldrb r1, [r4, #0x11]
	cmp r1, #0
	bne _080CCD20
	ldr r1, _080CCD1C @ =0x00003901
	b _080CCD2A
	.align 2, 0
_080CCD1C: .4byte 0x00003901
_080CCD20:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080CCD38
	ldr r1, _080CCD34 @ =0x00003902
_080CCD2A:
	adds r0, r4, #0
	bl SetMotion
	b _080CCD40
	.align 2, 0
_080CCD34: .4byte 0x00003902
_080CCD38:
	ldr r1, _080CCD78 @ =0x00003903
	adds r0, r4, #0
	bl SetMotion
_080CCD40:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CCD46:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080CCD56
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080CCD5E
_080CCD56:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
_080CCD5E:
	ldrb r0, [r4, #0x12]
	adds r2, r0, #0
	cmp r2, #0xf
	bhi _080CCD84
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	beq _080CCD7C
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080CCD82
	.align 2, 0
_080CCD78: .4byte 0x00003903
_080CCD7C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080CCD82:
	strb r0, [r4, #0xa]
_080CCD84:
	subs r0, r2, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _080CCDD8
	movs r0, #0x3f
	bl PlaySound
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r1, r1, r2
	bl CreateVFX43
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080CCDE4 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080CCDD8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CCDDE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CCDE4: .4byte gSolidFnTable
