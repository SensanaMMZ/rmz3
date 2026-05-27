	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c4fc8
FUN_080c4fc8: @ 0x080C4FC8
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080C5010 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C5006
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C5014 @ =gVFXFnTable
	movs r1, #0x45
	strb r1, [r3, #9]
	adds r1, #0xcf
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
_080C5006:
	adds r0, r3, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080C5010: .4byte gVFXHeaderPtr
_080C5014: .4byte gVFXFnTable

	thumb_func_start FUN_080c5018
FUN_080c5018: @ 0x080C5018
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	lsls r2, r2, #0x10
	lsrs r6, r2, #0x10
	ldr r0, _080C5070 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C5066
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C5074 @ =gVFXFnTable
	movs r1, #0x45
	strb r1, [r3, #9]
	adds r1, #0xcf
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	strb r5, [r3, #0x11]
	adds r0, r3, #0
	adds r0, #0x80
	strh r6, [r0]
_080C5066:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080C5070: .4byte gVFXHeaderPtr
_080C5074: .4byte gVFXFnTable

	thumb_func_start FUN_080c5078
FUN_080c5078: @ 0x080C5078
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	lsls r2, r2, #0x10
	lsrs r6, r2, #0x10
	lsls r3, r3, #0x10
	lsrs r7, r3, #0x10
	ldr r0, _080C50D8 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C50CE
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C50DC @ =gVFXFnTable
	movs r1, #0x45
	strb r1, [r3, #9]
	adds r1, #0xcf
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	strb r5, [r3, #0x11]
	adds r0, r3, #0
	adds r0, #0x82
	strh r6, [r0]
	subs r0, #2
	strh r7, [r0]
_080C50CE:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080C50D8: .4byte gVFXHeaderPtr
_080C50DC: .4byte gVFXFnTable

	thumb_func_start Ghost69_Init
Ghost69_Init: @ 0x080C50E0
	push {lr}
	ldr r2, _080C5108 @ =gVFXFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r2, #1
	str r2, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #4]
	str r1, [r0, #0x14]
	ldrb r1, [r0, #0x10]
	movs r2, #0
	strb r1, [r0, #0xd]
	strb r2, [r0, #0xe]
	strb r2, [r0, #0xf]
	bl Ghost69_Update
	pop {r0}
	bx r0
	.align 2, 0
_080C5108: .4byte gVFXFnTable
