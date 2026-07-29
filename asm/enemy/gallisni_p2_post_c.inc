	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08087988
FUN_08087988: @ 0x08087988
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _0808799A
	cmp r0, #1
	beq _08087A58
	b _08087A9E
_0808799A:
	movs r3, #0
	ldr r0, _080879BC @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r6, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _080879AC
	movs r3, #1
_080879AC:
	adds r4, r3, #0
	adds r2, r4, #0
	cmp r4, #0
	beq _080879C0
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080879C6
	.align 2, 0
_080879BC: .4byte pZero2
_080879C0:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080879C6:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	movs r5, #0
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	lsls r1, r4, #8
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	ldr r1, _08087AA8 @ =0x00006707
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r0, [r6, #0x54]
	str r0, [sp, #8]
	ldr r0, [r6, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r4, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r0, r0, #6
	subs r0, r1, r0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	adds r1, r6, #0
	adds r1, #0x54
	ldr r0, _08087AAC @ =0x08368760
	str r0, [sp]
	movs r4, #0x18
	str r4, [sp, #4]
	adds r0, r6, #0
	add r2, sp, #8
	movs r3, #0x40
	bl FUN_080b857c
	ldr r0, [sp, #8]
	lsrs r1, r0, #0x1f
	adds r0, r0, r1
	asrs r0, r0, #1
	str r0, [r6, #0x5c]
	str r5, [r6, #0x60]
	strb r4, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08087A58:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x60]
	adds r0, #0x20
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08087A70
	str r1, [r6, #0x60]
_08087A70:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08087A98
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08087A9E
_08087A98:
	adds r0, r6, #0
	bl FUN_080878f0
_08087A9E:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08087AA8: .4byte 0x00006707
_08087AAC: .4byte 0x08368760

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
