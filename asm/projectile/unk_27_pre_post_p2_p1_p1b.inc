	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_080a946c
FUN_080a946c: @ 0x080A946C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r1, _080A94AC @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r4, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A94B0 @ =0x00005C01
	adds r0, r6, #0
	bl SetMotion
	ldrb r2, [r6, #0x11]
	cmp r2, #0
	beq _080A94B4
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A94BA
	.align 2, 0
_080A94AC: .4byte gProjectileFnTable
_080A94B0: .4byte 0x00005C01
_080A94B4:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A94BA:
	strb r0, [r6, #0xa]
	movs r1, #1
	ands r1, r2
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
	beq _080A94F8
	ldr r0, [r6, #0x54]
	ldr r1, _080A94F0 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _080A94F4 @ =0xFFFFFF00
	b _080A9506
	.align 2, 0
_080A94F0: .4byte 0xFFFFF000
_080A94F4: .4byte 0xFFFFFF00
_080A94F8:
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r0, #0x80
	lsls r0, r0, #1
_080A9506:
	str r0, [r6, #0x5c]
	movs r5, #0
	strb r5, [r6, #0x12]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A9538 @ =0x0836C138
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r0, r6, #0
	bl Projectile27_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A9538: .4byte 0x0836C138

	thumb_func_start FUN_080a953c
FUN_080a953c: @ 0x080A953C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080A9586
	ldrb r0, [r6, #0x11]
	cmp r0, #0
	beq _080A9558
	ldr r0, [r6, #0x54]
	ldr r1, _080A9554 @ =0xFFFFE000
	b _080A955E
	.align 2, 0
_080A9554: .4byte 0xFFFFE000
_080A9558:
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #6
_080A955E:
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r5, #0
	strb r5, [r6, #0xe]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A95F8 @ =0x0836C138
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	strb r5, [r6, #0x12]
_080A9586:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xb
	bne _080A95C2
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A95FC @ =0x0836C168
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
_080A95C2:
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	bne _080A95D2
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A95D2:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080A95F2
	ldr r1, _080A9600 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080A95F2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A95F8: .4byte 0x0836C138
_080A95FC: .4byte 0x0836C168
_080A9600: .4byte gProjectileFnTable

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
