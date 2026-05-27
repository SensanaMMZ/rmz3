	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c025c
FUN_080c025c: @ 0x080C025C
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080C02A0 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C0298
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C02A4 @ =gVFXFnTable
	movs r1, #0x31
	strb r1, [r3, #9]
	adds r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
_080C0298:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C02A0: .4byte gVFXHeaderPtr
_080C02A4: .4byte gVFXFnTable

	thumb_func_start createLaserSign
createLaserSign: @ 0x080C02A8
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r5, r1, #0
	adds r6, r2, #0
	ldr r0, _080C02EC @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080C02E6
	adds r0, #0x25
	movs r3, #0
	movs r2, #1
	strb r2, [r0]
	ldr r0, _080C02F0 @ =gVFXFnTable
	movs r1, #0x31
	strb r1, [r4, #9]
	adds r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r2, [r4, #0x10]
	str r5, [r4, #0x54]
	str r6, [r4, #0x58]
	str r7, [r4, #0x28]
_080C02E6:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C02EC: .4byte gVFXHeaderPtr
_080C02F0: .4byte gVFXFnTable

	thumb_func_start FUN_080c02f4
FUN_080c02f4: @ 0x080C02F4
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080C0338 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C0332
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C033C @ =gVFXFnTable
	movs r1, #0x31
	strb r1, [r3, #9]
	adds r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #2
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
_080C0332:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C0338: .4byte gVFXHeaderPtr
_080C033C: .4byte gVFXFnTable

	thumb_func_start FUN_080c0340
FUN_080c0340: @ 0x080C0340
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080C0380 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C037A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C0384 @ =gVFXFnTable
	movs r1, #0x31
	strb r1, [r3, #9]
	adds r0, #0xc4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #3
	strb r0, [r3, #0x10]
	str r4, [r3, #0x28]
_080C037A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C0380: .4byte gVFXHeaderPtr
_080C0384: .4byte gVFXFnTable

	thumb_func_start VFX49_Init
VFX49_Init: @ 0x080C0388
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080C03C8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080C03CC @ =0x0836F160
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
	bl VFX49_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C03C8: .4byte gVFXFnTable
_080C03CC: .4byte 0x0836F160
