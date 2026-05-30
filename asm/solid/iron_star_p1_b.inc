	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start killIronStar
killIronStar: @ 0x080CBCA0
	ldrb r2, [r0, #0xb]
	movs r1, #0xf7
	ands r1, r2
	strb r1, [r0, #0xb]
	ldr r2, _080CBCBC @ =gSolidFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r2, #4
	str r2, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #0x10]
	str r1, [r0, #0x14]
	bx lr
	.align 2, 0
_080CBCBC: .4byte gSolidFnTable
