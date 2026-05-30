	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b155c
FUN_080b155c: @ 0x080B155C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _080B156C
	cmp r6, #1
	beq _080B15E2
	b _080B1656
_080B156C:
	ldrb r1, [r5, #0xa]
	movs r0, #4
	movs r7, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080B15A8 @ =0x0836D74C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldr r1, _080B15AC @ =0x0000DB0D
	adds r0, r5, #0
	bl SetMotion
	ldrb r2, [r5, #0x12]
	cmp r2, #0
	beq _080B15B0
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080B15B6
	.align 2, 0
_080B15A8: .4byte 0x0836D74C
_080B15AC: .4byte 0x0000DB0D
_080B15B0:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080B15B6:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r5, #0
	adds r0, #0x4c
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
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	movs r0, #0x55
	strb r0, [r5, #0x13]
	movs r0, #6
	strb r0, [r5, #0x12]
_080B15E2:
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B1610
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080B160C @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080B1656
	.align 2, 0
_080B160C: .4byte gProjectileFnTable
_080B1610:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080B164C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	beq _080B1650
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	bne _080B1650
	ldr r1, _080B1648 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080B1650
	.align 2, 0
_080B1648: .4byte gProjectileFnTable
_080B164C:
	subs r0, #1
	strb r0, [r5, #0x12]
_080B1650:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080B1656:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
  .align 2, 0
