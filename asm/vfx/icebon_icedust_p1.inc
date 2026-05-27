	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createIcebonIce
createIcebonIce: @ 0x080B9864
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080B98A4 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080B989E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r1, _080B98A8 @ =gVFXFnTable
	movs r0, #0x1a
	strb r0, [r3, #9]
	ldr r0, [r1, #0x68]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
	strb r0, [r3, #0x10]
_080B989E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080B98A4: .4byte gVFXHeaderPtr
_080B98A8: .4byte gVFXFnTable

	thumb_func_start FUN_080b98ac
FUN_080b98ac: @ 0x080B98AC
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	ldr r0, _080B98EC @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r4, r0, #0
	cmp r4, #0
	beq _080B98E4
	adds r0, #0x25
	movs r3, #0
	movs r2, #1
	strb r2, [r0]
	ldr r1, _080B98F0 @ =gVFXFnTable
	movs r0, #0x1a
	strb r0, [r4, #9]
	ldr r0, [r1, #0x68]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	str r5, [r4, #0x54]
	str r6, [r4, #0x58]
	strb r2, [r4, #0x10]
_080B98E4:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B98EC: .4byte gVFXHeaderPtr
_080B98F0: .4byte gVFXFnTable

	thumb_func_start IcebonIcedust_Init
IcebonIcedust_Init: @ 0x080B98F4
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080B9934 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _080B9938 @ =0x0836EAFC
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
	bl IcebonIcedust_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B9934: .4byte gVFXFnTable
_080B9938: .4byte 0x0836EAFC
