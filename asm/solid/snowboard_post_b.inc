	.include "asm/macros.inc"
	.syntax unified
	.text

	thumb_func_start FUN_080cfa80
FUN_080cfa80: @ 0x080CFA80
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080CFA90
	cmp r5, #1
	beq _080CFABA
	b _080CFB26
_080CFA90:
	ldr r1, _080CFB2C @ =0x00006D0D
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080CFB30 @ =0x083706AC
	bl SetDDP
	movs r0, #0x20
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	movs r1, #0x20
	bl __divsi3
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CFABA:
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _080CFAD2
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	subs r0, r2, #1
	strb r0, [r4, #0x12]
_080CFAD2:
	adds r0, r4, #0
	bl FUN_080cf428
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080CFAEA
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x64]
	rsbs r0, r0, #0
	str r0, [r4, #0x64]
_080CFAEA:
	ldrb r0, [r4, #0x12]
	adds r3, r4, #0
	adds r3, #0x8c
	cmp r0, #0
	bne _080CFB16
	ldr r0, [r3]
	movs r5, #4
	ands r0, r5
	cmp r0, #0
	beq _080CFB16
	ldr r0, _080CFB34 @ =pZero2
	ldr r2, [r0]
	ldr r0, [r4, #0x58]
	subs r0, #8
	ldr r1, [r2, #0x58]
	cmp r1, r0
	bge _080CFB16
	ldrb r0, [r2, #0xd]
	cmp r0, #0
	bne _080CFB16
	strb r5, [r4, #0xd]
	strb r0, [r4, #0xe]
_080CFB16:
	ldr r0, [r3]
	lsrs r0, r0, #2
	movs r1, #1
	ands r0, r1
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CFB26:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CFB2C: .4byte 0x00006D0D
_080CFB30: .4byte 0x083706AC
_080CFB34: .4byte pZero2
