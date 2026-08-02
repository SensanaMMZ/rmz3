	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08091da4
FUN_08091da4: @ 0x08091DA4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08091DB4
	cmp r0, #1
	beq _08091E26
	b _08091E4E
_08091DB4:
	movs r0, #0x80
	lsls r0, r0, #1
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08091DE8 @ =0x08369924
	bl SetDDP
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #7
	ldr r1, _08091DEC @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, _08091DF0 @ =0xFFFFFC00
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	lsrs r2, r0, #1
	cmp r2, #0
	beq _08091DF4
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08091DFA
	.align 2, 0
_08091DE8: .4byte 0x08369924
_08091DEC: .4byte 0xFFFFFE80
_08091DF0: .4byte 0xFFFFFC00
_08091DF4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08091DFA:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _08091E54 @ =0x00008801
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091E26:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	cmp r0, #0
	ble _08091E40
	movs r1, #0
	movs r0, #8
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08091E40:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08091E4E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08091E54: .4byte 0x00008801
