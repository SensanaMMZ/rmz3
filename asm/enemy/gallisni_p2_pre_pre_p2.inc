	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080873a0
FUN_080873a0: @ 0x080873A0
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _080873B6
	bl isKilled
	cmp r0, #0
	beq _080873D6
_080873B6:
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080873F4 @ =0x08368708
	bl SetDDP
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _080873D6
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080873D6:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _080873F8 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _080873EC
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080873EC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080873F4: .4byte 0x08368708
_080873F8: .4byte 0x00020001
