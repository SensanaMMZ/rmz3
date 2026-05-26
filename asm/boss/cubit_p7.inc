	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cubitMode5
cubitMode5: @ 0x080533C0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080533E6
	cmp r0, #1
	bgt _080533D4
	cmp r0, #0
	beq _080533DE
	b _08053450
_080533D4:
	cmp r0, #2
	beq _0805341A
	cmp r0, #3
	beq _0805343A
	b _08053450
_080533DE:
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080533E6:
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
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	beq _08053450
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _0805344E
_0805341A:
	ldr r1, _08053458 @ =0x0000B014
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805345C @ =sCollisions+(24*1)
	bl SetDDP
	adds r1, r4, #0
	adds r1, #0xc8
	movs r0, #0
	strb r0, [r1]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805343A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r1, [r0]
	cmp r1, #3
	bne _08053450
	movs r0, #0
	strb r1, [r4, #0xd]
_0805344E:
	strb r0, [r4, #0xe]
_08053450:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08053458: .4byte 0x0000B014
_0805345C: .4byte sCollisions+(24*1)
