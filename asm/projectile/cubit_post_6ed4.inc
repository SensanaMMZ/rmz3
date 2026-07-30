	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start cubit_080a6ed4
cubit_080a6ed4: @ 0x080A6ED4
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A6EEA
	ldrb r0, [r5, #0xe]
	cmp r0, #0x13
	bhi _080A6EEA
	movs r0, #0x14
	strb r0, [r5, #0xe]
_080A6EEA:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A6EF8
	b _080A723A
_080A6EF8:
	ldrb r0, [r5, #0xe]
	cmp r0, #0x15
	bls _080A6F00
	b _080A724C
_080A6F00:
	lsls r0, r0, #2
	ldr r1, _080A6F0C @ =_080A6F10
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A6F0C: .4byte _080A6F10
_080A6F10: @ jump table
	.4byte _080A6F68 @ case 0
	.4byte _080A7204 @ case 1
	.4byte _080A6FB8 @ case 2
	.4byte _080A6FC6 @ case 3
	.4byte _080A6FE8 @ case 4
	.4byte _080A7204 @ case 5
	.4byte _080A6FFC @ case 6
	.4byte _080A71F4 @ case 7
	.4byte _080A711A @ case 8
	.4byte _080A7128 @ case 9
	.4byte _080A7158 @ case 10
	.4byte _080A71F4 @ case 11
	.4byte _080A724C @ case 12
	.4byte _080A724C @ case 13
	.4byte _080A724C @ case 14
	.4byte _080A724C @ case 15
	.4byte _080A724C @ case 16
	.4byte _080A724C @ case 17
	.4byte _080A724C @ case 18
	.4byte _080A724C @ case 19
	.4byte _080A721C @ case 20
	.4byte _080A722A @ case 21
_080A6F68:
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	movs r1, #0xb1
	lsls r1, r1, #8
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0xb6
	ldrb r2, [r0]
	cmp r2, #0
	beq _080A6F8C
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A6F92
_080A6F8C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A6F92:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080A7204
_080A6FB8:
	ldr r1, _080A6FE4 @ =0x0000B101
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A6FC6:
	movs r0, #0xff
	strb r0, [r5, #0x12]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r1, r5, #0
	adds r1, #0xb5
	ldr r0, [r5, #0x28]
	adds r0, #0xb5
	ldrb r1, [r1]
	ldrb r0, [r0]
	cmp r1, r0
	beq _080A6FE2
	b _080A724C
_080A6FE2:
	b _080A7214
	.align 2, 0
_080A6FE4: .4byte 0x0000B101
_080A6FE8:
	ldr r1, _080A6FF8 @ =0x0000B102
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080A7204
	.align 2, 0
_080A6FF8: .4byte 0x0000B102
_080A6FFC:
	ldr r1, _080A70B0 @ =0x0000B10C
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x25
	movs r4, #8
	strb r4, [r0]
	adds r0, #0x4f
	ldr r1, _080A70B4 @ =0x0836BBBC
	bl SetDDP
	ldr r0, [r5, #0x28]
	ldr r0, [r0, #0x28]
	ldr r6, [r0, #0x54]
	ldr r7, [r0, #0x58]
	ldr r2, _080A70B8 @ =0x0836BDBC
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	rsbs r0, r0, #0
	asrs r0, r0, #0x1f
	ands r0, r4
	adds r1, r0, r2
	ldr r1, [r1]
	adds r1, r1, r6
	str r1, [r5, #0x54]
	adds r2, #4
	adds r0, r0, r2
	ldr r0, [r0]
	adds r0, r0, r7
	str r0, [r5, #0x58]
	adds r4, r5, #0
	adds r4, #0xb8
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r4]
	ldr r0, _080A70BC @ =pZero2
	ldr r1, [r0]
	ldr r2, [r1, #0x54]
	ldr r0, [r5, #0x54]
	subs r2, r2, r0
	str r2, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	movs r3, #0x80
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r1, [r1, #0x58]
	subs r1, r1, r0
	str r1, [r5, #0x60]
	asrs r2, r2, #2
	adds r0, r2, #0
	muls r0, r2, r0
	asrs r1, r1, #2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	adds r0, r0, r1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #0xe
	cmp r6, #0
	beq _080A7098
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	str r0, [r5, #0x60]
_080A7098:
	ldr r2, [r5, #0x60]
	adds r0, r2, #0
	cmp r2, #0
	bge _080A70A2
	rsbs r0, r2, #0
_080A70A2:
	cmp r0, #0x80
	ble _080A70DC
	cmp r2, #0
	ble _080A70C0
	movs r0, #0x80
	b _080A70C4
	.align 2, 0
_080A70B0: .4byte 0x0000B10C
_080A70B4: .4byte 0x0836BBBC
_080A70B8: .4byte 0x0836BDBC
_080A70BC: .4byte pZero2
_080A70C0:
	movs r0, #0x80
	rsbs r0, r0, #0
_080A70C4:
	str r0, [r5, #0x60]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A70D6
	movs r0, #0xdd
	rsbs r0, r0, #0
	b _080A70D8
_080A70D6:
	movs r0, #0xdd
_080A70D8:
	str r0, [r5, #0x5c]
	ldr r2, [r5, #0x60]
_080A70DC:
	ldr r0, [r5, #0x28]
	ldr r0, [r0, #0x28]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A70F2
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	ble _080A70FC
	b _080A70F8
_080A70F2:
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	bge _080A70FC
_080A70F8:
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
_080A70FC:
	ldr r1, [r5, #0x5c]
	ldr r0, [r4]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r5, #0x64]
	ldr r0, [r4]
	muls r0, r2, r0
	asrs r0, r0, #8
	str r0, [r5, #0x68]
	movs r0, #0xce
	bl PlaySound
	movs r0, #0x78
	strb r0, [r5, #0x12]
	b _080A71EE
_080A711A:
	ldr r1, _080A7154 @ =0x0000B10D
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A7128:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x64]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x68]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _080A7150
	b _080A724C
_080A7150:
	b _080A7214
	.align 2, 0
_080A7154: .4byte 0x0000B10D
_080A7158:
	ldr r1, _080A7174 @ =0x0000B10F
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A7178 @ =0x0836BBEC
	bl SetDDP
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	ble _080A717C
	movs r0, #0xb5
	b _080A7180
	.align 2, 0
_080A7174: .4byte 0x0000B10F
_080A7178: .4byte 0x0836BBEC
_080A717C:
	movs r0, #0xb5
	rsbs r0, r0, #0
_080A7180:
	str r0, [r5, #0x5c]
	ldr r2, _080A71C4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080A71C8 @ =0x000343FD
	muls r0, r1, r0
	ldr r3, _080A71CC @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r2, #1
	ands r0, r2
	cmp r0, #0
	beq _080A71D0
	movs r0, #0xb5
	str r0, [r5, #0x60]
	ldrb r1, [r5, #0xa]
	movs r0, #0x20
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4d
	strb r2, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	movs r2, #0x20
	ldrb r1, [r3]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	b _080A71D6
	.align 2, 0
_080A71C4: .4byte RNG_0202f388
_080A71C8: .4byte 0x000343FD
_080A71CC: .4byte 0x00269EC3
_080A71D0:
	movs r0, #0xb5
	rsbs r0, r0, #0
	str r0, [r5, #0x60]
_080A71D6:
	adds r2, r5, #0
	adds r2, #0xb8
	ldr r1, [r5, #0x5c]
	ldr r0, [r2]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r5, #0x64]
	ldr r1, [r5, #0x60]
	ldr r0, [r2]
	muls r0, r1, r0
	asrs r0, r0, #8
	str r0, [r5, #0x68]
_080A71EE:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A71F4:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x64]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x68]
	adds r0, r0, r1
	str r0, [r5, #0x58]
_080A7204:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A724C
_080A7214:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080A724C
_080A721C:
	ldr r1, _080A7254 @ =0x0000B102
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A722A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A724C
_080A723A:
	ldr r1, _080A7258 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080A724C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A7254: .4byte 0x0000B102
_080A7258: .4byte gProjectileFnTable

	thumb_func_start cubit_080a725c
cubit_080a725c: @ 0x080A725C
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r6, r0, #0
	ldr r1, [r6, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _080A726C
	b _080A745A
_080A726C:
	adds r0, r1, #0
	adds r0, #0xc0
	ldr r0, [r0]
	cmp r0, #0
	beq _080A7278
	b _080A745A
_080A7278:
	ldrb r0, [r1, #0xd]
	cmp r0, #0xb
	bne _080A7280
	b _080A745A
_080A7280:
	ldrb r0, [r6, #0xe]
	cmp r0, #7
	bls _080A7288
	b _080A746C
_080A7288:
	lsls r0, r0, #2
	ldr r1, _080A7294 @ =_080A7298
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A7294: .4byte _080A7298
_080A7298: @ jump table
	.4byte _080A72B8 @ case 0
	.4byte _080A72F2 @ case 1
	.4byte _080A73F0 @ case 2
	.4byte _080A7410 @ case 3
	.4byte _080A73F6 @ case 4
	.4byte _080A7410 @ case 5
	.4byte _080A7428 @ case 6
	.4byte _080A7436 @ case 7
_080A72B8:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	movs r0, #9
	strb r0, [r6, #0x12]
	movs r0, #4
	strb r0, [r6, #0x13]
	ldr r0, [r6, #0x28]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A72DC
	adds r1, r6, #0
	adds r1, #0xbc
	movs r0, #0xe8
	b _080A72E2
_080A72DC:
	adds r1, r6, #0
	adds r1, #0xbc
	movs r0, #0x18
_080A72E2:
	str r0, [r1]
	adds r1, r6, #0
	adds r1, #0xb5
	movs r0, #0xff
	strb r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A72F2:
	ldrb r0, [r6, #0x13]
	cmp r0, #0
	beq _080A7304
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080A7304
	b _080A746C
_080A7304:
	ldrb r1, [r6, #0x12]
	movs r0, #9
	subs r0, r0, r1
	mov ip, r0
	ldr r0, [r6, #0x28]
	ldr r3, [r0, #0x54]
	str r3, [sp]
	ldr r4, [r0, #0x58]
	str r4, [sp, #4]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A733C
	ldr r1, _080A7338 @ =0x0836BDCC
	mov r0, ip
	lsls r2, r0, #3
	adds r0, r2, r1
	ldr r0, [r0]
	adds r0, r0, r3
	str r0, [sp]
	adds r1, #4
	adds r2, r2, r1
	ldr r0, [r2]
	b _080A7354
	.align 2, 0
_080A7338: .4byte 0x0836BDCC
_080A733C:
	ldr r2, _080A73D8 @ =0x0836BDCC
	movs r1, #8
	mov r0, ip
	subs r1, r1, r0
	lsls r1, r1, #3
	adds r0, r1, r2
	ldr r0, [r0]
	adds r0, r0, r3
	str r0, [sp]
	adds r2, #4
	adds r1, r1, r2
	ldr r0, [r1]
_080A7354:
	adds r0, r0, r4
	str r0, [sp, #4]
	adds r0, r6, #0
	adds r0, #0xb8
	movs r3, #0x90
	lsls r3, r3, #6
	str r3, [r0]
	ldr r4, [r6, #0x28]
	ldr r5, _080A73DC @ =gSineTable
	adds r7, r6, #0
	adds r7, #0xbc
	ldr r2, [r7]
	ldrb r0, [r7]
	lsls r0, r0, #1
	adds r0, r0, r5
	movs r1, #0
	ldrsh r0, [r0, r1]
	adds r1, r0, #0
	muls r1, r3, r1
	asrs r1, r1, #8
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [sp]
	adds r2, #0x40
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x17
	adds r2, r2, r5
	movs r1, #0
	ldrsh r0, [r2, r1]
	adds r1, r0, #0
	muls r1, r3, r1
	asrs r1, r1, #8
	ldr r0, _080A73E0 @ =0xFFFFE800
	adds r1, r1, r0
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r0, #1
	ands r2, r0
	mov r1, ip
	lsls r3, r1, #0x18
	lsrs r3, r3, #0x18
	adds r0, r6, #0
	mov r1, sp
	bl FUN_080a60c8
	cmp r0, #0
	beq _080A73C0
	adds r1, r0, #0
	adds r1, #0xbc
	ldr r0, [r7]
	str r0, [r1]
_080A73C0:
	movs r0, #4
	strb r0, [r6, #0x13]
	ldr r0, [r6, #0x28]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A73E4
	ldr r0, [r7]
	subs r0, #0x1a
	b _080A73E8
	.align 2, 0
_080A73D8: .4byte 0x0836BDCC
_080A73DC: .4byte gSineTable
_080A73E0: .4byte 0xFFFFE800
_080A73E4:
	ldr r0, [r7]
	adds r0, #0x1a
_080A73E8:
	movs r1, #0xff
	ands r0, r1
	str r0, [r7]
	b _080A7410
_080A73F0:
	movs r0, #0xc
	strb r0, [r6, #0x12]
	b _080A740A
_080A73F6:
	movs r0, #0xcf
	bl PlaySound
	movs r0, #0x20
	strb r0, [r6, #0x12]
	strb r0, [r6, #0x13]
	adds r1, r6, #0
	adds r1, #0xb5
	movs r0, #9
	strb r0, [r1]
_080A740A:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A7410:
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080A7420
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A746C
_080A7420:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080A746C
_080A7428:
	movs r0, #0x81
	strb r0, [r6, #0x12]
	movs r0, #3
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A7436:
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080A7446
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A746C
_080A7446:
	movs r0, #0xc4
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x13]
	cmp r0, #0
	beq _080A745A
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A746C
_080A745A:
	ldr r1, _080A7474 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080A746C:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A7474: .4byte gProjectileFnTable

	thumb_func_start FUN_080a7478
FUN_080a7478: @ 0x080A7478
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r1, [r6, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bhi _080A748A
	ldrb r0, [r1, #0xd]
	cmp r0, #0xb
	bne _080A7494
_080A748A:
	ldrb r0, [r6, #0xe]
	cmp r0, #0x13
	bhi _080A7494
	movs r0, #0x14
	strb r0, [r6, #0xe]
_080A7494:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A74A2
	b _080A7A4E
_080A74A2:
	ldrb r0, [r6, #0xe]
	cmp r0, #0x15
	bls _080A74AA
	b _080A7A60
_080A74AA:
	lsls r0, r0, #2
	ldr r1, _080A74B4 @ =_080A74B8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A74B4: .4byte _080A74B8
_080A74B8: @ jump table
	.4byte _080A7510 @ case 0
	.4byte _080A755E @ case 1
	.4byte _080A7572 @ case 2
	.4byte _080A7584 @ case 3
	.4byte _080A75B4 @ case 4
	.4byte _080A75C2 @ case 5
	.4byte _080A75DC @ case 6
	.4byte _080A76A8 @ case 7
	.4byte _080A7784 @ case 8
	.4byte _080A7858 @ case 9
	.4byte _080A791C @ case 10
	.4byte _080A7942 @ case 11
	.4byte _080A7A60 @ case 12
	.4byte _080A7A60 @ case 13
	.4byte _080A7A60 @ case 14
	.4byte _080A7A60 @ case 15
	.4byte _080A7A60 @ case 16
	.4byte _080A7A60 @ case 17
	.4byte _080A7A60 @ case 18
	.4byte _080A7A60 @ case 19
	.4byte _080A7A04 @ case 20
	.4byte _080A7A2E @ case 21
_080A7510:
	adds r1, r6, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	movs r1, #0xb1
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0xb6
	ldrb r2, [r0]
	cmp r2, #0
	beq _080A7534
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A753A
_080A7534:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A753A:
	strb r0, [r6, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A755E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080A7570
	b _080A7A60
_080A7570:
	b _080A790C
_080A7572:
	ldr r1, _080A75AC @ =0x0000B101
	adds r0, r6, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A7584:
	movs r0, #0xff
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x13]
	adds r0, #1
	strb r0, [r6, #0x13]
	ldrb r2, [r6, #0x13]
	ldr r1, _080A75B0 @ =0x0836BE14
	adds r0, r6, #0
	adds r0, #0xb5
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	cmp r2, r0
	bge _080A75AA
	b _080A7A60
_080A75AA:
	b _080A790C
	.align 2, 0
_080A75AC: .4byte 0x0000B101
_080A75B0: .4byte 0x0836BE14
_080A75B4:
	ldr r1, _080A75D8 @ =0x0000B114
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A75C2:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080A75D4
	b _080A7A60
_080A75D4:
	b _080A790C
	.align 2, 0
_080A75D8: .4byte 0x0000B114
_080A75DC:
	ldr r1, _080A764C @ =0x0000B115
	adds r0, r6, #0
	bl SetMotion
	adds r1, r6, #0
	adds r1, #0x25
	movs r0, #8
	strb r0, [r1]
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _080A7650 @ =0x0836BD0C
	bl SetDDP
	adds r4, r6, #0
	adds r4, #0xbc
	ldr r0, [r4]
	strb r0, [r6, #0x13]
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r4]
	lsls r0, r0, #8
	str r0, [r1]
	subs r1, #8
	movs r0, #0x90
	lsls r0, r0, #6
	str r0, [r1]
	ldr r0, [r6, #0x28]
	ldr r1, [r0, #0x28]
	ldr r0, [r1, #0x54]
	ldr r1, [r1, #0x58]
	bl FUN_0800a31c
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x28]
	ldr r1, [r0, #0x28]
	ldr r0, [r1, #0x54]
	ldr r1, [r1, #0x58]
	bl FUN_08009f6c
	ldr r1, _080A7654 @ =0xFFFFA200
	adds r0, r0, r1
	ldr r1, [r6, #0x28]
	ldr r1, [r1, #0x28]
	ldr r1, [r1, #0x58]
	cmp r0, r1
	ble _080A7658
	adds r1, r6, #0
	adds r1, #0xb7
	movs r0, #1
	strb r0, [r1]
	ldr r0, [r6, #0x64]
	movs r2, #0xf8
	lsls r2, r2, #7
	adds r0, r0, r2
	b _080A7668
	.align 2, 0
_080A764C: .4byte 0x0000B115
_080A7650: .4byte 0x0836BD0C
_080A7654: .4byte 0xFFFFA200
_080A7658:
	adds r1, r6, #0
	adds r1, #0xb7
	movs r0, #0
	strb r0, [r1]
	ldr r0, [r6, #0x64]
	movs r1, #0xd0
	lsls r1, r1, #7
	adds r0, r0, r1
_080A7668:
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x28]
	ldr r1, [r0, #0x28]
	ldr r0, [r1, #0x58]
	ldr r2, _080A76CC @ =0xFFFFE800
	adds r0, r0, r2
	str r0, [r6, #0x68]
	ldr r0, [r1, #0x54]
	str r0, [r6, #0x5c]
	ldr r0, [r1, #0x58]
	adds r0, r0, r2
	str r0, [r6, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #9
	str r0, [r4]
	movs r0, #0xff
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	adds r0, #0xb5
	ldrb r0, [r0]
	cmp r0, #0
	beq _080A769C
	cmp r0, #3
	beq _080A769C
	cmp r0, #6
	bne _080A76A2
_080A769C:
	movs r0, #0xcb
	bl PlaySound
_080A76A2:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A76A8:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A76D4
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r1, [r0]
	ldr r2, _080A76D0 @ =0xFFFFFE40
	adds r1, r1, r2
	str r1, [r0]
	asrs r1, r1, #8
	movs r2, #0xff
	ands r1, r2
	adds r7, r0, #0
	cmp r1, #0xe8
	ble _080A76F4
	b _080A76EE
	.align 2, 0
_080A76CC: .4byte 0xFFFFE800
_080A76D0: .4byte 0xFFFFFE40
_080A76D4:
	adds r0, r6, #0
	adds r0, #0xc0
	ldr r1, [r0]
	movs r2, #0xe0
	lsls r2, r2, #1
	adds r1, r1, r2
	str r1, [r0]
	asrs r1, r1, #8
	movs r2, #0xff
	ands r1, r2
	adds r7, r0, #0
	cmp r1, #0x17
	bgt _080A76F4
_080A76EE:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A76F4:
	adds r0, r6, #0
	adds r0, #0xb7
	ldrb r0, [r0]
	cmp r0, #1
	bne _080A770A
	adds r2, r6, #0
	adds r2, #0xb8
	ldr r1, [r2]
	movs r0, #0xf8
	lsls r0, r0, #7
	b _080A7714
_080A770A:
	adds r2, r6, #0
	adds r2, #0xb8
	ldr r1, [r2]
	movs r0, #0xd0
	lsls r0, r0, #7
_080A7714:
	subs r0, r0, r1
	lsls r0, r0, #1
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r2]
	adds r5, r2, #0
	ldr r0, [r6, #0x64]
	ldr r1, [r6, #0x5c]
	subs r0, r0, r1
	lsls r0, r0, #1
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x68]
	ldr r3, [r6, #0x60]
	subs r0, r0, r3
	lsls r0, r0, #1
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x60]
	ldr r4, _080A7780 @ =gSineTable
	ldr r0, [r7]
	asrs r0, r0, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r0, [r0, r2]
	mov ip, r0
	ldr r0, [r5]
	mov r2, ip
	muls r2, r0, r2
	adds r0, r2, #0
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r0, [r7]
	asrs r0, r0, #8
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r5]
	muls r0, r1, r0
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _080A784A
	.align 2, 0
_080A7780: .4byte gSineTable
_080A7784:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A779C
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r1]
	ldr r2, _080A7798 @ =0xFFFFFE40
	b _080A77A6
	.align 2, 0
_080A7798: .4byte 0xFFFFFE40
_080A779C:
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r1]
	movs r2, #0xe0
	lsls r2, r2, #1
_080A77A6:
	adds r0, r0, r2
	str r0, [r1]
	adds r7, r1, #0
	adds r0, r6, #0
	adds r0, #0xb7
	ldrb r0, [r0]
	cmp r0, #1
	bne _080A77C2
	adds r2, r6, #0
	adds r2, #0xb8
	ldr r1, [r2]
	movs r0, #0xf8
	lsls r0, r0, #7
	b _080A77CC
_080A77C2:
	adds r2, r6, #0
	adds r2, #0xb8
	ldr r1, [r2]
	movs r0, #0xd0
	lsls r0, r0, #7
_080A77CC:
	subs r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r2]
	adds r5, r2, #0
	ldr r0, [r6, #0x64]
	ldr r1, [r6, #0x5c]
	subs r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x68]
	ldr r3, [r6, #0x60]
	subs r0, r0, r3
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x60]
	ldr r4, _080A7850 @ =gSineTable
	ldr r0, [r7]
	asrs r0, r0, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r0, [r0, r2]
	mov ip, r0
	ldr r0, [r5]
	mov r2, ip
	muls r2, r0, r2
	adds r0, r2, #0
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r0, [r7]
	asrs r0, r0, #8
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r5]
	muls r0, r1, r0
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r0, [r1]
	ldr r2, _080A7854 @ =0xFFFFFE40
	adds r0, r0, r2
	str r0, [r1]
	cmp r0, #0
	bgt _080A784A
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A784A:
	movs r0, #0xff
	strb r0, [r6, #0x12]
	b _080A7A60
	.align 2, 0
_080A7850: .4byte gSineTable
_080A7854: .4byte 0xFFFFFE40
_080A7858:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A7870
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r1]
	ldr r2, _080A786C @ =0xFFFFFD00
	b _080A787A
	.align 2, 0
_080A786C: .4byte 0xFFFFFD00
_080A7870:
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r1]
	movs r2, #0xc0
	lsls r2, r2, #2
_080A787A:
	adds r0, r0, r2
	str r0, [r1]
	adds r7, r1, #0
	adds r5, r6, #0
	adds r5, #0xb8
	ldr r2, [r5]
	rsbs r1, r2, #0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r5]
	ldr r0, [r6, #0x28]
	ldr r4, [r0, #0x28]
	ldr r1, [r4, #0x54]
	ldr r2, [r6, #0x5c]
	subs r1, r1, r2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r6, #0x5c]
	ldr r3, [r6, #0x60]
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r3, r1
	ldr r1, [r4, #0x58]
	subs r1, r1, r0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x60]
	ldr r4, _080A7914 @ =gSineTable
	ldr r0, [r7]
	asrs r0, r0, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r1, #0
	ldrsh r0, [r0, r1]
	mov ip, r0
	ldr r0, [r5]
	mov r1, ip
	muls r1, r0, r1
	adds r0, r1, #0
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r6, #0x54]
	ldr r0, [r7]
	asrs r0, r0, #8
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r5]
	muls r0, r1, r0
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, [r5]
	ldr r0, _080A7918 @ =0x000007FF
	cmp r1, r0
	ble _080A790C
	b _080A7A60
_080A790C:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080A7A60
	.align 2, 0
_080A7914: .4byte gSineTable
_080A7918: .4byte 0x000007FF
_080A791C:
	ldr r1, _080A7958 @ =0x0000B116
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A7942:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080A7960
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r1]
	ldr r2, _080A795C @ =0xFFFFFD00
	b _080A796A
	.align 2, 0
_080A7958: .4byte 0x0000B116
_080A795C: .4byte 0xFFFFFD00
_080A7960:
	adds r1, r6, #0
	adds r1, #0xc0
	ldr r0, [r1]
	movs r2, #0xc0
	lsls r2, r2, #2
_080A796A:
	adds r0, r0, r2
	str r0, [r1]
	adds r7, r1, #0
	adds r5, r6, #0
	adds r5, #0xb8
	ldr r2, [r5]
	rsbs r1, r2, #0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r5]
	ldr r0, [r6, #0x28]
	ldr r4, [r0, #0x28]
	ldr r1, [r4, #0x54]
	ldr r2, [r6, #0x5c]
	subs r1, r1, r2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r6, #0x5c]
	ldr r3, [r6, #0x60]
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r3, r1
	ldr r1, [r4, #0x58]
	subs r1, r1, r0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x60]
	ldr r4, _080A7A00 @ =gSineTable
	ldr r0, [r7]
	asrs r0, r0, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r1, #0
	ldrsh r0, [r0, r1]
	mov ip, r0
	ldr r0, [r5]
	mov r1, ip
	muls r1, r0, r1
	adds r0, r1, #0
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r6, #0x54]
	ldr r0, [r7]
	asrs r0, r0, #8
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r5]
	muls r0, r1, r0
	asrs r0, r0, #8
	adds r3, r3, r0
	str r3, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A7A60
	b _080A7A4E
	.align 2, 0
_080A7A00: .4byte gSineTable
_080A7A04:
	ldr r1, _080A7A68 @ =0x0000B102
	adds r0, r6, #0
	bl SetMotion
	movs r1, #0
	movs r0, #0xa
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A7A2E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A7A60
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080A7A4E
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A7A60
_080A7A4E:
	ldr r1, _080A7A6C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080A7A60:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A7A68: .4byte 0x0000B102
_080A7A6C: .4byte gProjectileFnTable
