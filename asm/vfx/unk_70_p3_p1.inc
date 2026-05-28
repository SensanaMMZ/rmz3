	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c572c
FUN_080c572c: @ 0x080C572C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldr r1, _080C5760 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Ghost70_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C5760: .4byte gVFXFnTable
