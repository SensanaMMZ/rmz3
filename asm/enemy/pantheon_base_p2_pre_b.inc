	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start PantheonBase_Update
PantheonBase_Update: @ 0x0808A304
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, _0808A320 @ =gCurStory
	ldrb r0, [r0, #8]
	movs r2, #0x42
	ands r2, r0
	cmp r2, #0
	beq _0808A324
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	b _0808A332
	.align 2, 0
_0808A320: .4byte gCurStory
_0808A324:
	ldr r5, [r4, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #2
	bls _0808A368
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0808A332:
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0808A364 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _0808A3CE
	.align 2, 0
_0808A364: .4byte gEnemyFnTable
_0808A368:
	adds r0, r4, #0
	bl FUN_0808a144
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _0808A3CE
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _0808A39C
	ldr r1, _0808A398 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
	adds r0, r4, #0
	bl PantheonBase_Die
	b _0808A3CE
	.align 2, 0
_0808A398: .4byte gEnemyFnTable
_0808A39C:
	adds r0, r4, #0
	bl pBase_0808a210
	adds r0, r4, #0
	bl pBase_0808a194
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808A3CE
	ldr r1, _0808A3D4 @ =0x0836896C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808A3D8 @ =0x08368974
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_0808A3CE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808A3D4: .4byte 0x0836896C
_0808A3D8: .4byte 0x08368974

