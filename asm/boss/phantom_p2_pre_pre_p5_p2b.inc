	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805feac
FUN_0805feac: @ 0x0805FEAC
	push {r4, lr}
	adds r4, r0, #0
	adds r1, r4, #0
	adds r1, #0xc4
	movs r0, #0
	str r0, [r1]
	ldrb r0, [r4, #0x12]
	adds r1, r0, #1
	movs r2, #0
	strb r1, [r4, #0x12]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x4f
	bhi _0805FED8
	movs r0, #3
	ands r1, r0
	cmp r1, #0
	bne _0805FEFC
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0805FF02
_0805FED8:
	cmp r0, #0x6f
	bhi _0805FEEC
	movs r0, #2
	ands r1, r0
	cmp r1, #0
	beq _0805FEFC
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0805FF02
_0805FEEC:
	movs r0, #3
	ands r1, r0
	cmp r1, #0
	beq _0805FEFC
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0805FF02
_0805FEFC:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0805FF02:
	strb r0, [r4, #0xa]
	ldr r1, _0805FF5C @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r0, r1
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	ldrb r0, [r4, #0x12]
	cmp r0, #0x80
	bne _0805FF54
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805FF60 @ =0x08365380
	bl SetDDP
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	adds r0, r4, #0
	movs r1, #0xf
	bl FUN_080607a0
	adds r1, r4, #0
	adds r1, #0xc4
	movs r0, #8
	str r0, [r1]
	movs r0, #2
	strh r0, [r4, #0xe]
	movs r0, #0
	strb r0, [r4, #0x12]
	movs r0, #0x10
	strb r0, [r4, #0x13]
_0805FF54:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805FF5C: .4byte gSineTable
_0805FF60: .4byte 0x08365380
