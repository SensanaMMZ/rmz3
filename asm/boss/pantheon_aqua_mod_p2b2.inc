	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start paquqmRubble
paquqmRubble: @ 0x080520B8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _0805211C
	cmp r5, #1
	bgt _080520CC
	cmp r5, #0
	beq _080520D4
	b _08052236
_080520CC:
	cmp r5, #2
	bne _080520D2
	b _08052204
_080520D2:
	b _08052236
_080520D4:
	movs r0, #0xe3
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080521DC @ =0x083636DC
	bl SetDDP
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r0, [r2]
	ldr r1, _080521E0 @ =0xFFFFFDFF
	ands r0, r1
	ldr r1, _080521E4 @ =0xFFFFFBFF
	ands r0, r1
	movs r1, #0x80
	orrs r0, r1
	adds r1, #0x80
	orrs r0, r1
	str r0, [r2]
	ldr r1, _080521E8 @ =0x00004D0E
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl createStretchedArms
	strb r5, [r4, #0x12]
	strb r5, [r4, #0x13]
	str r5, [r4, #0x68]
	str r5, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805211C:
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080521C8
	ldr r0, [r4, #0x68]
	cmp r0, #0
	bne _0805213C
	ldr r0, _080521EC @ =0x0000010D
	bl PlaySound
	movs r0, #1
	str r0, [r4, #0x68]
_0805213C:
	ldr r0, [r4, #0x5c]
	movs r1, #0x38
	bl __modsi3
	cmp r0, #0
	bne _08052172
	ldr r2, _080521F0 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080521F4 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080521F8 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	ands r0, r1
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	ldr r2, _080521FC @ =0xFFFFB800
	adds r1, r1, r2
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	bl createPAquaModRubble
_08052172:
	ldr r0, [r4, #0x5c]
	adds r0, #1
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #3
	bl AppendQuake
	ldrb r0, [r4, #0x12]
	adds r0, #8
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080521B2
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #6
	bls _080521B2
	ldr r0, _080521EC @ =0x0000010D
	bl StopSound
	ldr r0, [r5]
	movs r1, #0x80
	lsls r1, r1, #3
	orrs r0, r1
	str r0, [r5]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080521B2:
	ldr r1, [r4, #0x64]
	str r1, [r4, #0x54]
	ldr r2, _08052200 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #3
	adds r1, r1, r0
	str r1, [r4, #0x54]
_080521C8:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08052236
	.align 2, 0
_080521DC: .4byte 0x083636DC
_080521E0: .4byte 0xFFFFFDFF
_080521E4: .4byte 0xFFFFFBFF
_080521E8: .4byte 0x00004D0E
_080521EC: .4byte 0x0000010D
_080521F0: .4byte RNG_0202f388
_080521F4: .4byte 0x000343FD
_080521F8: .4byte 0x00269EC3
_080521FC: .4byte 0xFFFFB800
_08052200: .4byte gSineTable
_08052204:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r5, [r0]
	movs r0, #0xc0
	lsls r0, r0, #1
	ands r5, r0
	cmp r5, #0
	bne _08052226
	ldr r1, _0805223C @ =0x00004D01
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	movs r0, #0x46
	strb r0, [r4, #0x12]
_08052226:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08052236:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805223C: .4byte 0x00004D01

	thumb_func_start paqua_mod_08052240
paqua_mod_08052240: @ 0x08052240
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _0805224C
	b _080523AA
_0805224C:
	lsls r0, r0, #2
	ldr r1, _0805225C @ =0x08052260
	adds r0, r0, r1
	ldr r0, [r0]
	adds r5, r4, #0
	adds r5, #0xb8
	mov pc, r0
	.align 2, 0
_0805225C: .4byte 0x08052260
_08052260:
	.byte 0x78, 0x22, 0x05, 0x08, 0x9E, 0x22, 0x05, 0x08, 0xC8, 0x22, 0x05, 0x08, 0x12, 0x23, 0x05, 0x08
	.byte 0x32, 0x23, 0x05, 0x08, 0x8E, 0x23, 0x05, 0x08, 0x20, 0x1C, 0x74, 0x30, 0x10, 0x49, 0xB4, 0xF7
	.byte 0xC9, 0xFF, 0x22, 0x1C, 0xB4, 0x32, 0x10, 0x68, 0x80, 0x21, 0x09, 0x01, 0x08, 0x43, 0x10, 0x60
	.byte 0x0C, 0x49, 0x20, 0x1C, 0xC5, 0xF7, 0x68, 0xF9, 0xA0, 0x7B, 0x01, 0x30, 0xA0, 0x73, 0x20, 0x1C
	.byte 0xB8, 0x30, 0x00, 0x78, 0xB1, 0xF7, 0xE0, 0xFE, 0x20, 0x1C, 0xC5, 0xF7, 0xD7, 0xF9, 0x20, 0x1C
	.byte 0x73, 0x30, 0x00, 0x78, 0x03, 0x28, 0x78, 0xD1, 0xA0, 0x7B, 0x01, 0x30, 0x74, 0xE0, 0x00, 0x00
	.byte 0xD4, 0x38, 0x36, 0x08, 0x0F, 0x4D, 0x00, 0x00, 0xE5, 0x20, 0xB2, 0xF7, 0x69, 0xF9, 0x28, 0x20
	.byte 0xA0, 0x74, 0x20, 0x1C, 0x6E, 0xF0, 0x34, 0xF8, 0x20, 0x1C, 0xB8, 0x30, 0x01, 0x78, 0x05, 0x1C
	.byte 0x00, 0x29, 0x04, 0xD0, 0x28, 0x78, 0xB1, 0xF7, 0xE5, 0xFE, 0x00, 0x20, 0x28, 0x70, 0x20, 0x1C
	.byte 0xC5, 0xF7, 0x80, 0xFB, 0x01, 0x1C, 0x09, 0x06, 0xC9, 0x0C, 0x80, 0x22, 0x92, 0x00, 0x10, 0x1C
	.byte 0x01, 0x43, 0x58, 0x20, 0xB1, 0xF7, 0x12, 0xFE, 0x58, 0x20, 0x28, 0x70, 0xA0, 0x7B, 0x01, 0x30
	.byte 0xA0, 0x73, 0xA0, 0x7C, 0x01, 0x38, 0xA0, 0x74, 0x00, 0x06, 0x00, 0x28, 0x02, 0xD1, 0xA0, 0x7B
	.byte 0x01, 0x30, 0xA0, 0x73, 0x28, 0x78, 0xB1, 0xF7, 0x9F, 0xFE, 0x20, 0x1C, 0xC5, 0xF7, 0x96, 0xF9
	.byte 0x3B, 0xE0, 0x2C, 0x20, 0xB2, 0xF7, 0x34, 0xF9, 0x60, 0x6D, 0xA1, 0x6D, 0x53, 0xF0, 0x3A, 0xFC
	.byte 0x22, 0x1C, 0xB4, 0x32, 0x10, 0x68, 0x1A, 0x49, 0x08, 0x40, 0x10, 0x60, 0x20, 0x1C, 0xB8, 0x30
	.byte 0x01, 0x78, 0x05, 0x1C, 0x00, 0x29, 0x04, 0xD0, 0x28, 0x78, 0xB1, 0xF7, 0xAB, 0xFE, 0x00, 0x20
	.byte 0x28, 0x70, 0x20, 0x1C, 0xC5, 0xF7, 0x46, 0xFB, 0x01, 0x1C, 0x09, 0x06, 0xC9, 0x0C, 0x80, 0x22
	.byte 0x92, 0x00, 0x10, 0x1C, 0x01, 0x43, 0x59, 0x20, 0xB1, 0xF7, 0xD8, 0xFD, 0x59, 0x20, 0x28, 0x70
	.byte 0x0C, 0x49, 0x20, 0x1C, 0xC5, 0xF7, 0xF0, 0xF8, 0xA0, 0x7B, 0x01, 0x30, 0xA0, 0x73, 0x28, 0x78
	.byte 0xB1, 0xF7, 0x6A, 0xFE, 0x20, 0x1C, 0xC5, 0xF7, 0x61, 0xF9, 0x20, 0x1C, 0x73, 0x30, 0x00, 0x78
	.byte 0x03, 0x28, 0x02, 0xD1, 0x00, 0x20, 0x60, 0x73, 0xA0, 0x73
_080523AA:
	pop {r4, r5}
	pop {r0}
	bx r0
_080523B0:
	.byte 0xFF, 0xF7, 0xFF, 0xFF, 0x11, 0x4D, 0x00, 0x00

	thumb_func_start FUN_080523b8
FUN_080523b8: @ 0x080523B8
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	adds r7, r0, #0
	ldrb r4, [r7, #0xe]
	cmp r4, #1
	beq _0805245E
	cmp r4, #1
	ble _080523D0
	b _0805259C
_080523D0:
	cmp r4, #0
	beq _080523D6
	b _0805259C
_080523D6:
	ldr r0, _08052550 @ =0x0000010D
	bl StopSound
	ldr r1, _08052554 @ =0x00004D12
	adds r0, r7, #0
	bl SetMotion
	adds r5, r7, #0
	adds r5, #0xb8
	ldrb r0, [r5]
	cmp r0, #0
	beq _080523F4
	bl RemovePaletteAnimation
	strb r4, [r5]
_080523F4:
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x54
	bl StartPaletteAnimation
	movs r0, #0x54
	strb r0, [r5]
	bl StepPaletteAnimation
	ldr r3, _08052558 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r2
	cmp r0, #0
	beq _08052438
	ldrb r1, [r3, #0x12]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _08052438
	ldr r0, _0805255C @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_08052438:
	movs r0, #0xff
	strb r0, [r7, #0x12]
	movs r1, #0
	movs r0, #2
	strb r0, [r7, #0x13]
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
_0805245E:
	ldrb r0, [r7, #0x13]
	cmp r0, #0
	beq _08052480
	cmp r0, #1
	bne _0805247A
	adds r4, r7, #0
	adds r4, #0xb8
	ldrb r0, [r4]
	cmp r0, #0
	beq _0805247A
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_0805247A:
	ldrb r0, [r7, #0x13]
	subs r0, #1
	strb r0, [r7, #0x13]
_08052480:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0x12]
	movs r1, #7
	ands r0, r1
	cmp r0, #0
	bne _080524DC
	ldr r1, [r7, #0x54]
	ldr r3, _08052560 @ =0xFFFFE000
	mov r8, r3
	add r1, r8
	ldr r0, _08052564 @ =RNG_0202f388
	mov sb, r0
	ldr r0, [r0]
	ldr r6, _08052568 @ =0x000343FD
	muls r0, r6, r0
	ldr r3, _0805256C @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	ldr r5, _08052570 @ =0x00003FFF
	ands r0, r5
	adds r0, r0, r1
	str r0, [sp]
	ldr r2, [r7, #0x58]
	add r2, r8
	adds r0, r4, #0
	muls r0, r6, r0
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, sb
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	adds r0, r0, r2
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
_080524DC:
	ldrb r0, [r7, #0x12]
	adds r0, #2
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	bne _08052522
	ldr r5, _08052564 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08052568 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _0805256C @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #1
	lsrs r1, r1, #0x12
	ldr r0, _08052560 @ =0xFFFFE000
	adds r1, r1, r0
	ldr r0, [r7, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #2
	lsrs r2, r2, #0x13
	movs r1, #0x80
	lsls r1, r1, #5
	adds r2, r2, r1
	ldr r1, [r7, #0x58]
	subs r1, r1, r2
	bl FUN_080c02f4
_08052522:
	ldrb r0, [r7, #0x12]
	movs r1, #0x14
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08052536
	movs r0, #0x31
	bl PlaySound
_08052536:
	movs r0, #0x12
	ldrsb r0, [r7, r0]
	ldrb r2, [r7, #0x12]
	cmp r0, #0
	blt _0805257C
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	beq _08052574
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0805257A
	.align 2, 0
_08052550: .4byte 0x0000010D
_08052554: .4byte 0x00004D12
_08052558: .4byte gStageRun
_0805255C: .4byte 0x0000FFFE
_08052560: .4byte 0xFFFFE000
_08052564: .4byte RNG_0202f388
_08052568: .4byte 0x000343FD
_0805256C: .4byte 0x00269EC3
_08052570: .4byte 0x00003FFF
_08052574:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0805257A:
	strb r0, [r7, #0xa]
_0805257C:
	lsls r0, r2, #0x18
	cmp r0, #0
	bne _0805259C
	ldr r2, _080525AC @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #0xd
	bl TryDropItem
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0805259C:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080525AC: .4byte gStageRun
