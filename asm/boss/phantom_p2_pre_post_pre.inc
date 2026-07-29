	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08060410
FUN_08060410: @ 0x08060410
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	beq _0806044A
	cmp r0, #1
	bgt _08060424
	cmp r0, #0
	beq _0806042E
	b _080604D2
_08060424:
	cmp r0, #2
	beq _0806045C
	cmp r0, #3
	beq _08060494
	b _080604D2
_0806042E:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08060458 @ =0x08365350
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
_0806044A:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080604D2
	b _0806047E
	.align 2, 0
_08060458: .4byte 0x08365350
_0806045C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08060488 @ =sCollisions
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x58]
	ldr r1, _0806048C @ =0xFFFFB000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r1, _08060490 @ =0x0000BC17
	adds r0, r4, #0
	bl SetMotion
_0806047E:
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	b _080604D2
	.align 2, 0
_08060488: .4byte sCollisions
_0806048C: .4byte 0xFFFFB000
_08060490: .4byte 0x0000BC17
_08060494:
	ldr r0, [r4, #0x70]
	ldr r1, _080604D8 @ =0x00FFFF00
	ands r0, r1
	ldr r1, _080604DC @ =0x00010500
	cmp r0, r1
	bne _080604BE
	movs r0, #0xfc
	bl PlaySound
	adds r0, r4, #0
	movs r1, #0
	bl FUN_0809142c
	adds r0, r4, #0
	movs r1, #1
	bl FUN_0809142c
	adds r0, r4, #0
	movs r1, #2
	bl FUN_0809142c
_080604BE:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080604D2
	movs r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080604D2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080604D8: .4byte 0x00FFFF00
_080604DC: .4byte 0x00010500

