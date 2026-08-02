	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0800f6f8
FUN_0800f6f8: @ 0x0800F6F8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0xc
	adds r6, r0, #0
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	ldr r0, _0800F720 @ =gOverworld
	ldr r1, _0800F724 @ =0x0002D026
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0800F72C
	ldr r0, _0800F728 @ =gVideoRegBuffer
	lsls r1, r5, #8
	ldrh r2, [r0]
	orrs r1, r2
	strh r1, [r0]
	b _0800F736
	.align 2, 0
_0800F720: .4byte gOverworld
_0800F724: .4byte 0x0002D026
_0800F728: .4byte gVideoRegBuffer
_0800F72C:
	ldr r2, _0800F808 @ =gVideoRegBuffer
	lsls r1, r5, #8
	ldrh r0, [r2]
	bics r0, r1
	strh r0, [r2]
_0800F736:
	ldr r7, _0800F80C @ =gOverworld
	ldr r2, _0800F810 @ =0x0002C002
	adds r0, r7, r2
	ldrh r0, [r0]
	lsrs r1, r5, #4
	mov r8, r1
	cmp r0, #0
	beq _0800F778
	movs r4, #0
	lsls r0, r1, #1
	ldr r1, _0800F814 @ =gVideoRegBuffer+4
	adds r0, r0, r1
	ldrh r0, [r0]
	movs r1, #0xf8
	lsls r1, r1, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r1, r1, r0
	str r4, [sp, #4]
	ldr r2, _0800F818 @ =0x01000400
	add r0, sp, #4
	bl CpuFastSet
	lsls r0, r5, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _0800F81C @ =gBgMapOffsets
	str r4, [sp]
	movs r2, #0x59
	movs r3, #0
	bl LoadBgMap
_0800F778:
	ldr r2, _0800F820 @ =0x0002D038
	adds r0, r7, r2
	ldr r2, [r0]
	adds r5, r7, #0
	cmp r2, #0
	beq _0800F7C2
	ldr r7, _0800F824 @ =0x0002D03C
	adds r1, r5, r7
	ldr r0, [r2, #0x54]
	str r0, [r1]
	ldr r0, _0800F828 @ =0x0002D040
	adds r1, r5, r0
	ldr r0, [r2, #0x58]
	str r0, [r1]
	ldr r0, _0800F82C @ =gWhitePaintFlags
	ldrb r1, [r2, #0x1d]
	lsrs r2, r1, #5
	lsls r2, r2, #2
	adds r2, r2, r0
	movs r0, #0x1f
	ands r0, r1
	movs r1, #1
	lsls r1, r0
	ldr r0, [r2]
	ands r0, r1
	cmp r0, #0
	beq _0800F7C2
	ldr r1, _0800F830 @ =gPaletteManager
	ldr r7, _0800F834 @ =0x00000404
	adds r2, r1, r7
	movs r0, #0xc0
	lsls r0, r0, #1
	strh r0, [r2]
	ldr r0, _0800F838 @ =0x00000406
	adds r1, r1, r0
	movs r0, #0x20
	strh r0, [r1]
_0800F7C2:
	mov r1, r8
	lsls r3, r1, #2
	ldr r2, _0800F83C @ =gVideoRegBuffer+12
	adds r4, r3, r2
	ldr r1, [r6, #0x34]
	ldr r7, _0800F824 @ =0x0002D03C
	adds r0, r5, r7
	ldr r0, [r0]
	asrs r0, r0, #8
	subs r1, r1, r0
	adds r1, #0x30
	ldr r0, [r6, #0x2c]
	asrs r0, r0, #8
	adds r1, r1, r0
	strh r1, [r4]
	adds r2, #2
	adds r3, r3, r2
	ldr r1, [r6, #0x38]
	ldr r2, _0800F828 @ =0x0002D040
	adds r0, r5, r2
	ldr r0, [r0]
	asrs r0, r0, #8
	subs r1, r1, r0
	adds r1, #0x90
	ldr r0, [r6, #0x30]
	asrs r0, r0, #8
	adds r1, r1, r0
	strh r1, [r3]
	add sp, #0xc
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0800F808: .4byte gVideoRegBuffer
_0800F80C: .4byte gOverworld
_0800F810: .4byte 0x0002C002
_0800F814: .4byte gVideoRegBuffer+4
_0800F818: .4byte 0x01000400
_0800F81C: .4byte gBgMapOffsets
_0800F820: .4byte 0x0002D038
_0800F824: .4byte 0x0002D03C
_0800F828: .4byte 0x0002D040
_0800F82C: .4byte gWhitePaintFlags
_0800F830: .4byte gPaletteManager
_0800F834: .4byte 0x00000404
_0800F838: .4byte 0x00000406
_0800F83C: .4byte gVideoRegBuffer+12

