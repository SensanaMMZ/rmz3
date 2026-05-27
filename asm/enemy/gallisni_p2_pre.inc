	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08087380
FUN_08087380: @ 0x08087380
	push {lr}
	adds r2, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0808739C @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _08087398
	movs r1, #0
	movs r0, #7
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08087398:
	pop {r0}
	bx r0
	.align 2, 0
_0808739C: .4byte 0x00020001

	thumb_func_start FUN_080873a0
FUN_080873a0: @ 0x080873A0
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _080873B6
	bl isKilled
	cmp r0, #0
	beq _080873D6
_080873B6:
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080873F4 @ =0x08368708
	bl SetDDP
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _080873D6
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080873D6:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _080873F8 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _080873EC
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080873EC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080873F4: .4byte 0x08368708
_080873F8: .4byte 0x00020001

	thumb_func_start FUN_080873fc
FUN_080873fc: @ 0x080873FC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08087424
	ldr r1, _0808742C @ =0x00006703
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08087430 @ =0x08368720
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08087424:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808742C: .4byte 0x00006703
_08087430: .4byte 0x08368720

	thumb_func_start FUN_08087434
FUN_08087434: @ 0x08087434
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08087444
	cmp r0, #1
	beq _08087468
	b _0808749A
_08087444:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080874A0 @ =0x083686D8
	bl SetDDP
	movs r0, #0x80
	strb r0, [r4, #0x12]
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xf
	strb r0, [r1]
	ldr r1, _080874A4 @ =0x00006701
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08087468:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0808747C
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808747C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #8
	bne _0808749A
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080874A8 @ =0x083686F0
	bl SetDDP
_0808749A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080874A0: .4byte 0x083686D8
_080874A4: .4byte 0x00006701
_080874A8: .4byte 0x083686F0
