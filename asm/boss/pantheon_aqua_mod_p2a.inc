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

	thumb_func_start paquam_080519d0
paquam_080519d0: @ 0x080519D0
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #7
	bls _080519DE
	b _08051B82
_080519DE:
	lsls r0, r0, #2
	ldr r1, _080519E8 @ =_080519EC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080519E8: .4byte _080519EC
_080519EC: @ jump table
	.4byte _08051A0C @ case 0
	.4byte _08051A54 @ case 1
	.4byte _08051A74 @ case 2
	.4byte _08051AAC @ case 3
	.4byte _08051AE4 @ case 4
	.4byte _08051B14 @ case 5
	.4byte _08051B54 @ case 6
	.4byte _08051B64 @ case 7
_08051A0C:
	movs r0, #0x8d
	lsls r0, r0, #1
	bl PlaySound
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08051A70 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	movs r1, #1
	movs r2, #0
	bl CreateVFX39
	adds r3, r0, #0
	str r3, [r4, #0x2c]
	cmp r3, #0
	beq _08051A46
	adds r0, #0x7c
	movs r1, #0
	strb r1, [r0]
	subs r0, #8
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	str r1, [r3, #0x78]
_08051A46:
	movs r1, #0
	movs r0, #0x32
	strb r0, [r4, #0x12]
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051A54:
	ldr r1, [r4, #0x5c]
	movs r0, #0xb0
	lsls r0, r0, #7
	subs r0, r0, r1
	cmp r0, #0
	bge _08051A62
	adds r0, #0x1f
_08051A62:
	asrs r0, r0, #5
	adds r5, r1, r0
	str r5, [r4, #0x5c]
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _08051ACA
	b _08051AB4
	.align 2, 0
_08051A70: .4byte 0xFFFFF000
_08051A74:
	adds r1, r4, #0
	adds r1, #0x4c
	movs r0, #0
	strb r0, [r1]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	subs r0, #0x11
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0xbc
	ldr r0, [r0]
	str r0, [r4, #0x58]
	movs r1, #0x9a
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051AAC:
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _08051ACA
	ldr r5, [r4, #0x5c]
_08051AB4:
	adds r2, r5, #0
	cmp r5, #0
	bge _08051ABC
	adds r2, r5, #7
_08051ABC:
	asrs r2, r2, #3
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	muls r0, r2, r0
	adds r0, r5, r0
	str r0, [r3, #0x78]
_08051ACA:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08051ADC
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051ADC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08051B82
_08051AE4:
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x52
	bl StartPaletteAnimation
	adds r1, r4, #0
	adds r1, #0xb8
	movs r0, #0x52
	strb r0, [r1]
	bl StepPaletteAnimation
	movs r0, #0x60
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051B14:
	ldr r0, [r4, #0x5c]
	subs r0, #0xa0
	str r0, [r4, #0x5c]
	cmp r0, #0
	bge _08051B22
	movs r0, #0
	str r0, [r4, #0x5c]
_08051B22:
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _08051B40
	ldr r5, [r4, #0x5c]
	adds r2, r5, #0
	cmp r5, #0
	bge _08051B32
	adds r2, r5, #7
_08051B32:
	asrs r2, r2, #3
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	muls r0, r2, r0
	adds r0, r5, r0
	str r0, [r3, #0x78]
_08051B40:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08051B82
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08051B82
_08051B54:
	ldr r3, [r4, #0x2c]
	adds r1, r3, #0
	adds r1, #0x77
	movs r0, #1
	strb r0, [r1]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051B64:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #3
	bne _08051B7C
	movs r0, #0
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
_08051B7C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08051B82:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

