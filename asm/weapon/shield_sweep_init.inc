	.include "asm/macros.inc"

	.syntax unified
	
	.text

	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r1, [r4, #0xa]
	movs r0, #2
	adds r2, r0, #0
	orrs r2, r1
	movs r0, #1
	movs r3, #0
	orrs r2, r0
	strb r2, [r4, #0xa]
	ldrb r0, [r6, #0xa]
	lsrs r1, r0, #4
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	beq _0803C270
	movs r0, #0x10
	orrs r2, r0
	b _0803C274
_0803C270:
	movs r0, #0xef
	ands r2, r0
_0803C274:
	strb r2, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0803C2A0
	ldr r0, _0803C29C @ =0xFFFFFA00
	b _0803C2A4
	.align 2, 0
_0803C29C: .4byte 0xFFFFFA00
_0803C2A0:
	movs r0, #0xc0
	lsls r0, r0, #3
_0803C2A4:
	str r0, [r4, #0x64]
	ldrb r5, [r4, #0x10]
	cmp r5, #0
	bne _0803C2BA
	movs r1, #0x8d
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0x12]
	b _0803C2CA
_0803C2BA:
	ldr r1, _0803C2F0 @ =0x00008D01
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
_0803C2CA:
	ldr r1, _0803C2F4 @ =incrementShieldHitCount_0803c40c
	adds r0, r4, #0
	adds r0, #0x74
	str r1, [r0, #0x24]
	ldr r1, _0803C2F8 @ =gWeaponFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl ShieldSweep_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0803C2F0: .4byte 0x00008D01
_0803C2F4: .4byte incrementShieldHitCount_0803c40c
_0803C2F8: .4byte gWeaponFnTable
