	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080459e8
FUN_080459e8: @ 0x080459E8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r6, r0, #0
	ldr r2, [r6, #0x54]
	str r2, [sp]
	ldr r0, [r6, #0x58]
	ldr r1, _08045A54 @ =0xFFFFC200
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08045A60
	ldr r1, _08045A58 @ =0xFFFFEE00
	adds r0, r2, r1
	str r0, [sp]
	ldr r5, _08045A5C @ =gSineTable
	movs r1, #0xb2
	lsls r1, r1, #1
	adds r0, r5, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [sp, #8]
	movs r1, #0xf2
	lsls r1, r1, #1
	adds r0, r5, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	add r4, sp, #8
	str r0, [r4, #4]
	adds r0, r6, #0
	mov r1, sp
	adds r2, r4, #0
	movs r3, #0x72
	bl FUN_0809f4dc
	movs r1, #0xce
	lsls r1, r1, #1
	adds r0, r5, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [sp, #8]
	movs r1, #0x1c
	ldrsh r0, [r5, r1]
	str r0, [r4, #4]
	adds r0, r6, #0
	mov r1, sp
	adds r2, r4, #0
	movs r3, #0x8e
	bl FUN_0809f4dc
	b _08045AAE
	.align 2, 0
_08045A54: .4byte 0xFFFFC200
_08045A58: .4byte 0xFFFFEE00
_08045A5C: .4byte gSineTable
_08045A60:
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r2, r1
	str r0, [sp]
	ldr r5, _08045AB8 @ =gSineTable
	adds r0, r5, #0
	adds r0, #0x64
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [sp, #8]
	add r4, sp, #8
	adds r0, r5, #0
	adds r0, #0xe4
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [r4, #4]
	adds r0, r6, #0
	mov r1, sp
	adds r2, r4, #0
	movs r3, #0xf2
	bl FUN_0809f4dc
	adds r0, r5, #0
	adds r0, #0x9c
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [sp, #8]
	movs r1, #0x8e
	lsls r1, r1, #1
	adds r0, r5, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [r4, #4]
	adds r0, r6, #0
	mov r1, sp
	adds r2, r4, #0
	movs r3, #0xe
	bl FUN_0809f4dc
_08045AAE:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08045AB8: .4byte gSineTable
