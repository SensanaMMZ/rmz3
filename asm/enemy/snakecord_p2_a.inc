	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start snakecord_08074754
snakecord_08074754: @ 0x08074754
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	ldrb r7, [r6, #0xe]
	cmp r7, #0
	beq _08074768
	cmp r7, #1
	beq _08074806
	b _08074836
_08074768:
	ldr r0, [r6, #0x28]
	mov ip, r0
	cmp r0, #0
	beq _080747E0
	ldrb r2, [r0, #0xa]
	movs r1, #0xfe
	adds r0, r1, #0
	ands r0, r2
	movs r4, #0xfd
	ands r0, r4
	mov r2, ip
	strb r0, [r2, #0xa]
	mov r0, ip
	adds r0, #0x8c
	str r7, [r0]
	adds r0, #4
	str r7, [r0]
	adds r0, #4
	strb r7, [r0]
	ldrb r2, [r2, #0xa]
	movs r3, #0xfb
	adds r0, r3, #0
	ands r0, r2
	mov r5, ip
	strb r0, [r5, #0xa]
	ldr r0, _08074840 @ =gEnemyFnTable
	mov r8, r0
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	add r0, r8
	movs r2, #3
	str r2, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	ldr r5, [r5, #0x28]
	mov ip, r5
	ldrb r0, [r5, #0xa]
	ands r1, r0
	ands r1, r4
	strb r1, [r5, #0xa]
	mov r0, ip
	adds r0, #0x8c
	str r7, [r0]
	adds r0, #4
	str r7, [r0]
	adds r0, #4
	strb r7, [r0]
	mov r1, ip
	ldrb r0, [r1, #0xa]
	ands r3, r0
	strb r3, [r1, #0xa]
	ldrb r0, [r1, #9]
	lsls r0, r0, #2
	add r0, r8
	str r2, [r1, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r1, #0x14]
	str r7, [r6, #0x28]
_080747E0:
	str r7, [r6, #0x60]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldr r1, _08074844 @ =0x0000280C
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _08074848 @ =0x08366F14
	bl SetDDP
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08074806:
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	bne _08074836
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl GetGroundMetatileAttr
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08074836
	ldr r0, [r6, #0x60]
	adds r0, #0x40
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0807482E
	str r1, [r6, #0x60]
_0807482E:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
_08074836:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08074840: .4byte gEnemyFnTable
_08074844: .4byte 0x0000280C
_08074848: .4byte 0x08366F14
