	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start initCopyXSlidingSonicBoom
initCopyXSlidingSonicBoom: @ 0x080A81D0
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldr r5, [r7, #0x28]
	ldr r1, _080A8220 @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl InitNonAffineMotion
	ldrb r1, [r7, #0xa]
	movs r0, #1
	movs r6, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	movs r1, #0xbc
	lsls r1, r1, #7
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A8224
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A822A
	.align 2, 0
_080A8220: .4byte gProjectileFnTable
_080A8224:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A822A:
	strb r0, [r7, #0xa]
	movs r5, #1
	adds r1, r5, #0
	ands r1, r2
	adds r0, r7, #0
	adds r0, #0x4c
	movs r6, #0
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
	movs r0, #4
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r1, _080A827C @ =0x0836BEF4
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r7, [r4, #0x2c]
	str r6, [r4, #0x24]
	movs r0, #0x28
	strb r0, [r7, #0x12]
	strb r5, [r7, #0xe]
	adds r0, r7, #0
	bl CopyXProjectile_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A827C: .4byte 0x0836BEF4

	thumb_func_start moveSlidingSonicBoom
moveSlidingSonicBoom: @ 0x080A8280
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A829C
	ldr r0, [r5, #0x54]
	movs r1, #0xe0
	lsls r1, r1, #5
	b _080A82A0
_080A829C:
	ldr r0, [r5, #0x54]
	ldr r1, _080A82D4 @ =0xFFFFE400
_080A82A0:
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _080A82BC
	ldrb r0, [r5, #0xd]
	cmp r0, #5
	bls _080A82BC
	cmp r0, #8
	bls _080A82CE
_080A82BC:
	ldr r1, _080A82D8 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A82CE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A82D4: .4byte 0xFFFFE400
_080A82D8: .4byte gProjectileFnTable

	thumb_func_start FUN_080a82dc
FUN_080a82dc: @ 0x080A82DC
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldr r5, [r7, #0x28]
	ldr r1, _080A8328 @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl InitNonAffineMotion
	ldrb r1, [r7, #0xa]
	movs r0, #1
	movs r6, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _080A832C @ =0x00005E01
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A8330
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A8336
	.align 2, 0
_080A8328: .4byte gProjectileFnTable
_080A832C: .4byte 0x00005E01
_080A8330:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A8336:
	strb r0, [r7, #0xa]
	movs r5, #1
	adds r1, r5, #0
	ands r1, r2
	adds r0, r7, #0
	adds r0, #0x4c
	movs r6, #0
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
	movs r0, #4
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r1, _080A8388 @ =0x0836BF24
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r7, [r4, #0x2c]
	str r6, [r4, #0x24]
	movs r0, #0x28
	strb r0, [r7, #0x12]
	strb r5, [r7, #0xe]
	adds r0, r7, #0
	bl CopyXProjectile_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A8388: .4byte 0x0836BF24

	thumb_func_start moveNovaStrikeSonicBoom
moveNovaStrikeSonicBoom: @ 0x080A838C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A83A8
	ldr r0, [r5, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #5
	b _080A83AC
_080A83A8:
	ldr r0, [r5, #0x54]
	ldr r1, _080A83D8 @ =0xFFFFE800
_080A83AC:
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, _080A83DC @ =0xFFFFE600
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r5, #0xd]
	cmp r0, #0xf
	beq _080A83D0
	ldr r1, _080A83E0 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A83D0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A83D8: .4byte 0xFFFFE800
_080A83DC: .4byte 0xFFFFE600
_080A83E0: .4byte gProjectileFnTable
