	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b0168
FUN_080b0168: @ 0x080B0168
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B019C
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080B0198 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080B0206
	.align 2, 0
_080B0198: .4byte gProjectileFnTable
_080B019C:
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _080B01A8
	cmp r6, #1
	beq _080B01F8
	b _080B0206
_080B01A8:
	adds r0, r5, #0
	bl InitNonAffineMotion
	adds r0, r5, #0
	bl ResetDynamicMotion
	ldrb r0, [r5, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #0
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080B020C @ =0x0836D624
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #2
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	movs r1, #0xb8
	lsls r1, r1, #8
	adds r0, r5, #0
	bl SetMotion
	str r6, [r5, #0x60]
	ldr r0, _080B0210 @ =0xFFFFFB00
	str r0, [r5, #0x5c]
	movs r0, #0x78
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080B01F8:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080B0206:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B020C: .4byte 0x0836D624
_080B0210: .4byte 0xFFFFFB00

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

