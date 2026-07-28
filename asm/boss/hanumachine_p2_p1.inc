	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805c404
FUN_0805c404: @ 0x0805C404
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805C476
	ldr r1, _0805C45C @ =0x0000B508
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805C460 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C426
	movs r3, #1
_0805C426:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C438
	movs r3, #1
_0805C438:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _0805C464
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805C46A
	.align 2, 0
_0805C45C: .4byte 0x0000B508
_0805C460: .4byte pZero2
_0805C464:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805C46A:
	strb r0, [r4, #0xa]
	ldr r0, _0805C4A0 @ =0xFFFFFB80
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C476:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805C49A
	movs r1, #0
	movs r0, #0xb
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805C49A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805C4A0: .4byte 0xFFFFFB80

	thumb_func_start hanu_0805c4a4
hanu_0805c4a4: @ 0x0805C4A4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0805C4DE
	bl InitRotatableMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r1, _0805C4FC @ =0x0000B509
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x58]
	ldr r1, _0805C500 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #0x30
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805C504 @ =0x08364F28
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C4DE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805C520
	ldrb r0, [r4, #0x12]
	cmp r0, #0x20
	bne _0805C508
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0x50
	b _0805C538
	.align 2, 0
_0805C4FC: .4byte 0x0000B509
_0805C500: .4byte 0xFFFFF000
_0805C504: .4byte 0x08364F28
_0805C508:
	cmp r0, #0x10
	bne _0805C514
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0x40
	b _0805C538
_0805C514:
	cmp r0, #0
	bne _0805C558
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0x30
	b _0805C538
_0805C520:
	ldrb r0, [r4, #0x12]
	cmp r0, #0x20
	bne _0805C52E
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0xb0
	b _0805C538
_0805C52E:
	cmp r0, #0x10
	bne _0805C544
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0xc0
_0805C538:
	bl hanu_080ad598
	movs r0, #0x51
	bl PlaySound
	b _0805C558
_0805C544:
	cmp r0, #0
	bne _0805C558
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0xd0
	bl hanu_080ad598
	movs r0, #0x51
	bl PlaySound
_0805C558:
	ldrb r0, [r4, #0x13]
	adds r0, #0x10
	strb r0, [r4, #0x13]
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805C57A
	movs r0, #0xc
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_0805C57A:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805c580
FUN_0805c580: @ 0x0805C580
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0805C62A
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r6, #1
	ands r2, r6
	movs r1, #2
	bl hanu_080ad598
	adds r0, r4, #0
	adds r0, #0x24
	strb r5, [r0]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r1, _0805C5FC @ =0x0000B506
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805C600 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C5C2
	movs r3, #1
_0805C5C2:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C5D4
	movs r3, #1
_0805C5D4:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	adds r1, r6, #0
	ands r1, r3
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805C604
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805C60A
	.align 2, 0
_0805C5FC: .4byte 0x0000B506
_0805C600: .4byte pZero2
_0805C604:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805C60A:
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x58]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #0
	str r0, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805C66C @ =0x08364EC8
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C62A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _0805C646
	str r0, [r4, #0x60]
_0805C646:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805C666
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805C666:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0805C66C: .4byte 0x08364EC8

	thumb_func_start hanu_0805c670
hanu_0805c670: @ 0x0805C670
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805C714
	ldr r1, _0805C6C8 @ =0x0000B506
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805C6CC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C692
	movs r3, #1
_0805C692:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C6A4
	movs r3, #1
_0805C6A4:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _0805C6D0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805C6D6
	.align 2, 0
_0805C6C8: .4byte 0x0000B506
_0805C6CC: .4byte pZero2
_0805C6D0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805C6D6:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805C6F4
	ldr r0, _0805C6EC @ =0xFFFFFE80
	str r0, [r4, #0x5c]
	ldr r0, _0805C6F0 @ =0xFFFFF000
	b _0805C6FE
	.align 2, 0
_0805C6EC: .4byte 0xFFFFFE80
_0805C6F0: .4byte 0xFFFFF000
_0805C6F4:
	movs r0, #0xc0
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #5
_0805C6FE:
	str r0, [r4, #0x64]
	ldr r0, _0805C75C @ =0xFFFFFC40
	str r0, [r4, #0x60]
	movs r0, #0xe
	strb r0, [r4, #0x12]
	movs r0, #0x50
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C714:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x64]
	adds r0, r4, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805C732
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805C732:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805C754
	movs r0, #0xe
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_0805C754:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805C75C: .4byte 0xFFFFFC40

