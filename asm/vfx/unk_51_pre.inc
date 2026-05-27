	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreateVFX51
CreateVFX51: @ 0x080C0AA4
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r4, r1, #0
	adds r5, r2, #0
	ldr r0, _080C0AE8 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C0AE2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C0AEC @ =gVFXFnTable
	movs r1, #0x33
	strb r1, [r3, #9]
	adds r0, #0xcc
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
	str r6, [r3, #0x28]
_080C0AE2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080C0AE8: .4byte gVFXHeaderPtr
_080C0AEC: .4byte gVFXFnTable

	thumb_func_start VFX51_Init
VFX51_Init: @ 0x080C0AF0
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080C0B30 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080C0B34 @ =0x0836F1A0
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
	bl VFX51_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C0B30: .4byte gVFXFnTable
_080C0B34: .4byte 0x0836F1A0

	thumb_func_start VFX51_Update
VFX51_Update: @ 0x080C0B38
	push {lr}
	ldr r2, _080C0B4C @ =0x0836F19C
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080C0B4C: .4byte 0x0836F19C
