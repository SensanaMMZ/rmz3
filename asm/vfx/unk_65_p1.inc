	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreateGhost65
CreateGhost65: @ 0x080C4250
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	adds r7, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	ldr r0, _080C42A0 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C429A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C42A4 @ =gVFXFnTable
	movs r1, #0x41
	strb r1, [r3, #9]
	adds r1, #0xc3
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	strb r4, [r3, #0x12]
	str r6, [r3, #0x54]
	str r7, [r3, #0x58]
_080C429A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C42A0: .4byte gVFXHeaderPtr
_080C42A4: .4byte gVFXFnTable

	thumb_func_start Ghost65_Init
Ghost65_Init: @ 0x080C42A8
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080C42E8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080C42EC @ =0x0836F59C
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl Ghost65_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C42E8: .4byte gVFXFnTable
_080C42EC: .4byte 0x0836F59C
