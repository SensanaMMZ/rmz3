	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Ghost73_Update
Ghost73_Update: @ 0x080C6EF0
	push {lr}
	adds r2, r0, #0
	ldr r0, _080C6F20 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080C6F28
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080C6F24 @ =gVFXFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x14]
	b _080C6F38
	.align 2, 0
_080C6F20: .4byte gCurStory
_080C6F24: .4byte gVFXFnTable
_080C6F28:
	ldr r0, _080C6F3C @ =0x0836F87C
	ldrb r1, [r2, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r2, #0
	bl _call_via_r1
_080C6F38:
	pop {r0}
	bx r0
	.align 2, 0
_080C6F3C: .4byte 0x0836F87C
