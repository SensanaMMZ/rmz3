	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start blizzackBombStamp
blizzackBombStamp: @ 0x0805A8F4
	push {r4, r5, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0805A92C
	ldr r1, _0805A990 @ =0x0000B404
	adds r0, r5, #0
	bl SetMotion
	ldr r1, [r5, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r5, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A994 @ =0x00006404
	strh r1, [r0]
	strb r2, [r5, #0xe]
	strb r2, [r5, #0x12]
	movs r0, #0x91
	bl PlaySound
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #4
	bl AppendQuake
_0805A92C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r1, [r5, #0x12]
	adds r0, r1, #1
	strb r0, [r5, #0x12]
	movs r0, #0xf
	ands r0, r1
	cmp r0, #0
	bne _0805A972
	adds r4, r5, #0
	adds r4, #0x54
	movs r3, #0x8c
	lsls r3, r3, #1
	ldrb r0, [r5, #0x12]
	lsls r0, r0, #2
	rsbs r0, r0, #0
	subs r0, #0x40
	str r0, [sp]
	adds r0, r4, #0
	movs r1, #0
	movs r2, #1
	bl CreateVFX57
	ldr r3, _0805A998 @ =0xFFFFFEE8
	ldrb r0, [r5, #0x12]
	lsls r0, r0, #2
	rsbs r0, r0, #0
	subs r0, #0x40
	str r0, [sp]
	adds r0, r4, #0
	movs r1, #0
	movs r2, #1
	bl CreateVFX57
_0805A972:
	ldrb r0, [r5, #0x12]
	cmp r0, #0x30
	bne _0805AA3A
	adds r0, r5, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #0
	beq _0805A99C
	movs r0, #4
	strb r0, [r5, #0xd]
	movs r0, #1
	strb r0, [r5, #0xe]
	movs r0, #5
	b _0805AA38
	.align 2, 0
_0805A990: .4byte 0x0000B404
_0805A994: .4byte 0x00006404
_0805A998: .4byte 0xFFFFFEE8
_0805A99C:
	adds r0, r5, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	cmp r0, #1
	bls _0805A9D8
	adds r0, r5, #0
	adds r0, #0xd0
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsrs r1, r0, #0x1f
	adds r0, r0, r1
	adds r1, r5, #0
	adds r1, #0xa4
	asrs r0, r0, #1
	movs r2, #0
	ldrsh r1, [r1, r2]
	cmp r0, r1
	ble _0805A9D4
	ldr r0, _0805A9D0 @ =gMission
	ldr r0, [r0]
	ldrb r0, [r0, #1]
	cmp r0, #4
	bls _0805A9D4
	movs r0, #0xa
	b _0805A9F6
	.align 2, 0
_0805A9D0: .4byte gMission
_0805A9D4:
	movs r0, #7
	b _0805A9F6
_0805A9D8:
	ldr r2, _0805AA00 @ =RNG_0202f388
	ldr r0, [r2]
	ldr r3, _0805AA04 @ =0x000343FD
	muls r0, r3, r0
	ldr r1, _0805AA08 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r4, #7
	ands r0, r4
	cmp r0, #0
	bne _0805AA0C
	movs r0, #2
_0805A9F6:
	strb r0, [r5, #0xd]
	movs r0, #1
	strb r0, [r5, #0xe]
	b _0805AA3A
	.align 2, 0
_0805AA00: .4byte RNG_0202f388
_0805AA04: .4byte 0x000343FD
_0805AA08: .4byte 0x00269EC3
_0805AA0C:
	adds r0, r1, #0
	muls r0, r3, r0
	ldr r1, _0805AA2C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0805AA30
	strb r4, [r5, #0xd]
	strb r1, [r5, #0xe]
	b _0805AA3A
	.align 2, 0
_0805AA2C: .4byte 0x00269EC3
_0805AA30:
	movs r0, #4
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
	movs r0, #0xd
_0805AA38:
	strb r0, [r5, #0xf]
_0805AA3A:
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
