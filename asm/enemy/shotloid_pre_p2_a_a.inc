	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08093afc
FUN_08093afc: @ 0x08093AFC
	push {r4, lr}
	adds r2, r0, #0
	adds r3, r2, #0
	adds r3, #0x8c
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08093B48
	ldr r1, _08093B3C @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #2
	str r4, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	ldr r1, [r3]
	movs r0, #0x80
	lsls r0, r0, #9
	ands r0, r1
	cmp r0, #0
	bne _08093B40
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r0, r1
	cmp r0, #0
	beq _08093B42
	strb r4, [r2, #0xd]
	b _08093B44
	.align 2, 0
_08093B3C: .4byte gEnemyFnTable
_08093B40:
	movs r0, #1
_08093B42:
	strb r0, [r2, #0xd]
_08093B44:
	movs r0, #1
	b _08093B4A
_08093B48:
	movs r0, #0
_08093B4A:
	pop {r4}
	pop {r1}
	bx r1

	thumb_func_start FUN_08093b50
FUN_08093b50: @ 0x08093B50
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #7
	beq _08093BD6
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r5, [r0]
	cmp r5, #0
	bne _08093BD6
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _08093B70
	cmp r0, #1
	beq _08093BB4
	b _08093BD6
_08093B70:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08093BD6
	ldr r1, _08093BAC @ =0x08369E18
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _08093BB0 @ =0x08369E3C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08093BA6:
	movs r0, #1
	b _08093BD8
	.align 2, 0
_08093BAC: .4byte 0x08369E18
_08093BB0: .4byte 0x08369E3C
_08093BB4:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08093BD4
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _08093BD0 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _08093BA6
	strb r5, [r4, #0xf]
	b _08093BD6
	.align 2, 0
_08093BD0: .4byte 0x00020001
_08093BD4:
	strb r0, [r4, #0xf]
_08093BD6:
	movs r0, #0
_08093BD8:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
