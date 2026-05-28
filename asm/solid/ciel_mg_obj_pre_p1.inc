	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createCielMiniObj
createCielMiniObj: @ 0x080DDD04
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _080DDD58 @ =gSolidHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080DDD52
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x1e
	strb r0, [r1]
	ldr r0, _080DDD5C @ =gSolidFnTable
	movs r1, #0x2a
	strb r1, [r3, #9]
	adds r0, #0xa8
	ldr r0, [r0]
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
	str r6, [r3, #0x28]
	strb r5, [r3, #0x10]
	strb r4, [r3, #0x11]
_080DDD52:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DDD58: .4byte gSolidHeaderPtr
_080DDD5C: .4byte gSolidFnTable
