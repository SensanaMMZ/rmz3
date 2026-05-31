	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0808f27c
FUN_0808f27c: @ 0x0808F27C
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r4, r1, #0
	adds r6, r2, #0
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	ldr r0, _0808F2DC @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _0808F2D2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0808F2E0 @ =gEnemyFnTable
	movs r1, #0x39
	strb r1, [r3, #9]
	adds r0, #0xe4
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
	movs r0, #1
	strb r0, [r3, #0x10]
	str r4, [r3, #0x64]
	str r4, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r5, [r3, #0x12]
	str r7, [r3, #0x28]
_0808F2D2:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0808F2DC: .4byte gEnemyHeaderPtr
_0808F2E0: .4byte gEnemyFnTable

	thumb_func_start FUN_0808f2e4
FUN_0808f2e4: @ 0x0808F2E4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _0808F33C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _0808F334
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0808F340 @ =gEnemyFnTable
	movs r1, #0x39
	strb r1, [r3, #9]
	adds r0, #0xe4
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
	movs r0, #2
	strb r0, [r3, #0x10]
	str r5, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r4, [r3, #0x12]
_0808F334:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808F33C: .4byte gEnemyHeaderPtr
_0808F340: .4byte gEnemyFnTable
_0808F344:
	.byte 0x70, 0x47, 0x00, 0x00

