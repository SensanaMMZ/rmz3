	push {lr}
	adds r3, r0, #0
	ldr r0, _080F5450 @ =0x00000E17
	adds r2, r3, r0
	ldrb r1, [r2]
	cmp r1, #0
	beq _080F5454
	cmp r1, #1
	beq _080F545A
	b _080F549C
	.align 2, 0
_080F5450: .4byte 0x00000E17
_080F5454:
	movs r0, #1
	strb r0, [r2]
	b _080F549C
_080F545A:
	ldr r0, _080F5480 @ =gJoypad
	ldrh r2, [r0, #4]
	ands r1, r2
	cmp r1, #0
	beq _080F548C
	ldr r2, _080F5484 @ =gStageRun
	ldrh r1, [r2, #8]
	ldr r0, _080F5488 @ =0x0000FFFE
	ands r0, r1
	movs r1, #0x20
	orrs r0, r1
	strh r0, [r2, #8]
	movs r0, #3
	strb r0, [r3, #1]
	strb r0, [r3, #2]
	movs r0, #2
	bl PlaySound
	b _080F549C
	.align 2, 0
_080F5480: .4byte gJoypad
_080F5484: .4byte gStageRun
_080F5488: .4byte 0x0000FFFE
_080F548C:
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	beq _080F549C
	strb r1, [r3, #3]
	movs r0, #3
	bl PlaySound
_080F549C:
	pop {r0}
	bx r0
