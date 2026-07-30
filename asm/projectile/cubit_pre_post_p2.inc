	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cubit_080a63ac
cubit_080a63ac: @ 0x080A63AC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	adds r6, r0, #0
	ldr r1, [r6, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _080A63C0
	b _080A66F0
_080A63C0:
	adds r0, r1, #0
	adds r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _080A63CC
	b _080A66F0
_080A63CC:
	ldrb r0, [r1, #0xd]
	cmp r0, #0xb
	bne _080A63D4
	b _080A66F0
_080A63D4:
	ldrb r0, [r6, #0xe]
	cmp r0, #0xc
	bls _080A63DC
	b _080A6702
_080A63DC:
	lsls r0, r0, #2
	ldr r1, _080A63E8 @ =_080A63EC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A63E8: .4byte _080A63EC
_080A63EC: @ jump table
	.4byte _080A6420 @ case 0
	.4byte _080A649C @ case 1
	.4byte _080A64B4 @ case 2
	.4byte _080A64C6 @ case 3
	.4byte _080A64E8 @ case 4
	.4byte _080A6550 @ case 5
	.4byte _080A656C @ case 6
	.4byte _080A6590 @ case 7
	.4byte _080A65B4 @ case 8
	.4byte _080A6650 @ case 9
	.4byte _080A6666 @ case 10
	.4byte _080A66D2 @ case 11
	.4byte _080A66E0 @ case 12
_080A6420:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r7, #0
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A645C @ =0x0836BC1C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r1, _080A6460 @ =0x0000B103
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0xb6
	ldrb r2, [r0]
	cmp r2, #0
	beq _080A6464
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A646A
	.align 2, 0
_080A645C: .4byte 0x0836BC1C
_080A6460: .4byte 0x0000B103
_080A6464:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A646A:
	strb r0, [r6, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, [r6, #0x28]
	ldr r0, [r1, #0x54]
	str r0, [r6, #0x54]
	ldr r0, [r1, #0x58]
	str r0, [r6, #0x58]
	movs r0, #5
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A649C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	b _080A65F8
_080A64B4:
	ldr r1, _080A64E4 @ =0x0000B104
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A64C6:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	bne _080A64D4
	b _080A6640
_080A64D4:
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080A64E0
	b _080A6702
_080A64E0:
	b _080A6640
	.align 2, 0
_080A64E4: .4byte 0x0000B104
_080A64E8:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	movs r0, #0xff
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _080A6564 @ =0x0836BC1C
	bl SetDDP
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	movs r7, #0
	movs r0, #0xb5
	adds r0, r0, r6
	mov r8, r0
	mov r4, sp
	ldr r5, _080A6568 @ =0x0836BD24
_080A6512:
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [r4, #4]
	ldr r0, [r5]
	ldr r1, [sp]
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #4]
	ldr r1, [r4, #4]
	adds r0, r0, r1
	str r0, [r4, #4]
	lsls r2, r7, #0x18
	lsrs r2, r2, #0x18
	mov r0, r8
	ldrb r3, [r0]
	adds r0, r6, #0
	mov r1, sp
	bl FUN_080a5f54
	adds r5, #8
	adds r7, #1
	cmp r7, #4
	ble _080A6512
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	strb r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A6550:
	adds r0, r6, #0
	adds r0, #0xb4
	ldrb r0, [r0]
	cmp r0, #0
	bne _080A655C
	b _080A6702
_080A655C:
	movs r0, #0
	strb r0, [r6, #0x13]
	b _080A6640
	.align 2, 0
_080A6564: .4byte 0x0836BC1C
_080A6568: .4byte 0x0836BD24
_080A656C:
	ldrb r0, [r6, #0x13]
	adds r4, r6, #0
	adds r4, #0xb4
	cmp r0, #0
	bne _080A6586
	ldrb r0, [r4]
	cmp r0, #5
	bne _080A6586
	movs r0, #1
	strb r0, [r6, #0x13]
	movs r0, #0xcc
	bl PlaySound
_080A6586:
	ldrb r0, [r4]
	cmp r0, #0
	beq _080A658E
	b _080A6702
_080A658E:
	b _080A6640
_080A6590:
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, [r6, #0x28]
	ldr r0, [r1, #0x54]
	str r0, [r6, #0x54]
	ldr r0, [r1, #0x58]
	str r0, [r6, #0x58]
	movs r0, #5
	strb r0, [r6, #0x13]
	ldr r1, _080A6648 @ =0x0000B103
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A65B4:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x71
	movs r1, #0
	ldrsb r1, [r0, r1]
	adds r4, r0, #0
	cmp r1, #1
	beq _080A65DE
	cmp r1, #5
	beq _080A65DE
	cmp r1, #9
	beq _080A65DE
	cmp r1, #0xd
	beq _080A65DE
	cmp r1, #0x11
	bne _080A65F4
_080A65DE:
	adds r0, r6, #0
	adds r0, #0x72
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _080A65F4
	movs r0, #0xcb
	bl PlaySound
_080A65F4:
	movs r0, #0
	ldrsb r0, [r4, r0]
_080A65F8:
	cmp r0, #1
	beq _080A660C
	cmp r0, #5
	beq _080A660C
	cmp r0, #9
	beq _080A660C
	cmp r0, #0xd
	beq _080A660C
	cmp r0, #0x11
	bne _080A6636
_080A660C:
	adds r0, r6, #0
	adds r0, #0x72
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _080A6636
	adds r0, r6, #0
	adds r0, #0x74
	ldrb r2, [r6, #0x13]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080A664C @ =0x0836BC1C
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
_080A6636:
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A6702
_080A6640:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080A6702
	.align 2, 0
_080A6648: .4byte 0x0000B103
_080A664C: .4byte 0x0836BC1C
_080A6650:
	ldr r1, _080A66C4 @ =0x0000B105
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0x30
	strb r0, [r6, #0x12]
	movs r0, #2
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A6666:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	beq _080A6690
	cmp r0, #5
	beq _080A6690
	cmp r0, #9
	beq _080A6690
	cmp r0, #0xd
	beq _080A6690
	cmp r0, #0x11
	bne _080A66E6
_080A6690:
	adds r0, r6, #0
	adds r0, #0x72
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _080A66E6
	adds r0, r6, #0
	adds r0, #0x74
	ldrb r2, [r6, #0x13]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080A66C8 @ =0x0836BC1C
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r6, #0x13]
	adds r1, r0, #0
	cmp r1, #4
	bhi _080A66CC
	cmp r1, #0
	beq _080A66E6
	adds r0, #1
	b _080A66CE
	.align 2, 0
_080A66C4: .4byte 0x0000B105
_080A66C8: .4byte 0x0836BC1C
_080A66CC:
	movs r0, #0
_080A66CE:
	strb r0, [r6, #0x13]
	b _080A66E6
_080A66D2:
	ldr r1, _080A6710 @ =0x0000B105
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A66E0:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080A66E6:
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A6702
_080A66F0:
	ldr r1, _080A6714 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080A6702:
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A6710: .4byte 0x0000B105
_080A6714: .4byte gProjectileFnTable

	thumb_func_start FUN_080a6718
FUN_080a6718: @ 0x080A6718
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bhi _080A672C
	ldrb r0, [r1, #0xd]
	cmp r0, #0xb
	bne _080A6736
_080A672C:
	ldrb r0, [r4, #0xe]
	cmp r0, #0x13
	bhi _080A6736
	movs r0, #0x14
	strb r0, [r4, #0xe]
_080A6736:
	ldrb r0, [r4, #0xe]
	cmp r0, #0x15
	bls _080A673E
	b _080A6D2A
_080A673E:
	lsls r0, r0, #2
	ldr r1, _080A6748 @ =_080A674C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A6748: .4byte _080A674C
_080A674C: @ jump table
	.4byte _080A67A4 @ case 0
	.4byte _080A68A2 @ case 1
	.4byte _080A6900 @ case 2
	.4byte _080A691C @ case 3
	.4byte _080A6944 @ case 4
	.4byte _080A697E @ case 5
	.4byte _080A6A94 @ case 6
	.4byte _080A6D2A @ case 7
	.4byte _080A6D2A @ case 8
	.4byte _080A6D2A @ case 9
	.4byte _080A6B54 @ case 10
	.4byte _080A6C3E @ case 11
	.4byte _080A6C9C @ case 12
	.4byte _080A6CB4 @ case 13
	.4byte _080A6CD0 @ case 14
	.4byte _080A6CE2 @ case 15
	.4byte _080A6D2A @ case 16
	.4byte _080A6D2A @ case 17
	.4byte _080A6D2A @ case 18
	.4byte _080A6D2A @ case 19
	.4byte _080A6CFA @ case 20
	.4byte _080A6D08 @ case 21
_080A67A4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A686C @ =0x0836BCAC
	bl SetDDP
	adds r6, r4, #0
	adds r6, #0xb8
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r6]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_0800a31c
	str r0, [sp]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r1, _080A6870 @ =0xFFFF8400
	adds r1, r0, r1
	str r1, [sp, #4]
	ldr r1, _080A6874 @ =0x0836BD4C
	adds r3, r4, #0
	adds r3, #0xb4
	ldrb r0, [r3]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r2, [r0]
	ldr r0, [sp]
	adds r2, r2, r0
	ldr r0, [r4, #0x54]
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldrb r0, [r3]
	lsls r0, r0, #3
	adds r1, #4
	adds r0, r0, r1
	ldr r1, [r0]
	ldr r0, [sp, #4]
	adds r1, r1, r0
	ldr r0, [r4, #0x58]
	subs r1, r1, r0
	str r1, [r4, #0x60]
	asrs r2, r2, #2
	adds r0, r2, #0
	muls r0, r2, r0
	asrs r1, r1, #2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	adds r0, r0, r1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r5, r0, #0xe
	cmp r5, #0
	beq _080A6830
	ldr r0, [r4, #0x5c]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x60]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	str r0, [r4, #0x60]
_080A6830:
	ldr r1, [r4, #0x5c]
	ldr r0, [r6]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r4, #0x64]
	ldr r1, [r4, #0x60]
	ldr r0, [r6]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r4, #0x68]
	adds r0, r4, #0
	adds r0, #0xbc
	str r5, [r0]
	ldr r1, [r4, #0x64]
	cmp r1, #0
	bge _080A6852
	rsbs r1, r1, #0
_080A6852:
	movs r0, #0x80
	lsls r0, r0, #1
	cmp r1, r0
	ble _080A688C
	ldr r0, [r4, #0x64]
	cmp r0, #0
	ble _080A687C
	ldr r1, _080A6878 @ =0x0000B108
	adds r0, r4, #0
	bl SetMotion
	movs r0, #2
	b _080A6896
	.align 2, 0
_080A686C: .4byte 0x0836BCAC
_080A6870: .4byte 0xFFFF8400
_080A6874: .4byte 0x0836BD4C
_080A6878: .4byte 0x0000B108
_080A687C:
	ldr r1, _080A6888 @ =0x0000B107
	adds r0, r4, #0
	bl SetMotion
	movs r0, #1
	b _080A6896
	.align 2, 0
_080A6888: .4byte 0x0000B107
_080A688C:
	ldr r1, _080A68FC @ =0x0000B106
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
_080A6896:
	strb r0, [r4, #0x13]
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A68A2:
	ldrb r0, [r4, #0x12]
	adds r1, r0, #1
	strb r1, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r1, #5
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A68CE
	adds r0, r4, #0
	adds r0, #0x54
	adds r1, r4, #0
	adds r1, #0x64
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r3, #1
	ands r2, r3
	ldrb r3, [r4, #0x13]
	bl FUN_080c07e4
_080A68CE:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r2, r4, #0
	adds r2, #0xbc
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r2]
	ldr r1, [r1]
	subs r0, r0, r1
	str r0, [r2]
	cmp r0, #0
	ble _080A68FA
	b _080A6D2A
_080A68FA:
	b _080A6CC4
	.align 2, 0
_080A68FC: .4byte 0x0000B106
_080A6900:
	ldr r1, [r4, #0x28]
	adds r1, #0xb4
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	movs r0, #0x1e
	strb r0, [r4, #0x13]
	ldr r1, _080A6940 @ =0x0000B106
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A691C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x28]
	adds r0, #0xb4
	ldrb r0, [r0]
	cmp r0, #5
	beq _080A692E
	b _080A6D2A
_080A692E:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080A6936
	b _080A6CC4
_080A6936:
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	b _080A6CC0
	.align 2, 0
_080A6940: .4byte 0x0000B106
_080A6944:
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x58]
	str r0, [r4, #0x68]
	adds r0, r4, #0
	adds r0, #0xbc
	movs r2, #0
	str r2, [r0]
	subs r0, #8
	ldrb r0, [r0]
	cmp r0, #2
	bne _080A6974
	ldr r0, _080A696C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _080A6970
	strb r2, [r4, #0x13]
	b _080A6974
	.align 2, 0
_080A696C: .4byte pZero2
_080A6970:
	movs r0, #1
	strb r0, [r4, #0x13]
_080A6974:
	movs r0, #0
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A697E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xb4
	ldrb r1, [r0]
	adds r6, r0, #0
	cmp r1, #0
	bne _080A699A
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	adds r0, #3
	b _080A69C8
_080A699A:
	cmp r1, #1
	beq _080A69C0
	cmp r1, #3
	bne _080A69AC
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	adds r0, #3
	b _080A69C8
_080A69AC:
	cmp r1, #4
	beq _080A69C0
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080A69C0
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	adds r0, #3
	b _080A69C8
_080A69C0:
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	subs r0, #3
_080A69C8:
	str r0, [r1]
	adds r5, r1, #0
	ldr r3, _080A6A30 @ =gSineTable
	ldrb r0, [r5]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	asrs r0, r0, #1
	lsls r0, r0, #4
	ldr r2, [r4, #0x64]
	adds r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, [r5]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #6
	ldr r1, [r4, #0x68]
	adds r1, r1, r0
	str r1, [r4, #0x60]
	ldr r3, [r4, #0x54]
	subs r2, r2, r3
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r4, #0x54]
	ldr r2, [r4, #0x58]
	subs r1, r1, r2
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r4, #0x58]
	ldrb r0, [r6]
	cmp r0, #0
	bne _080A6A34
	ldr r1, [r5]
	movs r0, #0x9f
	lsls r0, r0, #1
	cmp r1, r0
	bgt _080A6A2E
	b _080A6D2A
_080A6A2E:
	b _080A6CC4
	.align 2, 0
_080A6A30: .4byte gSineTable
_080A6A34:
	cmp r0, #1
	bne _080A6A48
	ldr r1, [r5]
	ldr r0, _080A6A44 @ =0xFFFFFEC1
	cmp r1, r0
	ble _080A6A42
	b _080A6D2A
_080A6A42:
	b _080A6CC4
	.align 2, 0
_080A6A44: .4byte 0xFFFFFEC1
_080A6A48:
	cmp r0, #3
	bne _080A6A5A
	ldr r1, [r5]
	movs r0, #0x9f
	lsls r0, r0, #1
	cmp r1, r0
	bgt _080A6A58
	b _080A6D2A
_080A6A58:
	b _080A6CC4
_080A6A5A:
	cmp r0, #4
	bne _080A6A70
	ldr r1, [r5]
	ldr r0, _080A6A6C @ =0xFFFFFEC1
	cmp r1, r0
	ble _080A6A68
	b _080A6D2A
_080A6A68:
	b _080A6CC4
	.align 2, 0
_080A6A6C: .4byte 0xFFFFFEC1
_080A6A70:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080A6A84
	ldr r1, [r5]
	movs r0, #0x9f
	lsls r0, r0, #1
	cmp r1, r0
	bgt _080A6A82
	b _080A6D2A
_080A6A82:
	b _080A6CC4
_080A6A84:
	ldr r1, [r5]
	ldr r0, _080A6A90 @ =0xFFFFFEC1
	cmp r1, r0
	ble _080A6A8E
	b _080A6D2A
_080A6A8E:
	b _080A6CC4
	.align 2, 0
_080A6A90: .4byte 0xFFFFFEC1
_080A6A94:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xb4
	ldrb r1, [r0]
	adds r6, r0, #0
	cmp r1, #0
	bne _080A6AB0
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	adds r0, #1
	b _080A6ADE
_080A6AB0:
	cmp r1, #1
	beq _080A6AD6
	cmp r1, #3
	bne _080A6AC2
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	adds r0, #1
	b _080A6ADE
_080A6AC2:
	cmp r1, #4
	beq _080A6AD6
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080A6AD6
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	adds r0, #1
	b _080A6ADE
_080A6AD6:
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	subs r0, #1
_080A6ADE:
	str r0, [r1]
	adds r5, r1, #0
	ldr r0, [r4, #0x64]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	lsls r0, r0, #4
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x54]
	ldr r0, [r4, #0x68]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	lsls r0, r0, #4
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldrb r0, [r6]
	cmp r0, #0
	bne _080A6B12
	ldr r1, [r5]
	movs r0, #0xbf
	lsls r0, r0, #1
	cmp r1, r0
	bgt _080A6B10
	b _080A6D2A
_080A6B10:
	b _080A6B4A
_080A6B12:
	cmp r0, #1
	beq _080A6B40
	cmp r0, #3
	bne _080A6B28
	ldr r1, [r5]
	movs r0, #0xbf
	lsls r0, r0, #1
	cmp r1, r0
	bgt _080A6B26
	b _080A6D2A
_080A6B26:
	b _080A6B4A
_080A6B28:
	cmp r0, #4
	beq _080A6B40
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080A6B40
	ldr r1, [r5]
	movs r0, #0xbf
	lsls r0, r0, #1
	cmp r1, r0
	bgt _080A6B3E
	b _080A6D2A
_080A6B3E:
	b _080A6B4A
_080A6B40:
	ldr r1, [r5]
	ldr r0, _080A6B50 @ =0xFFFFFE81
	cmp r1, r0
	ble _080A6B4A
	b _080A6D2A
_080A6B4A:
	movs r0, #0xa
	strb r0, [r4, #0xe]
	b _080A6D2A
	.align 2, 0
_080A6B50: .4byte 0xFFFFFE81
_080A6B54:
	adds r7, r4, #0
	adds r7, #0xb8
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r7]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_0800a31c
	adds r5, r0, #0
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r2, _080A6C0C @ =0xFFFF8400
	adds r6, r0, r2
	ldr r1, _080A6C10 @ =0x0836BD4C
	adds r3, r4, #0
	adds r3, #0xb5
	ldrb r0, [r3]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r2, [r0]
	adds r2, r2, r5
	ldr r0, [r4, #0x54]
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldrb r0, [r3]
	lsls r0, r0, #3
	adds r1, #4
	adds r0, r0, r1
	ldr r1, [r0]
	adds r1, r1, r6
	ldr r0, [r4, #0x58]
	subs r1, r1, r0
	str r1, [r4, #0x60]
	asrs r2, r2, #2
	adds r0, r2, #0
	muls r0, r2, r0
	asrs r1, r1, #2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	adds r0, r0, r1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r5, r0, #0xe
	cmp r5, #0
	beq _080A6BD0
	ldr r0, [r4, #0x5c]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x60]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	str r0, [r4, #0x60]
_080A6BD0:
	ldr r1, [r4, #0x5c]
	ldr r0, [r7]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r4, #0x64]
	ldr r1, [r4, #0x60]
	ldr r0, [r7]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r4, #0x68]
	adds r0, r4, #0
	adds r0, #0xbc
	str r5, [r0]
	ldr r1, [r4, #0x64]
	cmp r1, #0
	bge _080A6BF2
	rsbs r1, r1, #0
_080A6BF2:
	movs r0, #0x80
	lsls r0, r0, #1
	cmp r1, r0
	ble _080A6C28
	ldr r0, [r4, #0x64]
	cmp r0, #0
	ble _080A6C18
	ldr r1, _080A6C14 @ =0x0000B108
	adds r0, r4, #0
	bl SetMotion
	movs r0, #2
	b _080A6C32
	.align 2, 0
_080A6C0C: .4byte 0xFFFF8400
_080A6C10: .4byte 0x0836BD4C
_080A6C14: .4byte 0x0000B108
_080A6C18:
	ldr r1, _080A6C24 @ =0x0000B107
	adds r0, r4, #0
	bl SetMotion
	movs r0, #1
	b _080A6C32
	.align 2, 0
_080A6C24: .4byte 0x0000B107
_080A6C28:
	ldr r1, _080A6C98 @ =0x0000B106
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
_080A6C32:
	strb r0, [r4, #0x13]
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A6C3E:
	ldrb r0, [r4, #0x12]
	adds r1, r0, #1
	strb r1, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r1, #5
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A6C6A
	adds r0, r4, #0
	adds r0, #0x54
	adds r1, r4, #0
	adds r1, #0x64
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r3, #1
	ands r2, r3
	ldrb r3, [r4, #0x13]
	bl FUN_080c07e4
_080A6C6A:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r2, r4, #0
	adds r2, #0xbc
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r2]
	ldr r1, [r1]
	subs r0, r0, r1
	str r0, [r2]
	cmp r0, #0
	bgt _080A6D2A
	b _080A6CC4
	.align 2, 0
_080A6C98: .4byte 0x0000B106
_080A6C9C:
	ldr r1, [r4, #0x28]
	adds r1, #0xb4
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	ldr r1, _080A6CCC @ =0x0000B106
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A6CB4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x28]
	adds r0, #0xb4
	ldrb r0, [r0]
_080A6CC0:
	cmp r0, #0
	bne _080A6D2A
_080A6CC4:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080A6D2A
	.align 2, 0
_080A6CCC: .4byte 0x0000B106
_080A6CD0:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A6CE2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080A6D18
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A6D2A
	b _080A6D18
_080A6CFA:
	ldr r1, _080A6D34 @ =0x0000B102
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A6D08:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A6D2A
_080A6D18:
	ldr r1, _080A6D38 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A6D2A:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A6D34: .4byte 0x0000B102
_080A6D38: .4byte gProjectileFnTable
