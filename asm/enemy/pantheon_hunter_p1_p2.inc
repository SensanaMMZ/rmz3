	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08064c38
FUN_08064c38: @ 0x08064C38
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _08064C54
	movs r1, #0x98
	lsls r1, r1, #5
	bl SetMotion
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08064C54:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08064C6A
	str r1, [r4, #0x60]
_08064C6A:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _08064CA4 @ =0x0000800F
	cmp r1, r0
	beq _08064C9C
	cmp r1, #0
	beq _08064C9C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	movs r0, #6
	strb r0, [r4, #0xf]
_08064C9C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08064CA4: .4byte 0x0000800F
