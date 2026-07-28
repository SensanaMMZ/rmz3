	push {r4, lr}
	ldr r2, _080D2ED4 @ =gWindowRegBuffer
	ldrh r3, [r2]
	movs r4, #0x80
	lsls r4, r4, #7
	adds r1, r4, #0
	movs r4, #0
	orrs r1, r3
	strh r1, [r2]
	ldrb r3, [r2, #0xe]
	movs r1, #0xfe
	orrs r1, r3
	strb r1, [r2, #0xe]
	movs r3, #1
	strb r4, [r2, #0xd]
	strb r4, [r0, #0x12]
	ldr r2, _080D2ED8 @ =gSolidFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	str r3, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	str r1, [r0, #0x14]
	bl Actor_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080D2ED4: .4byte gWindowRegBuffer
_080D2ED8: .4byte gSolidFnTable
