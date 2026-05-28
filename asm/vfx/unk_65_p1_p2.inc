	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Ghost65_Init
Ghost65_Init: @ 0x080C42A8
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080C42E8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080C42EC @ =0x0836F59C
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl Ghost65_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C42E8: .4byte gVFXFnTable
_080C42EC: .4byte 0x0836F59C
