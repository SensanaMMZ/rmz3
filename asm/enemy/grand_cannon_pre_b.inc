	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start grandcannonBombShot
grandcannonBombShot: @ 0x08069560
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08069572
	cmp r0, #1
	beq _080695DC
	b _080695F6
_08069572:
	movs r0, #0x2d
	bl PlaySound
	adds r0, r5, #0
	adds r0, #0x24
	ldrb r0, [r0]
	adds r0, #0x80
	lsls r0, r0, #0x18
	ldr r2, [r5, #0x54]
	str r2, [sp]
	ldr r3, _08069600 @ =gSineTable
	lsrs r4, r0, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x17
	adds r0, r0, r1
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r6, #0
	ldrsh r1, [r0, r6]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	str r0, [sp]
	ldr r2, [r5, #0x58]
	str r2, [sp, #4]
	lsls r0, r4, #1
	adds r0, r0, r3
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	str r0, [sp, #4]
	movs r0, #0x2d
	bl PlaySound
	movs r1, #0xa0
	lsls r1, r1, #3
	mov r0, sp
	adds r2, r4, #0
	bl CreateGrandCannonBomb
	movs r0, #4
	strb r0, [r5, #0x12]
	ldr r1, _08069604 @ =0x00000704
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080695DC:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080695F6
	movs r0, #1
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080695F6:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08069600: .4byte gSineTable
_08069604: .4byte 0x00000704
