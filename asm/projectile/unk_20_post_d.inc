	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a57ac
FUN_080a57ac: @ 0x080A57AC
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r7, [r5, #0x28]
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _080A57E2
	cmp r0, #1
	bgt _080A57C2
	cmp r0, #0
	beq _080A57CC
	b _080A5946
_080A57C2:
	cmp r0, #2
	beq _080A5870
	cmp r0, #3
	beq _080A588C
	b _080A5946
_080A57CC:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A5818 @ =0x0836BAB8
	bl SetDDP
	movs r0, #0xb0
	lsls r0, r0, #2
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A57E2:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _080A5820
	ldr r0, [r5, #0x54]
	ldr r1, _080A581C @ =0xFFFFF000
	adds r0, r0, r1
	movs r4, #0x80
	lsls r4, r4, #5
	adds r1, r2, r4
	bl PushoutToUp1
	adds r6, r0, #0
	ldr r0, [r5, #0x54]
	adds r0, r0, r4
	ldr r1, [r5, #0x58]
	adds r1, r1, r4
	bl PushoutToUp1
	adds r2, r0, #0
	cmp r6, #0
	bne _080A5850
	cmp r2, #0
	beq _080A5856
	b _080A5850
	.align 2, 0
_080A5818: .4byte 0x0836BAB8
_080A581C: .4byte 0xFFFFF000
_080A5820:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A583A
	ldr r0, [r5, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	adds r1, r2, r1
	bl PushoutToLeft1
	b _080A584A
_080A583A:
	ldr r0, [r5, #0x54]
	ldr r3, _080A586C @ =0xFFFFF000
	adds r0, r0, r3
	movs r3, #0x80
	lsls r3, r3, #5
	adds r1, r2, r3
	bl PushoutToRight1
_080A584A:
	adds r6, r0, #0
	cmp r6, #0
	bne _080A5856
_080A5850:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A5856:
	ldrb r0, [r5, #0x12]
	adds r0, #0x10
	strb r0, [r5, #0x12]
	adds r1, r5, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080A5946
	.align 2, 0
_080A586C: .4byte 0xFFFFF000
_080A5870:
	ldr r0, _080A58B8 @ =0xFFFFFD40
	str r0, [r5, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A5884
	movs r2, #0xb0
	lsls r2, r2, #2
_080A5884:
	str r2, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A588C:
	ldr r1, [r5, #0x54]
	ldr r0, [r5, #0x5c]
	adds r2, r1, r0
	str r2, [r5, #0x54]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A58C0
	movs r4, #0x80
	lsls r4, r4, #5
	adds r0, r2, r4
	ldr r1, [r5, #0x58]
	adds r1, r1, r4
	bl FUN_08009f6c
	adds r6, r0, #0
	ldr r0, [r5, #0x54]
	ldr r1, _080A58BC @ =0xFFFFF000
	adds r0, r0, r1
	b _080A58D6
	.align 2, 0
_080A58B8: .4byte 0xFFFFFD40
_080A58BC: .4byte 0xFFFFF000
_080A58C0:
	ldr r3, _080A58F0 @ =0xFFFFF000
	adds r0, r2, r3
	ldr r1, [r5, #0x58]
	movs r4, #0x80
	lsls r4, r4, #5
	adds r1, r1, r4
	bl FUN_08009f6c
	adds r6, r0, #0
	ldr r0, [r5, #0x54]
	adds r0, r0, r4
_080A58D6:
	ldr r1, [r5, #0x58]
	adds r1, r1, r4
	bl FUN_08009f6c
	adds r2, r0, #0
	ldr r0, [r5, #0x58]
	subs r3, r6, r0
	ldr r1, _080A58F4 @ =0xFFFFE800
	adds r4, r0, #0
	cmp r3, r1
	bge _080A58FC
	ldr r0, _080A58F8 @ =0xFFFFFD40
	b _080A590E
	.align 2, 0
_080A58F0: .4byte 0xFFFFF000
_080A58F4: .4byte 0xFFFFE800
_080A58F8: .4byte 0xFFFFFD40
_080A58FC:
	movs r1, #0xc0
	lsls r1, r1, #5
	cmp r3, r1
	ble _080A5916
	subs r0, r2, r4
	cmp r0, r1
	ble _080A5916
	movs r0, #0xb0
	lsls r0, r0, #2
_080A590E:
	str r0, [r5, #0x60]
	movs r0, #1
	strb r0, [r5, #0xe]
	b _080A5934
_080A5916:
	ldr r0, [r5, #0x54]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r1, r4, r2
	bl FUN_08009f6c
	adds r6, r0, #0
	ldr r0, [r5, #0x58]
	subs r0, r6, r0
	ldr r1, _080A5980 @ =0x000017FF
	cmp r0, r1
	bgt _080A5934
	ldr r3, _080A5984 @ =0xFFFFF000
	adds r0, r6, r3
	str r0, [r5, #0x58]
_080A5934:
	ldrb r0, [r5, #0x12]
	adds r0, #0x10
	strb r0, [r5, #0x12]
	adds r1, r5, #0
	adds r1, #0x24
	strb r0, [r1]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080A5946:
	adds r0, r7, #0
	adds r0, #0xb8
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	subs r2, r1, r0
	ldr r0, _080A5988 @ =0xFFFFA800
	cmp r2, r0
	bge _080A5960
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A5972
_080A5960:
	movs r0, #0xb0
	lsls r0, r0, #7
	cmp r2, r0
	ble _080A597A
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A597A
_080A5972:
	movs r1, #0
	movs r0, #4
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080A597A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A5980: .4byte 0x000017FF
_080A5984: .4byte 0xFFFFF000
_080A5988: .4byte 0xFFFFA800
