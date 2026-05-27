	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08039960
FUN_08039960: @ 0x08039960
	push {r4, r5, r6, r7, lr}
	adds r1, r0, #0
	ldr r4, [r1, #0x2c]
	ldr r0, [r1, #0xc]
	ldr r6, [r0, #0x2c]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r7, [r0]
	ldr r0, [r1, #0x14]
	movs r5, #4
	ands r0, r5
	cmp r0, #0
	beq _080399E6
	ldr r3, _080399EC @ =gMission
	ldrh r2, [r3, #0x20]
	ldr r0, _080399F0 @ =0x0000FFFE
	cmp r2, r0
	bhi _08039988
	adds r0, r2, #1
	strh r0, [r3, #0x20]
_08039988:
	ldr r0, [r1, #0x14]
	ands r0, r5
	cmp r0, #0
	beq _080399E6
	ldrb r0, [r4, #0x10]
	subs r0, #0xb
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #9
	bhi _080399B2
	ldr r4, [r1, #0x2c]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r2, _080399F4 @ =0x08360460
	ldrb r1, [r4, #0x10]
	subs r1, #0xb
	adds r1, r1, r2
	ldrb r1, [r1]
	bl CreateWeapon13
_080399B2:
	ldrb r0, [r4, #0x10]
	cmp r0, #0xd
	bne _080399CC
	ldr r1, [r4, #0x58]
	ldr r0, [r6, #0x58]
	cmp r1, r0
	bge _080399CC
	movs r0, #0x13
	strb r0, [r4, #0x10]
	ldr r0, _080399F8 @ =0x00000135
	adds r1, r7, r0
	movs r0, #1
	strb r0, [r1]
_080399CC:
	ldrb r0, [r4, #0x10]
	cmp r0, #0x10
	bne _080399E6
	ldr r1, [r4, #0x58]
	ldr r0, [r6, #0x58]
	cmp r1, r0
	bge _080399E6
	movs r0, #0x14
	strb r0, [r4, #0x10]
	ldr r0, _080399F8 @ =0x00000135
	adds r1, r7, r0
	movs r0, #1
	strb r0, [r1]
_080399E6:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080399EC: .4byte gMission
_080399F0: .4byte 0x0000FFFE
_080399F4: .4byte 0x08360460
_080399F8: .4byte 0x00000135

	thumb_func_start FUN_080399fc
FUN_080399fc: @ 0x080399FC
	push {lr}
	adds r3, r0, #0
	ldrb r0, [r3, #9]
	cmp r0, #4
	bne _08039A3C
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _08039A40 @ =gWeaponFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
_08039A3C:
	pop {r0}
	bx r0
	.align 2, 0
_08039A40: .4byte gWeaponFnTable

