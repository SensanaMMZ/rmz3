	.include "asm/macros.inc"

	.syntax unified

	.text

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
