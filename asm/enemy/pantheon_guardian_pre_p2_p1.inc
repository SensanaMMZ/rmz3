	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08063e28
FUN_08063e28: @ 0x08063E28
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08063E40
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063E40:
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _08063E52
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063E52:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x40
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _08063E6A
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063E6A:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08063E7A
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08063E7A:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_08063e80
FUN_08063e80: @ 0x08063E80
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08063E98
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063E98:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x40
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _08063EB0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063EB0:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08063EC0
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08063EC0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08063ec8
FUN_08063ec8: @ 0x08063EC8
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _08063EDC
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063EDC:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08063EEC
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08063EEC:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08063ef4
FUN_08063ef4: @ 0x08063EF4
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x40
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _08063F10
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08063F10:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08063F20
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08063F20:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
