	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08099eb4
FUN_08099eb4: @ 0x08099EB4
	push {r4, r5, lr}
	adds r2, r0, #0
	adds r5, r1, #0
	ldr r0, [r2, #0xc]
	ldr r3, [r0, #4]
	ldrb r0, [r3, #4]
	cmp r0, #3
	beq _08099ECC
	cmp r0, #0xe
	beq _08099ECC
	cmp r0, #0xf
	bne _08099EF6
_08099ECC:
	ldr r4, [r2, #0x2c]
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08099EF6
	ldr r1, [r4, #0x54]
	ldr r0, [r5]
	cmp r1, r0
	bge _08099EEE
	adds r1, r4, #0
	adds r1, #0xba
	movs r0, #0xff
	b _08099EF4
_08099EEE:
	adds r1, r4, #0
	adds r1, #0xba
	movs r0, #0xfe
_08099EF4:
	strb r0, [r1]
_08099EF6:
	ldr r0, [r3, #4]
	ldr r1, _08099F28 @ =0x000200FF
	ands r0, r1
	subs r1, #0xfd
	cmp r0, r1
	bne _08099F2C
	ldr r4, [r2, #0x2c]
	ldrb r0, [r4, #0xd]
	cmp r0, #6
	beq _08099F4E
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08099F20
	adds r0, r4, #0
	bl IsFrozen
_08099F20:
	movs r1, #0
	movs r0, #6
	b _08099F4A
	.align 2, 0
_08099F28: .4byte 0x000200FF
_08099F2C:
	ldr r4, [r2, #0x2c]
	ldr r0, [r2, #4]
	ldrb r0, [r0]
	cmp r0, #2
	bne _08099F4E
	ldrb r0, [r3, #6]
	cmp r0, #0x40
	beq _08099F4E
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _08099F4E
	movs r0, #5
_08099F4A:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08099F4E:
	pop {r4, r5}
	pop {r0}
	bx r0
