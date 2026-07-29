	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08084c30
FUN_08084c30: @ 0x08084C30
	push {r4, lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0xe]
	cmp r0, #0
	beq _08084C40
	cmp r0, #1
	beq _08084C4A
	b _08084CAC
_08084C40:
	movs r0, #0x60
	strb r0, [r2, #0x12]
	ldrb r0, [r2, #0xe]
	adds r0, #1
	strb r0, [r2, #0xe]
_08084C4A:
	ldrb r0, [r2, #0x12]
	subs r0, #1
	movs r4, #0
	strb r0, [r2, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08084C5E
	movs r0, #3
	strb r0, [r2, #0xd]
	strb r4, [r2, #0xe]
_08084C5E:
	ldrb r1, [r2, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08084C7C
	ldr r0, _08084C78 @ =pZero2
	ldr r3, [r0]
	ldr r0, [r3, #0x54]
	ldr r1, [r2, #0x54]
	subs r0, r0, r1
	movs r1, #0xf0
	lsls r1, r1, #7
	b _08084C88
	.align 2, 0
_08084C78: .4byte pZero2
_08084C7C:
	ldr r0, _08084CB4 @ =pZero2
	ldr r3, [r0]
	ldr r0, [r3, #0x54]
	ldr r1, [r2, #0x54]
	subs r0, r0, r1
	ldr r1, _08084CB8 @ =0xFFFFF000
_08084C88:
	adds r0, r0, r1
	movs r1, #0xd0
	lsls r1, r1, #7
	cmp r0, r1
	bhi _08084CA0
	ldr r0, [r3, #0x58]
	ldr r1, [r2, #0x58]
	subs r0, r0, r1
	movs r1, #0xe0
	lsls r1, r1, #7
	cmp r0, r1
	bls _08084CA6
_08084CA0:
	movs r0, #1
	strb r0, [r2, #0xd]
	strb r4, [r2, #0xe]
_08084CA6:
	adds r0, r2, #0
	bl UpdateMotionGraphic
_08084CAC:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08084CB4: .4byte pZero2
_08084CB8: .4byte 0xFFFFF000
