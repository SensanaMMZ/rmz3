	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080affe4
FUN_080affe4: @ 0x080AFFE4
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r4, r1, #0
	lsls r2, r2, #0x10
	lsrs r6, r2, #0x10
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	ldr r0, _080B0040 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B0038
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B0044 @ =gProjectileFnTable
	movs r1, #0x29
	strb r1, [r3, #9]
	adds r0, #0xa4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #6
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	adds r0, r3, #0
	adds r0, #0xbc
	strh r6, [r0]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r7, [r3, #0x28]
_080B0038:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080B0040: .4byte gProjectileHeaderPtr
_080B0044: .4byte gProjectileFnTable

	thumb_func_start FUN_080b0048
FUN_080b0048: @ 0x080B0048
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	ldr r0, _080B0094 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B008C
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B0098 @ =gProjectileFnTable
	movs r1, #0x29
	strb r1, [r3, #9]
	adds r0, #0xa4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #7
	strb r0, [r3, #0x10]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r5, [r3, #0x28]
_080B008C:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080B0094: .4byte gProjectileHeaderPtr
_080B0098: .4byte gProjectileFnTable

	thumb_func_start FUN_080b009c
FUN_080b009c: @ 0x080B009C
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _080B00DC @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080B00D2
	adds r0, #0x25
	movs r3, #0
	movs r2, #8
	strb r2, [r0]
	ldr r0, _080B00E0 @ =gProjectileFnTable
	movs r1, #0x29
	strb r1, [r4, #9]
	adds r0, #0xa4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r2, [r4, #0x10]
	str r5, [r4, #0x28]
_080B00D2:
	adds r0, r4, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080B00DC: .4byte gProjectileHeaderPtr
_080B00E0: .4byte gProjectileFnTable

	thumb_func_start OmegaZXProjectile_Init
OmegaZXProjectile_Init: @ 0x080B00E4
	push {lr}
	ldr r2, _080B0110 @ =gProjectileFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r2, #1
	str r2, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	str r1, [r0, #0x14]
	ldrb r1, [r0, #0x10]
	movs r2, #0
	strb r1, [r0, #0xd]
	strb r2, [r0, #0xe]
	strb r2, [r0, #0xf]
	movs r1, #0xff
	strb r1, [r0, #0x12]
	bl OmegaZXProjectile_Update
	pop {r0}
	bx r0
	.align 2, 0
_080B0110: .4byte gProjectileFnTable
