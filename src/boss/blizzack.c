#include "boss.h"
#include "collision.h"
#include "global.h"
#include "zero.h"
#include "stagerun.h"

void Blizzack_Init(struct Boss* p);
void Blizzack_Update(struct Boss* p);
void Blizzack_Die(struct Boss* p);

// clang-format off
const BossRoutine gBlizzackRoutine = {
    [ENTITY_INIT] =      (BossFunc)Blizzack_Init,
    [ENTITY_UPDATE] =    (BossFunc)Blizzack_Update,
    [ENTITY_DIE] =       (BossFunc)Blizzack_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

void CreateBlizzack(struct Coord* c) {
  struct Entity* p = AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_BLIZZACK);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = 0, p->work[1] = 0;
  }
}

// --------------------------------------------

static const BossFunc sDeads[3];

NAKED void Blizzack_Init(struct Boss* p) {
  asm(".syntax unified
\n	push {r4, r5, r6, r7, lr}
\n	mov r7, sl
\n	mov r6, sb
\n	mov r5, r8
\n	push {r5, r6, r7}
\n	adds r7, r0, #0
\n	ldr r1, _08059C94 @ =gBossFnTable
\n	ldrb r0, [r7, #9]
\n	lsls r0, r0, #2
\n	adds r0, r0, r1
\n	movs r1, #1
\n	str r1, [r7, #0xc]
\n	ldr r0, [r0]
\n	ldr r0, [r0, #4]
\n	str r0, [r7, #0x14]
\n	movs r4, #0xfa
\n	lsls r4, r4, #3
\n	ldr r5, _08059C98 @ =gStaticMotionGraphics
\n	adds r0, r4, r5
\n	ldr r2, _08059C9C @ =wStaticGraphicTilenums
\n	mov sb, r2
\n	mov r1, sb
\n	adds r1, #0xc8
\n	ldrh r1, [r1]
\n	ldrh r2, [r0, #6]
\n	lsrs r2, r2, #6
\n	subs r1, r1, r2
\n	lsls r1, r1, #5
\n	movs r6, #0x80
\n	lsls r6, r6, #9
\n	adds r1, r1, r6
\n	bl LoadGraphic
\n	ldr r0, _08059CA0 @ =gStaticMotionGraphics+12
\n	mov r8, r0
\n	add r4, r8
\n	ldr r1, _08059CA4 @ =wStaticMotionPalIDs
\n	mov sl, r1
\n	mov r0, sl
\n	adds r0, #0xc8
\n	ldrh r1, [r0]
\n	ldrb r0, [r4, #7]
\n	subs r1, r1, r0
\n	lsls r1, r1, #5
\n	movs r2, #0x80
\n	lsls r2, r2, #2
\n	adds r1, r1, r2
\n	adds r0, r4, #0
\n	bl LoadPalette
\n	movs r4, #0xf5
\n	lsls r4, r4, #3
\n	adds r0, r4, r5
\n	mov r1, sb
\n	adds r1, #0xc4
\n	ldrh r1, [r1]
\n	ldrh r2, [r0, #6]
\n	lsrs r2, r2, #6
\n	subs r1, r1, r2
\n	lsls r1, r1, #5
\n	adds r1, r1, r6
\n	bl LoadGraphic
\n	add r4, r8
\n	mov r0, sl
\n	adds r0, #0xc4
\n	ldrh r1, [r0]
\n	ldrb r0, [r4, #7]
\n	subs r1, r1, r0
\n	lsls r1, r1, #5
\n	movs r0, #0x80
\n	lsls r0, r0, #2
\n	adds r1, r1, r0
\n	adds r0, r4, #0
\n	bl LoadPalette
\n	ldr r4, _08059CA8 @ =0x000007BC
\n	adds r5, r4, r5
\n	mov r0, sb
\n	adds r0, #0xc6
\n	ldrh r1, [r0]
\n	ldrh r0, [r5, #6]
\n	lsrs r0, r0, #6
\n	subs r1, r1, r0
\n	lsls r1, r1, #5
\n	adds r1, r1, r6
\n	adds r0, r5, #0
\n	bl LoadGraphic
\n	add r4, r8
\n	mov r0, sl
\n	adds r0, #0xc6
\n	ldrh r1, [r0]
\n	ldrb r0, [r4, #7]
\n	subs r1, r1, r0
\n	lsls r1, r1, #5
\n	movs r2, #0x80
\n	lsls r2, r2, #2
\n	adds r1, r1, r2
\n	adds r0, r4, #0
\n	bl LoadPalette
\n	adds r0, r7, #0
\n	bl InitNonAffineMotion
\n	adds r0, r7, #0
\n	bl ResetDynamicMotion
\n	ldrb r1, [r7, #0xa]
\n	movs r0, #1
\n	movs r2, #0
\n	mov r8, r2
\n	orrs r0, r1
\n	movs r1, #2
\n	orrs r0, r1
\n	strb r0, [r7, #0xa]
\n	movs r1, #0xb4
\n	lsls r1, r1, #8
\n	adds r0, r7, #0
\n	bl SetMotion
\n	adds r0, r7, #0
\n	adds r0, #0x4c
\n	mov r1, r8
\n	strb r1, [r0]
\n	adds r2, r7, #0
\n	adds r2, #0x4a
\n	ldrb r1, [r2]
\n	movs r0, #0x11
\n	rsbs r0, r0, #0
\n	ands r0, r1
\n	strb r0, [r2]
\n	ldrb r1, [r7, #0xa]
\n	movs r0, #0xef
\n	ands r0, r1
\n	strb r0, [r7, #0xa]
\n	adds r1, r7, #0
\n	adds r1, #0xd0
\n	movs r0, #0x40
\n	strb r0, [r1]
\n	ldr r1, _08059CAC @ =sCollisions
\n	adds r0, r7, #0
\n	movs r2, #0x40
\n	bl ResetBossBody
\n	adds r2, r7, #0
\n	adds r2, #0x49
\n	ldrb r1, [r2]
\n	movs r0, #0xd
\n	rsbs r0, r0, #0
\n	ands r0, r1
\n	movs r1, #8
\n	orrs r0, r1
\n	strb r0, [r2]
\n	ldr r0, [r7, #0x54]
\n	ldr r1, [r7, #0x58]
\n	bl FUN_0800a134
\n	adds r1, r0, #0
\n	adds r4, r7, #0
\n	adds r4, #0xb8
\n	str r1, [r4]
\n	ldr r0, [r7, #0x54]
\n	bl FUN_0800a31c
\n	adds r5, r7, #0
\n	adds r5, #0xb4
\n	str r0, [r5]
\n	ldr r0, [r7, #0x54]
\n	ldr r1, [r4]
\n	bl FUN_0800a22c
\n	adds r1, r7, #0
\n	adds r1, #0xd8
\n	str r0, [r1]
\n	adds r3, r7, #0
\n	adds r3, #0xdc
\n	ldr r2, [r5]
\n	subs r0, r0, r2
\n	lsrs r1, r0, #0x1f
\n	adds r0, r0, r1
\n	asrs r0, r0, #1
\n	adds r2, r2, r0
\n	str r2, [r3]
\n	ldr r0, [r7, #0x54]
\n	ldr r1, [r7, #0x58]
\n	bl FUN_08009f6c
\n	adds r1, r7, #0
\n	adds r1, #0xbc
\n	str r0, [r1]
\n	str r0, [r7, #0x58]
\n	adds r1, #4
\n	ldr r0, [r7, #0x54]
\n	str r0, [r1]
\n	adds r0, r7, #0
\n	adds r0, #0xc5
\n	mov r2, r8
\n	strb r2, [r0]
\n	adds r0, #1
\n	strb r2, [r0]
\n	adds r0, #1
\n	strb r2, [r0]
\n	adds r1, #8
\n	ldr r0, _08059CB0 @ =0x0000FFFF
\n	strh r0, [r1]
\n	adds r0, r7, #0
\n	movs r1, #0
\n	movs r2, #0
\n	bl CreateEnemy42
\n	str r0, [r7, #0x2c]
\n	movs r1, #1
\n	strb r1, [r0, #0xe]
\n	ldr r0, [r7, #0x2c]
\n	adds r0, #0xbc
\n	movs r2, #0
\n	movs r1, #0xc8
\n	lsls r1, r1, #7
\n	strh r1, [r0]
\n	adds r1, r7, #0
\n	adds r1, #0xcc
\n	movs r0, #3
\n	strb r0, [r1]
\n	adds r1, #1
\n	strb r0, [r1]
\n	adds r1, #1
\n	strb r0, [r1]
\n	adds r0, r7, #0
\n	adds r0, #0xd4
\n	mov r1, r8
\n	str r1, [r0]
\n	adds r0, #0xc
\n	strb r2, [r0]
\n	strb r2, [r7, #0xd]
\n	movs r2, #1
\n	strb r2, [r7, #0xe]
\n	adds r0, r7, #0
\n	bl Blizzack_Update
\n	pop {r3, r4, r5}
\n	mov r8, r3
\n	mov sb, r4
\n	mov sl, r5
\n	pop {r4, r5, r6, r7}
\n	pop {r0}
\n	bx r0
\n	.align 2, 0
\n_08059C94: .4byte gBossFnTable
\n_08059C98: .4byte gStaticMotionGraphics
\n_08059C9C: .4byte wStaticGraphicTilenums
\n_08059CA0: .4byte gStaticMotionGraphics+12
\n_08059CA4: .4byte wStaticMotionPalIDs
\n_08059CA8: .4byte 0x000007BC
\n_08059CAC: .4byte sCollisions
\n_08059CB0: .4byte 0x0000FFFF
\n .syntax divided
");
}

INCASM("asm/boss/blizzack_pre.inc");

void Blizzack_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void blizzackMode0(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6400;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).work[2] = z;
  }
  UpdateMotionGraphic(&p->s);
  if (((struct Entity*)(p->s).scriptEntity)->id & 1) {
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 1;
  }
}

void blizzackMode1(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0x01));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6401;
    *t = v;
    (p->s).mode[2] = z;
    PlaySound(0x42);
  }
  UpdateMotionGraphic(&p->s);
  if (*(u8*)((u8*)p + 0x73) == 3 && (gStageRun.vm.active & 1) == 0) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/blizzack_rest_a.inc");

// 0x0805A140
void blizzackPreAI(struct Boss* p) {
  struct Zero* z;
  u8 f;
  if ((p->s).mode[2] != 0) {
    register u8 zz asm("r2");
    SetMotion(&p->s, MOTION(0xB4, 0x00));
    ((p->s).unk_2c)->mode[2] = 1;
    {
      register u16* h asm("r0");
      register s32 hv asm("r1");
      h = (u16*)((u8*)(p->s).unk_2c + 0xbc);
      zz = 0;
      asm("" : "+r"(zz));
      hv = 0x6400;
      *h = hv;
    }
    (p->s).mode[2] = zz;
    (p->s).work[2] = 0x20;
  }
  UpdateMotionGraphic(&p->s);
  f = 0;
  z = pZero2;
  if ((z->s).coord.x > (p->s).coord.x) {
    f = 1;
  }
  ((p->s).spr).xflip = f;
  f = 0;
  if ((z->s).coord.x > (p->s).coord.x) {
    f = 1;
  }
  {
    register u8* oa asm("ip");
    u32 sh4;
    s32 ov;
    s32 m11;
    oa = (u8*)p + 0x4a;
    sh4 = f << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    m11 |= sh4;
    *oa = m11;
  }
  if (f != 0) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= 0xEF;
  }
  if ((u8)--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 1;
  }
}

// blizzackNextMode does not match for the same regmove reason as blizzackMode1:
// agbcc schedules the mode[2]=0 zero early, forcing the 0x6402 constant into a
// spare reg + copy the target avoids. Logic is faithful in the MODERN branch;
// the INCCODE asm body matches the ROM byte-for-byte.
void blizzackNextMode(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0x02));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6402;
    *t = v;
    (p->s).mode[2] = z;
    PlaySound(0x42);
  }
  UpdateMotionGraphic(&p->s);
  if (*(u8*)((u8*)p + 0x73) == 3) {
    (p->s).mode[1] = *(u8*)((u8*)p + 0xf);
    (p->s).mode[2] = 1;
  }
}

void blizzackJump(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xB4, 0x03));
    ((p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6403;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).d.x = ((pZero2->s).coord.x - (p->s).coord.x) / 52;
    (p->s).d.y = -0x9C0;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x60;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  if (FUN_08009f6c((p->s).coord.x, (p->s).coord.y) < (p->s).coord.y) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 1;
  }
}

void CreateVFX57(struct Coord* c, u8 a1, u8 a2, s16 dx, s16 dy);

// 0x0805a2c4
void blizzackStamp(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    struct Entity* q;
    s32 z;
    SetMotion(&p->s, MOTION(0xB4, 0x04));
    ((p->s).unk_2c)->mode[2] = 1;
    q = (p->s).unk_2c;
    {
      register u16* hp asm("r0");
      register s32 hv asm("r1");
      hp = (u16*)((u8*)q + 0xbc);
      asm("" : "+r"(hp));
      z = 0;
      asm("" : "+r"(z) : "r"(hp));
      hv = 0x6404;
      *hp = hv;
    }
    (p->s).mode[2] = z;
    (p->s).work[2] = z;
    PlaySound(0x91);
    AppendQuake(4, &(p->s).coord);
  }
  UpdateMotionGraphic(&p->s);
  {
    register u8 w asm("r1");
    register s32 nx asm("r0");
    w = (p->s).work[2];
    nx = w + 1;
    asm("" : "+r"(nx));
    (p->s).work[2] = nx;
    if ((w & 7) == 0) {
      struct Coord* c = &(p->s).coord;
      CreateVFX57(c, 0, 1, 0x118, -((p->s).work[2] << 2) - 0x40);
      CreateVFX57(c, 0, 1, -0x118, -((p->s).work[2] << 2) - 0x40);
    }
  }
  {
    u8 st = (p->s).motion.state;
    if (st == 3) {
      (p->s).mode[1] = st;
      (p->s).mode[2] = 1;
    }
  }
}

static const struct Collision sCollisions[];

// 0x0805a368
void blizzackMode7(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    register s32 one asm("r5");
    register s32 v asm("r3");
    register struct Zero* z asm("r2");
    struct Entity* q;
    s32 zz;
    SetMotion(&p->s, MOTION(0xB4, 0x07));
    q = (p->s).unk_2c;
    one = 1;
    q->mode[2] = one;
    {
      register u16* hp asm("r0");
      register s32 hv asm("r1");
      hp = (u16*)((u8*)((p->s).unk_2c) + 0xbc);
      asm("" : "+r"(hp));
      zz = 0;
      asm("" : "+r"(zz) : "r"(hp));
      hv = 0x6407;
      *hp = hv;
    }
    (p->s).mode[2] = zz;
    v = 0;
    z = pZero2;
    if ((z->s).coord.x > (p->s).coord.x) {
      v = 1;
    }
    (p->s).spr.xflip = v;
    v = 0;
    if ((z->s).coord.x > (p->s).coord.x) {
      v = 1;
    }
    {
      register u8* oa asm("ip");
      register s32 fv asm("r1");
      u8* oa0;
      u32 k;
      s32 sh4, ov, m11;
      k = 0x4a;
      asm("" : "+r"(k));
      oa0 = (u8*)(k + (u32)p);
      oa = oa0;
      asm volatile("add %0, %1, #0" : "=&l"(fv) : "l"(one));
      fv &= v;
      sh4 = fv << 4;
      ov = *oa0;
      m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
      if (fv != 0) {
        (p->s).flags |= X_FLIP;
      } else {
        (p->s).flags &= ~X_FLIP;
      }
    }
    SetDDP(&p->body, &sCollisions[2]);
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 8;
    (p->s).mode[2] = 1;
  }
}

void FUN_080aabd4(struct Boss* p);

void blizzackMode8(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    (p->s).mode[2] = 0;
    (p->s).work[2] = 0xb4;
    FUN_080aabd4(p);
  }
  UpdateMotionGraphic(&p->s);
  if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 9;
    (p->s).mode[2] = 1;
  }
}

static const struct Collision sCollisions[4];
struct Entity* CreateEnemy42(struct Entity* e, u8 type, u8 param_3);
void FUN_080aac28(struct Entity* e);

// Same regmove tie as blizzackMode0: agbcc hoists the mode[2]=0 zero above
// the 0x64xx pool load, spilling the constant into r3 + copy.
void blizzackMode9(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0x08));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6408;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).work[2] = 8;
    SetDDP(&p->body, sCollisions);
  }
  UpdateMotionGraphic(&p->s);
  if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 1;
  }
}

void blizzackStartBlizzard(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0x09));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6409;
    *t = v;
    (p->s).mode[2] = z;
    SetDDP(&p->body, &sCollisions[2]);
  }
  UpdateMotionGraphic(&p->s);
  if (*(u8*)((u8*)p + 0x73) == 3) {
    (p->s).mode[1] = 0xb;
    (p->s).mode[2] = 1;
  }
}

void blizzackBlizzard(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    (p->s).mode[2] = 0;
    (p->s).work[2] = 0xb4;
    FUN_080aac28(&p->s);
    CreateEnemy42(&p->s, 1, ((p->s).flags >> 4) & 1);
    *(s16*)((u8*)p + 0xc8) = PlaySound(0x44);
  }
  UpdateMotionGraphic(&p->s);
  if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 0xc;
    (p->s).mode[2] = 1;
  }
}

void blizzackEndBlizzard(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0x08));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6408;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).work[2] = 8;
    StopSound(*(s16*)((u8*)p + 0xc8));
    SetDDP(&p->body, sCollisions);
  }
  UpdateMotionGraphic(&p->s);
  if ((u8)--(p->s).work[2] == 0xff) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 1;
  }
}

