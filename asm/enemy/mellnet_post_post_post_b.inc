	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807dee8
FUN_0807dee8: @ 0x0807DEE8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0807DEF8
	cmp r0, #1
	beq _0807DF2C
	b _0807DF90
_0807DEF8:
	movs r0, #0x84
	lsls r0, r0, #1
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r2, [r0]
	ldr r3, _0807DF98 @ =0x08367D5A
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	rsbs r0, r0, #0
	asrs r0, r0, #0x1f
	movs r1, #2
	ands r0, r1
	adds r0, r0, r3
	ldrh r1, [r0]
	adds r0, r4, #0
	movs r3, #3
	bl GotoMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807DF2C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0807DF8A
	ldr r0, _0807DF9C @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _0807DF8A
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
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
	ldr r1, _0807DFA0 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0807DF8A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0807DF90:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807DF98: .4byte 0x08367D5A
_0807DF9C: .4byte gStageRun+232
_0807DFA0: .4byte gEnemyFnTable
