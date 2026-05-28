	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start PantheonAquaModProjectile_Init
PantheonAquaModProjectile_Init: @ 0x080A5C14
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080A5C74 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080A5C78 @ =0x0836BB48
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
	ldr r1, _080A5C7C @ =0x0836BB18
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080A5C80 @ =nop_080a5c10
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl PantheonAquaModProjectile_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A5C74: .4byte gProjectileFnTable
_080A5C78: .4byte 0x0836BB48
_080A5C7C: .4byte 0x0836BB18
_080A5C80: .4byte nop_080a5c10