// 0x0805a5cc -- bomb-throw jump: aims at the stored target or Zero, random
// overshoot, then ballistic hop. Blocker (const-cluster placement): the r8
// zero's movs/mov pair clusters right after the r7 one-init in every source
// shape tried, while retail materializes it mid-statement after the unk_2c
// +0xbc address form; the 0x6403 pool load rides on it (r1 vs r2 + copy).
NON_MATCH void blizzackBombJump(struct Boss* p) {
#if MODERN
  if ((p->s).mode[2] != 0) {
    SetMotion(&p->s, 0xB403);
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    *(u16*)((u8*)(p->s).unk_2c + 0xbc) = 0x6403;
    (p->s).mode[2] = 0;
    {
      s32 tx = *(s32*)((u8*)p + 0xdc);
      s32 x = (p->s).coord.x;
      s32 d2 = tx - x;
      if (d2 > 0x7800) {
        (p->s).d.x = ((pZero2->s).coord.x - x) / 0x1A;
        (p->s).work[3] = 2;
      } else {
        s32 zx = (pZero2->s).coord.x;
        s32 d3 = zx - x;
        if (d3 > 0x5000) {
          (p->s).d.x = d3 / 0x34;
          (p->s).work[3] = 0;
        } else if (d2 <= 0xA000 && (RANDOM(RNG_0202f388) & 1)) {
          (p->s).d.x = d3 / 0x1A;
          (p->s).work[3] = 2;
        } else {
          (p->s).d.x = (x - zx) / 0x1A;
          (p->s).work[3] = 1;
        }
      }
    }
    (p->s).d.y = -0x9C0;
    (p->s).work[2] = 0x10;
    {
      u32 xf = 0;
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        xf = 1;
      }
      ((p->s).spr).xflip = xf;
      *((u8*)p + 0x4a) = (*((u8*)p + 0x4a) & ~0x11) | (xf << 4);
      if (xf != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
    }
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x60;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  {
    s32 t = (p->s).work[2] - 1;
    (p->s).work[2] = t;
    if ((u8)t == 0xFF) {
      (p->s).mode[1] = 0xE;
      (p->s).mode[2] = 1;
    }
  }
#else
  INCCODE("asm/boss/blizzack_bombjump.inc");
#endif
}

INCASM("asm/boss/blizzack_post_p2_a.inc");

// Same regmove tie as blizzackMode0: the mode[2]=0 zero and the 0x64xx pool
// load fight for the same slot, spilling the constant through r3.
void blizzackBombFall(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xb4, 0x03));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6403;
    *t = v;
    (p->s).mode[2] = z;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x60;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  if (FUN_08009f6c((p->s).coord.x, (p->s).coord.y) < (p->s).coord.y) {
    (p->s).mode[1] = 0x10;
    (p->s).mode[2] = 1;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  }
}

