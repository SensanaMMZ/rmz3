	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08096fb0
FUN_08096fb0: @ 0x08096FB0
	push {r4, lr}
	adds r3, r0, #0
	ldr r1, [r3, #0x54]
	str r1, [r3, #0x64]
	ldr r1, [r3, #0x58]
	str r1, [r3, #0x68]
	adds r2, r3, #0
	adds r2, #0xc0
	movs r1, #0
	str r1, [r2]
	ldr r1, _08096FF4 @ =0xFFFFFE00
	str r1, [r3, #0x5c]
	adds r4, r1, #0
	ldrb r2, [r3, #0xa]
	movs r1, #0x10
	ands r1, r2
	cmp r1, #0
	beq _08096FD8
	movs r4, #0x80
	lsls r4, r4, #2
_08096FD8:
	str r4, [r3, #0x5c]
	ldr r1, _08096FF8 @ =0xFFFFFC00
	str r1, [r3, #0x60]
	adds r4, r1, #0
	movs r1, #0x20
	ands r1, r2
	cmp r1, #0
	beq _08096FEC
	movs r4, #0x80
	lsls r4, r4, #3
_08096FEC:
	str r4, [r3, #0x60]
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_08096FF4: .4byte 0xFFFFFE00
_08096FF8: .4byte 0xFFFFFC00
