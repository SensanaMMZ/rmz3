	push {r4, r5, r6, lr}
	adds r3, r0, #0
	ldr r0, [r3, #0x28]
	ldr r1, _080E7BCC @ =0x00000DFC
	adds r0, r0, r1
	ldrb r1, [r3, #0x11]
	adds r0, r0, r1
	ldrb r4, [r0]
	cmp r4, #0xff
	beq _080E7C38
	ldr r1, _080E7BD0 @ =gElfBreedInfo
	lsls r2, r4, #2
	adds r0, r2, r1
	ldrb r5, [r0]
	lsls r0, r5, #0x19
	adds r6, r1, #0
	cmp r0, #0
	bge _080E7BE0
	lsrs r0, r5, #7
	cmp r0, #0
	beq _080E7BD8
	ldr r1, _080E7BD4 @ =0x00005311
	b _080E7C2A
	.align 2, 0
_080E7BCC: .4byte 0x00000DFC
_080E7BD0: .4byte gElfBreedInfo
_080E7BD4: .4byte 0x00005311
_080E7BD8:
	ldr r1, _080E7BDC @ =0x00005308
	b _080E7C2A
	.align 2, 0
_080E7BDC: .4byte 0x00005308
_080E7BE0:
	ldr r0, _080E7C04 @ =gUnlockedElfPtr
	ldr r0, [r0]
	adds r0, r0, r4
	ldrb r1, [r0]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080E7C14
	lsls r0, r5, #0x1a
	lsrs r0, r0, #0x1d
	cmp r0, #1
	bne _080E7C14
	lsls r0, r5, #0x18
	cmp r0, #0
	bge _080E7C0C
	ldr r1, _080E7C08 @ =0x00005311
	b _080E7C2A
	.align 2, 0
_080E7C04: .4byte gUnlockedElfPtr
_080E7C08: .4byte 0x00005311
_080E7C0C:
	ldr r1, _080E7C10 @ =0x00005308
	b _080E7C2A
	.align 2, 0
_080E7C10: .4byte 0x00005308
_080E7C14:
	adds r0, r2, r6
	ldrb r0, [r0]
	lsrs r0, r0, #7
	cmp r0, #0
	beq _080E7C28
	ldr r1, _080E7C24 @ =0x00005310
	b _080E7C2A
	.align 2, 0
_080E7C24: .4byte 0x00005310
_080E7C28:
	ldr r1, _080E7C34 @ =0x00005307
_080E7C2A:
	adds r0, r3, #0
	bl SetMotion
	b _080E7C40
	.align 2, 0
_080E7C34: .4byte 0x00005307
_080E7C38:
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r3, #0xa]
_080E7C40:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
