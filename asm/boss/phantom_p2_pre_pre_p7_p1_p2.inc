	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806019c
FUN_0806019c: @ 0x0806019C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080601B0
	str r1, [r4, #0x60]
_080601B0:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r5, #4
	ands r0, r5
	cmp r0, #0
	beq _080601CC
	ldr r0, _080601EC @ =0xFFFFFD00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0xd
	bl FUN_080607a0
	strb r5, [r4, #0xf]
_080601CC:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_0806089c
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080601E6
	adds r0, r4, #0
	movs r1, #4
	bl FUN_080607a0
	movs r0, #3
	strb r0, [r4, #0xf]
_080601E6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080601EC: .4byte 0xFFFFFD00
