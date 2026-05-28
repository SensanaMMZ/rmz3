	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start VFX44_Update
VFX44_Update: @ 0x080BE8F8
	push {lr}
	adds r2, r0, #0
	ldr r0, _080BE930 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _080BE910
	ldr r0, _080BE934 @ =gStageRun
	ldr r0, [r0, #0x30]
	cmp r0, #0
	beq _080BE93C
_080BE910:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080BE938 @ =gVFXFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x14]
	b _080BE94C
	.align 2, 0
_080BE930: .4byte gCurStory
_080BE934: .4byte gStageRun
_080BE938: .4byte gVFXFnTable
_080BE93C:
	ldr r0, _080BE950 @ =0x0836EFE0
	ldrb r1, [r2, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r2, #0
	bl _call_via_r1
_080BE94C:
	pop {r0}
	bx r0
	.align 2, 0
_080BE950: .4byte sUpdates
