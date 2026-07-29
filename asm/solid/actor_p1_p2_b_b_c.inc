	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Actor35_Update
Actor35_Update: @ 0x080D4228
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #9
	bls _080D4234
	b _080D43B6
_080D4234:
	lsls r0, r0, #2
	ldr r1, _080D4240 @ =_080D4244
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D4240: .4byte _080D4244
_080D4244: @ jump table
	.4byte _080D426C @ case 0
	.4byte _080D4284 @ case 1
	.4byte _080D42A4 @ case 2
	.4byte _080D42C0 @ case 3
	.4byte _080D42D4 @ case 4
	.4byte _080D42F4 @ case 5
	.4byte _080D4302 @ case 6
	.4byte _080D4324 @ case 7
	.4byte _080D434C @ case 8
	.4byte _080D436C @ case 9
_080D426C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldr r1, _080D429C @ =0x0000C20D
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D4284:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D4298
	b _080D43B6
_080D4298:
	ldr r1, _080D42A0 @ =0x0000C20C
	b _080D433A
	.align 2, 0
_080D429C: .4byte 0x0000C20D
_080D42A0: .4byte 0x0000C20C
_080D42A4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D42B8
	b _080D43B6
_080D42B8:
	ldr r1, _080D42BC @ =0x0000C201
	b _080D433A
	.align 2, 0
_080D42BC: .4byte 0x0000C201
_080D42C0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D43B6
	b _080D4336
_080D42D4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D43B6
	ldr r1, _080D42F0 @ =0x0000C206
	adds r0, r4, #0
	bl SetMotion
	b _080D4344
	.align 2, 0
_080D42F0: .4byte 0x0000C206
_080D42F4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	b _080D4330
_080D4302:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D43B6
	ldr r1, _080D4320 @ =0x0000C201
	adds r0, r4, #0
	bl SetMotion
	b _080D4344
	.align 2, 0
_080D4320: .4byte 0x0000C201
_080D4324:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
_080D4330:
	ands r0, r1
	cmp r0, #0
	beq _080D43B6
_080D4336:
	movs r1, #0xc2
	lsls r1, r1, #8
_080D433A:
	adds r0, r4, #0
	bl SetMotion
	movs r0, #6
	strb r0, [r4, #0x12]
_080D4344:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	b _080D43B6
_080D434C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D43B6
	ldr r1, _080D4390 @ =0x0000C206
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D436C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r2, #0
	ldr r0, [r4, #0x18]
	ldr r0, [r0, #4]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _080D4382
	movs r2, #1
_080D4382:
	cmp r2, #0
	beq _080D4394
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080D439A
	.align 2, 0
_080D4390: .4byte 0x0000C206
_080D4394:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080D439A:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
_080D43B6:
	pop {r4}
	pop {r0}
	bx r0
