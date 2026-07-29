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

	thumb_func_start anubis_08050f38
anubis_08050f38: @ 0x08050F38
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08050F84
	cmp r0, #1
	bgt _08050F4C
	cmp r0, #0
	beq _08050F56
	b _08051002
_08050F4C:
	cmp r0, #2
	beq _08050FA4
	cmp r0, #3
	beq _08050FDE
	b _08051002
_08050F56:
	movs r0, #0x53
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0xcf
	movs r0, #2
	strb r0, [r1]
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #1
	orrs r0, r1
	str r0, [r2]
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldr r1, _08050FA0 @ =0x0000AF03
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050F84:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08050F96
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050F96:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08051002
	.align 2, 0
_08050FA0: .4byte 0x0000AF03
_08050FA4:
	adds r0, r4, #0
	adds r0, #0xce
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	beq _08050FB4
	movs r0, #0
	b _08050FD0
_08050FB4:
	ldr r2, _08051008 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805100C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08051010 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
	adds r0, #1
_08050FD0:
	strb r0, [r5]
	ldrb r0, [r5]
	bl FUN_08010188
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050FDE:
	bl FUN_080101a8
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, #0
	bne _08050FFC
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	ldr r1, _08051014 @ =0xFFFFFEFF
	ands r0, r1
	str r0, [r2]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r3, [r4, #0xe]
_08050FFC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08051002:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08051008: .4byte RNG_0202f388
_0805100C: .4byte 0x000343FD
_08051010: .4byte 0x00269EC3
_08051014: .4byte 0xFFFFFEFF

	thumb_func_start anubis_08051018
anubis_08051018: @ 0x08051018
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bhi _080510E0
	lsls r0, r0, #2
	ldr r1, _0805102C @ =_08051030
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0805102C: .4byte _08051030
_08051030: @ jump table
	.4byte _08051044 @ case 0
	.4byte _08051090 @ case 1
	.4byte _080510B8 @ case 2
	.4byte _080510C8 @ case 3
	.4byte _080510E0 @ case 4
_08051044:
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r3, _080510AC @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _0805107E
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _0805107E
	ldr r0, _080510B0 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0805107E:
	movs r0, #0x50
	strb r0, [r4, #0x12]
	ldr r1, _080510B4 @ =0x0000AF04
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051090:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _080510E0
	b _080510DA
	.align 2, 0
_080510AC: .4byte gStageRun
_080510B0: .4byte 0x0000FFFE
_080510B4: .4byte 0x0000AF04
_080510B8:
	ldr r1, _080510E8 @ =0x083635DC
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080510C8:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080510E0
	ldr r2, _080510EC @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
_080510DA:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080510E0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080510E8: .4byte 0x083635DC
_080510EC: .4byte gStageRun

	thumb_func_start anubis_080510f0
anubis_080510f0: @ 0x080510F0
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _080510FE
	b _08051286
_080510FE:
	lsls r0, r0, #2
	ldr r1, _08051108 @ =_0805110C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08051108: .4byte _0805110C
_0805110C: @ jump table
	.4byte _08051120 @ case 0
	.4byte _080511F4 @ case 1
	.4byte _0805125E @ case 2
	.4byte _0805126E @ case 3
	.4byte _08051286 @ case 4
_08051120:
	movs r0, #0x2f
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xcc
	ldrb r6, [r0]
	ldr r0, _08051214 @ =gBossHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08051188
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _08051218 @ =gBossFnTable
	movs r0, #0xb
	strb r0, [r3, #9]
	ldr r0, [r1, #0x2c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r3, #0x5c]
	str r4, [r3, #0x28]
	movs r1, #1
	strb r1, [r3, #0x10]
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	ands r0, r1
	eors r0, r6
	strb r0, [r3, #0x13]
_08051188:
	ldr r1, _0805121C @ =0x0000AF06
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r3, _08051220 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _080511CA
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _080511CA
	ldr r0, _08051224 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_080511CA:
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	str r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r0, #0x32
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080511F4:
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x5c]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xcc
	ldrb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08051228
	cmp r3, #1
	bne _0805122C
	b _08051230
	.align 2, 0
_08051214: .4byte gBossHeaderPtr
_08051218: .4byte gBossFnTable
_0805121C: .4byte 0x0000AF06
_08051220: .4byte gStageRun
_08051224: .4byte 0x0000FFFE
_08051228:
	cmp r3, #0
	beq _08051230
_0805122C:
	movs r0, #0xfa
	b _08051232
_08051230:
	movs r0, #0xf6
_08051232:
	muls r0, r2, r0
	cmp r0, #0
	bge _0805123A
	adds r0, #0xff
_0805123A:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _08051256
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051256:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08051286
_0805125E:
	ldr r1, _08051290 @ =0x083635E4
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805126E:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08051286
	ldr r2, _08051294 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051286:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08051290: .4byte 0x083635E4
_08051294: .4byte gStageRun
