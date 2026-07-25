	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809664c
FUN_0809664c: @ 0x0809664C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0809665C
	cmp r5, #1
	beq _080966BC
	b _080966E2
_0809665C:
	ldr r0, _080966E8 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r2, r0, #0
	cmp r2, #0
	beq _0809669E
	adds r1, r2, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080966EC @ =gEnemyFnTable
	movs r1, #0x41
	strb r1, [r2, #9]
	adds r1, #0xc3
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	movs r0, #0
	strh r5, [r2, #0x20]
	adds r1, r2, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r2, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r2, #0xb]
	ldrb r0, [r2, #0x1c]
	strb r0, [r2, #0x1d]
	movs r0, #4
	strb r0, [r2, #0x10]
	str r4, [r2, #0x28]
_0809669E:
	str r2, [r4, #0x2c]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080966F0 @ =0x0836A14C
	bl SetDDP
	ldr r1, _080966F4 @ =0x0000DB0E
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080966BC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bne _080966D0
	ldr r0, _080966F8 @ =0x00000107
	bl PlaySound
_080966D0:
	ldrb r1, [r4, #0x12]
	cmp r1, #0
	bne _080966DC
	movs r0, #8
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080966DC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080966E2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080966E8: .4byte gEnemyHeaderPtr
_080966EC: .4byte gEnemyFnTable
_080966F0: .4byte 0x0836A14C
_080966F4: .4byte 0x0000DB0E
_080966F8: .4byte 0x00000107
