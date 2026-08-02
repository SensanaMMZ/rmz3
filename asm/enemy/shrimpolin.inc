	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start shrimporinBurrowSnow
shrimporinBurrowSnow: @ 0x08069D6C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08069D7C
	cmp r5, #1
	beq _08069D9A
	b _08069F56
_08069D7C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08069E74 @ =sCollisions
	bl SetDDP
	str r5, [r4, #0x5c]
	strb r5, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08069D9A:
	ldrb r0, [r4, #0x13]
	movs r5, #3
	ands r0, r5
	cmp r0, #0
	bne _08069DAE
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldrb r2, [r4, #0x11]
	bl FUN_080b8f68
_08069DAE:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x78
	bls _08069DC8
	strb r5, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_08069DC8:
	ldr r0, _08069E78 @ =pZero2
	ldr r0, [r0]
	ldr r2, [r0, #0x54]
	ldr r1, _08069E7C @ =0xFFFFC000
	adds r2, r2, r1
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08069DE2
	movs r0, #0x80
	lsls r0, r0, #8
	adds r2, r2, r0
_08069DE2:
	movs r1, #0x80
	lsls r1, r1, #6
	adds r2, r2, r1
	ldrb r0, [r4, #0x12]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	lsls r0, r0, #0xe
	subs r2, r2, r0
	movs r0, #0xa0
	lsls r0, r0, #3
	str r0, [r4, #0x64]
	adds r1, r0, #0
	ldr r0, [r4, #0x54]
	subs r0, r2, r0
	cmp r0, #0
	bge _08069E06
	ldr r1, _08069E80 @ =0xFFFFFB00
_08069E06:
	str r1, [r4, #0x64]
	ldr r2, [r4, #0x5c]
	subs r1, r1, r2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	cmp r0, #0
	bge _08069E18
	adds r0, #0xff
_08069E18:
	asrs r0, r0, #8
	adds r0, r2, r0
	str r0, [r4, #0x5c]
	movs r1, #0xc0
	lsls r1, r1, #2
	cmp r0, r1
	bgt _08069E2C
	ldr r1, _08069E84 @ =0xFFFFFD00
	cmp r0, r1
	bge _08069E2E
_08069E2C:
	str r1, [r4, #0x5c]
_08069E2E:
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r1, r1, r0
	str r1, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r2, [r0]
	subs r1, r1, r2
	movs r0, #0xb4
	lsls r0, r0, #9
	cmp r1, r0
	bgt _08069E4C
	ldr r0, _08069E88 @ =0xFFFE9800
	cmp r1, r0
	bge _08069E50
_08069E4C:
	adds r0, r2, r0
	str r0, [r4, #0x54]
_08069E50:
	movs r6, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _08069E90
	ldr r0, [r4, #0x54]
	movs r5, #0xc0
	lsls r5, r5, #4
	adds r0, r0, r5
	ldr r1, [r4, #0x58]
	ldr r2, _08069E8C @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToLeft2
	adds r2, r0, #0
	cmp r2, #0
	bge _08069EAE
	b _08069EA6
	.align 2, 0
_08069E74: .4byte sCollisions
_08069E78: .4byte pZero2
_08069E7C: .4byte 0xFFFFC000
_08069E80: .4byte 0xFFFFFB00
_08069E84: .4byte 0xFFFFFD00
_08069E88: .4byte 0xFFFE9800
_08069E8C: .4byte 0xFFFFF800
_08069E90:
	ldr r0, [r4, #0x54]
	ldr r5, _08069EEC @ =0xFFFFF400
	adds r0, r0, r5
	ldr r1, [r4, #0x58]
	ldr r2, _08069EF0 @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToRight2
	adds r2, r0, #0
	cmp r2, #0
	ble _08069EAE
_08069EA6:
	movs r6, #1
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
_08069EAE:
	ldr r0, [r4, #0x54]
	adds r0, r0, r5
	ldr r1, [r4, #0x58]
	bl FUN_0800a05c
	adds r2, r0, #0
	ldr r0, [r4, #0x58]
	subs r0, r2, r0
	movs r1, #0xf0
	lsls r1, r1, #4
	adds r0, r0, r1
	ldr r1, _08069EF4 @ =0x00001DFF
	cmp r0, r1
	bls _08069ED4
	movs r6, #1
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
_08069ED4:
	ldrb r0, [r4, #0x12]
	adds r0, r6, r0
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x5c]
	lsrs r2, r0, #0x1f
	cmp r2, #0
	beq _08069EF8
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08069EFE
	.align 2, 0
_08069EEC: .4byte 0xFFFFF400
_08069EF0: .4byte 0xFFFFF800
_08069EF4: .4byte 0x00001DFF
_08069EF8:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08069EFE:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	cmp r5, #0
	bne _08069F4C
	ldr r1, _08069F48 @ =0x00000D02
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _08069F56
	.align 2, 0
_08069F48: .4byte 0x00000D02
_08069F4C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_0800a05c
	str r0, [r4, #0x58]
_08069F56:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
