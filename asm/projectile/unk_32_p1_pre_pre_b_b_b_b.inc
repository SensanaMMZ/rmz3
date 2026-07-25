	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080aae34
FUN_080aae34: @ 0x080AAE34
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _080AAE4C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	bne _080AAE50
	movs r0, #0
	b _080AAE7A
	.align 2, 0
_080AAE4C: .4byte gProjectileHeaderPtr
_080AAE50:
	adds r0, r4, #0
	adds r0, #0x25
	movs r3, #0
	movs r2, #8
	strb r2, [r0]
	ldr r0, _080AAE80 @ =gProjectileFnTable
	movs r1, #0x20
	strb r1, [r4, #9]
	adds r0, #0x80
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r2, [r4, #0x10]
	strb r0, [r4, #0x11]
	str r5, [r4, #0x28]
	adds r0, r4, #0
_080AAE7A:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080AAE80: .4byte gProjectileFnTable
