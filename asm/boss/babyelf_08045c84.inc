	push {r4, r5, lr}
	mov ip, r0
	adds r0, #0xbc
	ldr r1, [r0]
	mov r0, ip
	str r1, [r0, #0x54]
	adds r0, #0xc0
	ldr r4, [r0]
	mov r2, ip
	str r4, [r2, #0x58]
	adds r0, #4
	ldrh r3, [r0]
	ldr r0, _08045CD4 @ =0x000001FF
	ands r3, r0
	cmp r3, #0xff
	bgt _08045CE0
	ldr r2, _08045CD8 @ =gSineTable
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r5, #0
	ldrsh r0, [r0, r5]
	lsls r0, r0, #4
	adds r0, r1, r0
	mov r1, ip
	str r0, [r1, #0x54]
	ldr r5, _08045CDC @ =0xFFFFF000
	adds r1, r4, r5
	mov r0, ip
	str r1, [r0, #0x58]
	adds r0, r3, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #4
	adds r1, r1, r0
	b _08045D14
	.align 2, 0
_08045CD4: .4byte 0x000001FF
_08045CD8: .4byte gSineTable
_08045CDC: .4byte 0xFFFFF000
_08045CE0:
	ldr r0, _08045D20 @ =0xFFFFFF00
	adds r3, r3, r0
	ldr r2, _08045D24 @ =gSineTable
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r5, #0
	ldrsh r0, [r0, r5]
	lsls r0, r0, #4
	adds r0, r1, r0
	mov r1, ip
	str r0, [r1, #0x54]
	movs r5, #0x80
	lsls r5, r5, #5
	adds r1, r4, r5
	mov r0, ip
	str r1, [r0, #0x58]
	adds r0, r3, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #4
	subs r1, r1, r0
_08045D14:
	mov r5, ip
	str r1, [r5, #0x58]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08045D20: .4byte 0xFFFFFF00
_08045D24: .4byte gSineTable
