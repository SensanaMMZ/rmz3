	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start anubisMode4
anubisMode4: @ 0x08050A1C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08050A64
	cmp r0, #1
	bgt _08050A30
	cmp r0, #0
	beq _08050A3A
	b _08050AD6
_08050A30:
	cmp r0, #2
	beq _08050A80
	cmp r0, #3
	beq _08050A9C
	b _08050AD6
_08050A3A:
	movs r0, #0x54
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0xd0
	strh r0, [r1]
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #8
	orrs r0, r1
	movs r1, #0x10
	orrs r0, r1
	str r0, [r2]
	ldr r1, _08050A7C @ =0x0000AF02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050A64:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08050AD6
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _08050AD4
	.align 2, 0
_08050A7C: .4byte 0x0000AF02
_08050A80:
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #9
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	ldr r1, _08050ADC @ =0x0000AF01
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050A9C:
	adds r0, r4, #0
	bl FUN_08050090
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08050AD6
	adds r5, r4, #0
	adds r5, #0xd0
	movs r0, #0
	ldrsh r1, [r5, r0]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	beq _08050AD0
	adds r0, r1, #0
	bl StopSound
	ldr r0, _08050AE0 @ =0x0000FFFF
	strh r0, [r5]
_08050AD0:
	movs r0, #1
	strb r0, [r4, #0xd]
_08050AD4:
	strb r0, [r4, #0xe]
_08050AD6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08050ADC: .4byte 0x0000AF01
_08050AE0: .4byte 0x0000FFFF
