	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080cec74
FUN_080cec74: @ 0x080CEC74
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _080CEC80
	b _080CEDB2
_080CEC80:
	lsls r0, r0, #2
	ldr r1, _080CEC8C @ =_080CEC90
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080CEC8C: .4byte _080CEC90
_080CEC90: @ jump table
	.4byte _080CECA8 @ case 0
	.4byte _080CECE8 @ case 1
	.4byte _080CED00 @ case 2
	.4byte _080CED14 @ case 3
	.4byte _080CED44 @ case 4
	.4byte _080CED4E @ case 5
_080CECA8:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080CECDE
	adds r0, r4, #0
	adds r0, #0xbd
	ldrb r0, [r0]
	cmp r0, #0
	beq _080CECDE
	ldr r0, [r4, #0x28]
	adds r0, #0xc4
	ldr r1, [r4, #0x54]
	ldr r0, [r0]
	subs r0, r1, r0
	str r0, [r4, #0x64]
	cmp r0, #0
	bge _080CECCC
	rsbs r0, r0, #0
	str r0, [r4, #0x64]
_080CECCC:
	ldr r0, [r4, #0x64]
	lsls r0, r0, #3
	str r0, [r4, #0x64]
	movs r1, #0xc0
	lsls r1, r1, #6
	bl __divsi3
	adds r0, #1
	b _080CECE0
_080CECDE:
	movs r0, #1
_080CECE0:
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CECE8:
	ldr r0, [r4, #0x64]
	subs r0, #1
	str r0, [r4, #0x64]
	cmp r0, #0
	bne _080CECF8
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CECF8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080CEDB2
_080CED00:
	movs r0, #0x18
	strb r0, [r4, #0x13]
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CED14:
	ldr r0, [r4, #0x64]
	ldr r2, [r4, #0x68]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	ldrb r1, [r4, #0x13]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080CED2A
	rsbs r0, r2, #0
	str r0, [r4, #0x68]
_080CED2A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080CEDB2
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080CEDB2
_080CED44:
	movs r0, #0
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CED4E:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080CED5E
	str r1, [r4, #0x60]
_080CED5E:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0xb8
	lsls r2, r2, #5
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080CED92
	ldr r0, _080CEDB8 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _080CEDB2
_080CED92:
	adds r1, r4, #0
	adds r1, #0xbc
	movs r0, #1
	strb r0, [r1]
	ldr r1, _080CEDBC @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl GlacierleArm_Die
_080CEDB2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080CEDB8: .4byte gStageRun+232
_080CEDBC: .4byte gSolidFnTable