INCASM("asm/boss/blizzack_post_p2_a2.inc");

struct Projectile* FUN_080aa7a8(struct Entity* e, u8 a, u8 b);

// 0x0805AA44
void blizzackMode17(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xB4, 0x05));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6405;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).work[2] = 0x18;
  }
  UpdateMotionGraphic(&p->s);
  if ((p->s).work[2] == 0xC) {
    if ((p->s).coord.y - 0x4000 > pZero2->s.coord.y) {
      FUN_080aa7a8(&p->s, 1, 4);
      FUN_080aa7a8(&p->s, 1, 5);
      FUN_080aa7a8(&p->s, 1, 6);
      FUN_080aa7a8(&p->s, 1, 7);
    } else {
      FUN_080aa7a8(&p->s, 1, 0);
      FUN_080aa7a8(&p->s, 1, 1);
      FUN_080aa7a8(&p->s, 1, 2);
      FUN_080aa7a8(&p->s, 1, 3);
    }
  }
  if (--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 0x12;
    (p->s).mode[2] = 1;
  }
}

void blizzackMode18(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xB4, 0x06));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x6406;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).work[2] = 8;
  }
  UpdateMotionGraphic(&p->s);
  if (--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/boss/blizzack_post_p2_a2b.inc");

// 0x0805AB5C
void blizzackMode19(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    s32 v;
    register u8 z asm("r2");
    SetMotion(&p->s, MOTION(0xB4, 0x0B));
    ((p->s).unk_2c)->mode[2] = 1;
    {
      register u16* h asm("r0");
      register s32 hv asm("r1");
      h = (u16*)((u8*)(p->s).unk_2c + 0xbc);
      z = 0;
      asm("" : "+r"(z));
      hv = 0x640B;
      *h = hv;
    }
    (p->s).mode[2] = z;
    v = 0x100;
    (p->s).d.x = v;
    (p->s).d.y = -0x300;
    if (*(u8*)((u8*)p + 0xc4) != 0) {
      (p->s).d.x = -v;
    }
    SetDDP(&p->body, &sCollisions[0]);
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 dy;
    (p->s).coord.y += (p->s).d.y;
    dy = (p->s).d.y + 0x60;
    (p->s).d.y = dy;
    if (dy > 0x700) {
      (p->s).d.y = 0x700;
    }
  }
  if (FUN_08009f6c((p->s).coord.x, (p->s).coord.y) < (p->s).coord.y) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    if (*(s32*)((u8*)p + 0xd4) == 0) {
      (p->s).mode[1] = 0x14;
      (p->s).mode[2] = 1;
    }
  } else {
    (p->s).coord.x += (p->s).d.x;
  }
}

