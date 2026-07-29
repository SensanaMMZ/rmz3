	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Actor23_Update
Actor23_Update: @ 0x080D31B0
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D31EE
	ldr r0, _080D31F4 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	ldr r1, _080D31F8 @ =0x00000FFF
	cmp r0, r1
	bhi _080D31EE
	ldr r0, [r4, #0x5c]
	adds r0, #4
	str r0, [r4, #0x5c]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080D31E0
	str r1, [r4, #0x5c]
_080D31E0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	subs r0, r0, r1
	str r0, [r4, #0x58]
_080D31EE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080D31F4: .4byte gStageRun+232
_080D31F8: .4byte 0x00000FFF

