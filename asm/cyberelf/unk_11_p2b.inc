	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e5818
FUN_080e5818: @ 0x080E5818
	push {lr}
	adds r2, r0, #0
	adds r3, r2, #0
	adds r3, #0x8c
	ldr r0, [r3]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _080E5840
	movs r1, #0
	str r1, [r3]
	adds r0, r2, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
_080E5840:
	adds r0, r2, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080E5862
	ldr r1, _080E5868 @ =gElfFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	adds r0, r2, #0
	bl Elf11_Die
_080E5862:
	pop {r0}
	bx r0
	.align 2, 0
_080E5868: .4byte gElfFnTable

	thumb_func_start FUN_080e586c
FUN_080e586c: @ 0x080E586C
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r2, _080E5894 @ =0x7FF20000
	adds r0, r0, r2
	lsrs r0, r0, #0x10
	cmp r0, #1
	bhi _080E5888
	movs r1, #0
_080E5888:
	movs r0, #0xf
	ands r1, r0
	cmp r1, #0
	beq _080E5898
	movs r0, #1
	b _080E58B6
	.align 2, 0
_080E5894: .4byte 0x7FF20000
_080E5898:
	ldr r0, _080E58B0 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #5
	cmp r0, r1
	bhi _080E58B4
	movs r0, #0
	b _080E58B6
	.align 2, 0
_080E58B0: .4byte gStageRun+232
_080E58B4:
	movs r0, #2
_080E58B6:
	pop {r4}
	pop {r1}
	bx r1
