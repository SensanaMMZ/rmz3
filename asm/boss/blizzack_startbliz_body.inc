	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805A4DE
	ldr r1, _0805A4FC @ =0x0000B409
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A500 @ =0x00006409
	strh r1, [r0]
	strb r2, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805A504 @ =0x08364BE0
	bl SetDDP
_0805A4DE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805A4F6
	movs r0, #0xb
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805A4F6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805A4FC: .4byte 0x0000B409
_0805A500: .4byte 0x00006409
_0805A504: .4byte sCollisions+(24*2)
