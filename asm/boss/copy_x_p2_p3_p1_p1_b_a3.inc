	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start copyx_080565c0
copyx_080565c0: @ 0x080565C0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805664C
	ldr r1, _0805661C @ =0x0000B307
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	movs r3, #0
	ldr r0, _08056620 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _080565E6
	movs r3, #1
_080565E6:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _080565F8
	movs r3, #1
_080565F8:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _08056624
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805662A
	.align 2, 0
_0805661C: .4byte 0x0000B307
_08056620: .4byte pZero2
_08056624:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805662A:
	strb r0, [r4, #0xa]
	ldr r0, _0805668C @ =0xFFFFFF00
	str r0, [r4, #0x60]
	ldr r2, _08056690 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08056694 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08056698 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	ands r0, r1
	adds r0, #6
	strb r0, [r4, #0x12]
_0805664C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080566A8
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #0
	bne _080566A0
	ldr r0, _0805669C @ =gMission
	ldr r0, [r0]
	ldrb r0, [r0, #1]
	cmp r0, #4
	bls _080566A0
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	cmp r0, #0
	beq _080566A0
	movs r0, #0x26
	b _080566A2
	.align 2, 0
_0805668C: .4byte 0xFFFFFF00
_08056690: .4byte RNG_0202f388
_08056694: .4byte 0x000343FD
_08056698: .4byte 0x00269EC3
_0805669C: .4byte gMission
_080566A0:
	movs r0, #0x16
_080566A2:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_080566A8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
