	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start childreMode16
childreMode16: @ 0x08041E44
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _08041E56
	cmp r1, #1
	beq _08041EC4
	b _08041F2C
_08041E56:
	ldrb r0, [r4, #0xb]
	movs r7, #0x10
	movs r6, #0
	orrs r0, r7
	strb r0, [r4, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r4, #0x1d]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _08041EAE
	ldrb r0, [r4, #0xa]
	orrs r0, r7
	b _08041EB4
_08041EAE:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08041EB4:
	strb r0, [r4, #0xa]
	ldr r1, _08041ED8 @ =0x0000A409
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041EC4:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _08041EDC
	movs r0, #0xf6
	b _08041EDE
	.align 2, 0
_08041ED8: .4byte 0x0000A409
_08041EDC:
	movs r0, #0xfa
_08041EDE:
	muls r0, r1, r0
	cmp r0, #0
	bge _08041EE6
	adds r0, #0xff
_08041EE6:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_0801779c
	ldrb r0, [r5, #0xc]
	cmp r0, #4
	bne _08041F2C
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08041F34 @ =gBossFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08041F2C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08041F34: .4byte gBossFnTable
