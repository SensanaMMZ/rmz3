	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start anubisMode0
anubisMode0: @ 0x080503CC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0xb
	bls _080503D8
	b _080505E6
_080503D8:
	lsls r0, r0, #2
	ldr r1, _080503E4 @ =_080503E8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080503E4: .4byte _080503E8
_080503E8: @ jump table
	.4byte _08050418 @ case 0
	.4byte _080504E0 @ case 1
	.4byte _08050516 @ case 2
	.4byte _08050528 @ case 3
	.4byte _0805053C @ case 4
	.4byte _08050592 @ case 5
	.4byte _08050544 @ case 6
	.4byte _08050560 @ case 7
	.4byte _08050584 @ case 8
	.4byte _08050592 @ case 9
	.4byte _080505B0 @ case 10
	.4byte _080505BE @ case 11
_08050418:
	ldrb r0, [r5, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r5, #0xa]
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _080504C4
	ldr r4, _080504A4 @ =0x000005DC
	ldr r1, _080504A8 @ =gStaticMotionGraphics
	adds r0, r4, r1
	ldr r1, _080504AC @ =wStaticGraphicTilenums
	adds r1, #0x96
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080504B0 @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldr r0, _080504B4 @ =wStaticMotionPalIDs
	adds r0, #0x96
	ldrh r1, [r0]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	adds r4, r5, #0
	adds r4, #0xbc
	ldr r0, [r4]
	ldr r1, _080504B8 @ =0xFFFF4000
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r1, _080504BC @ =0x0000AF0C
	adds r0, r5, #0
	bl SetMotion
	ldr r0, [r4]
	ldr r2, _080504C0 @ =0xFFFF8A00
	adds r1, r0, r2
	ldr r0, [r5, #0x58]
	subs r1, r1, r0
	adds r0, r1, #0
	cmp r1, #0
	bge _08050486
	adds r0, r1, #3
_08050486:
	asrs r0, r0, #2
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xd
	str r0, [r5, #0x60]
	adds r0, r5, #0
	bl FUN_080bf3d8
	movs r0, #0x10
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080504E0
	.align 2, 0
_080504A4: .4byte 0x000005DC
_080504A8: .4byte gStaticMotionGraphics
_080504AC: .4byte wStaticGraphicTilenums
_080504B0: .4byte gStaticMotionGraphics+12
_080504B4: .4byte wStaticMotionPalIDs
_080504B8: .4byte 0xFFFF4000
_080504BC: .4byte 0x0000AF0C
_080504C0: .4byte 0xFFFF8A00
_080504C4:
	adds r0, r5, #0
	adds r0, #0xbc
	ldr r0, [r0]
	ldr r1, _080504DC @ =0xFFFF8A00
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r1, r5, #0
	adds r1, #0xc4
	str r0, [r1]
	movs r0, #6
	strb r0, [r5, #0xe]
	b _080505E6
	.align 2, 0
_080504DC: .4byte 0xFFFF8A00
_080504E0:
	ldr r1, [r5, #0x60]
	cmp r1, #0
	bge _08050508
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08050578
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r2, r5, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #1
	orrs r0, r1
	str r0, [r2]
	b _08050572
_08050508:
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r1, #0
	subs r0, #8
	str r0, [r5, #0x60]
	b _08050578
_08050516:
	adds r1, r5, #0
	adds r1, #0xc4
	ldr r0, [r5, #0x58]
	str r0, [r1]
	movs r0, #0x64
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050528:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080505E6
	b _080505A2
_0805053C:
	ldr r1, _08050540 @ =0x0000AF0D
	b _08050586
	.align 2, 0
_08050540: .4byte 0x0000AF0D
_08050544:
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl FUN_080a4ef8
	ldr r1, _08050580 @ =0x0000AF01
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050560:
	adds r0, r5, #0
	bl FUN_08050090
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08050578
_08050572:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050578:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080505E6
	.align 2, 0
_08050580: .4byte 0x0000AF01
_08050584:
	ldr r1, _080505AC @ =0x0000AF02
_08050586:
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050592:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080505E6
_080505A2:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080505E6
	.align 2, 0
_080505AC: .4byte 0x0000AF02
_080505B0:
	ldr r1, _080505EC @ =0x0000AF01
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080505BE:
	adds r0, r5, #0
	bl FUN_08050090
	ldr r0, _080505F0 @ =gStageRun
	ldrb r1, [r0, #0x12]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _080505E0
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080505F4 @ =0x08363584
	bl SetDDP
	strb r4, [r5, #0xd]
	strb r4, [r5, #0xe]
_080505E0:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080505E6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080505EC: .4byte 0x0000AF01
_080505F0: .4byte gStageRun
_080505F4: .4byte 0x08363584

	thumb_func_start anubisNeutral
anubisNeutral: @ 0x080505F8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0805062E
	cmp r0, #1
	bgt _08050610
	cmp r0, #0
	beq _08050616
	b _080507CC
_08050610:
	cmp r0, #2
	beq _08050638
	b _080507CC
_08050616:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08050668 @ =0x08363584
	bl SetDDP
	ldr r1, _0805066C @ =0x0000AF01
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805062E:
	movs r0, #0x30
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050638:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xcd
	ldrb r0, [r0]
	adds r1, r4, #0
	adds r1, #0xa4
	movs r2, #0
	ldrsh r1, [r1, r2]
	subs r0, r0, r1
	cmp r0, #0xf
	ble _08050676
	adds r0, r4, #0
	adds r0, #0xce
	ldrb r1, [r0]
	cmp r1, #0
	beq _08050670
	movs r0, #0xa
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
	b _08050676
	.align 2, 0
_08050668: .4byte 0x08363584
_0805066C: .4byte 0x0000AF01
_08050670:
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08050676:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _0805067E
	b _080507C0
_0805067E:
	ldr r0, _080506B4 @ =pZero2
	ldr r2, [r0]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r1, r0
	cmp r1, #0
	beq _08050694
	b _080507C0
_08050694:
	adds r0, r2, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _080506A2
	b _080507C0
_080506A2:
	adds r2, r4, #0
	adds r2, #0xd2
	ldrb r0, [r2]
	cmp r0, #0
	beq _080506B8
	strb r1, [r2]
	movs r0, #2
	b _080507BC
	.align 2, 0
_080506B4: .4byte pZero2
_080506B8:
	adds r0, r4, #0
	adds r0, #0xcb
	ldrb r0, [r0]
	cmp r0, #2
	bls _0805073C
	ldr r7, _080506D0 @ =0x083635C0
	ldr r0, _080506D4 @ =gMission
	mov r8, r0
	ldr r6, _080506D8 @ =RNG_0202f388
	adds r5, r4, #0
	adds r5, #0xcf
	b _080506E4
	.align 2, 0
_080506D0: .4byte 0x083635C0
_080506D4: .4byte gMission
_080506D8: .4byte RNG_0202f388
_080506DC:
	adds r0, r1, r7
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _080507AC
_080506E4:
	mov r1, r8
	ldr r0, [r1]
	ldrb r0, [r0, #1]
	cmp r0, #4
	bls _08050710
	ldr r1, [r6]
	ldr r0, _08050708 @ =0x000343FD
	muls r0, r1, r0
	ldr r2, _0805070C @ =0x00269EC3
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r6]
	lsrs r1, r0, #0x11
	movs r0, #3
	ands r1, r0
	b _0805072C
	.align 2, 0
_08050708: .4byte 0x000343FD
_0805070C: .4byte 0x00269EC3
_08050710:
	ldr r1, [r6]
	ldr r0, _08050734 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08050738 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r6]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
_0805072C:
	ldrb r0, [r5]
	cmp r0, #0
	bne _080506DC
	b _080507AC
	.align 2, 0
_08050734: .4byte 0x000343FD
_08050738: .4byte 0x00269EC3
_0805073C:
	ldr r2, _0805074C @ =gMission
	mov r8, r2
	ldr r6, _08050750 @ =RNG_0202f388
	adds r5, r4, #0
	adds r5, #0xcf
	ldr r7, _08050754 @ =0x083635C4
	b _08050760
	.align 2, 0
_0805074C: .4byte gMission
_08050750: .4byte RNG_0202f388
_08050754: .4byte 0x083635C4
_08050758:
	adds r0, r1, r7
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _080507AC
_08050760:
	mov r1, r8
	ldr r0, [r1]
	ldrb r0, [r0, #1]
	cmp r0, #4
	bls _08050790
	ldr r1, [r6]
	ldr r0, _08050788 @ =0x000343FD
	muls r0, r1, r0
	ldr r2, _0805078C @ =0x00269EC3
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r6]
	lsrs r0, r0, #0x11
	movs r1, #5
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	b _080507A6
	.align 2, 0
_08050788: .4byte 0x000343FD
_0805078C: .4byte 0x00269EC3
_08050790:
	ldr r1, [r6]
	ldr r0, _080507D8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080507DC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r6]
	lsrs r1, r0, #0x11
	movs r0, #3
	ands r1, r0
_080507A6:
	ldrb r0, [r5]
	cmp r0, #0
	bne _08050758
_080507AC:
	ldrb r0, [r5]
	cmp r0, #0
	beq _080507B6
	subs r0, #1
	strb r0, [r5]
_080507B6:
	adds r0, r1, r7
	ldrb r0, [r0]
	movs r1, #0
_080507BC:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080507C0:
	adds r0, r4, #0
	bl FUN_08050090
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080507CC:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080507D8: .4byte 0x000343FD
_080507DC: .4byte 0x00269EC3

	thumb_func_start anubisMode2
anubisMode2: @ 0x080507E0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0805082C
	cmp r0, #1
	bgt _080507F4
	cmp r0, #0
	beq _080507FE
	b _0805089E
_080507F4:
	cmp r0, #2
	beq _0805084C
	cmp r0, #3
	beq _08050876
	b _0805089E
_080507FE:
	movs r0, #0x54
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0xd0
	strh r0, [r1]
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #2
	orrs r0, r1
	subs r1, #7
	ands r0, r1
	subs r1, #0xc
	ands r0, r1
	str r0, [r2]
	ldr r1, _08050848 @ =0x0000AF02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805082C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #3
	bne _0805089E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0805089E
	.align 2, 0
_08050848: .4byte 0x0000AF02
_0805084C:
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #3
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805086E
	ldr r2, _080508A4 @ =0xFFFFFE00
_0805086E:
	str r2, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050876:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, _080508A8 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bls _0805089E
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805089E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080508A4: .4byte 0xFFFFFE00
_080508A8: .4byte gStageRun+232

	thumb_func_start anubisMode3
anubisMode3: @ 0x080508AC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bls _080508B8
	b _08050A12
_080508B8:
	lsls r0, r0, #2
	ldr r1, _080508C4 @ =_080508C8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080508C4: .4byte _080508C8
_080508C8: @ jump table
	.4byte _080508DC @ case 0
	.4byte _080508EC @ case 1
	.4byte _08050900 @ case 2
	.4byte _080509A4 @ case 3
	.4byte _080509D8 @ case 4
_080508DC:
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080508EC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080508FA
	b _08050A12
_080508FA:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _08050A10
_08050900:
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #4
	orrs r0, r1
	str r0, [r2]
	movs r0, #0xd0
	lsls r0, r0, #3
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	strb r0, [r4, #0x12]
	lsls r0, r0, #4
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r5, r4, #0
	adds r5, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r5]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r5]
	cmp r1, #0
	beq _08050954
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805095A
_08050954:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805095A:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r2, #0x10
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _08050980
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r1, _0805097C @ =0xFFFF6800
	adds r0, r0, r1
	str r0, [r4, #0x54]
	movs r0, #0x10
	rsbs r0, r0, #0
	str r0, [r4, #0x64]
	b _08050996
	.align 2, 0
_0805097C: .4byte 0xFFFF6800
_08050980:
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	movs r1, #0x98
	lsls r1, r1, #8
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	str r2, [r4, #0x64]
_08050996:
	ldr r1, _080509D4 @ =0x0000AF01
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080509A4:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080509B6
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080509B6:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08050090
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08050A12
	.align 2, 0
_080509D4: .4byte 0x0000AF01
_080509D8:
	adds r0, r4, #0
	bl FUN_08050090
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	bne _08050A12
	adds r5, r4, #0
	adds r5, #0xd0
	movs r0, #0
	ldrsh r1, [r5, r0]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	beq _08050A0C
	adds r0, r1, #0
	bl StopSound
	ldr r0, _08050A18 @ =0x0000FFFF
	strh r0, [r5]
_08050A0C:
	movs r0, #1
	strb r0, [r4, #0xd]
_08050A10:
	strb r0, [r4, #0xe]
_08050A12:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08050A18: .4byte 0x0000FFFF

	thumb_func_start anubisMode4
anubisMode4: @ 0x08050A1C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08050A64
	cmp r0, #1
	bgt _08050A30
	cmp r0, #0
	beq _08050A3A
	b _08050AD6
_08050A30:
	cmp r0, #2
	beq _08050A80
	cmp r0, #3
	beq _08050A9C
	b _08050AD6
_08050A3A:
	movs r0, #0x54
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0xd0
	strh r0, [r1]
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #8
	orrs r0, r1
	movs r1, #0x10
	orrs r0, r1
	str r0, [r2]
	ldr r1, _08050A7C @ =0x0000AF02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050A64:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08050AD6
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _08050AD4
	.align 2, 0
_08050A7C: .4byte 0x0000AF02
_08050A80:
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #9
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	ldr r1, _08050ADC @ =0x0000AF01
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050A9C:
	adds r0, r4, #0
	bl FUN_08050090
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08050AD6
	adds r5, r4, #0
	adds r5, #0xd0
	movs r0, #0
	ldrsh r1, [r5, r0]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	beq _08050AD0
	adds r0, r1, #0
	bl StopSound
	ldr r0, _08050AE0 @ =0x0000FFFF
	strh r0, [r5]
_08050AD0:
	movs r0, #1
	strb r0, [r4, #0xd]
_08050AD4:
	strb r0, [r4, #0xe]
_08050AD6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08050ADC: .4byte 0x0000AF01
_08050AE0: .4byte 0x0000FFFF

	thumb_func_start anubisMode5
anubisMode5: @ 0x08050AE4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08050AF4
	cmp r0, #1
	beq _08050B3E
	b _08050B62
_08050AF4:
	adds r0, r4, #0
	adds r0, #0xce
	ldrb r0, [r0]
	cmp r0, #0
	beq _08050B10
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #1
	strb r0, [r4, #0xd]
	movs r0, #2
	strb r0, [r4, #0xe]
	strb r0, [r4, #0x12]
	b _08050B62
_08050B10:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08050B68 @ =sCollisions
	bl SetDDP
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #1
	orrs r0, r1
	movs r1, #0x20
	orrs r0, r1
	subs r1, #0x61
	ands r0, r1
	str r0, [r2]
	ldr r1, _08050B6C @ =0x0000AF08
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08050B3E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08050B62
	adds r2, r4, #0
	adds r2, #0xc0
	ldr r0, [r2]
	ldr r1, _08050B70 @ =0xFFFFFEFF
	ands r0, r1
	str r0, [r2]
	movs r1, #0
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08050B62:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08050B68: .4byte sCollisions
_08050B6C: .4byte 0x0000AF08
_08050B70: .4byte 0xFFFFFEFF

	thumb_func_start anubisMode6
anubisMode6: @ 0x08050B74
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08050B84
	cmp r0, #1
	beq _08050BFE
	b _08050C62
_08050B84:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r4, _08050C24 @ =0x000005DC
	ldr r1, _08050C28 @ =gStaticMotionGraphics
	adds r0, r4, r1
	ldr r1, _08050C2C @ =wStaticGraphicTilenums
	adds r1, #0x96
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _08050C30 @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldr r0, _08050C34 @ =wStaticMotionPalIDs
	adds r0, #0x96
	ldrh r1, [r0]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	ldr r3, _08050C38 @ =0x083635C9
	ldr r2, _08050C3C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08050C40 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08050C44 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #7
	ands r1, r0
	adds r0, r5, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r0, [r0, r2]
	cmp r0, #0x1f
	bgt _08050BEE
	adds r1, #8
_08050BEE:
	adds r0, r1, r3
	ldrb r0, [r0]
	strb r0, [r5, #0x12]
	movs r0, #0x1e
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08050BFE:
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08050C62
	movs r0, #0x60
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08050C48
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
	b _08050C4C
	.align 2, 0
_08050C24: .4byte 0x000005DC
_08050C28: .4byte gStaticMotionGraphics
_08050C2C: .4byte wStaticGraphicTilenums
_08050C30: .4byte gStaticMotionGraphics+12
_08050C34: .4byte wStaticMotionPalIDs
_08050C38: .4byte 0x083635C9
_08050C3C: .4byte RNG_0202f388
_08050C40: .4byte 0x000343FD
_08050C44: .4byte 0x00269EC3
_08050C48:
	movs r0, #1
	strb r0, [r5, #0xe]
_08050C4C:
	movs r0, #0x55
	bl PlaySound
	movs r1, #0
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _08050C5C
	movs r1, #1
_08050C5C:
	adds r0, r5, #0
	bl CreateAnubisCoffins
_08050C62:
	pop {r4, r5}
	pop {r0}
	bx r0

