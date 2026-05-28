	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Elf5_Init
Elf5_Init: @ 0x080E34BC
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #8
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r0, [r0]
	mov r8, r0
	ldr r1, _080E356C @ =gZeroRanges
	ldr r0, _080E3570 @ =0x00000147
	add r0, r8
	ldrb r0, [r0]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r1, [r0]
	ldr r2, [r0, #4]
	str r1, [sp]
	str r2, [sp, #4]
	ldr r0, _080E3574 @ =gPause
	movs r5, #1
	strb r5, [r0]
	ldr r1, _080E3578 @ =gElfFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r0, [r4, #0xa]
	movs r6, #0
	orrs r5, r0
	movs r0, #2
	orrs r5, r0
	strb r5, [r4, #0xa]
	movs r1, #0x90
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	subs r2, #1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldr r2, [sp]
	lsls r1, r2, #0x10
	asrs r1, r1, #0x10
	mov r2, r8
	ldr r0, [r2, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [sp]
	asrs r1, r0, #0x10
	ldr r0, [r2, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl Elf5_Update
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080E356C: .4byte gZeroRanges
_080E3570: .4byte 0x00000147
_080E3574: .4byte gPause
_080E3578: .4byte gElfFnTable
