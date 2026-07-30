	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start OmegaGoldHand_Update
OmegaGoldHand_Update: @ 0x08082D70
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08082D9C
	ldr r1, _08082D98 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl OmegaGoldHand_Die
	b _08082E14
	.align 2, 0
_08082D98: .4byte gEnemyFnTable
_08082D9C:
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08082DB8
	ldr r0, _08082DB4 @ =0x08368188
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	b _08082DC8
	.align 2, 0
_08082DB4: .4byte 0x08368188
_08082DB8:
	ldr r0, _08082DD8 @ =0x083681A0
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_08082DC8:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _08082DE8
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08082DE0
	ldr r0, _08082DDC @ =0x083681B8
	b _08082DF0
	.align 2, 0
_08082DD8: .4byte 0x083681A0
_08082DDC: .4byte 0x083681B8
_08082DE0:
	ldr r0, _08082DE4 @ =0x083681E8
	b _08082DF0
	.align 2, 0
_08082DE4: .4byte 0x083681E8
_08082DE8:
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08082E04
	ldr r0, _08082E00 @ =0x083681D0
_08082DF0:
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	b _08082E14
	.align 2, 0
_08082E00: .4byte 0x083681D0
_08082E04:
	ldr r0, _08082E1C @ =0x08368200
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_08082E14:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08082E1C: .4byte 0x08368200
