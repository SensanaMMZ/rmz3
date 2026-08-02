	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b1cbc
FUN_080b1cbc: @ 0x080B1CBC
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r5, r0, #0
	adds r0, #0xbc
	ldrb r6, [r0]
	cmp r6, #0
	beq _080B1D24
	subs r0, #0x30
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	str r0, [sp]
	str r1, [sp, #4]
	movs r1, #0x80
	lsls r1, r1, #4
	ldr r0, [sp]
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r1, [r5, #0x28]
	movs r2, #4
	ldrsh r0, [r1, r2]
	cmp r0, #2
	beq _080B1D0E
	ldr r0, [r1, #0x1c]
	adds r0, #1
	str r0, [r1, #0x1c]
	ldr r0, _080B1D20 @ =0x00000137
	bl PlaySound
_080B1D0E:
	movs r0, #0x2a
	bl PlaySound
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	b _080B1EE2
	.align 2, 0
_080B1D20: .4byte 0x00000137
_080B1D24:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	movs r7, #0
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B1D34
	b _080B1ED6
_080B1D34:
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _080B1E0C
	cmp r0, #1
	bgt _080B1D44
	cmp r0, #0
	beq _080B1D52
	b _080B1EF4
_080B1D44:
	cmp r0, #2
	bne _080B1D4A
	b _080B1E5C
_080B1D4A:
	cmp r0, #3
	bne _080B1D50
	b _080B1EA0
_080B1D50:
	b _080B1EF4
_080B1D52:
	adds r0, r5, #0
	bl InitNonAffineMotion
	adds r0, r5, #0
	adds r0, #0x24
	strb r6, [r0]
	adds r0, #0x2c
	movs r1, #0x80
	lsls r1, r1, #1
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _080B1D9C
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080B1D94 @ =0x0836D824
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldr r1, _080B1D98 @ =0x00000E08
	b _080B1DC0
	.align 2, 0
_080B1D94: .4byte 0x0836D824
_080B1D98: .4byte 0x00000E08
_080B1D9C:
	cmp r0, #1
	bne _080B1DD0
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080B1DC8 @ =0x0836D83C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldr r1, _080B1DCC @ =0x00000E07
_080B1DC0:
	adds r0, r5, #0
	bl SetMotion
	b _080B1DFA
	.align 2, 0
_080B1DC8: .4byte 0x0836D83C
_080B1DCC: .4byte 0x00000E07
_080B1DD0:
	adds r4, r5, #0
	adds r4, #0x74
	cmp r0, #2
	bne _080B1DFA
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080B1E4C @ =0x0836D854
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldr r1, _080B1E50 @ =0x00000E09
	adds r0, r5, #0
	bl SetMotion
_080B1DFA:
	ldr r0, _080B1E54 @ =FUN_080b21c0
	str r0, [r4, #0x24]
	movs r0, #0
	str r0, [r5, #0x60]
	subs r0, #0xa8
	str r0, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080B1E0C:
	ldr r0, [r5, #0x60]
	adds r0, #0x10
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080B1E1C
	str r1, [r5, #0x60]
_080B1E1C:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, _080B1E58 @ =0xFFFFF800
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	movs r2, #0xb0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	beq _080B1EF4
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	b _080B1E94
	.align 2, 0
_080B1E4C: .4byte 0x0836D854
_080B1E50: .4byte 0x00000E09
_080B1E54: .4byte FUN_080b21c0
_080B1E58: .4byte 0xFFFFF800
_080B1E5C:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #4
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	ldr r2, _080B1E9C @ =0xFFFFF000
	adds r1, r1, r2
	bl FUN_08009f6c
	ldr r1, [r5, #0x58]
	movs r2, #0xb0
	lsls r2, r2, #4
	adds r1, r1, r2
	cmp r0, r1
	beq _080B1EF4
	str r6, [r5, #0x60]
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
	movs r0, #0x28
	strb r0, [r5, #0x13]
_080B1E94:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080B1EF4
	.align 2, 0
_080B1E9C: .4byte 0xFFFFF000
_080B1EA0:
	ldr r0, [r5, #0x60]
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080B1EB0
	str r1, [r5, #0x60]
_080B1EB0:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _080B1ED6
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B1EF4
_080B1ED6:
	ldr r1, [r5, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	beq _080B1EE2
	subs r0, #1
	strb r0, [r1, #0xc]
_080B1EE2:
	ldr r1, _080B1EFC @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080B1EF4:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080B1EFC: .4byte gProjectileFnTable
