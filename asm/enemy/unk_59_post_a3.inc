	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08091da4
FUN_08091da4: @ 0x08091DA4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08091DB4
	cmp r0, #1
	beq _08091E26
	b _08091E4E
_08091DB4:
	movs r0, #0x80
	lsls r0, r0, #1
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08091DE8 @ =0x08369924
	bl SetDDP
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #7
	ldr r1, _08091DEC @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, _08091DF0 @ =0xFFFFFC00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	lsrs r2, r0, #1
	cmp r2, #0
	beq _08091DF4
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08091DFA
	.align 2, 0
_08091DE8: .4byte 0x08369924
_08091DEC: .4byte 0xFFFFFE80
_08091DF0: .4byte 0xFFFFFC00
_08091DF4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08091DFA:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
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
	ldr r1, _08091E54 @ =0x00008801
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091E26:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	cmp r0, #0
	ble _08091E40
	movs r1, #0
	movs r0, #8
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08091E40:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08091E4E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08091E54: .4byte 0x00008801

	thumb_func_start FUN_08091e58
FUN_08091e58: @ 0x08091E58
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08091E86
	cmp r0, #1
	bgt _08091E6E
	cmp r0, #0
	beq _08091E78
	b _08091EF6
_08091E6E:
	cmp r0, #2
	beq _08091EC4
	cmp r0, #3
	beq _08091ECE
	b _08091EF6
