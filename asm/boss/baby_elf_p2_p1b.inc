	.include "asm/macros.inc"

	.syntax unified

	.text

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
