	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0801478c
FUN_0801478c: @ 0x0801478C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	adds r7, r0, #0
	mov r8, r1
	ldr r0, [r7, #0x5c]
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	ldrb r4, [r7, #0xe]
	cmp r4, #1
	beq _080147E0
	cmp r4, #1
	bgt _080147AE
	cmp r4, #0
	beq _080147B4
	b _08014856
_080147AE:
	cmp r4, #2
	beq _0801484A
	b _08014856
_080147B4:
	lsrs r2, r0, #0x14
	lsls r2, r2, #1
	ldr r0, _08014864 @ =gVideoRegBuffer+4
	adds r2, r2, r0
	ldr r0, [r7, #0x60]
	ldr r1, [r7, #0x64]
	orrs r0, r1
	movs r1, #0x44
	orrs r0, r1
	strh r0, [r2]
	lsls r0, r5, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08014868 @ =gBgMapOffsets
	str r4, [sp]
	movs r2, #0x5e
	movs r3, #0
	bl LoadBgMap
	strh r4, [r7, #0x10]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080147E0:
	ldr r0, _0801486C @ =gOverworld
	ldr r1, _08014870 @ =0x0002D024
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #9
	bls _08014856
	mov r3, r8
	ldr r4, [r3, #8]
	lsrs r2, r5, #4
	lsls r2, r2, #1
	ldr r6, _08014864 @ =gVideoRegBuffer+4
	adds r2, r2, r6
	ldr r0, [r7, #0x64]
	ldr r3, _08014874 @ =0x00004046
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
	ldr r3, [r4]
	adds r3, r3, r4
	ldr r5, [r4, #8]
	adds r5, r5, r4
	adds r0, r7, #0
	adds r0, #0x14
	adds r1, r7, #0
	adds r1, #0x34
	ldr r2, [r7, #0x5c]
	lsrs r2, r2, #4
	lsls r2, r2, #1
	adds r2, r2, r6
	ldrh r4, [r2]
	movs r2, #0xf8
	lsls r2, r2, #5
	ands r2, r4
	lsls r2, r2, #3
	movs r4, #0xc0
	lsls r4, r4, #0x13
	adds r2, r2, r4
	str r5, [sp]
	ldrh r5, [r7, #0xc]
	lsls r5, r5, #2
	mov r4, r8
	adds r4, #0xc
	adds r4, r4, r5
	ldr r4, [r4]
	str r4, [sp, #4]
	bl ResetLayerGraphic
	ldr r0, _08014878 @ =0x80000001
	str r0, [r7, #0x40]
	str r0, [r7, #0x3c]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0801484A:
	ldr r0, _0801486C @ =gOverworld
	ldr r1, _0801487C @ =0x0002D03C
	adds r0, r0, r1
	ldr r0, [r0]
	asrs r0, r0, #8
	str r0, [r7, #0x4c]
_08014856:
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08014864: .4byte gVideoRegBuffer+4
_08014868: .4byte gBgMapOffsets
_0801486C: .4byte gOverworld
_08014870: .4byte 0x0002D024
_08014874: .4byte 0x00004046
_08014878: .4byte 0x80000001
_0801487C: .4byte 0x0002D03C
