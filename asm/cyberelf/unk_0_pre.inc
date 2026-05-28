	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Elf0_Init
Elf0_Init: @ 0x080E1D30
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	adds r7, r0, #0
	adds r0, #0xbc
	ldr r6, [r0]
	ldr r1, _080E1DF0 @ =gZeroRanges
	ldr r2, _080E1DF4 @ =0x00000147
	adds r0, r6, r2
	ldrb r0, [r0]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r1, [r0]
	ldr r2, [r0, #4]
	str r1, [sp]
	str r2, [sp, #4]
	ldr r0, _080E1DF8 @ =gPause
	movs r4, #1
	strb r4, [r0]
	adds r0, r7, #0
	bl InitNonAffineMotion
	adds r0, r7, #0
	bl ResetDynamicMotion
	ldrb r0, [r7, #0xa]
	movs r2, #0
	mov r8, r2
	orrs r4, r0
	movs r0, #2
	orrs r4, r0
	strb r4, [r7, #0xa]
	movs r0, #0
	bl GetElfMotion
	adds r1, r0, #0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x4c
	mov r1, r8
	strb r1, [r0]
	adds r2, r7, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r7, #0xa]
	subs r2, #1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldr r2, [sp]
	lsls r1, r2, #0x10
	asrs r1, r1, #0x10
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	ldr r0, [sp]
	asrs r5, r0, #0x10
	ldr r0, [r6, #0x58]
	adds r0, r0, r5
	str r0, [r7, #0x58]
	adds r1, r7, #0
	adds r1, #0xb4
	movs r0, #0xa0
	lsls r0, r0, #4
	str r0, [r1]
	adds r4, r7, #0
	adds r4, #0xb8
	movs r0, #0xa0
	lsls r0, r0, #7
	str r0, [r4]
	ldrb r0, [r7, #0x10]
	cmp r0, #0
	bne _080E1DFC
	adds r0, r6, #0
	bl getMaxHP1x
	lsls r0, r0, #0x18
	lsrs r0, r0, #0xf
	b _080E1E06
	.align 2, 0
_080E1DF0: .4byte gZeroRanges
_080E1DF4: .4byte 0x00000147
_080E1DF8: .4byte gPause
_080E1DFC:
	adds r0, r6, #0
	bl getMaxHP1x
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x10
_080E1E06:
	ldr r1, [r4]
	subs r1, r1, r0
	str r1, [r4]
	ldr r0, [r7, #0x54]
	movs r1, #0xf0
	lsls r1, r1, #7
	adds r0, r0, r1
	ldr r2, _080E1E58 @ =gStageRun+288
	ldr r1, [r2]
	subs r0, r0, r1
	str r0, [r7, #0x64]
	ldr r0, [r7, #0x58]
	movs r1, #0xa0
	lsls r1, r1, #7
	adds r0, r0, r1
	ldr r1, [r2, #4]
	subs r0, r0, r1
	str r0, [r7, #0x68]
	adds r1, r7, #0
	adds r1, #0xc1
	movs r0, #0x20
	strb r0, [r1]
	ldr r1, _080E1E5C @ =gElfFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl Elf0_Update
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E1E58: .4byte gStageRun+288
_080E1E5C: .4byte gElfFnTable

	thumb_func_start Elf0_Update
Elf0_Update: @ 0x080E1E60
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldr r1, _080E1EB8 @ =gElf0Updates
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xc]
	cmp r0, #1
	bne _080E1EB0
	ldr r0, [r4, #0x64]
	ldr r1, _080E1EBC @ =0xFFFF8800
	adds r0, r0, r1
	ldr r2, _080E1EC0 @ =gStageRun+288
	ldr r1, [r2]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x68]
	ldr r0, _080E1EC4 @ =0xFFFFB000
	adds r1, r1, r0
	ldr r0, [r2, #4]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xc0
	ldrb r0, [r0]
	ldr r2, _080E1EC8 @ =gSineTable
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #2
	adds r1, r1, r0
	str r1, [r4, #0x58]
_080E1EB0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080E1EB8: .4byte gElf0Updates
_080E1EBC: .4byte 0xFFFF8800
_080E1EC0: .4byte gStageRun+288
_080E1EC4: .4byte 0xFFFFB000
_080E1EC8: .4byte gSineTable
