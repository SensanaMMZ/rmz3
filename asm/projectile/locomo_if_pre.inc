	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a7c60
FUN_080a7c60: @ 0x080A7C60
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080A7CA8 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A7CA0
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A7CAC @ =gProjectileFnTable
	movs r0, #0x17
	strb r0, [r3, #9]
	ldr r0, [r1, #0x5c]
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
_080A7CA0:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A7CA8: .4byte gProjectileHeaderPtr
_080A7CAC: .4byte gProjectileFnTable

	thumb_func_start FUN_080a7cb0
FUN_080a7cb0: @ 0x080A7CB0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080A7CF8 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A7CF2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A7CFC @ =gProjectileFnTable
	movs r0, #0x17
	strb r0, [r3, #9]
	ldr r0, [r1, #0x5c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	str r5, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r4, [r3, #0x12]
_080A7CF2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A7CF8: .4byte gProjectileHeaderPtr
_080A7CFC: .4byte gProjectileFnTable

	thumb_func_start FUN_080a7d00
FUN_080a7d00: @ 0x080A7D00
	bx lr
	.align 2, 0

	thumb_func_start Projectile23_Init
Projectile23_Init: @ 0x080A7D04
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080A7D64 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080A7D68 @ =0x0836BEC4
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
	ldr r1, _080A7D6C @ =0x0836BE64
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080A7D70 @ =FUN_080a7d00
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile23_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A7D64: .4byte gProjectileFnTable
_080A7D68: .4byte 0x0836BEC4
_080A7D6C: .4byte 0x0836BE64
_080A7D70: .4byte FUN_080a7d00

	thumb_func_start Projectile23_Update
Projectile23_Update: @ 0x080A7D74
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080A7DA0 @ =0x0836BE4C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080A7DA4 @ =0x0836BE58
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
_080A7DA0: .4byte 0x0836BE4C
_080A7DA4: .4byte 0x0836BE58

	thumb_func_start Projectile23_Die
Projectile23_Die: @ 0x080A7DA8
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
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080A7DE4 @ =gProjectileFnTable
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
_080A7DE4: .4byte gProjectileFnTable
