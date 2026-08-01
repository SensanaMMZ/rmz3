	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start locomoIF_080550ec
locomoIF_080550ec: @ 0x080550EC
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #4
	bls _08055102
	b _0805531C
_08055102:
	lsls r0, r0, #2
	ldr r1, _0805510C @ =_08055110
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0805510C: .4byte _08055110
_08055110: @ jump table
	.4byte _08055124 @ case 0
	.4byte _080551D2 @ case 1
	.4byte _080551FC @ case 2
	.4byte _08055206 @ case 3
	.4byte _08055314 @ case 4
_08055124:
	movs r0, #0x2a
	bl PlaySound
	ldr r1, _080551EC @ =0x00005408
	adds r0, r7, #0
	bl SetMotion
	adds r4, r7, #0
	adds r4, #0xbe
	ldrb r0, [r4]
	cmp r0, #0
	beq _08055144
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_08055144:
	adds r0, r7, #0
	adds r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _08055156
	adds r1, r0, #0
	adds r1, #0xc2
	movs r0, #1
	strb r0, [r1]
_08055156:
	adds r0, r7, #0
	adds r0, #0xc4
	ldr r0, [r0]
	cmp r0, #0
	beq _08055168
	adds r1, r0, #0
	adds r1, #0xc2
	movs r0, #1
	strb r0, [r1]
_08055168:
	adds r0, r7, #0
	adds r0, #0xc8
	ldr r0, [r0]
	cmp r0, #0
	beq _0805517A
	adds r1, r0, #0
	adds r1, #0xc2
	movs r0, #1
	strb r0, [r1]
_0805517A:
	ldr r3, _080551F0 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r2
	cmp r0, #0
	beq _0805519C
	ldrb r1, [r3, #0x12]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _0805519C
	ldr r0, _080551F4 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0805519C:
	adds r0, r7, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	movs r0, #0x1e
	strb r0, [r7, #0x12]
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	ldr r2, _080551F8 @ =0x08363B4C
	adds r0, r7, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b7f70
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080551D2:
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080551E4
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080551E4:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	b _0805531C
	.align 2, 0
_080551EC: .4byte 0x00005408
_080551F0: .4byte gStageRun
_080551F4: .4byte 0x0000FFFE
_080551F8: .4byte 0x08363B4C
_080551FC:
	movs r0, #0xc8
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_08055206:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0x12]
	movs r1, #7
	ands r0, r1
	cmp r0, #0
	bne _080552C0
	ldr r1, [r7, #0x54]
	ldr r5, _080552F8 @ =0xFFFFE000
	adds r1, r1, r5
	ldr r2, _080552FC @ =RNG_0202f388
	ldr r0, [r2]
	ldr r4, _08055300 @ =0x000343FD
	muls r0, r4, r0
	ldr r2, _08055304 @ =0x00269EC3
	mov r8, r2
	add r0, r8
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	ldr r3, _08055308 @ =0x00003FFF
	ands r0, r3
	adds r0, r0, r1
	str r0, [sp, #8]
	ldr r2, [r7, #0x58]
	add r0, sp, #8
	mov sb, r0
	adds r2, r2, r5
	ldr r1, _08055300 @ =0x000343FD
	adds r0, r4, #0
	muls r0, r1, r0
	add r0, r8
	lsls r0, r0, #1
	lsrs r1, r0, #1
	ldr r4, _080552FC @ =RNG_0202f388
	str r1, [r4]
	lsrs r0, r0, #0x11
	ands r0, r3
	adds r0, r0, r2
	mov r1, sb
	str r0, [r1, #4]
	movs r0, #1
	bl CreateSmoke
	ldr r4, [r7, #0x54]
	ldr r2, _0805530C @ =0xFFFFE800
	mov sl, r2
	add r4, sl
	str r4, [sp, #8]
	ldr r1, _080552FC @ =RNG_0202f388
	ldr r0, [r1]
	ldr r2, _08055300 @ =0x000343FD
	muls r0, r2, r0
	add r0, r8
	lsls r0, r0, #1
	lsrs r5, r0, #1
	str r5, [r1]
	lsrs r0, r0, #0x11
	movs r6, #0xc0
	lsls r6, r6, #6
	adds r1, r6, #0
	bl __umodsi3
	adds r4, r4, r0
	str r4, [sp, #8]
	ldr r4, [r7, #0x58]
	add r4, sl
	mov r0, sb
	str r4, [r0, #4]
	ldr r1, _08055300 @ =0x000343FD
	adds r0, r5, #0
	muls r0, r1, r0
	add r0, r8
	lsls r0, r0, #1
	lsrs r1, r0, #1
	ldr r2, _080552FC @ =RNG_0202f388
	str r1, [r2]
	lsrs r0, r0, #0x11
	adds r1, r6, #0
	bl __umodsi3
	adds r4, r4, r0
	mov r0, sb
	str r4, [r0, #4]
	ldr r1, [sp, #8]
	adds r0, r7, #0
	adds r2, r4, #0
	bl CreateVFX51
_080552C0:
	ldrb r0, [r7, #0x12]
	movs r1, #0x14
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080552D4
	movs r0, #0x2a
	bl PlaySound
_080552D4:
	ldrb r0, [r7, #0x12]
	cmp r0, #0
	bne _0805531C
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #0xe
	bl TryDropItem
	ldr r2, _08055310 @ =gStageRun
	ldrb r0, [r2, #0x12]
	movs r1, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
	b _0805531C
	.align 2, 0
_080552F8: .4byte 0xFFFFE000
_080552FC: .4byte RNG_0202f388
_08055300: .4byte 0x000343FD
_08055304: .4byte 0x00269EC3
_08055308: .4byte 0x00003FFF
_0805530C: .4byte 0xFFFFE800
_08055310: .4byte gStageRun
_08055314:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
_0805531C:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

