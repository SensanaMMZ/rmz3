#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "element.h"

void Beetank_Init(struct Enemy* p);
void Beetank_Update(struct Enemy* p);
void Beetank_Die(struct Enemy* p);

bool8 FUN_0807be50(struct Enemy* p);
static const EnemyFunc sUpdates1[5];
static const EnemyFunc sUpdates2[5];

// clang-format off
const EnemyRoutine gBeetankRoutine = {
    [ENTITY_INIT] =      Beetank_Init,
    [ENTITY_UPDATE] =    Beetank_Update,
    [ENTITY_DIE] =       Beetank_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreateBeetank(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_BEETANK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

static const struct Collision sCollisions[2];
void nop_0807bea4(struct Enemy* p);

void Beetank_Init(struct Enemy* p) {
  s32 v[2];
  InitNonAffineMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    register s32 z2 asm("r2");
    f0 = (p->s).flags;
    d0 = 1;
    d0 |= f0;
    {
      register s32 c2 asm("r1");
      c2 = 2;
      d0 |= c2;
    }
    z2 = 0;
    {
      register s32 c3 asm("r1");
      c3 = 0xEF;
      d0 &= c3;
    }
    (p->s).flags = d0;
    ((p->s).spr).xflip = z2;
  }
  {
    u8* a = (u8*)p + 0x4a;
    register u8 b asm("r1");
    s32 msk;
    b = *a;
    msk = -0x11;
    msk &= b;
    *a = msk;
  }
  v[0] = PushoutToLeft1((p->s).coord.x + 0x1000, (p->s).coord.y + -0xC00);
  v[1] = PushoutToRight1((p->s).coord.x + -0x1000, (p->s).coord.y + -0xC00);
  if (v[0] != 0) {
    if (v[1] != 0) {
      goto skipx;
    }
    (p->s).coord.x += v[0];
  } else {
    if (v[1] == 0) {
      goto skipx;
    }
    (p->s).coord.x += v[1];
  }
skipx:
  v[0] = FUN_08009f6c((p->s).coord.x + -0x1000, (p->s).coord.y + -0x600);
  v[1] = FUN_08009f6c((p->s).coord.x + 0x1000, (p->s).coord.y + -0x600);
  if (v[0] < v[1]) {
    (p->s).coord.y = v[0];
  } else {
    (p->s).coord.y = v[1];
  }
  {
    register u8 f1 asm("r1");
    register s32 c4 asm("r0");
    register s32 z5 asm("r5");
    f1 = (p->s).flags;
    c4 = 4;
    z5 = 0;
    c4 |= f1;
    (p->s).flags = c4;
    {
      struct Body* body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 6);
      body->parent = (void*)p;
      body->fn = (BodyFunc)nop_0807bea4;
    }
    {
      u8* w = (u8*)p + 0x5c;
      *(s32*)(w + 4) = z5;
      (p->s).d.x = z5;
      w += 0x60;
      *(s32*)w = z5;
      w -= 4;
      *w = z5;
    }
    SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = z5;
    (p->s).mode[2] = z5;
    (p->s).mode[3] = z5;
  }
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, 0x3E00);
    UpdateMotionGraphic(&p->s);
  }
  Beetank_Update(p);
}


// Does not match: agbcc cannot reproduce the target's register allocation in
// the ground-snap min() block (the constant is cached in r8 forcing a push/pop,
// and the two FUN_08009f6c results are double-homed). ~48h of permuter search
// floored at 18 instruction diffs / score 235, so this stays as the matching
// asm body; the MODERN branch documents the equivalent C.
NON_MATCH void Beetank_Update(struct Enemy* p) {
#if MODERN
  if (*(u32*)((u8*)p + 0x8c) & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Beetank_Die(p);
  } else {
    s32 push, a, b;

    (sUpdates1[(p->s).mode[1]])(p);
    FUN_0807be50(p);

    push = PushoutToLeft1((p->s).coord.x + 0x400, (p->s).coord.y - 0x400);
    if (push != 0) (p->s).coord.x += push;
    push = PushoutToRight1((p->s).coord.x - 0x400, (p->s).coord.y - 0x400);
    if (push != 0) (p->s).coord.x += push;

    a = FUN_08009f6c((p->s).coord.x - 0x1000, (p->s).coord.y - 0x600);
    b = FUN_08009f6c((p->s).coord.x + 0x1000, (p->s).coord.y - 0x600);
    (p->s).coord.y = (a < b) ? a : b;

    if (IsFrozen(&p->s)) {
      *(u8*)((u8*)p + 0xba) = (p->s).mode[1];
    } else {
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
#else
  INCCODE("asm/enemy/beetank_Update.inc");
#endif
}

INCASM("asm/enemy/beetank_Die.inc");

bool8 nop_0807bc8c(struct Enemy* p) { return TRUE; }

#include "zero.h"

// 0x0807bc90
void FUN_0807bc90(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x3E, 0x00));
      (p->s).work[2] = 0x78;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      register u8 fl asm("r2");
      register s32 v asm("r1");
      register s32 sh asm("r0");
      register u8 fv asm("r0");
      if ((pZero2->s).coord.x > (p->s).coord.x) {
        fl = (p->s).flags;
        if ((fl & X_FLIP) != 0) {
          goto skip;
        }
        sh = fl >> 4;
        v = 1;
        v &= ~sh;
        if (v != 0) {
          fv = 0x10;
          fv |= fl;
          asm("" : "+r"(fv));
        } else {
          fv = 0xEF;
          fv &= fl;
        }
      } else {
        fl = (p->s).flags;
        if ((fl & X_FLIP) == 0) {
          goto skip;
        }
        sh = fl >> 4;
        v = 1;
        v &= ~sh;
        if (v != 0) {
          fv = 0x10;
          fv |= fl;
        } else {
          fv = 0xEF;
          fv &= fl;
        }
      }
      (p->s).flags = fv;
      (p->s).spr.xflip = v;
      {
        u8* oa = (u8*)p + 0x4a;
        s32 sh4, ov, m11;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
    skip:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      {
        s32 z = 0;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = z;
      }
      break;
    }
  }
}

