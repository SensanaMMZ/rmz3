	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808f15c
FUN_0808f15c: @ 0x0808F15C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0808F176
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808F194 @ =0x083693A0
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808F176:
	adds r5, r4, #0
	adds r5, #0xbc
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _0808F18C
	movs r0, #0
	str r0, [r5]
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_0808F18C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808F194: .4byte 0x083693A0
