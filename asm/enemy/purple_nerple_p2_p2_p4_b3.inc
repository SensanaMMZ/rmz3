	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080768e0
FUN_080768e0: @ 0x080768E0
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080768F0
	cmp r0, #1
	beq _0807699A
	b _08076A48
_080768F0:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08076910 @ =0x083671C8
	bl SetDDP
	adds r0, r6, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _08076918
	ldr r1, _08076914 @ =0x00002A04
	adds r0, r6, #0
	bl SetMotion
	b _08076920
	.align 2, 0
_08076910: .4byte 0x083671C8
_08076914: .4byte 0x00002A04
_08076918:
	ldr r1, _08076980 @ =0x00002A02
	adds r0, r6, #0
	bl SetMotion
_08076920:
	ldr r0, _08076984 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r6, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x58]
	ldr r3, _08076988 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r6, #0x60]
	asrs r1, r1, #8
	adds r5, r1, #0
	muls r5, r1, r5
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r5, r5, r0
	adds r0, r5, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r5, r0, #8
	cmp r5, #0
	beq _0807698C
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r6, #0x5c]
	ldr r0, [r6, #0x60]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r6, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r6, #0x60]
	b _08076994
	.align 2, 0
_08076980: .4byte 0x00002A02
_08076984: .4byte pZero2
_08076988: .4byte 0xFFFFE800
_0807698C:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r6, #0x5c]
	str r5, [r6, #0x60]
_08076994:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0807699A:
	adds r0, r6, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _080769B4
	ldr r1, _080769B0 @ =0x00002A04
	adds r0, r6, #0
	bl SetMotion
	b _080769BC
	.align 2, 0
_080769B0: .4byte 0x00002A04
_080769B4:
	ldr r1, _080769E4 @ =0x00002A02
	adds r0, r6, #0
	bl SetMotion
_080769BC:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	cmp r1, #0
	bge _080769E8
	ldr r1, [r6, #0x58]
	bl PushoutToRight1
	adds r5, r0, #0
	cmp r5, #0
	ble _080769FC
	ldr r0, [r6, #0x54]
	adds r0, r0, r5
	str r0, [r6, #0x54]
	b _08076A0A
	.align 2, 0
_080769E4: .4byte 0x00002A02
_080769E8:
	ldr r1, [r6, #0x58]
	bl PushoutToLeft1
	adds r5, r0, #0
	cmp r5, #0
	bge _080769FC
	ldr r0, [r6, #0x54]
	adds r0, r0, r5
	str r0, [r6, #0x54]
	b _08076A0A
_080769FC:
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _08076A12
_08076A0A:
	adds r0, r6, #0
	bl FUN_08076b30
	b _08076A48
_08076A12:
	ldr r0, [r6, #0x60]
	adds r0, #0x40
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08076A22
	str r1, [r6, #0x60]
_08076A22:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r2, r0, r1
	str r2, [r6, #0x58]
	cmp r1, #0
	ble _08076A48
	ldr r0, [r6, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r5, r0, #0
	cmp r5, #0
	bge _08076A48
	ldr r0, [r6, #0x58]
	adds r0, r0, r5
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl FUN_08076b30
_08076A48:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