void blizzackMode20(struct Boss* p) {
  if ((p->s).mode[2] != 0) {
    u16* t;
    register s32 z asm("r2");
    register s32 v asm("r1");
    SetMotion(&p->s, MOTION(0xB4, 0x0E));
    ((struct Entity*)(p->s).unk_2c)->mode[2] = 1;
    t = (u16*)((u8*)(p->s).unk_2c + 0xbc);
    z = 0;
    v = 0x640D;
    *t = v;
    (p->s).mode[2] = z;
    (p->s).work[2] = 8;
  }
  UpdateMotionGraphic(&p->s);
  if (--(p->s).work[2] == 0xFF) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 1;
  }
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);

// 0x0805AC5C
void blizzack_0805ac5c(struct Boss* p) {
  register s32 one asm("r5");
  s32 nm;
  register s32 z2 asm("r2");
  u8* fp;
  u32* st;
  struct Coord c;
  {
    struct StageRun* sr = &gStageRun;
    u16 ms = sr->missionStatus;
    s32 t;
    one = 1;
    asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
    t &= ms;
    if (t != 0) {
      u8 av = sr->vm.active;
      s32 t2;
      asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(one));
      t2 &= av;
      if (t2 == 0) {
        register s32 mk asm("r0");
        register s32 k10 asm("r1");
        mk = 0xFFFE;
        mk &= ms;
        k10 = 0x10;
        mk |= k10;
        sr->missionStatus = mk;
      }
    }
  }
  StopSound(*(s16*)((u8*)p + 0xc8));
  (p->s).mode[2] = 0;
  (p->s).work[2] = 0;
  {
    s32 onR = 0;
    if ((pZero2->s).coord.x > (p->s).coord.x) {
      onR = 1;
    }
    fp = (u8*)p + 0xc4;
    *fp = onR;
  }
  SetMotion(&p->s, 0xB40B);
  UpdateMotionGraphic(&p->s);
  {
    u32* st0 = (u32*)((u8*)p + 0x8c);
    u32 sv = *st0 & 0x10000;
    asm volatile("add %0, %1, #0" : "=&l"(st) : "l"(st0));
    if (sv != 0) {
    c.x = (p->s).coord.x;
    c.y = (p->s).coord.y - 0x1C00;
    FUN_080b2b40(0, &c, 0x200, *fp);
      nm = 2;
    } else {
      nm = 1;
    }
  }
  (p->s).mode[1] = nm;
  z2 = 0;
  asm("" : "+r"(z2));
  (p->s).mode[2] = 1;
  ((p->s).unk_2c)->mode[3] = 1;
  *st = z2;
  *(u32*)((u8*)p + 0x90) = z2;
  *(u8*)((u8*)p + 0x94) = z2;
  (p->s).flags &= 0xFB;
}

struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);

// 0x0805AD2C
void blizzack_0805ad2c(struct Boss* p) {
  struct Coord c;
  if ((p->s).mode[2] != 0) {
    u8 z;
    SetMotion(&p->s, MOTION(0xB4, 0x0B));
    z = 0;
    (p->s).d.y = z;
    (p->s).work[2] = z;
    (p->s).mode[2] = z;
    (p->s).mode[3] = z;
  }
  UpdateMotionGraphic(&p->s);
  switch ((p->s).mode[3]) {
    case 0:
      if (((p->s).scriptEntity->flags & 0x80) == 0) {
        return;
      }
      c.x = 0x600;
      c.y = -0x1800;
      (p->s).unk_2c = CreateBossExplosion(&p->s, &c);
      break;
    case 1:
      if (((p->s).unk_2c)->mode[0] <= 1) {
        return;
      }
      gStageRun.vm.active |= 2;
      (p->s).work[2] = 0x20;
      break;
    case 2:
      if ((u8)--(p->s).work[2] != 0xFF) {
        return;
      }
      {
        register u8 t asm("r0");
        register u8 fv asm("r1");
        t = (p->s).flags;
        fv = 0xFE;
        fv &= t;
        (p->s).flags = fv;
        asm volatile("" :: "r"(t));
      }
      break;
    default:
      return;
  }
  (p->s).mode[3]++;
}

