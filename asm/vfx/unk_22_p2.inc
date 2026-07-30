	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b7d4c
FUN_080b7d4c: @ 0x080B7D4C
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r6, r0, #0
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B7DE4
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	ldr r2, _080B7DCC @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080B7DD0 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r0, _080B7DD4 @ =0x00269EC3
	adds r4, r4, r0
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	ldrb r1, [r6, #0x10]
	ldr r2, _080B7DD8 @ =0x00001804
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080b7b8c
	ldrb r1, [r6, #0x10]
	ldr r5, _080B7DDC @ =0x00001805
	mov r0, sp
	adds r2, r5, #0
	adds r3, r4, #0
	bl FUN_080b7b8c
	ldrb r1, [r6, #0x10]
	mov r0, sp
	adds r2, r5, #0
	adds r3, r4, #0
	bl FUN_080b7b8c
	movs r0, #0x31
	bl PlaySound
	ldr r1, _080B7DE0 @ =gVFXFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
	b _080B7E2C
	.align 2, 0
_080B7DCC: .4byte RNG_0202f388
_080B7DD0: .4byte 0x000343FD
_080B7DD4: .4byte 0x00269EC3
_080B7DD8: .4byte 0x00001804
_080B7DDC: .4byte 0x00001805
_080B7DE0: .4byte gVFXFnTable
_080B7DE4:
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080B7DF0
	cmp r0, #1
	beq _080B7E06
	b _080B7E2C
_080B7DF0:
	movs r0, #0x32
	strb r0, [r6, #0x12]
	ldr r0, _080B7E34 @ =0xFFFFFF00
	str r0, [r6, #0x60]
	ldr r1, _080B7E38 @ =0x00001802
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080B7E06:
	ldr r0, [r6, #0x60]
	adds r0, #0x10
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080B7E16
	str r1, [r6, #0x60]
_080B7E16:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080B7E2C:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B7E34: .4byte 0xFFFFFF00
_080B7E38: .4byte 0x00001802
