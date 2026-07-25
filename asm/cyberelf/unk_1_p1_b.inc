	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080e234c
FUN_080e234c: @ 0x080E234C
	push {r4, lr}
	sub sp, #0xc
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r3, [r0]
	ldr r1, _080E239C @ =gZeroRanges
	ldr r2, _080E23A0 @ =0x00000147
	adds r0, r3, r2
	ldrb r0, [r0]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r1, [r0]
	ldr r2, [r0, #4]
	ldr r0, [r3, #0x54]
	str r0, [sp, #4]
	asrs r1, r1, #0x10
	ldr r0, [r3, #0x58]
	adds r0, r0, r1
	str r0, [sp, #8]
	adds r0, r4, #0
	adds r0, #0xbc
	adds r1, r4, #0
	adds r1, #0x64
	adds r3, r4, #0
	adds r3, #0xba
	movs r2, #0xa0
	str r2, [sp]
	add r2, sp, #4
	bl FUN_080e1578
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080E2394
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080E2394:
	add sp, #0xc
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080E239C: .4byte gZeroRanges
_080E23A0: .4byte 0x00000147

	thumb_func_start FUN_080e23a4
FUN_080e23a4: @ 0x080E23A4
	push {r4, lr}
	sub sp, #0xc
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r3, [r0]
	ldr r1, _080E23F4 @ =gZeroRanges
	ldr r2, _080E23F8 @ =0x00000147
	adds r0, r3, r2
	ldrb r0, [r0]
	lsls r0, r0, #3
	adds r0, r0, r1
	ldr r1, [r0]
	ldr r2, [r0, #4]
	ldr r0, [r3, #0x54]
	str r0, [sp, #4]
	asrs r1, r2, #0x10
	ldr r0, [r3, #0x58]
	subs r0, r0, r1
	str r0, [sp, #8]
	adds r0, r4, #0
	adds r0, #0xbc
	adds r1, r4, #0
	adds r1, #0x64
	adds r3, r4, #0
	adds r3, #0xba
	movs r2, #0xa0
	str r2, [sp]
	add r2, sp, #4
	bl FUN_080e1578
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080E23EC
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080E23EC:
	add sp, #0xc
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080E23F4: .4byte gZeroRanges
_080E23F8: .4byte 0x00000147
