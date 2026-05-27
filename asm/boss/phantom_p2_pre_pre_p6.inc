	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805ff7c
FUN_0805ff7c: @ 0x0805FF7C
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805FFAC @ =sCollisions
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	ldr r0, _0805FFB0 @ =0xFFFFFA40
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_080608c8
	adds r1, r4, #0
	adds r1, #0xc4
	movs r0, #2
	str r0, [r1]
	adds r0, r4, #0
	bl FUN_0805ffb4
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805FFAC: .4byte sCollisions
_0805FFB0: .4byte 0xFFFFFA40

	thumb_func_start FUN_0805ffb4
FUN_0805ffb4: @ 0x0805FFB4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	beq _0805FFCE
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0805FFD4
_0805FFCE:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0805FFD4:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805FFE6
	movs r0, #2
	strb r0, [r4, #0xf]
_0805FFE6:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805ffec
FUN_0805ffec: @ 0x0805FFEC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	beq _08060006
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0806000C
_08060006:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0806000C:
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl FUN_08060924
	ldr r0, [r5, #0x60]
	cmp r0, #0
	ble _08060038
	adds r1, r5, #0
	adds r1, #0xc4
	movs r0, #1
	str r0, [r1]
	ldrb r1, [r5, #0xa]
	movs r4, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	movs r1, #8
	bl FUN_080607a0
	strb r4, [r5, #0x12]
	movs r0, #3
	strb r0, [r5, #0xf]
_08060038:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08060040
FUN_08060040: @ 0x08060040
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bne _080600A4
	ldr r3, [r5, #0x54]
	str r3, [sp]
	ldr r2, [r5, #0x58]
	str r2, [sp, #4]
	ldr r0, _08060088 @ =pZero2
	ldr r1, [r0]
	ldr r0, [r1, #0x54]
	ldr r1, [r1, #0x58]
	subs r0, r0, r3
	subs r1, r1, r2
	ldr r2, _0806008C @ =0xFFFFE800
	adds r1, r1, r2
	lsls r0, r0, #8
	asrs r0, r0, #0x10
	lsls r1, r1, #8
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x18
	cmp r4, #0x80
	bls _08060092
	cmp r4, #0xc0
	bls _08060090
	movs r4, #0
	b _08060092
	.align 2, 0
_08060088: .4byte pZero2
_0806008C: .4byte 0xFFFFE800
_08060090:
	movs r4, #0x80
_08060092:
	movs r0, #0xfc
	bl PlaySound
	movs r1, #0xe0
	lsls r1, r1, #2
	mov r0, sp
	adds r2, r4, #0
	bl FUN_080afcec
_080600A4:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080600BE
	adds r0, r5, #0
	movs r1, #3
	movs r2, #2
	movs r3, #1
	bl FUN_080607bc
	movs r0, #4
	strb r0, [r5, #0xf]
_080600BE:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080600c8
FUN_080600c8: @ 0x080600C8
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080600DA
	movs r0, #5
	strb r0, [r4, #0xf]
_080600DA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_080600e0
FUN_080600e0: @ 0x080600E0
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _080600F4
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_080600F4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
