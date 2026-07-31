	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start hanu_0805c7c4
hanu_0805c7c4: @ 0x0805C7C4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805C80E
	ldr r1, _0805C7F8 @ =0x0000B50D
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805C7FC @ =0x08364F58
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805C800
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #5
	b _0805C806
	.align 2, 0
_0805C7F8: .4byte 0x0000B50D
_0805C7FC: .4byte 0x08364F58
_0805C800:
	ldr r0, _0805C864 @ =0xFFFFFC00
	str r0, [r4, #0x5c]
	ldr r0, _0805C868 @ =0xFFFFF000
_0805C806:
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C80E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805C874
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805C84A
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl FUN_08010dd8
_0805C84A:
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #5
	bl AppendQuake
	movs r0, #0x52
	bl PlaySound
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _0805C86C
	movs r0, #0x10
	b _0805C86E
	.align 2, 0
_0805C864: .4byte 0xFFFFFC00
_0805C868: .4byte 0xFFFFF000
_0805C86C:
	movs r0, #0x11
_0805C86E:
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_0805C874:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
