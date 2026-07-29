	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0806f5d0
FUN_0806f5d0: @ 0x0806F5D0
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r6, #0
	movs r7, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _0806F654 @ =0x08366970
	adds r2, r5, #0
	adds r2, #0x54
	movs r3, #0x80
	lsls r3, r3, #1
	adds r0, r4, #0
	bl InitBody
	str r5, [r4, #0x2c]
	ldr r0, _0806F658 @ =FUN_08070000
	str r0, [r4, #0x24]
	adds r0, r5, #0
	adds r0, #0xbc
	str r7, [r0]
	ldr r0, _0806F65C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _0806F660
	movs r0, #0x80
	str r0, [r5, #0x5c]
	movs r2, #1
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	b _0806F682
	.align 2, 0
_0806F654: .4byte 0x08366970
_0806F658: .4byte FUN_08070000
_0806F65C: .4byte pZero2
_0806F660:
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r7, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
_0806F682:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_08009f6c
	str r0, [r5, #0x58]
	adds r1, r5, #0
	adds r1, #0xb4
	ldr r0, [r5, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r5, #0x58]
	str r0, [r1]
	adds r0, r5, #0
	adds r0, #0xc2
	movs r1, #0
	strb r1, [r0]
	strb r1, [r5, #0x12]
	ldr r2, _0806F6C8 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r2, #1
	str r2, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	strb r1, [r5, #0xd]
	strb r2, [r5, #0xe]
	adds r0, r5, #0
	bl Enemy14_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806F6C8: .4byte gEnemyFnTable
