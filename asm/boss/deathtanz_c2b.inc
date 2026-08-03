	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start deathtanzMode14
deathtanzMode14: @ 0x0804A454
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bhi _0804A530
	lsls r0, r0, #2
	ldr r1, _0804A468 @ =_0804A46C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804A468: .4byte _0804A46C
_0804A46C: @ jump table
	.4byte _0804A484 @ case 0
	.4byte _0804A4A6 @ case 1
	.4byte _0804A4BC @ case 2
	.4byte _0804A4D4 @ case 3
	.4byte _0804A4F4 @ case 4
	.4byte _0804A518 @ case 5
_0804A484:
	adds r3, r4, #0
	adds r3, #0xc1
	ldrb r1, [r3]
	movs r0, #2
	movs r2, #0
	orrs r0, r1
	strb r0, [r3]
	adds r0, r4, #0
	adds r0, #0xbe
	strb r2, [r0]
	ldr r1, _0804A4B8 @ =0x0000A711
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A4A6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A530
	b _0804A4E4
	.align 2, 0
_0804A4B8: .4byte 0x0000A711
_0804A4BC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804A4EC @ =0x08362DAC
	bl SetDDP
	ldr r1, _0804A4F0 @ =0x0000A713
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A4D4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xbe
	ldrb r0, [r0]
	cmp r0, #0
	beq _0804A530
_0804A4E4:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0804A530
	.align 2, 0
_0804A4EC: .4byte sCollisions+(24*62)
_0804A4F0: .4byte 0x0000A713
_0804A4F4:
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #1
	orrs r0, r1
	strb r0, [r2]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804A538 @ =sCollisions+(24*60)
	bl SetDDP
	ldr r1, _0804A53C @ =0x0000A715
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A518:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A530
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804A530:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0804A538: .4byte sCollisions+(24*60)
_0804A53C: .4byte 0x0000A715
