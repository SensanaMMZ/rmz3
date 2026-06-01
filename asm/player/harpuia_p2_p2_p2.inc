	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start harpuia_080354d4
harpuia_080354d4: @ 0x080354D4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _08035512
	cmp r5, #1
	bgt _080354E8
	cmp r5, #0
	beq _080354F2
	b _080355AA
_080354E8:
	cmp r5, #2
	beq _0803555C
	cmp r5, #3
	beq _0803557A
	b _080355AA
_080354F2:
	ldr r1, _08035548 @ =0x0000BE22
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0803554C @ =0x0835EB10
	bl SetDDP
	movs r0, #0xf9
	bl PlaySound
	strb r5, [r4, #0xf]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08035512:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x70]
	ldr r1, _08035550 @ =0x00FFFF00
	ands r0, r1
	ldr r1, _08035554 @ =0x00010500
	cmp r0, r1
	bne _0803552E
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08035558 @ =0x0835EAF8
	bl SetDDP
_0803552E:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080355AA
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	bne _080355A2
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080355AA
	.align 2, 0
_08035548: .4byte 0x0000BE22
_0803554C: .4byte 0x0835EB10
_08035550: .4byte 0x00FFFF00
_08035554: .4byte 0x00010500
_08035558: .4byte 0x0835EAF8
_0803555C:
	ldr r1, _080355B0 @ =0x0000BE23
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080355B4 @ =0x0835EB10
	bl SetDDP
	movs r0, #0xf9
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0803557A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x70]
	ldr r1, _080355B8 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x82
	lsls r1, r1, #9
	cmp r0, r1
	bne _08035598
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080355BC @ =0x0835EAF8
	bl SetDDP
_08035598:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080355AA
_080355A2:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080355AA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080355B0: .4byte 0x0000BE23
_080355B4: .4byte 0x0835EB10
_080355B8: .4byte 0x00FFFF00
_080355BC: .4byte 0x0835EAF8
