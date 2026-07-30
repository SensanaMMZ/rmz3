	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c3108
FUN_080c3108: @ 0x080C3108
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080C3130
	ldr r1, _080C312C @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080C320C
	.align 2, 0
_080C312C: .4byte gVFXFnTable
_080C3130:
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080C313C
	cmp r5, #1
	beq _080C3178
	b _080C320C
_080C313C:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	ldr r1, _080C3198 @ =0x00006B03
	adds r0, r4, #0
	bl SetMotion
	str r5, [r4, #0x5c]
	str r5, [r4, #0x60]
	ldr r2, _080C319C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080C31A0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080C31A4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x7f
	ands r0, r1
	subs r0, #0x40
	str r0, [r4, #0x64]
	movs r0, #0x32
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080C3178:
	ldrb r0, [r4, #0x13]
	adds r1, r0, #1
	movs r5, #0
	strb r1, [r4, #0x13]
	ldrb r0, [r4, #0x12]
	cmp r0, #0x14
	bls _080C31A8
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	beq _080C31BE
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080C31C4
	.align 2, 0
_080C3198: .4byte 0x00006B03
_080C319C: .4byte RNG_0202f388
_080C31A0: .4byte 0x000343FD
_080C31A4: .4byte 0x00269EC3
_080C31A8:
	ldrb r0, [r4, #0x13]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080C31BE
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080C31C4
_080C31BE:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080C31C4:
	strb r0, [r4, #0xa]
	ldr r1, [r4, #0x64]
	cmp r1, #0
	ble _080C31D8
	ldr r0, [r4, #0x5c]
	adds r0, #8
	str r0, [r4, #0x5c]
	cmp r0, r1
	ble _080C31E6
	b _080C31E4
_080C31D8:
	ldr r0, [r4, #0x5c]
	subs r0, #8
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	cmp r0, r1
	bge _080C31E6
_080C31E4:
	str r1, [r4, #0x5c]
_080C31E6:
	ldr r0, [r4, #0x60]
	adds r0, #8
	str r0, [r4, #0x60]
	movs r1, #0x80
	lsls r1, r1, #1
	cmp r0, r1
	ble _080C31F6
	str r1, [r4, #0x60]
_080C31F6:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080C320C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
