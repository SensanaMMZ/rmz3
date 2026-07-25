	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809664c
FUN_0809664c: @ 0x0809664C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0809665C
	cmp r5, #1
	beq _080966BC
	b _080966E2
_0809665C:
	ldr r0, _080966E8 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r2, r0, #0
	cmp r2, #0
	beq _0809669E
	adds r1, r2, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080966EC @ =gEnemyFnTable
	movs r1, #0x41
	strb r1, [r2, #9]
	adds r1, #0xc3
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	movs r0, #0
	strh r5, [r2, #0x20]
	adds r1, r2, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r2, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r2, #0xb]
	ldrb r0, [r2, #0x1c]
	strb r0, [r2, #0x1d]
	movs r0, #4
	strb r0, [r2, #0x10]
	str r4, [r2, #0x28]
_0809669E:
	str r2, [r4, #0x2c]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080966F0 @ =0x0836A14C
	bl SetDDP
	ldr r1, _080966F4 @ =0x0000DB0E
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080966BC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bne _080966D0
	ldr r0, _080966F8 @ =0x00000107
	bl PlaySound
_080966D0:
	ldrb r1, [r4, #0x12]
	cmp r1, #0
	bne _080966DC
	movs r0, #8
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080966DC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080966E2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080966E8: .4byte gEnemyHeaderPtr
_080966EC: .4byte gEnemyFnTable
_080966F0: .4byte 0x0836A14C
_080966F4: .4byte 0x0000DB0E
_080966F8: .4byte 0x00000107

	thumb_func_start FUN_080966fc
FUN_080966fc: @ 0x080966FC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809670C
	cmp r0, #1
	beq _0809671A
	b _0809677A
_0809670C:
	ldr r1, _08096780 @ =0x0000DB10
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809671A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r5, [r0]
	cmp r5, #3
	bne _0809677A
	adds r0, #1
	ldr r1, _08096784 @ =0x0836A08C
	bl SetDDP
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _0809676E
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
	ldr r1, _08096788 @ =gEnemyFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r5, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
	str r2, [r4, #0x2c]
_0809676E:
	movs r0, #0
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	movs r0, #0x60
	strb r0, [r4, #0x12]
_0809677A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08096780: .4byte 0x0000DB10
_08096784: .4byte 0x0836A08C
_08096788: .4byte gEnemyFnTable

	thumb_func_start FUN_0809678c
FUN_0809678c: @ 0x0809678C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809679C
	cmp r0, #1
	beq _080967C8
	b _08096804
_0809679C:
	ldr r1, _0809680C @ =0x0000DB01
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x5c]
	str r0, [r4, #0x64]
	movs r0, #0x80
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	adds r1, r0, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _080967BC
	ldr r1, _08096810 @ =0xFFFFFF00
_080967BC:
	str r1, [r4, #0x5c]
	movs r0, #2
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080967C8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl FUN_08095e28
	ldrb r0, [r4, #0x12]
	cmp r0, #1
	bls _080967E0
	subs r0, #1
	strb r0, [r4, #0x12]
_080967E0:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080967FE
	ldr r0, [r4, #0x64]
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _080967F8
	movs r0, #6
_080967F8:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_080967FE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08096804:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0809680C: .4byte 0x0000DB01
_08096810: .4byte 0xFFFFFF00

	thumb_func_start FUN_08096814
FUN_08096814: @ 0x08096814
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r1, [r5, #0xe]
	cmp r1, #1
	beq _08096866
	cmp r1, #1
	bgt _0809682A
	cmp r1, #0
	beq _08096830
	b _08096936
_0809682A:
	cmp r1, #2
	beq _0809688A
	b _08096936
_08096830:
	movs r0, #0x3c
	strb r0, [r5, #0x12]
	movs r0, #6
	strb r0, [r5, #0x13]
	adds r0, r5, #0
	adds r0, #0xbd
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r2, #0x10
	adds r0, r2, #0
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r1, #1
	cmp r0, #0
	beq _08096852
	subs r1, #2
_08096852:
	str r1, [r5, #0x5c]
	str r2, [r5, #0x64]
	movs r1, #0x10
	cmp r0, #0
	beq _0809685E
	subs r1, #0x20
_0809685E:
	str r1, [r5, #0x64]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08096866:
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	bge _0809687C
	ldr r1, _08096878 @ =0x0000DB0F
	adds r0, r5, #0
	bl SetMotion
	b _08096884
	.align 2, 0
_08096878: .4byte 0x0000DB0F
_0809687C:
	ldr r1, _08096898 @ =0x0000DB05
	adds r0, r5, #0
	bl SetMotion
_08096884:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0809688A:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _0809689C
	subs r0, #1
	strb r0, [r5, #0x12]
	b _080968FE
	.align 2, 0
_08096898: .4byte 0x0000DB05
_0809689C:
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080968FE
	movs r0, #6
	strb r0, [r5, #0x13]
	adds r1, r5, #0
	adds r1, #0xbd
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _080968C6
	strb r2, [r1]
	movs r0, #0x3c
	strb r0, [r5, #0x12]
_080968C6:
	ldrb r4, [r5, #0xa]
	lsrs r4, r4, #4
	movs r0, #1
	ands r4, r0
	ldr r1, [r5, #0x54]
	ldr r0, _08096940 @ =0xFFFFF400
	adds r1, r1, r0
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r0, r0, #0xb
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08096944 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0x2c
	bl PlaySound
	ldr r1, _08096948 @ =0xFFFFFD00
	lsls r4, r4, #7
	subs r4, #0x80
	lsls r4, r4, #0x18
	lsrs r4, r4, #0x18
	mov r0, sp
	adds r2, r4, #0
	bl CreateLemon
_080968FE:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r2, r1, #0
	cmp r1, #0
	bge _0809690E
	rsbs r2, r1, #0
_0809690E:
	ldr r0, _0809694C @ =0x0000013F
	cmp r2, r0
	bgt _0809691A
	ldr r0, [r5, #0x64]
	adds r0, r1, r0
	str r0, [r5, #0x5c]
_0809691A:
	adds r0, r5, #0
	bl FUN_08095e28
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08096930
	ldr r0, [r5, #0x5c]
	rsbs r0, r0, #0
	str r0, [r5, #0x5c]
	movs r0, #1
	strb r0, [r5, #0xe]
_08096930:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08096936:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08096940: .4byte 0xFFFFF400
_08096944: .4byte 0xFFFFF600
_08096948: .4byte 0xFFFFFD00
_0809694C: .4byte 0x0000013F
