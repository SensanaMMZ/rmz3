	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile30_Init
Projectile30_Init: @ 0x080AA63C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080AA69C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080AA6A0 @ =0x0836C304
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
	ldr r1, _080AA6A4 @ =0x0836C2EC
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080AA6A8 @ =nop_080aa638
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile30_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AA69C: .4byte gProjectileFnTable
_080AA6A0: .4byte 0x0836C304
_080AA6A4: .4byte 0x0836C2EC
_080AA6A8: .4byte nop_080aa638
