	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r7, [r6, #0x28]
	ldr r1, _080A8A80 @ =gProjectileFnTable
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
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A8A84 @ =0x00005B01
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r7, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A8A88
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A8A8E
	.align 2, 0
_080A8A80: .4byte gProjectileFnTable
_080A8A84: .4byte 0x00005B01
_080A8A88:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A8A8E:
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
	adds r4, r6, #0
	adds r4, #0xc0
	ldr r0, _080A8AD4 @ =0x0000FFFF
	strh r0, [r4]
	movs r0, #0x48
	bl PlaySound
	strh r0, [r4]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A8AD8
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r0, #0xe0
	lsls r0, r0, #2
	b _080A8AE2
	.align 2, 0
_080A8AD4: .4byte 0x0000FFFF
_080A8AD8:
	ldr r0, [r6, #0x54]
	ldr r1, _080A8B3C @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _080A8B40 @ =0xFFFFFC80
_080A8AE2:
	str r0, [r6, #0x5c]
	ldr r0, [r6, #0x58]
	ldr r1, _080A8B44 @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r5, #0
	str r5, [r6, #0x60]
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r0, _080A8B48 @ =0x0000FFF0
	strh r0, [r1]
	subs r1, #8
	ldr r0, [r6, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r6, #0x58]
	str r0, [r1]
	adds r1, r7, #0
	adds r1, #0xcf
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A8B4C @ =0x0836C04C
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
_080A8B3C: .4byte 0xFFFFF000
_080A8B40: .4byte 0xFFFFFC80
_080A8B44: .4byte 0xFFFFE800
_080A8B48: .4byte 0x0000FFF0
_080A8B4C: .4byte 0x0836C04C
