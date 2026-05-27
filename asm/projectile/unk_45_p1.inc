	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b18d4
FUN_080b18d4: @ 0x080B18D4
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	lsls r2, r2, #0x18
	lsrs r6, r2, #0x18
	ldr r0, _080B192C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B1922
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B1930 @ =gProjectileFnTable
	movs r1, #0x2d
	strb r1, [r3, #9]
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	strb r6, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	ldr r0, [r5]
	str r0, [r3, #0x64]
	ldr r0, [r5, #4]
	str r0, [r3, #0x68]
_080B1922:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080B192C: .4byte gProjectileHeaderPtr
_080B1930: .4byte gProjectileFnTable

	thumb_func_start FUN_080b1934
FUN_080b1934: @ 0x080B1934
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r4, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _080B1988 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B197E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B198C @ =gProjectileFnTable
	movs r1, #0x2d
	strb r1, [r3, #9]
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r6, [r3, #0x28]
_080B197E:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080B1988: .4byte gProjectileHeaderPtr
_080B198C: .4byte gProjectileFnTable

	thumb_func_start FUN_080b1990
FUN_080b1990: @ 0x080B1990
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r4, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _080B19E4 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B19DA
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B19E8 @ =gProjectileFnTable
	movs r1, #0x2d
	strb r1, [r3, #9]
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #2
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r6, [r3, #0x28]
_080B19DA:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080B19E4: .4byte gProjectileHeaderPtr
_080B19E8: .4byte gProjectileFnTable

	thumb_func_start FUN_080b19ec
FUN_080b19ec: @ 0x080B19EC
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r4, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _080B1A40 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B1A36
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B1A44 @ =gProjectileFnTable
	movs r1, #0x2d
	strb r1, [r3, #9]
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #3
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r6, [r3, #0x28]
_080B1A36:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080B1A40: .4byte gProjectileHeaderPtr
_080B1A44: .4byte gProjectileFnTable

	thumb_func_start FUN_080b1a48
FUN_080b1a48: @ 0x080B1A48
	push {r4, r5, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r1, r0
	movs r0, #2
	orrs r1, r0
	strb r1, [r4, #0xa]
	ldrb r5, [r4, #0x10]
	cmp r5, #0
	bne _080B1A9C
	movs r0, #0xef
	ands r1, r0
	strb r1, [r4, #0xa]
	movs r2, #1
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldr r1, _080B1A98 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
	strb r5, [r4, #0xf]
	b _080B1B0C
	.align 2, 0
_080B1A98: .4byte gProjectileFnTable
_080B1A9C:
	cmp r5, #1
	bne _080B1ACC
	movs r2, #0
	movs r0, #0xef
	ands r1, r0
	strb r1, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldr r1, _080B1AC8 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r5, [r4, #0xc]
	b _080B1B00
	.align 2, 0
_080B1AC8: .4byte gProjectileFnTable
_080B1ACC:
	cmp r5, #2
	beq _080B1AD4
	cmp r5, #3
	bne _080B1B0C
_080B1AD4:
	movs r2, #0
	movs r0, #0xef
	ands r1, r0
	strb r1, [r4, #0xa]
	movs r3, #1
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	mov r1, ip
	strb r0, [r1]
	ldr r1, _080B1B24 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r3, [r4, #0xc]
_080B1B00:
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r5, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
_080B1B0C:
	movs r0, #0xff
	strb r0, [r4, #0x12]
	adds r1, r4, #0
	adds r1, #0xbc
	movs r0, #0
	strb r0, [r1]
	adds r0, r4, #0
	bl FUN_080b1b28
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B1B24: .4byte gProjectileFnTable
