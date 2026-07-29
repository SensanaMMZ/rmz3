	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080478b8
FUN_080478b8: @ 0x080478B8
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x2c]
	ldrb r4, [r5, #0xe]
	cmp r4, #1
	beq _0804790C
	cmp r4, #1
	bgt _080478CE
	cmp r4, #0
	beq _080478D8
	b _080479C4
_080478CE:
	cmp r4, #2
	beq _0804792C
	cmp r4, #3
	beq _08047984
	b _080479C4
_080478D8:
	adds r6, r5, #0
	adds r6, #0xc6
	ldrb r0, [r6]
	cmp r0, #0
	beq _080478E8
	bl RemovePaletteAnimation
	strb r4, [r6]
_080478E8:
	adds r0, r5, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x1f
	bl StartPaletteAnimation
	movs r0, #0x1f
	strb r0, [r6]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804790C:
	adds r0, r5, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _08047924
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08047924:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080479C4
_0804792C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080479CC @ =0x08362674
	bl SetDDP
	adds r0, r6, #0
	adds r0, #0x22
	movs r7, #0
	strb r7, [r0]
	ldr r4, _080479D0 @ =0x0000330A
	adds r0, r6, #0
	adds r1, r4, #0
	bl SetMotion
	adds r0, r5, #0
	adds r1, r4, #0
	bl SetMotion
	adds r4, r5, #0
	adds r4, #0xc6
	ldrb r0, [r4]
	cmp r0, #0
	beq _08047960
	bl RemovePaletteAnimation
	strb r7, [r4]
_08047960:
	adds r0, r5, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x1c
	bl StartPaletteAnimation
	movs r0, #0x1c
	strb r0, [r4]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08047984:
	adds r4, r5, #0
	adds r4, #0xc6
	ldrb r0, [r4]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _080479B8
	ldrb r0, [r4]
	cmp r0, #0
	beq _080479A4
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_080479A4:
	movs r2, #0
	movs r1, #0xb
	strb r1, [r6, #0xd]
	strb r2, [r6, #0xe]
	ldr r0, [r5, #0x54]
	str r0, [r6, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r6, #0x58]
	strb r1, [r5, #0xd]
	strb r2, [r5, #0xe]
_080479B8:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080479C4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080479CC: .4byte 0x08362674
_080479D0: .4byte 0x0000330A

	thumb_func_start babyelf_080479d4
babyelf_080479d4: @ 0x080479D4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	mov r8, r0
	ldrb r0, [r0, #0xe]
	cmp r0, #1
	beq _08047A90
	cmp r0, #1
	bgt _080479EE
	cmp r0, #0
	beq _080479FC
	b _08047BF6
_080479EE:
	cmp r0, #2
	bne _080479F4
	b _08047B08
_080479F4:
	cmp r0, #3
	bne _080479FA
	b _08047B6C
_080479FA:
	b _08047BF6
_080479FC:
	ldr r0, _08047A48 @ =0x00000117
	bl PlaySound
	mov r0, r8
	adds r0, #0x74
	ldr r1, _08047A4C @ =0x08362674
	bl SetDDP
	mov r1, r8
	ldrb r0, [r1, #0x10]
	adds r1, #0x22
	strb r0, [r1]
	movs r1, #0xc4
	lsls r1, r1, #6
	mov r0, r8
	bl SetMotion
	mov r2, r8
	ldrb r0, [r2, #0x10]
	cmp r0, #0
	bne _08047A50
	mov r0, r8
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	orrs r1, r0
	movs r0, #0x16
	bl StartPaletteAnimation
	mov r1, r8
	adds r1, #0xc6
	movs r0, #0x16
	b _08047A70
	.align 2, 0
_08047A48: .4byte 0x00000117
_08047A4C: .4byte 0x08362674
_08047A50:
	mov r0, r8
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r6, #0x80
	lsls r6, r6, #2
	adds r0, r6, #0
	orrs r1, r0
	movs r0, #0x11
	bl StartPaletteAnimation
	mov r1, r8
	adds r1, #0xc6
	movs r0, #0x11
_08047A70:
	strb r0, [r1]
	mov r0, r8
	ldrb r1, [r0, #0xa]
	movs r0, #1
	movs r2, #0
	orrs r0, r1
	mov r1, r8
	strb r0, [r1, #0xa]
	ldrb r0, [r1, #0x10]
	adds r1, #0xc7
	strb r0, [r1]
	mov r3, r8
	strb r2, [r3, #0x12]
	ldrb r0, [r3, #0xe]
	adds r0, #1
	strb r0, [r3, #0xe]
_08047A90:
	mov r0, r8
	adds r0, #0xb4
	ldr r0, [r0]
	mov r6, r8
	ldr r5, [r6, #0x54]
	subs r6, r0, r5
	ldr r0, _08047B04 @ =0xFFFFA800
	adds r6, r6, r0
	mov r0, r8
	adds r0, #0xc7
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #0xc
	adds r6, r6, r0
	mov r0, r8
	adds r0, #0xb8
	mov r1, r8
	ldr r4, [r1, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r1, r4, r2
	ldr r0, [r0]
	subs r7, r0, r1
	adds r0, r6, #0
	movs r1, #0xc
	bl __divsi3
	adds r6, r0, #0
	adds r0, r7, #0
	movs r1, #0xc
	bl __divsi3
	adds r7, r0, #0
	adds r5, r5, r6
	mov r3, r8
	str r5, [r3, #0x54]
	adds r4, r4, r7
	str r4, [r3, #0x58]
	mov r0, r8
	bl UpdateMotionGraphic
	mov r0, r8
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _08047BF6
	mov r6, r8
	ldrb r0, [r6, #0xe]
	adds r0, #1
	b _08047BF4
	.align 2, 0
_08047B04: .4byte 0xFFFFA800
_08047B08:
	movs r0, #0x28
	mov r1, r8
	strb r0, [r1, #0x13]
	mov r4, r8
	adds r4, #0xc6
	ldrb r0, [r4]
	cmp r0, #0
	beq _08047B20
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_08047B20:
	mov r2, r8
	ldrb r0, [r2, #0x10]
	cmp r0, #0
	bne _08047B46
	mov r0, r8
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	orrs r1, r0
	movs r0, #0x14
	bl StartPaletteAnimation
	movs r0, #0x14
	b _08047B62
_08047B46:
	mov r0, r8
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r6, #0x80
	lsls r6, r6, #2
	adds r0, r6, #0
	orrs r1, r0
	movs r0, #0xf
	bl StartPaletteAnimation
	movs r0, #0xf
_08047B62:
	strb r0, [r4]
	mov r1, r8
	ldrb r0, [r1, #0xe]
	adds r0, #1
	strb r0, [r1, #0xe]
_08047B6C:
	mov r0, r8
	adds r0, #0xb4
	ldr r0, [r0]
	mov r2, r8
	ldr r5, [r2, #0x54]
	subs r6, r0, r5
	ldr r3, _08047C5C @ =0xFFFFA800
	adds r6, r6, r3
	mov r0, r8
	adds r0, #0xc7
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #0xc
	adds r6, r6, r0
	mov r0, r8
	adds r0, #0xb8
	ldr r4, [r2, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r1, r4, r2
	ldr r0, [r0]
	subs r7, r0, r1
	adds r0, r6, #0
	movs r1, #0xc
	bl __divsi3
	adds r6, r0, #0
	adds r0, r7, #0
	movs r1, #0xc
	bl __divsi3
	adds r7, r0, #0
	adds r5, r5, r6
	mov r3, r8
	str r5, [r3, #0x54]
	adds r4, r4, r7
	str r4, [r3, #0x58]
	mov r0, r8
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	mov r0, r8
	bl UpdateMotionGraphic
	mov r6, r8
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _08047BF6
	mov r1, r8
	adds r1, #0xbc
	ldr r0, [r6, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r6, #0x58]
	str r0, [r1]
	mov r0, r8
	adds r0, #0xc4
	strh r2, [r0]
	movs r0, #1
	strb r0, [r6, #0xd]
_08047BF4:
	strb r0, [r6, #0xe]
_08047BF6:
	mov r1, r8
	ldrb r0, [r1, #0x12]
	adds r0, #1
	strb r0, [r1, #0x12]
	ldrb r0, [r1, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08047C50
	ldr r5, _08047C60 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08047C64 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08047C68 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r6, _08047C6C @ =0xFFFFFC00
	adds r1, r1, r6
	mov r6, r8
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	movs r1, #0x80
	lsls r1, r1, #4
	adds r2, r2, r1
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0
	movs r3, #0
	bl FUN_080bc594
_08047C50:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08047C5C: .4byte 0xFFFFA800
_08047C60: .4byte RNG_0202f388
_08047C64: .4byte 0x000343FD
_08047C68: .4byte 0x00269EC3
_08047C6C: .4byte 0xFFFFFC00

	thumb_func_start babyelf_08047c70
babyelf_08047c70: @ 0x08047C70
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _08047C82
	cmp r0, #1
	beq _08047CEC
	b _08047E0C
_08047C82:
	ldr r2, _08047CA8 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08047CAC @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08047CB0 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08047CB4
	movs r0, #0x8a
	lsls r0, r0, #1
	bl PlaySound
	b _08047CBA
	.align 2, 0
_08047CA8: .4byte RNG_0202f388
_08047CAC: .4byte 0x000343FD
_08047CB0: .4byte 0x00269EC3
_08047CB4:
	ldr r0, _08047E14 @ =0x00000115
	bl PlaySound
_08047CBA:
	adds r1, r6, #0
	adds r1, #0xbc
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r0, [r0]
	str r0, [r1]
	adds r1, #4
	adds r0, r6, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r2, _08047E18 @ =0xFFFFB000
	adds r0, r0, r2
	str r0, [r1]
	adds r0, r6, #0
	adds r0, #0xc7
	ldrb r1, [r0]
	movs r0, #1
	subs r0, r0, r1
	lsls r0, r0, #0xf
	str r0, [r6, #0x64]
	movs r0, #0
	str r0, [r6, #0x68]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047CEC:
	ldr r0, [r6, #0x68]
	adds r0, #8
	str r0, [r6, #0x68]
	movs r1, #0xa0
	lsls r1, r1, #2
	cmp r0, r1
	ble _08047CFC
	str r1, [r6, #0x68]
_08047CFC:
	ldr r2, [r6, #0x64]
	ldr r0, [r6, #0x68]
	subs r2, r2, r0
	str r2, [r6, #0x64]
	movs r3, #0xc7
	adds r3, r3, r6
	mov ip, r3
	ldrb r1, [r3]
	movs r3, #1
	subs r1, r3, r1
	lsls r1, r1, #7
	movs r0, #0xc0
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #8
	rsbs r0, r0, #0
	cmp r2, r0
	bge _08047D28
	str r0, [r6, #0x64]
	movs r0, #0
	strb r3, [r6, #0xd]
	strb r0, [r6, #0xe]
_08047D28:
	movs r4, #0xb0
	lsls r4, r4, #7
	str r4, [r6, #0x5c]
	ldr r5, [r6, #0x64]
	asrs r1, r5, #8
	mov r2, ip
	ldrb r0, [r2]
	subs r0, r3, r0
	lsls r0, r0, #7
	ldr r7, _08047E1C @ =gSineTable
	subs r0, r0, r1
	movs r1, #6
	bl __divsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r7
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r2, r0, r4
	str r2, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r1, [r0]
	str r1, [r6, #0x54]
	asrs r5, r5, #8
	adds r0, r5, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r7
	movs r4, #0
	ldrsh r0, [r0, r4]
	muls r0, r2, r0
	cmp r0, #0
	bge _08047D78
	adds r0, #0xff
_08047D78:
	asrs r0, r0, #8
	adds r0, r1, r0
	str r0, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r3, [r0]
	str r3, [r6, #0x58]
	lsls r0, r5, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r7
	movs r4, #0
	ldrsh r1, [r0, r4]
	asrs r0, r2, #1
	muls r0, r1, r0
	cmp r0, #0
	bge _08047D9A
	adds r0, #0xff
_08047D9A:
	asrs r0, r0, #8
	adds r0, r3, r0
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08047DFC
	ldr r5, _08047E20 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08047E24 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08047E28 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08047E2C @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	movs r1, #0x80
	lsls r1, r1, #4
	adds r2, r2, r1
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0
	movs r3, #0
	bl FUN_080bc594
_08047DFC:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
_08047E0C:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08047E14: .4byte 0x00000115
_08047E18: .4byte 0xFFFFB000
_08047E1C: .4byte gSineTable
_08047E20: .4byte RNG_0202f388
_08047E24: .4byte 0x000343FD
_08047E28: .4byte 0x00269EC3
_08047E2C: .4byte 0xFFFFFC00

	thumb_func_start babyelf_08047e30
babyelf_08047e30: @ 0x08047E30
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _08047E98
	cmp r0, #1
	bgt _08047E46
	cmp r0, #0
	beq _08047E52
	b _08047F74
_08047E46:
	cmp r0, #2
	beq _08047F40
	cmp r0, #3
	bne _08047E50
	b _08047F60
_08047E50:
	b _08047F74
_08047E52:
	ldr r2, _08047E78 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08047E7C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08047E80 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08047E84
	movs r0, #0x8a
	lsls r0, r0, #1
	bl PlaySound
	b _08047E8A
	.align 2, 0
_08047E78: .4byte RNG_0202f388
_08047E7C: .4byte 0x000343FD
_08047E80: .4byte 0x00269EC3
_08047E84:
	ldr r0, _08047F2C @ =0x00000115
	bl PlaySound
_08047E8A:
	movs r1, #0
	movs r0, #0x30
	strb r0, [r6, #0x13]
	str r1, [r6, #0x5c]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047E98:
	ldr r1, [r6, #0x5c]
	subs r1, #0x10
	str r1, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xc7
	ldrb r0, [r0]
	lsls r0, r0, #5
	adds r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08047EC2
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047EC2:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08047F18
	ldr r5, _08047F30 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08047F34 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08047F38 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08047F3C @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	movs r1, #0x80
	lsls r1, r1, #4
	adds r2, r2, r1
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0
	movs r3, #0
	bl FUN_080bc594
_08047F18:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _08047F74
	.align 2, 0
_08047F2C: .4byte 0x00000115
_08047F30: .4byte RNG_0202f388
_08047F34: .4byte 0x000343FD
_08047F38: .4byte 0x00269EC3
_08047F3C: .4byte 0xFFFFFC00
_08047F40:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08047F7C @ =sCollisions
	bl SetDDP
	adds r0, r6, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r1, _08047F80 @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r0, #0x30
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047F60:
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08047F74
	movs r0, #0xe
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_08047F74:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08047F7C: .4byte sCollisions
_08047F80: .4byte 0xFFFFE000

	thumb_func_start FUN_08047f84
FUN_08047f84: @ 0x08047F84
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #5
	bls _08047F92
	b _0804810C
_08047F92:
	lsls r0, r0, #2
	ldr r1, _08047FA0 @ =0x08047FA4
	adds r0, r0, r1
	ldr r0, [r0]
	adds r4, r6, #0
	adds r4, #0xc7
	mov pc, r0
	.align 2, 0
_08047FA0: .4byte 0x08047FA4
_08047FA4:
	.byte 0xBC, 0x7F, 0x04, 0x08, 0xE2, 0x7F, 0x04, 0x08, 0x34, 0x80, 0x04, 0x08
	.byte 0x54, 0x80, 0x04, 0x08, 0xBC, 0x80, 0x04, 0x08, 0xC2, 0x80, 0x04, 0x08, 0xC0, 0x22, 0x92, 0x00
	.byte 0xF2, 0x65, 0x34, 0x1C, 0xC7, 0x34, 0x21, 0x78, 0x48, 0x00, 0x40, 0x18, 0x40, 0x02, 0x12, 0x1A
	.byte 0xF2, 0x65, 0x30, 0x1C, 0x74, 0x30, 0x15, 0x49, 0xBF, 0xF7, 0x1C, 0xF9, 0xB0, 0x7B, 0x01, 0x30
	.byte 0xB0, 0x73, 0x70, 0x6D, 0xF1, 0x6D, 0x41, 0x18, 0x71, 0x65, 0x20, 0x78, 0x00, 0x28, 0x0A, 0xD1
	.byte 0x30, 0x1C, 0xB4, 0x30, 0x00, 0x68, 0x0E, 0x4A, 0x80, 0x18, 0x81, 0x42, 0x03, 0xDD, 0x70, 0x65
	.byte 0xB0, 0x7B, 0x01, 0x30, 0xB0, 0x73, 0x20, 0x78, 0x01, 0x28, 0x00, 0xD0, 0x7E, 0xE0, 0x30, 0x1C
	.byte 0xB4, 0x30, 0x00, 0x68, 0xA0, 0x23, 0xDB, 0x01, 0xC1, 0x18, 0x70, 0x6D, 0x88, 0x42, 0x75, 0xDA
	.byte 0x71, 0x65, 0xB0, 0x7B, 0x01, 0x30, 0xB0, 0x73, 0x70, 0xE0, 0x00, 0x00, 0x74, 0x26, 0x36, 0x08
	.byte 0x00, 0xB0, 0xFF, 0xFF, 0x40, 0x20, 0xF0, 0x74, 0x2A, 0x20, 0x70, 0x66, 0x31, 0x1C, 0xBC, 0x31
	.byte 0x70, 0x6D, 0x08, 0x60, 0x04, 0x31, 0xB0, 0x6D, 0x0A, 0x4A, 0x80, 0x18, 0x08, 0x60, 0xB0, 0x7B
	.byte 0x01, 0x30, 0xB0, 0x73, 0x70, 0x6E, 0x01, 0x38, 0x70, 0x66, 0x00, 0x28, 0x02, 0xD1, 0xB0, 0x7B
	.byte 0x01, 0x30, 0xB0, 0x73, 0x30, 0x1C, 0xC7, 0x30, 0x00, 0x78, 0x00, 0x28, 0x04, 0xD1, 0xF0, 0x7C
	.byte 0x06, 0x38, 0x03, 0xE0, 0x00, 0xF0, 0xFF, 0xFF, 0xF0, 0x7C, 0x06, 0x30, 0xF0, 0x74, 0x30, 0x1C
	.byte 0xBC, 0x30, 0x01, 0x68, 0x71, 0x65, 0x0C, 0x4A, 0xF0, 0x7C, 0x40, 0x30, 0x00, 0x06, 0xC0, 0x0D
	.byte 0x80, 0x18, 0x00, 0x23, 0xC0, 0x5E, 0x00, 0x01, 0x09, 0x18, 0x71, 0x65, 0x30, 0x1C, 0xC0, 0x30
	.byte 0x01, 0x68, 0xB1, 0x65, 0xF0, 0x7C, 0x40, 0x00, 0x80, 0x18, 0x00, 0x22, 0x80, 0x5E, 0x00, 0x01
	.byte 0x09, 0x18, 0xB1, 0x65, 0x2A, 0xE0, 0x00, 0x00, 0x74, 0xEA, 0x0F, 0x08, 0xB0, 0x7B, 0x01, 0x30
	.byte 0xB0, 0x73, 0x70, 0x6D, 0xF1, 0x6D, 0x41, 0x18, 0x71, 0x65, 0x30, 0x1C, 0xC7, 0x30, 0x02, 0x78
	.byte 0x04, 0x1C, 0x00, 0x2A, 0x09, 0xD1, 0x13, 0x38, 0x00, 0x68, 0x28, 0x4B, 0xC0, 0x18, 0x81, 0x42
	.byte 0x03, 0xDD, 0x70, 0x65, 0x0F, 0x20, 0x70, 0x73, 0xB2, 0x73, 0x20, 0x78, 0x01, 0x28, 0x0D, 0xD1
	.byte 0x30, 0x1C, 0xB4, 0x30, 0x00, 0x68, 0x80, 0x22, 0x52, 0x01, 0x81, 0x18, 0x70, 0x6D, 0x88, 0x42
	.byte 0x04, 0xDA, 0x71, 0x65, 0x00, 0x21, 0x0F, 0x20, 0x70, 0x73, 0xB1, 0x73
_0804810C:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08048162
	ldr r5, _08048180 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08048184 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08048188 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _0804818C @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	movs r1, #0x80
	lsls r1, r1, #4
	adds r2, r2, r1
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0
	movs r3, #0
	bl FUN_080bc594
_08048162:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804817C:
	.byte 0x00, 0xF0, 0xFF, 0xFF
_08048180: .4byte RNG_0202f388
_08048184: .4byte 0x000343FD
_08048188: .4byte 0x00269EC3
_0804818C: .4byte 0xFFFFFC00

	thumb_func_start FUN_08048190
FUN_08048190: @ 0x08048190
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #4
	bls _0804819E
	b _08048314
_0804819E:
	lsls r0, r0, #2
	ldr r1, _080481A8 @ =_080481AC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080481A8: .4byte _080481AC
_080481AC: @ jump table
	.4byte _080481C0 @ case 0
	.4byte _080481E0 @ case 1
	.4byte _08048248 @ case 2
	.4byte _08048270 @ case 3
	.4byte _080482A8 @ case 4
_080481C0:
	movs r0, #0x40
	strb r0, [r6, #0x13]
	movs r0, #0xa
	str r0, [r6, #0x64]
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r0, [r6, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r6, #0x58]
	ldr r2, _08048200 @ =0xFFFFF000
	adds r0, r0, r2
	str r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080481E0:
	ldr r0, [r6, #0x64]
	subs r0, #1
	str r0, [r6, #0x64]
	cmp r0, #0
	bne _080481F0
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080481F0:
	adds r0, r6, #0
	adds r0, #0xc7
	ldrb r0, [r0]
	cmp r0, #0
	bne _08048204
	ldrb r0, [r6, #0x13]
	subs r0, #6
	b _08048208
	.align 2, 0
_08048200: .4byte 0xFFFFF000
_08048204:
	ldrb r0, [r6, #0x13]
	adds r0, #6
_08048208:
	strb r0, [r6, #0x13]
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r1, [r0]
	str r1, [r6, #0x54]
	ldr r2, _08048244 @ =gSineTable
	ldrb r0, [r6, #0x13]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r0, [r0, r3]
	lsls r0, r0, #4
	adds r1, r1, r0
	str r1, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r1, [r0]
	str r1, [r6, #0x58]
	ldrb r0, [r6, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r4, #0
	ldrsh r0, [r0, r4]
	lsls r0, r0, #4
	adds r1, r1, r0
	str r1, [r6, #0x58]
	b _08048314
	.align 2, 0
_08048244: .4byte gSineTable
_08048248:
	ldr r1, [r6, #0x58]
	ldr r0, _08048268 @ =0xFFFFFD00
	adds r1, r1, r0
	str r1, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r2, _0804826C @ =0xFFFFB000
	adds r0, r0, r2
	cmp r1, r0
	bge _08048314
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _08048314
	.align 2, 0
_08048268: .4byte 0xFFFFFD00
_0804826C: .4byte 0xFFFFB000
_08048270:
	adds r1, r6, #0
	adds r1, #0xc7
	ldrb r0, [r1]
	lsls r0, r0, #7
	strb r0, [r6, #0x13]
	movs r0, #0x2a
	str r0, [r6, #0x64]
	adds r3, r6, #0
	adds r3, #0xbc
	ldr r2, [r6, #0x54]
	ldr r4, _080482C8 @ =0xFFFFD400
	adds r2, r2, r4
	str r2, [r3]
	ldrb r1, [r1]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #0xb
	adds r2, r2, r0
	str r2, [r3]
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r6, #0x58]
	str r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080482A8:
	ldr r0, [r6, #0x64]
	subs r1, r0, #1
	str r1, [r6, #0x64]
	cmp r1, #0
	bne _080482B8
	movs r0, #1
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_080482B8:
	adds r0, r6, #0
	adds r0, #0xc7
	ldrb r0, [r0]
	cmp r0, #0
	bne _080482CC
	ldrb r0, [r6, #0x13]
	subs r0, #3
	b _080482D0
	.align 2, 0
_080482C8: .4byte 0xFFFFD400
_080482CC:
	ldrb r0, [r6, #0x13]
	adds r0, #3
_080482D0:
	strb r0, [r6, #0x13]
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r2, [r0]
	str r2, [r6, #0x54]
	ldr r3, _08048384 @ =gSineTable
	ldrb r0, [r6, #0x13]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r1, [r0, r4]
	movs r0, #0x2c
	muls r0, r1, r0
	adds r2, r2, r0
	str r2, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r2, [r0]
	str r2, [r6, #0x58]
	ldrb r0, [r6, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r3, #0
	ldrsh r1, [r0, r3]
	ldr r0, _08048388 @ =0x00001D55
	muls r0, r1, r0
	cmp r0, #0
	bge _0804830E
	adds r0, #0xff
_0804830E:
	asrs r0, r0, #8
	adds r0, r2, r0
	str r0, [r6, #0x58]
_08048314:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804836A
	ldr r5, _0804838C @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08048390 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08048394 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08048398 @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	movs r1, #0x80
	lsls r1, r1, #4
	adds r2, r2, r1
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0
	movs r3, #0
	bl FUN_080bc594
_0804836A:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08048384: .4byte gSineTable
_08048388: .4byte 0x00001D55
_0804838C: .4byte RNG_0202f388
_08048390: .4byte 0x000343FD
_08048394: .4byte 0x00269EC3
_08048398: .4byte 0xFFFFFC00

	thumb_func_start FUN_0804839c
FUN_0804839c: @ 0x0804839C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0xa
	bls _080483A8
	b _08048540
_080483A8:
	lsls r0, r0, #2
	ldr r1, _080483B4 @ =_080483B8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080483B4: .4byte _080483B8
_080483B8: @ jump table
	.4byte _080483E4 @ case 0
	.4byte _080483FC @ case 1
	.4byte _0804840C @ case 2
	.4byte _08048430 @ case 3
	.4byte _08048454 @ case 4
	.4byte _08048472 @ case 5
	.4byte _08048494 @ case 6
	.4byte _080484B8 @ case 7
	.4byte _080484DC @ case 8
	.4byte _08048514 @ case 9
	.4byte _08048520 @ case 10
_080483E4:
	movs r1, #0
	movs r0, #0x1e
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0xce
	strb r1, [r0]
	adds r0, r4, #0
	bl FUN_0809f8ac
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080483FC:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0804840A
	b _08048502
_0804840A:
	b _080484FC
_0804840C:
	ldr r0, [r4, #0x54]
	ldr r1, _08048428 @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r1, [r1]
	ldr r2, _0804842C @ =0xFFFFB000
	adds r1, r1, r2
	cmp r0, r1
	bge _08048502
	str r1, [r4, #0x54]
	b _080484FC
	.align 2, 0
_08048428: .4byte 0xFFFFFE80
_0804842C: .4byte 0xFFFFB000
_08048430:
	ldr r0, [r4, #0x58]
	ldr r1, _0804844C @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r1, [r1]
	ldr r2, _08048450 @ =0xFFFF8800
	adds r1, r1, r2
	cmp r0, r1
	bge _08048502
	str r1, [r4, #0x58]
	b _080484FC
	.align 2, 0
_0804844C: .4byte 0xFFFFFE80
_08048450: .4byte 0xFFFF8800
_08048454:
	ldr r0, [r4, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r1, [r1]
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r1, r1, r2
	cmp r0, r1
	ble _08048502
	str r1, [r4, #0x54]
	b _080484FC
_08048472:
	ldr r0, [r4, #0x58]
	movs r1, #0xc0
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r1, [r1]
	ldr r2, _08048490 @ =0xFFFFC900
	adds r1, r1, r2
	cmp r0, r1
	ble _08048502
	str r1, [r4, #0x58]
	b _080484FC
	.align 2, 0
_08048490: .4byte 0xFFFFC900
_08048494:
	ldr r0, [r4, #0x54]
	ldr r1, _080484B0 @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r1, [r1]
	ldr r2, _080484B4 @ =0xFFFFB000
	adds r1, r1, r2
	cmp r0, r1
	bge _08048502
	str r1, [r4, #0x54]
	b _080484FC
	.align 2, 0
_080484B0: .4byte 0xFFFFFE80
_080484B4: .4byte 0xFFFFB000
_080484B8:
	ldr r0, [r4, #0x58]
	ldr r1, _080484D4 @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r1, [r1]
	ldr r2, _080484D8 @ =0xFFFF8800
	adds r1, r1, r2
	cmp r0, r1
	bge _08048502
	str r1, [r4, #0x58]
	b _080484FC
	.align 2, 0
_080484D4: .4byte 0xFFFFFE80
_080484D8: .4byte 0xFFFF8800
_080484DC:
	ldr r0, [r4, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r1, [r2]
	cmp r0, r1
	ble _08048502
	adds r1, r4, #0
	adds r1, #0xce
	movs r0, #1
	strb r0, [r1]
	ldr r0, [r2]
	str r0, [r4, #0x54]
_080484FC:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08048502:
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08048540
_08048514:
	movs r0, #0x96
	lsls r0, r0, #1
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08048520:
	ldr r0, [r4, #0x64]
	subs r1, r0, #1
	str r1, [r4, #0x64]
	cmp r1, #0
	bne _08048530
	movs r0, #0xa
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08048530:
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08048540:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08048548
FUN_08048548: @ 0x08048548
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	ldr r0, [r6, #0x28]
	mov r8, r0
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	bne _080485A0
	mov r1, r8
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _080485A0
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _0804859C @ =gBossFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _08048740
	.align 2, 0
_0804859C: .4byte gBossFnTable
_080485A0:
	ldrb r1, [r6, #0xe]
	cmp r1, #1
	beq _080485FA
	cmp r1, #1
	bgt _080485B0
	cmp r1, #0
	beq _080485B8
	b _08048740
_080485B0:
	cmp r1, #2
	bne _080485B6
	b _08048738
_080485B6:
	b _08048740
_080485B8:
	movs r0, #0x78
	strb r0, [r6, #0x12]
	strb r1, [r6, #0x13]
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	movs r2, #0xc0
	lsls r2, r2, #7
	adds r0, r0, r2
	ldr r5, [r6, #0x54]
	subs r0, r0, r5
	str r0, [r6, #0x5c]
	movs r1, #0x3c
	bl __divsi3
	str r0, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r0, [r0]
	ldr r3, _080486A4 @ =0xFFFFD800
	adds r0, r0, r3
	ldr r4, [r6, #0x58]
	subs r0, r0, r4
	str r0, [r6, #0x60]
	movs r1, #0x32
	bl __divsi3
	str r0, [r6, #0x60]
	str r5, [r6, #0x64]
	str r4, [r6, #0x68]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080485FA:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804860C
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0804860C:
	ldrb r0, [r6, #0x10]
	adds r7, r0, #0
	ldr r4, [r6, #0x64]
	ldr r5, [r6, #0x68]
	cmp r7, #1
	bne _0804863C
	ldr r1, [r6, #0x28]
	ldr r0, [r1, #0x64]
	ldr r2, _080486A8 @ =0xFFFFF000
	adds r0, r0, r2
	subs r0, r0, r4
	str r0, [r6, #0x5c]
	cmp r0, #0
	bge _0804862A
	adds r0, #0xf
_0804862A:
	asrs r0, r0, #4
	str r0, [r6, #0x5c]
	ldr r0, [r1, #0x68]
	subs r0, r0, r5
	str r0, [r6, #0x60]
	movs r1, #0x1e
	bl __divsi3
	str r0, [r6, #0x60]
_0804863C:
	ldr r0, [r6, #0x5c]
	adds r0, r4, r0
	str r0, [r6, #0x64]
	ldr r1, [r6, #0x60]
	adds r1, #1
	str r1, [r6, #0x60]
	adds r1, r5, r1
	str r1, [r6, #0x68]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
	lsls r0, r7, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _08048664
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	bne _08048676
_08048664:
	cmp r2, #1
	bne _080486B0
	mov r3, r8
	ldr r0, [r3, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080486B0
_08048676:
	ldr r2, _080486AC @ =gSineTable
	ldrb r0, [r6, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r1, r1, #1
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x13]
	lsls r0, r0, #0x19
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r1, r1, #1
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x13]
	adds r0, #0x20
	b _080486B2
	.align 2, 0
_080486A4: .4byte 0xFFFFD800
_080486A8: .4byte 0xFFFFF000
_080486AC: .4byte gSineTable
_080486B0:
	movs r0, #0
_080486B2:
	strb r0, [r6, #0x13]
	adds r4, r6, #0
	adds r4, #0xc4
	ldrb r1, [r6, #0x10]
	lsls r1, r1, #2
	subs r1, #2
	ldrh r0, [r4]
	subs r0, r0, r1
	strh r0, [r4]
	ldrh r0, [r4]
	ldr r1, _08048724 @ =0x000001FF
	ands r0, r1
	strh r0, [r4]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrh r0, [r4]
	adds r1, r6, #0
	adds r1, #0xd1
	ldrb r2, [r1]
	lsls r1, r2, #2
	adds r1, r1, r2
	lsls r1, r1, #1
	adds r1, #7
	bl __modsi3
	cmp r0, #0
	bne _08048740
	ldr r5, _08048728 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _0804872C @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08048730 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08048734 @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	movs r2, #0
	movs r3, #0
	bl FUN_080bc540
	b _08048740
	.align 2, 0
_08048724: .4byte 0x000001FF
_08048728: .4byte RNG_0202f388
_0804872C: .4byte 0x000343FD
_08048730: .4byte 0x00269EC3
_08048734: .4byte 0xFFFFFC00
_08048738:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
_08048740:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
