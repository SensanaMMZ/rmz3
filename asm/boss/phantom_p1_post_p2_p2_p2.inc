	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_0805f8c4
FUN_0805f8c4: @ 0x0805F8C4
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bne _0805F91A
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	str r0, [sp, #4]
	movs r0, #0xfc
	bl PlaySound
	movs r4, #0xf0
	lsls r4, r4, #2
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x10
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x30
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x50
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x70
	movs r3, #1
	bl FUN_080afbfc
_0805F91A:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F928
	movs r0, #2
	strb r0, [r5, #0xf]
_0805F928:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
