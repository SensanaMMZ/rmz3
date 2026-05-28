	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080612d8
FUN_080612d8: @ 0x080612D8
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bhi _080613B0
	lsls r0, r0, #2
	ldr r1, _080612F0 @ =_080612F4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080612F0: .4byte _080612F4
_080612F4: @ jump table
	.4byte _08061308 @ case 0
	.4byte _08061340 @ case 1
	.4byte _08061358 @ case 2
	.4byte _08061384 @ case 3
	.4byte _080613A2 @ case 4
_08061308:
	movs r0, #0xa7
	bl ClearBlink
	movs r0, #0xa8
	bl ClearBlink
	movs r0, #0xa9
	bl ClearBlink
	movs r0, #0xaa
	bl ClearBlink
	movs r1, #0xb0
	lsls r1, r1, #2
	movs r0, #0xaa
	bl LoadBlink
	adds r1, r4, #0
	adds r1, #0x54
	adds r0, r4, #0
	movs r2, #1
	bl FUN_080afedc
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08061340:
	movs r0, #0xaa
	bl UpdateBlinkMotionState
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080613B0
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080613B0
	b _0806139A
_08061358:
	ldr r0, _0806137C @ =0xFFFFDD00
	str r0, [sp]
	ldr r0, _08061380 @ =0xFFFFAA00
	str r0, [sp, #4]
	adds r0, r4, #0
	mov r1, sp
	movs r2, #3
	bl FUN_080afedc
	adds r1, r4, #0
	adds r1, #0xc4
	str r0, [r1]
	movs r0, #0xff
	strb r0, [r4, #0x12]
	movs r0, #1
	rsbs r0, r0, #0
	strb r0, [r4, #0x13]
	b _0806139A
	.align 2, 0
_0806137C: .4byte 0xFFFFDD00
_08061380: .4byte 0xFFFFAA00
_08061384:
	movs r0, #0xaa
	bl UpdateBlinkMotionState
	adds r1, r4, #0
	adds r1, #0xc4
	ldr r0, [r1]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080613B0
	movs r0, #0
	str r0, [r1]
_0806139A:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080613B0
_080613A2:
	movs r0, #0xaa
	bl ClearBlink
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080613B0:
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0
