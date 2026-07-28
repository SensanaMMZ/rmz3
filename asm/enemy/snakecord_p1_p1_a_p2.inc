	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807415c
FUN_0807415c: @ 0x0807415C
	push {r4, r5, r6, r7, lr}
	adds r3, r0, #0
	ldrb r0, [r3, #0x10]
	cmp r0, #0
	bne _080741FE
	adds r0, r3, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #0x80
	lsls r2, r2, #2
	ands r1, r2
	mov ip, r0
	cmp r1, #0
	beq _080741FE
	movs r2, #0
	ldr r1, [r3, #0x28]
	ldr r4, _080741D8 @ =gEnemyFnTable
	cmp r1, #0
	beq _080741A4
	adds r7, r4, #0
	movs r6, #2
	movs r5, #1
_08074188:
	ldrb r0, [r1, #9]
	lsls r0, r0, #2
	adds r0, r0, r7
	str r6, [r1, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r1, #0x14]
	strb r5, [r1, #0xd]
	ldr r1, [r1, #0x28]
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r1, #0
	bne _08074188
_080741A4:
	ldrb r0, [r3, #0xd]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _080741B4
	cmp r2, #2
	bne _080741E0
_080741B4:
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r2, #2
	str r2, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	mov r0, ip
	ldr r1, [r0]
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _080741DC
	strb r2, [r3, #0xd]
	b _080741F4
	.align 2, 0
_080741D8: .4byte gEnemyFnTable
_080741DC:
	strb r1, [r3, #0xd]
	b _080741F4
_080741E0:
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r1, #2
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	movs r0, #0
	strb r0, [r3, #0xd]
_080741F4:
	adds r0, r3, #0
	bl Snakecord_Die
	movs r0, #1
	b _08074200
_080741FE:
	movs r0, #0
_08074200:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_08074208
FUN_08074208: @ 0x08074208
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #0xa
	beq _080742E2
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	bne _080742E2
	ldrb r5, [r4, #0xf]
	cmp r5, #0
	beq _08074228
	cmp r5, #1
	beq _080742B8
	b _080742E2
_08074228:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _080742E2
	ldrb r0, [r4, #0xd]
	cmp r0, #9
	bne _0807427C
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToUp2
	cmp r0, #0
	bge _08074250
	movs r0, #0xb
	b _08074252
_08074250:
	movs r0, #4
_08074252:
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
	ldr r2, [r4, #0x2c]
	cmp r2, #0
	beq _0807427C
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080742AC @ =gVFXFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x14]
_0807427C:
	ldr r1, _080742B0 @ =0x08366E30
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080742B4 @ =0x08366E60
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080742A8:
	movs r0, #1
	b _080742E4
	.align 2, 0
_080742AC: .4byte gVFXFnTable
_080742B0: .4byte 0x08366E30
_080742B4: .4byte 0x08366E60
_080742B8:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _080742E0
	ldrb r0, [r4, #0xd]
	cmp r0, #2
	bls _080742A8
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r1, [r0]
	ands r5, r1
	cmp r5, #0
	beq _080742A8
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	bne _080742E2
	b _080742A8
_080742E0:
	strb r0, [r4, #0xf]
_080742E2:
	movs r0, #0
_080742E4:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

