	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809a1f0
FUN_0809a1f0: @ 0x0809A1F0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	adds r0, r6, #0
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A210
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0809A20C @ =0x0836A6D4
	bl SetDDP
	b _0809A30A
	.align 2, 0
_0809A20C: .4byte 0x0836A6D4
_0809A210:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0809A228 @ =0x0836A6EC
	bl SetDDP
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0809A22C
	cmp r0, #1
	beq _0809A292
	b _0809A30A
	.align 2, 0
_0809A228: .4byte 0x0836A6EC
_0809A22C:
	adds r1, r5, #0
	adds r1, #0x22
	movs r4, #1
	movs r0, #1
	strb r0, [r1]
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0x12]
	eors r4, r0
	cmp r4, #0
	beq _0809A250
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0809A256
_0809A250:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A256:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r4
	adds r0, r5, #0
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	movs r2, #0xb0
	lsls r2, r2, #1
	ldrb r1, [r5, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #6
	subs r2, r2, r0
	str r2, [r5, #0x5c]
	strb r3, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0809A292:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, _0809A310 @ =gSineTable
	ldrb r0, [r5, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsrs r0, r1, #0x1f
	adds r1, r1, r0
	asrs r1, r1, #1
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x13]
	adds r0, #4
	movs r4, #0
	strb r0, [r5, #0x13]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, _0809A314 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A30A
	str r4, [r6, #0x1c]
	adds r0, r6, #0
	adds r0, #0x32
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _0809A318 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_0809A30A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A310: .4byte gSineTable
_0809A314: .4byte 0xFFFF3000
_0809A318: .4byte gEnemyFnTable

	thumb_func_start FUN_0809a31c
FUN_0809a31c: @ 0x0809A31C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	adds r0, r6, #0
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A33C
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A338 @ =0x0836A6D4
	bl SetDDP
	b _0809A49A
	.align 2, 0
_0809A338: .4byte 0x0836A6D4
_0809A33C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A354 @ =0x0836A704
	bl SetDDP
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809A358
	cmp r0, #1
	beq _0809A3BE
	b _0809A49A
	.align 2, 0
_0809A354: .4byte 0x0836A704
_0809A358:
	adds r1, r4, #0
	adds r1, #0x22
	movs r0, #1
	strb r0, [r1]
	ldr r1, _0809A378 @ =0x00003501
	adds r0, r4, #0
	bl SetMotion
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _0809A37C
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0809A382
	.align 2, 0
_0809A378: .4byte 0x00003501
_0809A37C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A382:
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
	movs r2, #0x80
	lsls r2, r2, #2
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #8
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, _0809A4A0 @ =0xFFFFFEC0
	str r0, [r4, #0x60]
	movs r0, #0x3c
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809A3BE:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	movs r5, #0
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809A3F2
	ldr r2, _0809A4A4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0809A4A8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0809A4AC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1e
	bl __umodsi3
	adds r0, #0x1e
	strb r0, [r4, #0x13]
	ldr r1, _0809A4B0 @ =0x00003501
	adds r0, r4, #0
	bl SetMotion
_0809A3F2:
	ldr r1, [r4, #0x5c]
	lsls r0, r1, #7
	subs r0, r0, r1
	lsls r0, r0, #1
	cmp r0, #0
	bge _0809A400
	adds r0, #0xff
_0809A400:
	asrs r1, r0, #8
	str r1, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _0809A422
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0809A422:
	ldr r0, [r4, #0x60]
	adds r0, #0x10
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #2
	bne _0809A450
	ldr r0, _0809A4A0 @ =0xFFFFFEC0
	str r0, [r4, #0x60]
	movs r2, #0x80
	lsls r2, r2, #2
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #8
	subs r2, r2, r0
	str r2, [r4, #0x5c]
_0809A450:
	ldr r0, [r4, #0x54]
	ldr r1, _0809A4B4 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A49A
	str r5, [r6, #0x1c]
	adds r0, r6, #0
	adds r0, #0x32
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809A4B8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0809A49A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A4A0: .4byte 0xFFFFFEC0
_0809A4A4: .4byte RNG_0202f388
_0809A4A8: .4byte 0x000343FD
_0809A4AC: .4byte 0x00269EC3
_0809A4B0: .4byte 0x00003501
_0809A4B4: .4byte 0xFFFF3000
_0809A4B8: .4byte gEnemyFnTable

	thumb_func_start FUN_0809a4bc
FUN_0809a4bc: @ 0x0809A4BC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A4DC
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A4D8 @ =0x0836A6D4
	bl SetDDP
	b _0809A5CC
	.align 2, 0
_0809A4D8: .4byte 0x0836A6D4
_0809A4DC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A4F4 @ =0x0836A71C
	bl SetDDP
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809A4F8
	cmp r0, #1
	beq _0809A55C
	b _0809A5CC
	.align 2, 0
_0809A4F4: .4byte 0x0836A71C
_0809A4F8:
	movs r1, #0xf0
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0x12]
	movs r0, #1
	adds r2, r0, #0
	eors r2, r1
	cmp r2, #0
	beq _0809A516
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809A51C
_0809A516:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A51C:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	movs r2, #0xb0
	lsls r2, r2, #1
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #6
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	strb r3, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809A55C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, _0809A5D4 @ =gSineTable
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsrs r0, r1, #0x1f
	adds r1, r1, r0
	asrs r1, r1, #1
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	adds r0, #3
	movs r5, #0
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, _0809A5D8 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A5CC
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809A5DC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0809A5CC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809A5D4: .4byte gSineTable
_0809A5D8: .4byte 0xFFFF3000
_0809A5DC: .4byte gEnemyFnTable

	thumb_func_start FUN_0809a5e0
FUN_0809a5e0: @ 0x0809A5E0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A600
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A5FC @ =0x0836A6D4
	bl SetDDP
	b _0809A6EC
	.align 2, 0
_0809A5FC: .4byte 0x0836A6D4
_0809A600:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A618 @ =0x0836A734
	bl SetDDP
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809A61C
	cmp r0, #1
	beq _0809A67A
	b _0809A6EC
	.align 2, 0
_0809A618: .4byte 0x0836A734
_0809A61C:
	movs r1, #0xef
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0x12]
	movs r0, #1
	adds r2, r0, #0
	eors r2, r1
	cmp r2, #0
	beq _0809A63A
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809A640
_0809A63A:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A640:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	movs r2, #0xe0
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #6
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	strb r3, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809A67A:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, _0809A6F4 @ =gSineTable
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
	cmp r1, #0
	bge _0809A694
	adds r1, #3
_0809A694:
	asrs r1, r1, #2
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	adds r0, #3
	movs r5, #0
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, _0809A6F8 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A6EC
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809A6FC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0809A6EC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809A6F4: .4byte gSineTable
_0809A6F8: .4byte 0xFFFF3000
_0809A6FC: .4byte gEnemyFnTable

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

	thumb_func_start FUN_0809a90c
FUN_0809a90c: @ 0x0809A90C
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809AA02
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809A926
	cmp r0, #1
	beq _0809A9B2
	b _0809AA02
_0809A926:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	movs r3, #0x80
	rsbs r3, r3, #0
	ldr r2, _0809A974 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0809A978 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0809A97C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x7f
	ands r0, r1
	subs r3, r3, r0
	ldrb r0, [r4, #0x12]
	movs r1, #1
	eors r1, r0
	lsls r1, r1, #1
	movs r0, #1
	subs r0, r0, r1
	muls r0, r3, r0
	str r0, [r4, #0x5c]
	movs r1, #0
	cmp r0, #0
	ble _0809A964
	movs r1, #1
_0809A964:
	adds r2, r1, #0
	cmp r2, #0
	beq _0809A980
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0809A986
	.align 2, 0
_0809A974: .4byte RNG_0202f388
_0809A978: .4byte 0x000343FD
_0809A97C: .4byte 0x00269EC3
_0809A980:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A986:
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
	movs r1, #0xf2
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809A9B2:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, _0809AA08 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A9FC
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
	ldr r1, _0809AA0C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0809A9FC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0809AA02:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0809AA08: .4byte 0xFFFF3000
_0809AA0C: .4byte gEnemyFnTable

