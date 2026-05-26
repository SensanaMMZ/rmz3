	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Leviathan_Update
Leviathan_Update: @ 0x08035F74
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	bne _08035FA2
	ldr r1, _08035FD4 @ =0x0835EC00
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _08035FD8 @ =0x0835EC0C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_08035FA2:
	movs r0, #0x9f
	lsls r0, r0, #2
	adds r2, r4, r0
	ldr r0, [r2]
	ldr r3, _08035FDC @ =0xFFFF9400
	adds r1, r0, r3
	ldr r0, [r4, #0x54]
	cmp r0, r1
	bgt _08035FBA
	str r1, [r4, #0x54]
	movs r0, #0
	str r0, [r4, #0x5c]
_08035FBA:
	ldr r0, [r2]
	movs r2, #0xd8
	lsls r2, r2, #7
	adds r1, r0, r2
	ldr r0, [r4, #0x54]
	cmp r0, r1
	blt _08035FCE
	str r1, [r4, #0x54]
	movs r0, #0
	str r0, [r4, #0x5c]
_08035FCE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08035FD4: .4byte 0x0835EC00
_08035FD8: .4byte 0x0835EC0C
_08035FDC: .4byte 0xFFFF9400

	thumb_func_start Leviathan_Die
Leviathan_Die: @ 0x08035FE0
	ldr r2, _08035FF4 @ =gPlayerFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r2, #4
	str r2, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #0x10]
	str r1, [r0, #0x14]
	bx lr
	.align 2, 0
_08035FF4: .4byte gPlayerFnTable

	thumb_func_start leviathanMode0Pre
leviathanMode0Pre: @ 0x08035FF8
	push {lr}
	adds r2, r0, #0
	ldr r3, [r2, #0x28]
	ldrh r1, [r3, #0x10]
	movs r0, #0x30
	ands r0, r1
	cmp r0, #0
	beq _08036010
	movs r1, #0
	movs r0, #1
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08036010:
	ldrh r1, [r3, #0x12]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08036022
	movs r1, #0
	movs r0, #2
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08036022:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start leviathanMode1Pre
leviathanMode1Pre: @ 0x08036028
	push {lr}
	adds r2, r0, #0
	ldr r0, [r2, #0x28]
	ldrh r1, [r0, #0x12]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08036040
	movs r1, #0
	movs r0, #2
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08036040:
	pop {r0}
	bx r0
