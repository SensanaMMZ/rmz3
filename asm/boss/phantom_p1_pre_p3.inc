	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805efbc
FUN_0805efbc: @ 0x0805EFBC
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805EFF4 @ =sCollisions
	bl SetDDP
	movs r5, #1
	strh r5, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_080607a0
	ldr r2, _0805EFF8 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805EFFC @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F000 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r0, r0, #1
	str r0, [r2]
	strb r5, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_0805f004
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805EFF4: .4byte sCollisions
_0805EFF8: .4byte RNG_0202f388
_0805EFFC: .4byte 0x000343FD
_0805F000: .4byte 0x00269EC3

	thumb_func_start FUN_0805f004
FUN_0805f004: @ 0x0805F004
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080607f0
	ldrb r0, [r4, #0x12]
	subs r3, r0, #1
	strb r3, [r4, #0x12]
	cmp r3, #0
	bne _0805F09A
	adds r0, r4, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0x2f
	bgt _0805F060
	ldr r2, _0805F044 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805F048 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F04C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #0x1f
	ands r1, r0
	cmp r1, #9
	bhi _0805F050
	movs r0, #1
	b _0805F096
	.align 2, 0
_0805F044: .4byte RNG_0202f388
_0805F048: .4byte 0x000343FD
_0805F04C: .4byte 0x00269EC3
_0805F050:
	cmp r1, #0x10
	bhi _0805F058
	movs r0, #3
	b _0805F096
_0805F058:
	cmp r1, #0x17
	bls _0805F094
	movs r0, #6
	b _0805F096
_0805F060:
	ldr r2, _0805F080 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805F084 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F088 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #0x1f
	ands r1, r0
	cmp r1, #0xd
	bhi _0805F08C
	movs r0, #1
	b _0805F096
	.align 2, 0
_0805F080: .4byte RNG_0202f388
_0805F084: .4byte 0x000343FD
_0805F088: .4byte 0x00269EC3
_0805F08C:
	cmp r1, #0x16
	bhi _0805F094
	movs r0, #3
	b _0805F096
_0805F094:
	movs r0, #4
_0805F096:
	strb r0, [r4, #0xd]
	strh r3, [r4, #0xe]
_0805F09A:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start phantom_0805f0a0
phantom_0805f0a0: @ 0x0805F0A0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #3
	beq _0805F0BC
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0805F0BC
	movs r0, #3
	strh r0, [r4, #0xe]
_0805F0BC:
	ldr r1, _0805F0F0 @ =0x0836543C
	ldrb r0, [r4, #0xe]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	cmp r0, #0
	bne _0805F0EA
	adds r0, r4, #0
	adds r0, #0x54
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r1, #1
	ands r2, r1
	bl CreateParticle
	movs r0, #3
	strb r0, [r4, #0x13]
_0805F0EA:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F0F0: .4byte 0x0836543C

	thumb_func_start FUN_0805f0f4
FUN_0805f0f4: @ 0x0805F0F4
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F144 @ =sCollisions
	bl SetDDP
	movs r0, #1
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_080607a0
	adds r0, r4, #0
	bl FUN_08060838
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r0, #1
	adds r1, r5, #0
	ands r1, r0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805F148
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805F14E
	.align 2, 0
_0805F144: .4byte sCollisions
_0805F148:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805F14E:
	strb r0, [r4, #0xa]
	lsls r1, r5, #1
	subs r1, #1
	lsls r0, r1, #4
	subs r0, r0, r1
	lsls r0, r0, #6
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0x54
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r1, #1
	ands r2, r1
	movs r1, #0
	bl CreateParticle
	movs r0, #3
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	bl FUN_0805f180
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
