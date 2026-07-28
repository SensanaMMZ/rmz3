	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808f824
FUN_0808f824: @ 0x0808F824
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0808F85E
	cmp r0, #1
	bgt _0808F838
	cmp r0, #0
	beq _0808F842
	b _0808F8CC
_0808F838:
	cmp r0, #2
	beq _0808F880
	cmp r0, #3
	beq _0808F88E
	b _0808F8CC
_0808F842:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808F878 @ =0x08369434
	bl SetDDP
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldr r1, _0808F87C @ =0x00007707
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808F85E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808F870
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808F870:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0808F8CC
	.align 2, 0
_0808F878: .4byte 0x08369434
_0808F87C: .4byte 0x00007707
_0808F880:
	ldr r1, _0808F8D4 @ =0x00007701
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808F88E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r1, [r0]
	cmp r1, #3
	bne _0808F8A4
	movs r0, #0
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
_0808F8A4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808F8D8 @ =0x08369584
	adds r5, r4, #0
	adds r5, #0x71
	movs r1, #0
	ldrsb r1, [r5, r1]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808F8DC @ =0x0836941C
	adds r1, r1, r2
	bl SetDDP
	ldrb r1, [r5]
	adds r0, r4, #0
	adds r0, #0xc0
	strb r1, [r0]
_0808F8CC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808F8D4: .4byte 0x00007701
_0808F8D8: .4byte 0x08369584
_0808F8DC: .4byte 0x0836941C