_08091E78:
	ldr r1, _08091EC0 @ =0x00008802
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091E86:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r2, [r4, #0x60]
	adds r2, #0x40
	str r2, [r4, #0x60]
	ldr r1, [r4, #0x58]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	bl PushoutToUp1
	adds r5, r0, #0
	cmp r5, #0
	bge _08091EB8
	movs r0, #0x80
	lsls r0, r0, #1
	bl PlaySound
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091EB8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08091EF6
	.align 2, 0
_08091EC0: .4byte 0x00008802
_08091EC4:
	movs r0, #0xc0
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091ECE:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08091EE0
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _08091EF6
_08091EE0:
	ldr r1, _08091EFC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	movs r0, #3
	strb r0, [r4, #0xd]
_08091EF6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091EFC: .4byte gEnemyFnTable

	thumb_func_start FUN_08091f00
FUN_08091f00: @ 0x08091F00
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08091F10
	cmp r0, #1
	beq _08091F38
	b _08091F90
_08091F10:
	movs r0, #0x80
	lsls r0, r0, #1
	bl PlaySound
	ldr r0, _08091F98 @ =0xFFFFFD00
	str r0, [r4, #0x5c]
	adds r1, r0, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	bge _08091F2C
	movs r1, #0xc0
	lsls r1, r1, #2
_08091F2C:
	str r1, [r4, #0x5c]
	ldr r0, _08091F9C @ =0xFFFFFE00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091F38:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, _08091FA0 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _08091F90
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
	ldr r1, _08091FA4 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08091F90:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08091F98: .4byte 0xFFFFFD00
_08091F9C: .4byte 0xFFFFFE00
_08091FA0: .4byte gStageRun+232
_08091FA4: .4byte gEnemyFnTable

	thumb_func_start FUN_08091fa8
FUN_08091fa8: @ 0x08091FA8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0x10
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #1
	beq _08092016
	cmp r0, #1
	bgt _08091FC2
	cmp r0, #0
	beq _08091FCC
	b _080921A6
_08091FC2:
	cmp r0, #2
	beq _08092044
	cmp r0, #3
	beq _0809204E
	b _080921A6
_08091FCC:
	adds r0, r7, #0
	bl InitNonAffineMotion
	ldrb r2, [r7, #0x13]
	cmp r2, #0
	beq _08091FE0
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08091FE6
_08091FE0:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_08091FE6:
	strb r0, [r7, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r7, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _08092040 @ =0x00001303
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0x12
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_08092016:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _08092030
	adds r0, r7, #0
	bl FUN_08091280
_08092030:
	ldrb r0, [r7, #0x12]
	cmp r0, #0
	beq _08092038
	b _080921A6
_08092038:
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
	b _080921A6
	.align 2, 0
_08092040: .4byte 0x00001303
_08092044:
	movs r0, #0
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0809204E:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	cmp r0, #0
	bne _08092060
	movs r0, #0x2a
	bl PlaySound
_08092060:
	ldrb r0, [r7, #0x12]
	adds r0, #1
	strb r0, [r7, #0x12]
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08092072
	b _080921A6
_08092072:
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	ldr r1, _08092094 @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r4, _08092098 @ =0x083697F4
	ldrb r2, [r7, #0x13]
	ldrb r1, [r7, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0809209C
	orrs r3, r2
	b _0809209E
	.align 2, 0
_08092094: .4byte 0xFFFFE800
_08092098: .4byte 0x083697F4
_0809209C:
	adds r3, r2, #0
_0809209E:
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r4, sp
	ldr r5, _080920C0 @ =0x08369810
	ldrb r2, [r7, #0x13]
	ldrb r1, [r7, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080920C4
	orrs r3, r2
	b _080920C6
	.align 2, 0
_080920C0: .4byte 0x08369810
_080920C4:
	adds r3, r2, #0
_080920C6:
	adds r0, r4, #0
	adds r1, r5, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r4, sp
	ldr r5, _080920E8 @ =0x0836982C
	ldrb r2, [r7, #0x13]
	ldrb r1, [r7, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080920EC
	orrs r3, r2
	b _080920EE
	.align 2, 0
_080920E8: .4byte 0x0836982C
_080920EC:
	adds r3, r2, #0
_080920EE:
	adds r0, r4, #0
	adds r1, r5, #0
	movs r2, #0
	bl CreateSlashedEnemy
	ldr r0, [r7, #0x58]
	ldr r1, _080921B4 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r3, _080921B8 @ =RNG_0202f388
	ldr r0, [r3]
	ldr r2, _080921BC @ =0x000343FD
	adds r1, r0, #0
	muls r1, r2, r1
	ldr r5, _080921C0 @ =0x00269EC3
	adds r1, r1, r5
	lsls r1, r1, #1
	lsrs r0, r1, #1
	mov r8, r0
	lsrs r1, r1, #0x11
	movs r6, #0x1f
	ands r1, r6
	movs r4, #0x10
	subs r1, r4, r1
	lsls r1, r1, #8
	ldr r0, [r7, #0x54]
	adds r0, r0, r1
	str r0, [sp]
	mov r0, r8
	muls r0, r2, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r6
	lsls r0, r0, #8
	ldr r1, [r7, #0x58]
	subs r1, r1, r0
	str r1, [sp, #4]
	movs r0, #2
	mov r1, sp
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	bl CreateSmoke
	ldr r3, [sp, #0xc]
	ldr r0, [r3]
	ldr r2, [sp, #8]
	muls r0, r2, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r6
	subs r4, r4, r0
	lsls r4, r4, #8
	ldr r0, [r7, #0x54]
	adds r0, r0, r4
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r2, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r6
	lsls r0, r0, #8
	ldr r1, [r7, #0x58]
	subs r1, r1, r0
	str r1, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r1, _080921C4 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r7, #0x14]
_080921A6:
	add sp, #0x10
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080921B4: .4byte 0xFFFFF000
_080921B8: .4byte RNG_0202f388
_080921BC: .4byte 0x000343FD
_080921C0: .4byte 0x00269EC3
_080921C4: .4byte gEnemyFnTable

	thumb_func_start FUN_080921c8
FUN_080921c8: @ 0x080921C8
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _08092230
	cmp r0, #1
	bgt _080921DC
	cmp r0, #0
	beq _080921E6
	b _080922D6
_080921DC:
	cmp r0, #2
	beq _0809225C
	cmp r0, #3
	beq _08092266
	b _080922D6
_080921E6:
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r2, [r5, #0x13]
	cmp r2, #0
	beq _080921FA
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08092200
_080921FA:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08092200:
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
	ldr r1, _08092258 @ =0x00001303
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x12
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08092230:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _0809224A
	adds r0, r5, #0
	bl FUN_08091280
_0809224A:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080922D6
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080922D6
	.align 2, 0
_08092258: .4byte 0x00001303
_0809225C:
	movs r0, #0
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08092266:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _08092278
	movs r0, #0x2a
	bl PlaySound
_08092278:
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080922D6
	adds r4, r5, #0
	adds r4, #0x54
	ldrb r2, [r5, #0xa]
	lsrs r2, r2, #4
	movs r0, #1
	ands r2, r0
	ldrb r3, [r5, #0x13]
	adds r0, r4, #0
	movs r1, #0
	bl CreateGhost18
	ldr r6, _080922B4 @ =0x08369848
	ldrb r2, [r5, #0x13]
	ldrb r1, [r5, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080922B8
	orrs r3, r2
	b _080922BA
	.align 2, 0
_080922B4: .4byte 0x08369848
_080922B8:
	adds r3, r2, #0
_080922BA:
	adds r0, r4, #0
	adds r1, r6, #0
	movs r2, #0
	bl CreateSlashedEnemy
	ldr r1, _080922DC @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r5, #0x14]
_080922D6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080922DC: .4byte gEnemyFnTable

