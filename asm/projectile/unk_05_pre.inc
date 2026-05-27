	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0809d904
FUN_0809d904: @ 0x0809D904
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	adds r6, r2, #0
	adds r7, r3, #0
	ldr r0, _0809D95C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0809D954
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _0809D960 @ =gProjectileFnTable
	movs r0, #5
	strb r0, [r3, #9]
	ldr r0, [r1, #0x14]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	movs r0, #1
	strb r0, [r3, #0x10]
	adds r0, r3, #0
	adds r0, #0xb8
	str r5, [r0]
	adds r0, #4
	str r6, [r0]
	str r7, [r3, #0x28]
_0809D954:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0809D95C: .4byte gProjectileHeaderPtr
_0809D960: .4byte gProjectileFnTable

	thumb_func_start Projectile5_Init
Projectile5_Init: @ 0x0809D964
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r6, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _0809D9B8 @ =sCollisions
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	str r6, [r5, #0x24]
	ldr r1, _0809D9BC @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r6, [r4, #0xd]
	strb r6, [r4, #0xe]
	strb r6, [r4, #0xf]
	adds r0, r4, #0
	bl Projectile5_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809D9B8: .4byte sCollisions
_0809D9BC: .4byte gProjectileFnTable
