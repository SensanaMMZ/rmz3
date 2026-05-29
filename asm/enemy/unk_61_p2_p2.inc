	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Enemy61_Die
Enemy61_Die: @ 0x08093704
	push {lr}
	adds r2, r0, #0
	ldr r3, [r2, #0x28]
	ldrb r1, [r2, #0xe]
	cmp r1, #0
	beq _08093716
	cmp r1, #1
	beq _08093732
	b _0809374A
_08093716:
	adds r0, r2, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldrb r0, [r2, #0xe]
	adds r0, #1
	strb r0, [r2, #0xe]
_08093732:
	ldrb r0, [r3, #0xc]
	cmp r0, #2
	bls _0809374A
	ldr r1, _08093750 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r2, #0x14]
_0809374A:
	pop {r0}
	bx r0
	.align 2, 0
_08093750: .4byte gEnemyFnTable
