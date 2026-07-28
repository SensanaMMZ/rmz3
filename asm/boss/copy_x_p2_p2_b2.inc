	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyx_08057590
copyx_08057590: @ 0x08057590
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08057628
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080575C0
	movs r4, #0
	strb r4, [r5, #0xe]
	movs r1, #0xa0
	lsls r1, r1, #2
	movs r0, #0x63
	bl StartPaletteAnimation
	movs r0, #0x39
	bl PlaySound
	movs r0, #0xff
	strb r0, [r5, #0x12]
	strb r4, [r5, #0x13]
_080575C0:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	movs r0, #0x63
	bl StepPaletteAnimation
	ldrb r0, [r5, #0x12]
	movs r1, #7
	ands r1, r0
	cmp r1, #3
	bne _080575E8
	ldrb r2, [r5, #0x13]
	adds r0, r5, #0
	movs r1, #2
	bl CreateVFX56
	ldrb r0, [r5, #0x13]
	adds r0, #0xc
	strb r0, [r5, #0x13]
	b _0805760E
_080575E8:
	cmp r1, #7
	bne _0805760E
	ldr r3, _08057630 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _08057634 @ =0x000343FD
	adds r2, r1, #0
	muls r2, r0, r2
	ldr r0, _08057638 @ =0x00269EC3
	adds r2, r2, r0
	lsls r2, r2, #1
	lsrs r0, r2, #1
	str r0, [r3]
	lsrs r2, r2, #0x11
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	adds r0, r5, #0
	movs r1, #2
	bl CreateVFX56
_0805760E:
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r4, #4
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _08057628
	movs r0, #0x63
	bl RemovePaletteAnimation
	movs r0, #0
	strb r4, [r5, #0xd]
	strb r0, [r5, #0xe]
_08057628:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08057630: .4byte RNG_0202f388
_08057634: .4byte 0x000343FD
_08057638: .4byte 0x00269EC3

	thumb_func_start copyx_0805763c
copyx_0805763c: @ 0x0805763C
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _080576B4
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _080576EC @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	movs r1, #1
	movs r2, #0
	bl CreateVFX39
	adds r2, r4, #0
	adds r2, #0xe0
	str r0, [r2]
	cmp r0, #0
	beq _0805773C
	adds r0, #0x74
	movs r1, #0x1f
	strb r1, [r0]
	ldr r0, [r2]
	adds r0, #0x75
	strb r1, [r0]
	ldr r0, [r2]
	adds r0, #0x76
	strb r1, [r0]
	ldr r0, [r2]
	str r5, [r0, #0x78]
	ldr r0, [r2]
	adds r0, #0x7c
	movs r1, #0x21
	strb r1, [r0]
	ldr r0, [r2]
	adds r0, #0x7d
	movs r1, #0x1e
	strb r1, [r0]
	movs r1, #0xa0
	lsls r1, r1, #2
	movs r0, #0x64
	bl StartPaletteAnimation
	ldr r2, _080576F0 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	movs r0, #0xff
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	movs r0, #0x39
	bl StopSound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080576B4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	bhi _0805773C
	movs r0, #0x64
	bl StepPaletteAnimation
	ldrb r1, [r4, #0x13]
	adds r0, r1, #4
	cmp r0, #0xff
	ble _080576D0
	movs r0, #0xff
_080576D0:
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x12]
	movs r3, #1
	ands r3, r0
	cmp r3, #0
	beq _080576F4
	adds r2, r4, #0
	adds r2, #0xe0
	ldr r1, [r2]
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #8
	str r0, [r1, #0x78]
	adds r5, r2, #0
	b _0805771A
	.align 2, 0
_080576EC: .4byte 0xFFFFF000
_080576F0: .4byte gStageRun
_080576F4:
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #8
	ldr r1, _0805770C @ =0xFFFFF100
	adds r2, r0, r1
	cmp r2, #0
	ble _08057710
	adds r1, r4, #0
	adds r1, #0xe0
	ldr r0, [r1]
	str r2, [r0, #0x78]
	b _08057718
	.align 2, 0
_0805770C: .4byte 0xFFFFF100
_08057710:
	adds r1, r4, #0
	adds r1, #0xe0
	ldr r0, [r1]
	str r3, [r0, #0x78]
_08057718:
	adds r5, r1, #0
_0805771A:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805773C
	movs r0, #0x64
	bl RemovePaletteAnimation
	ldr r0, [r5]
	adds r0, #0x77
	movs r1, #1
	strb r1, [r0]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805773C:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start copyx_08057744
copyx_08057744: @ 0x08057744
	push {r4, lr}
	adds r2, r0, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r3, #0x80
	lsls r3, r3, #5
	adds r0, r1, r3
	ldr r3, [r2, #0x54]
	cmp r3, r0
	blt _08057766
	movs r4, #0xa0
	lsls r4, r4, #9
	adds r0, r1, r4
	adds r1, r2, #0
	adds r1, #0xbc
	cmp r3, r0
	ble _0805776E
_08057766:
	adds r1, r2, #0
	adds r1, #0xbc
	ldr r0, [r1]
	str r0, [r2, #0x54]
_0805776E:
	ldr r0, [r2, #0x54]
	str r0, [r1]
	adds r0, r2, #0
	adds r0, #0xb8
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #6
	adds r0, r0, r1
	ldr r1, [r2, #0x58]
	adds r3, r2, #0
	adds r3, #0xc0
	cmp r1, r0
	bge _0805778C
	ldr r0, [r3]
	str r0, [r2, #0x58]
_0805778C:
	ldr r0, [r2, #0x58]
	str r0, [r3]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
