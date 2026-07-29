	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b30b4
FUN_080b30b4: @ 0x080B30B4
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	adds r0, #8
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	ldr r1, _080B3130 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x12
	ldr r1, [r4, #0x5c]
	adds r1, r1, r0
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, _080B3134 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	cmp r0, #0
	bne _080B3116
	ldr r0, _080B3138 @ =gOverworld
	ldr r1, _080B313C @ =0x0002C00C
	adds r0, r0, r1
	ldr r1, [r4, #0x60]
	lsls r1, r1, #1
	ldr r2, [r4, #0x58]
	subs r1, r2, r1
	ldr r0, [r0]
	cmp r0, r1
	blt _080B3128
	ldr r0, [r4, #0x54]
	adds r1, r2, #0
	bl GetMetatileAttr
	lsls r0, r0, #0x10
	movs r1, #0x80
	lsls r1, r1, #0x18
	cmp r0, r1
	beq _080B3128
_080B3116:
	ldr r1, _080B3140 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B3128:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B3130: .4byte gSineTable
_080B3134: .4byte gStageRun+232
_080B3138: .4byte gOverworld
_080B313C: .4byte 0x0002C00C
_080B3140: .4byte gVFXFnTable

