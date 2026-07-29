	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start copyx_080578e0
copyx_080578e0: @ 0x080578E0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r4, r0, #0
	movs r3, #0
	movs r2, #0
	ldr r0, _08057960 @ =RNG_0202f388
	mov ip, r0
	adds r0, r4, #0
	adds r0, #0xdc
	ldrb r1, [r0]
	movs r6, #1
	adds r5, r0, #0
_080578F8:
	adds r0, r1, #0
	asrs r0, r2
	ands r0, r6
	cmp r0, #0
	beq _0805790A
	mov r7, sp
	adds r0, r7, r3
	strb r2, [r0]
	adds r3, #1
_0805790A:
	adds r2, #1
	cmp r2, #3
	ble _080578F8
	mov r0, ip
	ldr r1, [r0]
	ldr r0, _08057964 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08057968 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r2, ip
	str r1, [r2]
	lsrs r0, r0, #0x11
	adds r1, r3, #0
	bl __umodsi3
	movs r1, #5
	strb r1, [r4, #0xd]
	mov r7, sp
	adds r2, r7, r0
	ldrb r0, [r2]
	strb r0, [r4, #0xf]
	movs r4, #1
	adds r0, r4, #0
	ldrb r1, [r2]
	lsls r0, r1
	movs r3, #0xf
	eors r0, r3
	ldrb r1, [r5]
	ands r0, r1
	strb r0, [r5]
	cmp r0, #0
	bne _08057958
	adds r0, r4, #0
	ldrb r2, [r2]
	lsls r0, r2
	eors r0, r3
	strb r0, [r5]
_08057958:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08057960: .4byte RNG_0202f388
_08057964: .4byte 0x000343FD
_08057968: .4byte 0x00269EC3
