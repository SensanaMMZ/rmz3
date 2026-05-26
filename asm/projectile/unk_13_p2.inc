	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile13_Init
Projectile13_Init: @ 0x0809FAF4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _0809FB54 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _0809FB58 @ =0x0836B0C8
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
	ldr r1, _0809FB5C @ =0x0836B050
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _0809FB60 @ =nop_0809faf0
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile13_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809FB54: .4byte gProjectileFnTable
_0809FB58: .4byte 0x0836B0C8
_0809FB5C: .4byte 0x0836B050
_0809FB60: .4byte nop_0809faf0

	thumb_func_start Projectile13_Update
Projectile13_Update: @ 0x0809FB64
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _0809FB90 @ =0x0836B018
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0809FB94 @ =0x0836B034
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
_0809FB90: .4byte 0x0836B018
_0809FB94: .4byte 0x0836B034

	thumb_func_start Projectile13_Die
Projectile13_Die: @ 0x0809FB98
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _0809FBD4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0809FBD4: .4byte gProjectileFnTable
