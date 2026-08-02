	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start volteelKnockBackDamage
volteelKnockBackDamage: @ 0x08045614
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08045624
	cmp r5, #1
	beq _08045710
	b _080457B2
_08045624:
	movs r0, #0x81
	bl PlaySound
	ldr r1, _08045670 @ =0x0000A504
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x7f
	bl isSoundPlaying
	cmp r0, #0
	beq _08045642
	movs r0, #0x7f
	bl StopSound
_08045642:
	ldr r0, _08045674 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0804567C
	ldr r0, _08045678 @ =0xFFFFFE00
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0x4c
	movs r0, #1
	strb r0, [r1]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r4, #0xa]
	orrs r1, r0
	strb r1, [r4, #0xa]
	b _0804569E
	.align 2, 0
_08045670: .4byte 0x0000A504
_08045674: .4byte pZero2
_08045678: .4byte 0xFFFFFE00
_0804567C:
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
_0804569E:
	adds r5, r2, #0
	adds r0, r4, #0
	adds r0, #0xc0
	movs r3, #0
	str r3, [r0]
	ldr r2, _080456C0 @ =gOverworld
	movs r1, #0xe8
	lsls r1, r1, #1
	adds r0, r2, r1
	ldrh r1, [r0]
	movs r0, #0x7f
	ands r0, r1
	cmp r0, #0xd
	bne _080456C8
	ldr r1, _080456C4 @ =0x0002D024
	b _080456CA
	.align 2, 0
_080456C0: .4byte gOverworld
_080456C4: .4byte 0x0002D024
_080456C8:
	ldr r1, _080457B8 @ =0x0002D026
_080456CA:
	adds r0, r2, r1
	strb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r2, #0
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r3, r4, #0
	adds r3, #0x49
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r3]
	adds r0, r4, #0
	adds r0, #0x24
	strb r2, [r0]
	adds r0, #0x29
	strb r2, [r0]
	ldrb r1, [r5]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5]
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x28
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08045710:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x5c]
	rsbs r1, r0, #0
	lsls r1, r1, #3
	asrs r1, r1, #8
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x60]
	adds r0, #0x20
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08045732
	str r1, [r4, #0x60]
_08045732:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r2, r1, r0
	str r2, [r4, #0x58]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	cmp r1, #0
	ble _08045760
	movs r3, #0x90
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r3, _080457BC @ =0xFFFFF800
	adds r1, r2, r3
	bl PushoutToLeft2
	adds r1, r0, #0
	cmp r1, #0
	beq _08045760
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_08045760:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _08045782
	ldr r0, [r4, #0x54]
	ldr r1, _080457C0 @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	ldr r2, _080457BC @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToRight2
	adds r1, r0, #0
	cmp r1, #0
	beq _08045782
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_08045782:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToUp2
	adds r1, r0, #0
	cmp r1, #0
	beq _08045796
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_08045796:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080457A6
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080457B2
_080457A6:
	movs r0, #0
	movs r1, #3
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
	movs r0, #0xff
	strb r0, [r4, #0xf]
_080457B2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080457B8: .4byte 0x0002D026
_080457BC: .4byte 0xFFFFF800
_080457C0: .4byte 0xFFFFEE00

	thumb_func_start volteel_080457c4
volteel_080457c4: @ 0x080457C4
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	cmp r0, #0
	bne _08045864
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08045864
	ldrb r0, [r4, #0xd]
	cmp r0, #9
	bne _08045818
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080457F4
	ldr r2, _080457F0 @ =0x08362590
	b _0804581A
	.align 2, 0
_080457F0: .4byte 0x08362590
_080457F4:
	cmp r0, #1
	bne _08045800
	ldr r2, _080457FC @ =0x08362598
	b _0804581A
	.align 2, 0
_080457FC: .4byte 0x08362598
_08045800:
	cmp r0, #2
	bne _0804580C
	ldr r2, _08045808 @ =0x08362588
	b _0804581A
	.align 2, 0
_08045808: .4byte 0x08362588
_0804580C:
	cmp r0, #3
	bne _08045824
	ldr r2, _08045814 @ =0x083625A0
	b _0804581A
	.align 2, 0
_08045814: .4byte 0x083625A0
_08045818:
	ldr r2, _0804585C @ =0x08362570
_0804581A:
	movs r0, #0xd
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r5]
_08045824:
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	cmp r0, #0
	beq _08045864
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r1, [r0]
	movs r0, #0xf0
	ands r0, r1
	cmp r0, #0x30
	bne _08045860
	ldrb r1, [r4, #0xd]
	adds r0, r4, #0
	adds r0, #0xd0
	movs r2, #0
	strb r1, [r0]
	ldrb r0, [r4, #0xe]
	adds r1, r4, #0
	adds r1, #0xd1
	strb r0, [r1]
	ldrb r0, [r4, #0xf]
	adds r1, #1
	strb r0, [r1]
	movs r0, #0xb
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	b _08045864
	.align 2, 0
_0804585C: .4byte 0x08362570
_08045860:
	movs r0, #0
	str r0, [r2]
_08045864:
	movs r0, #1
	pop {r4, r5}
	pop {r1}
	bx r1
