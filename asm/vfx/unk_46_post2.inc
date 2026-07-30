	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080bf2f0
FUN_080bf2f0: @ 0x080BF2F0
	push {lr}
	adds r3, r0, #0
	ldrb r0, [r3, #0xe]
	cmp r0, #0
	beq _080BF300
	cmp r0, #1
	beq _080BF34A
	b _080BF386
_080BF300:
	adds r0, r3, #0
	adds r0, #0x7c
	ldrb r0, [r0]
	movs r2, #1
	ands r2, r0
	cmp r2, #0
	beq _080BF316
	ldrb r1, [r3, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080BF31C
_080BF316:
	ldrb r1, [r3, #0xa]
	movs r0, #0xef
	ands r0, r1
_080BF31C:
	strb r0, [r3, #0xa]
	adds r1, r2, #0
	adds r0, r3, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r3
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	movs r0, #3
	strb r0, [r3, #0x13]
	movs r0, #0xa
	strb r0, [r3, #0x12]
	ldrb r0, [r3, #0xe]
	adds r0, #1
	strb r0, [r3, #0xe]
_080BF34A:
	ldrb r0, [r3, #0x12]
	cmp r0, #0
	beq _080BF35A
	subs r0, #1
	strb r0, [r3, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BF380
_080BF35A:
	movs r0, #0xa
	strb r0, [r3, #0x12]
	ldrb r0, [r3, #0x13]
	cmp r0, #0
	beq _080BF36E
	subs r0, #1
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BF380
_080BF36E:
	ldr r1, _080BF38C @ =gVFXFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
_080BF380:
	adds r0, r3, #0
	bl UpdateMotionGraphic
_080BF386:
	pop {r0}
	bx r0
	.align 2, 0
_080BF38C: .4byte gVFXFnTable
