	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080615dc
FUN_080615dc: @ 0x080615DC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080615EC
	cmp r0, #1
	beq _0806161C
	b _08061642
_080615EC:
	movs r0, #0xa7
	bl ClearBlink
	movs r0, #0xa8
	bl ClearBlink
	movs r0, #0xa9
	bl ClearBlink
	movs r0, #0xaa
	bl ClearBlink
	movs r1, #0xb0
	lsls r1, r1, #2
	movs r0, #0xa7
	bl LoadBlink
	adds r0, r4, #0
	bl FUN_080616fc
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08061642
_0806161C:
	adds r0, r4, #0
	bl FUN_080616fc
	movs r0, #0xa7
	bl UpdateBlinkMotionState
	adds r0, r4, #0
	adds r0, #0xcc
	ldr r0, [r0]
	ldrb r0, [r0, #0xd]
	cmp r0, #7
	beq _08061642
	movs r0, #0xa7
	bl ClearBlink
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08061642:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_08061648
FUN_08061648: @ 0x08061648
	push {r4, r5, lr}
	adds r2, r0, #0
	adds r4, r1, #0
	adds r2, #0xa4
	movs r3, #0
	ldrsh r1, [r2, r3]
	cmp r1, #0x20
	bgt _0806167E
	movs r2, #0
	ldr r5, _08061670 @ =u16_ARRAY_080feffa
	adds r3, r5, #0
_0806165E:
	ldrh r1, [r3]
	cmp r1, r4
	beq _08061674
	adds r3, #2
	adds r2, #1
	cmp r2, #4
	ble _0806165E
	b _080616B0
	.align 2, 0
_08061670: .4byte u16_ARRAY_080feffa
_08061674:
	adds r0, r2, #1
	movs r1, #5
	bl __modsi3
	b _0806169A
_0806167E:
	movs r2, #0
	ldr r5, _080616A4 @ =u16_ARRAY_080feffa
	adds r3, r5, #0
_08061684:
	ldrh r1, [r3]
	cmp r1, r4
	bne _080616A8
	adds r1, r2, #1
	adds r0, r1, #0
	cmp r1, #0
	bge _08061694
	adds r0, r2, #4
_08061694:
	asrs r0, r0, #2
	lsls r0, r0, #2
	subs r0, r1, r0
_0806169A:
	lsls r0, r0, #1
	adds r0, r0, r5
	ldrh r0, [r0]
	b _080616B0
	.align 2, 0
_080616A4: .4byte u16_ARRAY_080feffa
_080616A8:
	adds r3, #2
	adds r2, #1
	cmp r2, #3
	ble _08061684
_080616B0:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_080616b8
FUN_080616b8: @ 0x080616B8
	push {lr}
	adds r3, r0, #0
	ldr r1, [r3, #0x2c]
	ldr r2, [r1, #0x2c]
	cmp r2, #0
	beq _080616D8
	ldrb r0, [r2, #0xc]
	cmp r0, #1
	bls _080616D0
	movs r0, #0
	str r0, [r1, #0x2c]
	b _080616D8
_080616D0:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
_080616D8:
	ldr r0, [r3, #0x2c]
	adds r1, r0, #0
	adds r1, #0xbc
	ldr r2, [r1]
	cmp r2, #0
	beq _080616F8
	ldrb r0, [r2, #0xc]
	cmp r0, #1
	bls _080616F0
	movs r0, #0
	str r0, [r1]
	b _080616F8
_080616F0:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
_080616F8:
	pop {r0}
	bx r0

	thumb_func_start FUN_080616fc
FUN_080616fc: @ 0x080616FC
	push {r4, lr}
	mov ip, r0
	mov r1, ip
	adds r1, #0xc0
	ldrh r0, [r1]
	adds r0, #1
	movs r2, #0xff
	ands r0, r2
	strh r0, [r1]
	ldr r1, _08061754 @ =gSineTable
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r3, #0
	ldrsh r0, [r0, r3]
	lsls r3, r0, #2
	mov r4, ip
	ldr r0, [r4, #0x68]
	adds r0, r0, r3
	str r0, [r4, #0x58]
	mov r3, ip
	adds r3, #0xc2
	ldrh r0, [r3]
	adds r0, #2
	ands r0, r2
	strh r0, [r3]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r3, r0, #3
	ldr r2, [r4, #0x64]
	adds r2, r2, r3
	str r2, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x60]
	str r2, [r4, #0x5c]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08061754: .4byte gSineTable
