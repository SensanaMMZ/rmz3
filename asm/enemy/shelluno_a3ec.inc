	push {r4, r5, lr}
	adds r3, r0, #0
	adds r5, r1, #0
	ldr r0, [r3, #0xc]
	ldr r4, [r0, #4]
	ldrb r0, [r4, #4]
	cmp r0, #3
	beq _0807A404
	cmp r0, #0xe
	beq _0807A404
	cmp r0, #0xf
	bne _0807A42E
_0807A404:
	ldr r2, [r3, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0807A42E
	ldr r1, [r2, #0x54]
	ldr r0, [r5]
	cmp r1, r0
	bge _0807A426
	adds r1, r2, #0
	adds r1, #0xba
	movs r0, #0xff
	b _0807A42C
_0807A426:
	adds r1, r2, #0
	adds r1, #0xba
	movs r0, #0xfe
_0807A42C:
	strb r0, [r1]
_0807A42E:
	ldr r0, [r4, #4]
	ldr r1, _0807A464 @ =0x000200FF
	ands r0, r1
	subs r1, #0xfd
	cmp r0, r1
	bne _0807A45E
	ldr r2, [r3, #0x2c]
	ldrb r0, [r2, #0xd]
	cmp r0, #5
	beq _0807A45E
	adds r0, r2, #0
	adds r0, #0xb9
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A45E
	ldr r1, _0807A468 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
_0807A45E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807A464: .4byte 0x000200FF
_0807A468: .4byte gEnemyFnTable

