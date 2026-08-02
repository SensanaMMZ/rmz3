	.include "asm/macros.inc"
	.syntax unified
	.text

	thumb_func_start killHeavyCannon
killHeavyCannon: @ 0x080CC1CC
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r1, [r4, #0xb]
	movs r0, #0xf7
	ands r0, r1
	movs r1, #0
	strb r0, [r4, #0xb]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r0, [r4, #0xa]
	movs r1, #0xfb
	ands r1, r0
	movs r0, #0xfe
	ands r1, r0
	strb r1, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r3, [r4, #0x58]
	ldr r2, _080CC270 @ =0xFFFFF800
	adds r0, r3, r2
	str r0, [sp, #4]
	adds r2, r0, #0
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _080CC212
	movs r0, #0x80
	lsls r0, r0, #4
	adds r2, r3, r0
_080CC212:
	str r2, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _080CC274 @ =gHeavyCannonMotions
	adds r0, r4, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b82c0
	ldrb r0, [r4, #0x10]
	cmp r0, #4
	beq _080CC256
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #0
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _080CC278 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _080CC27C @ =0x0000270E
	cmp r1, r0
	bhi _080CC24E
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_080CC24E:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
_080CC256:
	ldr r1, _080CC280 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CC270: .4byte 0xFFFFF800
_080CC274: .4byte gHeavyCannonMotions
_080CC278: .4byte gMission
_080CC27C: .4byte 0x0000270E
_080CC280: .4byte gSolidFnTable
