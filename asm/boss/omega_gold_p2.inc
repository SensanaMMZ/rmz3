	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start goldOmega1_0805b420
goldOmega1_0805b420: @ 0x0805B420
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0xe]
	cmp r0, #0
	beq _0805B430
	cmp r0, #1
	beq _0805B434
	b _0805B450
_0805B430:
	movs r0, #1
	strb r0, [r2, #0xe]
_0805B434:
	ldr r0, [r2, #0x18]
	ldrb r1, [r0, #9]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0805B450
	ldr r0, _0805B454 @ =gOverworld
	ldr r1, _0805B458 @ =0x0002D025
	adds r0, r0, r1
	movs r1, #0
	strb r3, [r0]
	strb r3, [r2, #0xd]
	strb r1, [r2, #0xe]
_0805B450:
	pop {r0}
	bx r0
	.align 2, 0
_0805B454: .4byte gOverworld
_0805B458: .4byte 0x0002D025
