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

	thumb_func_start FUN_08081208
FUN_08081208: @ 0x08081208
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #9
	bls _08081216
	b _08081428
_08081216:
	lsls r0, r0, #2
	ldr r1, _08081220 @ =_08081224
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08081220: .4byte _08081224
_08081224: @ jump table
	.4byte _0808124C @ case 0
	.4byte _08081296 @ case 1
	.4byte _080812D4 @ case 2
	.4byte _080812EE @ case 3
	.4byte _0808132C @ case 4
	.4byte _08081342 @ case 5
	.4byte _08081394 @ case 6
	.4byte _0808139E @ case 7
	.4byte _080813B8 @ case 8
	.4byte _080813C4 @ case 9
_0808124C:
	movs r0, #0x20
	strb r0, [r4, #0x12]
	movs r1, #0xa2
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x54]
	asrs r0, r0, #8
	str r0, [r4, #0x54]
	movs r1, #0xf0
	bl __divsi3
	lsls r1, r0, #4
	subs r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xb6
	lsls r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x54]
	ldr r0, [r4, #0x58]
	asrs r0, r0, #8
	str r0, [r4, #0x58]
	movs r1, #0xa0
	bl __divsi3
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #0xd
	movs r2, #0xe0
	lsls r2, r2, #6
	adds r1, r1, r2
	str r1, [r4, #0x58]
	str r1, [r4, #0x68]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081296:
	ldrb r0, [r4, #0x12]
	adds r0, #2
	strb r0, [r4, #0x12]
	ldr r1, [r4, #0x68]
	str r1, [r4, #0x58]
	ldr r2, _080812D0 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #2
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	bne _080812C6
	b _08081428
_080812C6:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08081428
	.align 2, 0
_080812D0: .4byte gSineTable
_080812D4:
	ldr r0, [r4, #0x54]
	ldr r1, _08081324 @ =0xFFFFAC00
	adds r0, r0, r1
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x58]
	ldr r2, _08081328 @ =0xFFFFD000
	adds r0, r0, r2
	str r0, [r4, #0x68]
	movs r0, #0x64
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080812EE:
	ldrb r0, [r4, #0x12]
	subs r6, r0, #1
	strb r6, [r4, #0x12]
	ldr r1, [r4, #0x64]
	ldr r2, [r4, #0x54]
	subs r1, r1, r2
	ldr r0, [r4, #0x68]
	ldr r5, [r4, #0x58]
	subs r3, r0, r5
	lsls r0, r1, #1
	adds r0, r0, r1
	cmp r0, #0
	bge _0808130A
	adds r0, #0xff
_0808130A:
	asrs r0, r0, #8
	adds r0, r2, r0
	str r0, [r4, #0x54]
	adds r0, r3, #0
	cmp r0, #0
	bge _08081318
	adds r0, #0xf
_08081318:
	asrs r0, r0, #4
	adds r0, r5, r0
	str r0, [r4, #0x58]
	lsls r0, r6, #0x18
	b _080813A6
	.align 2, 0
_08081324: .4byte 0xFFFFAC00
_08081328: .4byte 0xFFFFD000
_0808132C:
	adds r2, r5, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #1
	orrs r0, r1
	str r0, [r2]
	movs r0, #0xa0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081342:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _0808137E
	ldr r2, _08081384 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08081388 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0808138C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xa0
	lsls r1, r1, #5
	bl __umodsi3
	ldr r2, _08081390 @ =0xFFFFF600
	adds r0, r0, r2
	ldr r2, [r4, #0x54]
	adds r2, r2, r0
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl FUN_080c025c
_0808137E:
	ldrb r0, [r4, #0x12]
	b _080813A6
	.align 2, 0
_08081384: .4byte RNG_0202f388
_08081388: .4byte 0x000343FD
_0808138C: .4byte 0x00269EC3
_08081390: .4byte 0xFFFFF600
_08081394:
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808139E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
_080813A6:
	cmp r0, #0
	bne _080813B0
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080813B0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08081428
_080813B8:
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080813C4:
	ldr r0, [r4, #0x54]
	movs r1, #0x80
	lsls r1, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x60]
	adds r1, #4
	str r1, [r4, #0x60]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, _08081430 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _08081428
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08081434 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08081428:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08081430: .4byte gStageRun+232
_08081434: .4byte gEnemyFnTable

	thumb_func_start FUN_08081438
FUN_08081438: @ 0x08081438
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	mov sb, r0
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bhi _08081456
	ldr r0, _080814A8 @ =pZero2
	ldr r0, [r0]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080814B8
_08081456:
	ldr r2, _080814AC @ =gWindowRegBuffer
	ldrh r1, [r2]
	ldr r0, _080814B0 @ =0x0000BFFF
	ands r0, r1
	movs r4, #0
	movs r3, #0
	strh r0, [r2]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r3, [r0]
	adds r0, #4
	str r3, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080814B4 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	mov r2, sb
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	str r0, [r2]
	b _0808179C
	.align 2, 0
_080814A8: .4byte pZero2
_080814AC: .4byte gWindowRegBuffer
_080814B0: .4byte 0x0000BFFF
_080814B4: .4byte gEnemyFnTable
_080814B8:
	ldrb r0, [r5, #0xe]
	movs r1, #0xb6
	adds r1, r1, r5
	mov r8, r1
	adds r7, r5, #0
	adds r7, #0xb7
	cmp r0, #5
	bls _080814CA
	b _08081756
_080814CA:
	lsls r0, r0, #2
	ldr r1, _080814D4 @ =_080814D8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080814D4: .4byte _080814D8
_080814D8: @ jump table
	.4byte _080814F0 @ case 0
	.4byte _080815A0 @ case 1
	.4byte _08081604 @ case 2
	.4byte _08081614 @ case 3
	.4byte _080816B2 @ case 4
	.4byte _080816B8 @ case 5
_080814F0:
	ldrb r0, [r5, #0x11]
	cmp r0, #1
	bne _08081540
	adds r0, r5, #0
	bl FUN_080808b4
	movs r2, #0
	ldr r0, _08081518 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _0808150C
	movs r2, #1
_0808150C:
	cmp r2, #0
	beq _0808151C
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08081522
	.align 2, 0
_08081518: .4byte pZero2
_0808151C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08081522:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	b _0808155E
_08081540:
	movs r2, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
_0808155E:
	adds r0, r5, #0
	adds r0, #0x34
	ldr r1, _080815F4 @ =FUN_08080cbc
	bl SetTaskCallback
	ldrb r1, [r5, #0xa]
	movs r0, #0xf7
	ands r0, r1
	strb r0, [r5, #0xa]
	str r5, [r5, #0x3c]
	ldr r1, _080815F8 @ =gWindowRegBuffer
	ldrh r2, [r1]
	movs r3, #0x80
	lsls r3, r3, #7
	adds r0, r3, #0
	movs r3, #0
	orrs r0, r2
	strh r0, [r1]
	movs r0, #0x21
	strb r0, [r1, #0xd]
	ldrb r2, [r1, #0xe]
	movs r0, #0xe
	orrs r0, r2
	strb r0, [r1, #0xe]
	adds r1, r5, #0
	adds r1, #0xb6
	movs r0, #4
	strb r0, [r1]
	strb r3, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	mov r8, r1
_080815A0:
	ldrb r0, [r5, #0x13]
	lsrs r0, r0, #3
	adds r0, #4
	adds r1, r5, #0
	adds r1, #0xb7
	strb r0, [r1]
	ldrb r0, [r5, #0x13]
	adds r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r7, r1, #0
	cmp r0, #0x10
	bls _080815C2
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080815C2:
	ldrb r0, [r5, #0x13]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	ldr r4, _080815FC @ =gPaletteManager
	ldr r3, _08081600 @ =0x0836810A
	lsls r1, r6, #1
	adds r1, r1, r6
	adds r0, r3, #2
	adds r0, r1, r0
	ldrb r2, [r0]
	lsls r2, r2, #0xa
	adds r0, r3, #1
	adds r0, r1, r0
	ldrb r0, [r0]
	lsls r0, r0, #5
	orrs r2, r0
	adds r1, r1, r3
	ldrb r0, [r1]
	orrs r0, r2
	strh r0, [r4]
	b _08081756
	.align 2, 0
_080815F4: .4byte FUN_08080cbc
_080815F8: .4byte gWindowRegBuffer
_080815FC: .4byte gPaletteManager
_08081600: .4byte 0x0836810A
_08081604:
	adds r1, r5, #0
	adds r1, #0xb6
	ldrb r0, [r1]
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	mov r8, r1
_08081614:
	ldrb r0, [r5, #0x13]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	ldr r4, _0808169C @ =gPaletteManager
	ldr r3, _080816A0 @ =0x0836810A
	lsls r1, r6, #1
	adds r1, r1, r6
	adds r0, r3, #2
	adds r0, r1, r0
	ldrb r2, [r0]
	lsls r2, r2, #0xa
	adds r0, r3, #1
	adds r0, r1, r0
	ldrb r0, [r0]
	lsls r0, r0, #5
	orrs r2, r0
	adds r1, r1, r3
	ldrb r0, [r1]
	orrs r0, r2
	strh r0, [r4]
	adds r1, r5, #0
	adds r1, #0xb7
	ldrb r0, [r1]
	adds r0, #2
	strb r0, [r1]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r7, r1, #0
	cmp r0, #0x18
	bls _08081662
	mov r0, sb
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #2
	orrs r1, r2
	str r1, [r0]
_08081662:
	ldrb r1, [r7]
	ldrb r0, [r5, #0x12]
	subs r2, r1, r0
	cmp r2, #3
	ble _08081670
	subs r0, r1, #3
	strb r0, [r5, #0x12]
_08081670:
	ldrb r4, [r7]
	mov r0, r8
	strb r4, [r0]
	adds r0, r6, #1
	muls r0, r2, r0
	movs r1, #3
	bl __divsi3
	subs r4, r4, r0
	mov r1, r8
	strb r4, [r1]
	ldrb r0, [r5, #0x13]
	adds r0, #1
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _080816A4
	ldrb r0, [r7]
	cmp r0, #0x20
	bls _08081756
	b _080816AA
	.align 2, 0
_0808169C: .4byte gPaletteManager
_080816A0: .4byte 0x0836810A
_080816A4:
	ldrb r0, [r7]
	cmp r0, #0x78
	bls _08081756
_080816AA:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _08081756
_080816B2:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080816B8:
	adds r0, r5, #0
	adds r0, #0xb6
	ldrb r1, [r0]
	adds r1, #1
	movs r4, #0
	strb r1, [r0]
	adds r2, r5, #0
	adds r2, #0xb7
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	mov r8, r0
	adds r7, r2, #0
	ldrb r3, [r7]
	cmp r1, r3
	blo _08081722
	mov r2, sb
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	str r0, [r2]
	ldr r2, _08081770 @ =gWindowRegBuffer
	ldrh r1, [r2]
	ldr r0, _08081774 @ =0x0000BFFF
	ands r0, r1
	movs r3, #0
	strh r0, [r2]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r3, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08081778 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_08081722:
	ldrb r0, [r5, #0x13]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	ldr r4, _0808177C @ =gPaletteManager
	ldr r3, _08081780 @ =0x0836810A
	lsls r1, r6, #1
	adds r1, r1, r6
	adds r0, r3, #2
	adds r0, r1, r0
	ldrb r2, [r0]
	lsls r2, r2, #0xa
	adds r0, r3, #1
	adds r0, r1, r0
	ldrb r0, [r0]
	lsls r0, r0, #5
	orrs r2, r0
	adds r1, r1, r3
	ldrb r0, [r1]
	orrs r0, r2
	strh r0, [r4]
	ldrb r0, [r5, #0x13]
	adds r0, #1
	strb r0, [r5, #0x13]
_08081756:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08081784
	mov r0, r8
	ldrb r1, [r0]
	adds r0, r5, #0
	adds r0, #0xb4
	strb r1, [r0]
	ldrb r1, [r7]
	adds r0, #1
	b _0808179A
	.align 2, 0
_08081770: .4byte gWindowRegBuffer
_08081774: .4byte 0x0000BFFF
_08081778: .4byte gEnemyFnTable
_0808177C: .4byte gPaletteManager
_08081780: .4byte 0x0836810A
_08081784:
	mov r1, r8
	ldrb r0, [r1]
	movs r1, #0x80
	subs r0, r1, r0
	adds r2, r5, #0
	adds r2, #0xb5
	strb r0, [r2]
	ldrb r0, [r7]
	subs r1, r1, r0
	adds r0, r5, #0
	adds r0, #0xb4
_0808179A:
	strb r1, [r0]
_0808179C:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
