	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08080fec
FUN_08080fec: @ 0x08080FEC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0x14
	adds r5, r0, #0
	ldr r4, [r5, #0x28]
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _0808105C
	cmp r0, #1
	bgt _08081008
	cmp r0, #0
	beq _08081012
	b _080811D4
_08081008:
	cmp r0, #2
	beq _0808109C
	cmp r0, #3
	beq _080810EA
	b _080811D4
_08081012:
	movs r0, #0x40
	strb r0, [r5, #0x12]
	movs r1, #0x9c
	lsls r1, r1, #6
	adds r0, r5, #0
	bl SetMotion
	ldr r0, [r5, #0x54]
	asrs r0, r0, #8
	str r0, [r5, #0x54]
	movs r1, #0xf0
	bl __divsi3
	lsls r1, r0, #4
	subs r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xd0
	lsls r0, r0, #8
	adds r1, r1, r0
	str r1, [r5, #0x54]
	ldr r0, [r5, #0x58]
	asrs r0, r0, #8
	str r0, [r5, #0x58]
	movs r1, #0xa0
	bl __divsi3
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #0xd
	movs r2, #0xd0
	lsls r2, r2, #7
	adds r1, r1, r2
	str r1, [r5, #0x58]
	str r1, [r5, #0x68]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0808105C:
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	ldr r1, [r5, #0x68]
	str r1, [r5, #0x58]
	ldr r2, _08081098 @ =gSineTable
	ldrb r0, [r5, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #2
	adds r1, r1, r0
	str r1, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r1, #2
	ands r0, r1
	cmp r0, #0
	bne _0808108E
	b _080811D4
_0808108E:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080811D4
	.align 2, 0
_08081098: .4byte gSineTable
_0808109C:
	movs r0, #0x29
	bl PlaySound
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	ldr r1, _080811E0 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	movs r3, #0
	bl FUN_080b2b40
	movs r0, #0x28
	str r0, [sp, #8]
	movs r0, #0x30
	str r0, [sp, #0xc]
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _080811E4 @ =0x08368100
	str r0, [sp]
	movs r4, #0x18
	str r4, [sp, #4]
	adds r0, r5, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b857c
	ldr r1, _080811E8 @ =0x00002709
	adds r0, r5, #0
	bl SetMotion
	strb r4, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080810EA:
	ldr r0, [r5, #0x54]
	adds r0, #8
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	adds r0, #8
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	movs r1, #7
	ands r0, r1
	cmp r0, #0
	bne _08081166
	ldr r3, _080811EC @ =RNG_0202f388
	ldr r7, _080811F0 @ =0x000343FD
	ldr r6, _080811F4 @ =0x00269EC3
	add r2, sp, #8
	mov r8, r2
	movs r4, #2
_08081112:
	ldr r1, [r5, #0x54]
	ldr r0, _080811F8 @ =0xFFFFF800
	adds r1, r1, r0
	ldr r0, [r3]
	muls r0, r7, r0
	adds r0, r0, r6
	lsls r0, r0, #1
	lsrs r2, r0, #1
	lsls r0, r0, #3
	lsrs r0, r0, #0x14
	adds r1, r1, r0
	str r1, [sp, #8]
	ldr r1, [r5, #0x58]
	ldr r0, _080811FC @ =0xFFFFE000
	adds r1, r1, r0
	adds r0, r2, #0
	muls r0, r7, r0
	adds r0, r0, r6
	lsls r0, r0, #1
	lsrs r2, r0, #1
	lsls r0, r0, #2
	lsrs r0, r0, #0x13
	adds r1, r1, r0
	mov r0, r8
	str r1, [r0, #4]
	adds r1, r2, #0
	muls r1, r7, r1
	adds r1, r1, r6
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r3]
	lsrs r1, r1, #0x11
	movs r0, #1
	ands r1, r0
	add r0, sp, #8
	str r3, [sp, #0x10]
	bl FUN_080ba9f4
	subs r4, #1
	ldr r3, [sp, #0x10]
	cmp r4, #0
	bge _08081112
_08081166:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	bne _080811D4
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	ldr r4, _080811F8 @ =0xFFFFF800
	adds r0, r0, r4
	str r0, [sp, #0xc]
	ldr r2, _08081200 @ =0x08368102
	adds r0, r5, #0
	add r1, sp, #8
	movs r3, #4
	bl FUN_080b81a0
	ldr r0, [sp, #0xc]
	adds r0, r0, r4
	str r0, [sp, #0xc]
	movs r0, #1
	add r1, sp, #8
	bl CreateSmoke
	movs r0, #0x31
	bl PlaySound
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r6, [r0]
	adds r0, #4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08081204 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_080811D4:
	add sp, #0x14
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080811E0: .4byte 0xFFFFF000
_080811E4: .4byte 0x08368100
_080811E8: .4byte 0x00002709
_080811EC: .4byte RNG_0202f388
_080811F0: .4byte 0x000343FD
_080811F4: .4byte 0x00269EC3
_080811F8: .4byte 0xFFFFF800
_080811FC: .4byte 0xFFFFE000
_08081200: .4byte 0x08368102
_08081204: .4byte gEnemyFnTable
