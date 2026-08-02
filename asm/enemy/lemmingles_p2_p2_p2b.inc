	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806f07c
FUN_0806f07c: @ 0x0806F07C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _0806F08C
	cmp r0, #1
	beq _0806F142
	b _0806F1D6
_0806F08C:
	ldr r2, [r6, #0x28]
	cmp r2, #0
	beq _0806F0A0
	adds r2, #0xb4
	movs r1, #1
	ldrb r0, [r6, #0x11]
	lsls r1, r0
	ldr r0, [r2]
	bics r0, r1
	str r0, [r2]
_0806F0A0:
	adds r2, r6, #0
	adds r2, #0x74
	ldrb r0, [r6, #0x10]
	ldr r1, _0806F124 @ =0x083668E4
	cmp r0, #1
	bls _0806F0AE
	adds r1, #0x18
_0806F0AE:
	adds r0, r2, #0
	bl SetDDP
	ldr r1, _0806F128 @ =0x08366928
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r6, #0
	bl SetMotion
	ldr r0, _0806F12C @ =pZero2
	ldr r2, [r0]
	ldr r1, [r6, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x58]
	ldr r3, _0806F130 @ =0xFFFFE800
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
	beq _0806F134
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
	b _0806F13C
	.align 2, 0
_0806F124: .4byte 0x083668E4
_0806F128: .4byte 0x08366928
_0806F12C: .4byte pZero2
_0806F130: .4byte 0xFFFFE800
_0806F134:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r6, #0x5c]
	str r5, [r6, #0x60]
_0806F13C:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0806F142:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	cmp r1, #0
	ble _0806F168
	ldr r1, [r6, #0x58]
	bl PushoutToLeft1
	adds r5, r0, #0
	cmp r5, #0
	bge _0806F17C
	ldr r0, [r6, #0x54]
	adds r0, r0, r5
	str r0, [r6, #0x54]
	b _0806F1BA
_0806F168:
	ldr r1, [r6, #0x58]
	bl PushoutToRight1
	adds r5, r0, #0
	cmp r5, #0
	ble _0806F17C
	ldr r0, [r6, #0x54]
	adds r0, r0, r5
	str r0, [r6, #0x54]
	b _0806F1BA
_0806F17C:
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	bne _0806F1BA
	ldr r0, [r6, #0x60]
	adds r0, #0x40
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0806F19A
	str r1, [r6, #0x60]
_0806F19A:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r2, r0, r1
	str r2, [r6, #0x58]
	cmp r1, #0
	ble _0806F1C2
	ldr r0, [r6, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r5, r0, #0
	cmp r5, #0
	bge _0806F1D6
	ldr r0, [r6, #0x58]
	adds r0, r0, r5
	str r0, [r6, #0x58]
_0806F1BA:
	adds r0, r6, #0
	bl FUN_0806f1dc
	b _0806F1D6
_0806F1C2:
	ldr r0, [r6, #0x54]
	adds r1, r2, #0
	bl PushoutToDown1
	adds r5, r0, #0
	cmp r5, #0
	ble _0806F1D6
	ldr r0, [r6, #0x58]
	adds r0, r0, r5
	str r0, [r6, #0x58]
_0806F1D6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

