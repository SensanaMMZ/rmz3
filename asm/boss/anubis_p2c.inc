	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start anubisMode6
anubisMode6: @ 0x08050B74
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08050B84
	cmp r0, #1
	beq _08050BFE
	b _08050C62
_08050B84:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r4, _08050C24 @ =0x000005DC
	ldr r1, _08050C28 @ =gStaticMotionGraphics
	adds r0, r4, r1
	ldr r1, _08050C2C @ =wStaticGraphicTilenums
	adds r1, #0x96
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _08050C30 @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldr r0, _08050C34 @ =wStaticMotionPalIDs
	adds r0, #0x96
	ldrh r1, [r0]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	ldr r3, _08050C38 @ =0x083635C9
	ldr r2, _08050C3C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08050C40 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08050C44 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #7
	ands r1, r0
	adds r0, r5, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r0, [r0, r2]
	cmp r0, #0x1f
	bgt _08050BEE
	adds r1, #8
_08050BEE:
	adds r0, r1, r3
	ldrb r0, [r0]
	strb r0, [r5, #0x12]
	movs r0, #0x1e
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050BFE:
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08050C62
	movs r0, #0x60
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08050C48
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
	b _08050C4C
	.align 2, 0
_08050C24: .4byte 0x000005DC
_08050C28: .4byte gStaticMotionGraphics
_08050C2C: .4byte wStaticGraphicTilenums
_08050C30: .4byte gStaticMotionGraphics+12
_08050C34: .4byte wStaticMotionPalIDs
_08050C38: .4byte 0x083635C9
_08050C3C: .4byte RNG_0202f388
_08050C40: .4byte 0x000343FD
_08050C44: .4byte 0x00269EC3
_08050C48:
	movs r0, #1
	strb r0, [r5, #0xe]
_08050C4C:
	movs r0, #0x55
	bl PlaySound
	movs r1, #0
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _08050C5C
	movs r1, #1
_08050C5C:
	adds r0, r5, #0
	bl CreateAnubisCoffins
_08050C62:
	pop {r4, r5}
	pop {r0}
	bx r0
