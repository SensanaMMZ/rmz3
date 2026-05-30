	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080dc898
FUN_080dc898: @ 0x080DC898
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080DC8CC
	adds r0, r4, #0
	bl CreateSolid37
	ldr r2, _080DC8DC @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DC8E0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080DC8E4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	adds r0, #8
	strb r0, [r4, #0x13]
_080DC8CC:
	ldrb r0, [r4, #0x12]
	cmp r0, #0x1e
	bls _080DC8D6
	movs r0, #0
	strb r0, [r4, #0x12]
_080DC8D6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080DC8DC: .4byte RNG_0202f388
_080DC8E0: .4byte 0x000343FD
_080DC8E4: .4byte 0x00269EC3
