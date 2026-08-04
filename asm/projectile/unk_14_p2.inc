	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a0fa8
FUN_080a0fa8: @ 0x080A0FA8
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldrb r0, [r5, #0xe]
	cmp r0, #9
	bls _080A0FB6
	b _080A125E
_080A0FB6:
	lsls r0, r0, #2
	ldr r1, _080A0FC0 @ =_080A0FC4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A0FC0: .4byte _080A0FC4
_080A0FC4: @ jump table
	.4byte _080A0FEC @ case 0
	.4byte _080A107C @ case 1
	.4byte _080A10C8 @ case 2
	.4byte _080A10F8 @ case 3
	.4byte _080A1120 @ case 4
	.4byte _080A1138 @ case 5
	.4byte _080A115C @ case 6
	.4byte _080A11AA @ case 7
	.4byte _080A1208 @ case 8
	.4byte _080A1212 @ case 9
_080A0FEC:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A101C @ =0x0836B164
	bl SetDDP
	ldr r0, [r5, #0x54]
	str r0, [r5, #0x64]
	adds r0, r5, #0
	bl InitNonAffineMotion
	adds r0, r5, #0
	bl ResetDynamicMotion
	ldr r1, _080A1020 @ =0x0000A71C
	adds r0, r5, #0
	bl SetMotion
	ldrb r2, [r5, #0x12]
	cmp r2, #0
	beq _080A1024
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080A102A
	.align 2, 0
_080A101C: .4byte 0x0836B164
_080A1020: .4byte 0x0000A71C
_080A1024:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A102A:
	strb r0, [r5, #0xa]
	movs r4, #1
	adds r1, r4, #0
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
	ldr r2, _080A10A0 @ =0xFFFFFD80
	ldr r3, _080A10A4 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _080A10A8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080A10AC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r4
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #7
	subs r2, r2, r1
	rsbs r1, r2, #0
	ldrb r0, [r5, #0x12]
	lsls r0, r0, #1
	muls r0, r1, r0
	adds r2, r2, r0
	str r2, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A107C:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r1, r0, r1
	str r1, [r5, #0x54]
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _080A10B0
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r0, r0, r2
	cmp r1, r0
	bgt _080A109C
	b _080A1200
_080A109C:
	b _080A10C0
	.align 2, 0
_080A10A0: .4byte 0xFFFFFD80
_080A10A4: .4byte RNG_0202f388
_080A10A8: .4byte 0x000343FD
_080A10AC: .4byte 0x00269EC3
_080A10B0:
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r2, _080A10C4 @ =0xFFFFB000
	adds r0, r0, r2
	cmp r1, r0
	blt _080A10C0
	b _080A1200
_080A10C0:
	str r0, [r5, #0x54]
	b _080A11FA
	.align 2, 0
_080A10C4: .4byte 0xFFFFB000
_080A10C8:
	ldr r2, _080A1110 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080A1114 @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _080A1118 @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsrs r1, r1, #0x11
	movs r0, #1
	ands r1, r0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, #8
	strb r0, [r5, #0x12]
	ldr r1, _080A111C @ =0x0000A71D
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A10F8:
	adds r0, r5, #0
	bl FUN_0801779c
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080A110C
	b _080A125E
_080A110C:
	b _080A114A
	.align 2, 0
_080A1110: .4byte RNG_0202f388
_080A1114: .4byte 0x000343FD
_080A1118: .4byte 0x00269EC3
_080A111C: .4byte 0x0000A71D
_080A1120:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080A1154 @ =0x0836B17C
	bl SetDDP
	ldr r1, _080A1158 @ =0x0000A71E
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A1138:
	adds r0, r5, #0
	bl FUN_0801779c
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080A114A
	b _080A125E
_080A114A:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080A125E
	.align 2, 0
_080A1154: .4byte 0x0836B17C
_080A1158: .4byte 0x0000A71E
_080A115C:
	ldr r1, _080A1190 @ =0x0000A71F
	adds r0, r5, #0
	bl SetMotion
	ldr r2, _080A1194 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080A1198 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080A119C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	lsls r2, r0, #7
	str r2, [r5, #0x5c]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A11A0
	rsbs r0, r2, #0
	lsls r0, r0, #1
	b _080A11A2
	.align 2, 0
_080A1190: .4byte 0x0000A71F
_080A1194: .4byte RNG_0202f388
_080A1198: .4byte 0x000343FD
_080A119C: .4byte 0x00269EC3
_080A11A0:
	movs r0, #0
_080A11A2:
	str r0, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A11AA:
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x5c]
	adds r0, r0, r2
	str r0, [r5, #0x54]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A11D8
	adds r0, r2, #0
	subs r0, #0x30
	str r0, [r5, #0x5c]
	ldr r1, _080A11D4 @ =0xFFFFFA00
	cmp r0, r1
	bge _080A11CA
	str r1, [r5, #0x5c]
_080A11CA:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x64]
	cmp r0, r1
	bge _080A1200
	b _080A11F0
	.align 2, 0
_080A11D4: .4byte 0xFFFFFA00
_080A11D8:
	adds r0, r2, #0
	adds r0, #0x30
	str r0, [r5, #0x5c]
	movs r1, #0xc0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080A11E8
	str r1, [r5, #0x5c]
_080A11E8:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x64]
	cmp r0, r1
	ble _080A1200
_080A11F0:
	str r1, [r5, #0x54]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r0, #1
	strb r0, [r1]
_080A11FA:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A1200:
	adds r0, r5, #0
	bl FUN_0801779c
	b _080A125E
_080A1208:
	movs r0, #2
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080A1212:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080A1258
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080A1254 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	b _080A1274
	.align 2, 0
_080A1254: .4byte gProjectileFnTable
_080A1258:
	adds r0, r5, #0
	bl FUN_0801779c
_080A125E:
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _080A1276
	ldr r1, _080A127C @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
_080A1274:
	str r0, [r5, #0x14]
_080A1276:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A127C: .4byte gProjectileFnTable
