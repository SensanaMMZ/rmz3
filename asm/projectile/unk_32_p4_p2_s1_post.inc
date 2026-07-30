	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ab3ac
FUN_080ab3ac: @ 0x080AB3AC
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	adds r7, r0, #0
	ldr r0, [r7, #0x28]
	str r0, [sp, #4]
	ldrb r0, [r7, #0x11]
	cmp r0, #0
	beq _080AB3C6
	b _080AB4F2
_080AB3C6:
	movs r1, #0x54
	adds r1, r1, r7
	mov sl, r1
	ldr r4, _080AB53C @ =RNG_0202f388
	ldr r0, [r4]
	ldr r6, _080AB540 @ =0x000343FD
	muls r0, r6, r0
	ldr r5, _080AB544 @ =0x00269EC3
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	ldr r1, _080AB548 @ =0x000003FF
	ands r0, r1
	movs r1, #0x80
	lsls r1, r1, #1
	mov r8, r1
	add r0, r8
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #0
	movs r3, #0
	bl CreateVFX57
	ldr r0, [r4]
	adds r3, r0, #0
	muls r3, r6, r3
	adds r3, r3, r5
	lsls r3, r3, #1
	lsrs r0, r3, #1
	lsrs r3, r3, #0x11
	movs r1, #0x7f
	mov sb, r1
	mov r1, sb
	ands r3, r1
	adds r3, #0x80
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	ldr r1, _080AB548 @ =0x000003FF
	ands r0, r1
	add r0, r8
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #2
	bl CreateVFX57
	ldr r0, [r4]
	adds r3, r0, #0
	muls r3, r6, r3
	adds r3, r3, r5
	lsls r3, r3, #1
	lsrs r0, r3, #1
	lsrs r3, r3, #0x11
	movs r1, #0xff
	ands r3, r1
	mov r1, r8
	orrs r3, r1
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	ldr r1, _080AB548 @ =0x000003FF
	ands r0, r1
	add r0, r8
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #3
	bl CreateVFX57
	ldr r0, [r4]
	adds r3, r0, #0
	muls r3, r6, r3
	adds r3, r3, r5
	lsls r3, r3, #1
	lsrs r0, r3, #1
	lsrs r3, r3, #0x11
	mov r1, sb
	ands r3, r1
	adds r3, #0x80
	rsbs r3, r3, #0
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	ldr r1, _080AB548 @ =0x000003FF
	ands r0, r1
	add r0, r8
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #3
	bl CreateVFX57
	ldr r0, [r4]
	adds r3, r0, #0
	muls r3, r6, r3
	adds r3, r3, r5
	lsls r3, r3, #1
	lsrs r0, r3, #1
	lsrs r3, r3, #0x11
	movs r1, #0xff
	ands r3, r1
	add r3, r8
	rsbs r3, r3, #0
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	ldr r1, _080AB548 @ =0x000003FF
	ands r0, r1
	add r0, r8
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #1
	bl CreateVFX57
_080AB4F2:
	ldr r2, [sp, #4]
	adds r2, #0xc6
	ldrb r0, [r2]
	subs r0, #1
	movs r1, #0
	strb r0, [r2]
	adds r0, r7, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _080AB54C @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r7, #0x14]
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AB53C: .4byte RNG_0202f388
_080AB540: .4byte 0x000343FD
_080AB544: .4byte 0x00269EC3
_080AB548: .4byte 0x000003FF
_080AB54C: .4byte gProjectileFnTable
