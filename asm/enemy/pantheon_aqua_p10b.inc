	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08073610
FUN_08073610: @ 0x08073610
	push {r4, lr}
	adds r3, r0, #0
	ldr r1, _0807363C @ =gOverworld
	ldr r2, _08073640 @ =0x0002C00C
	adds r1, r1, r2
	ldr r2, [r1]
	ldr r1, _08073644 @ =gStageRun+232
	ldr r1, [r1, #0x3c]
	ldr r4, _08073648 @ =0x00004FFF
	adds r1, r1, r4
	cmp r2, r1
	bge _08073650
	ldr r1, [r3, #0x58]
	ldr r4, _0807364C @ =0xFFFFDA00
	adds r1, r1, r4
	cmp r2, r1
	ble _0807365A
	movs r4, #0x98
	lsls r4, r4, #6
	adds r1, r2, r4
	b _08073658
	.align 2, 0
_0807363C: .4byte gOverworld
_08073640: .4byte 0x0002C00C
_08073644: .4byte gStageRun+232
_08073648: .4byte 0x00004FFF
_0807364C: .4byte 0xFFFFDA00
_08073650:
	ldr r1, [r3, #0x58]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
_08073658:
	str r1, [r3, #0x58]
_0807365A:
	pop {r4}
	pop {r1}
	bx r1

