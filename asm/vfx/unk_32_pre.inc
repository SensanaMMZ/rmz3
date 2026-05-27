	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080baad8
FUN_080baad8: @ 0x080BAAD8
	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r2, [r4, #0x10]
	cmp r2, #0
	bne _080BAB06
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
	movs r0, #0x60
	b _080BAB2C
_080BAB06:
	movs r2, #1
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
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
	movs r0, #0x60
	rsbs r0, r0, #0
_080BAB2C:
	str r0, [r4, #0x5c]
	movs r2, #0
	str r2, [r4, #0x60]
	ldr r1, _080BAB50 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BAB50: .4byte gVFXFnTable

	thumb_func_start FUN_080bab54
FUN_080bab54: @ 0x080BAB54
	push {r4, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	movs r3, #0
	str r3, [r4, #0x5c]
	str r3, [r4, #0x60]
	ldr r2, _080BAB9C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BABA0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BABA4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #7
	ands r0, r1
	adds r0, #0x7f
	strb r0, [r4, #0x12]
	ldr r1, _080BABA8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r1, [r4, #0xd]
	strb r3, [r4, #0xe]
	strb r3, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BAB9C: .4byte RNG_0202f388
_080BABA0: .4byte 0x000343FD
_080BABA4: .4byte 0x00269EC3
_080BABA8: .4byte gVFXFnTable

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

	thumb_func_start Ghost32_Update
Ghost32_Update: @ 0x080BAD7C
	push {lr}
	adds r2, r0, #0
	ldr r0, _080BADA8 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080BADB0
	ldr r1, _080BADAC @ =gVFXFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	adds r0, r2, #0
	bl Ghost32_Die
	b _080BADC0
	.align 2, 0
_080BADA8: .4byte gCurStory
_080BADAC: .4byte gVFXFnTable
_080BADB0:
	ldr r0, _080BADC4 @ =0x0836EC44
	ldrb r1, [r2, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r2, #0
	bl _call_via_r1
_080BADC0:
	pop {r0}
	bx r0
	.align 2, 0
_080BADC4: .4byte 0x0836EC44
