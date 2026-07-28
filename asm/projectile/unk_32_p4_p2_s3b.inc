	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080aba60
FUN_080aba60: @ 0x080ABA60
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0xd]
	cmp r1, #0
	bne _080ABAA6
	ldr r0, [r4, #0x5c]
	adds r0, #0x10
	str r0, [r4, #0x5c]
	movs r2, #0xa0
	lsls r2, r2, #2
	cmp r0, r2
	ble _080ABA80
	str r2, [r4, #0x5c]
_080ABA80:
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _080ABAE0
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	b _080ABAE0
_080ABAA6:
	ldrb r1, [r4, #0x12]
	movs r0, #3
	ands r0, r1
	adds r2, r1, #0
	cmp r0, #1
	bls _080ABABA
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _080ABAC0
_080ABABA:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
_080ABAC0:
	strb r0, [r4, #0xa]
	adds r0, r2, #1
	strb r0, [r4, #0x12]
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x10
	bls _080ABAE0
	ldr r1, _080ABAF4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080ABAE0:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080ABAF8
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	b _080ABAFE
	.align 2, 0
_080ABAF4: .4byte gProjectileFnTable
_080ABAF8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
_080ABAFE:
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080ABB20
	ldr r1, _080ABB28 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080ABB20:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080ABB28: .4byte gProjectileFnTable

