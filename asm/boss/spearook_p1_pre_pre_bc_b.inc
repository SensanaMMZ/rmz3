	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08061e24
FUN_08061e24: @ 0x08061E24
	push {r4, lr}
	adds r2, r0, #0
	ldrb r4, [r2, #0x10]
	cmp r4, #1
	beq _08061E84
	cmp r4, #1
	bgt _08061E38
	cmp r4, #0
	beq _08061E3E
	b _08061EE8
_08061E38:
	cmp r4, #2
	beq _08061EBC
	b _08061EE8
_08061E3E:
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _08061E5A
	adds r0, r2, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _08061EE8
_08061E5A:
	ldr r0, _08061E7C @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	bne _08061EE8
	ldr r1, _08061E80 @ =gBossFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	strb r4, [r2, #0xd]
	b _08061ED8
	.align 2, 0
_08061E7C: .4byte gStageRun
_08061E80: .4byte gBossFnTable
_08061E84:
	ldr r3, [r2, #0x28]
	ldrb r0, [r3, #0xc]
	cmp r0, #1
	bls _08061EE8
	ldr r1, _08061EB4 @ =gBossFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #2
	str r4, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	adds r0, r3, #0
	adds r0, #0xbc
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08061EB8
	movs r0, #4
	b _08061ED6
	.align 2, 0
_08061EB4: .4byte gBossFnTable
_08061EB8:
	strb r4, [r2, #0xd]
	b _08061ED8
_08061EBC:
	ldr r3, [r2, #0x28]
	ldrb r0, [r3, #0xc]
	cmp r0, #1
	bls _08061EE8
	ldr r1, _08061EE4 @ =gBossFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r4, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	movs r0, #3
_08061ED6:
	strb r0, [r2, #0xd]
_08061ED8:
	adds r0, r2, #0
	bl Spearook_Die
	movs r0, #1
	b _08061EEA
	.align 2, 0
_08061EE4: .4byte gBossFnTable
_08061EE8:
	movs r0, #0
_08061EEA:
	pop {r4}
	pop {r1}
	bx r1
