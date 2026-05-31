	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start FUN_080babac
FUN_080babac: @ 0x080BABAC
	push {r4, lr}
	adds r4, r0, #0
	bl InitScalerotMotion1
	movs r1, #0x80
	lsls r1, r1, #1
	str r1, [r4, #0x7c]
	adds r0, r4, #0
	adds r0, #0x50
	movs r3, #0
	strh r1, [r0]
	ldr r0, [r4, #0x7c]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	ldr r2, _080BAC04 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BAC08 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BAC0C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r1, _080BAC10 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r3, [r4, #0xe]
	strb r3, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BAC04: .4byte RNG_0202f388
_080BAC08: .4byte 0x000343FD
_080BAC0C: .4byte 0x00269EC3
_080BAC10: .4byte gVFXFnTable

	thumb_func_start FUN_080bac14
FUN_080bac14: @ 0x080BAC14
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
	ldr r1, _080BAC58 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BAC58: .4byte gVFXFnTable

	thumb_func_start FUN_080bac5c
FUN_080bac5c: @ 0x080BAC5C
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
	ldr r1, _080BACA0 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	movs r1, #4
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r1, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BACA0: .4byte gVFXFnTable

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
