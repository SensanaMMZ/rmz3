	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808e358
FUN_0808e358: @ 0x0808E358
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0808E372
	cmp r0, #1
	beq _0808E45E
	b _0808E4BC
_0808E372:
	adds r0, r5, #0
	adds r0, #0xb9
	ldrb r6, [r0]
	adds r7, r5, #0
	adds r7, #0x8c
	movs r0, #0x90
	adds r0, r0, r5
	mov r8, r0
	movs r2, #0x94
	adds r2, r2, r5
	mov sb, r2
	movs r0, #0x54
	adds r0, r0, r5
	mov sl, r0
	cmp r6, #5
	bgt _0808E3AC
_0808E392:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	lsls r2, r6, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r5, #0xa]
	lsrs r3, r3, #4
	movs r4, #1
	ands r3, r4
	bl CreateGhost65
	adds r6, #1
	cmp r6, #5
	ble _0808E392
_0808E3AC:
	movs r4, #0
	ldr r0, _0808E434 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0808E3BE
	movs r4, #1
_0808E3BE:
	lsls r0, r4, #8
	subs r0, r1, r0
	str r0, [r5, #0x54]
	ldr r1, _0808E438 @ =0x0000740F
	adds r0, r5, #0
	bl SetMotion
	movs r6, #0
	str r6, [r7]
	mov r2, r8
	str r6, [r2]
	mov r0, sb
	strb r6, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r4, #0
	bl FUN_080b2b40
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl PushoutToUp1
	mvns r0, r0
	lsrs r0, r0, #0x1f
	strb r0, [r5, #0x13]
	movs r2, #0x60
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #6
	subs r1, r2, r1
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	cmp r0, #0
	beq _0808E440
	ldr r0, _0808E43C @ =0x08369328
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sl
	add r2, sp, #8
	movs r3, #0x20
	bl FUN_080b857c
	str r6, [r5, #0x60]
	b _0808E454
	.align 2, 0
_0808E434: .4byte pZero2
_0808E438: .4byte 0x0000740F
_0808E43C: .4byte 0x08369328
_0808E440:
	ldr r0, _0808E4AC @ =0x08369328
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sl
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b83d4
_0808E454:
	movs r0, #0x18
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0808E45E:
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _0808E47C
	ldr r0, [r5, #0x60]
	adds r0, #0x15
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808E474
	str r1, [r5, #0x60]
_0808E474:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
_0808E47C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r1, r0, #1
	strb r1, [r5, #0x12]
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _0808E4B0
	lsls r0, r1, #0x18
	cmp r0, #0
	beq _0808E4A2
	ldr r1, [r5, #0x54]
	adds r0, r1, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0808E4BC
_0808E4A2:
	adds r0, r5, #0
	bl maybeKillDeathlock
	b _0808E4BC
	.align 2, 0
_0808E4AC: .4byte 0x08369328
_0808E4B0:
	lsls r0, r1, #0x18
	cmp r0, #0
	bne _0808E4BC
	adds r0, r5, #0
	bl maybeKillDeathlock
_0808E4BC:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
