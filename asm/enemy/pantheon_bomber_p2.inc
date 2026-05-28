	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start pantheon_bomber_0808633c
pantheon_bomber_0808633c: @ 0x0808633C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0808634C
	cmp r5, #1
	beq _08086372
	b _08086390
_0808634C:
	ldr r1, _08086398 @ =0x00006904
	adds r0, r4, #0
	movs r2, #2
	movs r3, #1
	bl GotoMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808639C @ =0x08368534
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0xb9
	strb r5, [r0]
	movs r0, #0x30
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08086372:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08086388
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08086390
_08086388:
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08086390:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08086398: .4byte 0x00006904
_0808639C: .4byte 0x08368534
