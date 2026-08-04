	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start deathtanz_0804adb0
deathtanz_0804adb0: @ 0x0804ADB0
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _0804ADBE
	b _0804AFD2
_0804ADBE:
	lsls r0, r0, #2
	ldr r1, _0804ADC8 @ =_0804ADCC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804ADC8: .4byte _0804ADCC
_0804ADCC: @ jump table
	.4byte _0804ADE0 @ case 0
	.4byte _0804AF32 @ case 1
	.4byte _0804AFAA @ case 2
	.4byte _0804AFBA @ case 3
	.4byte _0804AFD2 @ case 4
_0804ADE0:
	movs r6, #0
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #1
	ands r0, r1
	adds r5, r2, #0
	cmp r0, #0
	beq _0804AE28
	movs r6, #1
	ldr r3, [r4, #0x54]
	ldr r1, _0804AF50 @ =0xFFFFD600
	adds r0, r3, r1
	str r0, [sp]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804AE0E
	movs r0, #0xb0
	lsls r0, r0, #6
	adds r2, r3, r0
_0804AE0E:
	str r2, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AF54 @ =0xFFFFE700
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bdb44
_0804AE28:
	ldrb r1, [r5]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0804AE50
	movs r6, #1
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AF58 @ =0xFFFFB400
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bdb44
_0804AE50:
	cmp r6, #0
	beq _0804AE5A
	movs r0, #0x2a
	bl PlaySound
_0804AE5A:
	movs r0, #0x2f
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xc2
	ldrb r6, [r0]
	ldr r0, _0804AF5C @ =gBossHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0804AEC2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _0804AF60 @ =gBossFnTable
	movs r0, #7
	strb r0, [r3, #9]
	ldr r0, [r1, #0x1c]
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
_0804AEC2:
	ldr r1, _0804AF64 @ =0x0000A738
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
	ldr r3, _0804AF68 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _0804AF04
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _0804AF04
	ldr r0, _0804AF6C @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0804AF04:
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0804AF70 @ =0xFFFFE000
	adds r0, r0, r1
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
_0804AF32:
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x5c]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xc2
	ldrb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804AF74
	cmp r3, #1
	bne _0804AF78
	b _0804AF7C
	.align 2, 0
_0804AF50: .4byte 0xFFFFD600
_0804AF54: .4byte 0xFFFFE700
_0804AF58: .4byte 0xFFFFB400
_0804AF5C: .4byte gBossHeaderPtr
_0804AF60: .4byte gBossFnTable
_0804AF64: .4byte 0x0000A738
_0804AF68: .4byte gStageRun
_0804AF6C: .4byte 0x0000FFFE
_0804AF70: .4byte 0xFFFFE000
_0804AF74:
	cmp r3, #0
	beq _0804AF7C
_0804AF78:
	movs r0, #0xfa
	b _0804AF7E
_0804AF7C:
	movs r0, #0xf6
_0804AF7E:
	muls r0, r2, r0
	cmp r0, #0
	bge _0804AF86
	adds r0, #0xff
_0804AF86:
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
	beq _0804AFA2
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AFA2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0804AFD2
_0804AFAA:
	ldr r1, _0804AFDC @ =sExplosionCoords+8
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AFBA:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0804AFD2
	ldr r2, _0804AFE0 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804AFD2:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804AFDC: .4byte sExplosionCoords+8
_0804AFE0: .4byte gStageRun
