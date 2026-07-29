	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806ee94
FUN_0806ee94: @ 0x0806EE94
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0806EEA4
	cmp r0, #1
	beq _0806EEDE
	b _0806EF9E
_0806EEA4:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0806EEB8
	ldr r1, _0806EEB4 @ =0x00001D05
	adds r0, r4, #0
	bl SetMotion
	b _0806EEC0
	.align 2, 0
_0806EEB4: .4byte 0x00001D05
_0806EEB8:
	ldr r1, _0806EEFC @ =0x00001D0B
	adds r0, r4, #0
	bl SetMotion
_0806EEC0:
	movs r0, #0
	strb r0, [r4, #0x12]
	ldr r0, _0806EF00 @ =0xFFFFFA64
	str r0, [r4, #0x60]
	ldr r1, [r4, #0x5c]
	movs r0, #0xd0
	muls r0, r1, r0
	cmp r0, #0
	bge _0806EED4
	adds r0, #0xff
_0806EED4:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806EEDE:
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x12
	bne _0806EF10
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0806EF08
	ldr r1, _0806EF04 @ =0x00001D06
	adds r0, r4, #0
	bl SetMotion
	b _0806EF10
	.align 2, 0
_0806EEFC: .4byte 0x00001D0B
_0806EF00: .4byte 0xFFFFFA64
_0806EF04: .4byte 0x00001D06
_0806EF08:
	ldr r1, _0806EF68 @ =0x00001D0C
	adds r0, r4, #0
	bl SetMotion
_0806EF10:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0806EF26
	str r1, [r4, #0x60]
_0806EF26:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r1, r0, r1
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _0806EF46
	ldr r0, [r4, #0x54]
	bl PushoutToDown1
	adds r1, r0, #0
	cmp r1, #0
	ble _0806EF46
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0806EF46:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r2, r0, r1
	str r2, [r4, #0x54]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _0806EF80
	cmp r1, #0
	ble _0806EF6C
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl PushoutToLeft1
	adds r1, r0, #0
	cmp r1, #0
	bge _0806EF80
	b _0806EF7A
	.align 2, 0
_0806EF68: .4byte 0x00001D0C
_0806EF6C:
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl PushoutToRight1
	adds r1, r0, #0
	cmp r1, #0
	ble _0806EF80
_0806EF7A:
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0806EF80:
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0806EF8E
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806EF8E:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _0806EF9E
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	strb r0, [r4, #0x13]
_0806EF9E:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0806efa4
FUN_0806efa4: @ 0x0806EFA4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0806EFE8
	cmp r0, #1
	bgt _0806EFB8
	cmp r0, #0
	beq _0806EFC2
	b _0806F06C
_0806EFB8:
	cmp r0, #2
	beq _0806F014
	cmp r0, #3
	beq _0806F042
	b _0806F06C
_0806EFC2:
	movs r0, #8
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0806EFD4
	ldr r1, _0806F00C @ =0x00001D08
	adds r0, r4, #0
	bl SetMotion
_0806EFD4:
	ldrb r0, [r4, #0x10]
	cmp r0, #3
	bne _0806EFE2
	ldr r1, _0806F010 @ =0x00001D0E
	adds r0, r4, #0
	bl SetMotion
_0806EFE2:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806EFE8:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0806EFFA
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806EFFA:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	beq _0806F004
	cmp r0, #3
	bne _0806F06C
_0806F004:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0806F06C
	.align 2, 0
_0806F00C: .4byte 0x00001D08
_0806F010: .4byte 0x00001D0E
_0806F014:
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0806F02A
	ldr r1, _0806F074 @ =0x00001D09
	adds r0, r4, #0
	movs r2, #1
	movs r3, #8
	bl GotoMotion
_0806F02A:
	ldrb r0, [r4, #0x10]
	cmp r0, #3
	bne _0806F03C
	ldr r1, _0806F078 @ =0x00001D0F
	adds r0, r4, #0
	movs r2, #1
	movs r3, #8
	bl GotoMotion
_0806F03C:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806F042:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	beq _0806F04C
	cmp r0, #3
	bne _0806F052
_0806F04C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0806F052:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0806F06C
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0xbd
	strb r1, [r0]
_0806F06C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0806F074: .4byte 0x00001D09
_0806F078: .4byte 0x00001D0F

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

	thumb_func_start FUN_0806f1dc
FUN_0806f1dc: @ 0x0806F1DC
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0806F260 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _0806F264 @ =0x08366930
	adds r0, r4, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b7f70
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #3
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _0806F268 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0806F26C @ =0x0000270E
	cmp r1, r0
	bhi _0806F23C
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0806F23C:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _0806F270 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0806F260: .4byte 0xFFFFF000
_0806F264: .4byte 0x08366930
_0806F268: .4byte gMission
_0806F26C: .4byte 0x0000270E
_0806F270: .4byte gEnemyFnTable

	thumb_func_start FUN_0806f274
FUN_0806f274: @ 0x0806F274
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0806F286
	cmp r0, #1
	beq _0806F36C
	b _0806F3BC
_0806F286:
	movs r3, #0
	ldr r0, _0806F328 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0806F298
	movs r3, #1
_0806F298:
	adds r7, r3, #0
	movs r6, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	beq _0806F2A6
	cmp r0, #3
	bne _0806F2A8
_0806F2A6:
	movs r6, #1
_0806F2A8:
	ldr r1, _0806F32C @ =0x00001D12
	cmp r6, #0
	beq _0806F2B0
	subs r1, #2
_0806F2B0:
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
	movs r5, #0
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp, #8]
	ldr r0, [r4, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r7, #0
	bl FUN_080b2b40
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _0806F2EC
	adds r0, #3
_0806F2EC:
	asrs r0, r0, #2
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	adds r1, r0, #0
	ldr r0, [r4, #0x58]
	subs r0, r1, r0
	ldr r1, _0806F330 @ =0x000003FF
	cmp r0, r1
	ble _0806F338
	movs r0, #0x20
	str r0, [r4, #0x68]
	adds r1, r4, #0
	adds r1, #0x54
	lsls r0, r6, #1
	ldr r2, _0806F334 @ =0x08366936
	adds r0, r0, r2
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b84f4
	b _0806F354
	.align 2, 0
_0806F328: .4byte pZero2
_0806F32C: .4byte 0x00001D12
_0806F330: .4byte 0x000003FF
_0806F334: .4byte 0x08366936
_0806F338:
	str r5, [r4, #0x68]
	adds r1, r4, #0
	adds r1, #0x54
	lsls r0, r6, #1
	ldr r2, _0806F3C4 @ =0x08366936
	adds r0, r0, r2
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b834c
_0806F354:
	ldr r0, [r4, #0x5c]
	movs r1, #0xa
	bl __divsi3
	str r0, [r4, #0x5c]
	movs r0, #0
	str r0, [r4, #0x60]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806F36C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x68]
	cmp r1, #0
	beq _0806F3A2
	ldr r0, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0806F388
	str r1, [r4, #0x60]
_0806F388:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _0806F3A2
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0806F3A2:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0806F3BC
	adds r0, r4, #0
	bl FUN_0806f1dc
_0806F3BC:
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806F3C4: .4byte 0x08366936
