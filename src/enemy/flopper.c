#include "collision.h"
#include "enemy.h"
#include "global.h"

struct FlopperObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  struct Coord c;
  u32 unk_08;
  u8 unk_0c[4];
};
static_assert(sizeof(struct FlopperObject) == sizeof(struct Enemy));

static const struct Collision sCollisions[2];
static const EnemyFunc sUpdates[4];

void Flopper_onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED);

static void Flopper_Init(struct FlopperObject* p);
static void Flopper_Update(struct FlopperObject* p);
void Flopper_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gFlopperRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Flopper_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Flopper_Update,
    [ENTITY_DIE] =       (EnemyFunc)Flopper_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void Flopper_Init(struct FlopperObject* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->c).x = (p->s).coord.x;
  (p->c).y = (p->s).coord.y;
  INIT_BODY(p, &sCollisions[0], 1, Flopper_onCollision);
  (p->s).flags |= FLIPABLE;
  (p->s).mode[1] = (p->s).work[0];
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM022_FLOPPER, 0x00));
  Flopper_Update((void*)p);
}

static void Flopper_Update(struct FlopperObject* p) {
  if ((p->body).status & (BODY_STATUS_DEAD | BODY_STATUS_B2)) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).work[2] = 0;
    EXIT_BODY(p);
    (p->s).flags &= ~DISPLAY;
    p->unk_08 = 0;
    (p->s).work[2] = 0;
    Flopper_Die((void*)p);
    return;
  }

  if ((p->s).mode[3] == 0) {
    if (IsFrozen((void*)p)) {
      (p->s).mode[3] = 1;
    }
  }

  if ((p->s).mode[3] != 0) {
    if ((p->s).mode[3] == 1) {
      UpdateMotionGraphic(&p->s);
      (p->s).mode[3] = 2;
    }
    if (!IsFrozen((void*)p)) {
      (p->s).mode[3] = 0;
    }
    return;
  }
  (sUpdates[(p->s).mode[1]])((void*)p);
}

#include "quake.h"
#include "mission.h"

struct Entity* CreateProjectile7(struct Coord* c, u16 a, u8 b);
void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

// 0x0806BF38
void Flopper_Die(struct Enemy* p) {
  struct Coord c;
  struct Coord* co = &(p->s).coord;
  u32* q;
  u32 v;
  AppendQuake(4, co);
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y;
  q = (u32*)((u8*)p + 0xbc);
  v = *q;
  if (*(u8*)q == 0) {
    CreateProjectile7(&c, 0x180, v >> 3);
    (p->s).work[2]++;
  }
  *q += 0x100;
  if (*q == 0x800) {
    {
      u8 t = (p->s).flags;
      register u8 fv asm("r1");
      fv = 0xFE;
      fv &= t;
      (p->s).flags = fv;
      asm volatile("" :: "r"(t));
    }
    PlaySound(0x35);
    TryDropItem(0, co);
    if (gMission.enemyCount <= 0x270E) {
      gMission.enemyCount++;
    }
    TryDropZakoDisk(p, co);
    SET_ENEMY_ROUTINE(p, 4);
  }
}

void Flopper_onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {}

#include "motion.h"
#include "trig.h"

void FUN_0806bfdc(struct FlopperObject* p) {
  switch ((p->s).mode[2]) {
    case 0:
      p->unk_08 = 0;
      SetMotion(&p->s, MOTION(0x16, 0x00));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.y = (p->c).y;
      (p->s).coord.y += SIN(p->unk_08 >> 8) * 45;
      p->unk_08 = (p->unk_08 + 0x200) & 0xFFFF;
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_0806c04c(struct FlopperObject* p) {
  switch ((p->s).mode[2]) {
    case 0:
      p->unk_08 = 0;
      SetMotion(&p->s, MOTION(0x16, 0x00));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.x = (p->c).x;
      (p->s).coord.x += SIN(p->unk_08 >> 8) * 45;
      p->unk_08 = (p->unk_08 + 0x200) & 0xFFFF;
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// 0x0806c0bc
void FUN_0806c0bc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      *(u32*)((u8*)p + 0xbc) = 0;
      SetMotion(&p->s, MOTION(0x16, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      register const s16* tbl asm("r4");
      register s32 t asm("r2");
      u32* a;
      s16 sv;
      t = *(s32*)((u8*)p + 0xb4);
      (p->s).coord.x = t;
      tbl = gSineTable;
      a = (u32*)((u8*)p + 0xbc);
      sv = tbl[(u8)(*a >> 8)];
      t += sv * 45;
      (p->s).coord.x = t;
      t = *(s32*)((u8*)p + 0xb8);
      (p->s).coord.y = t;
      sv = tbl[(u8)(*a >> 8)];
      t += sv * 45;
      (p->s).coord.y = t;
      *a = (*a + 0x200) & 0xFFFF;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x0806c150
void FUN_0806c150(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      *(u32*)((u8*)p + 0xbc) = 0;
      SetMotion(&p->s, MOTION(0x16, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      register const s16* tbl asm("r4");
      register s32 t asm("r2");
      u32* a;
      s16 sv;
      t = *(s32*)((u8*)p + 0xb4);
      (p->s).coord.x = t;
      tbl = gSineTable;
      a = (u32*)((u8*)p + 0xbc);
      sv = tbl[(u8)(*a >> 8)];
      t -= sv * 45;
      (p->s).coord.x = t;
      t = *(s32*)((u8*)p + 0xb8);
      (p->s).coord.y = t;
      sv = tbl[(u8)(*a >> 8)];
      t += sv * 45;
      (p->s).coord.y = t;
      *a = (*a + 0x200) & 0xFFFF;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      hitzone : 0x01,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1000, 0x1000},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 0x01,
      remaining : 0,
      range : {0x0000, 0x0000, 0x1000, 0x1000},
    },
};

void FUN_0806bfdc(struct FlopperObject* p);
void FUN_0806c04c(struct FlopperObject* p);
void FUN_0806c0bc(struct Enemy* p);
void FUN_0806c150(struct Enemy* p);

static const EnemyFunc sUpdates[4] = {
    (EnemyFunc)FUN_0806bfdc,
    (EnemyFunc)FUN_0806c04c,
    FUN_0806c0bc,
    FUN_0806c150,
};
