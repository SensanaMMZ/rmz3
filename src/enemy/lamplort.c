#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "camera.h"
#include "stagerun.h"
#include "zero.h"

static const struct Coord sElementCoord;

static const struct Collision sCollisions[8];

static void Lamplort_Init(struct Enemy* p);
void Lamplort_Update(struct Enemy* p);
void Lamplort_Die(struct Enemy* p);
void Lamplort_Disappear(struct Enemy* p);

// clang-format off
const EnemyRoutine gLamplortRoutine = {
    [ENTITY_INIT] =      Lamplort_Init,
    [ENTITY_UPDATE] =    Lamplort_Update,
    [ENTITY_DIE] =       Lamplort_Die,
    [ENTITY_DISAPPEAR] = Lamplort_Disappear,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreateLamplort(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_LAMPLORT);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

// --------------------------------------------

NAKED static void Lamplort_Init(struct Enemy* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	sub sp, #8\n\
	adds r6, r0, #0\n\
	bl InitNonAffineMotion\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #1\n\
	movs r3, #0\n\
	adds r2, r0, #0\n\
	orrs r2, r1\n\
	movs r0, #2\n\
	orrs r2, r0\n\
	orrs r2, r3\n\
	strb r2, [r6, #0xa]\n\
	ldr r0, _0806C290 @ =gSystemSavedataManager\n\
	ldrb r1, [r0, #0x15]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _0806C29C\n\
	ldr r0, _0806C294 @ =gCurStory\n\
	ldrb r1, [r0, #4]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	lsls r0, r0, #0x18\n\
	lsrs r5, r0, #0x18\n\
	cmp r5, #0\n\
	bne _0806C29C\n\
	movs r0, #4\n\
	orrs r2, r0\n\
	strb r2, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0806C298 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0xc\n\
	b _0806C2B4\n\
	.align 2, 0\n\
_0806C290: .4byte gSystemSavedataManager\n\
_0806C294: .4byte gCurStory\n\
_0806C298: .4byte sCollisions\n\
_0806C29C:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #4\n\
	movs r5, #0\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _0806C2E0 @ =sCollisions\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #8\n\
_0806C2B4:\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	str r5, [r4, #0x24]\n\
	ldr r0, _0806C2E4 @ =FUN_0806ce60\n\
	str r0, [r4, #0x24]\n\
	adds r1, r6, #0\n\
	adds r1, #0xb4\n\
	ldr r0, [r6, #0x54]\n\
	str r0, [r1]\n\
	movs r0, #0\n\
	str r0, [r6, #0x60]\n\
	str r0, [r6, #0x5c]\n\
	ldrb r1, [r6, #0x10]\n\
	cmp r1, #0\n\
	bne _0806C2E8\n\
	adds r0, r6, #0\n\
	adds r0, #0xbc\n\
	strb r1, [r0]\n\
	adds r4, r0, #0\n\
	b _0806C2F2\n\
	.align 2, 0\n\
_0806C2E0: .4byte sCollisions\n\
_0806C2E4: .4byte FUN_0806ce60\n\
_0806C2E8:\n\
	adds r1, r6, #0\n\
	adds r1, #0xbc\n\
	movs r0, #1\n\
	strb r0, [r1]\n\
	adds r4, r1, #0\n\
_0806C2F2:\n\
	ldrb r2, [r4]\n\
	cmp r2, #0\n\
	beq _0806C300\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0x10\n\
	orrs r0, r1\n\
	b _0806C306\n\
_0806C300:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xef\n\
	ands r0, r1\n\
_0806C306:\n\
	strb r0, [r6, #0xa]\n\
	movs r7, #1\n\
	adds r1, r7, #0\n\
	ands r1, r2\n\
	adds r0, r6, #0\n\
	adds r0, #0x4c\n\
	movs r5, #0\n\
	strb r1, [r0]\n\
	adds r3, r6, #0\n\
	adds r3, #0x4a\n\
	lsls r1, r1, #4\n\
	ldrb r2, [r3]\n\
	movs r0, #0x11\n\
	rsbs r0, r0, #0\n\
	ands r0, r2\n\
	orrs r0, r1\n\
	strb r0, [r3]\n\
	adds r0, r6, #0\n\
	adds r0, #0xc0\n\
	str r5, [r0]\n\
	strb r5, [r6, #0x12]\n\
	ldr r0, [r6, #0x54]\n\
	ldr r1, [r6, #0x58]\n\
	bl FUN_0800a05c\n\
	str r0, [r6, #0x58]\n\
	ldrb r2, [r4]\n\
	adds r0, r6, #0\n\
	mov r1, sp\n\
	movs r3, #0\n\
	bl CreateProjectile6\n\
	str r0, [r6, #0x2c]\n\
	adds r0, r6, #0\n\
	bl IsFrozen\n\
	cmp r0, #0\n\
	beq _0806C362\n\
	movs r1, #0xc8\n\
	lsls r1, r1, #5\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	adds r0, r6, #0\n\
	bl UpdateMotionGraphic\n\
_0806C362:\n\
	adds r0, r6, #0\n\
	adds r0, #0xbb\n\
	strb r5, [r0]\n\
	ldr r1, _0806C38C @ =gEnemyFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	str r7, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	strb r7, [r6, #0xd]\n\
	strb r5, [r6, #0xe]\n\
	strb r5, [r6, #0xf]\n\
	adds r0, r6, #0\n\
	bl Lamplort_Update\n\
	add sp, #8\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_0806C38C: .4byte gEnemyFnTable\n\
 .syntax divided\n");
}

// --------------------------------------------

extern const EnemyFunc sUpdates1[10];
extern const EnemyFunc sUpdates2[10];
s32 FUN_0806ce5c(struct Enemy* p);
bool8 lamplort_0806ce08(struct Enemy* p);
void Lamplort_Die(struct Enemy* p);

void Lamplort_Update(struct Enemy* p) {
  u8 m;
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    if (FUN_0806ce5c(p)) {
      goto alive;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Lamplort_Die(p);
  return;

alive:
  if (IsFrozen(&p->s)) {
    u32 v;
    *(u32*)((u8*)(p->s).unk_2c + 0xb4) |= 2;
    v = *(u32*)((u8*)p + 0xc0);
    if (v == 0) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = v;
    }
  }
  (sUpdates1[(p->s).mode[1]])(p);
  lamplort_0806ce08(p);
  m = (p->s).mode[1];
  if (m == 7) goto dispatch2;
  if (m == 9) goto dispatch2;
  if (IsFrozen(&p->s)) {
    p->props[6] = (p->s).mode[1];
    return;
  }
dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/lamplort_p1_pre_b.inc");

void Lamplort_Disappear(struct Enemy* p) {
  DeleteEnemy((struct Entity*)p);
}

bool8 FUN_0806c81c(struct Enemy* p) { return TRUE; }


void FUN_0806c820(struct Enemy* p) {}

bool8 FUN_0806c824(struct Enemy* p) { return TRUE; }

void FUN_0806c828(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      SetDDP(&p->body, &sCollisions[0]);
      SetMotion(&p->s, 0x1900);
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      (p->s).mode[2]++;
      // fallthrough
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_0806c8c8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/lamplort_p4.inc");

bool8 FUN_0806c9c0(struct Enemy* p) { return TRUE; }

// 0x0806c9c4
void FUN_0806c9c4(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x19, 0x06));
      SetDDP(&p->body, &sCollisions[0]);
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      (p->s).work[2] = 0xFF;
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
        (p->s).work[3] = 0;
      } else {
        (p->s).work[3] = 1;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      u8 w2 = (p->s).work[2];
      if ((w2 & 0xF) == 0) {
        PlaySound(0x11F);
      }
    }
      if ((p->s).work[3] == 0) {
        if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= 0x4000) {
          (p->s).work[3] = 1;
        }
      } else {
        if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
          (p->s).work[3] = 0;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          break;
        }
      }
      (p->s).mode[1] = 4, (p->s).mode[2] = 0;
      break;
  }
}

bool8 true_0806cac4(struct Enemy* p) { return TRUE; }

void FUN_0806cac8(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x1908);
      SetDDP(&p->body, &sCollisions[0]);
      *(u32*)((u8*)(p->s).unk_2c + 0xb4) |= 2;
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == MOTION_END) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_0806cb58(struct Enemy* p) { return TRUE; }

void FUN_0806cb5c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x1901);
      SetDDP(&p->body, &sCollisions[0]);
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      *(u32*)((u8*)(p->s).unk_2c + 0xb4) |= 2;
      (p->s).work[2] = 8;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == MOTION_END) {
        if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
          (p->s).mode[1] = 6;
          (p->s).mode[2] = 0;
        }
      }
      break;
  }
}

bool8 FUN_0806cc00(struct Enemy* p) { return TRUE; }

extern const motion_t Action_ARRAY_080ff004[4];

void lamplort_0806cc04(struct Enemy* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      u8 fv;
      u32 x1;
      s32 z3;
      SetMotion(&p->s, 0x1902);
      SetDDP(&p->body, &sCollisions[5]);
      fv = *((u8*)p + 0xbc);
      if (fv != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      x1 = 1 & fv;
      {
        bool8* xa = &((p->s).spr).xflip;
        z3 = 0;
        *xa = x1;
      }
      {
        register u8* t0 asm("r0");
        register u8* oa asm("ip");
        u32 off = 0x4a;
        asm("" : "+r"(off));
        off += (u32)p;
        t0 = (u8*)off;
        oa = t0;
        asm("" : "+r"(oa));
        x1 <<= 4;
        {
          s32 ov = *t0;
          s32 m11 = -0x11;
          u32 vv;
          register u8* fa asm("r1");
          asm("" : "+r"(m11));
          vv = (m11 & ov) | x1;
          fa = oa;
          asm("" : "+r"(fa));
          *fa = vv;
        }
      }
      (p->s).work[3] = z3;
      (p->s).work[2] = 8;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      u8 w2 = (p->s).work[2];
      if (w2 != 0) {
        s32 t = w2 - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          goto umg;
        }
      }
      {
        s32 raw = (p->s).work[3] + 1;
        u8 t3;
        (p->s).work[3] = raw;
        t3 = raw;
        if (t3 > 2) {
          (p->s).mode[2]++;
        } else {
          (p->s).work[2] = 8;
          if (t3 == 2) {
            SetMotion(&p->s, Action_ARRAY_080ff004[(p->s).work[3]]);
          }
          if ((p->s).work[3] == 1) {
            SetDDP(&p->body, &sCollisions[5]);
          } else {
            SetDDP(&p->body, &sCollisions[0]);
          }
        }
      }
      if ((p->s).work[3] == 1) {
        u8* bc = (u8*)p + 0xbc;
        register u32 nv asm("r1");
        register u32 one2 asm("r2");
        u8 rv;
        u32 x2;
        nv = *bc;
        one2 = 1;
        asm("" : "+r"(one2));
        nv ^= one2;
        *bc = nv;
        rv = *bc;
        if (rv != 0) {
          register s32 flA asm("r0");
          register s32 cA asm("r1");
          flA = (p->s).flags;
          cA = 0x10;
          asm("" : "+r"(cA));
          flA |= cA;
          (p->s).flags = flA;
        } else {
          (p->s).flags &= 0xEF;
        }
        x2 = 1 & rv;
        ((p->s).spr).xflip = x2;
        {
          register u8* oa3 asm("r3");
          s32 ov2;
          s32 m11b;
          oa3 = (u8*)&((p->s).spr).oam + 6;
          x2 <<= 4;
          ov2 = *oa3;
          m11b = -0x11;
          asm("" : "+r"(m11b));
          *oa3 = (m11b & ov2) | x2;
        }
      }
    umg:
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 true_0806cd48(struct Enemy* p) { return TRUE; }

void FUN_0806cd4c(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[7]);
    *(u32*)((u8*)(p->s).unk_2c + 0xb4) |= 2;
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[0]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0806cda4(struct Enemy* p) { return TRUE; }


void FUN_0806cda8(struct Enemy* p) {}

bool8 FUN_0806cdac(struct Enemy* p) { return TRUE; }

void FUN_0806cdb0(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[7]);
    *(u32*)((u8*)(p->s).unk_2c + 0xb4) |= 2;
    (p->s).d.y = 0;
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[0]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 lamplort_0806ce08(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xc0);
  if (*slot == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = e;
    if (e != NULL) {
      u8 attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        (p->s).mode[1] = 7;
        (p->s).mode[2] = 0;
      } else if (attr == 0x30) {
        (p->s).mode[1] = 9;
        (p->s).mode[2] = 0;
      }
    }
  }
  return TRUE;
}

s32 FUN_0806ce5c(struct Enemy* p) { return TRUE; }

// 0x0806CE60
void FUN_0806ce60(struct Body* b, struct Coord* c, struct Coord* r2 UNUSED) {
  u8 k = (b->enemy)->processing->atkType;
  if (k == 3 || k == 0xE || k == 0xF) {
    struct Enemy* e = (struct Enemy*)b->parent;
    if (*(u32*)((u8*)e + 0x8c) & 0x200) {
      if ((e->s).coord.x < c->x) {
        *((u8*)e + 0xbb) = 0xFF;
      } else {
        *((u8*)e + 0xbb) = 0xFE;
      }
    }
  }
  if (b->processing->kind == 2 && (*(u32*)&(b->enemy)->processing->atkType & 0x200FF) == 0x20002) {
    struct Enemy* q = (struct Enemy*)b->parent;
    if ((u8)((q->s).mode[1] - 5) > 1) {
      u8 fl = (q->s).flags & 0x10;
      if (fl == 0) {
        if ((pZero2->s).coord.x < (q->s).coord.x) {
          (q->s).mode[1] = 5;
          (q->s).mode[2] = fl;
        }
      } else {
        if ((pZero2->s).coord.x > (q->s).coord.x) {
          (q->s).mode[1] = 5;
          (q->s).mode[2] = 0;
        }
      }
      if (*(u32*)((u8*)q + 0x8c) & 0x200) {
        *(u16*)((u8*)q + 0xa4) = 1;
      }
    }
  }
}

bool8 FUN_0806c81c(struct Enemy* p);
bool8 FUN_0806c824(struct Enemy* p);
bool8 FUN_0806c8c8(struct Enemy* p);
bool8 FUN_0806c9c0(struct Enemy* p);
bool8 true_0806cac4(struct Enemy* p);
bool8 FUN_0806cb58(struct Enemy* p);
bool8 FUN_0806cc00(struct Enemy* p);
bool8 true_0806cd48(struct Enemy* p);
bool8 FUN_0806cda4(struct Enemy* p);
bool8 FUN_0806cdac(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    (EnemyFunc)FUN_0806c81c,
    (EnemyFunc)FUN_0806c824,
    (EnemyFunc)FUN_0806c8c8,
    (EnemyFunc)FUN_0806c9c0,
    (EnemyFunc)true_0806cac4,
    (EnemyFunc)FUN_0806cb58,
    (EnemyFunc)FUN_0806cc00,
    (EnemyFunc)true_0806cd48,
    (EnemyFunc)FUN_0806cda4,
    (EnemyFunc)FUN_0806cdac,
};
// clang-format on

void FUN_0806c820(struct Enemy* p);
void FUN_0806c828(struct Enemy* p);
void FUN_0806c8cc(struct Enemy* p);
void FUN_0806c9c4(struct Enemy* p);
void FUN_0806cac8(struct Enemy* p);
void FUN_0806cb5c(struct Enemy* p);
void lamplort_0806cc04(struct Enemy* p);
void FUN_0806cd4c(struct Enemy* p);
void FUN_0806cda8(struct Enemy* p);
void FUN_0806cdb0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_0806c820,
    FUN_0806c828,
    FUN_0806c8cc,
    FUN_0806c9c4,
    FUN_0806cac8,
    FUN_0806cb5c,
    lamplort_0806cc04,
    FUN_0806cd4c,
    FUN_0806cda8,
    FUN_0806cdb0,
};
// clang-format on

static const struct Collision sCollisions[8] = {
    {
      kind : DRP2,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 255,
      hardness : METAL,
      remaining : 4,
      range : {-PIXEL(9), -PIXEL(14), PIXEL(26), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 3,
      priorityLayer : 0xFFFFFFFF,
      range : {-PIXEL(8), -PIXEL(14), PIXEL(24), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      remaining : 2,
      range : {PIXEL(10), -PIXEL(14), PIXEL(14), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(6), -PIXEL(14), PIXEL(31), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(23), -PIXEL(14), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      hardness : METAL,
      remaining : 1,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(2), -PIXEL(12), PIXEL(22), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(1), -PIXEL(11), PIXEL(20), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 3,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(12), PIXEL(22), PIXEL(20)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(10)};
