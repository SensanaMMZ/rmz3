	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080bb830
FUN_080bb830: @ 0x080BB830
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _080BB870 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r4, r0, #0
	cmp r4, #0
	beq _080BB868
	adds r2, r4, #0
	adds r2, #0x25
	movs r3, #0
	movs r1, #1
	strb r1, [r2]
	ldr r1, _080BB874 @ =gVFXFnTable
	movs r2, #0x21
	strb r2, [r4, #9]
	adds r1, #0x84
	ldr r1, [r1]
	ldr r1, [r1]
	str r1, [r4, #0x14]
	movs r1, #0
	strh r3, [r4, #0x20]
	adds r2, r4, #0
	adds r2, #0x22
	strb r1, [r2]
	strb r1, [r4, #0x10]
	str r5, [r4, #0x28]
_080BB868:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080BB870: .4byte gVFXHeaderPtr
_080BB874: .4byte gVFXFnTable

	thumb_func_start FUN_080bb878
FUN_080bb878: @ 0x080BB878
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r0, _080BB8B8 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r5, r0, #0
	cmp r5, #0
	beq _080BB8B0
	adds r1, r5, #0
	adds r1, #0x25
	movs r4, #0
	movs r3, #1
	strb r3, [r1]
	ldr r1, _080BB8BC @ =gVFXFnTable
	movs r2, #0x21
	strb r2, [r5, #9]
	adds r1, #0x84
	ldr r1, [r1]
	ldr r1, [r1]
	str r1, [r5, #0x14]
	movs r1, #0
	strh r4, [r5, #0x20]
	adds r2, r5, #0
	adds r2, #0x22
	strb r1, [r2]
	strb r3, [r5, #0x10]
	str r6, [r5, #0x28]
_080BB8B0:
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080BB8B8: .4byte gVFXHeaderPtr
_080BB8BC: .4byte gVFXFnTable

	thumb_func_start FUN_080bb8c0
FUN_080bb8c0: @ 0x080BB8C0
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _080BB900 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r4, r0, #0
	cmp r4, #0
	beq _080BB8FA
	adds r2, r4, #0
	adds r2, #0x25
	movs r3, #0
	movs r1, #1
	strb r1, [r2]
	ldr r1, _080BB904 @ =gVFXFnTable
	movs r2, #0x21
	strb r2, [r4, #9]
	adds r1, #0x84
	ldr r1, [r1]
	ldr r1, [r1]
	str r1, [r4, #0x14]
	movs r1, #0
	strh r3, [r4, #0x20]
	adds r2, r4, #0
	adds r2, #0x22
	strb r1, [r2]
	movs r1, #2
	strb r1, [r4, #0x10]
	str r5, [r4, #0x28]
_080BB8FA:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080BB900: .4byte gVFXHeaderPtr
_080BB904: .4byte gVFXFnTable

	thumb_func_start FUN_080bb908
FUN_080bb908: @ 0x080BB908
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	adds r6, r1, #0
	movs r4, #0
	movs r5, #0
	ldr r0, _080BB960 @ =0x0836D984
	mov r8, r0
_080BB91A:
	ldr r0, _080BB964 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r1, r0, #0
	cmp r1, #0
	beq _080BB94E
	adds r2, r1, #0
	adds r2, #0x25
	movs r0, #1
	strb r0, [r2]
	movs r0, #0x21
	strb r0, [r1, #9]
	mov r2, r8
	ldr r0, [r2]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r5, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r5, [r0]
	movs r0, #3
	strb r0, [r1, #0x10]
	strb r4, [r1, #0x11]
	str r7, [r1, #0x54]
	str r6, [r1, #0x58]
_080BB94E:
	adds r4, #1
	cmp r4, #2
	ble _080BB91A
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080BB960: .4byte 0x0836D984
_080BB964: .4byte gVFXHeaderPtr

	thumb_func_start Ghost33_Init
Ghost33_Init: @ 0x080BB968
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080BB9A8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080BB9AC @ =0x0836ED60
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
	bl Ghost33_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BB9A8: .4byte gVFXFnTable
_080BB9AC: .4byte 0x0836ED60

	thumb_func_start Ghost33_Update
Ghost33_Update: @ 0x080BB9B0
	push {lr}
	adds r2, r0, #0
	ldr r0, _080BB9E0 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080BB9E8
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080BB9E4 @ =gVFXFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x14]
	b _080BB9F8
	.align 2, 0
_080BB9E0: .4byte gCurStory
_080BB9E4: .4byte gVFXFnTable
_080BB9E8:
	ldr r0, _080BB9FC @ =0x0836ED50
	ldrb r1, [r2, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r2, #0
	bl _call_via_r1
_080BB9F8:
	pop {r0}
	bx r0
	.align 2, 0
_080BB9FC: .4byte 0x0836ED50
