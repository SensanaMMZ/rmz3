	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start zsaber_0803c0f4
zsaber_0803c0f4: @ 0x0803C0F4
	push {lr}
	ldr r0, [r0, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0803C10E
	ldr r2, _0803C114 @ =gMission
	ldrh r1, [r2, #0x1e]
	ldr r0, _0803C118 @ =0x0000FFFE
	cmp r1, r0
	bhi _0803C10E
	adds r0, r1, #1
	strh r0, [r2, #0x1e]
_0803C10E:
	pop {r0}
	bx r0
	.align 2, 0
_0803C114: .4byte gMission
_0803C118: .4byte 0x0000FFFE

