	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08082348
FUN_08082348: @ 0x08082348
	push {lr}
	adds r1, r0, #0
	ldr r3, [r1, #0x2c]
	cmp r3, #0
	beq _0808239C
	ldr r0, [r3, #0x2c]
	cmp r0, #0
	beq _0808235A
	str r1, [r0, #0x28]
_0808235A:
	ldr r0, [r3, #0x2c]
	str r0, [r1, #0x2c]
	adds r1, #0xb4
	ldrb r0, [r1]
	subs r0, #1
	movs r2, #0
	strb r0, [r1]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _080823A0 @ =gEnemyFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
_0808239C:
	pop {r0}
	bx r0
	.align 2, 0
_080823A0: .4byte gEnemyFnTable
