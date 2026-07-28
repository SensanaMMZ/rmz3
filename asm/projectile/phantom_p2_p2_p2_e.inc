	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080afe38
FUN_080afe38: @ 0x080AFE38
	push {r4, r5, r6, lr}
	adds r4, r1, #0
	adds r6, r3, #0
	ldr r5, [r6]
	ldr r0, [r2]
	adds r3, r0, r5
	str r3, [r2]
	ldr r1, [r2, #4]
	movs r0, #0x80
	rsbs r0, r0, #0
	cmp r1, r0
	ble _080AFE54
	subs r1, #8
	str r1, [r2, #4]
_080AFE54:
	ldr r0, [r4]
	adds r0, r0, r3
	str r0, [r4]
	ldr r0, [r4, #4]
	adds r0, r0, r1
	str r0, [r4, #4]
	ldr r0, _080AFE70 @ =0x000003FF
	adds r1, r3, r0
	ldr r0, _080AFE74 @ =0x000007FE
	cmp r1, r0
	bhi _080AFE78
	movs r0, #0
	b _080AFE7E
	.align 2, 0
_080AFE70: .4byte 0x000003FF
_080AFE74: .4byte 0x000007FE
_080AFE78:
	rsbs r0, r5, #0
	str r0, [r6]
	movs r0, #1
_080AFE7E:
	pop {r4, r5, r6}
	pop {r1}
	bx r1

