	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CubitProjectile_Init
CubitProjectile_Init: @ 0x080A61FC
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r0, [r6, #0xa]
	movs r1, #1
	movs r4, #0
	movs r7, #0
	orrs r1, r0
	movs r0, #2
	orrs r1, r0
	strb r1, [r6, #0xa]
	adds r0, r6, #0
	bl ResetDynamicMotion
	ldrb r2, [r6, #0x10]
	cmp r2, #0
	bne _080A623C
	ldr r1, _080A6238 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r7, [r6, #0xd]
	b _080A6332
	.align 2, 0
_080A6238: .4byte gProjectileFnTable
_080A623C:
	cmp r2, #5
	bne _080A6260
	strb r7, [r6, #0x10]
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A625C @ =0x0836BCAC
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	b _080A6316
	.align 2, 0
_080A625C: .4byte 0x0836BCAC
_080A6260:
	cmp r2, #1
	bne _080A627C
	ldr r1, _080A6278 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r7, [r6, #0xd]
	b _080A6332
	.align 2, 0
_080A6278: .4byte gProjectileFnTable
_080A627C:
	cmp r2, #4
	bne _080A62C0
	movs r5, #1
	strb r5, [r6, #0x10]
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A62B8 @ =0x0836BBA4
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #6
	bl InitBody
	str r6, [r4, #0x2c]
	str r7, [r4, #0x24]
	ldr r1, _080A62BC @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r5, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r5, [r6, #0xd]
	b _080A6332
	.align 2, 0
_080A62B8: .4byte 0x0836BBA4
_080A62BC: .4byte gProjectileFnTable
_080A62C0:
	cmp r2, #2
	bne _080A62E0
	ldr r1, _080A62DC @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r7, [r6, #0xd]
	b _080A6332
	.align 2, 0
_080A62DC: .4byte gProjectileFnTable
_080A62E0:
	cmp r2, #6
	bne _080A62FC
	movs r0, #2
	strb r0, [r6, #0x10]
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A62F8 @ =0x0836BCF4
	b _080A630E
	.align 2, 0
_080A62F8: .4byte 0x0836BCF4
_080A62FC:
	cmp r2, #3
	bne _080A6336
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A6348 @ =0x0836BCC4
_080A630E:
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
_080A6316:
	bl InitBody
	str r6, [r4, #0x2c]
	str r7, [r4, #0x24]
	ldr r1, _080A634C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r1, [r6, #0xd]
_080A6332:
	strb r7, [r6, #0xe]
	strb r7, [r6, #0xf]
_080A6336:
	movs r0, #0xff
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	bl CubitProjectile_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A6348: .4byte 0x0836BCC4
_080A634C: .4byte gProjectileFnTable