struct Entity* CreateBossExplosion(struct Entity* boss, struct Coord* c);

// 0x0805ADD0
void blizzack_0805add0(struct Boss* p) {
  struct Coord c;
  if ((p->s).mode[2] != 0) {
    u8* q;
    register u32 one asm("r2");
    register u8 fl asm("r1");
    u32 z;
    SetMotion(&p->s, MOTION(0xB4, 0x0C));
    q = (u8*)p + 0xc4;
    {
      u8 qv = *q;
      u32 v;
      one = 1;
      asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(one));
      v &= qv;
      ((p->s).spr).xflip = v;
    }
    {
      register u8* oa asm("ip");
      u8 qv = *q;
      u32 v;
      oa = (u8*)p + 0x4a;
      asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(one));
      v &= qv;
      {
        u32 sh4 = v << 4;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
    }
    one &= *q;
    if (one != 0) {
      (p->s).flags |= 0x10;
    } else {
      (p->s).flags &= 0xEF;
    }
    fl = (p->s).flags;
    if ((0x10 & fl) != 0) {
      (p->s).d.x = 0x20;
      (p->s).unk_coord.x = -1;
    } else {
      (p->s).d.x = -0x20;
      (p->s).unk_coord.x = 1;
    }
    z = 0;
    (p->s).work[2] = 0x20;
    (p->s).mode[2] = z;
    (p->s).mode[3] = z;
    CreateEnemy42(&p->s, 2, (((u32)fl << 24) >> 28) & 1);
    (p->s).unk_2c = (struct Entity*)z;
    PlaySound(0x2F);
  }
  UpdateMotionGraphic(&p->s);
  switch ((p->s).mode[3]) {
    case 0:
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.x += (p->s).unk_coord.x;
      if ((u8)--(p->s).work[2] != 0xFF) {
        break;
      }
      goto next;
    case 1:
      if ((((p->s).scriptEntity)->flags & 0x80) == 0) {
        break;
      }
      c.x = 0xE00;
      c.y = -0x1800;
      (p->s).unk_2c = CreateBossExplosion(&p->s, &c);
      goto next;
    case 2:
      if (((p->s).unk_2c)->mode[0] <= 1) {
        break;
      }
      gStageRun.vm.active |= VM_FLAG1;
      (p->s).work[2] = 0x20;
      goto next;
    case 3:
      if ((u8)--(p->s).work[2] != 0xFF) {
        break;
      }
      {
        register u8 t asm("r0");
        register u8 fv asm("r1");
        t = (p->s).flags;
        fv = (u8)~DISPLAY;
        fv &= t;
        (p->s).flags = fv;
        asm volatile("" :: "r"(t));
      }
    next:
      (p->s).mode[3]++;
      break;
  }
}

