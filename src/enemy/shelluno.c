#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mod.h"
#include "physics.h"
#include "story.h"
#include "zero.h"
#include "syssav.h"
#include "overworld_terrain.h"

extern const struct Collision sCollisions[6];

struct Enemy* CreateShelluno(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_SHELLUNO);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

static const struct Collision sCollisions[];
void FUN_0807a3ec(struct Body* body, struct Coord* c);
void Shelluno_Update(struct Enemy* p);

void Shelluno_Init(struct Enemy* p) {
  register struct Body* b asm("r4");
  InitNonAffineMotion(&p->s);
  {
    register s32 fl0 asm("r1");
    register u32 c1 asm("r0");
    register s32 z3 asm("r3");
    register u32 f asm("r2");
    fl0 = (p->s).flags;
    c1 = 1;
    asm("" : "+r"(c1));
    z3 = 0;
    asm("" : "+r"(z3));
    f = c1;
    f |= fl0;
    f |= 2;
    f |= z3;
    (p->s).flags = f;
    {
      u8 mv = gSystemSavedataManager.mods[14];
      u32 c4t = 4;
      asm("" : "+r"(c4t));
      if (c4t & mv) {
      register u32 sf asm("r5");
      {
        register s32 fb asm("r1");
        register u32 c40s asm("r0");
        fb = gCurStory.s.gameflags[0];
        c40s = 0x40;
        asm("" : "+r"(c40s));
        c40s &= fb;
        asm("" : "+r"(c40s));
        sf = (u8)c40s;
      }
      if (sf == 0) {
        f |= 4;
        (p->s).flags = f;
        b = &p->body;
        InitBody(b, sCollisions, &(p->s).coord, 9);
        b->parent = (void*)p;
        b->fn = (void*)sf;
        goto after;
      }
      }
    }
    {
      register s32 z5 asm("r5");
      register s32 fl2 asm("r1");
      register s32 c4b asm("r0");
      fl2 = (p->s).flags;
      c4b = 4;
      asm("" : "+r"(c4b));
      z5 = 0;
      (p->s).flags = c4b | fl2;
      b = &p->body;
      InitBody(b, sCollisions, &(p->s).coord, 5);
      b->parent = (void*)p;
      b->fn = (void*)z5;
    }
  after:;
  }
  {
    u8 w0 = (p->s).work[0];
    if (w0 == 0) {
      (p->s).flags &= 0xEF;
      ((p->s).spr).xflip = w0;
      {
        u8* oa = (u8*)&((p->s).spr).oam + 6;
        s32 ov = *oa;
        s32 m11 = -0x11;
        asm("" : "+r"(m11));
        *oa = m11 & ov;
      }
    } else {
      register s32 one asm("r2");
      register s32 fl3 asm("r1");
      register s32 c10b asm("r0");
      one = 1;
      fl3 = (p->s).flags;
      c10b = 0x10;
      asm("" : "+r"(c10b));
      (p->s).flags = c10b | fl3;
      ((p->s).spr).xflip = one;
      {
        register u8* oa asm("r3");
        register s32 c10c asm("r2");
        s32 ov;
        s32 m11;
        oa = (u8*)&((p->s).spr).oam + 6;
        c10c = 0x10;
        asm("" : "+r"(c10c));
        ov = *oa;
        m11 = -0x11;
        asm("" : "+r"(m11));
        *oa = (m11 & ov) | c10c;
      }
    }
  }
  (p->s).coord.y = FUN_0800a05c((p->s).coord.x, (p->s).coord.y);
  {
    u8* a9 = (u8*)p + 0xb9;
    s32 z5b = 0;
    *a9 = z5b;
    b->fn = (void*)FUN_0807a3ec;
    {
      u8* w = (u8*)p + 0x5c;
      *(s32*)(w + 4) = z5b;
      (p->s).d.x = z5b;
      asm("" : "+r"(w));
      w += 8;
      *(s32*)(w + 4) = z5b;
      (p->s).unk_coord.x = z5b;
      asm("" : "+r"(w));
      w += 0x58;
      *(s32*)w = z5b;
      asm("" : "+r"(w));
      w += 4;
      *w = z5b;
      asm("" : "+r"(w));
      w += 1;
      *w = z5b;
      asm("" : "+r"(w));
      w += 1;
      *w = z5b;
    }
    SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = z5b;
    (p->s).mode[2] = z5b;
    (p->s).mode[3] = z5b;
    if (IsFrozen(&p->s)) {
      SetMotion(&p->s, 0x3500);
      UpdateMotionGraphic(&p->s);
    }
    *((u8*)p + 0xba) = z5b;
  }
  Shelluno_Update(p);
}

