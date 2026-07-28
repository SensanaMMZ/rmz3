	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080ce7a4
FUN_080ce7a4: @ 0x080CE7A4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080CE7B4
	cmp r5, #1
	beq _080CE7CE
	b _080CE7FE
_080CE7B4:
	ldr r0, _080CE804 @ =0x0000010B
	bl PlaySound
	ldr r1, _080CE808 @ =0x00005501
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x40
	strb r0, [r4, #0x12]
	str r5, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CE7CE:
	ldr r1, [r4, #0x5c]
	adds r1, #4
	str r1, [r4, #0x5c]
	adds r2, r4, #0
	adds r2, #0xb4
	ldrh r0, [r2]
	adds r0, r0, r1
	strh r0, [r2]
	adds r0, r4, #0
	bl FUN_080ce538
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080CE7FE
	movs r0, #2
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_080CE7FE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CE804: .4byte 0x0000010B
_080CE808: .4byte 0x00005501

