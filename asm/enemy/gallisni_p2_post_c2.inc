	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08087ab0
FUN_08087ab0: @ 0x08087AB0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08087AC0
	cmp r0, #1
	beq _08087B56
	b _08087B96
_08087AC0:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08087B38 @ =0x08368738
	bl SetDDP
	ldr r1, _08087B3C @ =0x00006703
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _08087B40 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _08087B44 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	cmp r6, #0
	beq _08087B48
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
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r5, #0x60]
	b _08087B50
	.align 2, 0
_08087B38: .4byte 0x08368738
_08087B3C: .4byte 0x00006703
_08087B40: .4byte pZero2
_08087B44: .4byte 0xFFFFE800
_08087B48:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_08087B50:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08087B56:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08087B6E
	str r1, [r5, #0x60]
_08087B6E:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08087B90
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _08087B96
_08087B90:
	adds r0, r5, #0
	bl FUN_080878f0
_08087B96:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
