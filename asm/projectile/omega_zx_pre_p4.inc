	.include "asm/macros.inc"

	.syntax unified

	.text

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
