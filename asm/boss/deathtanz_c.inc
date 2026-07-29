	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start deathtanzMode6
deathtanzMode6: @ 0x08049928
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #7
	bls _08049934
	b _08049B46
_08049934:
	lsls r0, r0, #2
	ldr r1, _08049940 @ =_08049944
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08049940: .4byte _08049944
_08049944: @ jump table
	.4byte _08049964 @ case 0
	.4byte _08049A00 @ case 1
	.4byte _08049A44 @ case 2
	.4byte _08049A5C @ case 3
	.4byte _08049A98 @ case 4
	.4byte _08049ABA @ case 5
	.4byte _08049AD2 @ case 6
	.4byte _08049B2E @ case 7
_08049964:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804999C @ =sCollisions+(24*15)
	bl SetDDP
	adds r3, r5, #0
	adds r3, #0xb4
	ldr r1, [r5, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _080499A0
	adds r1, r5, #0
	adds r1, #0x4c
	movs r0, #1
	strb r0, [r1]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r5, #0xa]
	orrs r1, r0
	strb r1, [r5, #0xa]
	ldr r0, [r3]
	movs r1, #0xa8
	lsls r1, r1, #7
	b _080499C0
	.align 2, 0
_0804999C: .4byte sCollisions+(24*15)
_080499A0:
	adds r1, r5, #0
	adds r1, #0x4c
	movs r0, #0
	strb r0, [r1]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	subs r0, #0x11
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r3]
	ldr r1, _08049A38 @ =0xFFFFAC00
_080499C0:
	adds r6, r0, r1
	str r6, [r5, #0x64]
	ldr r4, _08049A3C @ =0x00000666
	adds r0, r4, #0
	bl Sqrt
	adds r0, #0x10
	strb r0, [r5, #0x12]
	ldr r0, [r5, #0x54]
	subs r0, r6, r0
	ldrb r1, [r5, #0x12]
	bl __divsi3
	str r0, [r5, #0x5c]
	adds r0, r4, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #3
	adds r1, r1, r0
	rsbs r1, r1, #0
	str r1, [r5, #0x60]
	ldr r1, _08049A40 @ =0x0000A70A
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049A00:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x19
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08049A18
	str r1, [r5, #0x60]
_08049A18:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bls _08049A36
	b _08049B46
_08049A36:
	b _08049ACA
	.align 2, 0
_08049A38: .4byte 0xFFFFAC00
_08049A3C: .4byte 0x00000666
_08049A40: .4byte 0x0000A70A
_08049A44:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049A90 @ =0x083629D4
	bl SetDDP
	ldr r1, _08049A94 @ =0x0000A720
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049A5C:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x19
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08049A74
	str r1, [r5, #0x60]
_08049A74:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08049B46
	b _08049ACA
	.align 2, 0
_08049A90: .4byte sCollisions+(24*21)
_08049A94: .4byte 0x0000A720
_08049A98:
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	bge _08049AAC
	ldr r1, _08049AA8 @ =0xFFFFAC00
	b _08049AB0
	.align 2, 0
_08049AA8: .4byte 0xFFFFAC00
_08049AAC:
	movs r1, #0xa8
	lsls r1, r1, #7
_08049AB0:
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049ABA:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049B46
_08049ACA:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _08049B46
_08049AD2:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049B14 @ =0x08362A1C
	bl SetDDP
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _08049B18
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08049B1E
	.align 2, 0
_08049B14: .4byte sCollisions+(24*24)
_08049B18:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08049B1E:
	strb r0, [r5, #0xa]
	ldr r1, _08049B4C @ =0x0000A721
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049B2E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049B46
	movs r1, #0
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08049B46:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08049B4C: .4byte 0x0000A721
