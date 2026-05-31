	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a4f3c
FUN_080a4f3c: @ 0x080A4F3C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r7, _080A4F90 @ =RNG_0202f388
	movs r6, #3
_080A4F44:
	ldr r4, [r5, #0x54]
	ldr r0, _080A4F94 @ =0xFFFFF000
	adds r4, r4, r0
	ldr r1, [r7]
	ldr r0, _080A4F98 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080A4F9C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r7]
	lsls r0, r0, #2
	lsrs r0, r0, #0x13
	adds r4, r4, r0
	ldr r1, [r5, #0x58]
	adds r0, r4, #0
	bl FUN_08009f6c
	adds r2, r0, #0
	ldr r0, [r5, #0x58]
	subs r0, r2, r0
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, _080A4FA0 @ =0x00002FFF
	cmp r0, r1
	bhi _080A4F84
	adds r0, r4, #0
	adds r1, r2, #0
	movs r2, #1
	bl FUN_080bf438
_080A4F84:
	subs r6, #1
	cmp r6, #0
	bge _080A4F44
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A4F90: .4byte RNG_0202f388
_080A4F94: .4byte 0xFFFFF000
_080A4F98: .4byte 0x000343FD
_080A4F9C: .4byte 0x00269EC3
_080A4FA0: .4byte 0x00002FFF

	thumb_func_start FUN_080a4fa4
FUN_080a4fa4: @ 0x080A4FA4
	push {r4, r5, r6, r7, lr}
	adds r3, r0, #0
	ldr r5, [r3, #0x28]
	adds r0, #0xb4
	ldrh r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A4FBE
	rsbs r0, r4, #0
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
_080A4FBE:
	ldr r6, [r5, #0x54]
	str r6, [r3, #0x54]
	ldr r2, _080A4FF8 @ =gSineTable
	lsrs r0, r4, #8
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r7, #0
	ldrsh r1, [r0, r7]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xb
	rsbs r0, r0, #0
	adds r7, r2, #0
	lsrs r2, r4, #8
	cmp r0, #0
	bge _080A4FE0
	adds r0, #0xff
_080A4FE0:
	asrs r0, r0, #8
	adds r0, r6, r0
	str r0, [r3, #0x54]
	ldr r1, _080A4FFC @ =0xFFFFC000
	adds r0, r4, r1
	lsls r0, r0, #0x10
	cmp r0, #0
	blt _080A5000
	adds r1, r3, #0
	adds r1, #0x25
	movs r0, #0x17
	b _080A5006
	.align 2, 0
_080A4FF8: .4byte gSineTable
_080A4FFC: .4byte 0xFFFFC000
_080A5000:
	adds r1, r3, #0
	adds r1, #0x25
	movs r0, #0x19
_080A5006:
	strb r0, [r1]
	ldr r1, [r5, #0x58]
	str r1, [r3, #0x58]
	adds r0, r3, #0
	adds r0, #0xb8
	ldr r0, [r0]
	asrs r0, r0, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r7
	movs r4, #0
	ldrsh r0, [r0, r4]
	lsls r0, r0, #2
	adds r1, r1, r0
	str r1, [r3, #0x58]
	adds r0, r2, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r7
	movs r7, #0
	ldrsh r0, [r0, r7]
	lsls r0, r0, #0xa
	rsbs r0, r0, #0
	cmp r0, #0
	bge _080A503C
	adds r0, #0xff
_080A503C:
	asrs r0, r0, #8
	adds r0, r1, r0
	str r0, [r3, #0x58]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
