.syntax unified
.thumb
glabel CountRodButton
	push {r4, lr}
	adds r3, r0, #0
	lsls r1, r1, #0x18
	cmp r1, #0
	beq _080338EC
	adds r0, r3, #0
	adds r0, #0xd9
	ldrb r0, [r0]
	cmp r0, #0
	beq _080338EC
	cmp r0, #1
	bne _080338EC
	ldr r1, _080338E8 @ =0x00000222
	b _080338F0
	.align 2, 0
_080338E8: .4byte 0x00000222
_080338EC:
	movs r1, #0x88
	lsls r1, r1, #2
_080338F0:
	adds r0, r3, r1
	ldrh r2, [r0]
	movs r4, #0
	movs r1, #0
	movs r0, #0xca
	lsls r0, r0, #1
	adds r3, r3, r0
_080338FE:
	lsls r0, r1, #1
	adds r0, r3, r0
	ldrh r0, [r0]
	ands r0, r2
	adds r1, #1
	cmp r0, #0
	beq _0803391E
	lsls r0, r1, #1
	adds r0, r3, r0
	ldrh r0, [r0]
	ands r0, r2
	cmp r0, #0
	bne _0803391E
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
_0803391E:
	lsls r0, r1, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x1f
	bls _080338FE
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1