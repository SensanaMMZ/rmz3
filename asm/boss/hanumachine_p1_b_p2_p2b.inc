	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start hanu_0805bf60
hanu_0805bf60: @ 0x0805BF60
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805BFF4
	ldr r1, _0805BFC0 @ =0x0000B501
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805BFC4 @ =0x08364E68
	bl SetDDP
	movs r3, #0
	ldr r0, _0805BFC8 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805BF8C
	movs r3, #1
_0805BF8C:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805BF9E
	movs r3, #1
_0805BF9E:
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
	beq _0805BFCC
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805BFD2
	.align 2, 0
_0805BFC0: .4byte 0x0000B501
_0805BFC4: .4byte 0x08364E68
_0805BFC8: .4byte pZero2
_0805BFCC:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805BFD2:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805BFE4
	movs r0, #0xe0
	lsls r0, r0, #2
	b _0805BFE6
_0805BFE4:
	ldr r0, _0805C044 @ =0xFFFFFC80
_0805BFE6:
	str r0, [r4, #0x5c]
	movs r0, #0x4e
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805BFF4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	beq _0805C068
	ldr r0, [r4, #0x54]
	movs r5, #0x80
	lsls r5, r5, #5
	adds r0, r0, r5
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _0805C02E
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	adds r1, r4, #0
	adds r1, #0xbe
	movs r0, #1
	strb r0, [r1]
_0805C02E:
	ldr r1, [r4, #0x54]
	adds r2, r1, r5
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	adds r3, r1, #0
	cmp r2, r0
	ble _0805C048
	movs r1, #0
	movs r0, #5
	b _0805C05A
	.align 2, 0
_0805C044: .4byte 0xFFFFFC80
_0805C048:
	ldr r2, _0805C060 @ =0xFFFFE000
	adds r1, r3, r2
	ldr r0, _0805C064 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	ble _0805C0C4
	movs r1, #0
	movs r0, #3
_0805C05A:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0805C0CA
	.align 2, 0
_0805C060: .4byte 0xFFFFE000
_0805C064: .4byte pZero2
_0805C068:
	ldr r0, [r4, #0x54]
	ldr r1, _0805C0A4 @ =0xFFFFF000
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805C08E
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	adds r1, r4, #0
	adds r1, #0xbe
	movs r0, #1
	strb r0, [r1]
_0805C08E:
	ldr r1, [r4, #0x54]
	ldr r0, _0805C0A4 @ =0xFFFFF000
	adds r2, r1, r0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	adds r3, r1, #0
	cmp r2, r0
	bge _0805C0A8
	movs r0, #5
	b _0805C0BA
	.align 2, 0
_0805C0A4: .4byte 0xFFFFF000
_0805C0A8:
	movs r2, #0x80
	lsls r2, r2, #6
	adds r1, r3, r2
	ldr r0, _0805C0C0 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _0805C0C4
	movs r0, #3
_0805C0BA:
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _0805C0CA
	.align 2, 0
_0805C0C0: .4byte pZero2
_0805C0C4:
	ldr r0, [r4, #0x5c]
	adds r0, r3, r0
	str r0, [r4, #0x54]
_0805C0CA:
	pop {r4, r5}
	pop {r0}
	bx r0
