	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierle_080583c4
glacierle_080583c4: @ 0x080583C4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08058416
	cmp r0, #1
	bgt _080583D8
	cmp r0, #0
	beq _080583E2
	b _0805848E
_080583D8:
	cmp r0, #2
	beq _0805845C
	cmp r0, #3
	beq _08058478
	b _0805848E
_080583E2:
	movs r0, #0x91
	bl PlaySound
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	orrs r0, r1
	str r0, [r2]
	adds r1, r4, #0
	adds r1, #0xc4
	ldr r0, [r4, #0x54]
	str r0, [r1]
	subs r1, #0x70
	movs r0, #3
	bl AppendQuake
	movs r0, #0x12
	strb r0, [r4, #0x12]
	ldr r1, _08058450 @ =0x0000B208
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058416:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058454 @ =0x08364ABF
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058458 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805848E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _0805848C
	.align 2, 0
_08058450: .4byte 0x0000B208
_08058454: .4byte 0x08364ABF
_08058458: .4byte sCollisions
_0805845C:
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #3
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	ldr r1, _08058494 @ =0x0000B209
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058478:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805848E
	movs r0, #0
	strb r0, [r4, #0xd]
_0805848C:
	strb r0, [r4, #0xe]
_0805848E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08058494: .4byte 0x0000B209

	thumb_func_start glacierleHammerPunch1
glacierleHammerPunch1: @ 0x08058498
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080584C8
	cmp r0, #1
	bgt _080584AC
	cmp r0, #0
	beq _080584B6
	b _08058544
_080584AC:
	cmp r0, #2
	beq _08058510
	cmp r0, #3
	beq _08058528
	b _08058544
_080584B6:
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldr r1, _08058504 @ =0x0000B212
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080584C8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058508 @ =0x08364AC2
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0805850C @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08058544
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08058544
	.align 2, 0
_08058504: .4byte 0x0000B212
_08058508: .4byte 0x08364AC2
_0805850C: .4byte sCollisions
_08058510:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805854C @ =0x08364954
	bl SetDDP
	ldr r1, _08058550 @ =0x0000B213
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058528:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bne _08058544
	movs r1, #0
	movs r0, #9
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08058544:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805854C: .4byte 0x08364954
_08058550: .4byte 0x0000B213

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

	thumb_func_start glacierleHammerPunch3
glacierleHammerPunch3: @ 0x08058740
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r1, [r5, #0xe]
	cmp r1, #1
	beq _0805878A
	cmp r1, #1
	bgt _08058754
	cmp r1, #0
	beq _08058762
	b _08058902
_08058754:
	cmp r1, #2
	bne _0805875A
	b _08058878
_0805875A:
	cmp r1, #3
	bne _08058760
	b _080588EC
_08058760:
	b _08058902
_08058762:
	movs r0, #1
	strb r0, [r5, #0x12]
	ldr r4, [r5, #0x2c]
	adds r0, r4, #0
	adds r0, #0xb5
	strb r1, [r0]
	adds r0, r4, #0
	bl FUN_080823ec
	movs r1, #0xc0
	lsls r1, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x64]
	ldr r1, _08058808 @ =0x0000B214
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805878A:
	ldrb r1, [r5, #0x12]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	bne _080587A0
	movs r0, #0x8f
	bl PlaySound
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
_080587A0:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r6, [r5, #0x28]
	ldr r1, [r5, #0x54]
	str r1, [r6, #0x54]
	ldr r4, _0805880C @ =0x08364AC6
	adds r2, r5, #0
	adds r2, #0x71
	movs r0, #0
	ldrsb r0, [r2, r0]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r3, #0
	ldrsh r0, [r0, r3]
	adds r1, r1, r0
	str r1, [r6, #0x54]
	adds r3, r1, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	adds r7, r2, #0
	cmp r0, #0
	beq _080587E0
	movs r0, #0
	ldrsb r0, [r7, r0]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #1
	subs r3, r3, r0
_080587E0:
	str r3, [r6, #0x54]
	ldr r2, [r5, #0x58]
	str r2, [r6, #0x58]
	movs r0, #0
	ldrsb r0, [r7, r0]
	lsls r0, r0, #2
	adds r1, r4, #2
	adds r0, r0, r1
	movs r3, #0
	ldrsh r0, [r0, r3]
	adds r2, r2, r0
	str r2, [r6, #0x58]
	ldr r4, [r5, #0x2c]
	ldr r0, [r4, #0x64]
	cmp r0, #0
	blt _08058810
	subs r0, #0x20
	str r0, [r4, #0x64]
	b _08058816
	.align 2, 0
_08058808: .4byte 0x0000B214
_0805880C: .4byte 0x08364AC6
_08058810:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08058816:
	adds r0, r4, #0
	movs r1, #1
	bl glacierle_08082598
	ldrb r1, [r5, #0x12]
	adds r0, r0, r1
	strb r0, [r5, #0x12]
	ldr r1, [r5, #0x54]
	str r1, [r6, #0x54]
	ldr r4, _08058874 @ =0x08364AC6
	adds r3, r7, #0
	movs r0, #0
	ldrsb r0, [r3, r0]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r2, #0
	ldrsh r0, [r0, r2]
	adds r1, r1, r0
	str r1, [r6, #0x54]
	adds r2, r1, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08058858
	movs r0, #0
	ldrsb r0, [r3, r0]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r3, #0
	ldrsh r0, [r0, r3]
	lsls r0, r0, #1
	subs r2, r2, r0
_08058858:
	str r2, [r6, #0x54]
	ldr r2, [r5, #0x58]
	str r2, [r6, #0x58]
	movs r0, #0
	ldrsb r0, [r7, r0]
	lsls r0, r0, #2
	adds r1, r4, #2
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	adds r2, r2, r0
	str r2, [r6, #0x58]
	b _08058902
	.align 2, 0
_08058874: .4byte 0x08364AC6
_08058878:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08058908 @ =0x083649CC
	bl SetDDP
	ldr r4, [r5, #0x2c]
	adds r1, r4, #0
	adds r1, #0xb4
	ldrb r0, [r1]
	adds r7, r5, #0
	adds r7, #0xb4
	cmp r0, #0
	beq _080588A0
	adds r6, r1, #0
_08058894:
	adds r0, r4, #0
	bl FUN_08082348
	ldrb r0, [r6]
	cmp r0, #0
	bne _08058894
_080588A0:
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
	ldr r1, _0805890C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	ldr r0, [r7]
	movs r1, #1
	orrs r0, r1
	str r0, [r7]
	ldr r1, _08058910 @ =0x0000B215
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080588EC:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08058902
	movs r0, #0
	strb r0, [r5, #0xd]
	strb r0, [r5, #0xe]
_08058902:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08058908: .4byte 0x083649CC
_0805890C: .4byte gEnemyFnTable
_08058910: .4byte 0x0000B215

	thumb_func_start glacierleIceRainJump
glacierleIceRainJump: @ 0x08058914
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08058946
	cmp r0, #1
	bgt _08058928
	cmp r0, #0
	beq _08058932
	b _080589C8
_08058928:
	cmp r0, #2
	beq _0805898C
	cmp r0, #3
	beq _080589A0
	b _080589C8
_08058932:
	movs r0, #0x90
	bl PlaySound
	ldr r1, _08058980 @ =0x0000B20A
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058946:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058984 @ =0x08364ACE
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058988 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080589C8
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080589C8
	.align 2, 0
_08058980: .4byte 0x0000B20A
_08058984: .4byte 0x08364ACE
_08058988: .4byte sCollisions
_0805898C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_0800a134
	str r0, [r4, #0x68]
	ldr r0, _080589D0 @ =0xFFFFFB80
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080589A0:
	ldr r0, [r4, #0x60]
	adds r0, #0x20
	str r0, [r4, #0x60]
	ldr r1, [r4, #0x58]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x68]
	movs r2, #0xba
	lsls r2, r2, #7
	adds r0, r0, r2
	cmp r1, r0
	bge _080589C2
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #0xc
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080589C2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080589C8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080589D0: .4byte 0xFFFFFB80

	thumb_func_start glacierleIceRain1
glacierleIceRain1: @ 0x080589D4
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _080589E0
	b _08058BC4
_080589E0:
	lsls r0, r0, #2
	ldr r1, _080589EC @ =_080589F0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080589EC: .4byte _080589F0
_080589F0: @ jump table
	.4byte _08058A08 @ case 0
	.4byte _08058A1C @ case 1
	.4byte _08058A68 @ case 2
	.4byte _08058B1C @ case 3
	.4byte _08058B84 @ case 4
	.4byte _08058B98 @ case 5
_08058A08:
	movs r0, #0x93
	bl PlaySound
	ldr r1, _08058A58 @ =0x0000B20B
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058A1C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058A5C @ =0x08364AD3
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058A60 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldr r0, [r4, #0x70]
	ldr r1, _08058A64 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x81
	lsls r1, r1, #9
	cmp r0, r1
	beq _08058A54
	b _08058BC4
_08058A54:
	b _08058B62
	.align 2, 0
_08058A58: .4byte 0x0000B20B
_08058A5C: .4byte 0x08364AD3
_08058A60: .4byte sCollisions
_08058A64: .4byte 0x00FFFF00
_08058A68:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #2
	rsbs r2, r2, #0
	ands r1, r2
	str r1, [r0]
	adds r0, r4, #0
	bl createGlacierleAtkHand
	adds r5, r0, #0
	str r5, [r4, #0x2c]
	cmp r5, #0
	beq _08058B16
	adds r1, r4, #0
	bl createGlacierleJoint
	adds r6, r0, #0
	adds r0, r5, #0
	adds r1, r4, #0
	bl createGlacierleJoint
	adds r0, r5, #0
	adds r1, r4, #0
	bl createGlacierleJoint
	adds r0, r5, #0
	adds r1, r4, #0
	bl createGlacierleJoint
	cmp r6, #0
	beq _08058AD8
	adds r0, r6, #0
	adds r1, r4, #0
	bl createGlacierleSucker
	adds r2, r0, #0
	str r2, [r4, #0x28]
	ldr r6, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r6, r1
	str r0, [r2, #0x54]
	adds r3, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08058ACE
	ldr r0, _08058B6C @ =0xFFFFF600
	adds r3, r6, r0
_08058ACE:
	str r3, [r2, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _08058B70 @ =0xFFFFD300
	adds r0, r0, r1
	str r0, [r2, #0x58]
_08058AD8:
	ldr r2, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r2, r1
	str r0, [r5, #0x54]
	adds r3, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08058AF2
	ldr r0, _08058B6C @ =0xFFFFF600
	adds r3, r2, r0
_08058AF2:
	str r3, [r5, #0x54]
	ldr r2, [r4, #0x58]
	ldr r1, _08058B74 @ =0xFFFFFE00
	adds r0, r2, r1
	str r0, [r5, #0x58]
	ldr r0, _08058B78 @ =0xFFFFE200
	adds r2, r2, r0
	adds r0, r5, #0
	adds r1, r3, #0
	bl FUN_08082484
	adds r1, r5, #0
	adds r1, #0xb5
	movs r0, #0
	strb r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #3
	str r0, [r5, #0x64]
_08058B16:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058B1C:
	ldr r2, [r4, #0x28]
	adds r0, r2, #0
	movs r1, #0x40
	bl FUN_0808288c
	ldr r5, [r4, #0x2c]
	adds r0, r5, #0
	movs r1, #0
	bl glacierle_08082598
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058B7C @ =0x08364AD3
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058B80 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08058BC4
_08058B62:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08058BC4
	.align 2, 0
_08058B6C: .4byte 0xFFFFF600
_08058B70: .4byte 0xFFFFD300
_08058B74: .4byte 0xFFFFFE00
_08058B78: .4byte 0xFFFFE200
_08058B7C: .4byte 0x08364AD3
_08058B80: .4byte sCollisions
_08058B84:
	movs r0, #0x92
	bl PlaySound
	ldr r1, _08058BCC @ =0x0000B20C
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058B98:
	ldr r2, [r4, #0x28]
	adds r0, r2, #0
	movs r1, #0x40
	bl FUN_0808288c
	ldr r5, [r4, #0x2c]
	adds r0, r5, #0
	movs r1, #0
	bl glacierle_08082598
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08058BC4
	movs r1, #0
	movs r0, #0xd
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08058BC4:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08058BCC: .4byte 0x0000B20C

	thumb_func_start glacierleIceRain2
glacierleIceRain2: @ 0x08058BD0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08058C20
	cmp r0, #1
	bgt _08058BEC
	cmp r0, #0
	beq _08058BF2
	b _08058D32
_08058BEC:
	cmp r0, #2
	beq _08058C78
	b _08058D32
_08058BF2:
	ldr r2, [r4, #0x2c]
	cmp r2, #0
	beq _08058C10
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	movs r1, #0xa0
	lsls r1, r1, #2
	cmp r0, #0
	beq _08058C08
	ldr r1, _08058CC0 @ =0xFFFFFD80
_08058C08:
	adds r0, r2, #0
	movs r2, #0
	bl FUN_0808242c
_08058C10:
	movs r0, #0x20
	str r0, [r4, #0x64]
	movs r0, #0
	str r0, [r4, #0x68]
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058C20:
	ldr r5, [r4, #0x28]
	cmp r5, #0
	beq _08058C5E
	ldr r1, [r4, #0x54]
	str r1, [r5, #0x54]
	ldr r3, _08058CC4 @ =0x08364AF0
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r2, #0
	ldrsh r0, [r0, r2]
	adds r1, r1, r0
	str r1, [r5, #0x54]
	adds r2, r1, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08058C54
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #1
	subs r2, r2, r0
_08058C54:
	str r2, [r5, #0x54]
	ldr r0, [r4, #0x58]
	ldr r2, _08058CC8 @ =0xFFFFD300
	adds r0, r0, r2
	str r0, [r5, #0x58]
_08058C5E:
	movs r0, #0
	strb r0, [r4, #0x13]
	ldr r1, _08058CCC @ =0x08364AD8
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058C78:
	ldr r5, [r4, #0x28]
	ldr r3, _08058CD0 @ =0x08364B00
	ldrb r2, [r4, #0x12]
	adds r0, r2, r3
	ldrb r6, [r0]
	adds r1, r2, #1
	adds r0, r1, #0
	asrs r0, r0, #3
	lsls r0, r0, #3
	subs r0, r1, r0
	adds r0, r0, r3
	ldrb r0, [r0]
	subs r0, r0, r6
	ldrb r1, [r4, #0x13]
	muls r0, r1, r0
	ldr r1, _08058CD4 @ =0x08364AE8
	adds r1, r2, r1
	ldrb r1, [r1]
	bl __divsi3
	adds r6, r6, r0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08058CD8
	movs r0, #0x80
	rsbs r0, r0, #0
	adds r1, r0, #0
	subs r1, r1, r6
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r5, #0
	bl FUN_0808288c
	b _08058CE2
	.align 2, 0
_08058CC0: .4byte 0xFFFFFD80
_08058CC4: .4byte 0x08364AF0
_08058CC8: .4byte 0xFFFFD300
_08058CCC: .4byte 0x08364AD8
_08058CD0: .4byte 0x08364B00
_08058CD4: .4byte 0x08364AE8
_08058CD8:
	lsls r1, r6, #0x18
	lsrs r1, r1, #0x18
	adds r0, r5, #0
	bl FUN_0808288c
_08058CE2:
	ldr r2, [r4, #0x2c]
	adds r0, r2, #0
	movs r1, #0
	bl glacierle_08082598
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	ldr r1, _08058E10 @ =0x08364AE8
	ldrb r2, [r4, #0x12]
	adds r1, r2, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	bne _08058D12
	adds r0, r2, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x12]
	movs r1, #7
	ands r0, r1
	strb r0, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0xe]
_08058D12:
	ldr r0, [r4, #0x68]
	cmp r0, #3
	bne _08058D2C
	ldrb r0, [r4, #0x12]
	cmp r0, #4
	bne _08058D2C
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	bne _08058D2C
	movs r0, #0xe
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_08058D2C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08058D32:
	ldr r0, [r4, #0x64]
	subs r0, #1
	str r0, [r4, #0x64]
	cmp r0, #0
	bne _08058E00
	ldr r0, [r4, #0x68]
	cmp r0, #2
	bgt _08058E00
	movs r0, #0x2d
	bl PlaySound
	movs r0, #0x20
	str r0, [r4, #0x64]
	ldr r2, _08058E14 @ =0x08364B08
	ldr r0, [r4, #0x68]
	lsls r3, r0, #2
	adds r0, r3, r2
	movs r1, #0
	ldrsh r5, [r0, r1]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	mov sl, r0
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	cmp r7, #0
	beq _08058D6A
	rsbs r5, r5, #0
_08058D6A:
	adds r0, r2, #2
	adds r0, r3, r0
	movs r1, #0
	ldrsh r6, [r0, r1]
	ldr r2, _08058E18 @ =0x08364B14
	mov r8, r2
	adds r0, r3, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r4, #0x54]
	adds r2, r0, r1
	cmp r7, #0
	beq _08058D88
	lsls r0, r1, #1
	subs r2, r2, r0
_08058D88:
	movs r0, #2
	add r0, r8
	mov sb, r0
	adds r0, r3, r0
	movs r1, #0
	ldrsh r0, [r0, r1]
	ldr r1, [r4, #0x58]
	adds r1, r1, r0
	adds r0, r2, #0
	adds r2, r5, #0
	adds r3, r6, #0
	bl FUN_080aa5e8
	lsls r0, r5, #1
	adds r0, r0, r5
	lsls r0, r0, #2
	adds r0, r0, r5
	lsls r0, r0, #5
	cmp r0, #0
	bge _08058DB2
	adds r0, #0xff
_08058DB2:
	asrs r5, r0, #8
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #2
	subs r0, r0, r6
	lsls r0, r0, #5
	cmp r0, #0
	bge _08058DC4
	adds r0, #0xff
_08058DC4:
	asrs r6, r0, #8
	ldr r0, [r4, #0x68]
	lsls r7, r0, #2
	mov r2, r8
	adds r0, r7, r2
	movs r1, #0
	ldrsh r3, [r0, r1]
	ldr r0, [r4, #0x54]
	adds r2, r0, r3
	ldrb r1, [r4, #0xa]
	mov r0, sl
	ands r0, r1
	cmp r0, #0
	beq _08058DE4
	lsls r0, r3, #1
	subs r2, r2, r0
_08058DE4:
	mov r1, sb
	adds r0, r7, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	ldr r1, [r4, #0x58]
	adds r1, r1, r0
	adds r0, r2, #0
	adds r2, r5, #0
	adds r3, r6, #0
	bl FUN_080aa5e8
	ldr r0, [r4, #0x68]
	adds r0, #1
	str r0, [r4, #0x68]
_08058E00:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08058E10: .4byte 0x08364AE8
_08058E14: .4byte 0x08364B08
_08058E18: .4byte 0x08364B14

	thumb_func_start glacierleIceRain3
glacierleIceRain3: @ 0x08058E1C
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #5
	bls _08058E2E
	b _08058FDC
_08058E2E:
	lsls r0, r0, #2
	ldr r1, _08058E38 @ =_08058E3C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08058E38: .4byte _08058E3C
_08058E3C: @ jump table
	.4byte _08058E54 @ case 0
	.4byte _08058E62 @ case 1
	.4byte _08058E94 @ case 2
	.4byte _08058F3C @ case 3
	.4byte _08058FA8 @ case 4
	.4byte _08058FC6 @ case 5
_08058E54:
	ldr r1, _08058E90 @ =0x0000B21E
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08058E62:
	ldr r7, [r6, #0x28]
	adds r0, r7, #0
	movs r1, #0x40
	bl FUN_0808288c
	ldr r5, [r6, #0x2c]
	adds r0, r5, #0
	movs r1, #0
	bl glacierle_08082598
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08058E88
	b _08058FDC
_08058E88:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	b _08058FDA
	.align 2, 0
_08058E90: .4byte 0x0000B21E
_08058E94:
	ldr r5, [r6, #0x2c]
	adds r1, r5, #0
	adds r1, #0xb4
	ldrb r0, [r1]
	movs r2, #0xb4
	adds r2, r2, r6
	mov sb, r2
	cmp r0, #0
	beq _08058EB4
	adds r4, r1, #0
_08058EA8:
	adds r0, r5, #0
	bl FUN_08082348
	ldrb r0, [r4]
	cmp r0, #0
	bne _08058EA8
_08058EB4:
	ldr r7, [r6, #0x28]
	ldrb r2, [r7, #0xa]
	movs r1, #0xfe
	adds r0, r1, #0
	ands r0, r2
	movs r4, #0
	movs r2, #0xfd
	mov ip, r2
	ands r0, r2
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r2, [r7, #0xa]
	movs r3, #0xfb
	adds r0, r3, #0
	ands r0, r2
	strb r0, [r7, #0xa]
	ldr r0, _08058F98 @ =gEnemyFnTable
	mov r8, r0
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	add r0, r8
	movs r2, #3
	str r2, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
	ldrb r0, [r5, #0xa]
	ands r1, r0
	mov r0, ip
	ands r1, r0
	strb r1, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r0, [r5, #0xa]
	ands r3, r0
	strb r3, [r5, #0xa]
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	add r0, r8
	str r2, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	mov r1, sb
	ldr r0, [r1]
	movs r1, #1
	orrs r0, r1
	mov r2, sb
	str r0, [r2]
	str r4, [r6, #0x60]
	ldr r1, _08058F9C @ =0x0000B211
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08058F3C:
	ldr r0, [r6, #0x60]
	adds r0, #0x40
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08058F4C
	str r1, [r6, #0x60]
_08058F4C:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x74
	ldr r2, _08058FA0 @ =0x08364B20
	adds r1, r6, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058FA4 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08058FDC
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	b _08058FDA
	.align 2, 0
_08058F98: .4byte gEnemyFnTable
_08058F9C: .4byte 0x0000B211
_08058FA0: .4byte 0x08364B20
_08058FA4: .4byte sCollisions
_08058FA8:
	movs r0, #0x91
	bl PlaySound
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08058FE8 @ =0x08363DE4
	bl SetDDP
	ldr r1, _08058FEC @ =0x0000B209
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08058FC6:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08058FDC
	movs r0, #0
	strb r0, [r6, #0xd]
_08058FDA:
	strb r0, [r6, #0xe]
_08058FDC:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08058FE8: .4byte 0x08363DE4
_08058FEC: .4byte 0x0000B209

	thumb_func_start glacierleIceCarnival1
glacierleIceCarnival1: @ 0x08058FF0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08059000
	cmp r5, #1
	beq _08059040
	b _0805907A
_08059000:
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r4, #0x54]
	ldr r1, [r1]
	subs r0, r0, r1
	movs r1, #0xf0
	lsls r1, r1, #6
	adds r0, r0, r1
	movs r1, #0xf0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0805902C
	adds r0, r4, #0
	bl UpdateMotionGraphic
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
	adds r1, r4, #0
	adds r1, #0xc1
	movs r0, #0xa
	strb r0, [r1]
	b _0805907A
_0805902C:
	movs r0, #0x95
	bl PlaySound
	ldr r1, _08059080 @ =0x0000B216
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08059040:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08059058
	movs r1, #0
	movs r0, #0x10
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08059058:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08059084 @ =0x08364B22
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08059088 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
_0805907A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08059080: .4byte 0x0000B216
_08059084: .4byte 0x08364B22
_08059088: .4byte sCollisions

	thumb_func_start glacierleIceCarnival2
glacierleIceCarnival2: @ 0x0805908C
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldrb r4, [r6, #0xe]
	cmp r4, #1
	bne _08059098
	b _080591B0
_08059098:
	cmp r4, #1
	bgt _080590A2
	cmp r4, #0
	beq _080590B0
	b _080593BC
_080590A2:
	cmp r4, #2
	bne _080590A8
	b _08059314
_080590A8:
	cmp r4, #3
	bne _080590AE
	b _08059324
_080590AE:
	b _080593BC
_080590B0:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08059238 @ =0x08363F04
	bl SetDDP
	strb r4, [r6, #0x12]
	adds r2, r6, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	adds r0, r6, #0
	bl createGlacierleAtkHand
	adds r7, r0, #0
	str r7, [r6, #0x2c]
	cmp r7, #0
	beq _0805919A
	adds r1, r6, #0
	bl createGlacierleJoint
	adds r4, r0, #0
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	cmp r4, #0
	beq _0805912C
	adds r0, r4, #0
	adds r1, r6, #0
	bl createGlacierleSucker
	adds r4, r0, #0
	str r4, [r6, #0x28]
	ldr r3, [r6, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r3, r1
	str r0, [r4, #0x54]
	adds r2, r0, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08059122
	ldr r0, _0805923C @ =0xFFFFF600
	adds r2, r3, r0
_08059122:
	str r2, [r4, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, _08059240 @ =0xFFFFDB00
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0805912C:
	ldr r3, [r6, #0x54]
	movs r2, #0xb0
	lsls r2, r2, #6
	adds r0, r3, r2
	str r0, [r7, #0x54]
	adds r2, r0, #0
	ldrb r1, [r6, #0xa]
	movs r4, #0x10
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _08059148
	ldr r0, _08059244 @ =0xFFFFD400
	adds r2, r3, r0
_08059148:
	str r2, [r7, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, _08059248 @ =0xFFFFC900
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r2, [r6, #0x54]
	movs r0, #0x88
	lsls r0, r0, #5
	adds r3, r2, r0
	ldrb r1, [r6, #0xa]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _08059168
	ldr r1, _0805924C @ =0xFFFFEF00
	adds r3, r2, r1
_08059168:
	ldr r2, [r6, #0x58]
	ldr r0, _08059244 @ =0xFFFFD400
	adds r2, r2, r0
	adds r0, r7, #0
	adds r1, r3, #0
	bl FUN_08082484
	adds r1, r7, #0
	adds r1, #0xb5
	movs r0, #0
	strb r0, [r1]
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r7, #0x64]
	adds r0, r7, #0
	adds r0, #0x24
	ldrb r0, [r0]
	adds r0, #0x80
	strb r0, [r6, #0x12]
	movs r2, #0x98
	lsls r2, r2, #1
	adds r0, r7, #0
	movs r1, #0
	bl FUN_0808242c
_0805919A:
	movs r1, #0
	movs r0, #0x20
	strb r0, [r6, #0x13]
	str r1, [r6, #0x64]
	ldr r1, _08059250 @ =0x0000B217
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080591B0:
	ldr r7, [r6, #0x2c]
	movs r4, #0x80
	lsls r4, r4, #3
	str r4, [r7, #0x64]
	ldr r5, _08059254 @ =gSineTable
	ldr r0, [r6, #0x64]
	lsls r0, r0, #8
	ldr r1, _08059258 @ =0x00000212
	bl __divsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	adds r0, r0, r4
	str r0, [r7, #0x64]
	ldr r0, _0805925C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r1, _08059260 @ =0x00FFFF00
	ands r0, r1
	cmp r0, r4
	bne _080591F8
	adds r0, r7, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _080591F8
	movs r0, #0x52
	bl PlaySound
_080591F8:
	adds r0, r7, #0
	adds r0, #0xb4
	ldrb r0, [r0]
	cmp r0, #6
	bhi _0805921A
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805921A
	movs r0, #8
	strb r0, [r6, #0x13]
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
_0805921A:
	ldr r4, [r6, #0x28]
	ldr r0, [r6, #0x64]
	adds r0, #1
	str r0, [r6, #0x64]
	cmp r0, #2
	ble _0805926A
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08059264
	ldrb r0, [r6, #0x12]
	subs r0, #6
	b _08059268
	.align 2, 0
_08059238: .4byte 0x08363F04
_0805923C: .4byte 0xFFFFF600
_08059240: .4byte 0xFFFFDB00
_08059244: .4byte 0xFFFFD400
_08059248: .4byte 0xFFFFC900
_0805924C: .4byte 0xFFFFEF00
_08059250: .4byte 0x0000B217
_08059254: .4byte gSineTable
_08059258: .4byte 0x00000212
_0805925C: .4byte pZero2
_08059260: .4byte 0x00FFFF00
_08059264:
	ldrb r0, [r6, #0x12]
	adds r0, #6
_08059268:
	strb r0, [r6, #0x12]
_0805926A:
	ldr r0, [r6, #0x64]
	cmp r0, #0x90
	ble _0805928E
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08059282
	ldrb r0, [r6, #0x12]
	cmp r0, #0x1c
	beq _08059288
	b _0805928E
_08059282:
	ldrb r0, [r6, #0x12]
	cmp r0, #0x64
	bne _0805928E
_08059288:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0805928E:
	ldrb r0, [r6, #0x12]
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #5
	bhi _080592E4
	adds r0, r7, #0
	adds r0, #0x24
	ldrb r0, [r0]
	adds r0, #0x80
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r3, r0, #0
	ldr r5, _08059310 @ =gSineTable
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080592C0
	adds r0, #0xff
_080592C0:
	asrs r2, r0, #8
	lsls r0, r3, #1
	adds r0, r0, r5
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080592D6
	adds r0, #0xff
_080592D6:
	asrs r3, r0, #8
	ldr r0, [r7, #0x54]
	adds r0, r0, r2
	ldr r1, [r7, #0x58]
	adds r1, r1, r3
	bl FUN_080aa5e8
_080592E4:
	ldrb r0, [r6, #0x12]
	cmp r0, #5
	bhi _080592F0
	movs r0, #0x96
	bl PlaySound
_080592F0:
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	adds r0, r7, #0
	movs r1, #0
	bl glacierle_08082598
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _080593BC
	.align 2, 0
_08059310: .4byte gSineTable
_08059314:
	movs r0, #0x1e
	strb r0, [r6, #0x13]
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r6, #0x64]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08059324:
	ldr r7, [r6, #0x2c]
	ldr r4, [r6, #0x28]
	ldr r0, _08059374 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r1, _08059378 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bne _0805934E
	adds r0, r7, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0805934E
	movs r0, #0x52
	bl PlaySound
_0805934E:
	ldr r0, [r6, #0x64]
	subs r0, #0x64
	str r0, [r6, #0x64]
	ldr r1, _0805937C @ =0x000002FF
	cmp r0, r1
	bgt _08059360
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r6, #0x64]
_08059360:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08059380
	ldr r1, [r6, #0x64]
	asrs r1, r1, #8
	ldrb r0, [r6, #0x12]
	subs r0, r0, r1
	b _08059388
	.align 2, 0
_08059374: .4byte pZero2
_08059378: .4byte 0x00FFFF00
_0805937C: .4byte 0x000002FF
_08059380:
	ldr r0, [r6, #0x64]
	asrs r0, r0, #8
	ldrb r1, [r6, #0x12]
	adds r0, r0, r1
_08059388:
	strb r0, [r6, #0x12]
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	adds r0, r7, #0
	movs r1, #0
	bl glacierle_08082598
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080593B6
	movs r0, #0x11
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_080593B6:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080593BC:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start glacierle_080593c4
glacierle_080593c4: @ 0x080593C4
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080593DC
	cmp r0, #1
	beq _08059484
	b _080594BC
_080593DC:
	ldr r7, [r6, #0x2c]
	adds r1, r7, #0
	adds r1, #0xb4
	ldrb r0, [r1]
	movs r2, #0xb4
	adds r2, r2, r6
	mov sb, r2
	cmp r0, #0
	beq _080593FC
	adds r4, r1, #0
_080593F0:
	adds r0, r7, #0
	bl FUN_08082348
	ldrb r0, [r4]
	cmp r0, #0
	bne _080593F0
_080593FC:
	ldr r5, [r6, #0x28]
	mov ip, r5
	ldrb r2, [r5, #0xa]
	movs r1, #0xfe
	adds r0, r1, #0
	ands r0, r2
	movs r4, #0
	movs r2, #0xfd
	mov sl, r2
	ands r0, r2
	strb r0, [r5, #0xa]
	mov r0, ip
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r2, [r5, #0xa]
	movs r3, #0xfb
	adds r0, r3, #0
	ands r0, r2
	strb r0, [r5, #0xa]
	ldr r0, _080594CC @ =gEnemyFnTable
	mov r8, r0
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	add r0, r8
	movs r2, #3
	str r2, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	ldrb r0, [r7, #0xa]
	ands r1, r0
	mov r5, sl
	ands r1, r5
	strb r1, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r0, [r7, #0xa]
	ands r3, r0
	strb r3, [r7, #0xa]
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	add r0, r8
	str r2, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
	mov r1, sb
	ldr r0, [r1]
	movs r1, #1
	orrs r0, r1
	mov r2, sb
	str r0, [r2]
	ldr r1, _080594D0 @ =0x0000B219
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08059484:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805949A
	movs r0, #0
	strb r0, [r6, #0xd]
	strb r0, [r6, #0xe]
_0805949A:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r2, _080594D4 @ =0x08364B26
	adds r1, r6, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080594D8 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
_080594BC:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080594CC: .4byte gEnemyFnTable
_080594D0: .4byte 0x0000B219
_080594D4: .4byte 0x08364B26
_080594D8: .4byte sCollisions
