	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierleHammerPunch2
glacierleHammerPunch2: @ 0x08058554
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _080585E8
	cmp r0, #1
	bgt _08058568
	cmp r0, #0
	beq _08058576
	b _08058738
_08058568:
	cmp r0, #2
	bne _0805856E
	b _08058700
_0805856E:
	cmp r0, #3
	bne _08058574
	b _0805870A
_08058574:
	b _08058738
_08058576:
	movs r0, #0x8e
	bl PlaySound
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08058660 @ =0x0836499C
	bl SetDDP
	adds r2, r5, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	adds r0, r5, #0
	bl createGlacierleAtkHand
	adds r7, r0, #0
	adds r1, r5, #0
	bl createGlacierleJoint
	str r0, [r5, #0x28]
	str r7, [r5, #0x2c]
	ldr r3, [r5, #0x54]
	ldr r1, _08058664 @ =0xFFFFD100
	adds r0, r3, r1
	str r0, [r7, #0x54]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r4, #0x10
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _080585C2
	movs r0, #0xbc
	lsls r0, r0, #6
	adds r2, r3, r0
_080585C2:
	str r2, [r7, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, _08058668 @ =0xFFFFD700
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, _0805866C @ =0xFFFFFD00
	str r0, [r5, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _080585E0
	movs r2, #0xc0
	lsls r2, r2, #2
_080585E0:
	str r2, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080585E8:
	ldr r7, [r5, #0x2c]
	ldr r0, [r7, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	ldr r0, _08058670 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r1, _08058674 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bne _08058618
	adds r0, r7, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _08058618
	movs r0, #0x52
	bl PlaySound
_08058618:
	ldr r2, [r7, #0x54]
	ldr r0, [r5, #0x54]
	subs r0, r2, r0
	movs r1, #0x80
	lsls r1, r1, #8
	adds r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #9
	cmp r0, r1
	bhi _080586B8
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08058680
	ldr r0, _08058678 @ =0xFFFFE600
	adds r1, r2, r0
	adds r3, r5, #0
	adds r3, #0xbc
	ldr r0, [r3]
	ldr r2, _0805867C @ =0xFFFF5400
	adds r0, r0, r2
	cmp r1, r0
	bge _080586BE
	adds r2, r5, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	orrs r0, r1
	str r0, [r2]
	adds r1, r5, #0
	adds r1, #0xc4
	ldr r0, [r3]
	ldr r2, _0805867C @ =0xFFFF5400
	b _080586AC
	.align 2, 0
_08058660: .4byte 0x0836499C
_08058664: .4byte 0xFFFFD100
_08058668: .4byte 0xFFFFD700
_0805866C: .4byte 0xFFFFFD00
_08058670: .4byte pZero2
_08058674: .4byte 0x00FFFF00
_08058678: .4byte 0xFFFFE600
_0805867C: .4byte 0xFFFF5400
_08058680:
	movs r0, #0xd0
	lsls r0, r0, #5
	adds r1, r2, r0
	adds r3, r5, #0
	adds r3, #0xbc
	ldr r0, [r3]
	movs r2, #0xac
	lsls r2, r2, #8
	adds r0, r0, r2
	cmp r1, r0
	ble _080586BE
	adds r2, r5, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	orrs r0, r1
	str r0, [r2]
	adds r1, r5, #0
	adds r1, #0xc4
	ldr r0, [r3]
	movs r2, #0xac
	lsls r2, r2, #8
_080586AC:
	adds r0, r0, r2
	str r0, [r1]
	subs r1, #0x70
	movs r0, #3
	bl AppendQuake
_080586B8:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080586BE:
	ldr r6, [r5, #0x54]
	ldr r0, _080586F8 @ =0xFFFFE900
	adds r6, r6, r0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080586D4
	movs r1, #0xb8
	lsls r1, r1, #6
	adds r6, r6, r1
_080586D4:
	ldr r4, [r5, #0x58]
	ldr r2, _080586FC @ =0xFFFFD700
	adds r4, r4, r2
	adds r0, r7, #0
	adds r1, r5, #0
	adds r2, r6, #0
	adds r3, r4, #0
	bl FUN_080823a4
	adds r0, r7, #0
	adds r1, r6, #0
	adds r2, r4, #0
	bl FUN_08082484
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08058738
	.align 2, 0
_080586F8: .4byte 0xFFFFE900
_080586FC: .4byte 0xFFFFD700
_08058700:
	movs r0, #0x20
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805870A:
	ldrb r0, [r5, #0x12]
	cmp r0, #0x10
	bne _0805871E
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #3
	rsbs r2, r2, #0
	ands r1, r2
	str r1, [r0]
_0805871E:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08058732
	movs r0, #0xa
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08058732:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08058738:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
