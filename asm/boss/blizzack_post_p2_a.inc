	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start blizzackBomb
blizzackBomb: @ 0x0805A744
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805A76A
	ldr r1, _0805A7B0 @ =0x0000B40F
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A7B4 @ =0x0000640E
	strh r1, [r0]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0x12]
_0805A76A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r3, #0
	ldr r0, _0805A7B8 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805A780
	movs r3, #1
_0805A780:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805A792
	movs r3, #1
_0805A792:
	adds r5, r4, #0
	adds r5, #0x4a
	lsls r2, r3, #4
	ldrb r1, [r5]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r5]
	cmp r3, #0
	beq _0805A7BC
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805A7C2
	.align 2, 0
_0805A7B0: .4byte 0x0000B40F
_0805A7B4: .4byte 0x0000640E
_0805A7B8: .4byte pZero2
_0805A7BC:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805A7C2:
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x60
	str r1, [r4, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _0805A7E2
	str r0, [r4, #0x60]
_0805A7E2:
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xe
	bne _0805A864
	ldrb r0, [r4, #0x13]
	cmp r0, #1
	bne _0805A814
	ldr r0, _0805A80C @ =pZero2
	ldr r3, [r0]
	ldr r0, [r3, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	lsls r0, r0, #0xc
	asrs r0, r0, #0x10
	ldr r2, [r4, #0x58]
	ldr r1, _0805A810 @ =0xFFFFE000
	b _0805A828
	.align 2, 0
_0805A80C: .4byte pZero2
_0805A810: .4byte 0xFFFFE000
_0805A814:
	ldr r0, _0805A87C @ =pZero2
	ldr r3, [r0]
	ldr r0, [r3, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	lsls r0, r0, #0xc
	asrs r0, r0, #0x10
	ldr r2, [r4, #0x58]
	movs r1, #0xc0
	lsls r1, r1, #6
_0805A828:
	adds r2, r2, r1
	ldr r1, [r3, #0x58]
	subs r1, r1, r2
	lsls r1, r1, #0xc
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x80
	lsls r1, r1, #7
	adds r0, r0, r1
	asrs r0, r0, #8
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r0, #0x43
	bl PlaySound
	adds r1, r5, #6
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r4, #0
	bl blizzack_080aaae0
	subs r1, r5, #6
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r4, #0
	bl blizzack_080aaae0
_0805A864:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805A876
	movs r0, #0xf
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805A876:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805A87C: .4byte pZero2
