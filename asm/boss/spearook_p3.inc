	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08063174
FUN_08063174: @ 0x08063174
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _08063182
	b _0806328C
_08063182:
	lsls r0, r0, #2
	ldr r1, _0806318C @ =_08063190
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0806318C: .4byte _08063190
_08063190: @ jump table
	.4byte _080631A4 @ case 0
	.4byte _080631E8 @ case 1
	.4byte _0806320C @ case 2
	.4byte _08063216 @ case 3
	.4byte _0806328C @ case 4
_080631A4:
	ldr r3, _08063204 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _080631C6
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _080631C6
	ldr r0, _08063208 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_080631C6:
	movs r1, #0
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080631E8:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0806328C
	adds r2, r4, #0
	adds r2, #0xbc
	ldr r0, [r2]
	movs r1, #0x80
	orrs r0, r1
	str r0, [r2]
	b _08063286
	.align 2, 0
_08063204: .4byte gStageRun
_08063208: .4byte 0x0000FFFE
_0806320C:
	movs r0, #0x28
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08063216:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0806328C
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #0x10
	bl TryDropItem
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08063294 @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08063298 @ =gBossFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	ldr r2, _0806329C @ =gStageRun
	ldrb r0, [r2, #0x12]
	movs r1, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
_08063286:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806328C:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08063294: .4byte 0xFFFFF400
_08063298: .4byte gBossFnTable
_0806329C: .4byte gStageRun
