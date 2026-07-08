	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r3, #0
	adds r2, r0, #0
	orrs r2, r1
	movs r0, #2
	orrs r2, r0
	orrs r2, r3
	strb r2, [r4, #0xa]
	ldrb r1, [r4, #0x10]
	cmp r1, #0
	bne _0803CEE6
	movs r0, #0xef
	ands r2, r0
	strb r2, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _0803CF06
_0803CEE6:
	movs r1, #1
	movs r0, #0x10
	orrs r2, r0
	strb r2, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_0803CF06:
	ldr r1, _0803CF2C @ =gWeaponFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl Weapon16_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0803CF2C: .4byte gWeaponFnTable
