	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile20_Update
Projectile20_Update: @ 0x080A50BC
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A50D6
	ldrb r0, [r4, #0xd]
	cmp r0, #7
	beq _080A50D6
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A50D6:
	ldr r1, _080A50FC @ =0x0836BA50
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080A5100 @ =0x0836BA78
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A50FC: .4byte 0x0836BA50
_080A5100: .4byte 0x0836BA78
