	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808f234
FUN_0808f234: @ 0x0808F234
	push {lr}
	adds r2, r0, #0
	adds r3, r1, #0
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #4]
	cmp r0, #3
	beq _0808F24C
	cmp r0, #0xe
	beq _0808F24C
	cmp r0, #0xf
	bne _0808F276
_0808F24C:
	ldr r2, [r2, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0808F276
	ldr r1, [r2, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _0808F26E
	adds r1, r2, #0
	adds r1, #0xbb
	movs r0, #0xff
	b _0808F274
_0808F26E:
	adds r1, r2, #0
	adds r1, #0xbb
	movs r0, #0xfe
_0808F274:
	strb r0, [r1]
_0808F276:
	pop {r0}
	bx r0
	.align 2, 0
