	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080613bc
FUN_080613bc: @ 0x080613BC
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bhi _0806149C
	lsls r0, r0, #2
	ldr r1, _080613D4 @ =_080613D8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080613D4: .4byte _080613D8
_080613D8: @ jump table
	.4byte _080613EC @ case 0
	.4byte _08061424 @ case 1
	.4byte _0806143C @ case 2
	.4byte _08061464 @ case 3
	.4byte _08061488 @ case 4
_080613EC:
	movs r0, #0xa7
	bl ClearBlink
	movs r0, #0xa8
	bl ClearBlink
	movs r0, #0xa9
	bl ClearBlink
	movs r0, #0xaa
	bl ClearBlink
	movs r1, #0xb8
	lsls r1, r1, #2
	movs r0, #0xa8
	bl LoadBlink
	adds r1, r4, #0
	adds r1, #0x54
	adds r0, r4, #0
	movs r2, #0
	bl FUN_080c4f04
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08061424:
	adds r0, r4, #0
	bl FUN_080616fc
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0806149C
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0806149C
	b _08061480
_0806143C:
	ldr r0, [r4, #0x54]
	ldr r1, _0806145C @ =0xFFFFFC00
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08061460 @ =0xFFFFDE00
	adds r0, r0, r1
	str r0, [sp, #4]
	adds r0, r4, #0
	mov r1, sp
	movs r2, #0
	bl FUN_080aff34
	adds r1, r4, #0
	adds r1, #0xc4
	b _0806147E
	.align 2, 0
_0806145C: .4byte 0xFFFFFC00
_08061460: .4byte 0xFFFFDE00
_08061464:
	adds r0, r4, #0
	bl FUN_080616fc
	movs r0, #0xa8
	bl UpdateBlinkMotionState
	adds r1, r4, #0
	adds r1, #0xc4
	ldr r0, [r1]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0806149C
	movs r0, #0
_0806147E:
	str r0, [r1]
_08061480:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0806149C
_08061488:
	adds r0, r4, #0
	bl FUN_080616fc
	movs r0, #0xa8
	bl ClearBlink
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806149C:
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0
