	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807ff40
FUN_0807ff40: @ 0x0807FF40
	push {lr}
	adds r2, r0, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807FF66
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _0807FF5E
	movs r0, #7
	b _0807FF60
_0807FF5E:
	movs r0, #6
_0807FF60:
	strb r0, [r2, #0xd]
	movs r0, #0
	strb r0, [r2, #0xe]
_0807FF66:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0807ff6c
FUN_0807ff6c: @ 0x0807FF6C
	push {lr}
	adds r2, r0, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807FF8E
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _0807FF8E
	movs r1, #0
	movs r0, #7
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_0807FF8E:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0807ff94
FUN_0807ff94: @ 0x0807FF94
	push {lr}
	adds r2, r0, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r0, #0x80
	lsls r0, r0, #4
	ands r1, r0
	cmp r1, #0
	bne _0807FFAC
	movs r0, #5
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_0807FFAC:
	pop {r0}
	bx r0
