	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r4, [r5, #0x28]
	ldr r1, _0809C2D4 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	movs r1, #0xe9
	lsls r1, r1, #8
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	movs r1, #0
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	subs r2, #1
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	movs r0, #0xde
	lsls r0, r0, #4
	adds r4, r4, r0
	ldrb r0, [r5, #0x10]
	adds r4, r4, r0
	ldrb r1, [r4]
	strb r1, [r5, #0x12]
	adds r1, #5
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r5, #0
	bl ForceEntityPalette
	movs r0, #0xd8
	lsls r0, r0, #8
	str r0, [r5, #0x54]
	ldrb r1, [r5, #0x10]
	lsls r1, r1, #4
	movs r0, #0x30
	subs r0, r0, r1
	lsls r0, r0, #8
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x10]
	cmp r0, #3
	bne _0809C2C6
	movs r0, #0xe8
	lsls r0, r0, #8
	str r0, [r5, #0x54]
_0809C2C6:
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	beq _0809C2D0
	cmp r0, #3
	bne _0809C2DC
_0809C2D0:
	ldr r0, _0809C2D8 @ =0xFFFFFF00
	b _0809C2DE
	.align 2, 0
_0809C2D4: .4byte gEnemyFnTable
_0809C2D8: .4byte 0xFFFFFF00
_0809C2DC:
	movs r0, #0
_0809C2DE:
	str r0, [r5, #0x5c]
	adds r1, r5, #0
	adds r1, #0xb4
	ldr r0, [r5, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r5, #0x58]
	str r0, [r1]
	movs r0, #0x80
	lsls r0, r0, #1
	str r0, [r5, #0x60]
	adds r0, r5, #0
	bl CielMinigameEnemy2_Update
	pop {r4, r5}
	pop {r0}
	bx r0
