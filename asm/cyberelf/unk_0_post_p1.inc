	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e1ef8
FUN_080e1ef8: @ 0x080E1EF8
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	adds r3, r4, #0
	adds r3, #0xc0
	ldrb r1, [r3]
	adds r2, r1, #1
	adds r0, r2, #0
	asrs r0, r0, #5
	lsls r0, r0, #5
	subs r0, r2, r0
	strb r0, [r3]
	adds r6, r4, #0
	adds r6, #0xb4
	ldr r1, [r6]
	ldr r0, [r4, #0x64]
	subs r3, r1, r0
	adds r5, r4, #0
	adds r5, #0xb8
	ldr r1, [r5]
	ldr r0, [r4, #0x68]
	subs r2, r1, r0
	movs r1, #0x80
	lsls r1, r1, #2
	adds r0, r3, r1
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bhi _080E1F5C
	movs r7, #0x80
	lsls r7, r7, #2
	adds r0, r2, r7
	cmp r0, r1
	bhi _080E1F5C
	adds r0, r3, #0
	muls r0, r3, r0
	adds r1, r2, #0
	muls r1, r2, r1
	adds r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #0xb
	cmp r0, r1
	bgt _080E1F5C
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	ldr r0, [r6]
	str r0, [r4, #0x64]
	ldr r0, [r5]
	str r0, [r4, #0x68]
	b _080E1FAE
_080E1F5C:
	adds r0, r3, #0
	adds r1, r2, #0
	bl CalcAngle
	ldr r3, _080E1FB4 @ =gSineTable
	adds r1, r0, #0
	adds r1, #0x40
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r3
	movs r5, #0
	ldrsh r2, [r1, r5]
	lsls r2, r2, #1
	ldr r1, [r4, #0x64]
	adds r1, r1, r2
	str r1, [r4, #0x64]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r7, #0
	ldrsh r1, [r0, r7]
	lsls r1, r1, #1
	ldr r0, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x68]
	adds r5, r4, #0
	adds r5, #0xc1
	ldrb r0, [r5]
	subs r0, #1
	strb r0, [r5]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080E1FAE
	adds r0, r4, #0
	adds r0, #0x54
	movs r1, #0
	bl FUN_080bfc94
	movs r0, #0x20
	strb r0, [r5]
_080E1FAE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E1FB4: .4byte gSineTable
