	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a2ea0
FUN_080a2ea0: @ 0x080A2EA0
	push {r4, r5, r6, lr}
	movs r5, #0
	ldr r6, _080A2EE0 @ =gProjectileFnTable
	movs r4, #4
_080A2EA8:
	ldr r0, _080A2EE4 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2ED4
	adds r2, r1, #0
	adds r2, #0x25
	movs r0, #8
	strb r0, [r2]
	movs r0, #0x12
	strb r0, [r1, #9]
	ldr r0, [r6, #0x48]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r5, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r5, [r0]
	movs r0, #2
	strb r0, [r1, #0x10]
_080A2ED4:
	subs r4, #1
	cmp r4, #0
	bge _080A2EA8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A2EE0: .4byte gProjectileFnTable
_080A2EE4: .4byte gProjectileHeaderPtr

	thumb_func_start FUN_080a2ee8
FUN_080a2ee8: @ 0x080A2EE8
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080A2F2C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A2F24
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A2F30 @ =gProjectileFnTable
	movs r0, #0x12
	strb r0, [r3, #9]
	ldr r0, [r1, #0x48]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
_080A2F24:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A2F2C: .4byte gProjectileHeaderPtr
_080A2F30: .4byte gProjectileFnTable

	thumb_func_start FUN_080a2f34
FUN_080a2f34: @ 0x080A2F34
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r1, #0
	movs r5, #0
	movs r6, #0
	ldr r1, _080A2F98 @ =0xFFFFE400
	adds r4, r0, r1
	ldr r2, _080A2F9C @ =gProjectileFnTable
	mov r8, r2
_080A2F48:
	ldr r0, _080A2FA0 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2F80
	adds r2, r1, #0
	adds r2, #0x25
	movs r0, #8
	strb r0, [r2]
	movs r0, #0x12
	strb r0, [r1, #9]
	mov r2, r8
	ldr r0, [r2, #0x48]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r6, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r6, [r0]
	strb r6, [r1, #0x10]
	str r4, [r1, #0x54]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r7, r2
	str r0, [r1, #0x58]
	strb r5, [r1, #0x12]
_080A2F80:
	movs r0, #0xe0
	lsls r0, r0, #6
	adds r4, r4, r0
	adds r5, #1
	cmp r5, #1
	ble _080A2F48
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A2F98: .4byte 0xFFFFE400
_080A2F9C: .4byte gProjectileFnTable
_080A2FA0: .4byte gProjectileHeaderPtr
