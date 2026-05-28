	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createCopyXSonicBoom
createCopyXSonicBoom: @ 0x080A8118
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r6, r1, #0x18
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _080A8168 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A8160
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A816C @ =gProjectileFnTable
	movs r0, #0x18
	strb r0, [r3, #9]
	ldr r0, [r1, #0x60]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r6, [r3, #0x10]
	strb r5, [r3, #0x11]
	str r4, [r3, #0x28]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
_080A8160:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A8168: .4byte gProjectileHeaderPtr
_080A816C: .4byte gProjectileFnTable
