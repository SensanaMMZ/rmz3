	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080caafc
FUN_080caafc: @ 0x080CAAFC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080CAB0C
	cmp r0, #1
	beq _080CAB28
	b _080CAB48
_080CAB0C:
	ldr r1, _080CAB50 @ =0x00001104
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080CAB54 @ =0x0836FD28
	bl SetDDP
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CAB28:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080CAB3C
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080CAB3C:
	ldr r0, [r4, #0x58]
	subs r0, #0x80
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CAB48:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080CAB50: .4byte 0x00001104
_080CAB54: .4byte 0x0836FD28
