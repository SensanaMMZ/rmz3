	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08083258
FUN_08083258: @ 0x08083258
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0xe]
	cmp r0, #0
	bne _0808327C
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _08083280 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r2, #0x14]
_0808327C:
	pop {r0}
	bx r0
	.align 2, 0
_08083280: .4byte gEnemyFnTable

