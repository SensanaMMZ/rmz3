	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a5bb4
FUN_080a5bb4: @ 0x080A5BB4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	adds r6, r1, #0
	movs r4, #0
	movs r5, #0
	ldr r0, _080A5C08 @ =gProjectileFnTable
	mov r8, r0
_080A5BC6:
	ldr r0, _080A5C0C @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r1, r0, #0
	cmp r1, #0
	beq _080A5BF8
	adds r2, r1, #0
	adds r2, #0x25
	movs r0, #8
	strb r0, [r2]
	movs r0, #0x15
	strb r0, [r1, #9]
	mov r2, r8
	ldr r0, [r2, #0x54]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r5, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r5, [r0]
	strb r5, [r1, #0x10]
	strb r4, [r1, #0x12]
	str r7, [r1, #0x54]
	str r6, [r1, #0x58]
_080A5BF8:
	adds r4, #1
	cmp r4, #4
	ble _080A5BC6
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A5C08: .4byte gProjectileFnTable
_080A5C0C: .4byte gProjectileHeaderPtr
