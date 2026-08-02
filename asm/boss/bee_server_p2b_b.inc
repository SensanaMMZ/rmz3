	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0804d494
FUN_0804d494: @ 0x0804D494
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #1
	beq _0804D4FE
	cmp r0, #1
	ble _0804D4A6
	b _0804D5D0
_0804D4A6:
	cmp r0, #0
	beq _0804D4AC
	b _0804D5D0
_0804D4AC:
	movs r0, #0x45
	bl RemovePaletteAnimation
	ldr r3, _0804D58C @ =gStageRun
	ldrh r2, [r3, #8]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r2
	cmp r0, #0
	beq _0804D4D4
	ldrb r1, [r3, #0x12]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _0804D4D4
	ldr r0, _0804D590 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0804D4D4:
	ldrb r2, [r7, #0xa]
	movs r0, #1
	movs r1, #0
	orrs r0, r2
	strb r0, [r7, #0xa]
	movs r0, #0xff
	strb r0, [r7, #0x12]
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
	strb r0, [r7, #0xa]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0804D4FE:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0x12]
	movs r1, #7
	ands r0, r1
	cmp r0, #0
	bne _0804D55C
	ldr r1, [r7, #0x54]
	ldr r0, _0804D594 @ =0xFFFFE000
	adds r1, r1, r0
	ldr r6, _0804D598 @ =RNG_0202f388
	ldr r0, [r6]
	ldr r5, _0804D59C @ =0x000343FD
	muls r0, r5, r0
	ldr r2, _0804D5A0 @ =0x00269EC3
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r3, r0, #1
	lsls r0, r0, #1
	lsrs r0, r0, #0x12
	adds r0, r0, r1
	str r0, [sp]
	ldr r4, [r7, #0x58]
	ldr r0, _0804D5A4 @ =0xFFFFD200
	adds r4, r4, r0
	str r4, [sp, #4]
	adds r0, r3, #0
	muls r0, r5, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r6]
	lsrs r0, r0, #0x11
	movs r1, #0xb8
	lsls r1, r1, #7
	bl __umodsi3
	adds r0, r0, r4
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
_0804D55C:
	ldrb r0, [r7, #0x12]
	movs r1, #0x14
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804D570
	movs r0, #0x2a
	bl PlaySound
_0804D570:
	movs r0, #0x12
	ldrsb r0, [r7, r0]
	ldrb r2, [r7, #0x12]
	cmp r0, #0
	blt _0804D5B0
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	beq _0804D5A8
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0804D5AE
	.align 2, 0
_0804D58C: .4byte gStageRun
_0804D590: .4byte 0x0000FFFE
_0804D594: .4byte 0xFFFFE000
_0804D598: .4byte RNG_0202f388
_0804D59C: .4byte 0x000343FD
_0804D5A0: .4byte 0x00269EC3
_0804D5A4: .4byte 0xFFFFD200
_0804D5A8:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0804D5AE:
	strb r0, [r7, #0xa]
_0804D5B0:
	lsls r0, r2, #0x18
	cmp r0, #0
	bne _0804D5D0
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #0xc
	bl TryDropItem
	ldr r2, _0804D5D8 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0804D5D0:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0804D5D8: .4byte gStageRun
