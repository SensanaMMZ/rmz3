	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0808778c
FUN_0808778c: @ 0x0808778C
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0808779C
	cmp r5, #1
	beq _080877CC
	b _080878E4
_0808779C:
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
	ldr r2, [r4, #0x58]
	movs r0, #0xc0
	lsls r0, r0, #4
	adds r2, r2, r0
	ldrb r1, [r4, #0x12]
	lsrs r1, r1, #1
	movs r3, #1
	ands r1, r3
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xb
	subs r2, r2, r0
	str r2, [r4, #0x68]
	str r5, [r4, #0x5c]
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	eors r0, r3
	ands r0, r3
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080877CC:
	ldr r5, [r4, #0x64]
	str r5, [r4, #0x54]
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	adds r6, r1, #0
	cmp r0, #0
	bne _080877FC
	ldr r2, _080877F8 @ =gSineTable
	ldr r3, [r4, #0x5c]
	asrs r0, r3, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r7, #0
	ldrsh r1, [r0, r7]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r5, r0
	b _08087814
	.align 2, 0
_080877F8: .4byte gSineTable
_080877FC:
	ldr r2, _08087840 @ =gSineTable
	ldr r3, [r4, #0x5c]
	asrs r0, r3, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r7, #0
	ldrsh r1, [r0, r7]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r5, r0
_08087814:
	str r0, [r4, #0x54]
	ldr r5, [r4, #0x68]
	str r5, [r4, #0x58]
	lsls r0, r6, #0x18
	lsrs r0, r0, #0x19
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	bne _08087844
	asrs r0, r3, #8
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r5, r0
	b _0808785A
	.align 2, 0
_08087840: .4byte gSineTable
_08087844:
	asrs r0, r3, #8
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r7, #0
	ldrsh r1, [r0, r7]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r5, r0
_0808785A:
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x5c]
	movs r1, #0xc0
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r1, _08087880 @ =0x00007FFF
	cmp r0, r1
	ble _08087874
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08087874:
	ldr r1, [r4, #0x5c]
	ldr r0, _08087884 @ =0x000029FF
	cmp r1, r0
	bgt _0808788C
	ldr r1, _08087888 @ =0x00006704
	b _08087894
	.align 2, 0
_08087880: .4byte 0x00007FFF
_08087884: .4byte 0x000029FF
_08087888: .4byte 0x00006704
_0808788C:
	ldr r0, _0808789C @ =0x000053FF
	cmp r1, r0
	bgt _080878A4
	ldr r1, _080878A0 @ =0x00006705
_08087894:
	adds r0, r4, #0
	bl SetMotion
	b _080878DE
	.align 2, 0
_0808789C: .4byte 0x000053FF
_080878A0: .4byte 0x00006705
_080878A4:
	ldrb r2, [r4, #0x13]
	cmp r2, #0
	beq _080878B2
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080878B8
_080878B2:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080878B8:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _080878EC @ =0x00006704
	adds r0, r4, #0
	bl SetMotion
_080878DE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080878E4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080878EC: .4byte 0x00006704

