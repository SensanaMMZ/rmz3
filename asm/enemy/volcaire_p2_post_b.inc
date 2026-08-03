	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08077dd0
FUN_08077dd0: @ 0x08077DD0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08077DE0
	cmp r0, #1
	beq _08077E96
	b _08077F06
_08077DE0:
	ldrb r0, [r5, #0x10]
	cmp r0, #1
	bne _08077E00
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08077DFC @ =0x083673C0
	bl SetDDP
	movs r1, #0xb8
	lsls r1, r1, #6
	adds r0, r5, #0
	bl SetMotion
	b _08077E16
	.align 2, 0
_08077DFC: .4byte 0x083673C0
_08077E00:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08077E78 @ =0x083673D8
	bl SetDDP
	ldr r1, _08077E7C @ =0x00002E05
	adds r0, r5, #0
	movs r2, #4
	movs r3, #1
	bl GotoMotion
_08077E16:
	ldr r0, _08077E80 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _08077E84 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	cmp r6, #0
	beq _08077E88
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r5, #0x60]
	b _08077E90
	.align 2, 0
_08077E78: .4byte 0x083673D8
_08077E7C: .4byte 0x00002E05
_08077E80: .4byte pZero2
_08077E84: .4byte 0xFFFFE800
_08077E88:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_08077E90:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08077E96:
	adds r0, r5, #0
	adds r0, #0xb9
	ldrb r1, [r0]
	adds r4, r0, #0
	cmp r1, #0
	bne _08077EAA
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_08077EAA:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08077EBA
	str r1, [r5, #0x60]
_08077EBA:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _08077F00
	ldr r0, [r5, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r6, r0, #0
	cmp r6, #0
	bge _08077F00
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl GetMetatileAttr
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08077EFC
	ldrb r0, [r4]
	cmp r0, #0
	bne _08077EFC
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl MaybeKillVolcaire
	b _08077F06
_08077EFC:
	movs r0, #1
	strb r0, [r4]
_08077F00:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08077F06:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

