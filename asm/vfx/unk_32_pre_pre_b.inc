	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080baca4
FUN_080baca4: @ 0x080BACA4
	push {r4, lr}
	adds r4, r0, #0
	bl InitScalerotMotion1
	movs r1, #0x80
	lsls r1, r1, #1
	str r1, [r4, #0x7c]
	adds r0, r4, #0
	adds r0, #0x50
	movs r2, #0
	strh r1, [r0]
	ldr r0, [r4, #0x7c]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	adds r0, r4, #0
	adds r0, #0x24
	strb r2, [r0]
	ldr r1, _080BACE8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BACE8: .4byte gVFXFnTable

	thumb_func_start FUN_080bacec
FUN_080bacec: @ 0x080BACEC
	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	movs r1, #0x80
	lsls r1, r1, #1
	str r1, [r4, #0x7c]
	adds r0, r4, #0
	adds r0, #0x50
	movs r2, #0
	strh r1, [r0]
	ldr r0, [r4, #0x7c]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	adds r0, r4, #0
	adds r0, #0x24
	strb r2, [r0]
	ldr r1, _080BAD30 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BAD30: .4byte gVFXFnTable

	thumb_func_start FUN_080bad34
FUN_080bad34: @ 0x080BAD34
	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	movs r1, #0x80
	lsls r1, r1, #1
	str r1, [r4, #0x7c]
	adds r0, r4, #0
	adds r0, #0x50
	movs r2, #0
	strh r1, [r0]
	ldr r0, [r4, #0x7c]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	adds r0, r4, #0
	adds r0, #0x24
	strb r2, [r0]
	ldr r1, _080BAD78 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BAD78: .4byte gVFXFnTable
