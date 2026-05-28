	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e1ef8
FUN_080e1ef8: @ 0x080E1EF8
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	adds r3, r4, #0
	adds r3, #0xc0
	ldrb r1, [r3]
	adds r2, r1, #1
	adds r0, r2, #0
	asrs r0, r0, #5
	lsls r0, r0, #5
	subs r0, r2, r0
	strb r0, [r3]
	adds r6, r4, #0
	adds r6, #0xb4
	ldr r1, [r6]
	ldr r0, [r4, #0x64]
	subs r3, r1, r0
	adds r5, r4, #0
	adds r5, #0xb8
	ldr r1, [r5]
	ldr r0, [r4, #0x68]
	subs r2, r1, r0
	movs r1, #0x80
	lsls r1, r1, #2
	adds r0, r3, r1
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bhi _080E1F5C
	movs r7, #0x80
	lsls r7, r7, #2
	adds r0, r2, r7
	cmp r0, r1
	bhi _080E1F5C
	adds r0, r3, #0
	muls r0, r3, r0
	adds r1, r2, #0
	muls r1, r2, r1
	adds r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #0xb
	cmp r0, r1
	bgt _080E1F5C
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	ldr r0, [r6]
	str r0, [r4, #0x64]
	ldr r0, [r5]
	str r0, [r4, #0x68]
	b _080E1FAE
_080E1F5C:
	adds r0, r3, #0
	adds r1, r2, #0
	bl CalcAngle
	ldr r3, _080E1FB4 @ =gSineTable
	adds r1, r0, #0
	adds r1, #0x40
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r3
	movs r5, #0
	ldrsh r2, [r1, r5]
	lsls r2, r2, #1
	ldr r1, [r4, #0x64]
	adds r1, r1, r2
	str r1, [r4, #0x64]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r7, #0
	ldrsh r1, [r0, r7]
	lsls r1, r1, #1
	ldr r0, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x68]
	adds r5, r4, #0
	adds r5, #0xc1
	ldrb r0, [r5]
	subs r0, #1
	strb r0, [r5]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080E1FAE
	adds r0, r4, #0
	adds r0, #0x54
	movs r1, #0
	bl FUN_080bfc94
	movs r0, #0x20
	strb r0, [r5]
_080E1FAE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E1FB4: .4byte gSineTable

	thumb_func_start FUN_080e1fb8
FUN_080e1fb8: @ 0x080E1FB8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _080E1FD4
	adds r0, r4, #0
	adds r0, #0x54
	movs r1, #0
	bl FUN_080bfce8
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080E1FD4:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080E1FE2
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080E1FE2:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_080e1fe8
FUN_080e1fe8: @ 0x080E1FE8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r0, #0xbc
	ldr r5, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _080E2012
	adds r0, r5, #0
	adds r0, #0xb4
	ldrh r1, [r0, #4]
	adds r1, #3
	strh r1, [r0, #4]
	adds r0, r5, #0
	bl IsDoubleHP
	lsls r0, r0, #0x18
	movs r3, #4
	cmp r0, #0
	beq _080E2026
	movs r3, #8
	b _080E2026
_080E2012:
	adds r0, r5, #0
	adds r0, #0xb4
	ldrh r1, [r0, #4]
	adds r1, #5
	strh r1, [r0, #4]
	adds r0, r5, #0
	bl GetMaxHP
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
_080E2026:
	ldr r0, _080E2094 @ =gMission
	ldr r0, [r0]
	adds r1, r0, #0
	adds r1, #0x4c
	ldrb r0, [r1]
	cmp r0, #0x62
	bhi _080E2038
	adds r0, #1
	strb r0, [r1]
_080E2038:
	ldr r1, _080E2098 @ =gUnlockedElfPtr
	ldr r2, _080E209C @ =0x00000121
	adds r0, r5, r2
	ldrb r0, [r0]
	ldr r1, [r1]
	adds r1, r1, r0
	ldrb r0, [r1]
	movs r2, #2
	orrs r0, r2
	strb r0, [r1]
	adds r4, r5, #0
	adds r4, #0xa4
	ldrh r0, [r4]
	adds r0, r0, r3
	strh r0, [r4]
	adds r0, r5, #0
	bl GetMaxHP
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r2, #0
	ldrsh r1, [r4, r2]
	cmp r0, r1
	bge _080E2074
	adds r0, r5, #0
	bl GetMaxHP
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	strh r0, [r4]
_080E2074:
	ldr r1, _080E20A0 @ =gElfFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl Elf0_Die
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080E2094: .4byte gMission
_080E2098: .4byte gUnlockedElfPtr
_080E209C: .4byte 0x00000121
_080E20A0: .4byte gElfFnTable



