	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08082a20
FUN_08082a20: @ 0x08082A20
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _08082A30
	cmp r0, #1
	beq _08082A68
	b _08082A78
_08082A30:
	adds r4, r6, #0
	adds r4, #0x24
	ldrb r5, [r4]
	adds r0, r6, #0
	bl InitRotatableMotion
	movs r1, #0xb2
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	strb r5, [r4]
	adds r0, r6, #0
	adds r0, #0xb5
	ldrb r0, [r0]
	cmp r0, #0
	bne _08082A58
	adds r0, r6, #0
	bl UpdateMotionGraphic
_08082A58:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08082A98 @ =0x08368158
	bl SetDDP
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08082A68:
	adds r0, r6, #0
	adds r0, #0xb5
	ldrb r0, [r0]
	cmp r0, #0
	beq _08082A78
	adds r0, r6, #0
	bl UpdateMotionGraphic
_08082A78:
	ldr r0, [r6, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08082A92
	ldr r1, _08082A9C @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_08082A92:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08082A98: .4byte 0x08368158
_08082A9C: .4byte gEnemyFnTable
