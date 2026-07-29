	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyxMode18
copyxMode18: @ 0x080563CC
	push {r4, lr}
	sub sp, #4
	adds r4, r0, #0
	ldr r1, _080563FC @ =0x080FEFB4
	mov r0, sp
	movs r2, #4
	bl memcpy
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056410
	ldr r1, _08056400 @ =0x0000B302
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	cmp r0, #0
	beq _08056404
	movs r0, #4
	b _0805640E
	.align 2, 0
_080563FC: .4byte 0x080FEFB4
_08056400: .4byte 0x0000B302
_08056404:
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	add r0, sp
	ldrb r0, [r0]
_0805640E:
	strb r0, [r4, #0x12]
_08056410:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805642C
	movs r0, #0x13
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805642C:
	add sp, #4
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start copyxMode19
copyxMode19: @ 0x08056434
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080564DA
	ldr r1, _08056470 @ =0x0000B303
	adds r0, r4, #0
	bl SetMotion
	movs r6, #0
	strb r6, [r4, #0xe]
	adds r5, r4, #0
	adds r5, #0xc6
	ldrb r0, [r5]
	cmp r0, #0
	beq _08056474
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0
	bl FUN_080a83e4
	strb r6, [r5]
	movs r0, #0x46
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0xc7
	movs r0, #1
	b _080564D8
	.align 2, 0
_08056470: .4byte 0x0000B303
_08056474:
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #1
	beq _080564A4
	cmp r0, #1
	bgt _08056488
	cmp r0, #0
	beq _08056492
	b _080564D2
_08056488:
	cmp r0, #2
	beq _080564B0
	cmp r0, #3
	beq _080564C2
	b _080564D2
_08056492:
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl FUN_080a83e4
	movs r0, #0x46
	bl PlaySound
	b _080564D2
_080564A4:
	adds r0, r4, #0
	movs r1, #0
	movs r2, #6
	bl FUN_080a88a4
	b _080564D2
_080564B0:
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl FUN_080a9048
	movs r0, #0x49
	bl PlaySound
	b _080564D2
_080564C2:
	adds r0, r4, #0
	movs r1, #3
	movs r2, #0
	bl FUN_080a9048
	movs r0, #0x46
	bl PlaySound
_080564D2:
	adds r1, r4, #0
	adds r1, #0xc7
	movs r0, #0
_080564D8:
	strb r0, [r1]
_080564DA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08056502
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080564FA
	movs r0, #0x14
	b _080564FC
_080564FA:
	movs r0, #0x12
_080564FC:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08056502:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start copyx_08056508
copyx_08056508: @ 0x08056508
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805651E
	ldr r1, _0805653C @ =0x0000B304
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
_0805651E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080565AC
	adds r5, r4, #0
	adds r5, #0xcd
	ldrb r0, [r5]
	cmp r0, #0
	beq _08056540
	subs r0, #1
	b _0805659A
	.align 2, 0
_0805653C: .4byte 0x0000B304
_08056540:
	adds r0, r4, #0
	adds r0, #0xc7
	ldrb r0, [r0]
	cmp r0, #0
	bne _0805659C
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #1
	bne _0805657C
	ldr r2, _08056570 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08056574 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08056578 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	b _0805659A
	.align 2, 0
_08056570: .4byte RNG_0202f388
_08056574: .4byte 0x000343FD
_08056578: .4byte 0x00269EC3
_0805657C:
	cmp r0, #2
	bne _0805659C
	ldr r2, _080565B4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080565B8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080565BC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
_0805659A:
	strb r0, [r5]
_0805659C:
	movs r0, #3
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	movs r0, #2
	strb r0, [r4, #0xf]
	movs r0, #4
	strb r0, [r4, #0x12]
_080565AC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080565B4: .4byte RNG_0202f388
_080565B8: .4byte 0x000343FD
_080565BC: .4byte 0x00269EC3

	thumb_func_start copyx_080565c0
copyx_080565c0: @ 0x080565C0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805664C
	ldr r1, _0805661C @ =0x0000B307
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	movs r3, #0
	ldr r0, _08056620 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _080565E6
	movs r3, #1
_080565E6:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _080565F8
	movs r3, #1
_080565F8:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _08056624
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805662A
	.align 2, 0
_0805661C: .4byte 0x0000B307
_08056620: .4byte pZero2
_08056624:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805662A:
	strb r0, [r4, #0xa]
	ldr r0, _0805668C @ =0xFFFFFF00
	str r0, [r4, #0x60]
	ldr r2, _08056690 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08056694 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08056698 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	ands r0, r1
	adds r0, #6
	strb r0, [r4, #0x12]
_0805664C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080566A8
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #0
	bne _080566A0
	ldr r0, _0805669C @ =gMission
	ldr r0, [r0]
	ldrb r0, [r0, #1]
	cmp r0, #4
	bls _080566A0
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	cmp r0, #0
	beq _080566A0
	movs r0, #0x26
	b _080566A2
	.align 2, 0
_0805668C: .4byte 0xFFFFFF00
_08056690: .4byte RNG_0202f388
_08056694: .4byte 0x000343FD
_08056698: .4byte 0x00269EC3
_0805669C: .4byte gMission
_080566A0:
	movs r0, #0x16
_080566A2:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_080566A8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

