	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start GlacierleAtkArm_Init
GlacierleAtkArm_Init: @ 0x080828E0
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r1, _08082940 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	ldr r1, _08082944 @ =0x08368170
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0xd]
	ldrb r1, [r5, #0xa]
	movs r0, #2
	orrs r1, r0
	movs r0, #1
	movs r2, #0
	orrs r1, r0
	strb r1, [r5, #0xa]
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _08082932
	movs r0, #4
	orrs r1, r0
	strb r1, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _08082948 @ =0x08368140
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	ldr r0, _0808294C @ =nop_080828dc
	str r0, [r4, #0x24]
_08082932:
	adds r0, r5, #0
	bl GlacierleAtkArm_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08082940: .4byte gEnemyFnTable
_08082944: .4byte 0x08368170
_08082948: .4byte 0x08368140
_0808294C: .4byte nop_080828dc
