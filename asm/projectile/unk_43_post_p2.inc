	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b145c
FUN_080b145c: @ 0x080B145C
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080B14B0 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080B14A8
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080B14B4 @ =gProjectileFnTable
	movs r1, #0x2b
	strb r1, [r3, #9]
	adds r0, #0xac
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r1, #0
	strh r2, [r3, #0x20]
	adds r0, r3, #0
	adds r0, #0x22
	strb r1, [r0]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r5, [r3, #0x5c]
	movs r0, #0
	cmp r5, #0
	ble _080B14A4
	movs r0, #1
_080B14A4:
	strb r0, [r3, #0x12]
	strb r1, [r3, #0x10]
_080B14A8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B14B0: .4byte gProjectileHeaderPtr
_080B14B4: .4byte gProjectileFnTable

	thumb_func_start Projectile43_Init
Projectile43_Init: @ 0x080B14B8
	push {lr}
	ldr r2, _080B14EC @ =gProjectileFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r2, #1
	str r2, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	str r1, [r0, #0x14]
	ldr r2, _080B14F0 @ =0x0836D77C
	ldrb r1, [r0, #0x10]
	adds r1, r1, r2
	ldrb r1, [r1]
	strb r1, [r0, #0xd]
	ldrb r1, [r0, #0xa]
	movs r2, #1
	orrs r1, r2
	movs r2, #2
	orrs r1, r2
	strb r1, [r0, #0xa]
	bl Projectile43_Update
	pop {r0}
	bx r0
	.align 2, 0
_080B14EC: .4byte gProjectileFnTable
_080B14F0: .4byte 0x0836D77C

	thumb_func_start Projectile43_Update
Projectile43_Update: @ 0x080B14F4
	push {lr}
	adds r3, r0, #0
	ldr r0, _080B153C @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080B1544
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
	ldr r1, _080B1540 @ =gProjectileFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
	b _080B1554
	.align 2, 0
_080B153C: .4byte gCurStory
_080B1540: .4byte gProjectileFnTable
_080B1544:
	ldr r0, _080B1558 @ =0x0836D748
	ldrb r1, [r3, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r3, #0
	bl _call_via_r1
_080B1554:
	pop {r0}
	bx r0
	.align 2, 0
_080B1558: .4byte 0x0836D748

	thumb_func_start FUN_080b155c
FUN_080b155c: @ 0x080B155C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _080B156C
	cmp r6, #1
	beq _080B15E2
	b _080B1656
_080B156C:
	ldrb r1, [r5, #0xa]
	movs r0, #4
	movs r7, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080B15A8 @ =0x0836D74C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldr r1, _080B15AC @ =0x0000DB0D
	adds r0, r5, #0
	bl SetMotion
	ldrb r2, [r5, #0x12]
	cmp r2, #0
	beq _080B15B0
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080B15B6
	.align 2, 0
_080B15A8: .4byte 0x0836D74C
_080B15AC: .4byte 0x0000DB0D
_080B15B0:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080B15B6:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	movs r0, #0x55
	strb r0, [r5, #0x13]
	movs r0, #6
	strb r0, [r5, #0x12]
_080B15E2:
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080B1610
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	ldr r1, _080B160C @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080B1656
	.align 2, 0
_080B160C: .4byte gProjectileFnTable
_080B1610:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080B164C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	beq _080B1650
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	bne _080B1650
	ldr r1, _080B1648 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080B1650
	.align 2, 0
_080B1648: .4byte gProjectileFnTable
_080B164C:
	subs r0, #1
	strb r0, [r5, #0x12]
_080B1650:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080B1656:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
  .align 2, 0
