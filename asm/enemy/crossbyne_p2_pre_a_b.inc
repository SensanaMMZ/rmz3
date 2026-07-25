	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Crossbyne_Init
Crossbyne_Init: @ 0x0807CE0C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r1, _0807CE68 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r1, _0807CE6C @ =0x08367C3C
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
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	bls _0807CE74
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0807CE70 @ =0x08367B9C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #2
	bl InitBody
	str r6, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
	b _0807CED4
	.align 2, 0
_0807CE68: .4byte gEnemyFnTable
_0807CE6C: .4byte 0x08367C3C
_0807CE70: .4byte 0x08367B9C
_0807CE74:
	ldr r0, _0807CEA8 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x10]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _0807CEB4
	ldr r0, _0807CEAC @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0807CEB4
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0807CEB0 @ =0x08367B9C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #8
	b _0807CECC
	.align 2, 0
_0807CEA8: .4byte gSystemSavedataManager
_0807CEAC: .4byte gCurStory
_0807CEB0: .4byte 0x08367B9C
_0807CEB4:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0807CEF8 @ =0x08367B9C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
_0807CECC:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
_0807CED4:
	ldr r0, _0807CEFC @ =nop_0807cd70
	str r0, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	str r0, [r1]
	adds r1, #4
	movs r0, #1
	strb r0, [r1]
	subs r1, #0x93
	movs r0, #0x14
	strb r0, [r1]
	adds r0, r6, #0
	bl Crossbyne_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807CEF8: .4byte 0x08367B9C
_0807CEFC: .4byte nop_0807cd70

