#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "mission.h"

void TryDropZakoDisk(struct Enemy* p, struct Coord* c);

struct Enemy* createHellBouncer(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_HELL_BOUNCER);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = a2;
    (p->s).work[1] = a3;
    (p->s).unk_28 = e;
  }
  return p;
}

void nop_0807fd1c(struct Enemy* p);
void HellBouncer_Update(struct Enemy* p);

// 0x0807E2E4
void HellBouncer_Init(struct Enemy* p) {
  register struct Body* b asm("r4");
  register s32 z5 asm("r5");
  s32 z7;
  s32 k10;
  struct Entity* q;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  {
    register s32 f asm("r0");
    register u8 fl asm("r1");
    register s32 k asm("r1");
    fl = (p->s).flags;
    f = 0xFE;
    f &= fl;
    z5 = 0;
    asm("" : "+r"(z5));
    k = 2;
    f |= k;
    z7 = 0;
    asm("" : "+r"(z7));
    k = 4;
    f |= k;
    (p->s).flags = f;
  }
  b = &p->body;
  ((void (*)(struct Body*, const struct Collision*, struct Coord*, s32))InitBody)(b, (const struct Collision*)0x08367D98, &(p->s).coord, 0x40);
  b->parent = (struct CollidableEntity*)p;
  b->fn = (BodyFunc)z5;
  asm volatile("" ::: "memory");
  *(s32*)((u8*)p + 0xb4) = 0x40;
  b->fn = (BodyFunc)nop_0807fd1c;
  {
    register u8 f2 asm("r0");
    f2 = (p->s).flags2;
    k10 = 0x10;
    f2 |= k10;
    (p->s).flags2 = f2;
  }
  q = (p->s).unk_28;
  (p->s).invincibleID = q->uniqueID;
  {
    register s32 w asm("r3");
    w = (p->s).work[0];
    if (w == 1) {
      register s32 xf asm("r2");
      register s32 t0 asm("r0");
      t0 = q->flags;
      xf = t0 >> 4;
      xf &= w;
      if (xf != 0) {
        register u8 f3 asm("r0");
        f3 = (p->s).flags;
        f3 |= k10;
        (p->s).flags = f3;
      } else {
        register u8 h asm("r1");
        register u8 g asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xEF;
        g &= h;
        (p->s).flags = g;
      }
      {
        register s32 v asm("r1");
        register u8* oa asm("r3");
        s32 sh4, ov, m11;
        v = 1;
        v &= xf;
        *((u8*)p + 0x4c) = v;
        oa = (u8*)p + 0x4a;
        sh4 = v << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
    }
  }
  {
    register s32 zz asm("r2");
    u8* a;
    zz = 0;
    (p->s).d.y = zz;
    (p->s).d.x = zz;
    a = (u8*)p + 0xbc;
    *(u32*)a = zz;
    asm("" : "+r"(a));
    a -= 3;
    asm("" : "+r"(a));
    *a = zz;
    {
      u8 w1 = (p->s).work[1];
      asm("" : "+r"(a));
      a -= 1;
      asm("" : "+r"(a));
      *a = w1;
    }
    asm("" : "+r"(a));
    a += 3;
    asm("" : "+r"(a));
    *a = zz;
    asm("" : "+r"(a));
    a += 6;
    asm("" : "+r"(a));
    *a = zz;
    asm("" : "+r"(a));
    a += 1;
    asm("" : "+r"(a));
    *a = zz;
    {
      register s32 w0 asm("r3");
      w0 = (p->s).work[0];
      if (w0 == 1) {
        register u32 tbl asm("r1");
        EntityFunc** rt;
        tbl = (u32)gEnemyFnTable;
        asm("" : "+r"(tbl));
        rt = (EntityFunc**)((((p->s).id) << 2) + tbl);
        *(u32*)((p->s).mode) = w0;
        (p->s).onUpdate = (void*)(*rt)[1];
        *((u8*)p + 0xd) = zz;
        asm volatile("");
      } else {
        SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
        (p->s).mode[1] = 2;
      }
    }
    (p->s).mode[2] = zz;
    (p->s).mode[3] = zz;
  }
  if (IsFrozen(&p->s)) {
    SetMotion(&p->s, MOTION(0xAB, 0x1B));
    UpdateMotionGraphic(&p->s);
  }
  HellBouncer_Update(p);
  asm volatile("" ::"l"(z5), "l"(z7));
}

INCASM("asm/enemy/hell_bouncer_p1_p2_p1.inc");

void HellBouncer_Die(struct Enemy* p) {
  if (gMission.enemyCount <= 0x270E) {
    gMission.enemyCount++;
  }
  TryDropZakoDisk(p, &(p->s).coord);
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

bool8 FUN_0807e5f0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/hell_bouncer_p2.inc");

bool8 FUN_0807ead8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/hell_bouncer_p3.inc");

bool8 FUN_0807f644(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/hell_bouncer_p4_p1.inc");

void nop_0807fd1c(struct Enemy* p) {}

void HellBouncer_Init(struct Enemy* p);
void HellBouncer_Update(struct Enemy* p);
void HellBouncer_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gHellBouncerRoutine = {
    [ENTITY_INIT] =      HellBouncer_Init,
    [ENTITY_UPDATE] =    HellBouncer_Update,
    [ENTITY_DIE] =       HellBouncer_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_0807e5f0(struct Enemy* p);
bool8 FUN_0807ead8(struct Enemy* p);
bool8 FUN_0807f644(struct Enemy* p);

static const EnemyFunc sUpdates1[3] = {
    (EnemyFunc)FUN_0807e5f0,
    (EnemyFunc)FUN_0807ead8,
    (EnemyFunc)FUN_0807f644,
};

void FUN_0807e5f4(struct Enemy* p);
void FUN_0807eadc(struct Enemy* p);
void FUN_0807f648(struct Enemy* p);

static const EnemyFunc sUpdates2[3] = {
    FUN_0807e5f4,
    FUN_0807eadc,
    FUN_0807f648,
};

static const struct Collision sCollisions[9] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(17), PIXEL(58), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(26), -PIXEL(16), PIXEL(20), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(36), PIXEL(37), PIXEL(56)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(24), -PIXEL(69), PIXEL(22), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(33), PIXEL(61), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(22), -PIXEL(27), PIXEL(22), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(5), -PIXEL(17), PIXEL(55), PIXEL(23)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(5), -PIXEL(17), PIXEL(55), PIXEL(23)},
    },
};
