	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08087518
FUN_08087518: @ 0x08087518
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08087528
	cmp r0, #1
	beq _08087598
	b _080875BA
_08087528:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xe
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808754C @ =0x08368708
	bl SetDDP
	ldrb r0, [r4, #0x12]
	movs r3, #1
	ands r3, r0
	cmp r3, #0
	beq _08087550
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08087556
	.align 2, 0
_0808754C: .4byte 0x08368708
_08087550:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08087556:
	strb r0, [r4, #0xa]
	movs r1, #1
	adds r2, r1, #0
	ands r2, r3
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r2, #4
	ldrb r3, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r2
	mov r2, ip
	strb r0, [r2]
	ldrb r0, [r4, #0x12]
	ands r1, r0
	lsls r1, r1, #0xb
	ldr r0, _080875C0 @ =0xFFFFFC00
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	movs r0, #0xa
	strb r0, [r4, #0x13]
	ldr r1, _080875C4 @ =0x00006703
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08087598:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080875BA
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080875BA:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080875C0: .4byte 0xFFFFFC00
_080875C4: .4byte 0x00006703

