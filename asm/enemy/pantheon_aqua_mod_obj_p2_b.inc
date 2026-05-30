	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start PantheonAquaModObj_Update
PantheonAquaModObj_Update: @ 0x08080F34
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08080F64
	ldr r1, _08080F60 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl PantheonAquaModObj_Die
	b _08080F84
	.align 2, 0
_08080F60: .4byte gEnemyFnTable
_08080F64:
	ldr r1, _08080F8C @ =0x08367FB0
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _08080F90 @ =0x08367FD8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_08080F84:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080F8C: .4byte 0x08367FB0
_08080F90: .4byte 0x08367FD8

