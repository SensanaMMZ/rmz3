	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Cattatank_Init
Cattatank_Init: @ 0x0809889C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	movs r1, #0
	mov r8, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08098910 @ =0x0836A4D8
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #8
	bl InitBody
	str r6, [r4, #0x2c]
	ldr r0, _08098914 @ =FUN_08099eb4
	str r0, [r4, #0x24]
	adds r7, r6, #0
	adds r7, #0xb8
	strb r5, [r7]
	adds r0, r6, #0
	adds r0, #0xbc
	str r5, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _08098918
	movs r5, #1
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	subs r4, #0x28
	strb r5, [r4]
	adds r2, r6, #0
	adds r2, #0x4a
	movs r3, #0x10
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r3
	strb r0, [r2]
	strb r5, [r7]
	adds r3, r2, #0
	b _0809893A
	.align 2, 0
_08098910: .4byte 0x0836A4D8
_08098914: .4byte FUN_08099eb4
_08098918:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r3, r6, #0
	adds r3, #0x4c
	strb r5, [r3]
	adds r1, r6, #0
	adds r1, #0x4a
	ldrb r2, [r1]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	strb r0, [r1]
	strb r5, [r7]
	adds r4, r3, #0
	adds r3, r1, #0
_0809893A:
	ldrb r5, [r6, #0x11]
	cmp r5, #1
	bne _080989A4
	ldr r0, _08098968 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r6, #0x54]
	cmp r1, r0
	bge _0809896C
	movs r2, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	strb r2, [r4]
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	strb r2, [r7]
	b _08098986
	.align 2, 0
_08098968: .4byte pZero2
_0809896C:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	strb r5, [r4]
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	strb r5, [r7]
_08098986:
	ldr r1, _080989A0 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #0
	strb r0, [r6, #0xd]
	b _080989BA
	.align 2, 0
_080989A0: .4byte gEnemyFnTable
_080989A4:
	ldr r1, _08098A00 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #0
	strb r1, [r6, #0xd]
_080989BA:
	strb r0, [r6, #0xe]
	strb r0, [r6, #0xf]
	movs r4, #0
	str r4, [r6, #0x60]
	str r4, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xbb
	strb r4, [r0]
	str r4, [r6, #0x5c]
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	beq _080989E4
	ldr r1, _08098A04 @ =0x0000D503
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080989E4:
	adds r0, r6, #0
	adds r0, #0xc0
	strb r4, [r0]
	subs r0, #6
	strb r4, [r0]
	adds r0, r6, #0
	bl Cattatank_Update
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098A00: .4byte gEnemyFnTable
_08098A04: .4byte 0x0000D503

