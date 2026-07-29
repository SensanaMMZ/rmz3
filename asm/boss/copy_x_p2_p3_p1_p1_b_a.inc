	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyxNovaStrike3
copyxNovaStrike3: @ 0x080560D8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056166
	ldr r1, _08056108 @ =0x0000B30A
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08056110
	movs r0, #0xe0
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0xc8
	ldr r0, _0805610C @ =0x0000FFF8
	b _0805611A
	.align 2, 0
_08056108: .4byte 0x0000B30A
_0805610C: .4byte 0x0000FFF8
_08056110:
	ldr r0, _08056140 @ =0xFFFFFC80
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0xc8
	movs r0, #8
_0805611A:
	strh r0, [r1]
	movs r0, #0
	str r0, [r4, #0x60]
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xde
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	beq _08056148
	subs r0, #0x6a
	ldr r1, _08056144 @ =0x08363CA8
	bl SetDDP
	movs r0, #0x46
	bl PlaySound
	b _08056158
	.align 2, 0
_08056140: .4byte 0xFFFFFC80
_08056144: .4byte 0x08363CA8
_08056148:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080561F0 @ =0x08363C48
	bl SetDDP
	movs r0, #0x46
	bl PlaySound
_08056158:
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0
	bl createCopyXSonicBoom
	movs r0, #0
	strb r0, [r5]
_08056166:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r3, [r4, #0x5c]
	adds r0, r0, r3
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	adds r1, r0, #1
	strb r1, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	movs r2, #0xf0
	lsls r2, r2, #8
	adds r0, r0, r2
	ldr r2, [r4, #0x58]
	cmp r2, r0
	bge _08056224
	adds r0, r1, #1
	strb r0, [r4, #0x12]
	ldr r1, _080561F4 @ =pZero2
	ldr r0, [r1]
	ldr r0, [r0, #0x58]
	adds r3, r1, #0
	cmp r2, r0
	ble _080561A2
	ldr r5, _080561F8 @ =0xFFFFFE00
	adds r0, r2, r5
	str r0, [r4, #0x58]
_080561A2:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r2, [r0]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r2, r1
	ldr r1, [r4, #0x54]
	cmp r1, r0
	blt _080561BE
	movs r5, #0xa0
	lsls r5, r5, #9
	adds r0, r2, r5
	cmp r1, r0
	ble _080561C6
_080561BE:
	movs r0, #0xb
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_080561C6:
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	bics r2, r0
	movs r5, #0
	ldr r0, [r3]
	ldr r0, [r0, #0x54]
	adds r3, r1, #0
	cmp r0, r3
	bge _080561DC
	movs r5, #1
_080561DC:
	cmp r2, r5
	beq _08056266
	subs r2, r0, r3
	cmp r2, #0
	blt _080561FC
	movs r0, #0x80
	lsls r0, r0, #7
	cmp r2, r0
	bgt _08056206
	b _08056266
	.align 2, 0
_080561F0: .4byte 0x08363C48
_080561F4: .4byte pZero2
_080561F8: .4byte 0xFFFFFE00
_080561FC:
	subs r1, r1, r0
	movs r0, #0x80
	lsls r0, r0, #7
	cmp r1, r0
	ble _08056266
_08056206:
	ldrb r0, [r4, #0x12]
	cmp r0, #0x28
	bls _08056266
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r1, [r0]
	cmp r1, #0
	bne _0805625E
	movs r0, #0xa
	strb r0, [r4, #0xd]
	movs r0, #0x15
	strb r0, [r4, #0xf]
	str r1, [r4, #0x5c]
	str r1, [r4, #0x60]
	b _08056262
_08056224:
	adds r0, r4, #0
	adds r0, #0xc8
	movs r1, #0
	ldrsh r0, [r0, r1]
	adds r0, r3, r0
	str r0, [r4, #0x5c]
	adds r1, r0, #0
	cmp r1, #0
	bge _08056238
	rsbs r1, r1, #0
_08056238:
	ldr r0, _08056250 @ =0x000003FF
	cmp r1, r0
	bgt _08056258
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08056254
	movs r0, #0x80
	lsls r0, r0, #3
	b _08056256
	.align 2, 0
_08056250: .4byte 0x000003FF
_08056254:
	ldr r0, _0805626C @ =0xFFFFFC00
_08056256:
	str r0, [r4, #0x5c]
_08056258:
	ldrb r0, [r4, #0x12]
	cmp r0, #0x28
	bls _08056266
_0805625E:
	movs r0, #0xb
	strb r0, [r4, #0xd]
_08056262:
	movs r0, #1
	strb r0, [r4, #0xe]
_08056266:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805626C: .4byte 0xFFFFFC00

	thumb_func_start copyxMode16
copyxMode16: @ 0x08056270
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080562FA
	ldr r1, _080562C8 @ =0x0000B310
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _080562CC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08056292
	movs r3, #1
_08056292:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _080562A4
	movs r3, #1
_080562A4:
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
	beq _080562D0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080562D6
	.align 2, 0
_080562C8: .4byte 0x0000B310
_080562CC: .4byte pZero2
_080562D0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080562D6:
	strb r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xe]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080562F0
	ldr r0, _080562EC @ =0xFFFFFD00
	b _080562F4
	.align 2, 0
_080562EC: .4byte 0xFFFFFD00
_080562F0:
	movs r0, #0xc0
	lsls r0, r0, #2
_080562F4:
	str r0, [r4, #0x5c]
	ldr r0, _08056334 @ =0xFFFFFD00
	str r0, [r4, #0x60]
_080562FA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	adds r2, #0x40
	str r2, [r4, #0x60]
	bl FUN_08009f6c
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _0805632E
	ldr r0, [r4, #0x54]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r0, #0xc
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805632E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08056334: .4byte 0xFFFFFD00

