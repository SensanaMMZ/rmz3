	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start PantheonBase_Init
PantheonBase_Init: @ 0x0808A248
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r1, _0808A2B0 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r1, _0808A2B4 @ =0x08368BE4
	ldrb r0, [r6, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r6, #0xd]
	ldrb r0, [r6, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldr r0, _0808A2B8 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x10]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0808A2C4
	ldr r0, _0808A2BC @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0808A2C4
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808A2C0 @ =0x08368984
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x10
	b _0808A2DC
	.align 2, 0
_0808A2B0: .4byte gEnemyFnTable
_0808A2B4: .4byte 0x08368BE4
_0808A2B8: .4byte gSystemSavedataManager
_0808A2BC: .4byte gCurStory
_0808A2C0: .4byte 0x08368984
_0808A2C4:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808A2FC @ =0x08368984
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xc
_0808A2DC:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _0808A300 @ =nop_0808a140
	str r0, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	str r0, [r1]
	adds r0, r6, #0
	bl PantheonBase_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808A2FC: .4byte 0x08368984
_0808A300: .4byte nop_0808a140

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

