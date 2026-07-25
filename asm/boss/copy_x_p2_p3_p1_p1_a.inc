	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyxJumpForNovaStrike
copyxJumpForNovaStrike: @ 0x08055FE4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056058
	ldr r1, _08056040 @ =0x0000B307
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	movs r3, #0
	ldr r0, _08056044 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805600A
	movs r3, #1
_0805600A:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805601C
	movs r3, #1
_0805601C:
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
	beq _08056048
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805604E
	.align 2, 0
_08056040: .4byte 0x0000B307
_08056044: .4byte pZero2
_08056048:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805604E:
	strb r0, [r4, #0xa]
	ldr r0, _0805608C @ =0xFFFFFF00
	str r0, [r4, #0x60]
	movs r0, #0xc
	strb r0, [r4, #0x12]
_08056058:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _08056084
	movs r0, #0xe
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08056084:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805608C: .4byte 0xFFFFFF00
