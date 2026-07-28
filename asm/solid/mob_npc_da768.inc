	push {lr}
	ldr r2, _080DA788 @ =gCurStory
	ldrb r1, [r2, #6]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080DA798
	ldrb r0, [r2, #0x17]
	cmp r0, #2
	bhi _080DA790
	movs r0, #3
	strb r0, [r2, #0x17]
	ldr r0, _080DA78C @ =0x0000028A
	b _080DA7D0
	.align 2, 0
_080DA788: .4byte gCurStory
_080DA78C: .4byte 0x0000028A
_080DA790:
	ldr r0, _080DA794 @ =0x0000028B
	b _080DA7D0
	.align 2, 0
_080DA794: .4byte 0x0000028B
_080DA798:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DA7BC
	ldrb r0, [r2, #0x17]
	cmp r0, #1
	bhi _080DA7B2
	movs r0, #2
	strb r0, [r2, #0x17]
	movs r0, #0xa2
	lsls r0, r0, #2
	b _080DA7D0
_080DA7B2:
	ldr r0, _080DA7B8 @ =0x00000289
	b _080DA7D0
	.align 2, 0
_080DA7B8: .4byte 0x00000289
_080DA7BC:
	ldrb r0, [r2, #0x17]
	cmp r0, #0
	beq _080DA7CC
	ldr r0, _080DA7C8 @ =0x00000287
	b _080DA7D0
	.align 2, 0
_080DA7C8: .4byte 0x00000287
_080DA7CC:
	strb r3, [r2, #0x17]
	ldr r0, _080DA7D4 @ =0x00000286
_080DA7D0:
	pop {r1}
	bx r1
	.align 2, 0
_080DA7D4: .4byte 0x00000286

