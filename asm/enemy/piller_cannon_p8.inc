	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08068e64
FUN_08068e64: @ 0x08068E64
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08068E7E
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08068EA8 @ =0x083661BC
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08068E7E:
	adds r5, r4, #0
	adds r5, #0xbc
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _08068EA0
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08068EAC @ =0x083661A4
	bl SetDDP
	movs r1, #0
	str r1, [r5]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08068EA0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08068EA8: .4byte 0x083661BC
_08068EAC: .4byte 0x083661A4
