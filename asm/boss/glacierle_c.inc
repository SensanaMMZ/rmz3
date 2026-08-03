	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierle_08059674
glacierle_08059674: @ 0x08059674
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08059684
	cmp r0, #1
	beq _0805970A
	b _08059794
_08059684:
	movs r0, #0x97
	bl PlaySound
	ldr r1, _08059728 @ =0x0000B204
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0xc8
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r2, _0805972C @ =0xFFFFD000
	adds r0, r0, r2
	adds r2, r5, #0
	adds r2, #0xcc
	ldr r2, [r2]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r3, r0, #0
	muls r3, r0, r3
	adds r0, r3, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
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
	adds r1, r0, #0
	str r1, [r5, #0x60]
	lsls r0, r4, #2
	adds r0, r0, r4
	lsls r0, r0, #7
	cmp r0, #0
	bge _080596F0
	adds r0, #0xff
_080596F0:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08059700
	adds r0, #0xff
_08059700:
	asrs r0, r0, #8
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805970A:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r1, r0, r1
	str r1, [r5, #0x54]
	adds r0, r5, #0
	adds r0, #0xbc
	ldr r0, [r0]
	movs r3, #0x9a
	lsls r3, r3, #8
	adds r2, r0, r3
	cmp r1, r2
	ble _08059730
	str r2, [r5, #0x54]
	b _0805973A
	.align 2, 0
_08059728: .4byte 0x0000B204
_0805972C: .4byte 0xFFFFD000
_08059730:
	ldr r2, _08059774 @ =0xFFFF6600
	adds r0, r0, r2
	cmp r1, r0
	bge _0805973A
	str r0, [r5, #0x54]
_0805973A:
	ldr r0, [r5, #0x60]
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0805974A
	str r1, [r5, #0x60]
_0805974A:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _08059778
	ldr r0, [r5, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r6, r0, #0
	cmp r6, #0
	bge _0805978E
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
	movs r0, #0
	strb r0, [r5, #0xd]
	strb r0, [r5, #0xe]
	b _0805978E
	.align 2, 0
_08059774: .4byte 0xFFFF6600
_08059778:
	ldr r0, [r5, #0x54]
	ldr r3, _0805979C @ =0xFFFFD000
	adds r1, r2, r3
	bl PushoutToDown1
	adds r6, r0, #0
	cmp r6, #0
	bge _0805978E
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
_0805978E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08059794:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0805979C: .4byte 0xFFFFD000