extern const EnemyFunc sUpdates1[6];
extern const EnemyFunc sUpdates2[6];
s32 FUN_0807a3e8(struct Enemy* p);
void FUN_0807a244(struct Enemy* p);
void Shelluno_Die(struct Enemy* p);

void Shelluno_Update(struct Enemy* p) {
  u8 m;
  s32 sea;
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    if (FUN_0807a3e8(p)) {
      goto alive;
    }
  }
  SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  Shelluno_Die(p);
  return;

alive:
  (sUpdates1[(p->s).mode[1]])(p);
  FUN_0807a244(p);
  m = (p->s).mode[1];
  if (m == 2) goto water;
  if (m == 4) goto water;
  if (IsFrozen(&p->s)) {
    p->props[4] = (p->s).mode[1];
    return;
  }
water:
  sea = gOverworld.sea;
  if (sea > (p->s).coord.y - 0x400) {
    u8* fl = (u8*)((u8*)p + 0xc2);
    if (*fl == 0) {
      (p->s).d.y = 0;
    }
    *fl = 1;
    (p->s).d.y += 0x20;
    if ((p->s).d.y > 0x700) {
      (p->s).d.y = 0x700;
    }
    (p->s).coord.y += (p->s).d.y;
    return;
  } else {
    u8* fl = (u8*)((u8*)p + 0xc2);
    if (*fl == 1) {
      (p->s).mode[1] = 0;
      (p->s).mode[2] = 0;
    }
    *fl = 0;
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

INCASM("asm/enemy/shelluno_p1_p2_b.inc");

bool8 nop_0807939c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p2_p1.inc");

bool8 FUN_080795b8(struct Enemy* p) {
  if (gOverworld.sea > (p->s).coord.y - 0xc00) {
    u8* t = (u8*)((u8*)p + 0xc1);
    s32 zero = 0;
    *t = 0x3c;
    (p->s).d.y = zero;
    (p->s).mode[1] = zero;
    (p->s).mode[2] = zero;
  }
  return TRUE;
}

INCASM("asm/enemy/shelluno_p2_p2.inc");

bool8 FUN_0807a018(struct Enemy* p) { return TRUE; }

void FUN_0807a01c(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[3]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[2]);
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0807a064(struct Enemy* p) { return TRUE; }


void FUN_0807a068(struct Enemy* p) {}

bool8 FUN_0807a06c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p5.inc");

bool8 FUN_0807a0fc(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p6a.inc");

void FUN_0807a46c(struct Enemy* p);

void shelluno_0807a100(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8* a9 = (u8*)p + 0xb9;
      u32 c1r = 1;
      asm("" : "+r"(c1r));
      *a9 = 1;
      (p->s).work[2] = 0x20;
      SetMotion(&p->s, 0x3509);
      SetDDP(&p->body, &sCollisions[4]);
      {
        u32 xf = ((pZero2->s).flags >> 4) & c1r;
        (p->s).mode[3] = xf;
        if (xf == 0) {
          (p->s).d.x = -0x280;
          (p->s).unk_coord.x = 0x100;
        } else {
          (p->s).d.x = 0x280;
          (p->s).unk_coord.x = -0x100;
        }
      }
      (p->s).d.y = 0;
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      u16 a = GetGroundMetatileAttr((p->s).coord.x + (p->s).d.x, (p->s).coord.y + (p->s).d.y);
      if (a != 0) {
        if (!(a & 0x8000)) {
          SET_ENEMY_ROUTINE(p, ENTITY_DIE);
          break;
        }
      }
      {
        s32 cx = (p->s).coord.x;
        s32 dx = (p->s).d.x;
        s32 ny;
        (p->s).coord.x = cx + dx;
        ny = (p->s).coord.y + (p->s).d.y;
        (p->s).coord.y = ny;
        dx += (((p->s).unk_coord.x - dx) << 3) >> 8;
        (p->s).d.x = dx;
        {
          s32 g = FUN_0800a05c((p->s).coord.x, ny + -0x2000);
          if (g - (p->s).coord.y <= 0x40) {
            (p->s).coord.y = g;
          }
        }
      }
      FUN_0807a46c(p);
      {
        u8 m3 = (p->s).mode[3];
        if (m3 == 0) {
          if ((p->s).d.x >= 0) {
            (p->s).mode[1] = m3;
            (p->s).mode[2] = m3;
          }
        } else {
          if ((p->s).d.x <= 0) {
            (p->s).mode[1] = 0;
            (p->s).mode[2] = 0;
          }
        }
      }
      {
        u8 w2 = (p->s).work[2];
        if (w2 != 0) {
          s32 raw2 = w2 - 1;
          u8 t;
          (p->s).work[2] = raw2;
          t = raw2;
          if (t == 0) {
            *((u8*)p + 0xb9) = t;
            SetMotion(&p->s, 0x3500);
            SetDDP(&p->body, sCollisions);
          }
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/enemy/shelluno_p6b.inc");

s32 FUN_0807a3e8(struct Enemy* p) { return TRUE; }

// A pure r4/r5 swap from a match: retail gives the collision pointer the
// lower callee-saved register and the coord parameter the higher; agbcc
// assigns the opposite pair in every spelling tried.
NON_MATCH void FUN_0807a3ec(struct Body* body, struct Coord* c) {
#if MODERN
  const struct Collision* col = (body->enemy)->processing;
  u8 t = col->atkType;
  if (t == 3 || t == 14 || t == 15) {
    struct CollidableEntity* parent = body->parent;
    if ((parent->body).status & BODY_STATUS_DEAD) {
      if ((parent->s).coord.x < c->x) {
        ((struct Enemy*)parent)->props[6] = 0xFF;
      } else {
        ((struct Enemy*)parent)->props[6] = 0xFE;
      }
    }
  }
  if ((*(u32*)((u8*)col + 4) & 0x200FF) == 0x20002) {
    struct CollidableEntity* parent = body->parent;
    if ((parent->s).mode[1] != 5 && ((struct Enemy*)parent)->props[5] != 0) {
      SET_ENEMY_ROUTINE((struct Enemy*)parent, ENTITY_DIE);
    }
  }
#else
  INCCODE("asm/enemy/shelluno_a3ec.inc");
#endif
}

INCASM("asm/enemy/shelluno_p7b.inc");

void Shelluno_Init(struct Enemy* p);
void Shelluno_Update(struct Enemy* p);
void Shelluno_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gShellunoRoutine = {
    [ENTITY_INIT] =      Shelluno_Init,
    [ENTITY_UPDATE] =    Shelluno_Update,
    [ENTITY_DIE] =       Shelluno_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_0807939c(struct Enemy* p);
bool8 FUN_080795b8(struct Enemy* p);
bool8 FUN_0807a018(struct Enemy* p);
bool8 FUN_0807a064(struct Enemy* p);
bool8 FUN_0807a06c(struct Enemy* p);
bool8 FUN_0807a0fc(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)nop_0807939c,
    (EnemyFunc)FUN_080795b8,
    (EnemyFunc)FUN_0807a018,
    (EnemyFunc)FUN_0807a064,
    (EnemyFunc)FUN_0807a06c,
    (EnemyFunc)FUN_0807a0fc,
};
// clang-format on

void shelluno_080793a0(struct Enemy* p);
void FUN_080795f0(struct Enemy* p);
void FUN_0807a01c(struct Enemy* p);
void FUN_0807a068(struct Enemy* p);
void shelluno_0807a070(struct Enemy* p);
void shelluno_0807a100(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    shelluno_080793a0,
    FUN_080795f0,
    FUN_0807a01c,
    FUN_0807a068,
    shelluno_0807a070,
    shelluno_0807a100,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(18), PIXEL(25)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(18), PIXEL(25)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(9)};
