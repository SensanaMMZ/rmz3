	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Actor21_Update
Actor21_Update: @ 0x080D2EDC
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #6
	bls _080D2EE8
	b _080D2FEC
_080D2EE8:
	lsls r0, r0, #2
	ldr r1, _080D2EF4 @ =_080D2EF8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D2EF4: .4byte _080D2EF8
_080D2EF8: @ jump table
	.4byte _080D2F14 @ case 0
	.4byte _080D2F26 @ case 1
	.4byte _080D2F58 @ case 2
	.4byte _080D2F6A @ case 3
	.4byte _080D2F86 @ case 4
	.4byte _080D2FC0 @ case 5
	.4byte _080D2FEC @ case 6
_080D2F14:
	movs r1, #0
	str r1, [r6, #0x54]
	movs r0, #0x93
	lsls r0, r0, #8
	str r0, [r6, #0x58]
	strb r1, [r6, #0x13]
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D2F26:
	ldr r2, _080D2F54 @ =gSineTable
	ldrb r1, [r6, #0x13]
	lsls r0, r1, #0x19
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r2, [r0, r3]
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #4
	str r0, [r6, #0x54]
	adds r1, #1
	strb r1, [r6, #0x13]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	cmp r1, #0x1f
	bls _080D2FEC
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
	movs r0, #0x10
	strb r0, [r6, #0x13]
	b _080D2FEC
	.align 2, 0
_080D2F54: .4byte gSineTable
_080D2F58:
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D2FEC
	movs r0, #4
	strb r0, [r6, #0x13]
	b _080D2FE6
_080D2F6A:
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #2
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D2FEC
	movs r0, #8
	strb r0, [r6, #0x13]
	b _080D2FE6
_080D2F86:
	ldrb r1, [r6, #0x13]
	subs r1, #1
	strb r1, [r6, #0x13]
	ldr r2, _080D2FBC @ =gSineTable
	lsls r0, r1, #0x1b
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r2, [r0, r3]
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #4
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [r6, #0x54]
	lsls r1, r1, #0x18
	cmp r1, #0
	bne _080D2FEC
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
	movs r0, #0x97
	lsls r0, r0, #1
	bl PlaySound
	b _080D2FEC
	.align 2, 0
_080D2FBC: .4byte gSineTable
_080D2FC0:
	ldr r1, [r6, #0x54]
	lsls r0, r1, #1
	adds r0, r0, r1
	asrs r0, r0, #2
	str r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	lsls r0, r1, #1
	adds r0, r0, r1
	asrs r0, r0, #2
	str r0, [r6, #0x58]
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bgt _080D2FEC
	ldr r2, _080D302C @ =gWindowRegBuffer
	ldrh r1, [r2]
	ldr r0, _080D3030 @ =0x0000BFFF
	ands r0, r1
	strh r0, [r2]
_080D2FE6:
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D2FEC:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldr r5, _080D302C @ =gWindowRegBuffer
	ldr r2, [r6, #0x54]
	asrs r2, r2, #8
	movs r3, #1
	ands r3, r0
	lsls r0, r3, #3
	adds r2, r2, r0
	adds r1, r2, #0
	adds r1, #0xbc
	movs r4, #0xff
	ands r1, r4
	movs r0, #0xbc
	subs r0, r0, r2
	lsls r0, r0, #8
	orrs r1, r0
	strh r1, [r5, #6]
	ldr r0, [r6, #0x58]
	asrs r0, r0, #8
	lsls r3, r3, #2
	adds r0, r0, r3
	ands r0, r4
	strh r0, [r5, #0xa]
	ldr r1, _080D3034 @ =gPaletteManager
	ldr r3, _080D3038 @ =0x00007FFF
	adds r0, r3, #0
	strh r0, [r1]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080D302C: .4byte gWindowRegBuffer
_080D3030: .4byte 0x0000BFFF
_080D3034: .4byte gPaletteManager
_080D3038: .4byte 0x00007FFF
