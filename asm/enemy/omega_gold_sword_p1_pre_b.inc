	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start OmegaGoldSword_Update
OmegaGoldSword_Update: @ 0x0808B8B8
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0808B8F0
	adds r2, r4, #0
	adds r2, #0x49
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	ldr r1, _0808B8EC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl OmegaGoldSword_Die
	b _0808B910
	.align 2, 0
_0808B8EC: .4byte gEnemyFnTable
_0808B8F0:
	ldr r1, _0808B918 @ =0x08368D94
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808B91C @ =0x08368DA8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_0808B910:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808B918: .4byte 0x08368D94
_0808B91C: .4byte 0x08368DA8
