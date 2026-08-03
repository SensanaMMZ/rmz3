	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start anubis_080510f0
anubis_080510f0: @ 0x080510F0
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _080510FE
	b _08051286
_080510FE:
	lsls r0, r0, #2
	ldr r1, _08051108 @ =_0805110C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08051108: .4byte _0805110C
_0805110C: @ jump table
	.4byte _08051120 @ case 0
	.4byte _080511F4 @ case 1
	.4byte _0805125E @ case 2
	.4byte _0805126E @ case 3
	.4byte _08051286 @ case 4
_08051120:
	movs r0, #0x2f
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xcc
	ldrb r6, [r0]
	ldr r0, _08051214 @ =gBossHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08051188
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _08051218 @ =gBossFnTable
	movs r0, #0xb
	strb r0, [r3, #9]
	ldr r0, [r1, #0x2c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r3, #0x5c]
	str r4, [r3, #0x28]
	movs r1, #1
	strb r1, [r3, #0x10]
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	ands r0, r1
	eors r0, r6
	strb r0, [r3, #0x13]
_08051188:
	ldr r1, _0805121C @ =0x0000AF06
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r3, _08051220 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _080511CA
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _080511CA
	ldr r0, _08051224 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_080511CA:
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	str r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r0, #0x32
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080511F4:
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x5c]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xcc
	ldrb r3, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08051228
	cmp r3, #1
	bne _0805122C
	b _08051230
	.align 2, 0
_08051214: .4byte gBossHeaderPtr
_08051218: .4byte gBossFnTable
_0805121C: .4byte 0x0000AF06
_08051220: .4byte gStageRun
_08051224: .4byte 0x0000FFFE
_08051228:
	cmp r3, #0
	beq _08051230
_0805122C:
	movs r0, #0xfa
	b _08051232
_08051230:
	movs r0, #0xf6
_08051232:
	muls r0, r2, r0
	cmp r0, #0
	bge _0805123A
	adds r0, #0xff
_0805123A:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _08051256
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051256:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08051286
_0805125E:
	ldr r1, _08051290 @ =0x083635E4
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805126E:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08051286
	ldr r2, _08051294 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08051286:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08051290: .4byte 0x083635E4
_08051294: .4byte gStageRun
