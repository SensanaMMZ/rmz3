	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a8c74
FUN_080a8c74: @ 0x080A8C74
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldr r1, _080A8CBC @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r7, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	movs r1, #0xb6
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A8CC0
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A8CC6
	.align 2, 0
_080A8CBC: .4byte gProjectileFnTable
_080A8CC0:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A8CC6:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, _080A8D1C @ =0x0000FFFF
	strh r0, [r1]
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r0]
	str r1, [r6, #0x54]
	adds r0, #4
	ldr r0, [r0]
	str r0, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xb4
	str r1, [r0]
	adds r1, r6, #0
	adds r1, #0xb8
	ldr r0, [r6, #0x58]
	str r0, [r1]
	ldrb r0, [r6, #0x10]
	cmp r0, #2
	bne _080A8D24
	ldr r0, [r5, #0x5c]
	str r0, [r6, #0x5c]
	movs r0, #0
	str r0, [r6, #0x60]
	adds r1, #4
	ldr r0, _080A8D20 @ =0x0000FFF0
	b _080A8D34
	.align 2, 0
_080A8D1C: .4byte 0x0000FFFF
_080A8D20: .4byte 0x0000FFF0
_080A8D24:
	ldr r0, [r5, #0x5c]
	str r0, [r6, #0x5c]
	movs r0, #0xe0
	lsls r0, r0, #2
	str r0, [r6, #0x60]
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r0, _080A8D68 @ =0x0000FFE8
_080A8D34:
	strh r0, [r1]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A8D6C @ =0x0836C04C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	movs r0, #2
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	bl Projectile26_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A8D68: .4byte 0x0000FFE8
_080A8D6C: .4byte 0x0836C04C
