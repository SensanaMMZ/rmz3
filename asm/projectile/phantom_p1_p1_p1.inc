	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080af368
FUN_080af368: @ 0x080AF368
	push {r4, r5, r6, r7, lr}
	adds r3, r0, #0
	ldr r0, [r3, #0x28]
	ldr r6, [r0, #0x54]
	ldr r7, [r0, #0x58]
	ldrb r0, [r0, #0xa]
	lsrs r4, r0, #4
	movs r0, #1
	ands r4, r0
	adds r2, r4, #0
	cmp r2, #0
	beq _080AF388
	ldrb r1, [r3, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080AF38E
_080AF388:
	ldrb r1, [r3, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AF38E:
	strb r0, [r3, #0xa]
	movs r5, #1
	adds r1, r5, #0
	ands r1, r2
	adds r0, r3, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r3
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r4, #0
	bne _080AF3BC
	movs r0, #1
_080AF3BC:
	lsls r0, r0, #0xc
	adds r0, r6, r0
	str r0, [r3, #0x54]
	ldr r1, _080AF3E4 @ =0xFFFFE400
	adds r0, r7, r1
	str r0, [r3, #0x58]
	adds r0, r3, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080AF3DC
	strb r5, [r3, #0xd]
	ldr r1, _080AF3E8 @ =0x00008601
	adds r0, r3, #0
	bl SetMotion
_080AF3DC:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AF3E4: .4byte 0xFFFFE400
_080AF3E8: .4byte 0x00008601

