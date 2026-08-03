#include "collision.h"
#include "story.h"
#include "syssav.h"
#include "physics.h"
#include "element.h"
#include "enemy.h"
#include "global.h"

static const struct Coord sElementCoord;

static const struct Collision sCollisions[3];

void Claveker_Init(struct Enemy* p);
void Claveker_Update(struct Enemy* p);
void FUN_0808f234(struct Body* body, struct Coord* c);
void Claveker_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gClavekerRoutine = {
    [ENTITY_INIT] =      Claveker_Init,
    [ENTITY_UPDATE] =    Claveker_Update,
    [ENTITY_DIE] =       Claveker_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreateClaveker(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_CLAVEKER);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

void Claveker_Update(struct Enemy* p);

#ifdef NON_MATCHING
// one-instruction placement tie: retail branches to a SHARED `bl InitBody`
// from both hp arms (0xE / 0xA), duplicating only the r0-r2 argument setup.
// agbcc either duplicates the `bl` as well (arm 1 ends `bl; b init`, so the
// crossjumper finds no common tail) or, when the call is forced through a
// zero-arg cast with the arguments pre-pinned, drops the setup entirely.
// Instruction count and function length are exact; one branch offset differs.
NON_MATCH // 0x0808E52C
void Claveker_Init(struct Enemy* p) {
  register u8 f asm("r2");
  register s32 z5 asm("r5");
  struct Body* body;
  InitNonAffineMotion(&p->s);
  {
    register u8 fl asm("r1");
    register s32 k asm("r0");
    register s32 z3 asm("r3");
    fl = (p->s).flags;
    k = 1;
    z3 = 0;
    asm volatile("add %0, %1, #0" : "=&l"(f) : "l"(k));
    f |= fl;
    k = 2;
    f |= k;
    asm volatile("" : "+r"(z3));
    f |= z3;
    (p->s).flags = f;
  }
  if ((gSystemSavedataManager.mods[12] & 0x80) == 0) {
    goto arm2;
  }
  {
    register u8 gf asm("r1");
    register s32 k asm("r0");
    gf = gCurStory.s.gameflags[0];
    k = 0x40;
    k &= gf;
    k <<= 24;
    z5 = (u32)k >> 24;
    asm volatile("" : "+r"(z5));
    if (z5 != 0) {
      goto arm2;
    }
  }
  {
    register s32 k2 asm("r0");
    k2 = 4;
    f |= k2;
    (p->s).flags = f;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x08369388, &(p->s).coord, 0xE);
    goto init;
  }
arm2 : {
    register u8 fl2 asm("r1");
    register u8 g2 asm("r0");
    fl2 = (p->s).flags;
    g2 = 4;
    z5 = 0;
    g2 |= fl2;
    (p->s).flags = g2;
    body = &p->body;
    InitBody(body, (const struct Collision*)0x08369388, &(p->s).coord, 0xA);
  }
init:
  body->parent = (struct CollidableEntity*)p;
  body->fn = (BodyFunc)z5;
  body->fn = (BodyFunc)FUN_0808f234;
  (p->s).coord.y = FUN_0800a134((p->s).coord.x, (p->s).coord.y);
  {
    register s32 z4 asm("r4");
    register u8* b4 asm("r1");
    b4 = (u8*)p + 0xb4;
    *(s32*)b4 = (p->s).coord.x;
    {
      register u8* b8 asm("r0");
      b8 = (u8*)p + 0xb8;
      z4 = 0;
      *b8 = z4;
      asm("" : "+r"(b8));
      b8 += 4;
      asm("" : "+r"(b8));
      *(s32*)b8 = z4;
    }
    {
      u32 tbl = (u32)gEnemyFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
    (p->s).mode[1] = z4;
    (p->s).mode[2] = z4;
    (p->s).mode[3] = z4;
    if (IsFrozen(&p->s)) {
      SetMotion(&p->s, 0x7500);
      UpdateMotionGraphic(&p->s);
    }
    *((u8*)p + 0xbb) = z4;
  }
  Claveker_Update(p);
}
#else
NAKED void Claveker_Init(struct Enemy* p) {
  INCCODE("asm/enemy/claveker_init.inc");
}
#endif

extern const EnemyFunc sUpdates1[6];
extern const EnemyFunc sUpdates2[6];
bool8 FUN_0808f1e0(struct Enemy* p);
void Claveker_Die(struct Enemy* p);

void Claveker_Update(struct Enemy* p) {
  u32 dead = (p->body).status & BODY_STATUS_DEAD;
  if (dead) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Claveker_Die(p);
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_0808f1e0(p);
  if (IsFrozen(&p->s)) {
    u8 m = (p->s).mode[1];
    if (m == 2) goto skip_reset;
    if (m == 3) goto skip_reset;
    if (m == 5) goto skip_reset;
    if (m == 4) goto skip_reset;
    (p->s).mode[1] = dead;
    (p->s).mode[2] = dead;
  skip_reset:;
  }
  if (*(struct Entity**)((u8*)p + 0xbc) == NULL) {
    if (IsFrozen(&p->s)) {
      p->props[6] = (p->s).mode[1];
      return;
    }
  }
  if (IsFrozen(&p->s)) {
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
  if (*(struct Entity**)((u8*)p + 0xbc) == NULL) {
    goto dispatch2;
  }
  if (isKilled(*(struct Entity**)((u8*)p + 0xbc))) {
    SetDDP(&p->body, &sCollisions[1]);
    *(struct Entity**)((u8*)p + 0xbc) = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
    return;
  }
  SetDDP(&p->body, &sCollisions[2]);
  return;

dispatch2:
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/claveker_p1_b.inc");

bool8 FUN_0808eb20(struct Enemy* p) { return TRUE; }

#include "stagerun.h"

s32 FUN_0800a134(s32 x, s32 y);

// 0x0808EB24
void FUN_0808eb24(struct Enemy* p) {
  s32 m2 = (p->s).mode[2];
  switch (m2) {
    case 0:
      SetMotion(&p->s, 0x7500);
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
    case 1:
      UpdateMotionGraphic(&p->s);
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= 0x3FFF) {
        (p->s).coord.y = FUN_0800a134((p->s).coord.x, (p->s).coord.y);
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      s32 d;
      u8 t;
      UpdateMotionGraphic(&p->s);
      d = (p->s).work[2] - 1;
      (p->s).work[2] = d;
      t = d;
      if (t == 0) {
        (p->s).mode[1] = 1;
        (p->s).mode[2] = t;
      }
      break;
    }
  }
}

bool8 FUN_0808ebb0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/claveker_p3.inc");

bool8 FUN_0808effc(struct Enemy* p) { return TRUE; }

struct Projectile* FUN_080aed8c(struct Entity* boss, struct Coord* c1, struct Coord* c2, u8 n);

void FUN_0808f000(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x7500);
      (p->s).work[2] = 0x14;
      (p->s).mode[2]++;
      goto tick;
    case 2:
      SetMotion(&p->s, 0x7502);
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 4: {
      s32 z = 0;
      (p->s).work[2] = 8;
      *((u8*)p + 0xb9) = z;
      (p->s).mode[2]++;
    }
      // fallthrough
    case 5: {
      struct Coord c;
      SetMotion(&p->s, 0x7503);
      (p->s).work[3] = 6;
      c.x = (p->s).coord.x;
      c.y = (p->s).coord.y + 0x1A00;
      FUN_080aed8c(&p->s, &c, &c, 0);
      PlaySound(0x145);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 6: {
      s32 t3, mk, t4;
      UpdateMotionGraphic(&p->s);
      t3 = (p->s).work[3] - 1;
      (p->s).work[3] = t3;
      mk = 0xFF;
      asm("" : "+r"(mk) : "r"(t3) : "memory");
      if ((t3 << 24) != 0) {
        break;
      }
      t4 = (p->s).work[2] - 1;
      (p->s).work[2] = t4;
      if ((t4 & mk) == 0) {
        (p->s).mode[2]++;
        break;
      }
      (p->s).mode[2] = 5;
      break;
    }
    case 7:
      SetMotion(&p->s, 0x7504);
      (p->s).mode[2]++;
      // fallthrough
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 9:
      SetMotion(&p->s, 0x7500);
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
    case 10:
    tick: {
      s32 t2;
      UpdateMotionGraphic(&p->s);
      t2 = (p->s).work[2] - 1;
      (p->s).work[2] = t2;
      if ((t2 << 24) == 0) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 11: {
      s32 z = 0;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = z;
      break;
    }
  }
}

bool8 FUN_0808f158(struct Enemy* p) { return TRUE; }

void FUN_0808f15c(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0808f198(struct Enemy* p) { return TRUE; }


void FUN_0808f19c(struct Enemy* p) {}

bool8 FUN_0808f1a0(struct Enemy* p) { return TRUE; }

void FUN_0808f1a4(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0808f1e0(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xbc);
  if (*slot == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = e;
    if (e != NULL) {
      u8 attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      } else if (attr == 0x30) {
        (p->s).mode[1] = 5;
        (p->s).mode[2] = 0;
      }
    }
  }
  return TRUE;
}

void FUN_0808f234(struct Body* body, struct Coord* c) {
  const struct Collision* col = (body->enemy)->processing;
  if (col->atkType == 3 || col->atkType == 0xe || col->atkType == 0xf) {
    struct Enemy* self = (struct Enemy*)body->parent;
    if ((self->body).status & 0x200) {
      if ((self->s).coord.x < c->x) {
        *(u8*)((u8*)self + 0xbb) = 0xff;
      } else {
        *(u8*)((u8*)self + 0xbb) = 0xfe;
      }
    }
  }
}

// --------------------------------------------

bool8 FUN_0808eb20(struct Enemy* p);
bool8 FUN_0808ebb0(struct Enemy* p);
bool8 FUN_0808effc(struct Enemy* p);
bool8 FUN_0808f158(struct Enemy* p);
bool8 FUN_0808f198(struct Enemy* p);
bool8 FUN_0808f1a0(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)FUN_0808eb20,
    (EnemyFunc)FUN_0808ebb0,
    (EnemyFunc)FUN_0808effc,
    (EnemyFunc)FUN_0808f158,
    (EnemyFunc)FUN_0808f198,
    (EnemyFunc)FUN_0808f1a0,
};
// clang-format on

void FUN_0808eb24(struct Enemy* p);
void FUN_0808ebb4(struct Enemy* p);
void FUN_0808f000(struct Enemy* p);
void FUN_0808f15c(struct Enemy* p);
void FUN_0808f19c(struct Enemy* p);
void FUN_0808f1a4(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    FUN_0808eb24,
    FUN_0808ebb4,
    FUN_0808f000,
    FUN_0808f15c,
    FUN_0808f19c,
    FUN_0808f1a4,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(11), PIXEL(30), PIXEL(22)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(12)};
