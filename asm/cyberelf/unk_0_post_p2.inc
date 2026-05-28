	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e1fe8
FUN_080e1fe8: @ 0x080E1FE8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r0, #0xbc
	ldr r5, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _080E2012
	adds r0, r5, #0
	adds r0, #0xb4
	ldrh r1, [r0, #4]
	adds r1, #3
	strh r1, [r0, #4]
	adds r0, r5, #0
	bl IsDoubleHP
	lsls r0, r0, #0x18
	movs r3, #4
	cmp r0, #0
	beq _080E2026
	movs r3, #8
	b _080E2026
_080E2012:
	adds r0, r5, #0
	adds r0, #0xb4
	ldrh r1, [r0, #4]
	adds r1, #5
	strh r1, [r0, #4]
	adds r0, r5, #0
	bl GetMaxHP
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
_080E2026:
	ldr r0, _080E2094 @ =gMission
	ldr r0, [r0]
	adds r1, r0, #0
	adds r1, #0x4c
	ldrb r0, [r1]
	cmp r0, #0x62
	bhi _080E2038
	adds r0, #1
	strb r0, [r1]
_080E2038:
	ldr r1, _080E2098 @ =gUnlockedElfPtr
	ldr r2, _080E209C @ =0x00000121
	adds r0, r5, r2
	ldrb r0, [r0]
	ldr r1, [r1]
	adds r1, r1, r0
	ldrb r0, [r1]
	movs r2, #2
	orrs r0, r2
	strb r0, [r1]
	adds r4, r5, #0
	adds r4, #0xa4
	ldrh r0, [r4]
	adds r0, r0, r3
	strh r0, [r4]
	adds r0, r5, #0
	bl GetMaxHP
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r2, #0
	ldrsh r1, [r4, r2]
	cmp r0, r1
	bge _080E2074
	adds r0, r5, #0
	bl GetMaxHP
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	strh r0, [r4]
_080E2074:
	ldr r1, _080E20A0 @ =gElfFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl Elf0_Die
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080E2094: .4byte gMission
_080E2098: .4byte gUnlockedElfPtr
_080E209C: .4byte 0x00000121
_080E20A0: .4byte gElfFnTable
