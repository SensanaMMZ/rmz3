	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808d2f8
FUN_0808d2f8: @ 0x0808D2F8
	push {r4, lr}
	adds r2, r0, #0
	adds r3, r2, #0
	adds r3, #0x8c
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0808D368
	ldr r1, _0808D328 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #2
	str r4, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	ldrb r0, [r2, #0x10]
	cmp r0, #9
	bne _0808D32C
	movs r0, #0
	b _0808D35C
	.align 2, 0
_0808D328: .4byte gEnemyFnTable
_0808D32C:
	ldr r1, [r3]
	movs r0, #0x80
	lsls r0, r0, #9
	ands r1, r0
	cmp r1, #0
	beq _0808D344
	adds r1, r2, #0
	adds r1, #0xbb
	movs r0, #1
	strb r0, [r1]
	strb r4, [r2, #0xd]
	b _0808D35E
_0808D344:
	adds r0, r2, #0
	adds r0, #0xbb
	strb r1, [r0]
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #0xa
	ands r0, r1
	cmp r0, #0
	beq _0808D35A
	movs r0, #3
	b _0808D35C
_0808D35A:
	movs r0, #1
_0808D35C:
	strb r0, [r2, #0xd]
_0808D35E:
	adds r0, r2, #0
	bl Deathlock_Die
	movs r0, #1
	b _0808D36A
_0808D368:
	movs r0, #0
_0808D36A:
	pop {r4}
	pop {r1}
	bx r1

	thumb_func_start FUN_0808d370
FUN_0808d370: @ 0x0808D370
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #6
	bne _0808D37C
	b _0808D496
_0808D37C:
	ldrb r0, [r4, #0x10]
	cmp r0, #9
	bne _0808D384
	b _0808D496
_0808D384:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	beq _0808D390
	b _0808D496
_0808D390:
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _0808D39C
	cmp r0, #1
	beq _0808D420
	b _0808D496
_0808D39C:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808D496
	ldr r1, _0808D40C @ =0x08369148
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808D410 @ =0x08369168
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xd]
	cmp r0, #3
	bne _0808D3FA
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808D414 @ =0x0836930C
	adds r5, r4, #0
	adds r5, #0xb9
	ldrb r1, [r5]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808D418 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldr r1, _0808D41C @ =0x08369300
	ldrb r0, [r5]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
_0808D3FA:
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0808D406:
	movs r0, #1
	b _0808D498
	.align 2, 0
_0808D40C: .4byte 0x08369148
_0808D410: .4byte 0x08369168
_0808D414: .4byte 0x0836930C
_0808D418: .4byte sCollisions
_0808D41C: .4byte 0x08369300
_0808D420:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808D494
	ldr r0, [r4, #0x54]
	ldr r1, _0808D48C @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	bne _0808D45C
	ldr r0, [r4, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	beq _0808D462
_0808D45C:
	adds r0, r4, #0
	bl FUN_0808d160
_0808D462:
	ldrb r1, [r4, #0xd]
	cmp r1, #3
	bne _0808D46C
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
_0808D46C:
	ldrb r0, [r4, #0x10]
	cmp r0, #8
	beq _0808D406
	cmp r1, #3
	beq _0808D406
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0808D490 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0808D406
	movs r0, #0
	strb r0, [r4, #0xf]
	b _0808D498
	.align 2, 0
_0808D48C: .4byte 0xFFFFEE00
_0808D490: .4byte 0x00020001
_0808D494:
	strb r0, [r4, #0xf]
_0808D496:
	movs r0, #0
_0808D498:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
