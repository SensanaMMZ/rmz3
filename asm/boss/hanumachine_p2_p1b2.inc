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
