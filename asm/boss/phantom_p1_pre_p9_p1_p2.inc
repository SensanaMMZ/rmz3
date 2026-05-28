	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f5a8
FUN_0805f5a8: @ 0x0805F5A8
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F626
	movs r0, #2
	strb r0, [r4, #0xf]
	ldr r0, _0805F5DC @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	adds r0, r4, #0
	adds r0, #0xe0
	ldr r0, [r0]
	cmp r1, r0
	bne _0805F5F2
	ldr r2, [r4, #0x54]
	cmp r2, r1
	ble _0805F5E4
	adds r0, r4, #0
	adds r0, #0xd8
	ldr r0, [r0]
	ldr r1, _0805F5E0 @ =0xFFFFE800
	adds r0, r0, r1
	b _0805F612
	.align 2, 0
_0805F5DC: .4byte pZero2
_0805F5E0: .4byte 0xFFFFE800
_0805F5E4:
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r0, r1
	b _0805F612
_0805F5F2:
	cmp r1, r0
	bge _0805F604
	adds r0, r4, #0
	adds r0, #0xd8
	ldr r0, [r0]
	ldr r1, _0805F600 @ =0xFFFFE800
	b _0805F60E
	.align 2, 0
_0805F600: .4byte 0xFFFFE800
_0805F604:
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #5
_0805F60E:
	adds r0, r0, r1
	ldr r2, [r4, #0x54]
_0805F612:
	subs r0, r0, r2
	movs r1, #0x2e
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, _0805F62C @ =0xFFFFFA40
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_0805f630
_0805F626:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F62C: .4byte 0xFFFFFA40

	thumb_func_start FUN_0805f630
FUN_0805f630: @ 0x0805F630
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F65C @ =0x083653E0
	bl SetDDP
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08060864
	adds r0, r4, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F654
	movs r0, #3
	strb r0, [r4, #0xf]
_0805F654:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F65C: .4byte 0x083653E0

	thumb_func_start FUN_0805f660
FUN_0805f660: @ 0x0805F660
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r0, #0x74
	ldr r1, _0805F68C @ =sCollisions
	bl SetDDP
	adds r0, r5, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	ble _0805F686
	movs r4, #4
	strb r4, [r5, #0xf]
	adds r0, r5, #0
	movs r1, #0
	bl FUN_080607a0
	strb r4, [r5, #0x12]
_0805F686:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805F68C: .4byte sCollisions
