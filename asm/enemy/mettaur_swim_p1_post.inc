	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08089218
FUN_08089218: @ 0x08089218
	push {lr}
	ldr r3, [r0, #0x2c]
	ldr r1, [r0, #0xc]
	ldr r2, [r1, #0x2c]
	ldr r0, [r0, #0x14]
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _08089248
	ldrh r1, [r2, #8]
	ldr r0, _0808925C @ =0x00001206
	cmp r1, r0
	bne _08089248
	ldr r1, _08089260 @ =gEnemyFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	movs r0, #0
	strb r0, [r3, #0xd]
_08089248:
	adds r2, r3, #0
	adds r2, #0xb4
	ldr r0, _08089264 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	str r0, [r2]
	pop {r0}
	bx r0
	.align 2, 0
_0808925C: .4byte 0x00001206
_08089260: .4byte gEnemyFnTable
_08089264: .4byte pZero2

