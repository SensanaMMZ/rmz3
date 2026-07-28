	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start extraNPC_080da7d8
extraNPC_080da7d8: @ 0x080DA7D8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0x10]
	subs r0, #0xc
	cmp r0, #8
	bls _080DA7E6
	b _080DA8C8
_080DA7E6:
	lsls r0, r0, #2
	ldr r1, _080DA7F0 @ =_080DA7F4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080DA7F0: .4byte _080DA7F4
_080DA7F4: @ jump table
	.4byte _080DA818 @ case 0
	.4byte _080DA824 @ case 1
	.4byte _080DA830 @ case 2
	.4byte _080DA83C @ case 3
	.4byte _080DA848 @ case 4
	.4byte _080DA854 @ case 5
	.4byte _080DA860 @ case 6
	.4byte _080DA86C @ case 7
	.4byte _080DA878 @ case 8
_080DA818:
	ldr r0, _080DA820 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x12]
	movs r0, #0x10
	b _080DA87E
	.align 2, 0
_080DA820: .4byte gSystemSavedataManager
_080DA824:
	ldr r0, _080DA82C @ =gSystemSavedataManager
	ldrb r1, [r0, #0xe]
	movs r0, #0x80
	b _080DA87E
	.align 2, 0
_080DA82C: .4byte gSystemSavedataManager
_080DA830:
	ldr r0, _080DA838 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x11]
	movs r0, #0x40
	b _080DA87E
	.align 2, 0
_080DA838: .4byte gSystemSavedataManager
_080DA83C:
	ldr r0, _080DA844 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x11]
	movs r0, #0x80
	b _080DA87E
	.align 2, 0
_080DA844: .4byte gSystemSavedataManager
_080DA848:
	ldr r0, _080DA850 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x12]
	movs r0, #4
	b _080DA87E
	.align 2, 0
_080DA850: .4byte gSystemSavedataManager
_080DA854:
	ldr r0, _080DA85C @ =gSystemSavedataManager
	ldrb r1, [r0, #0xe]
	movs r0, #0x10
	b _080DA87E
	.align 2, 0
_080DA85C: .4byte gSystemSavedataManager
_080DA860:
	ldr r0, _080DA868 @ =gSystemSavedataManager
	ldrb r1, [r0, #0xe]
	movs r0, #0x40
	b _080DA87E
	.align 2, 0
_080DA868: .4byte gSystemSavedataManager
_080DA86C:
	ldr r0, _080DA874 @ =gSystemSavedataManager
	ldrb r1, [r0, #0xd]
	movs r0, #0x40
	b _080DA87E
	.align 2, 0
_080DA874: .4byte gSystemSavedataManager
_080DA878:
	ldr r0, _080DA8C0 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x12]
	movs r0, #0x20
_080DA87E:
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080DA8C8
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080DA8C4 @ =gSolidFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _080DA92E
	.align 2, 0
_080DA8C0: .4byte gSystemSavedataManager
_080DA8C4: .4byte gSolidFnTable
_080DA8C8:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080DA934 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r2, _080DA938 @ =sMotions
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r3, #0
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r1, [r0]
	adds r0, r6, #0
	adds r0, #0xc0
	strh r1, [r0]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xc2
	strh r0, [r1]
	subs r1, #9
	movs r0, #1
	strb r0, [r1]
	adds r0, r6, #0
	adds r0, #0xb8
	strb r3, [r0]
	adds r0, #4
	strh r5, [r0]
	strb r3, [r6, #0xd]
	adds r0, r6, #0
	bl MobNPC_Update
_080DA92E:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DA934: .4byte sCollisions
_080DA938: .4byte sMotions

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

	thumb_func_start FUN_080dab40
FUN_080dab40: @ 0x080DAB40
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r0, _080DAB88 @ =gSystemSavedataManager
	ldrb r0, [r0, #0xa]
	movs r7, #1
	adds r2, r7, #0
	ands r2, r0
	cmp r2, #0
	bne _080DAB90
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080DAB8C @ =gSolidFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _080DABF4
	.align 2, 0
_080DAB88: .4byte gSystemSavedataManager
_080DAB8C: .4byte gSolidFnTable
_080DAB90:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080DABFC @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r2, _080DAC00 @ =sMotions
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r3, #0
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r1, [r0]
	adds r0, r6, #0
	adds r0, #0xc0
	strh r1, [r0]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xc2
	strh r0, [r1]
	adds r0, r6, #0
	adds r0, #0xb9
	strb r7, [r0]
	subs r0, #1
	strb r3, [r0]
	adds r0, #4
	strh r5, [r0]
	strb r3, [r6, #0xd]
	adds r0, r6, #0
	bl MobNPC_Update
_080DABF4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080DABFC: .4byte sCollisions
_080DAC00: .4byte sMotions
