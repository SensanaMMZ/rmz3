	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Solid43_Die
Solid43_Die: @ 0x080DE13C
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #0
	bne _080DE18A
	ldr r5, _080DE1DC @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _080DE1E0 @ =0x000343FD
	muls r0, r4, r0
	ldr r3, _080DE1E4 @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r2, r0, #1
	lsls r0, r0, #4
	lsrs r0, r0, #0x15
	ldr r1, [r6, #0x54]
	adds r1, r1, r0
	str r1, [sp]
	adds r0, r2, #0
	muls r0, r4, r0
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r5]
	lsls r0, r0, #3
	lsrs r0, r0, #0x14
	ldr r1, [r6, #0x58]
	adds r1, r1, r0
	ldr r0, _080DE1E8 @ =0xFFFFF800
	adds r1, r1, r0
	str r1, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080DE18A:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, [r6, #0x60]
	ldr r0, _080DE1EC @ =0x000006FF
	cmp r1, r0
	bgt _080DE19E
	adds r0, r1, #0
	adds r0, #0x20
	str r0, [r6, #0x60]
_080DE19E:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	str r0, [r6, #0x68]
	ldr r0, _080DE1F0 @ =gStageRun+232
	adds r1, r6, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	bls _080DE1D4
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080DE1F4 @ =gSolidFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r6, #0x14]
_080DE1D4:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DE1DC: .4byte RNG_0202f388
_080DE1E0: .4byte 0x000343FD
_080DE1E4: .4byte 0x00269EC3
_080DE1E8: .4byte 0xFFFFF800
_080DE1EC: .4byte 0x000006FF
_080DE1F0: .4byte gStageRun+232
_080DE1F4: .4byte gSolidFnTable
