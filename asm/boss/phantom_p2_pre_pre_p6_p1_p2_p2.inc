	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805ffec
FUN_0805ffec: @ 0x0805FFEC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	beq _08060006
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0806000C
_08060006:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0806000C:
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl FUN_08060924
	ldr r0, [r5, #0x60]
	cmp r0, #0
	ble _08060038
	adds r1, r5, #0
	adds r1, #0xc4
	movs r0, #1
	str r0, [r1]
	ldrb r1, [r5, #0xa]
	movs r4, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	movs r1, #8
	bl FUN_080607a0
	strb r4, [r5, #0x12]
	movs r0, #3
	strb r0, [r5, #0xf]
_08060038:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

