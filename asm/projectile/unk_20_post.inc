	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a5148
FUN_080a5148: @ 0x080A5148
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080A5158
	cmp r5, #1
	beq _080A5180
	b _080A51A8
_080A5158:
	adds r0, r4, #0
	adds r0, #0xb4
	str r5, [r0]
	adds r1, r4, #0
	adds r1, #0xb8
	movs r0, #0x80
	lsls r0, r0, #6
	str r0, [r1]
	subs r1, #0x93
	movs r0, #0x19
	strb r0, [r1]
	movs r1, #0x92
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5180:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #0x80
	lsls r2, r2, #1
	adds r1, r1, r2
	str r1, [r0]
	ldr r0, _080A51B0 @ =0x00003FFF
	cmp r1, r0
	ble _080A519C
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A519C:
	adds r0, r4, #0
	bl FUN_080a4fa4
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A51A8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A51B0: .4byte 0x00003FFF

	thumb_func_start FUN_080a51b4
FUN_080a51b4: @ 0x080A51B4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A51C6
	cmp r0, #1
	beq _080A5222
	b _080A5288
_080A51C6:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A51EC @ =0x0836BAD0
	bl SetDDP
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080A51F0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080A51F6
	.align 2, 0
_080A51EC: .4byte 0x0836BAD0
_080A51F0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A51F6:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r1, #0x92
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5222:
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r0, r2
	str r0, [r1]
	adds r0, r4, #0
	bl FUN_080a4fa4
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x17
	strb r0, [r1]
	adds r2, r5, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080A5258
	strb r1, [r4, #0xd]
	strb r3, [r4, #0xe]
_080A5258:
	ldr r0, [r2]
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _080A5268
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r3, [r4, #0xe]
_080A5268:
	ldr r0, [r2]
	movs r1, #0x20
	ands r0, r1
	cmp r0, #0
	beq _080A5278
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r3, [r4, #0xe]
_080A5278:
	ldr r0, [r2]
	movs r1, #0x80
	ands r0, r1
	cmp r0, #0
	beq _080A5288
	movs r0, #9
	strb r0, [r4, #0xd]
	strb r3, [r4, #0xe]
_080A5288:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080a5290
FUN_080a5290:
	.byte 0xF0, 0xB5, 0x47, 0x46, 0x80, 0xB4, 0x07, 0x1C, 0xBD, 0x6A, 0xB8, 0x7B, 0x01, 0x28, 0x3F, 0xD0
	.byte 0x01, 0x28, 0x02, 0xDC, 0x00, 0x28, 0x06, 0xD0, 0x96, 0xE0, 0x02, 0x28, 0x62, 0xD0, 0x03, 0x28
	.byte 0x00, 0xD1, 0x84, 0xE0, 0x90, 0xE0, 0x38, 0x1C, 0x74, 0x30, 0x0A, 0x49, 0x61, 0xF7, 0xAA, 0xFF
	.byte 0x39, 0x1C, 0x25, 0x31, 0x17, 0x20, 0x08, 0x70, 0x38, 0x1C, 0x72, 0xF7, 0x61, 0xF8, 0xA8, 0x7A
	.byte 0x02, 0x09, 0x01, 0x20, 0x02, 0x40, 0x00, 0x2A, 0x06, 0xD0, 0xB8, 0x7A, 0x10, 0x21, 0x08, 0x43
	.byte 0x05, 0xE0, 0x00, 0x00, 0xB8, 0xBA, 0x36, 0x08, 0xB9, 0x7A, 0xEF, 0x20, 0x08, 0x40, 0xB8, 0x72
	.byte 0x11, 0x1C, 0x38, 0x1C, 0x4C, 0x30, 0x00, 0x24, 0x01, 0x70, 0x3B, 0x1C, 0x4A, 0x33, 0x09, 0x01
	.byte 0x1A, 0x78, 0x11, 0x20, 0x40, 0x42, 0x10, 0x40, 0x08, 0x43, 0x18, 0x70, 0x18, 0x49, 0x38, 0x1C
	.byte 0x72, 0xF7, 0x2A, 0xF9, 0xBC, 0x74, 0x10, 0x20, 0xF8, 0x74, 0xB8, 0x7B, 0x01, 0x30, 0xB8, 0x73
	.byte 0xF8, 0x7C, 0x01, 0x38, 0xF8, 0x74, 0x00, 0x06, 0x00, 0x28, 0x02, 0xD1, 0xB8, 0x7B, 0x01, 0x30
	.byte 0xB8, 0x73, 0x68, 0x6D, 0x7C, 0x6D, 0x06, 0x1B, 0xA8, 0x6D, 0xB9, 0x6D, 0x88, 0x46, 0x45, 0x1A
	.byte 0x30, 0x02, 0xE0, 0x26, 0x76, 0x00, 0x31, 0x1C, 0x59, 0xF0, 0xEA, 0xF9, 0x24, 0x18, 0x7C, 0x65
	.byte 0x28, 0x02, 0x31, 0x1C, 0x59, 0xF0, 0xE4, 0xF9, 0x40, 0x44, 0xB8, 0x65, 0xB8, 0x7C, 0x10, 0x30
	.byte 0xB8, 0x74, 0x39, 0x1C, 0x24, 0x31, 0x08, 0x70, 0x38, 0x1C, 0x72, 0xF7, 0x77, 0xF9, 0x33, 0xE0
	.byte 0x01, 0x49, 0x00, 0x00, 0x1B, 0x48, 0x00, 0x68, 0x40, 0x6D, 0x79, 0x6D, 0x46, 0x1A, 0xB9, 0x6D
	.byte 0x64, 0xF7, 0xF4, 0xFD, 0xB9, 0x6D, 0x45, 0x1A, 0x30, 0x02, 0x00, 0x14, 0x29, 0x02, 0x09, 0x14
	.byte 0x59, 0xF0, 0xD0, 0xF8, 0x00, 0x04, 0x00, 0x0E, 0x02, 0x1C, 0x40, 0x32, 0xBA, 0x74, 0xB9, 0x7A
	.byte 0x10, 0x20, 0x08, 0x40, 0x00, 0x28, 0x01, 0xD0, 0x50, 0x42, 0xB8, 0x74, 0xB9, 0x7C, 0x38, 0x1C
	.byte 0x24, 0x30, 0x01, 0x70, 0x14, 0x20, 0xF8, 0x74, 0xB8, 0x7B, 0x01, 0x30, 0xB8, 0x73, 0xF8, 0x7C
	.byte 0x01, 0x38, 0xF8, 0x74, 0x00, 0x06, 0x01, 0x0E, 0x00, 0x29, 0x02, 0xD1, 0x03, 0x20, 0x78, 0x73
	.byte 0xB9, 0x73, 0x38, 0x1C, 0x72, 0xF7, 0x42, 0xF9, 0x08, 0xBC, 0x98, 0x46, 0xF0, 0xBC, 0x01, 0xBC
	.byte 0x00, 0x47, 0x00, 0x00, 0x40, 0xF3, 0x02, 0x02

	thumb_func_start FUN_080a53e8
FUN_080a53e8: @ 0x080A53E8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080A547A
	cmp r0, #1
	bgt _080A53FE
	cmp r0, #0
	beq _080A5408
	b _080A54F0
_080A53FE:
	cmp r0, #2
	beq _080A54C0
	cmp r0, #3
	beq _080A54CA
	b _080A54F0
_080A5408:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A54B4 @ =0x0836BAB8
	bl SetDDP
	ldr r1, _080A54B8 @ =0x00004901
	adds r0, r4, #0
	bl SetMotion
	ldrb r2, [r4, #0x12]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A542C
	rsbs r0, r2, #0
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
_080A542C:
	adds r0, r2, #0
	subs r0, #0x40
	lsls r0, r0, #0x18
	ldr r3, _080A54BC @ =gSineTable
	lsrs r2, r0, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x17
	adds r0, r0, r1
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r5, #0
	ldrsh r1, [r0, r5]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #6
	cmp r0, #0
	bge _080A5454
	adds r0, #0xff
_080A5454:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	lsls r0, r2, #1
	adds r0, r0, r3
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #6
	cmp r0, #0
	bge _080A5470
	adds r0, #0xff
_080A5470:
	asrs r0, r0, #8
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A547A:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	movs r5, #0x80
	lsls r5, r5, #5
	adds r1, r1, r5
	bl PushoutToUp1
	cmp r0, #0
	bge _080A549E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A549E:
	ldrb r0, [r4, #0x12]
	adds r0, #0x10
	strb r0, [r4, #0x12]
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080A54F0
	.align 2, 0
_080A54B4: .4byte 0x0836BAB8
_080A54B8: .4byte 0x00004901
_080A54BC: .4byte gSineTable
_080A54C0:
	movs r0, #0x3c
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A54CA:
	ldrb r0, [r4, #0x12]
	adds r0, #0x10
	strb r0, [r4, #0x12]
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0xc0
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _080A54F0
	strb r1, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_080A54F0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080a54f8
FUN_080a54f8:
	.byte 0x70, 0xB5, 0x04, 0x1C, 0xA5, 0x6A, 0xA0, 0x7B
	.byte 0x01, 0x28, 0x69, 0xD0, 0x01, 0x28, 0x02, 0xDC, 0x00, 0x28, 0x07, 0xD0, 0xC3, 0xE0, 0x02, 0x28
	.byte 0x00, 0xD1, 0x81, 0xE0, 0x03, 0x28, 0x00, 0xD1, 0x99, 0xE0, 0xBC, 0xE0, 0x20, 0x1C, 0x74, 0x30
	.byte 0x16, 0x49, 0x61, 0xF7, 0x77, 0xFE, 0x28, 0x1C, 0xC0, 0x30, 0x00, 0x68, 0x10, 0x26, 0x30, 0x40
	.byte 0x00, 0x28, 0x27, 0xD0, 0xA3, 0x6D, 0xA8, 0x6D, 0x1B, 0x1A, 0x18, 0x1C, 0x00, 0x2B, 0x00, 0xDA
	.byte 0xD8, 0x1D, 0xC0, 0x10, 0x59, 0xF0, 0x02, 0xF8, 0x00, 0x04, 0x03, 0x0C, 0x18, 0x01, 0x40, 0x42
	.byte 0x20, 0x66, 0xA6, 0x66, 0xE3, 0x74, 0x6D, 0x6D, 0x09, 0x49, 0x68, 0x18, 0xE0, 0x65, 0x02, 0x1C
	.byte 0xA1, 0x7A, 0x30, 0x1C, 0x08, 0x40, 0x00, 0x28, 0x02, 0xD0, 0xC0, 0x20, 0x40, 0x01, 0x2A, 0x18
	.byte 0x60, 0x6D, 0x10, 0x1A, 0xE0, 0x65, 0x19, 0x1C, 0x28, 0xE0, 0x00, 0x00, 0xB8, 0xBA, 0x36, 0x08
	.byte 0x00, 0xE8, 0xFF, 0xFF, 0xA3, 0x6D, 0xA8, 0x6D, 0x1B, 0x1A, 0x18, 0x1C, 0x00, 0x2B, 0x00, 0xDA
	.byte 0xD8, 0x1D, 0xC0, 0x10, 0x58, 0xF0, 0xDA, 0xFF, 0x00, 0x04, 0x03, 0x0C, 0x18, 0x01, 0x40, 0x42
	.byte 0x20, 0x66, 0xA6, 0x66, 0xE3, 0x74, 0x28, 0x1C, 0xB8, 0x30, 0x02, 0x68, 0x19, 0x49, 0x50, 0x18
	.byte 0xE0, 0x65, 0x03, 0x1C, 0xA1, 0x7A, 0x30, 0x1C, 0x08, 0x40, 0x00, 0x28, 0x02, 0xD0, 0x98, 0x20
	.byte 0xC0, 0x01, 0x13, 0x18, 0x60, 0x6D, 0x18, 0x1A, 0xE0, 0x65, 0xE1, 0x7C, 0x59, 0xF0, 0xA8, 0xF8
	.byte 0xE0, 0x65, 0xA0, 0x7B, 0x01, 0x30, 0xA0, 0x73, 0xE0, 0x7C, 0x01, 0x38, 0xE0, 0x74, 0x00, 0x06
	.byte 0x00, 0x28, 0x02, 0xD1, 0xA0, 0x7B, 0x01, 0x30, 0xA0, 0x73, 0xA0, 0x7C, 0x10, 0x30, 0xA0, 0x74
	.byte 0x21, 0x1C, 0x24, 0x31, 0x08, 0x70, 0x60, 0x6D, 0xE1, 0x6D, 0x40, 0x18, 0x60, 0x65, 0xA0, 0x6D
	.byte 0x21, 0x6E, 0x40, 0x18, 0xA0, 0x65, 0xA0, 0x6E, 0x09, 0x18, 0x21, 0x66, 0x20, 0x1C, 0x72, 0xF7
	.byte 0x25, 0xF8, 0x40, 0xE0, 0x00, 0xB4, 0xFF, 0xFF, 0x21, 0x1C, 0xB8, 0x31, 0x00, 0x20, 0x08, 0x60
	.byte 0x04, 0x39, 0x80, 0x20, 0xC0, 0x01, 0x08, 0x60, 0xA0, 0x7C, 0x00, 0x02, 0x20, 0x66, 0x80, 0x21
	.byte 0x89, 0x02, 0x0B, 0x1A, 0x18, 0x1C, 0x00, 0x2B, 0x00, 0xDA, 0x3F, 0x30, 0x80, 0x11, 0x58, 0xF0
	.byte 0x85, 0xFF, 0x00, 0x04, 0x40, 0x0A, 0xE0, 0x65, 0xA0, 0x7B, 0x01, 0x30, 0xA0, 0x73, 0x20, 0x6E
	.byte 0xE1, 0x6D, 0x40, 0x18, 0x20, 0x66, 0x80, 0x39, 0xE1, 0x65, 0x00, 0x29, 0x0C, 0xDA, 0x00, 0x21
	.byte 0x21, 0x66, 0x01, 0x20, 0x60, 0x73, 0xA1, 0x73, 0x2A, 0x1C, 0xC0, 0x32, 0x10, 0x68, 0x05, 0x39
	.byte 0x08, 0x40, 0x0C, 0x39, 0x08, 0x40, 0x10, 0x60, 0x20, 0x6E, 0x00, 0x12, 0x21, 0x1C, 0x24, 0x31
	.byte 0x08, 0x70, 0x20, 0x1C, 0xFF, 0xF7, 0x8E, 0xFC, 0x21, 0x1C, 0x25, 0x31, 0x17, 0x20, 0x08, 0x70
	.byte 0x20, 0x1C, 0x71, 0xF7, 0xE3, 0xFF, 0x70, 0xBC, 0x01, 0xBC, 0x00, 0x47

	thumb_func_start FUN_080a569c
FUN_080a569c: @ 0x080A569C
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldr r5, [r7, #0x28]
	ldrb r0, [r7, #0xe]
	cmp r0, #1
	beq _080A5724
	cmp r0, #1
	bgt _080A56B2
	cmp r0, #0
	beq _080A56BC
	b _080A57A6
_080A56B2:
	cmp r0, #2
	beq _080A5764
	cmp r0, #3
	beq _080A5770
	b _080A57A6
_080A56BC:
	adds r0, r7, #0
	adds r0, #0x74
	ldr r1, _080A56E8 @ =0x0836BAD0
	bl SetDDP
	adds r1, r7, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	adds r0, r7, #0
	bl InitRotatableMotion
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080A56EC
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A56F2
	.align 2, 0
_080A56E8: .4byte 0x0836BAD0
_080A56EC:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A56F2:
	strb r0, [r7, #0xa]
	adds r1, r2, #0
	adds r0, r7, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _080A5760 @ =0x00004901
	adds r0, r7, #0
	bl SetMotion
	strb r4, [r7, #0x12]
	movs r0, #0x10
	strb r0, [r7, #0x13]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080A5724:
	ldrb r0, [r7, #0x13]
	subs r0, #1
	strb r0, [r7, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A5736
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080A5736:
	ldr r0, [r5, #0x54]
	ldr r4, [r7, #0x54]
	subs r0, r0, r4
	ldr r5, [r5, #0x58]
	ldr r6, [r7, #0x58]
	subs r5, r5, r6
	movs r1, #6
	bl __divsi3
	adds r4, r4, r0
	str r4, [r7, #0x54]
	adds r0, r5, #0
	movs r1, #6
	bl __divsi3
	adds r6, r6, r0
	str r6, [r7, #0x58]
	adds r0, r7, #0
	bl UpdateMotionGraphic
	b _080A57A6
	.align 2, 0
_080A5760: .4byte 0x00004901
_080A5764:
	movs r0, #0
	strb r0, [r7, #0x12]
	strb r0, [r7, #0x13]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080A5770:
	ldrb r0, [r7, #0x13]
	adds r0, #1
	strb r0, [r7, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x13
	bls _080A5786
	movs r0, #6
	strb r0, [r7, #0xd]
	movs r0, #0
	strb r0, [r7, #0xe]
_080A5786:
	ldrb r0, [r7, #0x13]
	cmp r0, #0x10
	bls _080A5792
	ldrb r0, [r7, #0x12]
	adds r0, #0x10
	b _080A5796
_080A5792:
	ldrb r1, [r7, #0x12]
	adds r0, r0, r1
_080A5796:
	strb r0, [r7, #0x12]
	ldrb r1, [r7, #0x12]
	adds r0, r7, #0
	adds r0, #0x24
	strb r1, [r0]
	adds r0, r7, #0
	bl UpdateMotionGraphic
_080A57A6:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start FUN_080a57ac
FUN_080a57ac: @ 0x080A57AC
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r7, [r5, #0x28]
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _080A57E2
	cmp r0, #1
	bgt _080A57C2
	cmp r0, #0
	beq _080A57CC
	b _080A5946
_080A57C2:
	cmp r0, #2
	beq _080A5870
	cmp r0, #3
	beq _080A588C
	b _080A5946
_080A57CC:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A5818 @ =0x0836BAB8
	bl SetDDP
	movs r0, #0xb0
	lsls r0, r0, #2
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A57E2:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _080A5820
	ldr r0, [r5, #0x54]
	ldr r1, _080A581C @ =0xFFFFF000
	adds r0, r0, r1
	movs r4, #0x80
	lsls r4, r4, #5
	adds r1, r2, r4
	bl PushoutToUp1
	adds r6, r0, #0
	ldr r0, [r5, #0x54]
	adds r0, r0, r4
	ldr r1, [r5, #0x58]
	adds r1, r1, r4
	bl PushoutToUp1
	adds r2, r0, #0
	cmp r6, #0
	bne _080A5850
	cmp r2, #0
	beq _080A5856
	b _080A5850
	.align 2, 0
_080A5818: .4byte 0x0836BAB8
_080A581C: .4byte 0xFFFFF000
_080A5820:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A583A
	ldr r0, [r5, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	adds r1, r2, r1
	bl PushoutToLeft1
	b _080A584A
_080A583A:
	ldr r0, [r5, #0x54]
	ldr r3, _080A586C @ =0xFFFFF000
	adds r0, r0, r3
	movs r3, #0x80
	lsls r3, r3, #5
	adds r1, r2, r3
	bl PushoutToRight1
_080A584A:
	adds r6, r0, #0
	cmp r6, #0
	bne _080A5856
_080A5850:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A5856:
	ldrb r0, [r5, #0x12]
	adds r0, #0x10
	strb r0, [r5, #0x12]
	adds r1, r5, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080A5946
	.align 2, 0
_080A586C: .4byte 0xFFFFF000
_080A5870:
	ldr r0, _080A58B8 @ =0xFFFFFD40
	str r0, [r5, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A5884
	movs r2, #0xb0
	lsls r2, r2, #2
_080A5884:
	str r2, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A588C:
	ldr r1, [r5, #0x54]
	ldr r0, [r5, #0x5c]
	adds r2, r1, r0
	str r2, [r5, #0x54]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A58C0
	movs r4, #0x80
	lsls r4, r4, #5
	adds r0, r2, r4
	ldr r1, [r5, #0x58]
	adds r1, r1, r4
	bl FUN_08009f6c
	adds r6, r0, #0
	ldr r0, [r5, #0x54]
	ldr r1, _080A58BC @ =0xFFFFF000
	adds r0, r0, r1
	b _080A58D6
	.align 2, 0
_080A58B8: .4byte 0xFFFFFD40
_080A58BC: .4byte 0xFFFFF000
_080A58C0:
	ldr r3, _080A58F0 @ =0xFFFFF000
	adds r0, r2, r3
	ldr r1, [r5, #0x58]
	movs r4, #0x80
	lsls r4, r4, #5
	adds r1, r1, r4
	bl FUN_08009f6c
	adds r6, r0, #0
	ldr r0, [r5, #0x54]
	adds r0, r0, r4
_080A58D6:
	ldr r1, [r5, #0x58]
	adds r1, r1, r4
	bl FUN_08009f6c
	adds r2, r0, #0
	ldr r0, [r5, #0x58]
	subs r3, r6, r0
	ldr r1, _080A58F4 @ =0xFFFFE800
	adds r4, r0, #0
	cmp r3, r1
	bge _080A58FC
	ldr r0, _080A58F8 @ =0xFFFFFD40
	b _080A590E
	.align 2, 0
_080A58F0: .4byte 0xFFFFF000
_080A58F4: .4byte 0xFFFFE800
_080A58F8: .4byte 0xFFFFFD40
_080A58FC:
	movs r1, #0xc0
	lsls r1, r1, #5
	cmp r3, r1
	ble _080A5916
	subs r0, r2, r4
	cmp r0, r1
	ble _080A5916
	movs r0, #0xb0
	lsls r0, r0, #2
_080A590E:
	str r0, [r5, #0x60]
	movs r0, #1
	strb r0, [r5, #0xe]
	b _080A5934
_080A5916:
	ldr r0, [r5, #0x54]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r1, r4, r2
	bl FUN_08009f6c
	adds r6, r0, #0
	ldr r0, [r5, #0x58]
	subs r0, r6, r0
	ldr r1, _080A5980 @ =0x000017FF
	cmp r0, r1
	bgt _080A5934
	ldr r3, _080A5984 @ =0xFFFFF000
	adds r0, r6, r3
	str r0, [r5, #0x58]
_080A5934:
	ldrb r0, [r5, #0x12]
	adds r0, #0x10
	strb r0, [r5, #0x12]
	adds r1, r5, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080A5946:
	adds r0, r7, #0
	adds r0, #0xb8
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	subs r2, r1, r0
	ldr r0, _080A5988 @ =0xFFFFA800
	cmp r2, r0
	bge _080A5960
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A5972
_080A5960:
	movs r0, #0xb0
	lsls r0, r0, #7
	cmp r2, r0
	ble _080A597A
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A597A
_080A5972:
	movs r1, #0
	movs r0, #4
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080A597A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A5980: .4byte 0x000017FF
_080A5984: .4byte 0xFFFFF000
_080A5988: .4byte 0xFFFFA800

	thumb_func_start FUN_080a598c
FUN_080a598c: @ 0x080A598C
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r4, [r5, #0x28]
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _080A5A10
	cmp r0, #1
	bgt _080A59A2
	cmp r0, #0
	beq _080A59A8
	b _080A5AB0
_080A59A2:
	cmp r0, #2
	beq _080A5A4C
	b _080A5AB0
_080A59A8:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A59CC @ =0x0836BAB8
	bl SetDDP
	adds r0, r5, #0
	bl InitRotatableMotion
	ldrb r0, [r4, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080A59D0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080A59D6
	.align 2, 0
_080A59CC: .4byte 0x0836BAB8
_080A59D0:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A59D6:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	movs r4, #0
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
	ldr r1, _080A5A48 @ =0x00004901
	adds r0, r5, #0
	bl SetMotion
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	strb r4, [r5, #0x12]
	strb r4, [r5, #0x13]
	str r4, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A5A10:
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	ldrb r1, [r5, #0x13]
	adds r1, r1, r0
	strb r1, [r5, #0x13]
	adds r0, r5, #0
	adds r0, #0x24
	strb r1, [r0]
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	ldr r1, [r5, #0x58]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	bl PushoutToUp1
	cmp r0, #0
	bge _080A5AB0
	adds r0, r5, #0
	bl FUN_080a4f3c
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080A5AB0
	.align 2, 0
_080A5A48: .4byte 0x00004901
_080A5A4C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A5AB8 @ =0x0836BAA0
	bl SetDDP
	ldrb r1, [r5, #0xa]
	movs r3, #0xfe
	adds r0, r3, #0
	ands r0, r1
	movs r2, #0
	strb r0, [r5, #0xa]
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	movs r1, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080A5A76
	movs r0, #8
	strb r0, [r5, #0xd]
	strb r2, [r5, #0xe]
_080A5A76:
	ldrb r0, [r4, #0xc]
	cmp r0, #1
	bls _080A5AB0
	ldrb r1, [r5, #0xa]
	adds r0, r3, #0
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080A5ABC @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_080A5AB0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A5AB8: .4byte 0x0836BAA0
_080A5ABC: .4byte gProjectileFnTable

	thumb_func_start FUN_080a5ac0
FUN_080a5ac0: @ 0x080A5AC0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A5AD0
	cmp r0, #1
	beq _080A5AEE
	b _080A5B1C
_080A5AD0:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A5B24 @ =0x0836BAB8
	bl SetDDP
	adds r0, r4, #0
	bl FUN_080a4f3c
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5AEE:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	subs r1, #0x40
	str r1, [r4, #0x60]
	ldrb r1, [r4, #0x13]
	ldrb r0, [r4, #0x12]
	subs r1, r1, r0
	strb r1, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080A5B14
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A5B14:
	ldrb r1, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0x24
	strb r1, [r0]
_080A5B1C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A5B24: .4byte 0x0836BAB8

	thumb_func_start FUN_080a5b28
FUN_080a5b28: @ 0x080A5B28
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A5B3A
	cmp r0, #1
	beq _080A5B62
	b _080A5BA8
_080A5B3A:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A5BB0 @ =0x0836BAD0
	bl SetDDP
	movs r0, #0x80
	lsls r0, r0, #3
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xb
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0xb4
	movs r0, #0x80
	lsls r0, r0, #7
	str r0, [r1]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5B62:
	adds r3, r4, #0
	adds r3, #0xb4
	ldr r0, [r3]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r3]
	movs r1, #0xc0
	lsls r1, r1, #0xa
	cmp r0, r1
	ble _080A5B7C
	ldr r0, [r4, #0x5c]
	subs r0, #0x20
	str r0, [r4, #0x5c]
_080A5B7C:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bgt _080A5B9C
	adds r2, r5, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #0x81
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #7
	str r0, [r3]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_080A5B9C:
	adds r0, r4, #0
	bl FUN_080a4fa4
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A5BA8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A5BB0: .4byte 0x0836BAD0

