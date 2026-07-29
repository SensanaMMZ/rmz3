	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start blizzack_0805ac5c
blizzack_0805ac5c: @ 0x0805AC5C
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r3, _0805ACEC @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _0805AC84
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _0805AC84
	ldr r0, _0805ACF0 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0805AC84:
	adds r0, r4, #0
	adds r0, #0xc8
	movs r1, #0
	ldrsh r0, [r0, r1]
	bl StopSound
	movs r0, #0
	strb r0, [r4, #0xe]
	strb r0, [r4, #0x12]
	movs r2, #0
	ldr r0, _0805ACF4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805ACA6
	movs r2, #1
_0805ACA6:
	adds r5, r4, #0
	adds r5, #0xc4
	strb r2, [r5]
	ldr r1, _0805ACF8 @ =0x0000B40B
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r2, r4, #0
	adds r2, #0x8c
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #9
	ands r0, r1
	adds r6, r2, #0
	cmp r0, #0
	beq _0805AD00
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _0805ACFC @ =0xFFFFE400
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	ldrb r3, [r5]
	movs r0, #0
	mov r1, sp
	bl FUN_080b2b40
	movs r0, #2
	b _0805AD02
	.align 2, 0
_0805ACEC: .4byte gStageRun
_0805ACF0: .4byte 0x0000FFFE
_0805ACF4: .4byte pZero2
_0805ACF8: .4byte 0x0000B40B
_0805ACFC: .4byte 0xFFFFE400
_0805AD00:
	movs r0, #1
_0805AD02:
	strb r0, [r4, #0xd]
	movs r2, #0
	movs r1, #1
	strb r1, [r4, #0xe]
	ldr r0, [r4, #0x2c]
	strb r1, [r0, #0xf]
	str r2, [r6]
	adds r0, r4, #0
	adds r0, #0x90
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start blizzack_0805ad2c
blizzack_0805ad2c: @ 0x0805AD2C
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805AD4A
	ldr r1, _0805AD60 @ =0x0000B40B
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	str r0, [r4, #0x60]
	strb r0, [r4, #0x12]
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
_0805AD4A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	beq _0805AD90
	cmp r0, #1
	bgt _0805AD64
	cmp r0, #0
	beq _0805AD6A
	b _0805ADC8
	.align 2, 0
_0805AD60: .4byte 0x0000B40B
_0805AD64:
	cmp r0, #2
	beq _0805ADAC
	b _0805ADC8
_0805AD6A:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0805ADC8
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [sp]
	ldr r0, _0805AD8C @ =0xFFFFE800
	str r0, [sp, #4]
	adds r0, r4, #0
	mov r1, sp
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	b _0805ADC2
	.align 2, 0
_0805AD8C: .4byte 0xFFFFE800
_0805AD90:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0805ADC8
	ldr r2, _0805ADA8 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	movs r0, #0x20
	strb r0, [r4, #0x12]
	b _0805ADC2
	.align 2, 0
_0805ADA8: .4byte gStageRun
_0805ADAC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805ADC8
	ldrb r0, [r4, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r4, #0xa]
_0805ADC2:
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
_0805ADC8:
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start blizzack_0805add0
blizzack_0805add0: @ 0x0805ADD0
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0805AE6E
	ldr r1, _0805AE24 @ =0x0000B40C
	adds r0, r5, #0
	bl SetMotion
	adds r4, r5, #0
	adds r4, #0xc4
	ldrb r1, [r4]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r0, [r4]
	movs r1, #0x4a
	adds r1, r1, r5
	mov ip, r1
	adds r1, r2, #0
	ands r1, r0
	lsls r1, r1, #4
	mov r0, ip
	ldrb r3, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	ldrb r0, [r4]
	ands r2, r0
	cmp r2, #0
	beq _0805AE28
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805AE2E
	.align 2, 0
_0805AE24: .4byte 0x0000B40C
_0805AE28:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805AE2E:
	strb r0, [r5, #0xa]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805AE42
	movs r0, #0x20
	str r0, [r5, #0x5c]
	subs r0, #0x21
	b _0805AE4A
_0805AE42:
	movs r0, #0x20
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
	movs r0, #1
_0805AE4A:
	str r0, [r5, #0x64]
	movs r4, #0
	movs r0, #0x20
	strb r0, [r5, #0x12]
	strb r4, [r5, #0xe]
	strb r4, [r5, #0xf]
	lsls r2, r1, #0x18
	lsrs r2, r2, #0x1c
	movs r0, #1
	ands r2, r0
	adds r0, r5, #0
	movs r1, #2
	bl CreateEnemy42
	str r4, [r5, #0x2c]
	movs r0, #0x2f
	bl PlaySound
_0805AE6E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xf]
	cmp r0, #1
	beq _0805AEAC
	cmp r0, #1
	bgt _0805AE84
	cmp r0, #0
	beq _0805AE8E
	b _0805AF0C
_0805AE84:
	cmp r0, #2
	beq _0805AED4
	cmp r0, #3
	beq _0805AEF0
	b _0805AF0C
_0805AE8E:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x64]
	adds r1, r1, r0
	str r1, [r5, #0x5c]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805AF0C
	b _0805AF06
_0805AEAC:
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0805AF0C
	movs r0, #0xe0
	lsls r0, r0, #4
	str r0, [sp]
	ldr r0, _0805AED0 @ =0xFFFFE800
	str r0, [sp, #4]
	adds r0, r5, #0
	mov r1, sp
	bl CreateBossExplosion
	str r0, [r5, #0x2c]
	b _0805AF06
	.align 2, 0
_0805AED0: .4byte 0xFFFFE800
_0805AED4:
	ldr r0, [r5, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0805AF0C
	ldr r2, _0805AEEC @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	movs r0, #0x20
	strb r0, [r5, #0x12]
	b _0805AF06
	.align 2, 0
_0805AEEC: .4byte gStageRun
_0805AEF0:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805AF0C
	ldrb r0, [r5, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r5, #0xa]
_0805AF06:
	ldrb r0, [r5, #0xf]
	adds r0, #1
	strb r0, [r5, #0xf]
_0805AF0C:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
