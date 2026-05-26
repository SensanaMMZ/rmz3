	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start pBomber_08086628
pBomber_08086628: @ 0x08086628
	push {r4, lr}
	adds r3, r0, #0
	adds r4, r3, #0
	adds r4, #0xbc
	ldr r0, [r4]
	cmp r0, #0
	bne _08086650
	adds r0, r3, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08086650
	ldr r2, _08086658 @ =0x083685AC
	movs r0, #0
	adds r1, r3, #0
	bl ApplyElementEffect
	str r0, [r4]
_08086650:
	movs r0, #1
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_08086658: .4byte 0x083685AC

	thumb_func_start FUN_0808665c
FUN_0808665c: @ 0x0808665C
	push {lr}
	adds r2, r0, #0
	adds r3, r1, #0
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #4]
	cmp r0, #3
	beq _08086674
	cmp r0, #0xe
	beq _08086674
	cmp r0, #0xf
	bne _0808669E
_08086674:
	ldr r2, [r2, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0808669E
	ldr r1, [r2, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _08086696
	adds r1, r2, #0
	adds r1, #0xba
	movs r0, #0xff
	b _0808669C
_08086696:
	adds r1, r2, #0
	adds r1, #0xba
	movs r0, #0xfe
_0808669C:
	strb r0, [r1]
_0808669E:
	pop {r0}
	bx r0
	.align 2, 0

