	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c078c
FUN_080c078c: @ 0x080C078C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r4, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _080C07DC @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C07D4
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C07E0 @ =gVFXFnTable
	movs r1, #0x32
	strb r1, [r3, #9]
	adds r0, #0xc8
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r5, [r3, #0x10]
	strb r0, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r6, [r3, #0x28]
_080C07D4:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080C07DC: .4byte gVFXHeaderPtr
_080C07E0: .4byte gVFXFnTable

	thumb_func_start FUN_080c07e4
FUN_080c07e4: @ 0x080C07E4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	mov r8, r1
	lsls r2, r2, #0x18
	lsrs r6, r2, #0x18
	lsls r3, r3, #0x18
	lsrs r7, r3, #0x18
	ldr r0, _080C084C @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080C0840
	adds r0, #0x25
	movs r3, #0
	movs r2, #1
	strb r2, [r0]
	ldr r0, _080C0850 @ =gVFXFnTable
	movs r1, #0x32
	strb r1, [r4, #9]
	adds r0, #0xc8
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r6, [r4, #0x10]
	adds r0, r4, #0
	adds r0, #0x7c
	strb r7, [r0]
	strb r2, [r4, #0x11]
	ldr r0, [r5]
	str r0, [r4, #0x54]
	ldr r0, [r5, #4]
	str r0, [r4, #0x58]
	mov r1, r8
	ldr r0, [r1]
	str r0, [r4, #0x64]
	ldr r0, [r1, #4]
	str r0, [r4, #0x68]
_080C0840:
	adds r0, r4, #0
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080C084C: .4byte gVFXHeaderPtr
_080C0850: .4byte gVFXFnTable

	thumb_func_start VFX50_Init
VFX50_Init: @ 0x080C0854
	push {r4, r5, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r0, [r4, #0xa]
	movs r1, #1
	movs r5, #0
	orrs r1, r0
	movs r0, #2
	orrs r1, r0
	strb r1, [r4, #0xa]
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r2, [r4, #0x10]
	cmp r2, #0
	bne _080C0896
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0x80
	b _080C08BC
_080C0896:
	movs r2, #1
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	movs r0, #0x80
	rsbs r0, r0, #0
_080C08BC:
	str r0, [r4, #0x5c]
	movs r2, #0
	str r2, [r4, #0x60]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _080C08E4
	ldr r1, _080C08E0 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r1, [r4, #0xd]
	b _080C08F8
	.align 2, 0
_080C08E0: .4byte gVFXFnTable
_080C08E4:
	ldr r1, _080C0910 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
_080C08F8:
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	movs r0, #0
	str r0, [r4, #0x60]
	movs r0, #0xff
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	bl VFX50_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C0910: .4byte gVFXFnTable

	thumb_func_start VFX50_Update
VFX50_Update: @ 0x080C0914
	push {lr}
	ldr r2, _080C0928 @ =0x0836F178
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080C0928: .4byte 0x0836F178
