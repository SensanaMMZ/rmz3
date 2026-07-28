	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start shrimporin_0806a544
shrimporin_0806a544: @ 0x0806A544
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0806A554
	cmp r0, #1
	beq _0806A5E0
	b _0806A6C0
_0806A554:
	ldr r1, _0806A5C0 @ =0x00000D03
	adds r0, r5, #0
	movs r2, #6
	movs r3, #1
	bl GotoMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _0806A5C4 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	movs r3, #0xc0
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r4, r0, #0
	muls r4, r0, r4
	adds r0, r4, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	cmp r6, #0
	beq _0806A5C8
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	lsls r4, r4, #2
	str r4, [r5, #0x5c]
	lsls r0, r0, #2
	str r0, [r5, #0x60]
	b _0806A5D0
	.align 2, 0
_0806A5C0: .4byte 0x00000D03
_0806A5C4: .4byte pZero2
_0806A5C8:
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_0806A5D0:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0806A628 @ =sCollisions+(24*5)
	bl SetDDP
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806A5E0:
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x5c]
	adds r0, r0, r2
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0806A5F8
	str r1, [r5, #0x60]
_0806A5F8:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	cmp r2, #0
	beq _0806A654
	cmp r2, #0
	ble _0806A630
	ldr r0, [r5, #0x54]
	movs r2, #0xc0
	lsls r2, r2, #4
	adds r0, r0, r2
	ldr r3, _0806A62C @ =0xFFFFF800
	adds r1, r1, r3
	bl PushoutToLeft2
	adds r2, r0, #0
	cmp r2, #0
	bge _0806A654
	ldr r0, [r5, #0x54]
	adds r0, r0, r2
	str r0, [r5, #0x54]
	b _0806A662
	.align 2, 0
_0806A628: .4byte sCollisions+(24*5)
_0806A62C: .4byte 0xFFFFF800
_0806A630:
	ldr r0, [r5, #0x54]
	ldr r4, _0806A64C @ =0xFFFFF400
	adds r0, r0, r4
	ldr r2, _0806A650 @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToRight2
	adds r2, r0, #0
	cmp r2, #0
	ble _0806A654
	ldr r0, [r5, #0x54]
	adds r0, r0, r2
	str r0, [r5, #0x54]
	b _0806A662
	.align 2, 0
_0806A64C: .4byte 0xFFFFF400
_0806A650: .4byte 0xFFFFF800
_0806A654:
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0806A66A
_0806A662:
	adds r0, r5, #0
	bl explodeShrimpolin
	b _0806A6C0
_0806A66A:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl PushoutToUp2
	adds r2, r0, #0
	cmp r2, #0
	bge _0806A6C0
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	beq _0806A6AC
	adds r3, r5, #0
	adds r3, #0xb8
	ldr r1, [r5, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	ble _0806A69C
	movs r4, #0xb4
	lsls r4, r4, #9
	adds r0, r0, r4
	cmp r1, r0
	ble _0806A6AC
	ldr r4, _0806A698 @ =0xFFFE9800
	b _0806A6A8
	.align 2, 0
_0806A698: .4byte 0xFFFE9800
_0806A69C:
	ldr r4, _0806A6C8 @ =0xFFFE9800
	adds r0, r0, r4
	cmp r1, r0
	bge _0806A6AC
	movs r4, #0xb4
	lsls r4, r4, #9
_0806A6A8:
	adds r0, r1, r4
	str r0, [r3]
_0806A6AC:
	ldr r1, [r5, #0x58]
	adds r1, r1, r2
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldrb r2, [r5, #0x11]
	bl createShrimporinIce
	adds r0, r5, #0
	bl explodeShrimpolin
_0806A6C0:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0806A6C8: .4byte 0xFFFE9800
