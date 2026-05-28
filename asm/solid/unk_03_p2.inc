	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080cb980
FUN_080cb980: @ 0x080CB980
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	str r0, [sp]
	ldr r7, [r0, #0x2c]
	ldrb r0, [r7, #0xd]
	cmp r0, #0
	beq _080CB998
	b _080CBAB6
_080CB998:
	ldr r1, [sp]
	ldr r0, [r1, #0xc]
	ldr r2, [r0, #4]
	ldr r3, [r0, #8]
	adds r4, r2, #0
	adds r4, #0x10
	ldr r0, [r0, #0x2c]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080CB9BA
	movs r0, #0x10
	ldrsh r1, [r2, r0]
	ldr r0, [r3]
	adds r5, r0, r1
	b _080CB9C2
_080CB9BA:
	movs r0, #0x10
	ldrsh r1, [r2, r0]
	ldr r0, [r3]
	subs r5, r0, r1
_080CB9C2:
	movs r0, #2
	ldrsh r1, [r4, r0]
	ldr r0, [r3, #4]
	adds r6, r0, r1
	ldrh r0, [r4, #4]
	lsrs r0, r0, #1
	str r0, [sp, #4]
	ldrh r0, [r4, #6]
	lsrs r0, r0, #1
	mov sl, r0
	ldrb r0, [r7, #0x10]
	cmp r0, #0
	bne _080CBA30
	adds r0, r5, #0
	adds r1, r6, #0
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	ldr r1, [sp, #4]
	adds r4, r5, r1
	adds r0, r6, #0
	add r0, sl
	mov sb, r0
	adds r0, r4, #0
	mov r1, sb
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	mov r1, sl
	subs r1, r6, r1
	mov r8, r1
	adds r0, r4, #0
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	ldr r0, [sp, #4]
	subs r4, r5, r0
	adds r0, r4, #0
	mov r1, sb
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	adds r0, r4, #0
	mov r1, r8
	bl FUN_0800e284
	b _080CBA82
_080CBA30:
	adds r0, r5, #0
	adds r1, r6, #0
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	ldr r1, [sp, #4]
	adds r4, r5, r1
	adds r0, r6, #0
	add r0, sl
	mov sb, r0
	adds r0, r4, #0
	mov r1, sb
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	mov r1, sl
	subs r1, r6, r1
	mov r8, r1
	adds r0, r4, #0
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	ldr r0, [sp, #4]
	subs r4, r5, r0
	adds r0, r4, #0
	mov r1, sb
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CBA88
	adds r0, r4, #0
	mov r1, r8
	bl FUN_08010cd0
_080CBA82:
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CBAA8
_080CBA88:
	str r5, [r7, #0x64]
	str r6, [r7, #0x68]
	ldr r1, [sp, #4]
	str r1, [r7, #0x5c]
	mov r0, sl
	str r0, [r7, #0x60]
	movs r0, #0x3d
	bl isSoundPlaying
	cmp r0, #0
	bne _080CBAA4
	movs r0, #0x3d
	bl PlaySound
_080CBAA4:
	movs r0, #1
	strb r0, [r7, #0xd]
_080CBAA8:
	ldr r1, [sp]
	ldr r0, [r1, #0x18]
	movs r1, #2
	rsbs r1, r1, #0
	ands r0, r1
	ldr r1, [sp]
	str r0, [r1, #0x18]
_080CBAB6:
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
