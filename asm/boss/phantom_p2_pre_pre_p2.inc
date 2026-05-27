	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f94c
FUN_0805f94c: @ 0x0805F94C
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F974 @ =sCollisions+(24*2)
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	movs r1, #0xb
	bl FUN_080607a0
	ldr r0, _0805F978 @ =0xFFFFFB00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_0805f97c
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F974: .4byte sCollisions+(24*2)
_0805F978: .4byte 0xFFFFFB00

	thumb_func_start FUN_0805f97c
FUN_0805f97c: @ 0x0805F97C
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060924
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F99A
	movs r0, #2
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	movs r1, #0xc
	bl FUN_080607a0
_0805F99A:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f9a0
FUN_0805f9a0: @ 0x0805F9A0
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r5, #4
	ands r0, r5
	cmp r0, #0
	beq _0805F9C8
	ldr r0, _0805F9C4 @ =0xFFFFFD00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0xd
	bl FUN_080607a0
	movs r0, #3
	strb r0, [r4, #0xf]
	b _0805F9D6
	.align 2, 0
_0805F9C4: .4byte 0xFFFFFD00
_0805F9C8:
	adds r0, r4, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F9D6
	strb r5, [r4, #0xf]
_0805F9D6:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f9dc
FUN_0805f9dc: @ 0x0805F9DC
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F9EE
	movs r0, #4
	strb r0, [r4, #0xf]
_0805F9EE:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f9f4
FUN_0805f9f4: @ 0x0805F9F4
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _0805FA08
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_0805FA08:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
