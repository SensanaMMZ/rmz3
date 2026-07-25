	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08096814
FUN_08096814: @ 0x08096814
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r1, [r5, #0xe]
	cmp r1, #1
	beq _08096866
	cmp r1, #1
	bgt _0809682A
	cmp r1, #0
	beq _08096830
	b _08096936
_0809682A:
	cmp r1, #2
	beq _0809688A
	b _08096936
_08096830:
	movs r0, #0x3c
	strb r0, [r5, #0x12]
	movs r0, #6
	strb r0, [r5, #0x13]
	adds r0, r5, #0
	adds r0, #0xbd
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r2, #0x10
	adds r0, r2, #0
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r1, #1
	cmp r0, #0
	beq _08096852
	subs r1, #2
_08096852:
	str r1, [r5, #0x5c]
	str r2, [r5, #0x64]
	movs r1, #0x10
	cmp r0, #0
	beq _0809685E
	subs r1, #0x20
_0809685E:
	str r1, [r5, #0x64]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08096866:
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	bge _0809687C
	ldr r1, _08096878 @ =0x0000DB0F
	adds r0, r5, #0
	bl SetMotion
	b _08096884
	.align 2, 0
_08096878: .4byte 0x0000DB0F
_0809687C:
	ldr r1, _08096898 @ =0x0000DB05
	adds r0, r5, #0
	bl SetMotion
_08096884:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0809688A:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _0809689C
	subs r0, #1
	strb r0, [r5, #0x12]
	b _080968FE
	.align 2, 0
_08096898: .4byte 0x0000DB05
_0809689C:
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080968FE
	movs r0, #6
	strb r0, [r5, #0x13]
	adds r1, r5, #0
	adds r1, #0xbd
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _080968C6
	strb r2, [r1]
	movs r0, #0x3c
	strb r0, [r5, #0x12]
_080968C6:
	ldrb r4, [r5, #0xa]
	lsrs r4, r4, #4
	movs r0, #1
	ands r4, r0
	ldr r1, [r5, #0x54]
	ldr r0, _08096940 @ =0xFFFFF400
	adds r1, r1, r0
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r0, r0, #0xb
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08096944 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0x2c
	bl PlaySound
	ldr r1, _08096948 @ =0xFFFFFD00
	lsls r4, r4, #7
	subs r4, #0x80
	lsls r4, r4, #0x18
	lsrs r4, r4, #0x18
	mov r0, sp
	adds r2, r4, #0
	bl CreateLemon
_080968FE:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r2, r1, #0
	cmp r1, #0
	bge _0809690E
	rsbs r2, r1, #0
_0809690E:
	ldr r0, _0809694C @ =0x0000013F
	cmp r2, r0
	bgt _0809691A
	ldr r0, [r5, #0x64]
	adds r0, r1, r0
	str r0, [r5, #0x5c]
_0809691A:
	adds r0, r5, #0
	bl FUN_08095e28
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08096930
	ldr r0, [r5, #0x5c]
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
	movs r0, #1
	strb r0, [r5, #0xe]
_08096930:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08096936:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08096940: .4byte 0xFFFFF400
_08096944: .4byte 0xFFFFF600
_08096948: .4byte 0xFFFFFD00
_0809694C: .4byte 0x0000013F
