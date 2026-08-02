	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start fefnir_minigame_080fb354
fefnir_minigame_080fb354: @ 0x080FB354
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	ldr r1, _080FB448 @ =0x00000DCC
	adds r6, r0, r1
	ldr r2, _080FB44C @ =gJoypad
	ldrh r1, [r2]
	strh r1, [r6, #0x18]
	ldrh r1, [r2, #4]
	strh r1, [r6, #0x1a]
	movs r7, #0
	movs r2, #0xdd
	lsls r2, r2, #4
	adds r2, r2, r0
	mov sb, r2
	movs r3, #0
	movs r2, #0xdd
	lsls r2, r2, #4
	adds r1, r0, r2
	movs r2, #3
_080FB380:
	ldr r0, [r1]
	cmp r0, #0
	beq _080FB390
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080FB390
	str r3, [r1]
	movs r7, #1
_080FB390:
	adds r1, #4
	subs r2, #1
	cmp r2, #0
	bge _080FB380
	cmp r7, #0
	beq _080FB3B2
	adds r2, r6, #0
	adds r2, #0x2f
	movs r1, #0
	movs r0, #1
	strb r0, [r2]
	ldrb r0, [r6]
	adds r0, #1
	strb r0, [r6]
	strb r1, [r6, #1]
	strb r1, [r6, #2]
	strb r1, [r6, #3]
_080FB3B2:
	adds r0, r6, #0
	adds r0, #0x2d
	ldrb r1, [r0]
	mov r8, r0
	cmp r1, #0
	bne _080FB472
	ldr r0, _080FB450 @ =RNG_0202f388
	mov ip, r0
	ldr r0, [r0]
	ldr r3, _080FB454 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r3, r1
	ldr r2, _080FB458 @ =0x00269EC3
	adds r1, r1, r2
	lsls r1, r1, #1
	lsrs r4, r1, #1
	lsrs r1, r1, #0x11
	movs r0, #0x1f
	ands r1, r0
	adds r5, r6, #0
	adds r5, #0x2e
	ldrb r0, [r5]
	lsrs r0, r0, #3
	subs r0, #0x30
	subs r1, r1, r0
	mov r0, r8
	strb r1, [r0]
	adds r0, r4, #0
	muls r0, r3, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r2, ip
	str r1, [r2]
	lsrs r2, r0, #0x11
	movs r0, #3
	ands r2, r0
	adds r7, r2, #0
	adds r0, r2, #4
	cmp r2, r0
	bge _080FB468
	mov r4, ip
_080FB406:
	adds r0, r2, #0
	cmp r2, #0
	bge _080FB40E
	adds r0, r2, #3
_080FB40E:
	asrs r0, r0, #2
	lsls r0, r0, #2
	subs r0, r2, r0
	lsls r0, r0, #2
	add r0, sb
	ldr r3, [r0]
	cmp r3, #0
	beq _080FB460
	ldr r1, [r4]
	ldr r0, _080FB454 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080FB458 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	str r0, [sp]
	adds r0, r6, #0
	adds r1, r3, #0
	ldr r2, _080FB45C @ =0x0026E800
	movs r3, #0xe0
	lsls r3, r3, #9
	bl FUN_08071470
	b _080FB468
	.align 2, 0
_080FB448: .4byte 0x00000DCC
_080FB44C: .4byte gJoypad
_080FB450: .4byte RNG_0202f388
_080FB454: .4byte 0x000343FD
_080FB458: .4byte 0x00269EC3
_080FB45C: .4byte 0x0026E800
_080FB460:
	adds r2, #1
	adds r0, r7, #4
	cmp r2, r0
	blt _080FB406
_080FB468:
	ldrb r0, [r5]
	cmp r0, #0xfe
	bhi _080FB472
	adds r0, #1
	strb r0, [r5]
_080FB472:
	mov r2, r8
	ldrb r0, [r2]
	subs r0, #1
	strb r0, [r2]
	movs r0, #1
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
