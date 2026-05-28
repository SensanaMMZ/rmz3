	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08075a5c
FUN_08075a5c: @ 0x08075A5C
	push {lr}
	adds r3, r0, #0
	ldr r0, [r3, #0xc]
	ldr r0, [r0, #4]
	ldrb r2, [r0, #2]
	cmp r2, #1
	bne _08075A7C
	ldr r0, [r0, #4]
	ldr r1, _08075A80 @ =0x000200FF
	ands r0, r1
	subs r1, #0xfd
	cmp r0, r1
	bne _08075A7C
	ldr r0, [r3, #0x2c]
	adds r0, #0xb5
	strb r2, [r0]
_08075A7C:
	pop {r0}
	bx r0
	.align 2, 0
_08075A80: .4byte 0x000200FF
