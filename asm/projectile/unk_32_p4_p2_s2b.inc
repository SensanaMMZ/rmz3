	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ab8cc
FUN_080ab8cc: @ 0x080AB8CC
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r5, r0, #0
	ldr r7, [r5, #0x28]
	bl UpdateMotionGraphic
	ldr r1, [r5, #0x5c]
	ldrb r0, [r5, #0x13]
	adds r0, r0, r1
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0x12]
	movs r1, #0x18
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AB948
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	adds r6, r1, #0
	cmp r0, #0
	beq _080AB902
	ldr r0, [r5, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	b _080AB906
_080AB902:
	ldr r0, [r5, #0x54]
	ldr r1, _080AB984 @ =0xFFFFF000
_080AB906:
	adds r0, r0, r1
	str r0, [sp]
	ldr r4, _080AB988 @ =0x0836C57C
	ldrb r0, [r5, #0x12]
	movs r1, #0x18
	bl __udivsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x16
	adds r1, r5, #0
	adds r1, #0xc2
	ldrb r2, [r1]
	lsls r1, r2, #2
	adds r1, r1, r2
	lsls r1, r1, #3
	adds r0, r0, r1
	adds r0, r0, r4
	ldr r1, [r0]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	beq _080AB948
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [sp, #4]
	lsls r1, r6, #0x18
	lsrs r1, r1, #0x1c
	movs r0, #1
	ands r1, r0
	mov r0, sp
	adds r2, r5, #0
	bl FUN_080aac7c
_080AB948:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _080AB962
	ldrb r0, [r7, #0xc]
	cmp r0, #1
	bhi _080AB962
	ldrb r0, [r7, #0xd]
	cmp r0, #0x13
	bne _080AB97A
_080AB962:
	ldr r1, _080AB98C @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl Projectile32_Die
_080AB97A:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AB984: .4byte 0xFFFFF000
_080AB988: .4byte 0x0836C57C
_080AB98C: .4byte gProjectileFnTable
