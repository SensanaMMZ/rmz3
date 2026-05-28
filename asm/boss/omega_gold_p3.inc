	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start makeGoldOmega1Mode2
makeGoldOmega1Mode2: @ 0x0805B460
	push {lr}
	adds r2, r0, #0
	ldrb r1, [r2, #0xe]
	cmp r1, #1
	beq _0805B482
	cmp r1, #1
	bgt _0805B474
	cmp r1, #0
	beq _0805B47A
	b _0805B49E
_0805B474:
	cmp r1, #2
	beq _0805B498
	b _0805B49E
_0805B47A:
	movs r0, #1
	strb r0, [r2, #0xe]
	movs r0, #0x3c
	strb r0, [r2, #0x12]
_0805B482:
	ldrb r0, [r2, #0x12]
	cmp r0, #0
	beq _0805B492
	subs r0, #1
	strb r0, [r2, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805B49E
_0805B492:
	ldrb r0, [r2, #0xe]
	adds r0, #1
	b _0805B49C
_0805B498:
	movs r0, #0
	strb r1, [r2, #0xd]
_0805B49C:
	strb r0, [r2, #0xe]
_0805B49E:
	pop {r0}
	bx r0
	.align 2, 0
