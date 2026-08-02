	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0806da5c
FUN_0806da5c: @ 0x0806DA5C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806DA7A
	movs r1, #0xb8
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x78
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806DA7A:
	adds r1, r4, #0
	adds r1, #0xb4
	movs r5, #0
	movs r0, #1
	strb r0, [r1, #0xb]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0xb0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0806DA9C
	strb r5, [r4, #0xd]
	b _0806DAAE
_0806DA9C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806DAB0
	movs r0, #3
	strb r0, [r4, #0xd]
_0806DAAE:
	strb r5, [r4, #0xe]
_0806DAB0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
