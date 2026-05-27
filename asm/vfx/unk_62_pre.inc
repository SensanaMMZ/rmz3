	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreateVFX62
CreateVFX62: @ 0x080C34C0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	adds r5, r1, #0
	movs r4, #0
	movs r6, #0
	ldr r0, _080C351C @ =0x0836D9F8
	mov r8, r0
_080C34D2:
	ldr r0, _080C3520 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r1, r0, #0
	cmp r1, #0
	beq _080C350A
	adds r2, r1, #0
	adds r2, #0x25
	movs r0, #1
	strb r0, [r2]
	movs r0, #0x3e
	strb r0, [r1, #9]
	mov r2, r8
	ldr r0, [r2]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r6, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r6, [r0]
	strb r6, [r1, #0x10]
	strb r4, [r1, #0x11]
	str r7, [r1, #0x28]
	ldr r0, [r5]
	str r0, [r1, #0x54]
	ldr r0, [r5, #4]
	str r0, [r1, #0x58]
_080C350A:
	adds r4, #1
	cmp r4, #2
	ble _080C34D2
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C351C: .4byte 0x0836D9F8
_080C3520: .4byte gVFXHeaderPtr

	thumb_func_start VFX62_Init
VFX62_Init: @ 0x080C3524
	push {lr}
	ldr r2, _080C3538 @ =0x0836F4B0
	ldrb r1, [r0, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080C3538: .4byte 0x0836F4B0

	thumb_func_start VFX62_Update
VFX62_Update: @ 0x080C353C
	push {lr}
	ldr r2, _080C3550 @ =0x0836F4B4
	ldrb r1, [r0, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080C3550: .4byte 0x0836F4B4
