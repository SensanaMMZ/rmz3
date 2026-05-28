	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile20_Init
Projectile20_Init: @ 0x080A504C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080A50AC @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080A50B0 @ =0x0836BAE8
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
	ldr r1, _080A50B4 @ =0x0836BAA0
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080A50B8 @ =nop_080a5048
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile20_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A50AC: .4byte gProjectileFnTable
_080A50B0: .4byte 0x0836BAE8
_080A50B4: .4byte 0x0836BAA0
_080A50B8: .4byte nop_080a5048

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
