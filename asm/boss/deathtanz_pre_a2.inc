	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start deathtanzMode2
deathtanzMode2: @ 0x080493F8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0804945E
	cmp r0, #1
	bgt _0804940C
	cmp r0, #0
	beq _08049418
	b _0804959C
_0804940C:
	cmp r0, #2
	beq _08049480
	cmp r0, #3
	bne _08049416
	b _08049538
_08049416:
	b _0804959C
_08049418:
	strb r0, [r4, #0x12]
	movs r2, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r1, [r4, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	ble _0804942A
	movs r2, #1
_0804942A:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804943A
	cmp r2, #0
	beq _0804943E
	b _08049442
_0804943A:
	cmp r2, #0
	beq _08049442
_0804943E:
	movs r0, #2
	b _0804959A
_08049442:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049478 @ =sCollisions+(24*4)
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0x12]
	ldr r1, _0804947C @ =0x0000A707
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804945E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08049470
	b _0804959C
_08049470:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _0804959A
	.align 2, 0
_08049478: .4byte sCollisions+(24*4)
_0804947C: .4byte 0x0000A707
_08049480:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080494C8
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _080494C0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080494C6
_080494C0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080494C6:
	strb r0, [r4, #0xa]
_080494C8:
	ldr r3, _08049508 @ =u8_ARRAY_08362ea6
	ldr r2, _0804950C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08049510 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08049514 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xf
	ands r0, r1
	adds r0, r0, r3
	ldrb r0, [r0]
	adds r1, r4, #0
	adds r1, #0xbc
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08049520
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049518 @ =sCollisions+(24*7)
	bl SetDDP
	ldr r1, _0804951C @ =0x0000A708
	adds r0, r4, #0
	bl SetMotion
	b _08049532
	.align 2, 0
_08049508: .4byte u8_ARRAY_08362ea6
_0804950C: .4byte RNG_0202f388
_08049510: .4byte 0x000343FD
_08049514: .4byte 0x00269EC3
_08049518: .4byte sCollisions+(24*7)
_0804951C: .4byte 0x0000A708
_08049520:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804957C @ =sCollisions+(24*9)
	bl SetDDP
	ldr r1, _08049580 @ =0x0000A709
	adds r0, r4, #0
	bl SetMotion
_08049532:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049538:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r5, [r0]
	cmp r5, #3
	bne _0804959C
	movs r0, #0x5c
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r0, [r0]
	cmp r0, #0
	bne _08049596
	ldr r2, _08049584 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08049588 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0804958C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08049590
	movs r0, #6
	strb r0, [r4, #0xd]
	b _08049598
	.align 2, 0
_0804957C: .4byte sCollisions+(24*9)
_08049580: .4byte 0x0000A709
_08049584: .4byte RNG_0202f388
_08049588: .4byte 0x000343FD
_0804958C: .4byte 0x00269EC3
_08049590:
	movs r0, #9
	strb r0, [r4, #0xd]
	b _08049598
_08049596:
	strb r5, [r4, #0xd]
_08049598:
	movs r0, #0
_0804959A:
	strb r0, [r4, #0xe]
_0804959C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
