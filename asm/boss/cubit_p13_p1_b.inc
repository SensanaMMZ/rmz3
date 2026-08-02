	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08054530
FUN_08054530: @ 0x08054530
	push {r4, lr}
	adds r3, r0, #0
	ldr r0, [r3, #0xc]
	ldr r2, [r0, #4]
	ldrb r0, [r2, #4]
	cmp r0, #3
	beq _08054546
	cmp r0, #0xe
	beq _08054546
	cmp r0, #0xf
	bne _08054588
_08054546:
	ldr r2, [r3, #0x2c]
	ldr r0, [r3, #0xc]
	ldr r4, [r0, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _08054568
	adds r0, r2, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _08054588
_08054568:
	ldr r0, _08054580 @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08054588
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _08054584
	movs r0, #0xff
	b _08054586
	.align 2, 0
_08054580: .4byte gStageRun
_08054584:
	movs r0, #0xfe
_08054586:
	strb r0, [r2, #0x11]
_08054588:
	ldr r0, [r3, #0xc]
	ldr r2, [r0, #4]
	ldr r1, [r3, #4]
	ldrb r0, [r1]
	cmp r0, #2
	beq _080545C0
	ldr r1, [r1, #0xc]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	beq _080545C0
	ldr r0, [r2, #4]
	ldr r1, _080545C8 @ =0x000200FF
	ands r0, r1
	subs r1, #0xfd
	cmp r0, r1
	bne _080545C0
	ldr r2, [r3, #0x2c]
	ldrb r0, [r2, #0xd]
	subs r0, #0xa
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _080545C0
	movs r1, #0
	movs r0, #0xb
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_080545C0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080545C8: .4byte 0x000200FF
