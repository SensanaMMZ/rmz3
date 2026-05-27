	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c4c2c
FUN_080c4c2c: @ 0x080C4C2C
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r6, r0, #0
	adds r7, r1, #0
	mov r8, r2
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	mov sb, r5
	ldr r0, _080C4CC4 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080C4CB8
	adds r0, #0x25
	movs r3, #0
	movs r2, #1
	strb r2, [r0]
	ldr r0, _080C4CC8 @ =gVFXFnTable
	movs r1, #0x44
	strb r1, [r4, #9]
	adds r1, #0xcc
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r2, [r4, #0x10]
	str r6, [r4, #0x54]
	str r7, [r4, #0x58]
	ldr r1, _080C4CCC @ =gSineTable
	adds r0, r5, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r2, #0
	ldrsh r0, [r0, r2]
	mov r2, r8
	muls r2, r0, r2
	adds r0, r2, #0
	cmp r0, #0
	bge _080C4C92
	adds r0, #0xff
_080C4C92:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	mov r2, sb
	lsls r0, r2, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	mov r2, r8
	muls r2, r0, r2
	adds r0, r2, #0
	cmp r0, #0
	bge _080C4CAC
	adds r0, #0xff
_080C4CAC:
	asrs r0, r0, #8
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_080afda4
	str r0, [r4, #0x2c]
_080C4CB8:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C4CC4: .4byte gVFXHeaderPtr
_080C4CC8: .4byte gVFXFnTable
_080C4CCC: .4byte gSineTable

	thumb_func_start Ghost68_Init
Ghost68_Init: @ 0x080C4CD0
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080C4CF0 @ =0x0836F6BC
	ldrb r0, [r4, #0x10]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl Ghost68_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C4CF0: .4byte sGhost68Initializers
