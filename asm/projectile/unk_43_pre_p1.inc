	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Projectile42_Init
Projectile42_Init: @ 0x080B129C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080B12FC @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080B1300 @ =0x0836D730
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _080B1304 @ =0x0836D718
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #1
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _080B1308 @ =0x080B1299
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile42_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B12FC: .4byte gProjectileFnTable
_080B1300: .4byte 0x0836D730
_080B1304: .4byte 0x0836D718
_080B1308: .4byte 0x080B1299

	thumb_func_start Projectile42_Update
Projectile42_Update: @ 0x080B130C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #0x10]
	cmp r2, #0
	bne _080B1360
	ldr r0, _080B1358 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080B1360
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
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
	ldr r1, _080B135C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _080B1380
	.align 2, 0
_080B1358: .4byte gCurStory
_080B135C: .4byte gProjectileFnTable
_080B1360:
	ldr r1, _080B1388 @ =0x0836D710
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080B138C @ =0x0836D714
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_080B1380:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B1388: .4byte 0x0836D710
_080B138C: .4byte 0x0836D714
