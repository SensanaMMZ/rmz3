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

	thumb_func_start FUN_08050e44
FUN_08050e44: @ 0x08050E44
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _08050E56
	cmp r1, #1
	beq _08050EC4
	b _08050F2C
_08050E56:
	ldrb r0, [r4, #0xb]
	movs r7, #0x10
	movs r6, #0
	orrs r0, r7
	strb r0, [r4, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r4, #0x1d]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _08050EAE
	ldrb r0, [r4, #0xa]
	orrs r0, r7
	b _08050EB4
_08050EAE:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08050EB4:
	strb r0, [r4, #0xa]
	ldr r1, _08050ED8 @ =0x0000AF07
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050EC4:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _08050EDC
	movs r0, #0xf6
	b _08050EDE
	.align 2, 0
_08050ED8: .4byte 0x0000AF07
_08050EDC:
	movs r0, #0xfa
_08050EDE:
	muls r0, r1, r0
	cmp r0, #0
	bge _08050EE6
	adds r0, #0xff
_08050EE6:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_0801779c
	ldrb r0, [r5, #0xc]
	cmp r0, #4
	bne _08050F2C
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08050F34 @ =gBossFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08050F2C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08050F34: .4byte gBossFnTable
