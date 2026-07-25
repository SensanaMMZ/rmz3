	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start GeneratorCannon_Init
GeneratorCannon_Init: @ 0x0808C538
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r1, _0808C5C8 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r1, _0808C5CC @ =0x08369110
	ldrb r0, [r6, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	movs r5, #0
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
	adds r0, r6, #0
	adds r0, #0xb4
	str r5, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _0808C604
	ldrb r0, [r6, #0xb]
	movs r1, #8
	orrs r0, r1
	strb r0, [r6, #0xb]
	ldr r0, _0808C5D0 @ =0x08369114
	str r0, [r6, #0x30]
	ldr r0, _0808C5D4 @ =0x00000801
	strh r0, [r6, #0x26]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	str r0, [r6, #0x58]
	ldr r0, _0808C5D8 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x13]
	movs r2, #0x40
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _0808C5E4
	ldr r0, _0808C5DC @ =gCurStory
	ldrb r1, [r0, #4]
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	bne _0808C5E4
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808C5E0 @ =0x08368F58
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x18
	b _0808C620
	.align 2, 0
_0808C5C8: .4byte gEnemyFnTable
_0808C5CC: .4byte 0x08369110
_0808C5D0: .4byte 0x08369114
_0808C5D4: .4byte 0x00000801
_0808C5D8: .4byte gSystemSavedataManager
_0808C5DC: .4byte gCurStory
_0808C5E0: .4byte 0x08368F58
_0808C5E4:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808C600 @ =0x08368F58
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x14
	b _0808C620
	.align 2, 0
_0808C600: .4byte 0x08368F58
_0808C604:
	adds r0, r6, #0
	adds r0, #0xb8
	strb r5, [r0]
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808C638 @ =0x08368F58
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #5
_0808C620:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _0808C63C @ =onCollision
	str r0, [r4, #0x24]
	adds r0, r6, #0
	bl GeneratorCannon_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808C638: .4byte 0x08368F58
_0808C63C: .4byte onCollision

