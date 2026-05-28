	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b9b9c
FUN_080b9b9c: @ 0x080B9B9C
	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080B9BCC @ =0x00001701
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080B9BD0
	movs r0, #0x40
	str r0, [r4, #0x5c]
	subs r0, #0x42
	b _080B9BD8
	.align 2, 0
_080B9BCC: .4byte 0x00001701
_080B9BD0:
	movs r0, #0x40
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	movs r0, #2
_080B9BD8:
	str r0, [r4, #0x64]
	movs r0, #0x40
	str r0, [r4, #0x60]
	subs r0, #0x42
	str r0, [r4, #0x68]
	movs r0, #0x20
	strb r0, [r4, #0x12]
	ldr r1, _080B9C04 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Ghost27_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B9C04: .4byte gVFXFnTable
