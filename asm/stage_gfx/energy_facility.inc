	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080128bc
FUN_080128bc: @ 0x080128BC
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	bne _080128EA
	movs r2, #0
	movs r3, #0
_080128CC:
	lsls r1, r2, #0x10
	asrs r1, r1, #0x10
	lsls r0, r1, #2
	adds r0, r0, r6
	str r3, [r0, #0x68]
	adds r1, #1
	lsls r1, r1, #0x10
	lsrs r2, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #5
	ble _080128CC
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _0801291C
_080128EA:
	movs r2, #0
_080128EC:
	lsls r0, r2, #0x10
	asrs r5, r0, #0x10
	lsls r0, r5, #2
	adds r4, r0, r6
	ldr r0, [r4, #0x68]
	cmp r0, #0
	bne _08012910
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	str r0, [sp]
	movs r0, #0xc5
	lsls r0, r0, #0xd
	movs r1, #0xbc
	lsls r1, r1, #9
	movs r3, #0
	bl CreateStructuralSteel
	str r0, [r4, #0x68]
_08012910:
	adds r0, r5, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #5
	ble _080128EC
_0801291C:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0

