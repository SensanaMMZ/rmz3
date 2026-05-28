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
