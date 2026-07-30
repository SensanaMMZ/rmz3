	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyx_minigame_080fa560
copyx_minigame_080fa560: @ 0x080FA560
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r1, _080FA57C @ =0x00000DCC
	adds r5, r0, r1
	movs r1, #6
	ldrsh r0, [r5, r1]
	cmp r0, #1
	beq _080FA594
	cmp r0, #1
	bgt _080FA580
	cmp r0, #0
	beq _080FA58A
	b _080FA5CE
	.align 2, 0
_080FA57C: .4byte 0x00000DCC
_080FA580:
	cmp r0, #2
	beq _080FA5A8
	cmp r0, #3
	beq _080FA5BC
	b _080FA5CE
_080FA58A:
	movs r0, #0x3c
	strh r0, [r5]
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
_080FA594:
	ldrh r0, [r5]
	subs r0, #1
	strh r0, [r5]
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080FA5CE
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
	b _080FA5CE
_080FA5A8:
	movs r0, #0
	bl CreateMissionAlert
	str r0, [r5, #0x10]
	movs r0, #0x1d
	bl PlaySound
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
_080FA5BC:
	ldr r0, [r5, #0x10]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080FA5CE
	ldrh r0, [r5, #4]
	adds r0, #1
	movs r1, #0
	strh r0, [r5, #4]
	strh r1, [r5, #6]
_080FA5CE:
	ldr r1, _080FA624 @ =0x0810E25C
	mov r0, sp
	movs r2, #6
	bl memcpy
	mov r0, sp
	movs r1, #0x12
	movs r2, #0
	bl PrintUnicodeString
	ldr r4, [r5, #0x1c]
	adds r0, r4, #0
	movs r1, #0x1b
	movs r2, #0
	bl PrintMinigameNumber
	ldr r0, [r5, #0x24]
	cmp r4, r0
	bls _080FA5F6
	str r4, [r5, #0x24]
_080FA5F6:
	add r4, sp, #8
	ldr r1, _080FA628 @ =0x0810E264
	adds r0, r4, #0
	movs r2, #9
	bl memcpy
	adds r0, r4, #0
	movs r1, #0xf
	movs r2, #1
	bl PrintUnicodeString
	ldr r4, [r5, #0x24]
	adds r0, r4, #0
	movs r1, #0x1b
	movs r2, #1
	bl PrintMinigameNumber
	movs r0, #1
	add sp, #0x14
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080FA624: .4byte 0x0810E25C
_080FA628: .4byte 0x0810E264

