	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b0214
FUN_080b0214: @ 0x080B0214
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bhi _080B02BE
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _080B0268
	cmp r5, #1
	bgt _080B0230
	cmp r5, #0
	beq _080B0236
	b _080B02D0
_080B0230:
	cmp r5, #2
	beq _080B0282
	b _080B02D0
_080B0236:
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r1, [r4, #0xa]
	movs r0, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x11
	strb r0, [r1]
	strb r5, [r4, #0x12]
	movs r1, #0xb9
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B0268:
	ldr r1, [r4, #0x28]
	ldr r0, [r1, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x58]
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xd]
	cmp r0, #5
	beq _080B02D0
	b _080B02B6
_080B0282:
	ldr r0, [r1, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x58]
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0x12]
	adds r0, r1, #0
	adds r0, #0xff
	strb r0, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080B02A8
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080B02AE
_080B02A8:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080B02AE:
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080B02D0
_080B02B6:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
_080B02BE:
	ldr r1, _080B02D8 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B02D0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B02D8: .4byte gProjectileFnTable

