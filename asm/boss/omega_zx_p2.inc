	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08060f9c
FUN_08060f9c: @ 0x08060F9C
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0xe]
	cmp r0, #0
	beq _08060FAC
	cmp r0, #1
	beq _08060FB0
	b _08060FCC
_08060FAC:
	movs r0, #1
	strb r0, [r2, #0xe]
_08060FB0:
	ldr r0, [r2, #0x18]
	ldrb r1, [r0, #9]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _08060FCC
	ldr r0, _08060FD0 @ =gOverworld
	ldr r1, _08060FD4 @ =0x0002D025
	adds r0, r0, r1
	movs r1, #0
	strb r3, [r0]
	strb r3, [r2, #0xd]
	strb r1, [r2, #0xe]
_08060FCC:
	pop {r0}
	bx r0
	.align 2, 0
_08060FD0: .4byte gOverworld
_08060FD4: .4byte 0x0002D025
