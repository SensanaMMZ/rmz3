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

	thumb_func_start FUN_08075a84
FUN_08075a84: @ 0x08075A84
	push {lr}
	sub sp, #8
	ldr r1, [r0, #0x54]
	str r1, [sp]
	ldr r0, [r0, #0x58]
	ldr r1, _08075AA4 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	movs r1, #0
	bl FUN_080b9228
	movs r0, #1
	add sp, #8
	pop {r1}
	bx r1
	.align 2, 0
_08075AA4: .4byte 0xFFFFF000
