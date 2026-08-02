	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080849b0
FUN_080849b0: @ 0x080849B0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080849C0
	cmp r0, #1
	beq _080849DC
	b _08084A6A
_080849C0:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08084A14 @ =0x08368328
	bl SetDDP
	ldr r1, _08084A18 @ =0x00006601
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x80
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080849DC:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0
	bne _08084A28
	ldr r0, _08084A1C @ =pZero2
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	movs r1, #0xf0
	lsls r1, r1, #7
	adds r0, r0, r1
	ldr r1, _08084A20 @ =0x000067FF
	cmp r0, r1
	bhi _08084A50
	ldr r0, [r2, #0x58]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	ldr r1, _08084A24 @ =0x00006FFF
	cmp r0, r1
	bhi _08084A50
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r3, [r4, #0xe]
	b _08084A50
	.align 2, 0
_08084A14: .4byte 0x08368328
_08084A18: .4byte 0x00006601
_08084A1C: .4byte pZero2
_08084A20: .4byte 0x000067FF
_08084A24: .4byte 0x00006FFF
_08084A28:
	ldr r0, _08084A70 @ =pZero2
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	ldr r1, _08084A74 @ =0xFFFFF000
	adds r0, r0, r1
	ldr r1, _08084A78 @ =0x000067FF
	cmp r0, r1
	bhi _08084A50
	ldr r0, [r2, #0x58]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	ldr r1, _08084A7C @ =0x00006FFF
	cmp r0, r1
	bhi _08084A50
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08084A50:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08084A64
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08084A64:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08084A6A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08084A70: .4byte pZero2
_08084A74: .4byte 0xFFFFF000
_08084A78: .4byte 0x000067FF
_08084A7C: .4byte 0x00006FFF
