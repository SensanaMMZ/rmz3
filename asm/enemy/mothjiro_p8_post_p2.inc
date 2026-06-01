	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08088b0c
FUN_08088b0c: @ 0x08088B0C
	push {lr}
	adds r2, r0, #0
	adds r3, r1, #0
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #4]
	cmp r0, #3
	beq _08088B24
	cmp r0, #0xe
	beq _08088B24
	cmp r0, #0xf
	bne _08088B46
_08088B24:
	ldr r2, [r2, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08088B46
	ldr r1, [r2, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _08088B42
	movs r0, #0xff
	b _08088B44
_08088B42:
	movs r0, #0xfe
_08088B44:
	strb r0, [r2, #0x11]
_08088B46:
	pop {r0}
	bx r0
	.align 2, 0
