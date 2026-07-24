	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start tilecannon_08078198
tilecannon_08078198: @ 0x08078198
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _080781A8
	cmp r0, #1
	beq _080781EC
	b _08078208
_080781A8:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08078208
	ldr r1, _080781E4 @ =0x08367418
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080781E8 @ =0x0836743C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #1
	b _0807820A
	.align 2, 0
_080781E4: .4byte 0x08367418
_080781E8: .4byte 0x0836743C
_080781EC:
	ldrb r0, [r4, #0xd]
	cmp r0, #3
	bne _080781F8
	adds r0, r4, #0
	bl FUN_080780c4
_080781F8:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08078206
	movs r0, #1
	b _0807820A
_08078206:
	strb r0, [r4, #0xf]
_08078208:
	movs r0, #0
_0807820A:
	pop {r4}
	pop {r1}
	bx r1
