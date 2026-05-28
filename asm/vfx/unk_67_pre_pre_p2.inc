	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Ghost67_Init
Ghost67_Init: @ 0x080C4978
	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r3, #0
	adds r2, r0, #0
	orrs r2, r1
	movs r0, #2
	orrs r2, r0
	orrs r2, r3
	strb r2, [r4, #0xa]
	ldrb r1, [r4, #0x10]
	cmp r1, #0
	bne _080C49B4
	movs r0, #0xef
	ands r2, r0
	strb r2, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080C49D4
_080C49B4:
	movs r1, #1
	movs r0, #0x10
	orrs r2, r0
	strb r2, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_080C49D4:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080C49E0
	movs r0, #0xc0
	rsbs r0, r0, #0
	b _080C49E2
_080C49E0:
	movs r0, #0xc0
_080C49E2:
	str r0, [r4, #0x5c]
	movs r0, #0
	str r0, [r4, #0x60]
	ldrb r3, [r4, #0x11]
	cmp r3, #0
	bne _080C4A22
	ldr r2, _080C4A30 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080C4A34 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080C4A38 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #7
	ands r0, r1
	adds r0, #0x7f
	strb r0, [r4, #0x12]
	ldr r1, _080C4A3C @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r3, [r4, #0xd]
	strb r3, [r4, #0xe]
	strb r3, [r4, #0xf]
_080C4A22:
	adds r0, r4, #0
	bl Ghost67_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C4A30: .4byte RNG_0202f388
_080C4A34: .4byte 0x000343FD
_080C4A38: .4byte 0x00269EC3
_080C4A3C: .4byte gVFXFnTable
