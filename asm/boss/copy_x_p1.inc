	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyxNeutral
copyxNeutral: @ 0x08055848
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	ldr r2, _0805587C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08055880 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08055884 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r6, r0, #0x11
	movs r0, #0x1f
	ands r6, r0
	ldr r0, _08055888 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _0805588C
	movs r2, #0x80
	lsls r2, r2, #7
	adds r0, r0, r2
	b _08055890
	.align 2, 0
_0805587C: .4byte RNG_0202f388
_08055880: .4byte 0x000343FD
_08055884: .4byte 0x00269EC3
_08055888: .4byte pZero2
_0805588C:
	ldr r7, _080558DC @ =0xFFFFC000
	adds r0, r0, r7
_08055890:
	subs r1, r1, r0
	mov r8, r1
	adds r0, r5, #0
	bl UpdateMotionGraphic
	movs r3, #0
	ldr r0, _080558E0 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _080558AA
	movs r3, #1
_080558AA:
	adds r0, r5, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _080558BC
	movs r3, #1
_080558BC:
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r2, r3, #4
	ldrb r1, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r4]
	cmp r3, #0
	beq _080558E4
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080558EA
	.align 2, 0
_080558DC: .4byte 0xFFFFC000
_080558E0: .4byte pZero2
_080558E4:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080558EA:
	strb r0, [r5, #0xa]
	ldr r0, _0805591C @ =gStageRun+232
	adds r4, r5, #0
	adds r4, #0x54
	adds r1, r4, #0
	bl CalcFromCamera
	adds r3, r0, #0
	mov ip, r4
	adds r4, #0x50
	cmp r3, #0
	bne _08055920
	adds r2, r5, #0
	adds r2, #0xce
	ldrb r1, [r2]
	movs r7, #0
	ldrsh r0, [r4, r7]
	cmp r1, r0
	ble _08055920
	movs r0, #0x23
	strb r0, [r5, #0xd]
	movs r0, #1
	strb r0, [r5, #0xe]
	strb r3, [r2]
	b _08055ABC
	.align 2, 0
_0805591C: .4byte gStageRun+232
_08055920:
	adds r7, r5, #0
	adds r7, #0xd8
	movs r0, #0
	ldrsh r1, [r7, r0]
	movs r2, #0
	ldrsh r0, [r4, r2]
	cmp r1, r0
	ble _08055942
	adds r0, r5, #0
	bl copyx_080578e0
	movs r0, #1
	strb r0, [r5, #0xe]
	ldrh r0, [r4]
	subs r0, #8
	strh r0, [r7]
	b _08055ABC
_08055942:
	adds r0, r5, #0
	adds r0, #0xcd
	ldrb r0, [r0]
	cmp r0, #0
	beq _0805595A
	adds r0, r5, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	cmp r0, #0
	bne _0805595A
	movs r0, #0x11
	b _08055AB6
_0805595A:
	ldr r0, _0805597C @ =gStageRun+232
	mov r1, ip
	bl CalcFromCamera
	cmp r0, #0
	beq _080559A0
	cmp r6, #0xf
	bhi _08055984
	movs r0, #9
	strb r0, [r5, #0xd]
	movs r0, #0xd
	strb r0, [r5, #0xf]
	ldr r0, _08055980 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	b _080559CE
	.align 2, 0
_0805597C: .4byte gStageRun+232
_08055980: .4byte pZero2
_08055984:
	movs r0, #9
	strb r0, [r5, #0xd]
	movs r0, #0xb
	strb r0, [r5, #0xf]
	ldr r0, _0805599C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	movs r1, #0x2e
	b _08055A6E
	.align 2, 0
_0805599C: .4byte pZero2
_080559A0:
	ldr r2, _080559E4 @ =pZero2
	ldr r3, [r2]
	ldr r1, [r5, #0x58]
	ldr r0, [r3, #0x58]
	subs r1, r1, r0
	movs r0, #0x90
	lsls r0, r0, #7
	adds r7, r2, #0
	cmp r1, r0
	ble _080559EC
	movs r7, #0
	ldrsh r0, [r4, r7]
	cmp r6, #1
	bls _08055A62
	cmp r6, #0x13
	bls _08055A84
	cmp r6, #0x19
	bhi _08055AB4
	movs r0, #9
	strb r0, [r5, #0xd]
	movs r0, #0xd
	strb r0, [r5, #0xf]
	ldr r1, [r3, #0x54]
_080559CE:
	ldr r0, [r5, #0x54]
	subs r0, r1, r0
	cmp r0, #0
	bge _080559D8
	adds r0, #0x7f
_080559D8:
	asrs r0, r0, #7
	str r0, [r5, #0x5c]
	ldr r0, _080559E8 @ =0xFFFFFA00
	str r0, [r5, #0x60]
	b _08055AB8
	.align 2, 0
_080559E4: .4byte pZero2
_080559E8: .4byte 0xFFFFFA00
_080559EC:
	ldr r2, [r3, #0x54]
	ldr r0, [r5, #0x54]
	subs r1, r2, r0
	adds r3, r0, #0
	cmp r1, #0
	blt _08055A02
	movs r0, #0xc8
	lsls r0, r0, #7
	cmp r1, r0
	bgt _08055A0C
	b _08055A36
_08055A02:
	subs r1, r3, r2
	movs r0, #0xc8
	lsls r0, r0, #7
	cmp r1, r0
	ble _08055A36
_08055A0C:
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #0x1f
	bgt _08055A1E
_08055A14:
	cmp r6, #1
	bls _08055A62
_08055A18:
	cmp r6, #0x13
	bls _08055A84
	b _08055A8C
_08055A1E:
	cmp r0, #0x2f
	bgt _08055A2C
	cmp r6, #0
	beq _08055A50
	cmp r6, #2
	bls _08055A62
	b _08055A18
_08055A2C:
	cmp r6, #1
	bls _08055A50
	cmp r6, #5
	bls _08055A62
	b _08055A18
_08055A36:
	movs r2, #0
	ldrsh r0, [r4, r2]
	cmp r0, #0x1f
	ble _08055A14
	cmp r0, #0x2f
	bgt _08055A4C
	cmp r6, #0
	beq _08055A50
	cmp r6, #2
	bls _08055A62
	b _08055A18
_08055A4C:
	cmp r6, #1
	bhi _08055A5E
_08055A50:
	movs r0, #3
	strb r0, [r5, #0xd]
	movs r0, #2
	strb r0, [r5, #0xf]
	movs r0, #0x10
	strb r0, [r5, #0x12]
	b _08055AB8
_08055A5E:
	cmp r6, #3
	bhi _08055A80
_08055A62:
	movs r0, #9
	strb r0, [r5, #0xd]
	movs r0, #0xb
	strb r0, [r5, #0xf]
	mov r0, r8
	movs r1, #0x28
_08055A6E:
	bl __divsi3
	str r0, [r5, #0x5c]
	ldr r0, _08055A7C @ =0xFFFFFB00
	str r0, [r5, #0x60]
	b _08055AB8
	.align 2, 0
_08055A7C: .4byte 0xFFFFFB00
_08055A80:
	cmp r6, #0x10
	bhi _08055A8C
_08055A84:
	adds r0, r5, #0
	bl copyx_080577c8
	b _08055AB8
_08055A8C:
	cmp r6, #0x19
	bhi _08055AB4
	movs r0, #9
	strb r0, [r5, #0xd]
	movs r0, #0xd
	strb r0, [r5, #0xf]
	ldr r0, [r7]
	ldr r0, [r0, #0x54]
	subs r0, r0, r3
	cmp r0, #0
	bge _08055AA4
	adds r0, #0x3f
_08055AA4:
	asrs r0, r0, #6
	str r0, [r5, #0x5c]
	ldr r0, _08055AB0 @ =0xFFFFFE00
	str r0, [r5, #0x60]
	b _08055AB8
	.align 2, 0
_08055AB0: .4byte 0xFFFFFE00
_08055AB4:
	movs r0, #6
_08055AB6:
	strb r0, [r5, #0xd]
_08055AB8:
	movs r0, #1
	strb r0, [r5, #0xe]
_08055ABC:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