void FUN_0805af14(struct Boss* p) {
  if ((p->s).coord.x < *(s32*)((u8*)p + 0xb4) + 0x2000 ||
      (p->s).coord.x > *(s32*)((u8*)p + 0xd8) - 0x2000) {
    (p->s).coord.x = *(s32*)((u8*)p + 0xc0);
  }
  *(s32*)((u8*)p + 0xc0) = (p->s).coord.x;
}

void blizzackMode0(struct Boss* p);
void blizzackMode1(struct Boss* p);
void blizzackNeutral(struct Boss* p);
void blizzackPreAI(struct Boss* p);
void blizzackNextMode(struct Boss* p);
void blizzackJump(struct Boss* p);
void blizzackStamp(struct Boss* p);
void blizzackMode7(struct Boss* p);
void blizzackMode8(struct Boss* p);
void blizzackMode9(struct Boss* p);
void blizzackStartBlizzard(struct Boss* p);
void blizzackBlizzard(struct Boss* p);
void blizzackEndBlizzard(struct Boss* p);
void blizzackBombJump(struct Boss* p);
void blizzackBomb(struct Boss* p);
void blizzackBombFall(struct Boss* p);
void blizzackBombStamp(struct Boss* p);
void blizzackMode17(struct Boss* p);
void blizzackMode18(struct Boss* p);
void blizzackMode19(struct Boss* p);
void blizzackMode20(struct Boss* p);

