#include "collision.h"
#include "enemy.h"
#include "zero.h"
#include "global.h"
#include "metatile.h"
#include "overworld_terrain.h"
#include "story.h"
#include "mission.h"
#include "vfx.h"

struct GyroCannon {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct {
    struct VFX* elementEffect;  // 0xB4
    u8 unk_b8[4];               // 0xB8
    bool8 is_right;             // 0xBC
    u32 unk_c0;                 // 0xC0
  } props;
};
static_assert(sizeof(struct GyroCannon) == sizeof(struct Enemy));

static const struct Collision sCollisions[];

static void GyroCannon_Init(struct Enemy* p);
static void GyroCannon_Update(struct Enemy* p);
static void GyroCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gGyroCannonRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)GyroCannon_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)GyroCannon_Update,
    [ENTITY_DIE] =       (EnemyFunc)GyroCannon_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static struct Entity* CreateGyroCannon(struct Entity* e, u8 n, u8 r2) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_GYRO_CANNON);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = e;
    p->work[0] = n, p->work[1] = r2;
  }
  return p;
}

// --------------------------------------------

static void initGyroCannonWithPropeller(struct Enemy* p);
static void initGyroCannonWithoutPropeller(struct GyroCannon* p);

static void GyroCannon_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] != 0) {
    initGyroCannonWithoutPropeller((void*)p);
  } else {
    initGyroCannonWithPropeller(p);
  }
  GyroCannon_Update(p);
}

// --------------------------------------------

void gyrocannon_0806d32c(struct Enemy* p);
static void gyrocannon_0806d1b4(struct Enemy* p);

static void GyroCannon_Update(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  if ((p->s).work[0] != 0) {
    gyrocannon_0806d32c(p);
  } else {
    gyrocannon_0806d1b4(p);
  }
}

// --------------------------------------------

void FUN_0806d524(struct Enemy* p);
void FUN_0806d470(struct Enemy* p);

static void GyroCannon_Die(struct Enemy* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  if ((p->s).work[0] != 0) {
    FUN_0806d524(p);
  } else {
    FUN_0806d470(p);
  }
}

// --------------------------------------------

