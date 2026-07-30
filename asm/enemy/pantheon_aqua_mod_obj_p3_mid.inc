	.include "asm/macros.inc"

	.syntax unified
	
	.text

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
