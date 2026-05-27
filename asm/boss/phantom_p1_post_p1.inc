	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f794
FUN_0805f794: @ 0x0805F794
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F7CA
	movs r2, #0
	movs r0, #2
	strb r0, [r4, #0xf]
	adds r3, r4, #0
	adds r3, #0xb7
	ldrb r1, [r3]
	adds r0, r1, #1
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	adds r1, #8
	strb r1, [r3]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r4, #0x54]
	str r0, [r1]
	strb r2, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_0805f7d0
_0805F7CA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f7d0
FUN_0805f7d0: @ 0x0805F7D0
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r1, [r5, #0x12]
	adds r1, #1
	strb r1, [r5, #0x12]
	adds r0, #0xbc
	adds r2, r5, #0
	adds r2, #0xb8
	ldr r0, [r0]
	ldr r4, [r2]
	subs r0, r0, r4
	muls r0, r1, r0
	adds r1, r5, #0
	adds r1, #0xb7
	ldrb r1, [r1]
	bl __divsi3
	adds r4, r4, r0
	str r4, [r5, #0x54]
	adds r0, r5, #0
	bl FUN_08060924
	ldr r0, [r5, #0x60]
	cmp r0, #0
	ble _0805F818
	ldr r0, [r5, #0x2c]
	ldr r0, [r0, #0x58]
	subs r0, #0x80
	ldr r1, [r5, #0x58]
	cmp r1, r0
	blt _0805F818
	movs r0, #4
	strh r0, [r5, #0xe]
	adds r0, r5, #0
	bl FUN_0805f820
_0805F818:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
