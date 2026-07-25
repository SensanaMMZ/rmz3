	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start deathtanz_080a0934
deathtanz_080a0934: @ 0x080A0934
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	adds r6, r1, #0
	adds r7, r2, #0
	ldr r0, [sp, #0x18]
	lsls r3, r3, #0x18
	lsrs r4, r3, #0x18
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	ldr r0, _080A0998 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080A098C
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _080A099C @ =gProjectileFnTable
	movs r0, #0xe
	strb r0, [r3, #9]
	ldr r0, [r1, #0x38]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	str r6, [r3, #0x54]
	str r7, [r3, #0x58]
	strb r4, [r3, #0x12]
	mov r0, r8
	str r0, [r3, #0x28]
	adds r0, r3, #0
	adds r0, #0xbc
	strb r5, [r0]
_080A098C:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A0998: .4byte gProjectileHeaderPtr
_080A099C: .4byte gProjectileFnTable
