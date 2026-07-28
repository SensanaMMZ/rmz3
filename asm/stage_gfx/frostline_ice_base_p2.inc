	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08011414
FUN_08011414: @ 0x08011414
	push {lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0xe]
	adds r1, r3, #0
	cmp r1, #0
	bne _0801142E
	movs r0, #0x40
	str r0, [r2, #0x44]
	adds r0, #0xc0
	str r0, [r2, #0x48]
	strh r1, [r2, #0x10]
	adds r0, r3, #1
	strb r0, [r2, #0xe]
_0801142E:
	ldr r1, [r2, #0x34]
	ldr r0, _0801143C @ =0x00001C1F
	cmp r1, r0
	bgt _08011444
	ldr r0, _08011440 @ =0x000012FC
	b _08011446
	.align 2, 0
_0801143C: .4byte 0x00001C1F
_08011440: .4byte 0x000012FC
_08011444:
	ldr r0, _08011460 @ =0x000015CC
_08011446:
	str r0, [r2, #0x4c]
	ldrh r0, [r2, #0x10]
	adds r0, #1
	strh r0, [r2, #0x10]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x30
	bne _0801145A
	movs r0, #0
	strh r0, [r2, #0x10]
_0801145A:
	pop {r0}
	bx r0
	.align 2, 0
_08011460: .4byte 0x000015CC

	thumb_func_start FUN_08011464
FUN_08011464: @ 0x08011464
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	adds r4, r0, #0
	mov r8, r1
	ldr r6, _080114C8 @ =gStageTilesetOffsets+(18*4)
	ldrh r0, [r4, #0x10]
	lsrs r0, r0, #3
	movs r1, #6
	bl __umodsi3
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	ldr r5, _080114CC @ =0x08704A20
	adds r1, r1, r5
	ldr r0, [r6]
	adds r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #7
	bl RequestGraphicTransfer
	ldrh r0, [r4, #0x10]
	lsrs r0, r0, #3
	movs r1, #6
	bl __umodsi3
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r5
	ldr r0, [r6]
	adds r0, r0, r1
	adds r0, #0xc
	movs r1, #0
	bl LoadPalette
	adds r0, r4, #0
	mov r1, r8
	bl DrawGeneralStageLayer
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080114C8: .4byte gStageTilesetOffsets+(18*4)
_080114CC: .4byte 0x08704A20

