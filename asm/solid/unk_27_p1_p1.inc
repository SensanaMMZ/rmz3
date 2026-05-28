	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080d8f2c
FUN_080d8f2c: @ 0x080D8F2C
	push {r4, lr}
	ldr r0, _080D8F74 @ =gSolidHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080D8F6A
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x1e
	strb r0, [r1]
	ldr r1, _080D8F78 @ =gSolidFnTable
	movs r0, #0x1b
	strb r0, [r4, #9]
	ldr r0, [r1, #0x6c]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r2, #0
	strh r3, [r4, #0x20]
	adds r0, r4, #0
	adds r0, #0x22
	strb r2, [r0]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	strb r2, [r4, #0x10]
_080D8F6A:
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080D8F74: .4byte gSolidHeaderPtr
_080D8F78: .4byte gSolidFnTable

	thumb_func_start FUN_080d8f7c
FUN_080d8f7c: @ 0x080D8F7C
	push {r4, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r0, _080D8FCC @ =gSolidHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080D8FC2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x1e
	strb r0, [r1]
	ldr r1, _080D8FD0 @ =gSolidFnTable
	movs r0, #0x1b
	strb r0, [r3, #9]
	ldr r0, [r1, #0x6c]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #1
	strb r0, [r3, #0x10]
	strb r4, [r3, #0x11]
_080D8FC2:
	adds r0, r3, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080D8FCC: .4byte gSolidHeaderPtr
_080D8FD0: .4byte gSolidFnTable
