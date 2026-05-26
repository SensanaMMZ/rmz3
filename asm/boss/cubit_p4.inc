	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cubitMode2
cubitMode2: @ 0x08052C34
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08052C44
	cmp r0, #1
	beq _08052C52
	b _08052C6A
_08052C44:
	ldr r1, _08052C70 @ =0x0000B002
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08052C52:
	ldr r0, _08052C74 @ =gStageRun
	ldrb r0, [r0, #0x12]
	movs r1, #1
	ands r1, r0
	cmp r1, #0
	bne _08052C64
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08052C64:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08052C6A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08052C70: .4byte 0x0000B002
_08052C74: .4byte gStageRun
