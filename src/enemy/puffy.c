#include "collision.h"
#include "element.h"
#include "enemy.h"
#include "global.h"
#include "overworld.h"
#include "overworld_terrain.h"

struct Enemy* CreatePuffy(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_PUFFY);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

static const struct Collision sCollisions[2];
void Puffy_Update(struct Enemy* p);
void FUN_0807cba4(struct Body* body);

void Puffy_Init(struct Enemy* p) {
  register s32 z6 asm("r6");
  s32 z7;
  register s32 one8 asm("r8");
  s32 y2;
  InitNonAffineMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    d0 |= f0;
    d0 |= FLIPABLE;
    z6 = 0;
    d0 &= 0xEF;
    z7 = 0;
    (p->s).flags = d0;
  }
  one8 = 1;
  ((p->s).spr).xflip = z7;
  {
    u8* a = (u8*)p + 0x4a;
    register u8 b asm("r1");
    s32 msk;
    b = *a;
    msk = -0x11;
    msk &= b;
    *a = msk;
  }
  (p->s).flags |= COLLIDABLE;
  {
    struct Body* body;
    body = &p->body;
    InitBody(body, sCollisions, &(p->s).coord, 6);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)FUN_0807cba4;
  }
  {
    struct Overworld* ow = &gOverworld;
    register u32 so asm("r1");
    s32 sea;
    asm("" : "+r"(ow));
    so = 0x2C00C;
    asm("" : "+r"(so));
    {
      u8* a2 = (u8*)ow;
      asm("" : "+r"(a2));
      a2 += so;
      sea = *(s32*)a2;
    }
    y2 = (p->s).coord.y;
    if (sea <= y2) {
      goto underwater;
    }
  }
  {
    register u8 f1 asm("r1");
    register s32 f2 asm("r0");
    f1 = (p->s).flags;
    f2 = 0xFE;
    f2 &= f1;
    {
      register s32 c2 asm("r1");
      c2 = 0xFD;
      f2 &= c2;
    }
    (p->s).flags = f2;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
underwater:
  {
    u8* q = (u8*)p + 0xb4;
    (p->s).unk_coord.y = y2;
    *(s32*)q = y2;
    q -= 0x58;
    *(s32*)(q + 4) = z6;
    (p->s).d.x = z6;
    q += 0x60;
    *(s32*)q = z6;
    q -= 4;
    *q = z6;
    q += 8;
    *q = one8;
  }
  {
    u32 tb = (u32)gEnemyFnTable;
    const EnemyRoutine** ta = (const EnemyRoutine**)(tb + (p->s).id * 4);
    {
      register s32 mv asm("r1");
      mv = one8;
      *(u32*)&(p->s).mode[0] = mv;
    }
    (p->s).onUpdate = (void*)(**ta)[ENTITY_UPDATE];
  }
  (p->s).mode[1] = z6;
  (p->s).mode[2] = z6;
  (p->s).mode[3] = z6;
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(0x41, 0x00));
    UpdateMotionGraphic(&p->s);
  }
  Puffy_Update(p);
}

extern const EnemyFunc PTR_ARRAY_08367aec[4];
extern const EnemyFunc PTR_ARRAY_08367afc[4];
bool32 FUN_0807cb50(struct Enemy* p);
void Puffy_Die(struct Enemy* p);

void Puffy_Update(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Puffy_Die(p);
  } else {
    (PTR_ARRAY_08367aec[(p->s).mode[1]])(p);
    FUN_0807cb50(p);
    if (IsFrozen(&p->s)) {
      u8 m = (p->s).mode[1];
      *(u8*)((u8*)p + 0xba) = m;
    } else {
      (PTR_ARRAY_08367afc[(p->s).mode[1]])(p);
    }
  }
}

INCASM("asm/enemy/puffy_p1_p2_c.inc");

bool8 nop_0807c968(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/puffy_p2.inc");

bool8 nop_0807ca98(struct Enemy* p) { return TRUE; }

void FUN_0807ca9c(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) (p->s).mode[2] = 1;
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 nop_0807cac8(struct Enemy* p) { return TRUE; }


void nop_0807cacc(struct Enemy* p) {}

bool8 nop_0807cad0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/puffy_p5_p1.inc");

static const struct Coord sElementCoord;

bool32 FUN_0807cb50(struct Enemy* p) {
  struct VFX** slot = (struct VFX**)((u8*)p + 0xBC);
  struct VFX* e = *slot;
  if (e == NULL && ((p->body).status & BODY_STATUS_WHITE)) {
    struct VFX* n = ApplyElementEffect(0, &p->s, &sElementCoord);
    *slot = n;
    if (n != NULL) {
      u8 b = *((u8*)p + 0x97) & 0xF0;
      if (b == 0x10) {
        // e is provably NULL here; stored through it to keep the register
        (p->s).mode[1] = 1, (p->s).mode[2] = (u32)e;
      } else if (b == 0x30) {
        (p->s).mode[1] = 3, (p->s).mode[2] = (u32)e;
      }
    }
  }
  return TRUE;
}

void FUN_0807cba4(struct Body* body) {
  struct Enemy* parent = (struct Enemy*)body->parent;
  if ((*(u32*)((u8*)parent + 0x8c) & 0x200) && (gCollisionManager.sweep & 2)) {
    *(u8*)((u8*)parent + 0xc0) = 0;
  }
}

int dragInSea(struct Entity* p) {
  s32 sea = gOverworld.sea;
  if (sea > p->coord.y) {
    p->coord.y = sea;
  }
}

void Puffy_Init(struct Enemy* p);
void Puffy_Update(struct Enemy* p);
void Puffy_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPuffyRoutine = {
    [ENTITY_INIT] =      Puffy_Init,
    [ENTITY_UPDATE] =    Puffy_Update,
    [ENTITY_DIE] =       Puffy_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_0807c968(struct Enemy* p);
bool8 nop_0807ca98(struct Enemy* p);
bool8 nop_0807cac8(struct Enemy* p);
bool8 nop_0807cad0(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367aec[4] = {
    (EnemyFunc)nop_0807c968,
    (EnemyFunc)nop_0807ca98,
    (EnemyFunc)nop_0807cac8,
    (EnemyFunc)nop_0807cad0,
};

void FUN_0807c96c(struct Enemy* p);
void FUN_0807ca9c(struct Enemy* p);
void nop_0807cacc(struct Enemy* p);
void FUN_0807cad4(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367afc[4] = {
    FUN_0807c96c,
    FUN_0807ca9c,
    nop_0807cacc,
    FUN_0807cad4,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(28), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(6), PIXEL(28), PIXEL(28)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
