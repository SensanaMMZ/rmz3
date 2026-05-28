	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile29_Init
Projectile29_Init: @ 0x080AA29C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	ldr r6, [r7, #0x28]
	ldr r1, _080AA2E8 @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl InitNonAffineMotion
	ldrb r1, [r7, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	movs r1, #0xc0
	lsls r1, r1, #7
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r6, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080AA2EC
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080AA2F2
	.align 2, 0
_080AA2E8: .4byte gProjectileFnTable
_080AA2EC:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AA2F2:
	strb r0, [r7, #0xa]
	adds r1, r2, #0
	adds r0, r7, #0
	adds r0, #0x4c
	movs r2, #0
	mov r8, r2
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r7, #0xa]
	movs r5, #4
	orrs r0, r5
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r1, _080AA364 @ =0x0836C2A0
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r7, [r4, #0x2c]
	mov r0, r8
	str r0, [r4, #0x24]
	adds r2, r7, #0
	adds r2, #0x49
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r5
	strb r0, [r2]
	ldrb r0, [r7, #0x10]
	cmp r0, #0
	bne _080AA38C
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080AA368
	ldr r0, [r6, #0x54]
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r7, #0x54]
	movs r0, #0xa0
	lsls r0, r0, #3
	b _080AA372
	.align 2, 0
_080AA364: .4byte 0x0836C2A0
_080AA368:
	ldr r0, [r6, #0x54]
	ldr r2, _080AA380 @ =0xFFFFEB00
	adds r0, r0, r2
	str r0, [r7, #0x54]
	ldr r0, _080AA384 @ =0xFFFFFB00
_080AA372:
	str r0, [r7, #0x5c]
	ldr r0, [r6, #0x58]
	ldr r4, _080AA388 @ =0xFFFFE900
	adds r0, r0, r4
	str r0, [r7, #0x58]
	movs r0, #0
	b _080AA3E6
	.align 2, 0
_080AA380: .4byte 0xFFFFEB00
_080AA384: .4byte 0xFFFFFB00
_080AA388: .4byte 0xFFFFE900
_080AA38C:
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080AA3A8
	ldr r0, [r6, #0x54]
	movs r1, #0x88
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r7, #0x54]
	adds r1, r7, #0
	adds r1, #0xc0
	movs r0, #0x20
	b _080AA3B6
_080AA3A8:
	ldr r0, [r6, #0x54]
	ldr r2, _080AA400 @ =0xFFFFEF00
	adds r0, r0, r2
	str r0, [r7, #0x54]
	adds r1, r7, #0
	adds r1, #0xc0
	movs r0, #0x60
_080AA3B6:
	strb r0, [r1]
	adds r3, r1, #0
	ldr r0, [r6, #0x58]
	ldr r4, _080AA404 @ =0xFFFFF200
	adds r0, r0, r4
	str r0, [r7, #0x58]
	ldr r2, _080AA408 @ =gSineTable
	ldrb r0, [r3]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r4, #0
	ldrsh r1, [r0, r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	str r0, [r7, #0x5c]
	ldrb r0, [r3]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
_080AA3E6:
	str r0, [r7, #0x60]
	movs r1, #0
	movs r0, #0x14
	strb r0, [r7, #0x12]
	strb r1, [r7, #0x13]
	adds r0, r7, #0
	bl Projectile29_Update
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AA400: .4byte 0xFFFFEF00
_080AA404: .4byte 0xFFFFF200
_080AA408: .4byte gSineTable

	thumb_func_start Projectile29_Update
Projectile29_Update: @ 0x080AA40C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _080AA438
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bls _080AA438
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl CreateVFX56
	movs r0, #0
	strb r0, [r4, #0x12]
_080AA438:
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _080AA4B8
	cmp r0, #1
	bgt _080AA448
	cmp r0, #0
	beq _080AA44E
	b _080AA56C
_080AA448:
	cmp r0, #2
	beq _080AA524
	b _080AA56C
_080AA44E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080AA46E
	movs r0, #0x4d
	bl PlaySound
	ldrb r0, [r4, #0xd]
	adds r0, #1
	ldrb r1, [r4, #0x10]
	adds r0, r0, r1
	strb r0, [r4, #0xd]
	b _080AA56C
_080AA46E:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080AA494
	ldrb r0, [r5, #0x1e]
	lsls r0, r0, #8
	adds r1, r5, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	ldr r1, _080AA490 @ =0x0000B31B
	cmp r0, r1
	beq _080AA56C
	movs r0, #0x4d
	bl PlaySound
	b _080AA516
	.align 2, 0
_080AA490: .4byte 0x0000B31B
_080AA494:
	ldrb r0, [r5, #0x1e]
	lsls r0, r0, #8
	adds r1, r5, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	ldr r1, _080AA4B4 @ =0x0000B31C
	cmp r0, r1
	beq _080AA56C
	movs r0, #0x4d
	bl PlaySound
	ldrb r0, [r4, #0xd]
	adds r0, #2
	strb r0, [r4, #0xd]
	b _080AA56C
	.align 2, 0
_080AA4B4: .4byte 0x0000B31C
_080AA4B8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA56C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	cmp r1, #0
	bge _080AA4E0
	adds r1, r4, #0
	adds r1, #0xc0
	movs r0, #0x20
	b _080AA4E6
_080AA4E0:
	adds r1, r4, #0
	adds r1, #0xc0
	movs r0, #0x60
_080AA4E6:
	strb r0, [r1]
	adds r3, r1, #0
	ldr r2, _080AA520 @ =gSineTable
	ldrb r0, [r3]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r5, #0
	ldrsh r1, [r0, r5]
	lsls r0, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldrb r0, [r3]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
_080AA516:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	b _080AA56C
	.align 2, 0
_080AA520: .4byte gSineTable
_080AA524:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA546
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	rsbs r1, r1, #0
	str r1, [r4, #0x5c]
	b _080AA566
_080AA546:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA56C
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	rsbs r1, r1, #0
	str r1, [r4, #0x60]
_080AA566:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
_080AA56C:
	ldrb r0, [r4, #0x13]
	cmp r0, #2
	bls _080AA5BC
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x20
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x40
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x60
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x80
	bl CreateVFX56
	ldr r1, _080AA5C4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Projectile29_Die
_080AA5BC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AA5C4: .4byte gProjectileFnTable
