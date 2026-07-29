	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08063074
FUN_08063074: @ 0x08063074
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080630BA
	cmp r0, #1
	bgt _08063088
	cmp r0, #0
	beq _08063092
	b _0806315C
_08063088:
	cmp r0, #2
	beq _0806311A
	cmp r0, #3
	beq _08063138
	b _0806315C
_08063092:
	adds r2, r4, #0
	adds r2, #0xbc
	ldr r0, [r2]
	movs r1, #0x40
	orrs r0, r1
	str r0, [r2]
	movs r2, #0xc0
	lsls r2, r2, #2
	str r2, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0xc0
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #9
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080630BA:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	movs r5, #0
	cmp r1, #0
	bge _080630E4
	ldr r1, _080630E0 @ =0xFFFFEA00
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806310C
	b _080630FC
	.align 2, 0
_080630E0: .4byte 0xFFFFEA00
_080630E4:
	movs r1, #0xb0
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08063106
_080630FC:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	b _08063108
_08063106:
	movs r5, #1
_08063108:
	cmp r5, #0
	beq _08063112
_0806310C:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08063112:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0806315C
_0806311A:
	ldr r0, [r4, #0x5c]
	rsbs r1, r0, #0
	str r1, [r4, #0x5c]
	movs r0, #0x18
	rsbs r0, r0, #0
	str r0, [r4, #0x64]
	cmp r1, #0
	bge _0806312C
	movs r0, #0x18
_0806312C:
	str r0, [r4, #0x64]
	lsrs r0, r1, #0x1f
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08063138:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	cmp r1, #0
	bge _08063152
	cmp r0, #1
	bne _08063156
	b _0806315C
_08063152:
	cmp r0, #0
	beq _0806315C
_08063156:
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_0806315C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	pop {r4, r5}
	pop {r0}
	bx r0
