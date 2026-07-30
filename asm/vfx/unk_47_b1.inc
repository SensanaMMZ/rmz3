	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080bfa7c
FUN_080bfa7c: @ 0x080BFA7C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080BFA8C
	cmp r5, #1
	beq _080BFADC
	b _080BFB4A
_080BFA8C:
	adds r2, r4, #0
	adds r2, #0x49
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	ldr r1, _080BFAB4 @ =0x0836F112
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080BFAB8
	str r5, [r4, #0x60]
	b _080BFAD6
	.align 2, 0
_080BFAB4: .4byte sMotions
_080BFAB8:
	ldr r2, _080BFB18 @ =0xFFFFFB80
	ldr r3, _080BFB1C @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _080BFB20 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BFB24 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	movs r1, #0xff
	ands r0, r1
	subs r2, r2, r0
	str r2, [r4, #0x60]
_080BFAD6:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BFADC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080BFAF2
	str r1, [r4, #0x60]
_080BFAF2:
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r0, r2
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080BFB28
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080BFB4A
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #1
	bl FUN_080bf438
	b _080BFB2C
	.align 2, 0
_080BFB18: .4byte 0xFFFFFB80
_080BFB1C: .4byte RNG_0202f388
_080BFB20: .4byte 0x000343FD
_080BFB24: .4byte 0x00269EC3
_080BFB28:
	cmp r2, #0
	ble _080BFB4A
_080BFB2C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080BFB50 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080BFB4A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BFB50: .4byte gVFXFnTable

