	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a5f00
FUN_080a5f00: @ 0x080A5F00
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _080A5F4C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A5F44
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A5F50 @ =gProjectileFnTable
	movs r0, #0x16
	strb r0, [r3, #9]
	ldr r0, [r1, #0x58]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	str r4, [r3, #0x28]
	adds r1, #0x94
	strb r0, [r1]
	adds r0, r3, #0
	adds r0, #0xb5
	strb r5, [r0]
_080A5F44:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080A5F4C: .4byte gProjectileHeaderPtr
_080A5F50: .4byte gProjectileFnTable

	thumb_func_start FUN_080a5f54
FUN_080a5f54: @ 0x080A5F54
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	ldr r0, _080A5FBC @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	mov ip, r0
	cmp r0, #0
	beq _080A5FB2
	mov r1, ip
	adds r1, #0x25
	movs r3, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A5FC0 @ =gProjectileFnTable
	movs r0, #0x16
	mov r2, ip
	strb r0, [r2, #9]
	ldr r0, [r1, #0x58]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	movs r2, #0
	mov r0, ip
	strh r3, [r0, #0x20]
	adds r0, #0x22
	strb r2, [r0]
	movs r0, #5
	mov r1, ip
	strb r0, [r1, #0x10]
	ldr r0, [r6]
	ldr r1, [r6, #4]
	mov r3, ip
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	mov r0, ip
	adds r0, #0xb4
	strb r4, [r0]
	adds r0, #1
	strb r5, [r0]
	adds r0, #1
	strb r2, [r0]
	str r7, [r3, #0x28]
_080A5FB2:
	mov r0, ip
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080A5FBC: .4byte gProjectileHeaderPtr
_080A5FC0: .4byte gProjectileFnTable
