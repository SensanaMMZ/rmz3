	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start faucon_080da93c
faucon_080da93c: @ 0x080DA93C
	push {lr}
	ldrb r0, [r0, #0x10]
	subs r0, #0xa
	cmp r0, #0xa
	bls _080DA948
	b _080DAB34
_080DA948:
	lsls r0, r0, #2
	ldr r1, _080DA954 @ =_080DA958
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080DA954: .4byte _080DA958
_080DA958: @ jump table
	.4byte _080DA984 @ case 0
	.4byte _080DA9AE @ case 1
	.4byte _080DAA04 @ case 2
	.4byte _080DAA24 @ case 3
	.4byte _080DAA44 @ case 4
	.4byte _080DAA64 @ case 5
	.4byte _080DAA84 @ case 6
	.4byte _080DAAA4 @ case 7
	.4byte _080DAAC8 @ case 8
	.4byte _080DAAEC @ case 9
	.4byte _080DAB10 @ case 10
_080DA984:
	ldr r2, _080DA994 @ =gCurStory
	ldrb r1, [r2, #6]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080DA99C
	ldr r0, _080DA998 @ =0x000002A2
	b _080DAB36
	.align 2, 0
_080DA994: .4byte gCurStory
_080DA998: .4byte 0x000002A2
_080DA99C:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	bne _080DA9A8
	b _080DAB34
_080DA9A8:
	movs r0, #0xa8
	lsls r0, r0, #2
	b _080DAB36
_080DA9AE:
	ldr r2, _080DA9C0 @ =gCurStory
	ldrb r1, [r2, #6]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080DA9C8
	ldr r0, _080DA9C4 @ =0x000002AB
	b _080DAB36
	.align 2, 0
_080DA9C0: .4byte gCurStory
_080DA9C4: .4byte 0x000002AB
_080DA9C8:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DA9DC
	ldr r0, _080DA9D8 @ =0x000002A9
	b _080DAB36
	.align 2, 0
_080DA9D8: .4byte 0x000002A9
_080DA9DC:
	ldr r0, _080DA9F4 @ =gStageDiskManager
	ldr r0, [r0]
	ldrb r1, [r0, #0xe]
	movs r0, #0xf
	ands r0, r1
	lsrs r0, r0, #1
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080DA9FC
	ldr r0, _080DA9F8 @ =0x000002A7
	b _080DAB36
	.align 2, 0
_080DA9F4: .4byte gStageDiskManager
_080DA9F8: .4byte 0x000002A7
_080DA9FC:
	ldr r0, _080DAA00 @ =0x000002A6
	b _080DAB36
	.align 2, 0
_080DAA00: .4byte 0x000002A6
_080DAA04:
	ldr r1, _080DAA18 @ =gCurStory
	ldrb r0, [r1, #0x1b]
	cmp r0, #0
	bne _080DAA1C
	adds r0, #1
	strb r0, [r1, #0x1b]
	movs r0, #0xb2
	lsls r0, r0, #2
	b _080DAB36
	.align 2, 0
_080DAA18: .4byte gCurStory
_080DAA1C:
	ldr r0, _080DAA20 @ =0x000002C9
	b _080DAB36
	.align 2, 0
_080DAA20: .4byte 0x000002C9
_080DAA24:
	ldr r1, _080DAA38 @ =gCurStory
	ldrb r0, [r1, #0x1c]
	cmp r0, #0
	bne _080DAA3C
	adds r0, #1
	strb r0, [r1, #0x1c]
	movs r0, #0xb0
	lsls r0, r0, #2
	b _080DAB36
	.align 2, 0
_080DAA38: .4byte gCurStory
_080DAA3C:
	ldr r0, _080DAA40 @ =0x000002C1
	b _080DAB36
	.align 2, 0
_080DAA40: .4byte 0x000002C1
_080DAA44:
	ldr r1, _080DAA54 @ =gCurStory
	ldrb r0, [r1, #0x1d]
	cmp r0, #0
	bne _080DAA5C
	adds r0, #1
	strb r0, [r1, #0x1d]
	ldr r0, _080DAA58 @ =0x000002C2
	b _080DAB36
	.align 2, 0
_080DAA54: .4byte gCurStory
_080DAA58: .4byte 0x000002C2
_080DAA5C:
	ldr r0, _080DAA60 @ =0x000002C3
	b _080DAB36
	.align 2, 0
_080DAA60: .4byte 0x000002C3
_080DAA64:
	ldr r1, _080DAA78 @ =gCurStory
	ldrb r0, [r1, #0x1e]
	cmp r0, #0
	bne _080DAA7C
	adds r0, #1
	strb r0, [r1, #0x1e]
	movs r0, #0xb1
	lsls r0, r0, #2
	b _080DAB36
	.align 2, 0
_080DAA78: .4byte gCurStory
_080DAA7C:
	ldr r0, _080DAA80 @ =0x000002C5
	b _080DAB36
	.align 2, 0
_080DAA80: .4byte 0x000002C5
_080DAA84:
	ldr r1, _080DAA94 @ =gCurStory
	ldrb r0, [r1, #0x1f]
	cmp r0, #0
	bne _080DAA9C
	adds r0, #1
	strb r0, [r1, #0x1f]
	ldr r0, _080DAA98 @ =0x000002C6
	b _080DAB36
	.align 2, 0
_080DAA94: .4byte gCurStory
_080DAA98: .4byte 0x000002C6
_080DAA9C:
	ldr r0, _080DAAA0 @ =0x000002C7
	b _080DAB36
	.align 2, 0
_080DAAA0: .4byte 0x000002C7
_080DAAA4:
	ldr r0, _080DAABC @ =gCurStory
	adds r1, r0, #0
	adds r1, #0x20
	ldrb r0, [r1]
	cmp r0, #0
	bne _080DAAC0
	adds r0, #1
	strb r0, [r1]
	movs r0, #0xaf
	lsls r0, r0, #2
	b _080DAB36
	.align 2, 0
_080DAABC: .4byte gCurStory
_080DAAC0:
	ldr r0, _080DAAC4 @ =0x000002BD
	b _080DAB36
	.align 2, 0
_080DAAC4: .4byte 0x000002BD
_080DAAC8:
	ldr r0, _080DAADC @ =gCurStory
	adds r1, r0, #0
	adds r1, #0x21
	ldrb r0, [r1]
	cmp r0, #0
	bne _080DAAE4
	adds r0, #1
	strb r0, [r1]
	ldr r0, _080DAAE0 @ =0x000002BE
	b _080DAB36
	.align 2, 0
_080DAADC: .4byte gCurStory
_080DAAE0: .4byte 0x000002BE
_080DAAE4:
	ldr r0, _080DAAE8 @ =0x000002BF
	b _080DAB36
	.align 2, 0
_080DAAE8: .4byte 0x000002BF
_080DAAEC:
	ldr r0, _080DAB00 @ =gCurStory
	adds r1, r0, #0
	adds r1, #0x22
	ldrb r0, [r1]
	cmp r0, #0
	bne _080DAB08
	adds r0, #1
	strb r0, [r1]
	ldr r0, _080DAB04 @ =0x000002BA
	b _080DAB36
	.align 2, 0
_080DAB00: .4byte gCurStory
_080DAB04: .4byte 0x000002BA
_080DAB08:
	ldr r0, _080DAB0C @ =0x000002BB
	b _080DAB36
	.align 2, 0
_080DAB0C: .4byte 0x000002BB
_080DAB10:
	ldr r0, _080DAB24 @ =gCurStory
	adds r1, r0, #0
	adds r1, #0x23
	ldrb r0, [r1]
	cmp r0, #0
	bne _080DAB2C
	adds r0, #1
	strb r0, [r1]
	ldr r0, _080DAB28 @ =0x000002CA
	b _080DAB36
	.align 2, 0
_080DAB24: .4byte gCurStory
_080DAB28: .4byte 0x000002CA
_080DAB2C:
	ldr r0, _080DAB30 @ =0x000002CB
	b _080DAB36
	.align 2, 0
_080DAB30: .4byte 0x000002CB
_080DAB34:
	ldr r0, _080DAB3C @ =0x0000029E
_080DAB36:
	pop {r1}
	bx r1
	.align 2, 0
_080DAB3C: .4byte 0x0000029E
