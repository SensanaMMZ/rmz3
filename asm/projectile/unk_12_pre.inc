	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0809f64c
FUN_0809f64c: @ 0x0809F64C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0809F67E
	cmp r0, #1
	bgt _0809F660
	cmp r0, #0
	beq _0809F66C
	b _0809F7BE
_0809F660:
	cmp r0, #2
	beq _0809F6A0
	cmp r0, #3
	bne _0809F66A
	b _0809F780
_0809F66A:
	b _0809F7BE
_0809F66C:
	ldr r1, _0809F69C @ =0x0000A601
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x14
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809F67E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0809F696
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0809F696
	b _0809F7BE
_0809F696:
	movs r0, #0xa0
	strb r0, [r4, #0x12]
	b _0809F774
	.align 2, 0
_0809F69C: .4byte 0x0000A601
_0809F6A0:
	ldr r0, _0809F744 @ =pZero2
	ldr r1, [r0]
	ldr r2, [r1, #0x54]
	ldr r0, [r4, #0x54]
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, [r4, #0x58]
	movs r3, #0x80
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r1, [r1, #0x58]
	subs r1, r1, r0
	str r1, [r4, #0x60]
	asrs r2, r2, #2
	adds r0, r2, #0
	muls r0, r2, r0
	asrs r1, r1, #2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	adds r0, r0, r1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r5, r0, #0xe
	cmp r5, #0
	beq _0809F6EE
	ldr r0, [r4, #0x5c]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x60]
	lsls r0, r0, #8
	adds r1, r5, #0
	bl __divsi3
	str r0, [r4, #0x60]
_0809F6EE:
	ldr r0, [r4, #0x5c]
	lsls r2, r0, #1
	adds r2, r2, r0
	lsls r2, r2, #6
	asrs r2, r2, #8
	str r2, [r4, #0x64]
	ldr r0, [r4, #0x60]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #6
	asrs r1, r1, #8
	str r1, [r4, #0x68]
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	movs r3, #0
	strb r0, [r4, #0x12]
	movs r5, #0xff
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0809F730
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0809F748
_0809F730:
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	orrs r0, r5
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0x8c
	str r3, [r0]
	adds r0, #4
	b _0809F766
	.align 2, 0
_0809F744: .4byte pZero2
_0809F748:
	adds r2, r4, #0
	adds r2, #0x8c
	ldr r0, [r2]
	ldr r1, _0809F77C @ =0x00400100
	ands r0, r1
	cmp r0, #0
	beq _0809F7BE
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	orrs r0, r5
	strb r0, [r4, #0x13]
	str r3, [r2]
	adds r0, r4, #0
	adds r0, #0x90
_0809F766:
	str r3, [r0]
	adds r0, #4
	strb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
_0809F774:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0809F7BE
	.align 2, 0
_0809F77C: .4byte 0x00400100
_0809F780:
	ldrb r1, [r4, #0x13]
	rsbs r0, r1, #0
	asrs r0, r0, #4
	adds r1, r1, r0
	strb r1, [r4, #0x13]
	ldrb r1, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0x50
	strh r1, [r0]
	ldrb r0, [r4, #0x13]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809F7BE
	ldr r1, _0809F7C4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_0809F7BE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809F7C4: .4byte gProjectileFnTable
