	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start anubisMode8
anubisMode8: @ 0x08050CFC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08050D10
	cmp r0, #1
	beq _08050D34
	b _08050E0C
_08050D10:
	movs r0, #0x53
	bl PlaySound
	movs r0, #0x3c
	strb r0, [r5, #0x12]
	ldr r1, _08050E18 @ =0x0000AF03
	adds r0, r5, #0
	bl SetMotion
	adds r2, r5, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #0x80
	orrs r0, r1
	str r0, [r2]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050D34:
	ldrb r0, [r5, #0x12]
	movs r1, #0xc0
	adds r1, r1, r5
	mov r8, r1
	cmp r0, #0
	beq _08050DF4
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08050DF4
	movs r4, #0xbe
	lsls r4, r4, #3
	ldr r2, _08050E1C @ =gStaticMotionGraphics
	adds r0, r4, r2
	ldr r1, _08050E20 @ =wStaticGraphicTilenums
	adds r1, #0x98
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _08050E24 @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldr r0, _08050E28 @ =wStaticMotionPalIDs
	adds r0, #0x98
	ldrh r1, [r0]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	ldr r2, _08050E2C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08050E30 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08050E34 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #1
	ands r1, r0
	adds r0, r1, #1
	cmp r0, #0
	beq _08050DEE
	movs r7, #0
	adds r6, r0, #0
_08050DA8:
	ldr r0, _08050E38 @ =pZero2
	ldr r0, [r0]
	ldr r4, [r0, #0x54]
	ldr r2, _08050E3C @ =0xFFFFCE00
	adds r4, r4, r2
	adds r4, r4, r7
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r2, _08050E40 @ =0xFFFF9000
	adds r1, r0, r2
	cmp r4, r1
	bge _08050DC4
	adds r4, r1, #0
_08050DC4:
	movs r1, #0xe0
	lsls r1, r1, #7
	adds r0, r0, r1
	cmp r4, r0
	ble _08050DD0
	adds r4, r0, #0
_08050DD0:
	ldr r1, [r5, #0x58]
	adds r0, r4, #0
	bl FUN_08009f6c
	adds r2, r0, #0
	adds r0, r5, #0
	adds r1, r4, #0
	bl createPantheonZombie
	movs r2, #0xc8
	lsls r2, r2, #7
	adds r7, r7, r2
	subs r6, #1
	cmp r6, #0
	bne _08050DA8
_08050DEE:
	movs r0, #0x55
	bl PlaySound
_08050DF4:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	mov r0, r8
	ldr r1, [r0]
	movs r0, #0x80
	ands r1, r0
	cmp r1, #0
	bne _08050E0C
	movs r0, #1
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08050E0C:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08050E18: .4byte 0x0000AF03
_08050E1C: .4byte gStaticMotionGraphics
_08050E20: .4byte wStaticGraphicTilenums
_08050E24: .4byte gStaticMotionGraphics+12
_08050E28: .4byte wStaticMotionPalIDs
_08050E2C: .4byte RNG_0202f388
_08050E30: .4byte 0x000343FD
_08050E34: .4byte 0x00269EC3
_08050E38: .4byte pZero2
_08050E3C: .4byte 0xFFFFCE00
_08050E40: .4byte 0xFFFF9000
