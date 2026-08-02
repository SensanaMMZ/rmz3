	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start andrew_080d9d8c
andrew_080d9d8c: @ 0x080D9D8C
	push {lr}
	ldr r0, _080D9DB8 @ =gSystemSavedataManager
	ldrb r1, [r0, #0xc]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080D9E28
	ldr r2, _080D9DBC @ =gCurStory
	ldrb r1, [r2, #6]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080D9DCC
	ldrb r0, [r2, #0xf]
	cmp r0, #3
	bhi _080D9DC4
	movs r0, #4
	strb r0, [r2, #0xf]
	ldr r0, _080D9DC0 @ =0x000002D1
	b _080D9EAE
	.align 2, 0
_080D9DB8: .4byte gSystemSavedataManager
_080D9DBC: .4byte gCurStory
_080D9DC0: .4byte 0x000002D1
_080D9DC4:
	ldr r0, _080D9DC8 @ =0x000002D2
	b _080D9EAE
	.align 2, 0
_080D9DC8: .4byte 0x000002D2
_080D9DCC:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080D9DFC
	ldr r0, _080D9DF0 @ =gStageDiskManager
	ldr r0, [r0]
	ldrb r1, [r0, #0x1a]
	movs r0, #0xf
	ands r0, r1
	lsrs r0, r0, #2
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080D9DF4
	movs r0, #0xb4
	lsls r0, r0, #2
	b _080D9EAE
	.align 2, 0
_080D9DF0: .4byte gStageDiskManager
_080D9DF4:
	ldr r0, _080D9DF8 @ =0x000002CF
	b _080D9EAE
	.align 2, 0
_080D9DF8: .4byte 0x000002CF
_080D9DFC:
	ldrb r0, [r2, #0xf]
	cmp r0, #0
	bne _080D9E0A
	strb r3, [r2, #0xf]
	movs r0, #0xb3
	lsls r0, r0, #2
	b _080D9EAE
_080D9E0A:
	cmp r0, #1
	bne _080D9E1C
	movs r0, #2
	strb r0, [r2, #0xf]
	ldr r0, _080D9E18 @ =0x000002CD
	b _080D9EAE
	.align 2, 0
_080D9E18: .4byte 0x000002CD
_080D9E1C:
	movs r0, #3
	strb r0, [r2, #0xf]
	ldr r0, _080D9E24 @ =0x000002CE
	b _080D9EAE
	.align 2, 0
_080D9E24: .4byte 0x000002CE
_080D9E28:
	ldr r2, _080D9E44 @ =gCurStory
	ldrb r1, [r2, #6]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080D9E54
	ldrb r0, [r2, #0xf]
	cmp r0, #3
	bhi _080D9E4C
	movs r0, #4
	strb r0, [r2, #0xf]
	ldr r0, _080D9E48 @ =0x00000242
	b _080D9EAE
	.align 2, 0
_080D9E44: .4byte gCurStory
_080D9E48: .4byte 0x00000242
_080D9E4C:
	ldr r0, _080D9E50 @ =0x00000243
	b _080D9EAE
	.align 2, 0
_080D9E50: .4byte 0x00000243
_080D9E54:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080D9E88
	ldr r0, _080D9E78 @ =gStageDiskManager
	ldr r0, [r0]
	ldrb r1, [r0, #0x1a]
	movs r0, #0xf
	ands r0, r1
	lsrs r0, r0, #2
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080D9E80
	ldr r0, _080D9E7C @ =0x000002D3
	b _080D9EAE
	.align 2, 0
_080D9E78: .4byte gStageDiskManager
_080D9E7C: .4byte 0x000002D3
_080D9E80:
	ldr r0, _080D9E84 @ =0x00000241
	b _080D9EAE
	.align 2, 0
_080D9E84: .4byte 0x00000241
_080D9E88:
	ldrb r0, [r2, #0xf]
	cmp r0, #0
	bne _080D9E98
	strb r3, [r2, #0xf]
	ldr r0, _080D9E94 @ =0x0000023D
	b _080D9EAE
	.align 2, 0
_080D9E94: .4byte 0x0000023D
_080D9E98:
	cmp r0, #1
	beq _080D9EA8
	movs r0, #3
	strb r0, [r2, #0xf]
	ldr r0, _080D9EA4 @ =0x0000023F
	b _080D9EAE
	.align 2, 0
_080D9EA4: .4byte 0x0000023F
_080D9EA8:
	movs r0, #2
	strb r0, [r2, #0xf]
	ldr r0, _080D9EB4 @ =0x0000023E
_080D9EAE:
	pop {r1}
	bx r1
	.align 2, 0
_080D9EB4: .4byte 0x0000023E
