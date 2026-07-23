glabel unused_080e14d4
	push {lr}
	lsl r0, r0, #24
	lsr r3, r0, #24
	ldr r0, _080E14FC
	ldr r0, [r0]
	add r2, r0, #0
	add r2, #0x14
	cmp r1, #0
	bne _080E14E8
	add r1, r2, #0
_080E14E8:
	ldr r1, [r1, #4]
	cmp r1, r2
	beq _080E14F8
	ldrb r0, [r1, #9]
	cmp r0, r3
	bne _080E14E8
	cmp r1, r2
	bne _080E1500
_080E14F8:
	mov r0, #0
	b _080E1502
	.align 2, 0
_080E14FC: .4byte gElfHeaderPtr
_080E1500:
	add r0, r1, #0
_080E1502:
	pop {r1}
	bx r1
