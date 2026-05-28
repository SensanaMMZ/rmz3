	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreateVFX57
CreateVFX57: @ 0x080C18EC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	ldr r0, [sp, #0x18]
	lsls r1, r1, #0x18
	lsrs r7, r1, #0x18
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	lsls r3, r3, #0x10
	lsrs r4, r3, #0x10
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	ldr r0, _080C195C @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C1950
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C1960 @ =gVFXFnTable
	movs r1, #0x39
	strb r1, [r3, #9]
	adds r0, #0xe4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r7, [r3, #0x10]
	strb r5, [r3, #0x11]
	lsls r0, r4, #0x10
	asrs r0, r0, #0x10
	str r0, [r3, #0x5c]
	lsls r0, r6, #0x10
	asrs r0, r0, #0x10
	str r0, [r3, #0x60]
	mov r2, r8
	ldr r0, [r2]
	ldr r1, [r2, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
_080C1950:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C195C: .4byte gVFXHeaderPtr
_080C1960: .4byte gVFXFnTable

	thumb_func_start VFX57_Init
VFX57_Init: @ 0x080C1964
	push {lr}
	adds r1, r0, #0
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _080C1976
	adds r0, r1, #0
	bl FUN_080c19b4
	b _080C197C
_080C1976:
	adds r0, r1, #0
	bl FUN_080c1a3c
_080C197C:
	pop {r0}
	bx r0

	thumb_func_start VFX57_Update
VFX57_Update: @ 0x080C1980
	push {lr}
	adds r1, r0, #0
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _080C1992
	adds r0, r1, #0
	bl FUN_080c1aec
	b _080C1998
_080C1992:
	adds r0, r1, #0
	bl FUN_080c1b34
_080C1998:
	pop {r0}
	bx r0
