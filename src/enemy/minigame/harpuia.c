#include "collision.h"
#include "enemy.h"
#include "global.h"

static const EnemyFunc sUpdates1[6];
static const EnemyFunc sUpdates2[6];

struct Enemy* FUN_0809af20(struct Entity* e, struct Coord* c, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HARPUIA_MG);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Enemy* FUN_0809af88(struct Entity* e, struct Coord* c, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HARPUIA_MG);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = 1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Enemy* FUN_0809aff0(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HARPUIA_MG);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = 2;
    (p->s).work[1] = a2;
    p->props[0] = a3;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Enemy* FUN_0809b064(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HARPUIA_MG);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = 3;
    (p->s).work[1] = a2;
    p->props[0] = a3;
    (p->s).unk_28 = e;
  }
  return p;
}

static const struct Collision sCollisions[5];
void FUN_0809bd2c(struct Body* body);
void HarpuiaMinigameEnemy_Update(struct Enemy* p);

// Cross-arm register-economy basin: retail recycles the work[0] load (r7) as
// per-arm zero/one/two sources while keeping per-arm 0x10/one webs in r4/r5
// and fresh or-consts; every pin/barrier/literal-asm combination taken either
// spills a web to r8, folds the oam insert mask, or duplicates the consts.
NON_MATCH void HarpuiaMinigameEnemy_Init(struct Enemy* p) {
#if MODERN
  u8 w0 = (p->s).work[0];
  if (w0 == 0) {
    s32 one;
    u32 k10;
    InitNonAffineMotion(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    ResetDynamicMotion(&p->s);
    (p->s).taskCol = 0x11;
    one = 1;
    k10 = 0x10;
    (p->s).flags |= k10;
    (p->s).spr.xflip = one;
    {
      u8* q = (u8*)p + 0x4a;
      s32 m11 = -0x11;
      asm("" : "+r"(m11));
      *q = (*q & m11) | 0x10;
    }
    {
      struct Coord c;
      s32 cx = (p->s).coord.x;
      s32 cy = (p->s).coord.y;
      c.x = cx;
      c.y = cy;
      (p->s).unk_2c = (struct Entity*)FUN_0809af88(&p->s, &c, 0);
    }
    k10 |= (p->s).flags2;
    (p->s).flags2 = k10;
    (p->s).invincibleID = ((struct Entity*)(p->s).unk_28)->uniqueID;
    {
      u32 tbl = (u32)gEnemyFnTable;
      u32 id = (p->s).id << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = one;
      (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
    }
    (p->s).mode[1] = w0;
    (p->s).mode[2] = w0;
    (p->s).mode[3] = w0;
  } else if (w0 == 1) {
    u32 k10b;
    u32 z4;
    InitNonAffineMotion(&p->s);
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    ResetDynamicMotion(&p->s);
    (p->s).taskCol = 0xF;
    k10b = 0x10;
    (p->s).flags |= k10b;
    z4 = 0;
    (p->s).spr.xflip = w0;
    {
      u8* q = (u8*)p + 0x4a;
      s32 m11b = -0x11;
      asm("" : "+r"(m11b));
      *q = (*q & m11b) | 0x10;
    }
    k10b |= (p->s).flags2;
    (p->s).flags2 = k10b;
    (p->s).invincibleID = ((struct Entity*)((struct Entity*)(p->s).unk_28)->unk_28)->uniqueID;
    {
      u32 tbl = (u32)gEnemyFnTable;
      u32 id = (p->s).id << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = w0;
      (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
    }
    (p->s).mode[1] = 3;
    (p->s).mode[2] = z4;
    (p->s).mode[3] = z4;
  } else if (w0 == 2) {
    u32 f;
    u32 z2;
    register s32 z5 asm("r5");
    struct Body* body;
    InitNonAffineMotion(&p->s);
    f = (p->s).flags;
    {
      u32 c1 = 1;
      asm("" : "+r"(c1));
      z2 = 0;
      asm("" : "+r"(z2));
      z5 = 0;
      f |= c1;
    }
    {
      u32 c2t;
      asm volatile("movs %0, #2" : "=r"(c2t));
      f |= c2t;
    }
    f |= z2;
    (p->s).flags = f;
    if (*((u8*)p + 0xb4) == 1) {
      f |= COLLIDABLE;
      (p->s).flags = f;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 0x18);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
      (p->s).palID = w0;
    } else {
      f |= COLLIDABLE;
      (p->s).flags = f;
      body = &p->body;
      InitBody(body, sCollisions, &(p->s).coord, 8);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5;
      (p->s).palID = 1;
    }
    body->fn = (void*)FUN_0809bd2c;
    {
      u32 tbl = (u32)gEnemyFnTable;
      u32 id = (p->s).id << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      EntityFunc* t1;
      u8 m4;
      *(u32*)((p->s).mode) = 1;
      t1 = *rt;
      m4 = 4;
      (p->s).onUpdate = (void*)t1[ENTITY_UPDATE];
      (p->s).mode[1] = m4;
    }
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
  } else {
    s32 z5b;
    u32 fb;
    InitNonAffineMotion(&p->s);
    fb = (p->s).flags;
    {
      u32 c1b = 1;
      asm("" : "+r"(c1b));
      z5b = 0;
      fb |= c1b;
    }
    {
      u32 c2b = 2;
      asm("" : "+r"(c2b));
      fb |= c2b;
    }
    {
      u32 c4b = 4;
      asm("" : "+r"(c4b));
      fb |= c4b;
    }
    (p->s).flags = fb;
    {
      struct Body* body = &p->body;
      InitBody(body, &sCollisions[3], &(p->s).coord, 4);
      body->parent = (struct CollidableEntity*)p;
      body->fn = (void*)z5b;
    }
    (p->s).palID = z5b;
    {
      u32 tbl = (u32)gEnemyFnTable;
      u32 id = (p->s).id << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 1;
      (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
    }
    (p->s).mode[1] = 5;
    (p->s).mode[2] = z5b;
    (p->s).mode[3] = z5b;
  }
  HarpuiaMinigameEnemy_Update(p);
#else
  INCCODE("asm/enemy/minigame_harpuia_init.inc");
#endif
}

void HarpuiaMinigameEnemy_Update(struct Enemy* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void HarpuiaMinigameEnemy_Die(struct Enemy* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
}

bool8 FUN_0809b350(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/minigame_harpuia_p1_p2.inc");

bool8 FUN_0809b408(struct Enemy* p) { return TRUE; }

void FUN_0809b40c(struct Enemy* p) {}

bool8 FUN_0809b410(struct Enemy* p) { return TRUE; }

void FUN_0809b414(struct Enemy* p) {}

bool8 FUN_0809b418(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/minigame_harpuia_p3_post_p1.inc");

bool8 FUN_0809b4d8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/minigame_harpuia_p3_post_p2.inc");

bool8 FUN_0809b950(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/minigame_harpuia_p3_post_p3.inc");

void HarpuiaMinigameEnemy_Init(struct Enemy* p);
void HarpuiaMinigameEnemy_Update(struct Enemy* p);
void HarpuiaMinigameEnemy_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gHarpuiaMinigameEnemyRoutine = {
    [ENTITY_INIT] =      HarpuiaMinigameEnemy_Init,
    [ENTITY_UPDATE] =    HarpuiaMinigameEnemy_Update,
    [ENTITY_DIE] =       HarpuiaMinigameEnemy_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

bool8 FUN_0809b350(struct Enemy* p);
bool8 FUN_0809b408(struct Enemy* p);
bool8 FUN_0809b410(struct Enemy* p);
bool8 FUN_0809b418(struct Enemy* p);
bool8 FUN_0809b4d8(struct Enemy* p);
bool8 FUN_0809b950(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)FUN_0809b350,
    (EnemyFunc)FUN_0809b408,
    (EnemyFunc)FUN_0809b410,
    (EnemyFunc)FUN_0809b418,
    (EnemyFunc)FUN_0809b4d8,
    (EnemyFunc)FUN_0809b950,
};
// clang-format on

void FUN_0809b354(struct Enemy* p);
void FUN_0809b40c(struct Enemy* p);
void FUN_0809b414(struct Enemy* p);
void FUN_0809b41c(struct Enemy* p);
void FUN_0809b4dc(struct Enemy* p);
void FUN_0809b954(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    FUN_0809b354,
    FUN_0809b40c,
    FUN_0809b414,
    FUN_0809b41c,
    FUN_0809b4dc,
    FUN_0809b954,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 8,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(18), PIXEL(18)},
    },
};
