	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start hanu_0805ccc0
hanu_0805ccc0: @ 0x0805CCC0
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805CD28
	ldr r1, _0805CCFC @ =0x0000B512
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805CD00 @ =0x08364F88
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805CD08
	ldr r0, [r4, #0x54]
	ldr r1, _0805CD04 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r4, #0x54]
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r4, #0x5c]
	movs r0, #0xc0
	lsls r0, r0, #6
	b _0805CD18
	.align 2, 0
_0805CCFC: .4byte 0x0000B512
_0805CD00: .4byte 0x08364F88
_0805CD04: .4byte 0xFFFFF000
_0805CD08:
	ldr r0, [r4, #0x54]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [r4, #0x54]
	ldr r0, _0805CDB0 @ =0xFFFFFC00
	str r0, [r4, #0x5c]
	ldr r0, _0805CDB4 @ =0xFFFFD000
_0805CD18:
	str r0, [r4, #0x64]
	ldr r0, _0805CDB0 @ =0xFFFFFC00
	str r0, [r4, #0x60]
	movs r0, #0x14
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805CD28:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	movs r6, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _0805CDA4
	ldr r1, [r4, #0x64]
	adds r0, r4, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805CD56
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805CD56:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x64]
	adds r0, r0, r2
	ldr r5, _0805CDB8 @ =0xFFFFE000
	adds r1, r1, r5
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805CDAA
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805CD94
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	bl FUN_08010dd8
_0805CD94:
	movs r0, #0x52
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #5
	bl AppendQuake
_0805CDA4:
	movs r0, #0x15
	strb r0, [r4, #0xd]
	strb r6, [r4, #0xe]
_0805CDAA:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0805CDB0: .4byte 0xFFFFFC00
_0805CDB4: .4byte 0xFFFFD000
_0805CDB8: .4byte 0xFFFFE000

