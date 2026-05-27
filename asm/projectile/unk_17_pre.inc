	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a2790
FUN_080a2790: @ 0x080A2790
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _080A27DC @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A27D4
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A27E0 @ =gProjectileFnTable
	movs r0, #0x11
	strb r0, [r3, #9]
	ldr r0, [r1, #0x44]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r5, [r3, #0x10]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	movs r0, #1
	strb r0, [r3, #0x11]
_080A27D4:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080A27DC: .4byte gProjectileHeaderPtr
_080A27E0: .4byte gProjectileFnTable

	thumb_func_start FUN_080a27e4
FUN_080a27e4: @ 0x080A27E4
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _080A2830 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A2828
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A2834 @ =gProjectileFnTable
	movs r0, #0x11
	strb r0, [r3, #9]
	ldr r0, [r1, #0x44]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r5, [r3, #0x10]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	movs r0, #2
	strb r0, [r3, #0x11]
_080A2828:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080A2830: .4byte gProjectileHeaderPtr
_080A2834: .4byte gProjectileFnTable

	thumb_func_start FUN_080a2838
FUN_080a2838: @ 0x080A2838
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r4, r1, #0
	adds r5, r2, #0
	lsls r3, r3, #0x18
	lsrs r6, r3, #0x18
	ldr r0, _080A2890 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080A2888
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A2894 @ =gProjectileFnTable
	movs r0, #0x11
	strb r0, [r3, #9]
	ldr r0, [r1, #0x44]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r1, #0
	strh r2, [r3, #0x20]
	adds r0, r3, #0
	adds r0, #0x22
	strb r1, [r0]
	strb r6, [r3, #0x10]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	ldr r0, [r5]
	str r0, [r3, #0x64]
	ldr r0, [r5, #4]
	str r0, [r3, #0x68]
	strb r1, [r3, #0x11]
	str r7, [r3, #0x28]
_080A2888:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080A2890: .4byte gProjectileHeaderPtr
_080A2894: .4byte gProjectileFnTable

	thumb_func_start Projectile17_Init
Projectile17_Init: @ 0x080A2898
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r3, #0
	adds r2, r0, #0
	orrs r2, r1
	movs r0, #2
	orrs r2, r0
	orrs r2, r3
	strb r2, [r6, #0xa]
	ldrb r1, [r6, #0x10]
	cmp r1, #0
	bne _080A28D4
	movs r0, #0xef
	ands r2, r0
	strb r2, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080A28F4
_080A28D4:
	movs r1, #1
	movs r0, #0x10
	orrs r2, r0
	strb r2, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_080A28F4:
	movs r0, #0xff
	strb r0, [r6, #0x12]
	ldrb r7, [r6, #0x11]
	cmp r7, #0
	bne _080A298C
	movs r4, #0xa5
	lsls r4, r4, #3
	ldr r1, _080A2974 @ =gStaticMotionGraphics
	adds r0, r4, r1
	ldr r1, _080A2978 @ =wStaticGraphicTilenums
	adds r1, #0x84
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080A297C @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldr r0, _080A2980 @ =wStaticMotionPalIDs
	adds r0, #0x84
	ldrh r1, [r0]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A2984 @ =0x0836B3C0
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	bl InitBody
	str r6, [r4, #0x2c]
	str r7, [r4, #0x24]
	ldr r1, _080A2988 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r7, [r6, #0xd]
	strb r7, [r6, #0xe]
	strb r7, [r6, #0xf]
	b _080A2A20
	.align 2, 0
_080A2974: .4byte gStaticMotionGraphics
_080A2978: .4byte wStaticGraphicTilenums
_080A297C: .4byte gStaticMotionGraphics+12
_080A2980: .4byte wStaticMotionPalIDs
_080A2984: .4byte 0x0836B3C0
_080A2988: .4byte gProjectileFnTable
_080A298C:
	cmp r7, #1
	bne _080A29C4
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A29BC @ =0x0836B3F0
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r1, _080A29C0 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r7, [r6, #0xc]
	b _080A2A14
	.align 2, 0
_080A29BC: .4byte 0x0836B3F0
_080A29C0: .4byte gProjectileFnTable
_080A29C4:
	cmp r7, #2
	bne _080A2A20
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A2A2C @ =0x0836B408
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r2, _080A2A30 @ =0x080FF080
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #3
	adds r0, r0, r2
	ldr r1, [r6, #0x54]
	ldr r0, [r0]
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldrb r1, [r6, #0x10]
	lsls r1, r1, #3
	adds r2, #4
	adds r1, r1, r2
	ldr r0, [r6, #0x58]
	ldr r1, [r1]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r1, _080A2A34 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
_080A2A14:
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r7, [r6, #0xd]
	strb r5, [r6, #0xe]
	strb r5, [r6, #0xf]
_080A2A20:
	adds r0, r6, #0
	bl Projectile17_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A2A2C: .4byte 0x0836B408
_080A2A30: .4byte 0x080FF080
_080A2A34: .4byte gProjectileFnTable

	thumb_func_start Projectile17_Update
Projectile17_Update: @ 0x080A2A38
	push {lr}
	adds r3, r0, #0
	ldr r0, _080A2A80 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080A2A88
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _080A2A84 @ =gProjectileFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
	b _080A2A98
	.align 2, 0
_080A2A80: .4byte gCurStory
_080A2A84: .4byte gProjectileFnTable
_080A2A88:
	ldr r0, _080A2A9C @ =0x0836B3B4
	ldrb r1, [r3, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r3, #0
	bl _call_via_r1
_080A2A98:
	pop {r0}
	bx r0
	.align 2, 0
_080A2A9C: .4byte 0x0836B3B4

	thumb_func_start Projectile17_Die
Projectile17_Die:
	.byte 0x02, 0x1C, 0x91, 0x7A, 0xFE, 0x20, 0x08, 0x40, 0x00, 0x21, 0x90, 0x72, 0x10, 0x1C, 0x8C, 0x30
	.byte 0x01, 0x60, 0x04, 0x30, 0x01, 0x60, 0x04, 0x30, 0x01, 0x70, 0x91, 0x7A, 0xFB, 0x20, 0x08, 0x40
	.byte 0x90, 0x72, 0x05, 0x49, 0x50, 0x7A, 0x80, 0x00, 0x40, 0x18, 0x04, 0x21, 0xD1, 0x60, 0x00, 0x68
	.byte 0x00, 0x69, 0x50, 0x61, 0x70, 0x47, 0x00, 0x00, 0x0C, 0xA9, 0x36, 0x08

	thumb_func_start FUN_080a2adc
FUN_080a2adc: @ 0x080A2ADC
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r6, r0, #0
	adds r3, r6, #0
	adds r3, #0x8c
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r1, r0
	cmp r1, #0
	beq _080A2AF6
	movs r1, #0
	b _080A2AFE
_080A2AF6:
	ldr r2, _080A2B20 @ =0x00400100
	ands r2, r0
	cmp r2, #0
	beq _080A2B28
_080A2AFE:
	str r1, [r3]
	adds r0, r6, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A2B24 @ =0x00004201
	adds r0, r6, #0
	bl SetMotion
	movs r0, #4
	strb r0, [r6, #0xe]
	b _080A2B6A
	.align 2, 0
_080A2B20: .4byte 0x00400100
_080A2B24: .4byte 0x00004201
_080A2B28:
	movs r4, #4
	ands r0, r4
	cmp r0, #0
	beq _080A2B3E
	str r2, [r3]
	adds r0, r6, #0
	adds r0, #0x90
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	b _080A2B58
_080A2B3E:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080A2B6A
	str r1, [r3]
	adds r0, r6, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
_080A2B58:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A2B7C @ =0x00004201
	adds r0, r6, #0
	bl SetMotion
	strb r4, [r6, #0xe]
_080A2B6A:
	ldrb r0, [r6, #0xe]
	cmp r0, #5
	bls _080A2B72
	b _080A2D86
_080A2B72:
	lsls r0, r0, #2
	ldr r1, _080A2B80 @ =_080A2B84
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A2B7C: .4byte 0x00004201
_080A2B80: .4byte _080A2B84
_080A2B84: @ jump table
	.4byte _080A2B9C @ case 0
	.4byte _080A2BB0 @ case 1
	.4byte _080A2BE0 @ case 2
	.4byte _080A2C22 @ case 3
	.4byte _080A2CE4 @ case 4
	.4byte _080A2D5E @ case 5
_080A2B9C:
	movs r1, #0x84
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0xc
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A2BB0:
	ldr r0, [r6, #0x28]
	ldr r0, [r0, #0x58]
	ldr r1, _080A2BDC @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x13]
	cmp r0, #0
	beq _080A2BD2
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080A2BD2
	b _080A2D86
_080A2BD2:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080A2D86
	.align 2, 0
_080A2BDC: .4byte 0xFFFFF600
_080A2BE0:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A2BF8
	ldr r0, [r6, #0x54]
	ldr r2, _080A2BF4 @ =0xFFFFC000
	adds r1, r0, r2
	b _080A2C00
	.align 2, 0
_080A2BF4: .4byte 0xFFFFC000
_080A2BF8:
	ldr r0, [r6, #0x54]
	movs r3, #0x80
	lsls r3, r3, #7
	adds r1, r0, r3
_080A2C00:
	movs r0, #0x4c
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x54]
	subs r0, r1, r0
	movs r1, #0x4c
	bl __divsi3
	str r0, [r6, #0x5c]
	movs r1, #0
	ldr r0, _080A2C4C @ =0xFFFFFDA0
	str r0, [r6, #0x60]
	movs r0, #0x4b
	str r0, [r6, #0x64]
	strb r1, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A2C22:
	ldr r2, [r6, #0x60]
	adds r2, #0x10
	str r2, [r6, #0x60]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x58]
	adds r0, r0, r2
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	movs r4, #0
	ldr r1, [r6, #0x58]
	ldr r0, [r6, #0x5c]
	cmp r0, #0
	bge _080A2C54
	ldr r0, [r6, #0x54]
	ldr r3, _080A2C50 @ =0xFFFFF600
	b _080A2C5A
	.align 2, 0
_080A2C4C: .4byte 0xFFFFFDA0
_080A2C50: .4byte 0xFFFFF600
_080A2C54:
	ldr r0, [r6, #0x54]
	movs r3, #0xa0
	lsls r3, r3, #4
_080A2C5A:
	adds r2, r0, r3
	adds r0, r2, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	movs r1, #0xf0
	lsls r1, r1, #0xc
	ands r1, r0
	lsrs r1, r1, #0x10
	cmp r1, #1
	bne _080A2C96
	adds r0, r6, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A2CDC @ =0x00004201
	adds r0, r6, #0
	bl SetMotion
	movs r0, #4
	strb r0, [r6, #0xe]
	movs r4, #1
_080A2C96:
	cmp r4, #0
	bne _080A2D86
	ldr r2, [r6, #0x54]
	ldr r0, [r6, #0x58]
	movs r3, #0x80
	lsls r3, r3, #3
	adds r1, r0, r3
	adds r0, r2, #0
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2CBA
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r0, #2
	strb r0, [r6, #0xe]
_080A2CBA:
	ldr r2, [r6, #0x54]
	ldr r0, [r6, #0x58]
	ldr r3, _080A2CE0 @ =0xFFFFFC00
	adds r1, r0, r3
	adds r0, r2, #0
	bl PushoutToDown1
	adds r1, r0, #0
	cmp r1, #0
	beq _080A2D86
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r0, [r6, #0x60]
	rsbs r0, r0, #0
	str r0, [r6, #0x60]
	b _080A2D86
	.align 2, 0
_080A2CDC: .4byte 0x00004201
_080A2CE0: .4byte 0xFFFFFC00
_080A2CE4:
	movs r0, #0xff
	strb r0, [r6, #0x12]
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	ldr r1, _080A2D90 @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r6, #0xa]
	lsrs r1, r1, #4
	movs r5, #1
	ands r1, r5
	mov r0, sp
	bl FUN_080a2790
	ldr r0, [r6, #0x54]
	movs r4, #0xc0
	lsls r4, r4, #4
	adds r0, r0, r4
	str r0, [sp]
	ldr r0, [r6, #0x58]
	adds r0, r0, r4
	str r0, [sp, #4]
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	adds r1, r5, #0
	bics r1, r0
	mov r0, sp
	bl FUN_080a2790
	ldr r0, [r6, #0x54]
	ldr r2, _080A2D90 @ =0xFFFFF400
	adds r0, r0, r2
	str r0, [sp]
	ldr r0, [r6, #0x58]
	adds r0, r0, r4
	str r0, [sp, #4]
	ldrb r1, [r6, #0xa]
	lsrs r1, r1, #4
	ands r1, r5
	mov r0, sp
	bl FUN_080a2790
	movs r4, #0
	adds r5, r6, #0
	adds r5, #0x54
_080A2D40:
	lsls r1, r4, #0x18
	lsrs r1, r1, #0x18
	adds r0, r5, #0
	bl FUN_080a27e4
	adds r4, #1
	cmp r4, #4
	ble _080A2D40
	ldr r1, _080A2D94 @ =0x00004201
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A2D5E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A2D86
	movs r0, #0x31
	bl PlaySound
	ldr r1, _080A2D98 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080A2D86:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A2D90: .4byte 0xFFFFF400
_080A2D94: .4byte 0x00004201
_080A2D98: .4byte gProjectileFnTable
