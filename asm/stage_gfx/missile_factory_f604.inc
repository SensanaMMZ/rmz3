	push {r4, r5, lr}
	ldrh r4, [r0, #0x10]
	movs r0, #0xa0
	lsls r0, r0, #2
	bl Malloc
	adds r3, r0, #0
	cmp r3, #0
	beq _0800F67A
	ldr r2, _0800F680 @ =gIntrManager
	movs r1, #0xba
	lsls r1, r1, #1
	adds r0, r2, r1
	str r3, [r0]
	movs r5, #0xbc
	lsls r5, r5, #1
	adds r1, r2, r5
	ldr r0, _0800F684 @ =0x0400001C
	str r0, [r1]
	movs r0, #0xbe
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _0800F688 @ =0xA6600001
	str r0, [r1]
	lsrs r1, r4, #6
	movs r2, #0x9e
	lsls r2, r2, #1
	adds r0, r3, r2
_0800F63C:
	str r1, [r0]
	subs r0, #4
	cmp r0, r3
	bge _0800F63C
	lsrs r2, r4, #5
	movs r5, #0xa0
	lsls r5, r5, #1
	adds r0, r3, r5
	movs r1, #7
_0800F64E:
	stm r0!, {r2}
	subs r1, #1
	cmp r1, #0
	bge _0800F64E
	lsrs r2, r4, #3
	movs r1, #0x58
	movs r5, #0xb0
	lsls r5, r5, #1
	adds r0, r3, r5
_0800F660:
	stm r0!, {r2}
	adds r1, #1
	cmp r1, #0x6f
	ble _0800F660
	cmp r1, #0x9f
	bgt _0800F67A
	lsrs r2, r4, #2
	lsls r0, r1, #2
	adds r0, r0, r3
_0800F672:
	stm r0!, {r2}
	adds r1, #1
	cmp r1, #0x9f
	ble _0800F672
_0800F67A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0800F680: .4byte gIntrManager
_0800F684: .4byte 0x0400001C
_0800F688: .4byte 0xA6600001