bool8 nop_0807bd3c(struct Enemy* p) { return TRUE; }

struct Entity* FUN_080a244c(struct Coord* a, struct Coord* b, u8 c);

// 0x0807BD40
void FUN_0807bd40(struct Enemy* p) {
  struct Coord c;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 4;
      SetMotion(&p->s, MOTION(0x3E, 0x01));
      (p->s).mode[2]++;
    case 1:
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          goto draw;
        }
      }
      {
        register s32 x asm("r3");
        register u8 fl asm("r1");
        register s32 k asm("r2");
        x = (p->s).coord.x;
        c.x = x;
        {
          s32 cy = (p->s).coord.y;
          s32 k1 = -0x1000;
          asm("" : "+r"(k1));
          c.y = cy + k1;
        }
        fl = (p->s).flags;
        if ((0x10 & fl) == 0) {
          k = -0x1000;
          asm("" : "+r"(k));
        } else {
          k = 0x1000;
        }
        { register s32 nx asm("r0"); nx = x + k; c.x = nx; }
        FUN_080a244c(&c, &c, (((u32)fl << 24) >> 28) & 1);
        PlaySound(0x2D);
        (p->s).mode[2]++;
      }
    case 2:
    draw:
      UpdateMotionGraphic(&p->s);
      if (*(u8*)((u8*)p + 0x73) == 3) {
        u8 z = 0;
        (p->s).mode[1] = z;
        (p->s).mode[2] = z;
      }
      break;
  }
}

bool8 nop_0807bde4(struct Enemy* p) { return TRUE; }

void FUN_0807bde8(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) (p->s).mode[2] = 1;
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0807be14(struct Enemy* p) { return TRUE; }


void nop_0807be18(struct Enemy* p) {}

bool8 FUN_0807be1c(struct Enemy* p) { return TRUE; }

void FUN_0807be20(struct Enemy* p) {
  struct Entity** slot;
  u8 m = (p->s).mode[2];
  if (m == 0) {
    (p->s).d.y = m;
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

static const struct Coord sElementCoord;

bool8 FUN_0807be50(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xbc);
  if (*slot == NULL && ((p->body).status & 1)) {
    struct VFX* e = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = e;
    if (e != NULL) {
      u8 attr = *(u8*)((u8*)p + 0x97) & 0xf0;
      if (attr == 0x10) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      } else if (attr == 0x30) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = 0;
      }
    }
  }
  return TRUE;
}

void nop_0807bea4(struct Enemy* p) {}

bool8 nop_0807bc8c(struct Enemy* p);
bool8 nop_0807bd3c(struct Enemy* p);
bool8 nop_0807bde4(struct Enemy* p);
bool8 FUN_0807be14(struct Enemy* p);
bool8 FUN_0807be1c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[5] = {
    (EnemyFunc)nop_0807bc8c,
    (EnemyFunc)nop_0807bd3c,
    (EnemyFunc)nop_0807bde4,
    (EnemyFunc)FUN_0807be14,
    (EnemyFunc)FUN_0807be1c,
};
// clang-format on

void FUN_0807bc90(struct Enemy* p);
void FUN_0807bd40(struct Enemy* p);
void FUN_0807bde8(struct Enemy* p);
void nop_0807be18(struct Enemy* p);
void FUN_0807be20(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[5] = {
    FUN_0807bc90,
    FUN_0807bd40,
    FUN_0807bde8,
    nop_0807be18,
    FUN_0807be20,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(24), PIXEL(24)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
