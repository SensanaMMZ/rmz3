	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierleIceCarnival2
glacierleIceCarnival2: @ 0x0805908C
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldrb r4, [r6, #0xe]
	cmp r4, #1
	bne _08059098
	b _080591B0
_08059098:
	cmp r4, #1
	bgt _080590A2
	cmp r4, #0
	beq _080590B0
	b _080593BC
_080590A2:
	cmp r4, #2
	bne _080590A8
	b _08059314
_080590A8:
	cmp r4, #3
	bne _080590AE
	b _08059324
_080590AE:
	b _080593BC
_080590B0:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08059238 @ =0x08363F04
	bl SetDDP
	strb r4, [r6, #0x12]
	adds r2, r6, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	adds r0, r6, #0
	bl createGlacierleAtkHand
	adds r7, r0, #0
	str r7, [r6, #0x2c]
	cmp r7, #0
	beq _0805919A
	adds r1, r6, #0
	bl createGlacierleJoint
	adds r4, r0, #0
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
	cmp r4, #0
	beq _0805912C
	adds r0, r4, #0
	adds r1, r6, #0
	bl createGlacierleSucker
	adds r4, r0, #0
	str r4, [r6, #0x28]
	ldr r3, [r6, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r3, r1
	str r0, [r4, #0x54]
	adds r2, r0, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08059122
	ldr r0, _0805923C @ =0xFFFFF600
	adds r2, r3, r0
_08059122:
	str r2, [r4, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, _08059240 @ =0xFFFFDB00
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0805912C:
	ldr r3, [r6, #0x54]
	movs r2, #0xb0
	lsls r2, r2, #6
	adds r0, r3, r2
	str r0, [r7, #0x54]
	adds r2, r0, #0
	ldrb r1, [r6, #0xa]
	movs r4, #0x10
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _08059148
	ldr r0, _08059244 @ =0xFFFFD400
	adds r2, r3, r0
_08059148:
	str r2, [r7, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, _08059248 @ =0xFFFFC900
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r2, [r6, #0x54]
	movs r0, #0x88
	lsls r0, r0, #5
	adds r3, r2, r0
	ldrb r1, [r6, #0xa]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	beq _08059168
	ldr r1, _0805924C @ =0xFFFFEF00
	adds r3, r2, r1
_08059168:
	ldr r2, [r6, #0x58]
	ldr r0, _08059244 @ =0xFFFFD400
	adds r2, r2, r0
	adds r0, r7, #0
	adds r1, r3, #0
	bl FUN_08082484
	adds r1, r7, #0
	adds r1, #0xb5
	movs r0, #0
	strb r0, [r1]
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r7, #0x64]
	adds r0, r7, #0
	adds r0, #0x24
	ldrb r0, [r0]
	adds r0, #0x80
	strb r0, [r6, #0x12]
	movs r2, #0x98
	lsls r2, r2, #1
	adds r0, r7, #0
	movs r1, #0
	bl FUN_0808242c
_0805919A:
	movs r1, #0
	movs r0, #0x20
	strb r0, [r6, #0x13]
	str r1, [r6, #0x64]
	ldr r1, _08059250 @ =0x0000B217
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080591B0:
	ldr r7, [r6, #0x2c]
	movs r4, #0x80
	lsls r4, r4, #3
	str r4, [r7, #0x64]
	ldr r5, _08059254 @ =gSineTable
	ldr r0, [r6, #0x64]
	lsls r0, r0, #8
	ldr r1, _08059258 @ =0x00000212
	bl __divsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	adds r0, r0, r4
	str r0, [r7, #0x64]
	ldr r0, _0805925C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r1, _08059260 @ =0x00FFFF00
	ands r0, r1
	cmp r0, r4
	bne _080591F8
	adds r0, r7, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _080591F8
	movs r0, #0x52
	bl PlaySound
_080591F8:
	adds r0, r7, #0
	adds r0, #0xb4
	ldrb r0, [r0]
	cmp r0, #6
	bhi _0805921A
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805921A
	movs r0, #8
	strb r0, [r6, #0x13]
	adds r0, r7, #0
	adds r1, r6, #0
	bl createGlacierleJoint
_0805921A:
	ldr r4, [r6, #0x28]
	ldr r0, [r6, #0x64]
	adds r0, #1
	str r0, [r6, #0x64]
	cmp r0, #2
	ble _0805926A
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08059264
	ldrb r0, [r6, #0x12]
	subs r0, #6
	b _08059268
	.align 2, 0
_08059238: .4byte 0x08363F04
_0805923C: .4byte 0xFFFFF600
_08059240: .4byte 0xFFFFDB00
_08059244: .4byte 0xFFFFD400
_08059248: .4byte 0xFFFFC900
_0805924C: .4byte 0xFFFFEF00
_08059250: .4byte 0x0000B217
_08059254: .4byte gSineTable
_08059258: .4byte 0x00000212
_0805925C: .4byte pZero2
_08059260: .4byte 0x00FFFF00
_08059264:
	ldrb r0, [r6, #0x12]
	adds r0, #6
_08059268:
	strb r0, [r6, #0x12]
_0805926A:
	ldr r0, [r6, #0x64]
	cmp r0, #0x90
	ble _0805928E
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08059282
	ldrb r0, [r6, #0x12]
	cmp r0, #0x1c
	beq _08059288
	b _0805928E
_08059282:
	ldrb r0, [r6, #0x12]
	cmp r0, #0x64
	bne _0805928E
_08059288:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0805928E:
	ldrb r0, [r6, #0x12]
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #5
	bhi _080592E4
	adds r0, r7, #0
	adds r0, #0x24
	ldrb r0, [r0]
	adds r0, #0x80
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r3, r0, #0
	ldr r5, _08059310 @ =gSineTable
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080592C0
	adds r0, #0xff
_080592C0:
	asrs r2, r0, #8
	lsls r0, r3, #1
	adds r0, r0, r5
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _080592D6
	adds r0, #0xff
_080592D6:
	asrs r3, r0, #8
	ldr r0, [r7, #0x54]
	adds r0, r0, r2
	ldr r1, [r7, #0x58]
	adds r1, r1, r3
	bl FUN_080aa5e8
_080592E4:
	ldrb r0, [r6, #0x12]
	cmp r0, #5
	bhi _080592F0
	movs r0, #0x96
	bl PlaySound
_080592F0:
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	adds r0, r7, #0
	movs r1, #0
	bl glacierle_08082598
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _080593BC
	.align 2, 0
_08059310: .4byte gSineTable
_08059314:
	movs r0, #0x1e
	strb r0, [r6, #0x13]
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r6, #0x64]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08059324:
	ldr r7, [r6, #0x2c]
	ldr r4, [r6, #0x28]
	ldr r0, _08059374 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r1, _08059378 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bne _0805934E
	adds r0, r7, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0805934E
	movs r0, #0x52
	bl PlaySound
_0805934E:
	ldr r0, [r6, #0x64]
	subs r0, #0x64
	str r0, [r6, #0x64]
	ldr r1, _0805937C @ =0x000002FF
	cmp r0, r1
	bgt _08059360
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r6, #0x64]
_08059360:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08059380
	ldr r1, [r6, #0x64]
	asrs r1, r1, #8
	ldrb r0, [r6, #0x12]
	subs r0, r0, r1
	b _08059388
	.align 2, 0
_08059374: .4byte pZero2
_08059378: .4byte 0x00FFFF00
_0805937C: .4byte 0x000002FF
_08059380:
	ldr r0, [r6, #0x64]
	asrs r0, r0, #8
	ldrb r1, [r6, #0x12]
	adds r0, r0, r1
_08059388:
	strb r0, [r6, #0x12]
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	adds r0, r7, #0
	movs r1, #0
	bl glacierle_08082598
	ldrb r1, [r6, #0x12]
	adds r0, r4, #0
	bl FUN_0808288c
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080593B6
	movs r0, #0x11
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_080593B6:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080593BC:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
