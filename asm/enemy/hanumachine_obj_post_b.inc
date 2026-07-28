	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08086e34
FUN_08086e34: @ 0x08086E34
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	bne _08086F2E
	ldr r1, _08086EA4 @ =0x00006A03
	adds r0, r6, #0
	bl SetMotion
	ldr r4, _08086EA8 @ =pZero2
	ldr r2, [r4]
	ldr r1, [r6, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x58]
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	ldr r2, _08086EAC @ =0xFFFFE800
	adds r0, r0, r2
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
	lsrs r5, r0, #0x10
	cmp r5, #0
	beq _08086EB0
	ldr r0, [r6, #0x5c]
	adds r1, r5, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r6, #0x5c]
	ldr r0, [r6, #0x60]
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
	b _08086ECA
	.align 2, 0
_08086EA4: .4byte 0x00006A03
_08086EA8: .4byte pZero2
_08086EAC: .4byte 0xFFFFE800
_08086EB0:
	ldr r0, [r4]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08086EC2
	movs r0, #0xc0
	lsls r0, r0, #3
	b _08086EC4
_08086EC2:
	ldr r0, _08086EF0 @ =0xFFFFFA00
_08086EC4:
	str r0, [r6, #0x5c]
	movs r0, #0
	str r0, [r6, #0x60]
_08086ECA:
	ldr r0, [r6, #0x5c]
	cmp r0, #0
	ble _08086EF4
	movs r2, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _08086F16
	.align 2, 0
_08086EF0: .4byte 0xFFFFFA00
_08086EF4:
	movs r2, #1
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_08086F16:
	adds r1, r6, #0
	adds r1, #0xbd
	movs r0, #1
	strb r0, [r1]
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08086F88 @ =0x08368648
	bl SetDDP
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08086F2E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x54]
	ldr r4, [r6, #0x5c]
	adds r3, r0, r4
	str r3, [r6, #0x54]
	ldr r1, [r6, #0x58]
	ldr r0, [r6, #0x60]
	adds r2, r1, r0
	str r2, [r6, #0x58]
	adds r0, #0x40
	str r0, [r6, #0x60]
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	bne _08086F7A
	adds r0, r3, r4
	adds r1, r2, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08086F7A
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	ldr r1, [r6, #0x58]
	ldr r2, _08086F8C @ =0xFFFFF000
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08086F82
_08086F7A:
	adds r1, r6, #0
	adds r1, #0xc0
	movs r0, #0
	strh r0, [r1]
_08086F82:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08086F88: .4byte 0x08368648
_08086F8C: .4byte 0xFFFFF000

