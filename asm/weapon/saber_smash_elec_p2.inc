	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start SmashElec_Init
SmashElec_Init: @ 0x0803C8C8
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	adds r7, r0, #0
	ldr r0, [r7, #0x28]
	mov r8, r0
	ldr r1, _0803C970 @ =gWeaponFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl InitNonAffineMotion
	adds r0, r7, #0
	bl ResetDynamicMotion
	ldrb r1, [r7, #0xb]
	movs r0, #0xfb
	ands r0, r1
	movs r6, #0
	strb r0, [r7, #0xb]
	movs r0, #0
	strh r6, [r7, #0x20]
	adds r1, r7, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r0, [r7, #0xa]
	movs r1, #1
	movs r2, #0
	mov sb, r2
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0803C974 @ =0x00001A06
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r7, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r5, _0803C978 @ =0x083616E0
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	adds r1, r5, #0
	movs r3, #1
	bl InitBody
	str r7, [r4, #0x2c]
	str r6, [r4, #0x24]
	mov r0, r8
	bl CalcSaberBonus
	adds r2, r0, #0
	adds r2, #8
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	movs r3, #1
	rsbs r3, r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	adds r0, r4, #0
	adds r1, r5, #0
	bl InitWeaponBody
	ldrb r2, [r7, #0x10]
	cmp r2, #0
	beq _0803C97C
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0803C982
	.align 2, 0
_0803C970: .4byte gWeaponFnTable
_0803C974: .4byte 0x00001A06
_0803C978: .4byte 0x083616E0
_0803C97C:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_0803C982:
	strb r0, [r7, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r7, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0803C9B0
	movs r0, #0x80
	lsls r0, r0, #3
	b _0803C9B2
_0803C9B0:
	ldr r0, _0803C9D0 @ =0xFFFFFC00
_0803C9B2:
	str r0, [r7, #0x5c]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	bl FUN_08009f6c
	adds r3, r0, #0
	ldr r1, [r7, #0x58]
	subs r2, r3, r1
	cmp r2, #0
	blt _0803C9D4
	movs r0, #0xf0
	lsls r0, r0, #4
	cmp r2, r0
	bgt _0803C9DE
	b _0803CA1C
	.align 2, 0
_0803C9D0: .4byte 0xFFFFFC00
_0803C9D4:
	subs r1, r1, r3
	movs r0, #0xf0
	lsls r0, r0, #4
	cmp r1, r0
	ble _0803CA1C
_0803C9DE:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0803CA18 @ =gWeaponFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
	b _0803CA30
	.align 2, 0
_0803CA18: .4byte gWeaponFnTable
_0803CA1C:
	str r3, [r7, #0x58]
	movs r0, #0xff
	strb r0, [r7, #0x12]
	ldr r1, _0803CA40 @ =onCollision
	adds r0, r7, #0
	adds r0, #0x74
	str r1, [r0, #0x24]
	adds r0, r7, #0
	bl SmashElec_Update
_0803CA30:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0803CA40: .4byte onCollision

	thumb_func_start SmashElec_Update
SmashElec_Update: @ 0x0803CA44
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _0803CA94
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	adds r3, r0, #0
	ldr r1, [r4, #0x58]
	subs r2, r3, r1
	cmp r2, #0
	blt _0803CA7A
	movs r0, #0xf0
	lsls r0, r0, #4
	cmp r2, r0
	bgt _0803CA94
	b _0803CA84
_0803CA7A:
	subs r1, r1, r3
	movs r0, #0xf0
	lsls r0, r0, #4
	cmp r1, r0
	bgt _0803CA94
_0803CA84:
	str r3, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0803CAB4
_0803CA94:
	ldr r1, _0803CAB0 @ =gWeaponFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl SmashElec_Die
	b _0803CADE
	.align 2, 0
_0803CAB0: .4byte gWeaponFnTable
_0803CAB4:
	ldr r0, _0803CAE4 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	bls _0803CADE
	ldr r1, _0803CAE8 @ =gWeaponFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl SmashElec_Die
_0803CADE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0803CAE4: .4byte gStageRun+232
_0803CAE8: .4byte gWeaponFnTable

	thumb_func_start SmashElec_Die
SmashElec_Die: @ 0x0803CAEC
	push {lr}
	adds r2, r0, #0
	ldr r0, [r2, #0x28]
	movs r3, #0x9d
	lsls r3, r3, #1
	adds r1, r0, r3
	ldrb r0, [r1]
	cmp r0, #0
	beq _0803CB02
	subs r0, #1
	strb r0, [r1]
_0803CB02:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0
	strb r0, [r2, #0xa]
	adds r0, r2, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _0803CB38 @ =gWeaponFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r2, #0x14]
	pop {r0}
	bx r0
	.align 2, 0
_0803CB38: .4byte gWeaponFnTable
