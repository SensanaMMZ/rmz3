	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start phunterShotBuster
phunterShotBuster: @ 0x0806505C
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _08065076
	ldr r1, _0806508C @ =0x00001302
	bl SetMotion
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08065076:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #5
	beq _0806509A
	cmp r0, #5
	bgt _08065090
	cmp r0, #0
	beq _0806509A
	b _080650F4
	.align 2, 0
_0806508C: .4byte 0x00001302
_08065090:
	cmp r0, #0xa
	beq _0806509A
	cmp r0, #0x30
	beq _080650EC
	b _080650F4
_0806509A:
	ldr r0, [r4, #0x58]
	ldr r1, _080650C4 @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080650C8
	ldr r0, [r4, #0x54]
	movs r1, #0xd8
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [sp]
	movs r1, #0x90
	lsls r1, r1, #2
	mov r0, sp
	movs r2, #0x80
	bl CreateLemon
	b _080650DC
	.align 2, 0
_080650C4: .4byte 0xFFFFEE00
_080650C8:
	ldr r0, [r4, #0x54]
	ldr r1, _080650E8 @ =0xFFFFE500
	adds r0, r0, r1
	str r0, [sp]
	movs r1, #0x90
	lsls r1, r1, #2
	mov r0, sp
	movs r2, #0
	bl CreateLemon
_080650DC:
	cmp r0, #0
	beq _080650F4
	movs r0, #0x2c
	bl PlaySound
	b _080650F4
	.align 2, 0
_080650E8: .4byte 0xFFFFE500
_080650EC:
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080650F4:
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08065104
FUN_08065104: @ 0x08065104
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08065122
	movs r1, #0x98
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08065122:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, _08065184 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #6
	ble _0806518C
	movs r6, #0
	ldr r0, _08065188 @ =pZero2
	ldr r5, [r0]
	ldr r3, [r5, #0x54]
	ldr r2, [r4, #0x54]
	cmp r3, r2
	bgt _08065144
	movs r6, #1
_08065144:
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	cmp r6, r0
	beq _0806518C
	subs r0, r3, r2
	movs r1, #0xdc
	lsls r1, r1, #7
	adds r0, r0, r1
	movs r1, #0xdc
	lsls r1, r1, #8
	cmp r0, r1
	bhi _0806518C
	ldr r0, [r5, #0x58]
	ldr r1, [r4, #0x58]
	subs r0, r0, r1
	movs r1, #0xa0
	lsls r1, r1, #7
	adds r0, r0, r1
	movs r1, #0xa0
	lsls r1, r1, #8
	cmp r0, r1
	bhi _0806518C
	ldrb r0, [r4, #0xd]
	movs r1, #0
	strb r0, [r4, #0xf]
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _080651B8
	.align 2, 0
_08065184: .4byte gProjectileHeaderPtr
_08065188: .4byte pZero2
_0806518C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080651B8
	movs r0, #6
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
	movs r2, #0
	adds r1, r4, #0
	adds r1, #0xbd
	ldrb r0, [r1]
	cmp r0, #0
	bne _080651B0
	movs r2, #1
_080651B0:
	strb r2, [r1]
	adds r0, r4, #0
	bl FUN_08064e7c
_080651B8:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

