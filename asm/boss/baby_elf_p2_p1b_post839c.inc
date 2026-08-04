	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08048548
FUN_08048548: @ 0x08048548
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	ldr r0, [r6, #0x28]
	mov r8, r0
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	bne _080485A0
	mov r1, r8
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _080485A0
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _0804859C @ =gBossFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _08048740
	.align 2, 0
_0804859C: .4byte gBossFnTable
_080485A0:
	ldrb r1, [r6, #0xe]
	cmp r1, #1
	beq _080485FA
	cmp r1, #1
	bgt _080485B0
	cmp r1, #0
	beq _080485B8
	b _08048740
_080485B0:
	cmp r1, #2
	bne _080485B6
	b _08048738
_080485B6:
	b _08048740
_080485B8:
	movs r0, #0x78
	strb r0, [r6, #0x12]
	strb r1, [r6, #0x13]
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	movs r2, #0xc0
	lsls r2, r2, #7
	adds r0, r0, r2
	ldr r5, [r6, #0x54]
	subs r0, r0, r5
	str r0, [r6, #0x5c]
	movs r1, #0x3c
	bl __divsi3
	str r0, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r0, [r0]
	ldr r3, _080486A4 @ =0xFFFFD800
	adds r0, r0, r3
	ldr r4, [r6, #0x58]
	subs r0, r0, r4
	str r0, [r6, #0x60]
	movs r1, #0x32
	bl __divsi3
	str r0, [r6, #0x60]
	str r5, [r6, #0x64]
	str r4, [r6, #0x68]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080485FA:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804860C
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0804860C:
	ldrb r0, [r6, #0x10]
	adds r7, r0, #0
	ldr r4, [r6, #0x64]
	ldr r5, [r6, #0x68]
	cmp r7, #1
	bne _0804863C
	ldr r1, [r6, #0x28]
	ldr r0, [r1, #0x64]
	ldr r2, _080486A8 @ =0xFFFFF000
	adds r0, r0, r2
	subs r0, r0, r4
	str r0, [r6, #0x5c]
	cmp r0, #0
	bge _0804862A
	adds r0, #0xf
_0804862A:
	asrs r0, r0, #4
	str r0, [r6, #0x5c]
	ldr r0, [r1, #0x68]
	subs r0, r0, r5
	str r0, [r6, #0x60]
	movs r1, #0x1e
	bl __divsi3
	str r0, [r6, #0x60]
_0804863C:
	ldr r0, [r6, #0x5c]
	adds r0, r4, r0
	str r0, [r6, #0x64]
	ldr r1, [r6, #0x60]
	adds r1, #1
	str r1, [r6, #0x60]
	adds r1, r5, r1
	str r1, [r6, #0x68]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
	lsls r0, r7, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _08048664
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	bne _08048676
_08048664:
	cmp r2, #1
	bne _080486B0
	mov r3, r8
	ldr r0, [r3, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080486B0
_08048676:
	ldr r2, _080486AC @ =gSineTable
	ldrb r0, [r6, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r1, r1, #1
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x13]
	lsls r0, r0, #0x19
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r1, r1, #1
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x13]
	adds r0, #0x20
	b _080486B2
	.align 2, 0
_080486A4: .4byte 0xFFFFD800
_080486A8: .4byte 0xFFFFF000
_080486AC: .4byte gSineTable
_080486B0:
	movs r0, #0
_080486B2:
	strb r0, [r6, #0x13]
	adds r4, r6, #0
	adds r4, #0xc4
	ldrb r1, [r6, #0x10]
	lsls r1, r1, #2
	subs r1, #2
	ldrh r0, [r4]
	subs r0, r0, r1
	strh r0, [r4]
	ldrh r0, [r4]
	ldr r1, _08048724 @ =0x000001FF
	ands r0, r1
	strh r0, [r4]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrh r0, [r4]
	adds r1, r6, #0
	adds r1, #0xd1
	ldrb r2, [r1]
	lsls r1, r2, #2
	adds r1, r1, r2
	lsls r1, r1, #1
	adds r1, #7
	bl __modsi3
	cmp r0, #0
	bne _08048740
	ldr r5, _08048728 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _0804872C @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08048730 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08048734 @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	movs r2, #0
	movs r3, #0
	bl FUN_080bc540
	b _08048740
	.align 2, 0
_08048724: .4byte 0x000001FF
_08048728: .4byte RNG_0202f388
_0804872C: .4byte 0x000343FD
_08048730: .4byte 0x00269EC3
_08048734: .4byte 0xFFFFFC00
_08048738:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
_08048740:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
