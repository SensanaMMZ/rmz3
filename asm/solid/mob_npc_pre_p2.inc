	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080dac28
FUN_080dac28: @ 0x080DAC28
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0x10]
	cmp r0, #0x16
	bne _080DAC42
	ldr r0, _080DAC90 @ =gSystemSavedataManager
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	beq _080DAC58
_080DAC42:
	ldrb r0, [r6, #0x10]
	cmp r0, #0x19
	bne _080DAC98
	ldr r0, _080DAC90 @ =gSystemSavedataManager
	ldrb r1, [r0, #0xb]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080DAC98
_080DAC58:
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
	ldr r1, _080DAC94 @ =gSolidFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _080DAD00
	.align 2, 0
_080DAC90: .4byte gSystemSavedataManager
_080DAC94: .4byte gSolidFnTable
_080DAC98:
	ldr r2, _080DAD08 @ =sMotions
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r5, #0
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r0, #2
	adds r1, #2
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, #2
	strh r0, [r1]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080DAD0C @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r0, r6, #0
	adds r0, #0xb9
	movs r2, #1
	strb r2, [r0]
	adds r1, r6, #0
	adds r1, #0xb8
	movs r0, #0x30
	strb r0, [r1]
	adds r1, #4
	movs r0, #0xc0
	strh r0, [r1]
	strb r2, [r6, #0xd]
	adds r0, r6, #0
	bl MobNPC_Update
_080DAD00:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DAD08: .4byte sMotions
_080DAD0C: .4byte sCollisions
