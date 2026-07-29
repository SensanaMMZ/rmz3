	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809a700
FUN_0809a700: @ 0x0809A700
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	ldr r0, [r6, #0x28]
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A724
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _0809A720 @ =0x0836A6D4
	bl SetDDP
	b _0809A8F4
	.align 2, 0
_0809A720: .4byte 0x0836A6D4
_0809A724:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _0809A740 @ =0x0836A74C
	bl SetDDP
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _0809A782
	cmp r0, #1
	bgt _0809A744
	cmp r0, #0
	beq _0809A750
	b _0809A8F4
	.align 2, 0
_0809A740: .4byte 0x0836A74C
_0809A744:
	cmp r0, #2
	beq _0809A7A8
	cmp r0, #3
	bne _0809A74E
	b _0809A894
_0809A74E:
	b _0809A8F4
_0809A750:
	movs r1, #0xf1
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r6, #0x12]
	ldr r2, _0809A79C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0809A7A0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0809A7A4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1e
	bl __umodsi3
	adds r0, #0x1e
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0809A782:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809A794
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0809A794:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _0809A8F4
	.align 2, 0
_0809A79C: .4byte RNG_0202f388
_0809A7A0: .4byte 0x000343FD
_0809A7A4: .4byte 0x00269EC3
_0809A7A8:
	movs r0, #0x1e
	strb r0, [r6, #0x12]
	ldr r2, _0809A800 @ =RNG_0202f388
	mov r8, r2
	ldr r0, [r2]
	ldr r7, _0809A804 @ =0x000343FD
	muls r0, r7, r0
	ldr r5, _0809A808 @ =0x00269EC3
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r4, r0, #1
	str r4, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1e
	bl __umodsi3
	adds r0, #0x1e
	strb r0, [r6, #0x12]
	adds r0, r4, #0
	muls r0, r7, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r3, r0, #1
	mov r1, r8
	str r3, [r1]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #0
	bne _0809A810
	adds r0, r3, #0
	muls r0, r7, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r2, r8
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	lsls r0, r0, #0xa
	ldr r3, _0809A80C @ =0xFFFFFE00
	adds r0, r0, r3
	b _0809A846
	.align 2, 0
_0809A800: .4byte RNG_0202f388
_0809A804: .4byte 0x000343FD
_0809A808: .4byte 0x00269EC3
_0809A80C: .4byte 0xFFFFFE00
_0809A810:
	movs r2, #0x80
	rsbs r2, r2, #0
	adds r0, r3, #0
	muls r0, r7, r0
	ldr r1, _0809A860 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r3, r0, #1
	lsrs r0, r0, #0x11
	movs r1, #0x7f
	ands r0, r1
	subs r2, r2, r0
	adds r0, r3, #0
	muls r0, r7, r0
	ldr r3, _0809A860 @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, r8
	str r1, [r3]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	lsls r0, r0, #1
	subs r1, r1, r0
	adds r0, r2, #0
	muls r0, r1, r0
_0809A846:
	str r0, [r6, #0x5c]
	movs r1, #0
	ldr r0, [r6, #0x5c]
	cmp r0, #0
	ble _0809A852
	movs r1, #1
_0809A852:
	adds r2, r1, #0
	cmp r2, #0
	beq _0809A864
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809A86A
	.align 2, 0
_0809A860: .4byte 0x00269EC3
_0809A864:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A86A:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
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
	ldr r1, _0809A900 @ =0x0000F101
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0809A894:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x12]
	subs r0, #1
	movs r2, #0
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809A8AC
	strb r2, [r6, #0xe]
_0809A8AC:
	ldr r0, [r6, #0x54]
	ldr r1, _0809A904 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A8EE
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _0809A908 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
_0809A8EE:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_0809A8F4:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809A900: .4byte 0x0000F101
_0809A904: .4byte 0xFFFF3000
_0809A908: .4byte gEnemyFnTable
