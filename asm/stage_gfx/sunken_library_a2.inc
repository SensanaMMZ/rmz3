	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08013b10
FUN_08013b10: @ 0x08013B10
	push {r4, lr}
	ldr r3, [r0, #0x68]
	cmp r3, #0
	beq _08013B4E
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _08013B68 @ =gSolidFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
_08013B4E:
	movs r4, #0x92
	lsls r4, r4, #1
	adds r0, r4, #0
	bl isSoundPlaying
	cmp r0, #0
	beq _08013B62
	adds r0, r4, #0
	bl StopSound
_08013B62:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08013B68: .4byte gSolidFnTable
