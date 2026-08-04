	.include "asm/macros.inc"

	.syntax unified

	.text


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
