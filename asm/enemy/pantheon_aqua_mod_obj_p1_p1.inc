	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createPAquaModRubble
createPAquaModRubble: @ 0x08080804
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _08080850 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0808084A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080854 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #8
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
_0808084A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080850: .4byte gEnemyHeaderPtr
_08080854: .4byte gEnemyFnTable
