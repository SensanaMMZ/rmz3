	push {r4, r5, lr}
	adds r3, r0, #0
	ldr r0, [r3, #0x28]
	ldr r2, _080E7AE0 @ =0x000064AC
	adds r1, r0, r2
	ldr r1, [r1]
	ldr r2, _080E7AE4 @ =0x00000DFC
	adds r0, r0, r2
	ldrb r2, [r3, #0x11]
	adds r0, r0, r2
	ldrb r2, [r0]
	cmp r2, #0xff
	beq _080E7B8C
	ldr r0, _080E7AE8 @ =gUnlockedElfPtr
	ldr r0, [r0]
	adds r4, r0, r2
	ldrb r5, [r4]
	movs r0, #2
	ands r0, r5
	cmp r0, #0
	beq _080E7AF0
	ldr r1, _080E7AEC @ =0x00005302
	b _080E7B7E
	.align 2, 0
_080E7AE0: .4byte 0x000064AC
_080E7AE4: .4byte 0x00000DFC
_080E7AE8: .4byte gUnlockedElfPtr
_080E7AEC: .4byte 0x00005302
_080E7AF0:
	adds r1, #0xb4
	ldrb r0, [r1]
	cmp r0, r2
	bne _080E7B00
	ldr r1, _080E7AFC @ =0x00005301
	b _080E7B7E
	.align 2, 0
_080E7AFC: .4byte 0x00005301
_080E7B00:
	ldrb r0, [r1, #1]
	cmp r0, r2
	bne _080E7B10
	ldr r1, _080E7B0C @ =0x0000530F
	b _080E7B7E
	.align 2, 0
_080E7B0C: .4byte 0x0000530F
_080E7B10:
	ldr r1, _080E7B34 @ =gElfBreedInfo
	lsls r0, r2, #2
	adds r0, r0, r1
	ldrb r2, [r0]
	lsls r1, r2, #0x1d
	lsrs r1, r1, #0x1d
	ldr r0, [r4]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	subs r0, r1, r0
	cmp r0, #1
	beq _080E7B72
	cmp r0, #1
	bgt _080E7B38
	cmp r0, #0
	beq _080E7B3E
	b _080E7B94
	.align 2, 0
_080E7B34: .4byte gElfBreedInfo
_080E7B38:
	cmp r0, #2
	beq _080E7B7C
	b _080E7B94
_080E7B3E:
	lsls r1, r2, #0x1a
	lsrs r0, r1, #0x1d
	cmp r0, #1
	bne _080E7B50
	ldr r1, _080E7B4C @ =0x00005303
	b _080E7B7E
	.align 2, 0
_080E7B4C: .4byte 0x00005303
_080E7B50:
	lsrs r0, r1, #0x1d
	cmp r0, #2
	bne _080E7B6C
	movs r0, #4
	ands r0, r5
	cmp r0, #0
	beq _080E7B64
	movs r1, #0xa6
	lsls r1, r1, #7
	b _080E7B7E
_080E7B64:
	ldr r1, _080E7B68 @ =0x00005306
	b _080E7B7E
	.align 2, 0
_080E7B68: .4byte 0x00005306
_080E7B6C:
	movs r1, #0xa6
	lsls r1, r1, #7
	b _080E7B7E
_080E7B72:
	ldr r1, _080E7B78 @ =0x00005304
	b _080E7B7E
	.align 2, 0
_080E7B78: .4byte 0x00005304
_080E7B7C:
	ldr r1, _080E7B88 @ =0x00005305
_080E7B7E:
	adds r0, r3, #0
	bl SetMotion
	b _080E7B94
	.align 2, 0
_080E7B88: .4byte 0x00005305
_080E7B8C:
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r3, #0xa]
_080E7B94:
	pop {r4, r5}
	pop {r0}
	bx r0
