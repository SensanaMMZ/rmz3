	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start ShieldSweep_Update
ShieldSweep_Update: @ 0x0803C2FC
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	ldrb r2, [r4, #0x10]
	cmp r2, #0
	bne _0803C3BE
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bhi _0803C318
	ldrb r0, [r5, #0xd]
	cmp r0, #3
	beq _0803C354
_0803C318:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0803C350 @ =gWeaponFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _0803C3E0
	.align 2, 0
_0803C350: .4byte gWeaponFnTable
_0803C354:
	ldr r0, [r5, #0x60]
	cmp r0, #0
	bne _0803C3B4
	ldrb r0, [r4, #0xa]
	movs r6, #1
	adds r2, r6, #0
	orrs r2, r0
	strb r2, [r4, #0xa]
	ldr r0, [r5, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	movs r1, #0xd0
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r1, [r4, #0x12]
	adds r3, r1, #1
	strb r3, [r4, #0x12]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	beq _0803C3E0
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x19
	ands r0, r6
	cmp r0, #0
	beq _0803C3A2
	adds r0, r4, #0
	adds r0, #0x54
	lsrs r1, r2, #4
	adds r2, r5, #0
	bics r2, r1
	movs r1, #4
	bl CreateParticle
	b _0803C3E0
_0803C3A2:
	adds r0, r4, #0
	adds r0, #0x54
	lsrs r1, r2, #4
	adds r2, r5, #0
	bics r2, r1
	movs r1, #5
	bl CreateParticle
	b _0803C3E0
_0803C3B4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	b _0803C3E0
_0803C3BE:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0803C3E0
	ldr r1, _0803C3E8 @ =gWeaponFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl ShieldSweep_Die
_0803C3E0:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0803C3E8: .4byte gWeaponFnTable
