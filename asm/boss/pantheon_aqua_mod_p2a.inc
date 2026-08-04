	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start paquam_080517ac
paquam_080517ac: @ 0x080517AC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0xb
	bls _080517B8
	b _080519B6
_080517B8:
	lsls r0, r0, #2
	ldr r1, _080517C4 @ =_080517C8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080517C4: .4byte _080517C8
_080517C8: @ jump table
	.4byte _080517F8 @ case 0
	.4byte _0805183E @ case 1
	.4byte _08051874 @ case 2
	.4byte _080518E6 @ case 3
	.4byte _0805188C @ case 4
	.4byte _0805189E @ case 5
	.4byte _080518C0 @ case 6
	.4byte _080518E6 @ case 7
	.4byte _08051908 @ case 8
	.4byte _0805191A @ case 9
	.4byte _08051960 @ case 10
	.4byte _08051976 @ case 11
_080517F8:
	adds r1, r5, #0
	adds r1, #0x25
	movs r4, #0
	movs r0, #0x1a
	strb r0, [r1]
	adds r0, r5, #0
	bl FUN_08080908
	adds r0, r5, #0
	bl FUN_08080964
	adds r1, r5, #0
	adds r1, #0x4c
	movs r0, #1
	strb r0, [r1]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r5, #0xa]
	orrs r1, r0
	strb r1, [r5, #0xa]
	movs r1, #0x9c
	lsls r1, r1, #6
	adds r0, r5, #0
	bl SetMotion
	strb r4, [r5, #0x12]
	ldr r0, [r5, #0x58]
	str r0, [r5, #0x68]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805183E:
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08051856
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08051856:
	ldr r1, [r5, #0x68]
	str r1, [r5, #0x58]
	ldr r2, _08051870 @ =gSineTable
	ldrb r0, [r5, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #2
	adds r1, r1, r0
	str r1, [r5, #0x58]
	b _08051954
	.align 2, 0
_08051870: .4byte gSineTable
_08051874:
	adds r2, r5, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #5
	orrs r0, r1
	str r0, [r2]
	ldr r1, _08051888 @ =0x00002702
	b _080518DA
	.align 2, 0
_08051888: .4byte 0x00002702
_0805188C:
	movs r0, #0x20
	strb r0, [r5, #0x13]
	ldr r1, _080518BC @ =0x00002704
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805189E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	bne _080518B8
	b _080519B6
_080518B8:
	b _080518F6
	.align 2, 0
_080518BC: .4byte 0x00002704
_080518C0:
	movs r0, #0x63
	bl PlaySound
	ldr r0, [r5, #0x54]
	movs r1, #0xf0
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	ldr r2, _08051900 @ =0xFFFFE300
	adds r1, r1, r2
	bl FUN_08080c64
	ldr r1, _08051904 @ =0x00002706
_080518DA:
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080518E6:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080519B6
_080518F6:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080519B6
	.align 2, 0
_08051900: .4byte 0xFFFFE300
_08051904: .4byte 0x00002706
_08051908:
	movs r0, #0x20
	strb r0, [r5, #0x13]
	ldr r1, _0805195C @ =0x00002707
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805191A:
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0805193A
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805193A
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805193A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080519B6
	movs r1, #0x9c
	lsls r1, r1, #6
	adds r0, r5, #0
	bl SetMotion
_08051954:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080519B6
	.align 2, 0
_0805195C: .4byte 0x00002707
_08051960:
	movs r0, #0xc8
	strb r0, [r5, #0x12]
	ldr r0, [r5, #0x54]
	str r0, [r5, #0x64]
	ldr r1, _080519BC @ =0x00002708
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08051976:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _08051990
	movs r0, #2
	strb r0, [r5, #0xd]
	movs r0, #0
	strb r0, [r5, #0xe]
_08051990:
	ldr r2, [r5, #0x64]
	ldr r0, _080519C0 @ =0xFFFFFE00
	adds r2, r2, r0
	ldr r3, _080519C4 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _080519C8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080519CC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #5
	lsrs r0, r0, #0x16
	adds r2, r2, r0
	str r2, [r5, #0x54]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080519B6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080519BC: .4byte 0x00002708
_080519C0: .4byte 0xFFFFFE00
_080519C4: .4byte RNG_0202f388
_080519C8: .4byte 0x000343FD
_080519CC: .4byte 0x00269EC3