// clang-format off
// 0x08364b50
static const BossFunc sUpdates[21] = {
    (BossFunc)blizzackMode0,
    (BossFunc)blizzackMode1,
    (BossFunc)blizzackNeutral,
    (BossFunc)blizzackPreAI,
    (BossFunc)blizzackNextMode,
    (BossFunc)blizzackJump,
    (BossFunc)blizzackStamp,
    (BossFunc)blizzackMode7,
    (BossFunc)blizzackMode8,
    (BossFunc)blizzackMode9,
    (BossFunc)blizzackStartBlizzard,
    (BossFunc)blizzackBlizzard,
    (BossFunc)blizzackEndBlizzard,
    (BossFunc)blizzackBombJump,
    (BossFunc)blizzackBomb,
    (BossFunc)blizzackBombFall,
    (BossFunc)blizzackBombStamp,
    (BossFunc)blizzackMode17,
    (BossFunc)blizzackMode18,
    (BossFunc)blizzackMode19,
    (BossFunc)blizzackMode20,
};
// clang-format on

// --------------------------------------------

void blizzack_0805ac5c(struct Boss* p);
void blizzack_0805ad2c(struct Boss* p);
void blizzack_0805add0(struct Boss* p);

static const BossFunc sDeads[3] = {
    (BossFunc)blizzack_0805ac5c,
    (BossFunc)blizzack_0805ad2c,
    (BossFunc)blizzack_0805add0,
};

// --------------------------------------------

// 0x08364bb0
static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      hitzone : 8,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(24), PIXEL(34), PIXEL(48)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 8,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(24), PIXEL(34), PIXEL(48)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      hitzone : 8,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(24), PIXEL(50), PIXEL(48)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 8,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(24), PIXEL(50), PIXEL(48)},
    },
};

// 0x08364c10
static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(24)};
