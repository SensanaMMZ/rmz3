	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a5bb4
FUN_080a5bb4: @ 0x080A5BB4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	adds r6, r1, #0
	movs r4, #0
	movs r5, #0
	ldr r0, _080A5C08 @ =gProjectileFnTable
	mov r8, r0
_080A5BC6:
	ldr r0, _080A5C0C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r1, r0, #0
	cmp r1, #0
	beq _080A5BF8
	adds r2, r1, #0
	adds r2, #0x25
	movs r0, #8
	strb r0, [r2]
	movs r0, #0x15
	strb r0, [r1, #9]
	mov r2, r8
	ldr r0, [r2, #0x54]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r5, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r5, [r0]
	strb r5, [r1, #0x10]
	strb r4, [r1, #0x12]
	str r7, [r1, #0x54]
	str r6, [r1, #0x58]
_080A5BF8:
	adds r4, #1
	cmp r4, #4
	ble _080A5BC6
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A5C08: .4byte gProjectileFnTable
_080A5C0C: .4byte gProjectileHeaderPtr

	thumb_func_start nop_080a5c10
nop_080a5c10: @ 0x080A5C10
	bx lr
	.align 2, 0

	thumb_func_start PantheonAquaModProjectile_Init
PantheonAquaModProjectile_Init: @ 0x080A5C14
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080A5C74 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080A5C78 @ =0x0836BB48
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
	ldr r1, _080A5C7C @ =0x0836BB18
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080A5C80 @ =nop_080a5c10
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl PantheonAquaModProjectile_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A5C74: .4byte gProjectileFnTable
_080A5C78: .4byte 0x0836BB48
_080A5C7C: .4byte 0x0836BB18
_080A5C80: .4byte nop_080a5c10

	thumb_func_start PantheonAquaModProjectile_Update
PantheonAquaModProjectile_Update: @ 0x080A5C84
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080A5CB0 @ =0x0836BB00
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080A5CB4 @ =0x0836BB0C
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
_080A5CB0: .4byte 0x0836BB00
_080A5CB4: .4byte 0x0836BB0C

	thumb_func_start PantheonAquaModProjectile_Die
PantheonAquaModProjectile_Die: @ 0x080A5CB8
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
	ldr r1, _080A5CF4 @ =gProjectileFnTable
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
_080A5CF4: .4byte gProjectileFnTable
