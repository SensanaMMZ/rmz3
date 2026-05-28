	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start leviathanMode0Pre
leviathanMode0Pre: @ 0x08035FF8
	push {lr}
	adds r2, r0, #0
	ldr r3, [r2, #0x28]
	ldrh r1, [r3, #0x10]
	movs r0, #0x30
	ands r0, r1
	cmp r0, #0
	beq _08036010
	movs r1, #0
	movs r0, #1
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08036010:
	ldrh r1, [r3, #0x12]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08036022
	movs r1, #0
	movs r0, #2
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08036022:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start leviathanMode1Pre
leviathanMode1Pre: @ 0x08036028
	push {lr}
	adds r2, r0, #0
	ldr r0, [r2, #0x28]
	ldrh r1, [r0, #0x12]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08036040
	movs r1, #0
	movs r0, #2
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08036040:
	pop {r0}
	bx r0

