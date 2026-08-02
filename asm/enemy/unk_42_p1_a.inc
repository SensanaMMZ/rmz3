	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08084e7c
FUN_08084e7c: @ 0x08084E7C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldr r1, _08084ED0 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r7, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0xbc
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r5, #0xb]
	ldrb r0, [r6, #0x1c]
	strb r0, [r5, #0x1d]
	ldrb r0, [r6, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _08084ED4
	ldrb r0, [r5, #0xa]
	orrs r0, r1
	b _08084EDA
	.align 2, 0
_08084ED0: .4byte gEnemyFnTable
_08084ED4:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08084EDA:
	strb r0, [r5, #0xa]
	movs r3, #1
	adds r1, r3, #0
	ands r1, r2
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [r5, #0x54]
	str r1, [r5, #0x58]
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	strb r3, [r5, #0xe]
	adds r0, r5, #0
	bl Enemy42_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
