	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c8744
FUN_080c8744: @ 0x080C8744
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080C87A6
	cmp r0, #1
	bgt _080C8758
	cmp r0, #0
	beq _080C8762
	b _080C8826
_080C8758:
	cmp r0, #2
	beq _080C8810
	cmp r0, #3
	beq _080C8814
	b _080C8826
_080C8762:
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r1, r0
	movs r0, #2
	orrs r1, r0
	strb r1, [r4, #0xa]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _080C8780
	movs r1, #0x9e
	lsls r1, r1, #8
	b _080C8788
_080C8780:
	cmp r0, #2
	bne _080C8790
	movs r1, #0x9f
	lsls r1, r1, #8
_080C8788:
	adds r0, r4, #0
	bl SetMotion
	b _080C879A
_080C8790:
	movs r1, #0xa1
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
_080C879A:
	movs r0, #0
	strb r0, [r4, #0x12]
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080C87A6:
	ldr r6, [r4, #0x74]
	ldrb r0, [r4, #0x11]
	adds r5, r4, #0
	adds r5, #0x7c
	cmp r0, #3
	bne _080C87E8
	ldr r2, [r4, #0x2c]
	ldr r0, _080C8800 @ =0x00000DC4
	adds r2, r2, r0
	ldrb r0, [r5]
	lsls r0, r0, #0xc
	ldr r1, _080C8804 @ =0xFFFF9800
	adds r0, r0, r1
	ldr r1, [r2]
	subs r1, r1, r0
	ldr r3, _080C8808 @ =0xFFFFF800
	adds r0, r1, r3
	str r0, [r4, #0x54]
	ldr r0, [r2, #4]
	movs r2, #0xe0
	lsls r2, r2, #6
	adds r0, r0, r2
	str r0, [r4, #0x58]
	ldr r2, [r4, #0x28]
	movs r3, #4
	ldrsh r0, [r2, r3]
	cmp r0, #1
	bne _080C87E8
	ldr r3, _080C880C @ =0xFFFFF600
	adds r0, r1, r3
	ldr r1, [r2, #0x34]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_080C87E8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5]
	ldrb r6, [r6]
	cmp r0, r6
	blo _080C8826
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080C8826
	.align 2, 0
_080C8800: .4byte 0x00000DC4
_080C8804: .4byte 0xFFFF9800
_080C8808: .4byte 0xFFFFF800
_080C880C: .4byte 0xFFFFF600
_080C8810:
	movs r0, #3
	strb r0, [r4, #0xe]
_080C8814:
	ldr r1, _080C882C @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080C8826:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080C882C: .4byte gVFXFnTable

