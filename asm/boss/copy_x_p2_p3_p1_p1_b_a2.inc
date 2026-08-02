	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start copyxMode19
copyxMode19: @ 0x08056434
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080564DA
	ldr r1, _08056470 @ =0x0000B303
	adds r0, r4, #0
	bl SetMotion
	movs r6, #0
	strb r6, [r4, #0xe]
	adds r5, r4, #0
	adds r5, #0xc6
	ldrb r0, [r5]
	cmp r0, #0
	beq _08056474
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0
	bl FUN_080a83e4
	strb r6, [r5]
	movs r0, #0x46
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0xc7
	movs r0, #1
	b _080564D8
	.align 2, 0
_08056470: .4byte 0x0000B303
_08056474:
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #1
	beq _080564A4
	cmp r0, #1
	bgt _08056488
	cmp r0, #0
	beq _08056492
	b _080564D2
_08056488:
	cmp r0, #2
	beq _080564B0
	cmp r0, #3
	beq _080564C2
	b _080564D2
_08056492:
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl FUN_080a83e4
	movs r0, #0x46
	bl PlaySound
	b _080564D2
_080564A4:
	adds r0, r4, #0
	movs r1, #0
	movs r2, #6
	bl FUN_080a88a4
	b _080564D2
_080564B0:
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl FUN_080a9048
	movs r0, #0x49
	bl PlaySound
	b _080564D2
_080564C2:
	adds r0, r4, #0
	movs r1, #3
	movs r2, #0
	bl FUN_080a9048
	movs r0, #0x46
	bl PlaySound
_080564D2:
	adds r1, r4, #0
	adds r1, #0xc7
	movs r0, #0
_080564D8:
	strb r0, [r1]
_080564DA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08056502
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080564FA
	movs r0, #0x14
	b _080564FC
_080564FA:
	movs r0, #0x12
_080564FC:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08056502:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
