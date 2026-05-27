	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile32_Die
Projectile32_Die: @ 0x080AAEB4
	push {lr}
	ldr r2, _080AAEC8 @ =0x0836C408
	ldrb r1, [r0, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080AAEC8: .4byte 0x0836C408

