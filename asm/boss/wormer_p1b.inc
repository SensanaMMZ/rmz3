	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Wormer_Die
Wormer_Die: @ 0x08042724
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #1
	beq _08042796
	cmp r0, #1
	ble _0804273C
	b _0804287E
_0804273C:
	cmp r0, #0
	beq _08042742
	b _0804287E
_08042742:
	ldr r3, _08042828 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r2
	cmp r0, #0
	beq _08042764
	ldrb r1, [r3, #0x12]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _08042764
	ldr r0, _0804282C @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_08042764:
	ldrb r1, [r7, #0xa]
	movs r0, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _08042830 @ =0x00002B08
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0xff
	strb r0, [r7, #0x12]
	adds r0, r7, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_08042796:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0x12]
	movs r1, #7
	ands r0, r1
	cmp r0, #0
	bne _080427FA
	ldr r4, [r7, #0x54]
	ldr r0, _08042834 @ =0xFFFFEC00
	adds r4, r4, r0
	str r4, [sp]
	ldr r5, _08042838 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r1, _0804283C @ =0x000343FD
	mov sb, r1
	mov r1, sb
	muls r1, r0, r1
	adds r0, r1, #0
	ldr r1, _08042840 @ =0x00269EC3
	mov r8, r1
	add r0, r8
	lsls r0, r0, #1
	lsrs r6, r0, #1
	str r6, [r5]
	lsrs r0, r0, #0x11
	movs r1, #0xc0
	lsls r1, r1, #6
	bl __umodsi3
	adds r0, r0, r4
	str r0, [sp]
	ldr r2, [r7, #0x58]
	mov r0, sb
	muls r0, r6, r0
	add r0, r8
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r5]
	lsls r0, r0, #1
	lsrs r0, r0, #0x12
	subs r2, r2, r0
	str r2, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
_080427FA:
	ldrb r0, [r7, #0x12]
	movs r1, #0xc
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804280E
	movs r0, #0x2a
	bl PlaySound
_0804280E:
	movs r0, #0x12
	ldrsb r0, [r7, r0]
	ldrb r2, [r7, #0x12]
	cmp r0, #0
	blt _0804284C
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	beq _08042844
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0804284A
	.align 2, 0
_08042828: .4byte gStageRun
_0804282C: .4byte 0x0000FFFE
_08042830: .4byte 0x00002B08
_08042834: .4byte 0xFFFFEC00
_08042838: .4byte RNG_0202f388
_0804283C: .4byte 0x000343FD
_08042840: .4byte 0x00269EC3
_08042844:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0804284A:
	strb r0, [r7, #0xa]
_0804284C:
	lsls r0, r2, #0x18
	cmp r0, #0
	bne _0804287E
	ldrb r0, [r7, #0x10]
	cmp r0, #0
	bne _08042864
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #0xa
	bl TryDropItem
	b _0804286E
_08042864:
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #0xb
	bl TryDropItem
_0804286E:
	ldr r2, _0804288C @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_0804287E:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0804288C: .4byte gStageRun
