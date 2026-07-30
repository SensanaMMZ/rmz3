	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start NurseB_Init
NurseB_Init: @ 0x080E25EC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	adds r0, #0xb4
	ldr r7, [r0]
	ldr r1, _080E2684 @ =gZeroRanges
	ldr r2, _080E2688 @ =0x00000147
	adds r0, r7, r2
	ldrb r0, [r0]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r4, [r0]
	ldr r5, [r0, #4]
	adds r0, r6, #0
	bl InitNonAffineMotion
	adds r0, r6, #0
	bl ResetDynamicMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r2, #0
	mov r8, r2
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	movs r0, #0
	bl GetElfMotion
	adds r1, r0, #0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x4c
	mov r1, r8
	strb r1, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r0, [r7, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	asrs r4, r4, #0x10
	ldr r0, [r7, #0x58]
	adds r0, r0, r4
	str r0, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xbc
	mov r2, r8
	str r2, [r0]
	str r2, [r0, #4]
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080E268C
	adds r0, r6, #0
	adds r0, #0xb8
	strb r2, [r0]
	b _080E2694
	.align 2, 0
_080E2684: .4byte gZeroRanges
_080E2688: .4byte 0x00000147
_080E268C:
	adds r1, r6, #0
	adds r1, #0xb8
	movs r0, #8
	strb r0, [r1]
_080E2694:
	adds r1, r6, #0
	adds r1, #0xb9
	movs r0, #0x20
	strb r0, [r1]
	adds r0, r6, #0
	adds r1, r7, #0
	bl CreateElf3
	ldr r1, _080E26C8 @ =gElfFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl NurseB_Update
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E26C8: .4byte gElfFnTable

