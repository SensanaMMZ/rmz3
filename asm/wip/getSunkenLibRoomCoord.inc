	push {lr}
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #7
	bls _0801F6FC
	ldr r0, _0801F6F4 @ =0x0202FFF4
	adds r0, r1, r0
	ldrb r0, [r0]
	lsls r0, r0, #3
	ldr r1, _0801F6F8 @ =sSunkenLibRoom
	b _0801F706
	.align 2, 0
_0801F6F4: .4byte 0x0202FFF4
_0801F6F8: .4byte sSunkenLibRoom
_0801F6FC:
	ldr r0, _0801F70C @ =0x0202FFF4
	adds r0, r1, r0
	ldrb r0, [r0]
	lsls r0, r0, #3
	ldr r1, _0801F710 @ =sSunkenLibRoom
_0801F706:
	adds r0, r0, r1
	pop {r1}
	bx r1
	.align 2, 0
_0801F70C: .4byte 0x0202FFF4
_0801F710: .4byte sSunkenLibRoom
