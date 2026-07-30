	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile29_Update
Projectile29_Update: @ 0x080AA40C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _080AA438
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bls _080AA438
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl CreateVFX56
	movs r0, #0
	strb r0, [r4, #0x12]
_080AA438:
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _080AA4B8
	cmp r0, #1
	bgt _080AA448
	cmp r0, #0
	beq _080AA44E
	b _080AA56C
_080AA448:
	cmp r0, #2
	beq _080AA524
	b _080AA56C
_080AA44E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080AA46E
	movs r0, #0x4d
	bl PlaySound
	ldrb r0, [r4, #0xd]
	adds r0, #1
	ldrb r1, [r4, #0x10]
	adds r0, r0, r1
	strb r0, [r4, #0xd]
	b _080AA56C
_080AA46E:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080AA494
	ldrb r0, [r5, #0x1e]
	lsls r0, r0, #8
	adds r1, r5, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	ldr r1, _080AA490 @ =0x0000B31B
	cmp r0, r1
	beq _080AA56C
	movs r0, #0x4d
	bl PlaySound
	b _080AA516
	.align 2, 0
_080AA490: .4byte 0x0000B31B
_080AA494:
	ldrb r0, [r5, #0x1e]
	lsls r0, r0, #8
	adds r1, r5, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	ldr r1, _080AA4B4 @ =0x0000B31C
	cmp r0, r1
	beq _080AA56C
	movs r0, #0x4d
	bl PlaySound
	ldrb r0, [r4, #0xd]
	adds r0, #2
	strb r0, [r4, #0xd]
	b _080AA56C
	.align 2, 0
_080AA4B4: .4byte 0x0000B31C
_080AA4B8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA56C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	cmp r1, #0
	bge _080AA4E0
	adds r1, r4, #0
	adds r1, #0xc0
	movs r0, #0x20
	b _080AA4E6
_080AA4E0:
	adds r1, r4, #0
	adds r1, #0xc0
	movs r0, #0x60
_080AA4E6:
	strb r0, [r1]
	adds r3, r1, #0
	ldr r2, _080AA520 @ =gSineTable
	ldrb r0, [r3]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r5, #0
	ldrsh r1, [r0, r5]
	lsls r0, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldrb r0, [r3]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
_080AA516:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	b _080AA56C
	.align 2, 0
_080AA520: .4byte gSineTable
_080AA524:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA546
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	rsbs r1, r1, #0
	str r1, [r4, #0x5c]
	b _080AA566
_080AA546:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AA56C
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	rsbs r1, r1, #0
	str r1, [r4, #0x60]
_080AA566:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
_080AA56C:
	ldrb r0, [r4, #0x13]
	cmp r0, #2
	bls _080AA5BC
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x20
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x40
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x60
	bl CreateVFX56
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0x80
	bl CreateVFX56
	ldr r1, _080AA5C4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Projectile29_Die
_080AA5BC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AA5C4: .4byte gProjectileFnTable
