	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08094c80
FUN_08094c80: @ 0x08094C80
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bhi _08094D40
	lsls r0, r0, #2
	ldr r1, _08094C94 @ =_08094C98
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08094C94: .4byte _08094C98
_08094C98: @ jump table
	.4byte _08094CB0 @ case 0
	.4byte _08094CC2 @ case 1
	.4byte _08094CD0 @ case 2
	.4byte _08094CE4 @ case 3
	.4byte _08094D0A @ case 4
	.4byte _08094D14 @ case 5
_08094CB0:
	movs r0, #2
	strb r0, [r4, #0x13]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094CC2:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D40
	b _08094CFC
_08094CD0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldrb r2, [r4, #0x10]
	bl FUN_08094a54
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094CE4:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D40
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D04
_08094CFC:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08094D40
_08094D04:
	movs r0, #2
	strb r0, [r4, #0xe]
	b _08094D40
_08094D0A:
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094D14:
	ldrb r0, [r4, #0x12]
	movs r1, #9
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D2C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldrb r2, [r4, #0x10]
	bl FUN_080949d4
_08094D2C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	bne _08094D40
	strb r0, [r4, #0xe]
	movs r0, #0x78
	strb r0, [r4, #0x12]
_08094D40:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
