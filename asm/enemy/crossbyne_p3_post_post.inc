	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807d000
FUN_0807d000: @ 0x0807D000
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0807D03E
	cmp r0, #1
	bgt _0807D014
	cmp r0, #0
	beq _0807D01A
	b _0807D078
_0807D014:
	cmp r0, #2
	beq _0807D060
	b _0807D078
_0807D01A:
	movs r0, #0x20
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0807D058 @ =0x08367BB4
	bl SetDDP
	ldr r1, _0807D05C @ =0x08367C44
	ldrb r0, [r4, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807D03E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807D050
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807D050:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0807D078
	.align 2, 0
_0807D058: .4byte 0x08367BB4
_0807D05C: .4byte 0x08367C44
_0807D060:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	movs r1, #0
	ldrsb r1, [r0, r1]
	cmp r1, #3
	bne _0807D078
	movs r0, #0
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
_0807D078:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