NAKED static void initGyroCannonWithPropeller(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r6, r0, #0\n\
	movs r1, #0xb8\n\
	lsls r1, r1, #5\n\
	bl SetMotion\n\
	adds r0, r6, #0\n\
	bl UpdateMotionGraphic\n\
	ldr r0, _0806D0F0 @ =gSystemSavedataManager\n\
	ldrb r1, [r0, #0x16]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _0806D0FC\n\
	ldr r0, _0806D0F4 @ =gCurStory\n\
	ldrb r1, [r0, #4]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	lsls r0, r0, #0x18\n\
	lsrs r5, r0, #0x18\n\
	cmp r5, #0\n\
	bne _0806D0FC\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #4\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0806D0F8 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0x14\n\
	b _0806D114\n\
	.align 2, 0\n\
_0806D0F0: .4byte gSystemSavedataManager\n\
_0806D0F4: .4byte gCurStory\n\
_0806D0F8: .4byte sCollisions\n\
_0806D0FC:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #4\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0806D14C @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0x10\n\
_0806D114:\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	str r5, [r4, #0x24]\n\
	ldr r0, _0806D150 @ =FUN_0806df10\n\
	str r0, [r4, #0x24]\n\
	adds r0, r6, #0\n\
	movs r1, #1\n\
	movs r2, #0\n\
	bl CreateGyroCannon\n\
	str r0, [r6, #0x2c]\n\
	adds r2, r6, #0\n\
	adds r2, #0xb4\n\
	movs r1, #0\n\
	strb r1, [r2, #9]\n\
	ldr r0, [r6, #0x58]\n\
	str r0, [r2, #4]\n\
	strb r1, [r2, #0xa]\n\
	strb r1, [r2, #0xb]\n\
	str r1, [r6, #0x60]\n\
	strb r1, [r6, #0x13]\n\
	str r1, [r2]\n\
	movs r0, #2\n\
	strb r0, [r6, #0xd]\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0806D14C: .4byte sCollisions\n\
_0806D150: .4byte FUN_0806df10\n\
 .syntax divided\n");
}

static void initGyroCannonWithoutPropeller(struct GyroCannon* p) {
  SetMotion(&p->s, MOTION(SM023_GYRO_CANNON, 6));
  UpdateMotionGraphic(&p->s);
  INIT_BODY(p, &sCollisions[2], 6, NULL);

  (p->s).flags &= ~X_FLIP;
  (p->s).spr.xflip = FALSE;
  (p->s).spr.oam.xflip = FALSE;

  (p->props).elementEffect = NULL;
}

static const struct Coord sElementCoord;
static const EnemyFunc PTR_ARRAY_0836666c[10];

NAKED static void gyrocannon_0806d1b4(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r4, r0, #0\n\
	ldr r0, [r4, #0x54]\n\
	ldr r1, [r4, #0x58]\n\
	ldr r2, _0806D204 @ =0xFFFFE800\n\
	adds r1, r1, r2\n\
	bl IsVoidSpace\n\
	lsls r0, r0, #0x18\n\
	lsrs r2, r0, #0x18\n\
	cmp r2, #0\n\
	beq _0806D20C\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r2, #0\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r4, #0xa]\n\
	adds r0, r4, #0\n\
	adds r0, #0x8c\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r4, #0xa]\n\
	ldr r1, _0806D208 @ =gEnemyFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	str r0, [r4, #0x14]\n\
	b _0806D31C\n\
	.align 2, 0\n\
_0806D204: .4byte 0xFFFFE800\n\
_0806D208: .4byte gEnemyFnTable\n\
_0806D20C:\n\
	ldrb r0, [r4, #0xd]\n\
	adds r1, r0, #0\n\
	cmp r1, #1\n\
	beq _0806D246\n\
	ldr r0, [r4, #0x2c]\n\
	cmp r0, #0\n\
	beq _0806D222\n\
	ldrb r0, [r0, #0xc]\n\
	cmp r0, #1\n\
	bls _0806D222\n\
	str r2, [r4, #0x2c]\n\
_0806D222:\n\
	lsls r0, r1, #0x18\n\
	lsrs r0, r0, #0x18\n\
	cmp r0, #1\n\
	beq _0806D246\n\
	adds r3, r4, #0\n\
	adds r3, #0x8c\n\
	ldr r0, [r3]\n\
	ldr r1, _0806D250 @ =0x00020001\n\
	ands r0, r1\n\
	cmp r0, r1\n\
	bne _0806D240\n\
	movs r1, #0\n\
	movs r0, #1\n\
	strb r0, [r4, #0xd]\n\
	strb r1, [r4, #0xe]\n\
_0806D240:\n\
	ldrb r2, [r4, #0xd]\n\
	cmp r2, #1\n\
	bne _0806D254\n\
_0806D246:\n\
	adds r0, r4, #0\n\
	bl FUN_0806d684\n\
	b _0806D31C\n\
	.align 2, 0\n\
_0806D250: .4byte 0x00020001\n\
_0806D254:\n\
	ldr r1, [r3]\n\
	movs r0, #0x80\n\
	lsls r0, r0, #2\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _0806D280\n\
	ldr r1, _0806D27C @ =gEnemyFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #2\n\
	str r1, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r4, #0x14]\n\
	adds r0, r4, #0\n\
	bl GyroCannon_Die\n\
	b _0806D31C\n\
	.align 2, 0\n\
_0806D27C: .4byte gEnemyFnTable\n\
_0806D280:\n\
	adds r5, r4, #0\n\
	adds r5, #0xb4\n\
	cmp r2, #8\n\
	beq _0806D2AC\n\
	movs r0, #1\n\
	ands r1, r0\n\
	cmp r1, #0\n\
	beq _0806D2AC\n\
	ldr r6, [r5]\n\
	cmp r6, #0\n\
	bne _0806D2B2\n\
	ldr r2, _0806D2D0 @ =0x083666A0\n\
	movs r0, #0\n\
	adds r1, r4, #0\n\
	bl ApplyElementEffect\n\
	str r0, [r5]\n\
	cmp r0, #0\n\
	beq _0806D2DC\n\
	movs r0, #8\n\
	strb r0, [r4, #0xd]\n\
	strb r6, [r4, #0xe]\n\
_0806D2AC:\n\
	ldr r0, [r5]\n\
	cmp r0, #0\n\
	beq _0806D2DC\n\
_0806D2B2:\n\
	ldr r1, _0806D2D4 @ =0x0836666C\n\
	ldrb r0, [r4, #0xd]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	ldr r1, [r0]\n\
	adds r0, r4, #0\n\
	bl _call_via_r1\n\
	adds r0, r4, #0\n\
	adds r0, #0x74\n\
	ldr r1, _0806D2D8 @ =0x083666C0\n\
	bl SetDDP\n\
	b _0806D31C\n\
	.align 2, 0\n\
_0806D2D0: .4byte sElementCoord\n\
_0806D2D4: .4byte PTR_ARRAY_0836666c\n\
_0806D2D8: .4byte sCollisions+(24*1)\n\
_0806D2DC:\n\
	adds r0, r4, #0\n\
	adds r0, #0x74\n\
	ldr r1, _0806D324 @ =sCollisions\n\
	bl SetDDP\n\
	adds r0, r4, #0\n\
	bl IsFrozen\n\
	cmp r0, #0\n\
	bne _0806D31C\n\
	ldrb r0, [r5, #0xb]\n\
	cmp r0, #0\n\
	bne _0806D306\n\
	ldrb r0, [r4, #0xd]\n\
	cmp r0, #0\n\
	beq _0806D306\n\
	ldr r0, [r4, #0x2c]\n\
	cmp r0, #0\n\
	bne _0806D306\n\
	strb r0, [r4, #0xd]\n\
	strb r0, [r4, #0xe]\n\
_0806D306:\n\
	ldr r0, _0806D328 @ =0x0836666C\n\
	ldrb r1, [r4, #0xd]\n\
	lsls r1, r1, #2\n\
	adds r1, r1, r0\n\
	ldr r1, [r1]\n\
	adds r0, r4, #0\n\
	bl _call_via_r1\n\
	adds r0, r4, #0\n\
	bl UpdateMotionGraphic\n\
_0806D31C:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0806D324: .4byte sCollisions\n\
_0806D328: .4byte PTR_ARRAY_0836666c\n\
 .syntax divided\n");
}

void GyroCannon_Die(struct Enemy* p);

void gyrocannon_0806d32c(struct Enemy* p) {
  struct Entity* par = (p->s).unk_28;
  if ((p->body).status & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    GyroCannon_Die(p);
    return;
  }
  if ((p->s).mode[1] == 0) {
    register u32 f asm("r0");
    s32 zv;
    if (par->mode[1] != 8) {
      SetDDP(&p->body, &sCollisions[2]);
      if (!IsFrozen(par)) {
        UpdateMotionGraphic(&p->s);
      }
    } else {
      SetDDP(&p->body, &sCollisions[3]);
    }
    (p->s).coord.x = par->coord.x;
    (p->s).coord.y = par->coord.y;
    if (par->mode[0] > 1) {
      u8* pb = (u8*)par + 0xb4;
      s32 p9 = pb[9];
      if (p9 == 0) {
        register s32 flg asm("r1");
        register s32 cfe asm("r0");
        asm("" : "+r"(p9));
        flg = (p->s).flags;
        cfe = 0xFE;
        asm("" : "+r"(cfe));
        f = cfe & flg;
        zv = p9;
        goto ta;
      }
      (p->s).work[2] = 0x40;
      (p->s).mode[1]++;
    }
    if (IsVoidSpace(par->coord.x, par->coord.y + -0x1800)) {
      register s32 flg2 asm("r1");
      register s32 cfe2 asm("r0");
      flg2 = (p->s).flags;
      cfe2 = 0xFE;
      asm("" : "+r"(cfe2));
      f = cfe2 & flg2;
      zv = 0;
      asm("" : "+r"(zv));
    ta:
      asm("" : "+r"(f));
      f &= 0xFD;
      (p->s).flags = f;
      (p->body).status = zv;
      (p->body).prevStatus = zv;
      (p->body).invincibleTime = zv;
      (p->s).flags &= 0xFB;
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  } else {
    s32 oy;
    UpdateMotionGraphic(&p->s);
    oy = (p->s).coord.y;
    (p->s).coord.y = oy + -0x200;
    {
      s32 raw = (p->s).work[2] - 1;
      (p->s).work[2] = raw;
      if ((u8)raw == 0xFF) {
        goto die2;
      }
    }
    if (FUN_080098a4((p->s).coord.x, oy + -0xE00) != 0) {
    die2:
      SET_ENEMY_ROUTINE(p, ENTITY_DIE);
      GyroCannon_Die(p);
    }
  }
}

void FUN_080b2b40(u8 kind, struct Coord* c, s32 v, u8 n);
static const EnemyFunc sUpdates2[3];

// 0x0806D470
void FUN_0806d470(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    u8* b0 = (u8*)p + 0xb4;
    u8 v = b0[0xa];
    u8* b;
    asm volatile("add %0, %1, #0" : "=&l"(b) : "l"(b0));
    if (v != 0) {
      (p->s).mode[1] = 0;
    } else if (((p->body).status & 0x10000) != 0) {
      struct Coord c;
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y - 0x1400;
      FUN_080b2b40(0, &c, 0x200, b[8]);
      if ((p->s).unk_2c != NULL) {
        (p->s).mode[1] = 1;
      } else if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0xB00) != 0) {
        (p->s).mode[1] = 2;
      } else {
        (p->s).mode[1] = 0;
      }
    } else {
      (p->s).mode[1] = 0;
    }
    EXIT_BODY(p);
    b[9] = 1;
    (p->s).mode[2]++;
  }
  (sUpdates2[(p->s).mode[1]])(p);
}

extern const struct SlashedEnemy sSlashedEnemies[4];

// 0x0806D524
void FUN_0806d524(struct Enemy* p) {
  struct Coord c;
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - 0x1200;
  CreateSmoke(2, &c);
  if (!((bool16 (*)(s32, s32))FUN_080098a4)(c.x, c.y)) {
    const struct SlashedEnemy* t0;
    register u8* b4 asm("r6");
    t0 = sSlashedEnemies;
    {
      register u8* b40 asm("r2");
      register s32 pal asm("r5");
      register s32 k asm("r3");
      register s32 kk asm("r0");
      register u8 fl asm("r1");
      b40 = (u8*)p + 0xb4;
      pal = b40[8];
      fl = (p->s).flags;
      k = 0x10;
      kk = k;
      kk &= fl;
      asm volatile("add %0, %1, #0" : "=&l"(b4) : "l"(b40));
      if (kk != 0) {
        k |= pal;
      } else {
        k = pal;
      }
      ((struct VFX* (*)())CreateSlashedEnemy)(&c, t0, 0, k);
    }
    {
      register struct Coord* cp asm("r5");
      const struct SlashedEnemy* t1;
      register s32 pal2 asm("r2");
      register s32 k2 asm("r3");
      register s32 kk2 asm("r0");
      register u8 fl2 asm("r1");
      cp = &c;
      t1 = sSlashedEnemies;
      pal2 = b4[8];
      fl2 = (p->s).flags;
      k2 = 0x10;
      kk2 = k2;
      kk2 &= fl2;
      if (kk2 != 0) {
        k2 |= pal2;
      } else {
        k2 = pal2;
      }
      ((struct VFX* (*)())CreateSlashedEnemy)(cp, t1, 0, k2);
    }
    {
      register struct Coord* cp2 asm("r5");
      const struct SlashedEnemy* t2;
      register s32 pal3 asm("r2");
      register s32 k3 asm("r3");
      register s32 kk3 asm("r0");
      register u8 fl3 asm("r1");
      cp2 = &c;
      t2 = &sSlashedEnemies[1];
      pal3 = b4[8];
      fl3 = (p->s).flags;
      k3 = 0x10;
      kk3 = k3;
      kk3 &= fl3;
      if (kk3 != 0) {
        k3 |= pal3;
      } else {
        k3 = pal3;
      }
      ((struct VFX* (*)())CreateSlashedEnemy)(cp2, t2, 0, k3);
    }
    {
      register struct Coord* cp3 asm("r5");
      const struct SlashedEnemy* t3;
      register s32 pal4 asm("r2");
      register s32 k4 asm("r3");
      register s32 kk4 asm("r0");
      register u8 fl4 asm("r1");
      cp3 = &c;
      t3 = &sSlashedEnemies[1];
      pal4 = b4[8];
      fl4 = (p->s).flags;
      k4 = 0x10;
      kk4 = k4;
      kk4 &= fl4;
      if (kk4 != 0) {
        k4 |= pal4;
      } else {
        k4 = pal4;
      }
      ((struct VFX* (*)())CreateSlashedEnemy)(cp3, t3, 0, k4);
    }
  }
  PlaySound(0x2A);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

// 0x0806d618
void FUN_0806d618(struct Enemy* p) {
  register struct Enemy* pp asm("r4");
  register s32 m asm("r5");
  s32 v;
  s32 y;
  pp = p;
  m = (pp->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, MOTION(0x17, 0x00));
    (pp->s).d.y = m;
    (pp->s).mode[2]++;
  }
  v = (pp->s).d.y + 0x40;
  (pp->s).d.y = v;
  if (v > 0x700) {
    (pp->s).d.y = 0x700;
  }
  y = (pp->s).coord.y + (pp->s).d.y;
  (pp->s).coord.y = y;
  if ((u16)FUN_080098a4((pp->s).coord.x, y + 0xA00) != 0) {
    s32 z;
    (pp->s).coord.y = FUN_08009f6c((pp->s).coord.x, (pp->s).coord.y) - 0xA00;
    z = 0;
    (pp->s).mode[1] = 7;
    (pp->s).mode[2] = z;
    {
      register u8* pr asm("r1");
      register s32 one asm("r0");
      pr = pp->props;
      asm("" : "+r"(pr));
      one = 1;
      pr[11] = one;
    }
    asm volatile("" ::"r"(pp));
  }
}


INCASM("asm/enemy/gyro_cannon_p1b_b.inc");

// 0x0806D7E0
void FUN_0806d7e0(struct Enemy* p) {
  s32 onR;
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1700);
    (p->s).work[2] = 0x78;
    (p->s).mode[2]++;
  }
  onR = 0;
  if ((p->s).coord.x < (pZero2->s).coord.x) {
    onR = 1;
  }
  if (onR != 0) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= 0xEF;
  }
  {
    register s32 xfc asm("r1");
    xfc = onR;
    asm("" : "+r"(xfc));
    ((p->s).spr).xflip = xfc;
  {
    u8* oa = (u8*)p + 0x4a;
    s32 sh = xfc << 4;
    s32 ov = *oa;
    s32 m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh;
  }
  }
  {
    s32* bp = (s32*)((u8*)p + 0xb4);
    (p->s).coord.y = bp[1] + (gSineTable[(p->s).work[3]] << 5);
  }
  (p->s).work[3]++;
  {
    s32 raw = (p->s).work[2] - 1;
    (p->s).work[2] = raw;
    if ((u8)raw == 0xFF) {
      register u8 nm asm("r0");
      u32 rv = RANDOM(RNG_0202f388) & 0xF;
      asm("" : "+r"(rv));
      if (rv <= 9) {
        nm = 3;
        asm("" : "+r"(nm));
        goto setm;
      }
      nm = 5;
      asm("" : "+r"(nm));
    setm:
      (p->s).mode[1] = nm;
      {
        register u8 zz asm("r0");
        zz = 0;
        (p->s).mode[2] = zz;
      }
    }
  }
}

struct Projectile* CreateLemon(struct Coord* c, s32 r1, u8 r2);

// 0x0806D8B0
void FUN_0806d8b0(struct Enemy* p) {
  struct Coord c;
  register struct Entity* q asm("r4");
  if ((p->s).mode[2] == 0) {
    register s32 sp asm("r4");
    SetMotion(&p->s, MOTION(0x17, 0x03));
    c.y = (p->s).coord.y + 0x800;
    if ((p->s).flags & X_FLIP) {
      c.x = (p->s).coord.x + 0x1000;
      sp = 0x180;
      CreateLemon(&c, sp, 0x90);
      c.y = (p->s).coord.y - 0x500;
      CreateLemon(&c, sp, 0x70);
    } else {
      c.x = (p->s).coord.x - 0x1000;
      sp = 0x180;
      CreateLemon(&c, sp, 0xEF);
      c.y = (p->s).coord.y - 0x500;
      CreateLemon(&c, sp, 0x10);
    }
    PlaySound(0x2C);
    (p->s).work[2] = 0x30;
    (p->s).mode[2]++;
  }
  q = (p->s).unk_2c;
  if (q == NULL) {
    if (((bool16 (*)(s32, s32))FUN_080098a4)((p->s).coord.x, (p->s).coord.y + 0xA00)) {
      (p->s).mode[1] = (u8)(u32)q;
      (p->s).mode[2] = (u8)(u32)q;
      return;
    }
  }
  {
    s32 t = (p->s).work[2] - 1;
    (p->s).work[2] = t;
    t <<= 24;
    t = (u32)t >> 24;
    if (t == 0xFF) {
      register struct Entity* r asm("r1");
      r = (p->s).unk_2c;
      if (r != NULL) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
        return;
      }
      (p->s).mode[1] = 7;
      (p->s).mode[2] = (u8)(u32)r;
    }
  }
}

void FUN_0806d998(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1700);
    (p->s).work[2] = 8;
    (p->s).mode[2]++;
  }
  if ((u8)(--(p->s).work[2]) == 0xff) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

void CreateProjectile8(s32 x, s32 y);

void FUN_0806d9d4(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1704);
    (p->s).work[2] = 8;
    (p->s).mode[2]++;
  }
  if ((u8)(--(p->s).work[2]) == 0xff) {
    CreateProjectile8((p->s).coord.x, (p->s).coord.y + 0xc00);
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

void FUN_0806da20(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, 0x1705);
    (p->s).work[2] = 8;
    (p->s).mode[2]++;
  }
  if ((u8)(--(p->s).work[2]) == 0xff) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/gyro_cannon_p3a.inc");

// 0x0806DA5C
void FUN_0806da5c(struct Enemy* p) {
  u8 z;
  if ((p->s).mode[2] == 0) {
    SetMotion(&p->s, MOTION(0x17, 0x00));
    (p->s).work[2] = 0x78;
    (p->s).mode[2]++;
  }
  {
    register u8* q asm("r1");
    q = (u8*)p + 0xb4;
    asm("" : "+r"(q));
    z = 0;
    q[0xb] = 1;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0xB00) == 0) {
    (p->s).mode[1] = z;
  } else {
    if ((u8)--(p->s).work[2] != 0xFF) {
      return;
    }
    (p->s).mode[1] = 3;
  }
  (p->s).mode[2] = z;
}

// 0x0806DAB8
void FUN_0806dab8(struct Enemy* p) {
  struct Entity** slot;
  u8 m = (p->s).mode[2];
  if (m == 0) {
    SetMotion(&p->s, MOTION(0x17, 0x00));
    SetDDP(&p->body, &sCollisions[1]);
    (p->s).d.y = m;
    (p->s).mode[2]++;
  }
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  (p->s).coord.y += (p->s).d.y;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0xA00)) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - 0xA00;
  }
  slot = (struct Entity**)((u8*)p + 0xb4);
  if (isKilled(*slot)) {
    u32 z = 0;
    *slot = (struct Entity*)z;
    SetDDP(&p->body, &sCollisions[0]);
    if ((p->s).unk_2c != NULL) {
      (p->s).mode[1] = 9;
      (p->s).mode[2] = z;
    } else {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 1;
    }
  }
}

void FUN_0806db58(struct Enemy* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.y -= 0x200;
  {
    s32* base = (s32*)((u8*)p + 0xb4);
    if ((p->s).coord.y < base[1]) {
      (p->s).coord.y = base[1];
      (p->s).mode[1] = 2;
      (p->s).mode[2] = 0;
      (p->s).work[3] = 0x7f;
    }
  }
}

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
extern const struct SlashedEnemy sSlashedEnemies[4];

void gyroCannon_0806db8c(struct Enemy* p) {
  register u32 a3 asm("r3");
  register struct Coord* c5 asm("r5");
  register u8* pr8 asm("r8");
  c5 = &(p->s).coord;
  {
    register const struct SlashedEnemy* s6 asm("r6");
    register s32 pv asm("r2");
    s6 = &sSlashedEnemies[2];
    {
      register u8* pt asm("r0");
      pt = (u8*)p + 0xb4;
      pv = pt[8];
    }
    {
      register u8 fl asm("r1");
      register u32 t0 asm("r0");
      fl = (p->s).flags;
      a3 = 0x10;
      t0 = a3;
      t0 &= fl;
      if (t0 != 0) {
        a3 |= pv;
      } else {
        a3 = pv;
      }
    }
    ((struct VFX* (*)())CreateSlashedEnemy)(c5, s6, 0, a3);
  }
  {
    struct Coord* c7;
    register const struct SlashedEnemy* sip asm("ip");
    register u8* pr2 asm("r2");
    register s32 pv6 asm("r6");
    c7 = &(p->s).coord;
    asm("" : "+r"(c7));
    sip = &sSlashedEnemies[2];
    pr2 = (u8*)p + 0xb4;
    pv6 = pr2[8];
    {
      register u8 fl asm("r1");
      register u32 t0 asm("r0");
      fl = (p->s).flags;
      a3 = 0x10;
      t0 = a3;
      t0 &= fl;
      c5 = c7;
      pr8 = pr2;
      if (t0 != 0) {
        a3 |= pv6;
      } else {
        a3 = pv6;
      }
    }
    ((struct VFX* (*)())CreateSlashedEnemy)(c7, sip, 0, a3);
  }
  {
    register struct Coord* c6 asm("r6");
    const struct SlashedEnemy* s7;
    u8 p2;
    c6 = c5;
    s7 = &sSlashedEnemies[3];
    {
      register u8* pl asm("r0");
      pl = pr8;
      p2 = pl[8];
    }
    {
      register u8 fl asm("r1");
      register u32 t0 asm("r0");
      fl = (p->s).flags;
      a3 = 0x10;
      t0 = a3;
      t0 &= fl;
      if (t0 != 0) {
        a3 |= p2;
      } else {
        a3 = p2;
      }
    }
    ((struct VFX* (*)())CreateSlashedEnemy)(c6, s7, 0, a3);
  }
  {
    register struct Coord* c6 asm("r6");
    const struct SlashedEnemy* s7;
    u8 p2;
    c6 = c5;
    s7 = &sSlashedEnemies[3];
    {
      register u8* pl asm("r0");
      pl = pr8;
      p2 = pl[8];
    }
    {
      register u8 fl asm("r1");
      register u32 t0 asm("r0");
      fl = (p->s).flags;
      a3 = 0x10;
      t0 = a3;
      t0 &= fl;
      if (t0 != 0) {
        a3 |= p2;
      } else {
        a3 = p2;
      }
    }
    ((struct VFX* (*)())CreateSlashedEnemy)(c6, s7, 0, a3);
  }
  CreateSmoke(1, c5);
  if ((p->s).flags & 0x10) {
    CreateSmoke(2, c5);
    CreateSmoke(2, c5);
  } else {
    CreateSmoke(2, c5);
    CreateSmoke(2, c5);
  }
  {
    register s32 cf asm("r0");
    register s32 flv asm("r1");
    flv = (p->s).flags;
    cf = 0xFE;
    asm("" : "+r"(cf));
    (p->s).flags = cf & flv;
  }
  PlaySound(0x2A);
  {
    register struct Coord* c1 asm("r1");
    c1 = c5;
    TryDropItem(4, c1);
  }
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, c5);
  SET_ENEMY_ROUTINE(p, 4);
}

void CreateGhost27(struct Coord* c, u8 r1, u8 r2);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);
extern const struct SlashedEnemy sSlashedEnemies[4];

void gyroCannon_0806dccc(struct Enemy* p) {
  if ((p->s).mode[3] == 0) {
    SetMotion(&p->s, 0x1707);
    {
      struct Coord* ca;
      u32 xf;
      u32 one;
      ca = &(p->s).coord;
      xf = (p->s).flags >> 4;
      one = 1;
      xf &= one;
      CreateGhost27(ca, xf, one);
    }
    {
      struct Entity* e = (p->s).unk_2c;
      s32 y = e->coord.y;
      s32 x = e->coord.x;
      (p->s).coord.x = x;
      (p->s).coord.y = y;
    }
    (p->s).mode[3]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    struct Entity* e = (p->s).unk_2c;
    if (e != NULL) {
      if (e->mode[0] > 1) {
        (p->s).unk_2c = NULL;
      } else {
        (p->s).coord.y = e->coord.y + -0x200;
      }
      if ((p->s).unk_2c != NULL) {
        return;
      }
    }
  }
  {
    struct Coord* c7;
    register const struct SlashedEnemy* sip asm("ip");
    register u8* pr2 asm("r2");
    register u8* pr8 asm("r8");
    u8 p5;
    register struct Coord* c6 asm("r6");
    register u32 a3 asm("r3");
    c7 = &(p->s).coord;
    sip = &sSlashedEnemies[2];
    pr2 = (u8*)p + 0xb4;
    p5 = pr2[8];
    {
      register u8 fl asm("r1");
      register u32 t0 asm("r0");
      fl = (p->s).flags;
      a3 = 0x10;
      t0 = a3;
      t0 &= fl;
      c6 = c7;
      pr8 = pr2;
      if (t0 != 0) {
        a3 |= p5;
      } else {
        a3 = p5;
      }
    }
    ((struct VFX* (*)())CreateSlashedEnemy)(c7, sip, 0, a3);
    {
      register struct Coord* c5 asm("r5");
      const struct SlashedEnemy* s7;
      u8 p2;
      c5 = c6;
      s7 = &sSlashedEnemies[3];
      {
        register u8* pl asm("r1");
        pl = pr8;
        p2 = pl[8];
      }
      {
        register u8 fl asm("r1");
        register u32 t0 asm("r0");
        fl = (p->s).flags;
        a3 = 0x10;
        t0 = a3;
        t0 &= fl;
        if (t0 != 0) {
          a3 |= p2;
        } else {
          a3 = p2;
        }
      }
      ((struct VFX* (*)())CreateSlashedEnemy)(c5, s7, 0, a3);
    }
    CreateSmoke(1, c6);
    if ((p->s).flags & 0x10) {
      CreateSmoke(2, c6);
    } else {
      CreateSmoke(2, c6);
    }
    {
      register struct Coord* c1 asm("r1");
      c1 = c6;
      TryDropItem(4, c1);
    }
    PlaySound(0x2A);
    if (gMission.enemyCount <= 0x270E) {
      gMission.enemyCount++;
    }
    TryDropZakoDisk(p, c6);
    SET_ENEMY_ROUTINE(p, 4);
  }

}



static void FUN_0806ddfc(struct Enemy* p) {
  register u32 a3 asm("r3");
  register struct Coord* c6 asm("r6");
  register u8* pr8 asm("r8");
  if ((p->s).mode[3] == 0) {
    SetMotion(&p->s, 0x1708);
    {
      struct Coord* ca;
      u32 xf;
      u32 one;
      ca = &(p->s).coord;
      xf = (p->s).flags >> 4;
      one = 1;
      xf &= one;
      CreateGhost27(ca, xf, 0);
    }
    (p->s).work[2] = 0x30;
    (p->s).mode[3]++;
  }
  UpdateMotionGraphic(&p->s);
  {
    s32 raw = (p->s).work[2] - 1;
    (p->s).work[2] = raw;
    if ((u8)raw == 0xFF) {
      {
        struct Coord* c7;
        register const struct SlashedEnemy* sip asm("ip");
        register u8* pr2 asm("r2");
        register s32 pv5 asm("r5");
        c7 = &(p->s).coord;
        asm("" : "+r"(c7));
        sip = &sSlashedEnemies[2];
        pr2 = (u8*)p + 0xb4;
        pv5 = pr2[8];
        {
          register u8 fl asm("r1");
          register u32 t0 asm("r0");
          fl = (p->s).flags;
          a3 = 0x10;
          t0 = a3;
          t0 &= fl;
          c6 = c7;
          pr8 = pr2;
          if (t0 != 0) {
            a3 |= pv5;
          } else {
            a3 = pv5;
          }
        }
        ((struct VFX* (*)())CreateSlashedEnemy)(c7, sip, 0, a3);
      }
      {
        register struct Coord* c5 asm("r5");
        const struct SlashedEnemy* s7;
        u8 p2;
        c5 = c6;
        s7 = &sSlashedEnemies[3];
        {
          register u8* pl asm("r0");
          pl = pr8;
          p2 = pl[8];
        }
        {
          register u8 fl asm("r1");
          register u32 t0 asm("r0");
          fl = (p->s).flags;
          a3 = 0x10;
          t0 = a3;
          t0 &= fl;
          if (t0 != 0) {
            a3 |= p2;
          } else {
            a3 = p2;
          }
        }
        ((struct VFX* (*)())CreateSlashedEnemy)(c5, s7, 0, a3);
      }
      CreateSmoke(1, c6);
      if ((p->s).flags & 0x10) {
        CreateSmoke(2, c6);
      } else {
        CreateSmoke(2, c6);
      }
      {
        register struct Coord* c1 asm("r1");
        c1 = c6;
        TryDropItem(4, c1);
      }
      PlaySound(0x2A);
      if (gMission.enemyCount <= 0x270E) {
        gMission.enemyCount++;
      }
      TryDropZakoDisk(p, c6);
      SET_ENEMY_ROUTINE(p, 4);
    }
  }
}

// 0x0806df10
static void FUN_0806df10(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & BODY_STATUS_WHITE) {
    struct Entity* other = (struct Entity*)body->enemy->parent;
    struct GyroCannon* self = (struct GyroCannon*)body->parent;
    (&self->props)->is_right = (other->coord).x > (self->s).coord.x;
  }
}

void FUN_0806d618(struct Enemy* p);
void FUN_0806d684(struct Enemy* p);
void FUN_0806d7e0(struct Enemy* p);
void FUN_0806d8b0(struct Enemy* p);
void FUN_0806d998(struct Enemy* p);
void FUN_0806d9d4(struct Enemy* p);
void FUN_0806da20(struct Enemy* p);
void FUN_0806da5c(struct Enemy* p);
void FUN_0806dab8(struct Enemy* p);
void FUN_0806db58(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_0836666c[10] = {
    FUN_0806d618,
    FUN_0806d684,
    FUN_0806d7e0,
    FUN_0806d8b0,
    FUN_0806d998,
    FUN_0806d9d4,
    FUN_0806da20,
    FUN_0806da5c,
    FUN_0806dab8,
    FUN_0806db58,
};
// clang-format on

void gyroCannon_0806db8c(struct Enemy* p);
void gyroCannon_0806dccc(struct Enemy* p);
static void FUN_0806ddfc(struct Enemy* p);

static const EnemyFunc sUpdates2[3] = {
    gyroCannon_0806db8c,
    gyroCannon_0806dccc,
    FUN_0806ddfc,
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};

// 0x083666a8
static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(4), PIXEL(32), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(4), PIXEL(32), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(20), PIXEL(32), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 2,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(20), PIXEL(32), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(4), PIXEL(32), PIXEL(24)},
    },
};

// 0x08366720
const struct SlashedEnemy sSlashedEnemies[4] = {
    {
      m : 0x170B,
      unk_02 : {255, 17},
      c : {0x0000, 0x0000},
      d : {0x0100, -0x0400},
      unk_coord_0c : {0x03FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {0, 0},
    },
    {
      m : 0x170C,
      unk_02 : {255, 17},
      c : {0x0000, 0x0000},
      d : {0x0100, -0x0300},
      unk_coord_0c : {0x01FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {0, 0},
    },
    {
      m : 0x170D,
      unk_02 : {255, 17},
      c : {0x0000, 0x0000},
      d : {0x0100, -0x0400},
      unk_coord_0c : {0x03FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {0, 0},
    },
    {
      m : 0x170E,
      unk_02 : {255, 17},
      c : {0x0000, 0x0000},
      d : {0x0100, -0x0300},
      unk_coord_0c : {0x01FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {0, 0},
    },
};
