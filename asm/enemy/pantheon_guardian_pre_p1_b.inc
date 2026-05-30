	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08063da0
FUN_08063da0: @ 0x08063DA0
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0xbc
	ldr r1, [r0]
	ldr r0, _08063E0C @ =0x00002FFF
	cmp r1, r0
	bhi _08063DB6
	movs r1, #0
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063DB6:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08063DCC
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063DCC:
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _08063DDE
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063DDE:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x40
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _08063DF6
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063DF6:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08063E06
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08063E06:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08063E0C: .4byte 0x00002FFF
