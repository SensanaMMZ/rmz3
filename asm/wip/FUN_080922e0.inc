push {r4, r5, r6, lr}
adds r5, r0, #0
ldrb r0, [r5, #0xe]
cmp r0, #1
beq _08092348
cmp r0, #1
bgt _080922F4
cmp r0, #0
beq _080922FE
b _080923E2
_080922F4:
cmp r0, #2
beq _08092374
cmp r0, #3
beq _0809237E
b _080923E2
_080922FE:
adds r0, r5, #0
bl InitNonAffineMotion
ldrb r2, [r5, #0x13]
cmp r2, #0
beq _08092312
ldrb r1, [r5, #0xa]
movs r0, #0x10
orrs r0, r1
b _08092318
_08092312:
ldrb r1, [r5, #0xa]
movs r0, #0xef
ands r0, r1
_08092318:
strb r0, [r5, #0xa]
movs r1, #1
ands r1, r2
adds r0, r5, #0
adds r0, #0x4c
strb r1, [r0]
adds r3, r5, #0
adds r3, #0x4a
lsls r1, r1, #4
ldrb r2, [r3]
movs r0, #0x11
rsbs r0, r0, #0
ands r0, r2
orrs r0, r1
strb r0, [r3]
ldr r1, _08092370 @ =0x00001303
adds r0, r5, #0
bl SetMotion
movs r0, #0x12
strb r0, [r5, #0x12]
ldrb r0, [r5, #0xe]
adds r0, #1
strb r0, [r5, #0xe]
_08092348:
adds r0, r5, #0
bl UpdateMotionGraphic
ldrb r0, [r5, #0x12]
subs r0, #1
strb r0, [r5, #0x12]
movs r1, #3
ands r0, r1
cmp r0, #0
bne _08092362
adds r0, r5, #0
bl FUN_08091280
_08092362:
ldrb r0, [r5, #0x12]
cmp r0, #0
bne _080923E2
ldrb r0, [r5, #0xe]
adds r0, #1
strb r0, [r5, #0xe]
b _080923E2
.align 2, 0
_08092370: .4byte 0x00001303
_08092374:
movs r0, #0
strb r0, [r5, #0x12]
ldrb r0, [r5, #0xe]
adds r0, #1
strb r0, [r5, #0xe]
_0809237E:
adds r0, r5, #0
bl UpdateMotionGraphic
ldrb r0, [r5, #0x12]
cmp r0, #0
bne _08092390
movs r0, #0x2a
bl PlaySound
_08092390:
ldrb r0, [r5, #0x12]
adds r0, #1
strb r0, [r5, #0x12]
adds r4, r5, #0
adds r4, #0x54
ldrb r2, [r5, #0xa]
lsrs r2, r2, #4
movs r0, #1
ands r2, r0
ldrb r3, [r5, #0x13]
adds r0, r4, #0
movs r1, #0
bl CreateGhost18
ldr r6, _080923C0 @ =0x08369848
ldrb r2, [r5, #0x13]
ldrb r1, [r5, #0xa]
movs r3, #0x10
adds r0, r3, #0
ands r0, r1
cmp r0, #0
beq _080923C4
orrs r3, r2
b _080923C6
.align 2, 0
_080923C0: .4byte 0x08369848
_080923C4:
adds r3, r2, #0
_080923C6:
adds r0, r4, #0
adds r1, r6, #0
movs r2, #0
bl CreateSlashedEnemy
ldr r1, _080923E8 @ =gEnemyFnTable
ldrb r0, [r5, #9]
lsls r0, r0, #2
adds r0, r0, r1
movs r1, #4
str r1, [r5, #0xc]
ldr r0, [r0]
ldr r0, [r0, #0x10]
str r0, [r5, #0x14]
_080923E2:
pop {r4, r5, r6}
pop {r0}
bx r0
.align 2, 0
_080923E8: .4byte gEnemyFnTable

