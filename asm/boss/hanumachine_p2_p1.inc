	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start hanu_0805c670
hanu_0805c670: @ 0x0805C670
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805C714
	ldr r1, _0805C6C8 @ =0x0000B506
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805C6CC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C692
	movs r3, #1
_0805C692:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C6A4
	movs r3, #1
_0805C6A4:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _0805C6D0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805C6D6
	.align 2, 0
_0805C6C8: .4byte 0x0000B506
_0805C6CC: .4byte pZero2
_0805C6D0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805C6D6:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805C6F4
	ldr r0, _0805C6EC @ =0xFFFFFE80
	str r0, [r4, #0x5c]
	ldr r0, _0805C6F0 @ =0xFFFFF000
	b _0805C6FE
	.align 2, 0
_0805C6EC: .4byte 0xFFFFFE80
_0805C6F0: .4byte 0xFFFFF000
_0805C6F4:
	movs r0, #0xc0
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #5
_0805C6FE:
	str r0, [r4, #0x64]
	ldr r0, _0805C75C @ =0xFFFFFC40
	str r0, [r4, #0x60]
	movs r0, #0xe
	strb r0, [r4, #0x12]
	movs r0, #0x50
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C714:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x64]
	adds r0, r4, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805C732
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805C732:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805C754
	movs r0, #0xe
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_0805C754:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805C75C: .4byte 0xFFFFFC40

