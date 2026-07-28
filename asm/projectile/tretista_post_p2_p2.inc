	.include "asm/macros.inc"

	.syntax unified

	.text

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

