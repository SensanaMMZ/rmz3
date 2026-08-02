	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806d8b0
FUN_0806d8b0: @ 0x0806D8B0
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	bne _0806D944
	ldr r1, _0806D904 @ =0x00001703
	adds r0, r5, #0
	bl SetMotion
	ldr r0, [r5, #0x58]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806D90C
	ldr r0, [r5, #0x54]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [sp]
	movs r4, #0xc0
	lsls r4, r4, #1
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x90
	bl CreateLemon
	ldr r0, [r5, #0x58]
	ldr r1, _0806D908 @ =0xFFFFFB00
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x70
	bl CreateLemon
	b _0806D934
	.align 2, 0
_0806D904: .4byte 0x00001703
_0806D908: .4byte 0xFFFFFB00
_0806D90C:
	ldr r0, [r5, #0x54]
	ldr r2, _0806D964 @ =0xFFFFF000
	adds r0, r0, r2
	str r0, [sp]
	movs r4, #0xc0
	lsls r4, r4, #1
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0xef
	bl CreateLemon
	ldr r0, [r5, #0x58]
	ldr r1, _0806D968 @ =0xFFFFFB00
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x10
	bl CreateLemon
_0806D934:
	movs r0, #0x2c
	bl PlaySound
	movs r0, #0x30
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806D944:
	ldr r4, [r5, #0x2c]
	cmp r4, #0
	bne _0806D96C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806D96C
	strb r4, [r5, #0xd]
	strb r4, [r5, #0xe]
	b _0806D990
	.align 2, 0
_0806D964: .4byte 0xFFFFF000
_0806D968: .4byte 0xFFFFFB00
_0806D96C:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806D990
	ldr r1, [r5, #0x2c]
	cmp r1, #0
	beq _0806D98A
	movs r0, #4
	strb r0, [r5, #0xd]
	movs r0, #0
	strb r0, [r5, #0xe]
	b _0806D990
_0806D98A:
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0806D990:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0

