	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start oz_080c39a0
oz_080c39a0: @ 0x080C39A0
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080C39E0 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C39DA
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C39E4 @ =gVFXFnTable
	movs r1, #0x40
	strb r1, [r3, #9]
	adds r1, #0xc0
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	str r4, [r3, #0x28]
	strb r0, [r3, #0x10]
_080C39DA:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C39E0: .4byte gVFXHeaderPtr
_080C39E4: .4byte gVFXFnTable

	thumb_func_start FUN_080c39e8
FUN_080c39e8: @ 0x080C39E8
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _080C3A4C @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080C3A44
	adds r0, #0x25
	movs r3, #0
	movs r2, #1
	strb r2, [r0]
	ldr r0, _080C3A50 @ =gVFXFnTable
	movs r1, #0x40
	strb r1, [r4, #9]
	adds r1, #0xc0
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	str r5, [r4, #0x28]
	strb r2, [r4, #0x10]
	ldr r3, [r5, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #4
	adds r0, r3, r1
	str r0, [r4, #0x54]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080C3A3A
	ldr r0, _080C3A54 @ =0xFFFFF400
	adds r2, r3, r0
_080C3A3A:
	str r2, [r4, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, _080C3A58 @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [r4, #0x58]
_080C3A44:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C3A4C: .4byte gVFXHeaderPtr
_080C3A50: .4byte gVFXFnTable
_080C3A54: .4byte 0xFFFFF400
_080C3A58: .4byte 0xFFFFE000

	thumb_func_start oz_Rekkoha_080c3a5c
oz_Rekkoha_080c3a5c: @ 0x080C3A5C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, _080C3AC4 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C3ABC
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C3AC8 @ =gVFXFnTable
	movs r1, #0x40
	strb r1, [r3, #9]
	adds r1, #0xc0
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	str r4, [r3, #0x28]
	movs r0, #3
	strb r0, [r3, #0x10]
	ldr r5, [r4, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #4
	adds r0, r5, r1
	str r0, [r3, #0x54]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080C3AB2
	ldr r0, _080C3ACC @ =0xFFFFF400
	adds r2, r5, r0
_080C3AB2:
	str r2, [r3, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _080C3AD0 @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [r3, #0x58]
_080C3ABC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C3AC4: .4byte gVFXHeaderPtr
_080C3AC8: .4byte gVFXFnTable
_080C3ACC: .4byte 0xFFFFF400
_080C3AD0: .4byte 0xFFFFE000

	thumb_func_start ozMessenkou2
ozMessenkou2: @ 0x080C3AD4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r0, _080C3B38 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C3B32
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r1, _080C3B3C @ =gVFXFnTable
	movs r0, #0x40
	strb r0, [r3, #9]
	movs r6, #0x80
	lsls r6, r6, #1
	adds r1, r1, r6
	ldr r0, [r1]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #2
	strb r0, [r3, #0x10]
	ldr r4, [r5, #0x54]
	ldr r1, _080C3B40 @ =0xFFFFFB00
	adds r0, r4, r1
	str r0, [r3, #0x54]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080C3B2A
	movs r0, #0xa0
	lsls r0, r0, #3
	adds r2, r4, r0
_080C3B2A:
	str r2, [r3, #0x54]
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r3, #0x58]
_080C3B32:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080C3B38: .4byte gVFXHeaderPtr
_080C3B3C: .4byte gVFXFnTable
_080C3B40: .4byte 0xFFFFFB00

	thumb_func_start oz_080c3b44
oz_080c3b44: @ 0x080C3B44
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080C3B90 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C3B8A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C3B94 @ =gVFXFnTable
	movs r1, #0x40
	strb r1, [r3, #9]
	adds r1, #0xc0
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #4
	strb r0, [r3, #0x10]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _080C3B98 @ =0xFFFFEA00
	adds r0, r0, r1
	str r0, [r3, #0x58]
_080C3B8A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C3B90: .4byte gVFXHeaderPtr
_080C3B94: .4byte gVFXFnTable
_080C3B98: .4byte 0xFFFFEA00

	thumb_func_start oz_080c3b9c
oz_080c3b9c: @ 0x080C3B9C
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080C3BE8 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C3BE2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C3BEC @ =gVFXFnTable
	movs r1, #0x40
	strb r1, [r3, #9]
	adds r1, #0xc0
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #5
	strb r0, [r3, #0x10]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _080C3BF0 @ =0xFFFFEA00
	adds r0, r0, r1
	str r0, [r3, #0x58]
_080C3BE2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C3BE8: .4byte gVFXHeaderPtr
_080C3BEC: .4byte gVFXFnTable
_080C3BF0: .4byte 0xFFFFEA00

	thumb_func_start FUN_080c3bf4
FUN_080c3bf4: @ 0x080C3BF4
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080C3C3C @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C3C34
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C3C40 @ =gVFXFnTable
	movs r1, #0x40
	strb r1, [r3, #9]
	adds r1, #0xc0
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #6
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
_080C3C34:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C3C3C: .4byte gVFXHeaderPtr
_080C3C40: .4byte gVFXFnTable

	thumb_func_start Ghost64_Init
Ghost64_Init: @ 0x080C3C44
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080C3C84 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080C3C88 @ =0x0836F57C
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
	bl Ghost64_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C3C84: .4byte gVFXFnTable
_080C3C88: .4byte 0x0836F57C
