	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_080a9604
FUN_080a9604: @ 0x080A9604
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldr r1, _080A964C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl InitRotatableMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r7, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A9650 @ =0x00005C02
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A9654
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A965A
	.align 2, 0
_080A964C: .4byte gProjectileFnTable
_080A9650: .4byte 0x00005C02
_080A9654:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A965A:
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
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A9690
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r0, #0x80
	lsls r0, r0, #3
	b _080A969A
_080A9690:
	ldr r0, [r6, #0x54]
	ldr r1, _080A96E8 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _080A96EC @ =0xFFFFFC00
_080A969A:
	str r0, [r6, #0x5c]
	adds r1, r6, #0
	adds r1, #0x24
	movs r5, #0
	movs r0, #0xc0
	strb r0, [r1]
	ldr r1, [r6, #0x58]
	ldr r0, _080A96F0 @ =0xFFFFE800
	adds r1, r1, r0
	str r1, [r6, #0x58]
	ldr r0, [r6, #0x54]
	bl FUN_08009f6c
	adds r1, r6, #0
	adds r1, #0xb8
	str r0, [r1]
	str r5, [r6, #0x60]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A96F4 @ =0x0836C198
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r0, r6, #0
	bl Projectile27_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A96E8: .4byte 0xFFFFF000
_080A96EC: .4byte 0xFFFFFC00
_080A96F0: .4byte 0xFFFFE800
_080A96F4: .4byte 0x0836C198
