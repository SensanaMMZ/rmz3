	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08071a28
FUN_08071a28: @ 0x08071A28
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	ldr r5, [r4, #0x2c]
	cmp r5, #0
	beq _08071A78
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _08071A78
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
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
	ldr r1, _08071A74 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _08071B6A
	.align 2, 0
_08071A74: .4byte gEnemyFnTable
_08071A78:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08071A84
	cmp r0, #1
	beq _08071ABE
	b _08071B6A
_08071A84:
	movs r0, #0x34
	bl PlaySound
	cmp r5, #0
	beq _08071AB8
	ldr r0, [r5, #0x28]
	cmp r0, #0
	bne _08071AB4
	ldr r0, [r5, #0x58]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	ldr r1, _08071AB0 @ =0x000027FF
	cmp r0, r1
	bgt _08071AB4
	str r4, [r5, #0x28]
	movs r1, #0x88
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	b _08071AB8
	.align 2, 0
_08071AB0: .4byte 0x000027FF
_08071AB4:
	movs r5, #0
	str r5, [r4, #0x2c]
_08071AB8:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08071ABE:
	ldr r0, [r4, #0x58]
	ldr r1, _08071B74 @ =0xFFFFFEC0
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r1, [r4, #0x54]
	ldr r0, _08071B78 @ =0x00267FFF
	cmp r1, r0
	bgt _08071AD2
	adds r0, #1
	str r0, [r4, #0x54]
_08071AD2:
	ldr r0, [r4, #0x54]
	ldr r1, _08071B7C @ =0x00275000
	cmp r0, r1
	ble _08071ADC
	str r1, [r4, #0x54]
_08071ADC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	cmp r5, #0
	beq _08071AF4
	ldr r0, [r4, #0x54]
	str r0, [r5, #0x54]
	ldr r0, [r4, #0x58]
	movs r1, #0x88
	lsls r1, r1, #6
	adds r0, r0, r1
	str r0, [r5, #0x58]
_08071AF4:
	ldr r1, [r4, #0x58]
	ldr r0, _08071B80 @ =0x00019FFF
	cmp r1, r0
	bgt _08071B6A
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	mov r8, r0
	ands r0, r1
	movs r2, #0
	movs r6, #0xfd
	ands r0, r6
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r7, #0xfb
	adds r0, r7, #0
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08071B84 @ =gEnemyFnTable
	mov ip, r1
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	add r0, ip
	movs r3, #3
	str r3, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	cmp r5, #0
	beq _08071B6A
	ldrb r1, [r5, #0xa]
	mov r0, r8
	ands r0, r1
	ands r0, r6
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	adds r0, r7, #0
	ands r0, r1
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	add r0, ip
	str r3, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_08071B6A:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08071B74: .4byte 0xFFFFFEC0
_08071B78: .4byte 0x00267FFF
_08071B7C: .4byte 0x00275000
_08071B80: .4byte 0x00019FFF
_08071B84: .4byte gEnemyFnTable
