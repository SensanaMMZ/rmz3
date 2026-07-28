	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805fb8c
FUN_0805fb8c: @ 0x0805FB8C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	subs r3, r0, #1
	strb r3, [r5, #0x12]
	cmp r3, #0
	bne _0805FC04
	movs r0, #6
	strb r0, [r5, #0xf]
	ldr r2, _0805FC0C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805FC10 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805FC14 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r6, r0, #0x11
	movs r0, #3
	ands r6, r0
	subs r1, r6, #2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xc
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r5, #0x54]
	adds r0, r1, r0
	str r0, [r5, #0x64]
	movs r2, #0
	subs r0, r0, r1
	cmp r0, #0
	ble _0805FBD4
	movs r2, #1
_0805FBD4:
	lsls r0, r2, #9
	ldr r1, _0805FC18 @ =0xFFFFFF00
	adds r0, r0, r1
	str r0, [r5, #0x5c]
	strb r3, [r5, #0x12]
	adds r0, r5, #0
	adds r0, #0xc4
	str r3, [r0]
	movs r4, #0
_0805FBE6:
	cmp r4, r6
	beq _0805FBF2
	adds r0, r5, #0
	adds r1, r4, #0
	bl FUN_0809130c
_0805FBF2:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #3
	bls _0805FBE6
	adds r0, r5, #0
	movs r1, #4
	bl FUN_0809130c
_0805FC04:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0805FC0C: .4byte RNG_0202f388
_0805FC10: .4byte 0x000343FD
_0805FC14: .4byte 0x00269EC3
_0805FC18: .4byte 0xFFFFFF00

