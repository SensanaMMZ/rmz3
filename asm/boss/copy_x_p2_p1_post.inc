	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start copyxMode7
copyxMode7: @ 0x08055CDC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08055D90
	ldr r1, _08055D34 @ =0x0000B30F
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _08055D38 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08055CFE
	movs r3, #1
_08055CFE:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08055D10
	movs r3, #1
_08055D10:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _08055D3C
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08055D42
	.align 2, 0
_08055D34: .4byte 0x0000B30F
_08055D38: .4byte pZero2
_08055D3C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08055D42:
	strb r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xe]
	ldrb r1, [r4, #0xa]
	movs r2, #0x10
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _08055D68
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0xc8
	ldr r0, _08055D64 @ =0x0000FFF0
	strh r0, [r1]
	b _08055D72
	.align 2, 0
_08055D64: .4byte 0x0000FFF0
_08055D68:
	ldr r0, _08055DC8 @ =0xFFFFFC00
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0xc8
	strh r2, [r0]
_08055D72:
	movs r0, #0x28
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	movs r1, #0
	movs r2, #0
	bl createCopyXSonicBoom
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08055DCC @ =0x08363CD8
	bl SetDDP
	movs r0, #0x4c
	bl PlaySound
_08055D90:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xc8
	movs r2, #0
	ldrsh r0, [r0, r2]
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	cmp r1, #0
	bge _08055DB0
	rsbs r1, r1, #0
_08055DB0:
	ldr r0, _08055DD0 @ =0x000002BF
	cmp r1, r0
	bgt _08055DD8
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08055DD4
	movs r0, #0xb0
	lsls r0, r0, #2
	b _08055DD6
	.align 2, 0
_08055DC8: .4byte 0xFFFFFC00
_08055DCC: .4byte 0x08363CD8
_08055DD0: .4byte 0x000002BF
_08055DD4:
	ldr r0, _08055DF4 @ =0xFFFFFD40
_08055DD6:
	str r0, [r4, #0x5c]
_08055DD8:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _08055DEE
	movs r0, #8
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08055DEE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08055DF4: .4byte 0xFFFFFD40

