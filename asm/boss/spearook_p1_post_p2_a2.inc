	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_08062a94
FUN_08062a94: @ 0x08062A94
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, _08062AB8 @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08062AD8
	cmp r0, #1
	bgt _08062ABC
	cmp r0, #0
	beq _08062AC6
	b _08062B60
	.align 2, 0
_08062AB8: .4byte 0xFFFFEE00
_08062ABC:
	cmp r0, #2
	beq _08062B10
	cmp r0, #3
	beq _08062B2C
	b _08062B60
_08062AC6:
	ldr r1, _08062B08 @ =0x0000D602
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062AD8:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _08062AF2
	movs r1, #0xf0
	lsls r1, r1, #4
	ldr r2, _08062B0C @ =0xFFFFCF00
	adds r0, r4, #0
	bl FUN_08061b68
_08062AF2:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _08062AFE
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062AFE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08062B60
	.align 2, 0
_08062B08: .4byte 0x0000D602
_08062B0C: .4byte 0xFFFFCF00
_08062B10:
	adds r2, r5, #0
	adds r2, #0xbc
	ldr r0, [r2]
	movs r1, #0x11
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	ldr r1, _08062B68 @ =0x0000D601
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062B2C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _08062B46
	movs r1, #0xf0
	lsls r1, r1, #4
	ldr r2, _08062B6C @ =0xFFFFCF00
	adds r0, r4, #0
	bl FUN_08061b68
_08062B46:
	adds r0, r5, #0
	adds r0, #0xbc
	ldr r2, [r0]
	movs r0, #4
	ands r2, r0
	cmp r2, #0
	bne _08062B5A
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
_08062B5A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08062B60:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08062B68: .4byte 0x0000D601
_08062B6C: .4byte 0xFFFFCF00

