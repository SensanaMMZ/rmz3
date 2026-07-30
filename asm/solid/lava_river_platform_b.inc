	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080cd03c
FUN_080cd03c: @ 0x080CD03C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080CD04C
	cmp r0, #1
	beq _080CD060
	b _080CD0B2
_080CD04C:
	strb r0, [r4, #0x12]
	str r0, [r4, #0x60]
	movs r1, #0xec
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CD060:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080CD070
	str r1, [r4, #0x60]
_080CD070:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r2, [r2]
	adds r1, r1, r2
	bl PushoutToUp2
	adds r1, r0, #0
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080CD09C
	movs r0, #0x80
	str r0, [r4, #0x60]
	cmp r1, #0
	bne _080CD0AC
	movs r0, #1
	strb r0, [r4, #0x12]
	b _080CD0AC
_080CD09C:
	cmp r1, #0
	bge _080CD0AC
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_080CD0AC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CD0B2:
	pop {r4}
	pop {r0}
	bx r0
