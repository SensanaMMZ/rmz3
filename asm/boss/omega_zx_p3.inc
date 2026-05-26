	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08060fdc
FUN_08060fdc: @ 0x08060FDC
	push {lr}
	mov ip, r0
	ldrb r1, [r0, #0xe]
	cmp r1, #1
	beq _0806100A
	cmp r1, #1
	bgt _08060FF0
	cmp r1, #0
	beq _08060FF6
	b _08061060
_08060FF0:
	cmp r1, #2
	beq _08061058
	b _08061060
_08060FF6:
	movs r0, #1
	mov r1, ip
	strb r0, [r1, #0xe]
	adds r1, #0xd0
	movs r0, #0xa0
	lsls r0, r0, #2
	str r0, [r1]
	movs r0, #0xf0
	mov r2, ip
	strb r0, [r2, #0x12]
_0806100A:
	mov r3, ip
	adds r3, #0xd0
	ldr r2, [r3]
	movs r1, #0x98
	subs r1, r1, r2
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #1
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r3]
	mov r1, ip
	ldr r0, [r1, #0x58]
	subs r0, r0, r2
	str r0, [r1, #0x58]
	adds r1, #0xb8
	ldr r1, [r1]
	cmp r0, r1
	bge _08061034
	mov r2, ip
	str r1, [r2, #0x58]
_08061034:
	mov r2, ip
	ldr r0, [r2, #0x54]
	ldr r1, [r2, #0x58]
	str r0, [r2, #0x5c]
	str r1, [r2, #0x60]
	ldrb r0, [r2, #0x12]
	cmp r0, #0
	beq _0806104E
	subs r0, #1
	strb r0, [r2, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08061060
_0806104E:
	mov r1, ip
	ldrb r0, [r1, #0xe]
	adds r0, #1
	strb r0, [r1, #0xe]
	b _08061060
_08061058:
	movs r0, #0
	mov r2, ip
	strb r1, [r2, #0xd]
	strb r0, [r2, #0xe]
_08061060:
	pop {r0}
	bx r0
