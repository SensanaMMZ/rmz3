	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start leviathan_minigame_080fbcdc
leviathan_minigame_080fbcdc: @ 0x080FBCDC
	push {r4, r5, lr}
	adds r1, r0, #0
	ldr r0, _080FBD20 @ =0x00000DCC
	adds r4, r1, r0
	movs r5, #0
	strh r5, [r4, #0x10]
	strh r5, [r4, #0x12]
	adds r0, #0x31
	adds r2, r1, r0
	ldrb r0, [r2]
	cmp r0, #0
	beq _080FBCF8
	subs r0, #1
	strb r0, [r2]
_080FBCF8:
	adds r0, r1, #0
	bl leviathan_minigame_080fb5dc
	ldr r0, [r4, #0x20]
	ldr r1, _080FBD24 @ =0x00002A30
	cmp r0, r1
	ble _080FBD08
	str r1, [r4, #0x20]
_080FBD08:
	ldr r0, [r4, #0x20]
	cmp r0, #0
	bgt _080FBD10
	str r5, [r4, #0x20]
_080FBD10:
	ldrb r0, [r4, #1]
	cmp r0, #5
	bhi _080FBDB4
	lsls r0, r0, #2
	ldr r1, _080FBD28 @ =_080FBD2C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080FBD20: .4byte 0x00000DCC
_080FBD24: .4byte 0x00002A30
_080FBD28: .4byte _080FBD2C
_080FBD2C: @ jump table
	.4byte _080FBD44 @ case 0
	.4byte _080FBD5E @ case 1
	.4byte _080FBD70 @ case 2
	.4byte _080FBD7E @ case 3
	.4byte _080FBD8E @ case 4
	.4byte _080FBD9A @ case 5
_080FBD44:
	movs r0, #0xb6
	bl fadeoutBGM
	movs r0, #0xf6
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x33
	movs r0, #0x3c
	strb r0, [r1]
	ldrb r0, [r4, #1]
	adds r0, #1
	strb r0, [r4, #1]
_080FBD5E:
	adds r1, r4, #0
	adds r1, #0x33
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080FBDB4
	b _080FBD86
_080FBD70:
	movs r0, #4
	bl CreateMissionAlert
	str r0, [r4, #8]
	ldrb r0, [r4, #1]
	adds r0, #1
	strb r0, [r4, #1]
_080FBD7E:
	ldr r0, [r4, #8]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080FBDB4
_080FBD86:
	ldrb r0, [r4, #1]
	adds r0, #1
	strb r0, [r4, #1]
	b _080FBDB4
_080FBD8E:
	ldr r1, _080FBDB0 @ =gGameState
	movs r0, #0x40
	strh r0, [r1, #4]
	ldrb r0, [r4, #1]
	adds r0, #1
	strb r0, [r4, #1]
_080FBD9A:
	ldr r0, _080FBDB0 @ =gGameState
	movs r1, #4
	ldrsh r0, [r0, r1]
	cmp r0, #0x20
	bne _080FBDB4
	movs r0, #0x32
	bl StopSound
	movs r0, #0
	b _080FBDB6
	.align 2, 0
_080FBDB0: .4byte gGameState
_080FBDB4:
	movs r0, #1
_080FBDB6:
	pop {r4, r5}
	pop {r1}
	bx r1
