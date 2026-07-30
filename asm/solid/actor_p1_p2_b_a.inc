	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Actor29_Update
Actor29_Update: @ 0x080D39FC
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r6, r0, #0
	ldrb r7, [r6, #0xd]
	cmp r7, #1
	beq _080D3A7E
	cmp r7, #1
	bgt _080D3A12
	cmp r7, #0
	beq _080D3A1A
	b _080D3B2E
_080D3A12:
	cmp r7, #2
	bne _080D3A18
	b _080D3B24
_080D3A18:
	b _080D3B2E
_080D3A1A:
	ldr r0, [r6, #0x54]
	ldr r1, _080D3AF8 @ =0xFFFF1000
	adds r0, r0, r1
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	adds r0, #1
	str r0, [r6, #0x58]
	ldr r0, _080D3AFC @ =wStaticGraphicTilenums
	movs r5, #0
	ldr r1, _080D3B00 @ =0x000003CE
	strh r1, [r0, #2]
	ldr r4, _080D3B04 @ =wStaticMotionPalIDs
	movs r0, #9
	strh r0, [r4, #2]
	ldr r0, _080D3B08 @ =0x085D790C
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D3B0C @ =0x085D7918
	ldrh r1, [r4, #2]
	ldrb r2, [r0, #7]
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	bl LoadPalette
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r6, #0
	bl SetMotion
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #8
	bl AppendQuake
	strb r5, [r6, #0x12]
	str r7, [r6, #0x60]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D3A7E:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, [r6, #0x60]
	adds r1, #0x10
	str r1, [r6, #0x60]
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r4, r6, #0
	adds r4, #0x54
	movs r0, #2
	adds r1, r4, #0
	bl AppendQuake
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	beq _080D3AD6
	ldr r0, [r6, #0x54]
	ldr r1, _080D3B10 @ =0xFFFFC000
	adds r0, r0, r1
	str r0, [sp]
	ldr r2, _080D3B14 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080D3B18 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080D3B1C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsls r0, r0, #3
	lsrs r0, r0, #0x14
	ldr r1, [r6, #0x58]
	adds r1, r1, r0
	str r1, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_080D3AD6:
	ldr r0, _080D3B20 @ =gStageRun+232
	adds r1, r4, #0
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #4
	cmp r0, r1
	bls _080D3B2E
	ldrb r0, [r6, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r6, #0xa]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
	b _080D3B2E
	.align 2, 0
_080D3AF8: .4byte 0xFFFF1000
_080D3AFC: .4byte wStaticGraphicTilenums
_080D3B00: .4byte 0x000003CE
_080D3B04: .4byte wStaticMotionPalIDs
_080D3B08: .4byte gStaticMotionGraphics+(20*1)
_080D3B0C: .4byte gStaticMotionGraphics+(20*1)+12
_080D3B10: .4byte 0xFFFFC000
_080D3B14: .4byte RNG_0202f388
_080D3B18: .4byte 0x000343FD
_080D3B1C: .4byte 0x00269EC3
_080D3B20: .4byte gStageRun+232
_080D3B24:
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #2
	bl AppendQuake
_080D3B2E:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
