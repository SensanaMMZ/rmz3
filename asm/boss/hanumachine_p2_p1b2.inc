	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start hanu_0805c98c
hanu_0805c98c: @ 0x0805C98C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0805C9C2
	bl InitRotatableMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r1, _0805CA3C @ =0x0000B50D
	adds r0, r4, #0
	bl SetMotion
	adds r1, r4, #0
	adds r1, #0x24
	movs r0, #0x60
	strb r0, [r1]
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	ldr r0, _0805CA40 @ =0xFFFFFC00
	str r0, [r4, #0x60]
	strb r5, [r4, #0xf]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C9C2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805CA58
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805C9F2
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010dd8
_0805C9F2:
	movs r0, #0x52
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #5
	bl AppendQuake
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805CA44
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805CA4A
	.align 2, 0
_0805CA3C: .4byte 0x0000B50D
_0805CA40: .4byte 0xFFFFFC00
_0805CA44:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805CA4A:
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	rsbs r1, r1, #0
	str r1, [r4, #0x5c]
_0805CA58:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805CAEA
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805CA82
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010dd8
_0805CA82:
	movs r0, #0x52
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #5
	bl AppendQuake
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #5
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4d
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #5
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #5
	ldrb r2, [r0]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805CACC
	ldrb r0, [r4, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _0805CAD2
_0805CACC:
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
_0805CAD2:
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	rsbs r1, r1, #0
	str r1, [r4, #0x60]
	cmp r1, #0
	bge _0805CAEA
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
_0805CAEA:
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	bls _0805CAF8
	movs r1, #0
	movs r0, #0x12
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805CAF8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805cb00
FUN_0805cb00: @ 0x0805CB00
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	bne _0805CBA6
	adds r0, #0x24
	strb r1, [r0]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	movs r1, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0805CB24
	movs r1, #1
_0805CB24:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r3, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0805CB34
	movs r3, #1
_0805CB34:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _0805CB56
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805CB5C
_0805CB56:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805CB5C:
	strb r0, [r4, #0xa]
	ldr r1, _0805CB8C @ =0x0000B50E
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805CB90 @ =0x08364EC8
	bl SetDDP
	ldr r0, _0805CB94 @ =0xFFFFFB80
	str r0, [r4, #0x60]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805CB98
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #5
	b _0805CB9E
	.align 2, 0
_0805CB8C: .4byte 0x0000B50E
_0805CB90: .4byte 0x08364EC8
_0805CB94: .4byte 0xFFFFFB80
_0805CB98:
	ldr r0, _0805CBF4 @ =0xFFFFFE00
	str r0, [r4, #0x5c]
	ldr r0, _0805CBF8 @ =0xFFFFF000
_0805CB9E:
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805CBA6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x64]
	adds r0, r4, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805CBC4
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805CBC4:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, #0x40
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805CBEE
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805CBEE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805CBF4: .4byte 0xFFFFFE00
_0805CBF8: .4byte 0xFFFFF000
