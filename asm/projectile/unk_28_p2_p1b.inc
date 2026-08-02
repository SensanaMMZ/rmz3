	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a9ef8
FUN_080a9ef8: @ 0x080A9EF8
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r0, _080A9F28 @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _080A9F30
	ldr r1, _080A9F2C @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl Projectile28_Die
	b _080A9FD8
	.align 2, 0
_080A9F28: .4byte gStageRun
_080A9F2C: .4byte gProjectileFnTable
_080A9F30:
	ldrb r6, [r5, #0xd]
	cmp r6, #1
	beq _080A9F84
	cmp r6, #1
	bgt _080A9F40
	cmp r6, #0
	beq _080A9F46
	b _080A9FD2
_080A9F40:
	cmp r6, #2
	beq _080A9FB0
	b _080A9FD2
_080A9F46:
	ldrb r0, [r5, #0x13]
	adds r0, #4
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x1f
	bls _080A9FD2
	ldrb r0, [r5, #0xd]
	adds r0, #1
	strb r0, [r5, #0xd]
	movs r0, #0x78
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080A9F80 @ =0x0836C25C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	b _080A9FD2
	.align 2, 0
_080A9F80: .4byte sCollisions+(24*2)
_080A9F84:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080A9FD2
	ldrb r0, [r5, #0xd]
	adds r0, #1
	strb r0, [r5, #0xd]
	adds r0, r5, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	b _080A9FD2
_080A9FB0:
	ldrb r0, [r5, #0x13]
	subs r0, #4
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A9FD2
	ldr r1, _080A9FE0 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r6, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl Projectile28_Die
_080A9FD2:
	ldrb r0, [r5, #0xf]
	adds r0, #1
	strb r0, [r5, #0xf]
_080A9FD8:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A9FE0: .4byte gProjectileFnTable
