	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080dd4fc
FUN_080dd4fc: @ 0x080DD4FC
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, _080DD56C @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r6, #1
	str r6, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r2, _080DD570 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD574 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080DD578 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r5, r0, #0x11
	ands r5, r6
	cmp r5, #0
	beq _080DD580
	ldr r1, _080DD57C @ =0x0000D802
	adds r0, r4, #0
	bl SetMotion
	movs r2, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r6, [r4, #0x13]
	b _080DD5A8
	.align 2, 0
_080DD56C: .4byte gSolidFnTable
_080DD570: .4byte RNG_0202f388
_080DD574: .4byte 0x000343FD
_080DD578: .4byte 0x00269EC3
_080DD57C: .4byte 0x0000D802
_080DD580:
	ldr r1, _080DD5DC @ =0x0000D803
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	strb r5, [r4, #0xd]
	strb r5, [r4, #0x13]
_080DD5A8:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x1d
	strb r0, [r1]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r0, [r4, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r4, #0x58]
	str r0, [r1]
	adds r0, r4, #0
	bl Cat_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DD5DC: .4byte 0x0000D803
