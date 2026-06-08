	push {lr}
	movs r3, #0
	ldr r2, [r0, #0x2c]
	adds r0, #0x23
	ldrb r0, [r0]
	movs r1, #0xf
	ands r1, r0
	cmp r1, #1
	beq _0809F252
	cmp r1, #3
	bne _0809F282
_0809F252:
	adds r0, r2, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r0, #0
	bne _0809F270
	ldr r0, _0809F26C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	ble _0809F282
	b _0809F28E
	.align 2, 0
_0809F26C: .4byte pZero2
_0809F270:
	cmp r0, #1
	bne _0809F282
	ldr r0, _0809F294 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0809F282
	movs r3, #1
_0809F282:
	cmp r3, #0
	bne _0809F28E
	adds r1, r2, #0
	adds r1, #0xa4
	movs r0, #1
	strh r0, [r1]
_0809F28E:
	pop {r0}
	bx r0
	.align 2, 0
_0809F294: .4byte pZero2
