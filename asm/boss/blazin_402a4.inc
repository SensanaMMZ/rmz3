	push {r4, lr}
	sub sp, #0x10
	adds r2, r0, #0
	movs r3, #0x54
	ldrb r1, [r2, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080402B8
	movs r3, #0xac
_080402B8:
	ldr r1, _080402F4 @ =gSineTable
	lsls r0, r3, #1
	adds r0, r0, r1
	movs r4, #0
	ldrsh r0, [r0, r4]
	str r0, [sp]
	adds r0, r3, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	rsbs r0, r0, #0
	str r0, [sp, #4]
	ldr r0, [r2, #0x54]
	str r0, [sp, #8]
	ldr r0, [r2, #0x58]
	add r1, sp, #8
	ldr r3, _080402F8 @ =0xFFFFF800
	adds r0, r0, r3
	str r0, [r1, #4]
	adds r0, r2, #0
	mov r2, sp
	bl blazin_0809e620
	add sp, #0x10
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080402F4: .4byte gSineTable
_080402F8: .4byte 0xFFFFF800

