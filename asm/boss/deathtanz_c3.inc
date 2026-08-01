	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start deathtanzEX1
deathtanzEX1: @ 0x0804A6B4
	push {r4, r5, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #8
	bls _0804A6C2
	b _0804A8AE
_0804A6C2:
	lsls r0, r0, #2
	ldr r1, _0804A6CC @ =_0804A6D0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804A6CC: .4byte _0804A6D0
_0804A6D0: @ jump table
	.4byte _0804A6F4 @ case 0
	.4byte _0804A77E @ case 1
	.4byte _0804A79C @ case 2
	.4byte _0804A7FE @ case 3
	.4byte _0804A814 @ case 4
	.4byte _0804A824 @ case 5
	.4byte _0804A84C @ case 6
	.4byte _0804A882 @ case 7
	.4byte _0804A894 @ case 8
_0804A6F4:
	adds r1, r5, #0
	adds r1, #0xc0
	movs r2, #0
	movs r0, #3
	strb r0, [r1]
	strb r2, [r5, #0x12]
	movs r1, #0
	ldr r0, _0804A744 @ =pZero2
	ldr r0, [r0]
	ldr r2, [r5, #0x54]
	ldr r0, [r0, #0x54]
	cmp r2, r0
	bge _0804A710
	movs r1, #1
_0804A710:
	adds r4, r1, #0
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r3, [r0]
	subs r0, r2, r3
	movs r1, #0xa0
	lsls r1, r1, #6
	adds r0, r0, r1
	movs r1, #0xa0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0804A748
	movs r0, #0
	cmp r2, r3
	bge _0804A730
	movs r0, #1
_0804A730:
	cmp r4, r0
	beq _0804A748
	movs r0, #1
	strb r0, [r5, #0xd]
	strb r0, [r5, #0xe]
	strb r0, [r5, #0x12]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _0804A8AE
	.align 2, 0
_0804A744: .4byte pZero2
_0804A748:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804A758
	cmp r4, #0
	beq _0804A762
	b _0804A75C
_0804A758:
	cmp r4, #0
	bne _0804A762
_0804A75C:
	movs r0, #2
	strb r0, [r5, #0xe]
	b _0804A8AE
_0804A762:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A794 @ =sCollisions+(24*4)
	bl SetDDP
	movs r0, #1
	strb r0, [r5, #0x12]
	ldr r1, _0804A798 @ =0x0000A707
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A77E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _0804A790
	b _0804A8AE
_0804A790:
	b _0804A86A
	.align 2, 0
_0804A794: .4byte sCollisions+(24*4)
_0804A798: .4byte 0x0000A707
_0804A79C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A7E4 @ =0x08362E3C
	bl SetDDP
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _0804A7F0
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _0804A7E8
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0804A7EE
	.align 2, 0
_0804A7E4: .4byte sCollisions+(24*68)
_0804A7E8:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0804A7EE:
	strb r0, [r5, #0xa]
_0804A7F0:
	ldr r1, _0804A810 @ =0x0000A727
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A7FE:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A8AE
	b _0804A86A
	.align 2, 0
_0804A810: .4byte 0x0000A727
_0804A814:
	movs r0, #0x5f
	bl PlaySound
	movs r0, #0
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A824:
	ldr r1, [r5, #0x54]
	ldr r2, [r5, #0x58]
	ldr r0, _0804A874 @ =0xFFFFB700
	adds r2, r2, r0
	ldrb r3, [r5, #0x12]
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r4, #1
	ands r0, r4
	str r0, [sp]
	adds r0, r5, #0
	bl deathtanz_080a09f4
	ldr r1, _0804A878 @ =0x0000A729
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A84C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A8AE
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bls _0804A87C
_0804A86A:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _0804A8AE
	.align 2, 0
_0804A874: .4byte 0xFFFFB700
_0804A878: .4byte 0x0000A729
_0804A87C:
	movs r0, #5
	strb r0, [r5, #0xe]
	b _0804A8AE
_0804A882:
	ldr r1, _0804A8B8 @ =0x0000A72A
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x5a
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A894:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0804A8AE
	movs r0, #0x12
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0804A8AE:
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804A8B8: .4byte 0x0000A72A

	thumb_func_start deathtanzEX2
deathtanzEX2: @ 0x0804A8BC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #7
	bls _0804A8C8
	b _0804AA1A
_0804A8C8:
	lsls r0, r0, #2
	ldr r1, _0804A8D4 @ =_0804A8D8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804A8D4: .4byte _0804A8D8
_0804A8D8: @ jump table
	.4byte _0804A8F8 @ case 0
	.4byte _0804A914 @ case 1
	.4byte _0804A948 @ case 2
	.4byte _0804A95A @ case 3
	.4byte _0804A994 @ case 4
	.4byte _0804A9A6 @ case 5
	.4byte _0804A9F4 @ case 6
	.4byte _0804AA02 @ case 7
_0804A8F8:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A940 @ =sCollisions+(24*1)
	bl SetDDP
	ldr r1, _0804A944 @ =0x0000A72B
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A914:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _0804A9DE
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _0804A9DE
	movs r0, #0x5d
	bl PlaySound
	adds r1, r5, #0
	adds r1, #0xc0
	movs r0, #2
	strb r0, [r1]
	b _0804A9CC
	.align 2, 0
_0804A940: .4byte sCollisions+(24*1)
_0804A944: .4byte 0x0000A72B
_0804A948:
	ldr r1, _0804A990 @ =0x0000A72D
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A95A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _0804A9DE
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _0804A9DE
	adds r0, r5, #0
	adds r0, #0xc0
	movs r4, #1
	strb r4, [r0]
	movs r0, #0x5d
	bl PlaySound
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldrb r3, [r5, #0xa]
	lsrs r3, r3, #4
	ands r3, r4
	movs r2, #1
	b _0804A9DA
	.align 2, 0
_0804A990: .4byte 0x0000A72D
_0804A994:
	ldr r1, _0804A9F0 @ =0x0000A72F
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A9A6:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _0804A9DE
	ldrb r1, [r5, #0x12]
	cmp r1, #0
	bne _0804A9DE
	adds r0, r5, #0
	adds r0, #0xc0
	strb r1, [r0]
	movs r0, #0x5d
	bl PlaySound
_0804A9CC:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldrb r3, [r5, #0xa]
	lsrs r3, r3, #4
	movs r2, #1
	ands r3, r2
	movs r2, #0
_0804A9DA:
	bl FUN_080a0888
_0804A9DE:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804AA1A
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _0804AA1A
	.align 2, 0
_0804A9F0: .4byte 0x0000A72F
_0804A9F4:
	ldr r1, _0804AA20 @ =0x0000A731
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804AA02:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804AA1A
	movs r1, #0
	movs r0, #5
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0804AA1A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804AA20: .4byte 0x0000A731

	thumb_func_start deathtanzKnockBackDamage
deathtanzKnockBackDamage: @ 0x0804AA24
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0804AA34
	cmp r0, #1
	beq _0804AABA
	b _0804AB44
_0804AA34:
	movs r0, #0x60
	bl PlaySound
	ldr r1, _0804AAD8 @ =0x0000A736
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0xc8
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r2, _0804AADC @ =0xFFFFD000
	adds r0, r0, r2
	adds r2, r5, #0
	adds r2, #0xcc
	ldr r2, [r2]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r3, r0, #0
	muls r3, r0, r3
	adds r0, r3, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r1, r0, #0
	str r1, [r5, #0x60]
	lsls r0, r4, #3
	adds r0, r0, r4
	lsls r0, r0, #7
	cmp r0, #0
	bge _0804AAA0
	adds r0, #0xff
_0804AAA0:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _0804AAB0
	adds r0, #0xff
_0804AAB0:
	asrs r0, r0, #8
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804AABA:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r1, r0, r1
	str r1, [r5, #0x54]
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r3, #0xa0
	lsls r3, r3, #7
	adds r2, r0, r3
	cmp r1, r2
	ble _0804AAE0
	str r2, [r5, #0x54]
	b _0804AAEA
	.align 2, 0
_0804AAD8: .4byte 0x0000A736
_0804AADC: .4byte 0xFFFFD000
_0804AAE0:
	ldr r2, _0804AB24 @ =0xFFFFB000
	adds r0, r0, r2
	cmp r1, r0
	bge _0804AAEA
	str r0, [r5, #0x54]
_0804AAEA:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0804AAFA
	str r1, [r5, #0x60]
_0804AAFA:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _0804AB28
	ldr r0, [r5, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r6, r0, #0
	cmp r6, #0
	bge _0804AB3E
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
	movs r1, #0
	movs r0, #5
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
	b _0804AB3E
	.align 2, 0
_0804AB24: .4byte 0xFFFFB000
_0804AB28:
	ldr r0, [r5, #0x54]
	ldr r3, _0804AB4C @ =0xFFFFE000
	adds r1, r2, r3
	bl PushoutToDown1
	adds r6, r0, #0
	cmp r6, #0
	bge _0804AB3E
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
_0804AB3E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0804AB44:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804AB4C: .4byte 0xFFFFE000

	thumb_func_start deathtanzMode19
deathtanzMode19: @ 0x0804AB50
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _0804AB62
	cmp r1, #1
	beq _0804ABD0
	b _0804AC38
_0804AB62:
	ldrb r0, [r4, #0xb]
	movs r7, #0x10
	movs r6, #0
	orrs r0, r7
	strb r0, [r4, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r4, #0x1d]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0804ABBA
	ldrb r0, [r4, #0xa]
	orrs r0, r7
	b _0804ABC0
_0804ABBA:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0804ABC0:
	strb r0, [r4, #0xa]
	ldr r1, _0804ABE4 @ =0x0000A739
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804ABD0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _0804ABE8
	movs r0, #0xf6
	b _0804ABEA
	.align 2, 0
_0804ABE4: .4byte 0x0000A739
_0804ABE8:
	movs r0, #0xfa
_0804ABEA:
	muls r0, r1, r0
	cmp r0, #0
	bge _0804ABF2
	adds r0, #0xff
_0804ABF2:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_0801779c
	ldrb r0, [r5, #0xc]
	cmp r0, #4
	bne _0804AC38
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
	ldr r1, _0804AC40 @ =gBossFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0804AC38:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0804AC40: .4byte gBossFnTable

	thumb_func_start FUN_0804ac44
FUN_0804ac44: @ 0x0804AC44
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _0804AC52
	b _0804ADA0
_0804AC52:
	lsls r0, r0, #2
	ldr r1, _0804AC5C @ =_0804AC60
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804AC5C: .4byte _0804AC60
_0804AC60: @ jump table
	.4byte _0804AC74 @ case 0
	.4byte _0804AD46 @ case 1
	.4byte _0804AD78 @ case 2
	.4byte _0804AD88 @ case 3
	.4byte _0804ADA0 @ case 4
_0804AC74:
	movs r5, #0
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #1
	ands r0, r1
	adds r6, r2, #0
	cmp r0, #0
	beq _0804ACBC
	movs r5, #1
	ldr r3, [r4, #0x54]
	ldr r1, _0804AD60 @ =0xFFFFD600
	adds r0, r3, r1
	str r0, [sp]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804ACA2
	movs r0, #0xb0
	lsls r0, r0, #6
	adds r2, r3, r0
_0804ACA2:
	str r2, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AD64 @ =0xFFFFE700
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bdb44
_0804ACBC:
	ldrb r1, [r6]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0804ACE4
	movs r5, #1
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AD68 @ =0xFFFFB400
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bdb44
_0804ACE4:
	cmp r5, #0
	beq _0804ACEE
	movs r0, #0x2a
	bl PlaySound
_0804ACEE:
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r3, _0804AD6C @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _0804AD34
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _0804AD34
	ldr r0, _0804AD70 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0804AD34:
	movs r0, #0x50
	strb r0, [r4, #0x12]
	ldr r1, _0804AD74 @ =0x0000A737
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AD46:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0804ADA0
	b _0804AD9A
	.align 2, 0
_0804AD60: .4byte 0xFFFFD600
_0804AD64: .4byte 0xFFFFE700
_0804AD68: .4byte 0xFFFFB400
_0804AD6C: .4byte gStageRun
_0804AD70: .4byte 0x0000FFFE
_0804AD74: .4byte 0x0000A737
_0804AD78:
	ldr r1, _0804ADA8 @ =sExplosionCoords
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AD88:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0804ADA0
	ldr r2, _0804ADAC @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
_0804AD9A:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804ADA0:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804ADA8: .4byte sExplosionCoords
_0804ADAC: .4byte gStageRun

	thumb_func_start deathtanz_0804adb0
deathtanz_0804adb0: @ 0x0804ADB0
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _0804ADBE
	b _0804AFD2
_0804ADBE:
	lsls r0, r0, #2
	ldr r1, _0804ADC8 @ =_0804ADCC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804ADC8: .4byte _0804ADCC
_0804ADCC: @ jump table
	.4byte _0804ADE0 @ case 0
	.4byte _0804AF32 @ case 1
	.4byte _0804AFAA @ case 2
	.4byte _0804AFBA @ case 3
	.4byte _0804AFD2 @ case 4
_0804ADE0:
	movs r6, #0
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #1
	ands r0, r1
	adds r5, r2, #0
	cmp r0, #0
	beq _0804AE28
	movs r6, #1
	ldr r3, [r4, #0x54]
	ldr r1, _0804AF50 @ =0xFFFFD600
	adds r0, r3, r1
	str r0, [sp]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804AE0E
	movs r0, #0xb0
	lsls r0, r0, #6
	adds r2, r3, r0
_0804AE0E:
	str r2, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AF54 @ =0xFFFFE700
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bdb44
_0804AE28:
	ldrb r1, [r5]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0804AE50
	movs r6, #1
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AF58 @ =0xFFFFB400
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bdb44
_0804AE50:
	cmp r6, #0
	beq _0804AE5A
	movs r0, #0x2a
	bl PlaySound
_0804AE5A:
	movs r0, #0x2f
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xc2
	ldrb r6, [r0]
	ldr r0, _0804AF5C @ =gBossHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0804AEC2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _0804AF60 @ =gBossFnTable
	movs r0, #7
	strb r0, [r3, #9]
	ldr r0, [r1, #0x1c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r3, #0x5c]
	str r4, [r3, #0x28]
	movs r1, #1
	strb r1, [r3, #0x10]
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	ands r0, r1
	eors r0, r6
	strb r0, [r3, #0x13]
_0804AEC2:
	ldr r1, _0804AF64 @ =0x0000A738
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r3, _0804AF68 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _0804AF04
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _0804AF04
	ldr r0, _0804AF6C @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0804AF04:
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AF70 @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r0, #0x32
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AF32:
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x5c]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xc2
	ldrb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804AF74
	cmp r3, #1
	bne _0804AF78
	b _0804AF7C
	.align 2, 0
_0804AF50: .4byte 0xFFFFD600
_0804AF54: .4byte 0xFFFFE700
_0804AF58: .4byte 0xFFFFB400
_0804AF5C: .4byte gBossHeaderPtr
_0804AF60: .4byte gBossFnTable
_0804AF64: .4byte 0x0000A738
_0804AF68: .4byte gStageRun
_0804AF6C: .4byte 0x0000FFFE
_0804AF70: .4byte 0xFFFFE000
_0804AF74:
	cmp r3, #0
	beq _0804AF7C
_0804AF78:
	movs r0, #0xfa
	b _0804AF7E
_0804AF7C:
	movs r0, #0xf6
_0804AF7E:
	muls r0, r2, r0
	cmp r0, #0
	bge _0804AF86
	adds r0, #0xff
_0804AF86:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0804AFA2
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AFA2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0804AFD2
_0804AFAA:
	ldr r1, _0804AFDC @ =sExplosionCoords+8
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AFBA:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0804AFD2
	ldr r2, _0804AFE0 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AFD2:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804AFDC: .4byte sExplosionCoords+8
_0804AFE0: .4byte gStageRun
