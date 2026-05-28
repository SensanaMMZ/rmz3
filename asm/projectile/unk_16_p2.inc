	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile16_Init
Projectile16_Init: @ 0x080A24A8
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	movs r7, #0
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A2500 @ =0x0836B358
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #2
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldrb r2, [r6, #0x10]
	cmp r2, #0
	bne _080A2504
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080A2526
	.align 2, 0
_080A2500: .4byte 0x0836B358
_080A2504:
	movs r2, #1
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_080A2526:
	movs r0, #0xff
	strb r0, [r6, #0x12]
	ldr r1, _080A2550 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #0
	strb r0, [r6, #0xd]
	strb r0, [r6, #0xe]
	strb r0, [r6, #0xf]
	adds r0, r6, #0
	bl Projectile16_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A2550: .4byte gProjectileFnTable

	thumb_func_start Projectile16_Update
Projectile16_Update: @ 0x080A2554
	push {lr}
	adds r3, r0, #0
	ldr r0, _080A259C @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080A25A4
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _080A25A0 @ =gProjectileFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
	b _080A25B4
	.align 2, 0
_080A259C: .4byte gCurStory
_080A25A0: .4byte gProjectileFnTable
_080A25A4:
	ldr r0, _080A25B8 @ =0x0836B350
	ldrb r1, [r3, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r3, #0
	bl _call_via_r1
_080A25B4:
	pop {r0}
	bx r0
	.align 2, 0
_080A25B8: .4byte 0x0836B350

	thumb_func_start Projectile16_Die
Projectile16_Die:
	.byte 0x02, 0x1C, 0x91, 0x7A
	.byte 0xFE, 0x20, 0x08, 0x40, 0x00, 0x21, 0x90, 0x72, 0x10, 0x1C, 0x8C, 0x30, 0x01, 0x60, 0x04, 0x30
	.byte 0x01, 0x60, 0x04, 0x30, 0x01, 0x70, 0x91, 0x7A, 0xFB, 0x20, 0x08, 0x40, 0x90, 0x72, 0x05, 0x49
	.byte 0x50, 0x7A, 0x80, 0x00, 0x40, 0x18, 0x04, 0x21, 0xD1, 0x60, 0x00, 0x68, 0x00, 0x69, 0x50, 0x61
	.byte 0x70, 0x47, 0x00, 0x00, 0x0C, 0xA9, 0x36, 0x08

	thumb_func_start FUN_080a25f8
FUN_080a25f8: @ 0x080A25F8
	push {r4, lr}
	adds r4, r0, #0
	adds r2, r4, #0
	adds r2, #0x8c
	ldr r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #2
	ands r3, r1
	cmp r3, #0
	beq _080A2622
	movs r1, #0
	str r1, [r2]
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	b _080A265C
_080A2622:
	movs r0, #4
	ands r1, r0
	cmp r1, #0
	beq _080A2650
	str r3, [r2]
	adds r0, r4, #0
	adds r0, #0x90
	str r3, [r0]
	adds r0, #4
	strb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	movs r0, #0x35
	bl PlaySound
	b _080A2666
_080A2650:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A2680
_080A265C:
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
_080A2666:
	ldr r1, _080A267C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080A2706
	.align 2, 0
_080A267C: .4byte gProjectileFnTable
_080A2680:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A268C
	cmp r0, #1
	beq _080A26D6
	b _080A2706
_080A268C:
	ldr r1, _080A26A4 @ =0x00003E03
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A26AC
	ldr r0, [r4, #0x54]
	ldr r2, _080A26A8 @ =0xFFFFA000
	b _080A26B2
	.align 2, 0
_080A26A4: .4byte 0x00003E03
_080A26A8: .4byte 0xFFFFA000
_080A26AC:
	ldr r0, [r4, #0x54]
	movs r2, #0xc0
	lsls r2, r2, #7
_080A26B2:
	adds r1, r0, r2
	movs r0, #0x1e
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x54]
	subs r0, r1, r0
	movs r1, #0x1e
	bl __divsi3
	str r0, [r4, #0x5c]
	movs r1, #0
	ldr r0, _080A270C @ =0xFFFFFC40
	str r0, [r4, #0x60]
	movs r0, #0x1d
	str r0, [r4, #0x64]
	strb r1, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A26D6:
	ldr r2, [r4, #0x60]
	adds r2, #0x40
	str r2, [r4, #0x60]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080A2706
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A2706:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A270C: .4byte 0xFFFFFC40

	thumb_func_start FUN_080a2710
FUN_080a2710: @ 0x080A2710
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A2722
	cmp r0, #1
	beq _080A2758
	b _080A277A
_080A2722:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x14
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _080A2784 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x35
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A2788 @ =0x0836B388
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A2758:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080A2768
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A277A
_080A2768:
	ldr r1, _080A278C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A277A:
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A2784: .4byte 0xFFFFF800
_080A2788: .4byte 0x0836B388
_080A278C: .4byte gProjectileFnTable
