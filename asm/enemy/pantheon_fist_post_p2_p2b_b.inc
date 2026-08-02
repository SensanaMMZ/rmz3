	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_08095c20
FUN_08095c20: @ 0x08095C20
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08095C34
	cmp r5, #1
	bne _08095C32
	b _08095D34
_08095C32:
	b _08095D72
_08095C34:
	movs r6, #0
	ldr r0, _08095CB8 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _08095C46
	movs r6, #1
_08095C46:
	ldr r1, _08095CBC @ =0x0000D408
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
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
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #6
	subs r0, r1, r0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095CE0
	movs r0, #0x20
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08095CC4
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095CC0 @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b84f4
	b _08095D1A
	.align 2, 0
_08095CB8: .4byte pZero2
_08095CBC: .4byte 0x0000D408
_08095CC0: .4byte 0x0836A074
_08095CC4:
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095CDC @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b857c
	b _08095D1A
	.align 2, 0
_08095CDC: .4byte 0x0836A074
_08095CE0:
	str r5, [r4, #0x68]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08095D04
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095D00 @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b834c
	b _08095D1A
	.align 2, 0
_08095D00: .4byte 0x0836A074
_08095D04:
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095D7C @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b83d4
_08095D1A:
	ldr r0, [sp, #8]
	cmp r0, #0
	bge _08095D22
	adds r0, #3
_08095D22:
	asrs r0, r0, #2
	str r0, [r4, #0x5c]
	movs r0, #0
	str r0, [r4, #0x60]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095D34:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x68]
	cmp r1, #0
	beq _08095D58
	ldr r0, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08095D50
	str r1, [r4, #0x60]
_08095D50:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08094fe0
_08095D58:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095D72
	adds r0, r4, #0
	bl FUN_08095b70
_08095D72:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08095D7C: .4byte 0x0836A074
