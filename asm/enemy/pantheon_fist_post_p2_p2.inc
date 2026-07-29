	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080954a4
FUN_080954a4: @ 0x080954A4
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080954B4
	cmp r0, #1
	beq _080954D2
	b _08095572
_080954B4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080954F8 @ =0x08369FEC
	bl SetDDP
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	movs r1, #0xd4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080954D2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r2, #0
	ldr r0, _080954FC @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _080954E8
	movs r2, #1
_080954E8:
	adds r5, r2, #0
	cmp r5, #0
	beq _08095500
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08095506
	.align 2, 0
_080954F8: .4byte 0x08369FEC
_080954FC: .4byte pZero2
_08095500:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08095506:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809555C
	lsls r0, r5, #1
	subs r5, r0, #1
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_08095074
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	bne _08095550
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_08094fa8
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095556
_08095550:
	movs r0, #0x10
	strb r0, [r4, #0x12]
	b _0809555C
_08095556:
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r6, [r4, #0xe]
_0809555C:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08095572
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08095572:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start FUN_08095578
FUN_08095578: @ 0x08095578
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _080955A8
	cmp r5, #1
	bgt _0809558C
	cmp r5, #0
	beq _08095596
	b _0809565E
_0809558C:
	cmp r5, #2
	beq _08095614
	cmp r5, #3
	beq _08095622
	b _0809565E
_08095596:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08095610 @ =0x08369FEC
	bl SetDDP
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080955A8:
	movs r1, #0xd4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #2
	bne _080955D6
	ldr r3, [r4, #0x54]
	adds r0, r3, #0
	subs r0, #0x80
	str r0, [r4, #0x54]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080955D4
	adds r2, r3, #0
	adds r2, #0x80
_080955D4:
	str r2, [r4, #0x54]
_080955D6:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080955E6
	str r1, [r4, #0x60]
_080955E6:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08095606
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095606:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0809565E
	.align 2, 0
_08095610: .4byte 0x08369FEC
_08095614:
	ldr r1, _08095644 @ =0x0000D401
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095622:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r2, [r0]
	cmp r2, #3
	bne _08095656
	adds r1, r4, #0
	adds r1, #0xb8
	ldrb r0, [r1]
	cmp r0, #0
	bne _08095648
	movs r0, #1
	strb r0, [r1]
	movs r0, #8
	b _08095650
	.align 2, 0
_08095644: .4byte 0x0000D401
_08095648:
	cmp r0, #2
	bne _0809564E
	strb r2, [r1]
_0809564E:
	movs r0, #1
_08095650:
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_08095656:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
_0809565E:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start FUN_08095664
FUN_08095664: @ 0x08095664
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08095674
	cmp r0, #1
	beq _080956B8
	b _0809576E
_08095674:
	movs r2, #0
	ldr r0, _0809569C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _08095684
	movs r2, #1
_08095684:
	lsls r1, r2, #8
	subs r1, #0x80
	adds r0, r4, #0
	bl FUN_08094fa8
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080956A0
	movs r0, #1
	b _0809576A
	.align 2, 0
_0809569C: .4byte pZero2
_080956A0:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080956DC @ =0x08369FEC
	bl SetDDP
	ldr r1, _080956E0 @ =0x0000D402
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080956B8:
	movs r3, #0
	ldr r1, _080956E4 @ =pZero2
	ldr r0, [r1]
	ldr r2, [r4, #0x54]
	ldr r0, [r0, #0x54]
	mov ip, r1
	cmp r2, r0
	bge _080956CA
	movs r3, #1
_080956CA:
	adds r5, r3, #0
	adds r2, r5, #0
	cmp r5, #0
	beq _080956E8
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080956EE
	.align 2, 0
_080956DC: .4byte 0x08369FEC
_080956E0: .4byte 0x0000D402
_080956E4: .4byte pZero2
_080956E8:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080956EE:
	strb r0, [r4, #0xa]
	movs r7, #1
	adds r1, r7, #0
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	movs r6, #0
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	mov r1, ip
	ldr r0, [r1]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	movs r1, #0xc8
	lsls r1, r1, #6
	adds r0, r0, r1
	ldr r1, _08095774 @ =0x000063FF
	cmp r0, r1
	bhi _0809572C
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r6, [r4, #0xe]
_0809572C:
	lsls r0, r5, #8
	adds r5, r0, #0
	subs r5, #0x80
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_08094fa8
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0809574E
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_08095014
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08095752
_0809574E:
	strb r7, [r4, #0xd]
	strb r6, [r4, #0xe]
_08095752:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0809576E
	movs r0, #2
_0809576A:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0809576E:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08095774: .4byte 0x000063FF

	thumb_func_start FUN_08095778
FUN_08095778: @ 0x08095778
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08095788
	cmp r0, #1
	beq _080957A4
	b _080957C6
_08095788:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080957CC @ =0x08369FEC
	bl SetDDP
	ldr r1, _080957D0 @ =0x0000D403
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080957A4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080957BE
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080957BE:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
_080957C6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080957CC: .4byte 0x08369FEC
_080957D0: .4byte 0x0000D403

	thumb_func_start FUN_080957d4
FUN_080957d4: @ 0x080957D4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080957E8
	cmp r0, #1
	beq _0809583E
	b _08095900
_080957E8:
	ldr r0, _08095820 @ =0x00000109
	bl PlaySound
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08095824 @ =0x0836A01C
	bl SetDDP
	movs r4, #0x10
	str r4, [r5, #0x64]
	movs r0, #0xa0
	lsls r0, r0, #3
	bl Sqrt
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0x12]
	ldr r2, [r5, #0x64]
	adds r1, r0, #0
	muls r1, r2, r1
	str r1, [r5, #0x5c]
	ldrb r0, [r5, #0xa]
	ands r4, r0
	cmp r4, #0
	bne _08095828
	rsbs r0, r1, #0
	str r0, [r5, #0x5c]
	b _0809582C
	.align 2, 0
_08095820: .4byte 0x00000109
_08095824: .4byte 0x0836A01C
_08095828:
	rsbs r0, r2, #0
	str r0, [r5, #0x64]
_0809582C:
	movs r0, #0
	strb r0, [r5, #0x13]
	ldr r1, _0809590C @ =0x0000D404
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0809583E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r7, _08095910 @ =pZero2
	ldr r0, [r7]
	adds r0, #0x8c
	ldr r0, [r0]
	movs r6, #1
	ands r0, r6
	cmp r0, #0
	beq _0809588C
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	mov r8, r1
	ands r0, r1
	cmp r0, #0
	beq _0809588C
	ldrb r0, [r5, #0x12]
	cmp r0, #0x10
	bls _0809588C
	ldrb r4, [r5, #0x13]
	cmp r4, #0
	bne _0809588C
	movs r0, #0x52
	bl PlaySound
	strb r6, [r5, #0x13]
	ldr r0, [r7]
	movs r1, #0x91
	lsls r1, r1, #1
	adds r0, r0, r1
	strb r6, [r0]
	ldr r0, [r7]
	mov r1, r8
	strb r1, [r0, #0xd]
	ldr r0, [r7]
	strb r4, [r0, #0xe]
_0809588C:
	ldr r0, [r5, #0x5c]
	ldr r1, [r5, #0x64]
	adds r0, r0, r1
	str r0, [r5, #0x5c]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	ldrb r1, [r5, #0x12]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	bne _080958B2
	cmp r1, #8
	bls _080958B2
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
_080958B2:
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08094fa8
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080958D4
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _080958D4
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08095014
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080958DC
_080958D4:
	movs r1, #0
	movs r0, #1
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080958DC:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080958F8
	movs r0, #2
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080958F8:
	adds r0, r5, #0
	movs r1, #1
	bl FUN_08094fe0
_08095900:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809590C: .4byte 0x0000D404
_08095910: .4byte pZero2
