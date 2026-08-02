	.include "asm/macros.inc"
	.syntax unified
	.text

	thumb_func_start FUN_080cf91c
FUN_080cf91c: @ 0x080CF91C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x2c]
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080CF92E
	cmp r5, #1
	beq _080CF968
	b _080CF9C6
_080CF92E:
	ldr r1, _080CF98C @ =0x00006D0D
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080CF990 @ =0x08370694
	bl SetDDP
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r4, #0x58]
	str r0, [r1]
	str r5, [r4, #0x5c]
	str r5, [r4, #0x60]
	movs r0, #0x40
	rsbs r0, r0, #0
	str r0, [r4, #0x64]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080CF960
	movs r2, #0x40
_080CF960:
	str r2, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CF968:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080CF998
	movs r0, #0xc0
	lsls r0, r0, #2
	cmp r1, r0
	ble _080CF986
	str r0, [r4, #0x5c]
_080CF986:
	ldr r0, [r4, #0x5c]
	ldr r1, _080CF994 @ =0xFFFFFD00
	b _080CF9A6
	.align 2, 0
_080CF98C: .4byte 0x00006D0D
_080CF990: .4byte 0x08370694
_080CF994: .4byte 0xFFFFFD00
_080CF998:
	movs r0, #0x80
	lsls r0, r0, #3
	cmp r1, r0
	ble _080CF9A2
	str r0, [r4, #0x5c]
_080CF9A2:
	ldr r0, [r4, #0x5c]
	ldr r1, _080CF9DC @ =0xFFFFFC00
_080CF9A6:
	cmp r0, r1
	bge _080CF9AC
	str r1, [r4, #0x5c]
_080CF9AC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	bl FUN_080cf428
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080CF9C6
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080CF9C6:
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _080CF9D6
	movs r1, #0
	str r1, [r4, #0x2c]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080CF9D6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080CF9DC: .4byte 0xFFFFFC00
