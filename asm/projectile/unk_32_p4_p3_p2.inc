	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080abdf8
FUN_080abdf8: @ 0x080ABDF8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _080ABE48 @ =0x0836C4BC
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #0x40
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080ABE4C @ =FUN_080ac1a4
	str r0, [r5, #0x24]
	ldr r1, _080ABE50 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Projectile32_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080ABE48: .4byte 0x0836C4BC
_080ABE4C: .4byte FUN_080ac1a4
_080ABE50: .4byte gProjectileFnTable
