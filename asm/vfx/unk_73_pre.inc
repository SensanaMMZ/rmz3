	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c6e70
FUN_080c6e70: @ 0x080C6E70
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	mov r8, r0
	adds r5, r1, #0
	movs r4, #0
	movs r7, #0
	movs r6, #1
	ldr r0, _080C6ED0 @ =0x0836DA24
	mov sb, r0
_080C6E86:
	ldr r0, _080C6ED4 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r1, r0, #0
	cmp r1, #0
	beq _080C6EBC
	adds r0, #0x25
	strb r6, [r0]
	movs r0, #0x49
	strb r0, [r1, #9]
	mov r2, sb
	ldr r0, [r2]
	ldr r0, [r0]
	str r0, [r1, #0x14]
	strh r7, [r1, #0x20]
	adds r0, r1, #0
	adds r0, #0x22
	strb r7, [r0]
	strb r6, [r1, #0x10]
	strb r4, [r1, #0x11]
	mov r0, r8
	str r0, [r1, #0x28]
	ldr r0, [r5]
	str r0, [r1, #0x54]
	ldr r0, [r5, #4]
	str r0, [r1, #0x58]
_080C6EBC:
	adds r4, #1
	cmp r4, #2
	ble _080C6E86
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C6ED0: .4byte 0x0836DA24
_080C6ED4: .4byte gVFXHeaderPtr
