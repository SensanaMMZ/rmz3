	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierle_080583c4
glacierle_080583c4: @ 0x080583C4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08058416
	cmp r0, #1
	bgt _080583D8
	cmp r0, #0
	beq _080583E2
	b _0805848E
_080583D8:
	cmp r0, #2
	beq _0805845C
	cmp r0, #3
	beq _08058478
	b _0805848E
_080583E2:
	movs r0, #0x91
	bl PlaySound
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #2
	orrs r0, r1
	str r0, [r2]
	adds r1, r4, #0
	adds r1, #0xc4
	ldr r0, [r4, #0x54]
	str r0, [r1]
	subs r1, #0x70
	movs r0, #3
	bl AppendQuake
	movs r0, #0x12
	strb r0, [r4, #0x12]
	ldr r1, _08058450 @ =0x0000B208
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058416:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058454 @ =0x08364ABF
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058458 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805848E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _0805848C
	.align 2, 0
_08058450: .4byte 0x0000B208
_08058454: .4byte 0x08364ABF
_08058458: .4byte sCollisions
_0805845C:
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #3
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	ldr r1, _08058494 @ =0x0000B209
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058478:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805848E
	movs r0, #0
	strb r0, [r4, #0xd]
_0805848C:
	strb r0, [r4, #0xe]
_0805848E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08058494: .4byte 0x0000B209
