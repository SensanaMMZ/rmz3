	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807ffd8
FUN_0807ffd8: @ 0x0807FFD8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0807FFE8
	cmp r5, #1
	beq _08080002
	b _0808004C
_0807FFE8:
	ldr r1, _08080014 @ =0x00004C02
	adds r0, r4, #0
	bl SetMotion
	str r5, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08080018 @ =0x08367F00
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08080002:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _0808001C
	ldr r0, [r4, #0x58]
	adds r0, #0x20
	b _08080044
	.align 2, 0
_08080014: .4byte 0x00004C02
_08080018: .4byte 0x08367F00
_0808001C:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808002C
	str r1, [r4, #0x60]
_0808002C:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08080046
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
_08080044:
	str r0, [r4, #0x58]
_08080046:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0808004C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
