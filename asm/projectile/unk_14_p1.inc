	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a0888
FUN_080a0888: @ 0x080A0888
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	adds r7, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	ldr r0, _080A08D8 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A08D0
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A08DC @ =gProjectileFnTable
	movs r0, #0xe
	strb r0, [r3, #9]
	ldr r0, [r1, #0x38]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #4
	strb r0, [r3, #0x10]
	str r6, [r3, #0x54]
	str r7, [r3, #0x58]
	strb r5, [r3, #0x12]
	strb r4, [r3, #0x13]
_080A08D0:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A08D8: .4byte gProjectileHeaderPtr
_080A08DC: .4byte gProjectileFnTable

	thumb_func_start FUN_080a08e0
FUN_080a08e0: @ 0x080A08E0
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r5, r1, #0
	adds r6, r2, #0
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	ldr r0, _080A092C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A0924
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A0930 @ =gProjectileFnTable
	movs r0, #0xe
	strb r0, [r3, #9]
	ldr r0, [r1, #0x38]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	str r5, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r4, [r3, #0x12]
	str r7, [r3, #0x28]
_080A0924:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A092C: .4byte gProjectileHeaderPtr
_080A0930: .4byte gProjectileFnTable

	thumb_func_start deathtanz_080a0934
deathtanz_080a0934: @ 0x080A0934
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	adds r6, r1, #0
	adds r7, r2, #0
	ldr r0, [sp, #0x18]
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	ldr r0, _080A0998 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A098C
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A099C @ =gProjectileFnTable
	movs r0, #0xe
	strb r0, [r3, #9]
	ldr r0, [r1, #0x38]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	str r6, [r3, #0x54]
	str r7, [r3, #0x58]
	strb r4, [r3, #0x12]
	mov r0, r8
	str r0, [r3, #0x28]
	adds r0, r3, #0
	adds r0, #0xbc
	strb r5, [r0]
_080A098C:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A0998: .4byte gProjectileHeaderPtr
_080A099C: .4byte gProjectileFnTable

	thumb_func_start deathtanz_080a09a0
deathtanz_080a09a0: @ 0x080A09A0
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r5, r1, #0
	adds r6, r2, #0
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	ldr r0, _080A09EC @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A09E6
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A09F0 @ =gProjectileFnTable
	movs r0, #0xe
	strb r0, [r3, #9]
	ldr r0, [r1, #0x38]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #2
	strb r0, [r3, #0x10]
	str r5, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r4, [r3, #0x12]
	str r7, [r3, #0x28]
_080A09E6:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A09EC: .4byte gProjectileHeaderPtr
_080A09F0: .4byte gProjectileFnTable

	thumb_func_start deathtanz_080a09f4
deathtanz_080a09f4: @ 0x080A09F4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	adds r6, r1, #0
	adds r7, r2, #0
	ldr r0, [sp, #0x18]
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r0, _080A0A54 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A0A48
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A0A58 @ =gProjectileFnTable
	movs r0, #0xe
	strb r0, [r3, #9]
	ldr r0, [r1, #0x38]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #3
	strb r0, [r3, #0x10]
	str r6, [r3, #0x54]
	str r7, [r3, #0x58]
	strb r5, [r3, #0x12]
	strb r4, [r3, #0x13]
	mov r0, r8
	str r0, [r3, #0x28]
_080A0A48:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A0A54: .4byte gProjectileHeaderPtr
_080A0A58: .4byte gProjectileFnTable
_080A0A5C:
	.byte 0x70, 0x47, 0x00, 0x00

	thumb_func_start Projectile14_Init
Projectile14_Init: @ 0x080A0A60
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080A0AE0 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080A0AE4 @ =0x0836B20C
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _080A0AE8 @ =0x0836B11C
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080A0AEC @ =0x080A0A5D
	str r0, [r5, #0x24]
	ldr r0, [r4, #0x28]
	adds r1, r4, #0
	adds r1, #0xb4
	adds r0, #0xb4
	ldr r0, [r0]
	str r0, [r1]
	adds r5, #0x44
	ldr r0, [r4, #0x58]
	asrs r0, r0, #8
	str r0, [r5]
	movs r1, #0xa0
	bl __divsi3
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #0xd
	str r1, [r5]
	adds r0, r4, #0
	bl Projectile14_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A0AE0: .4byte gProjectileFnTable
_080A0AE4: .4byte 0x0836B20C
_080A0AE8: .4byte 0x0836B11C
_080A0AEC: .4byte 0x080A0A5D

	thumb_func_start Projectile14_Update
Projectile14_Update: @ 0x080A0AF0
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080A0B1C @ =0x0836B0F4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080A0B20 @ =0x0836B108
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A0B1C: .4byte 0x0836B0F4
_080A0B20: .4byte 0x0836B108

	thumb_func_start Projectile14_Die
Projectile14_Die: @ 0x080A0B24
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #1
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r1, _080A0B68 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A0B68: .4byte gProjectileFnTable
