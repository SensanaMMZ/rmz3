	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start ocean_0800d568
ocean_0800d568: @ 0x0800D568
	push {lr}
	ldr r0, [r0, #0x34]
	ldr r1, _0800D590 @ =0xFFFFE69F
	adds r0, r0, r1
	movs r1, #0xdf
	lsls r1, r1, #1
	cmp r0, r1
	bhi _0800D594
	movs r0, #0xe1
	bl isSoundPlaying
	cmp r0, #0
	bne _0800D588
	movs r0, #0xe1
	bl PlaySound
_0800D588:
	movs r0, #0xe1
	bl SetStageNoiseVolume
	b _0800D5A4
	.align 2, 0
_0800D590: .4byte 0xFFFFE69F
_0800D594:
	movs r0, #0xe1
	bl isSoundPlaying
	cmp r0, #0
	beq _0800D5A4
	movs r0, #0xe1
	bl StopSound
_0800D5A4:
	pop {r0}
	bx r0
