	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e56a0
FUN_080e56a0: @ 0x080E56A0
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl FUN_080e586c
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080E56C6
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080E56E4
_080E56C6:
	ldr r1, _080E56E0 @ =gElfFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Elf11_Die
	b _080E570C
	.align 2, 0
_080E56E0: .4byte gElfFnTable
_080E56E4:
	movs r0, #0x80
	lsls r0, r0, #5
	ands r1, r0
	cmp r1, #0
	beq _080E570C
	movs r0, #0x2b
	bl PlaySound
	ldr r1, _080E5714 @ =gElfFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Elf11_Die
_080E570C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080E5714: .4byte gElfFnTable

